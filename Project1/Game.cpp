/**
 * \file Game.cpp
 *
 * \author Zachary Morris
 */

#include "pch.h"

#include <algorithm>
#include <memory>
#include "Grid.h"
#include "Game.h"
#include "Tower.h"
#include "Tower8Shot.h"
#include "Item.h"
#include "Tile.h"
#include "ControlPanel.h"
#include "Scoreboard.h"
#include "ItemVisitor.h"
#include "TowerCounter.h"
#include "ProjectileCounter.h"
#include "BalloonCounter.h"

using namespace std;
using namespace Gdiplus;


/// The directory containing the file images
static const std::wstring ImagesDirectory = L"images/";


/// Constructor
CGame::CGame()
{
	// create Grid
	mGrid = make_shared<CGrid>(this);

	// create ControlPanel
	mControlPanel = make_shared<CControlPanel>(this);
}

/// Destructor
CGame::~CGame()
{
}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);

    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    // From here on you are drawing virtual pixels
    mGrid->OnDraw(graphics);
    mControlPanel->OnDraw(graphics);
	
	//Use visitors for balloons, projectiles, and towers
	CBalloonCounter balloonVisitor;
	Accept(&balloonVisitor);
	std::vector<CBalloon*> balloonVector = balloonVisitor.GetBalloons();
	CProjectileCounter projectileVisitor;
	Accept(&projectileVisitor);
	std::vector<CProjectile*> projectileVector = projectileVisitor.GetProjectiles();
	CTowerCounter towerVisitor;
	Accept(&towerVisitor);
	std::vector<CTower*> towerVector = towerVisitor.GetTowers();

	//Balloon Updates
	for (auto balloon : balloonVector)
	{
		balloon->Draw(graphics);
	}

	//Projectile Updates
	for (auto projectile : projectileVector)
	{
		projectile->Draw(graphics);
	}

	//Tower Updates
	for (auto tower : towerVector)
	{
		tower->Draw(graphics);
	}
    
	//Draws level text
	if (mLevelTimer <= 2) {
		Transition(graphics,width,height);
	}
}

/** The way you set the image
* \param file The file being opened
* \param id the Id to be stored for lookup
* \return bitmap of image
*/
shared_ptr<Gdiplus::Bitmap> CGame::SetImage(const wstring& id, const wstring& file)
{
	if (mDeclarations.find(file) != mDeclarations.end())
	{
		return mDeclarations.at(id);
	}
	wstring filename = ImagesDirectory + file;
	shared_ptr<Gdiplus::Bitmap> bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	mDeclarations.insert(pair<wstring, shared_ptr<Bitmap>>(id, bitmap));
	return bitmap;
}

/**
 *  Used by CItem objects to lookup image bitmap.
 * \param file File name
 * \returns image bitmap
 */
shared_ptr<Gdiplus::Bitmap> CGame::GetDeclaration(const wstring file)
{
	if (mDeclarations.find(file) == mDeclarations.end())
	{
		return 0;
	}
	return mDeclarations.at(file);
}

/**
* Handle a click on the game area
* \param x X location clicked on
* \param y Y location clicked on
*/
void CGame::OnLButtonDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

	if (!mActive) // cannot add towers while game is active
	{
		if (oX > 1024) // Grabbed Control Panel Tower
		{
			mGrabbedItem = mControlPanel->HitTest(oX, oY);
		}
		else // Grabbed Tower on Grid
		{
			mGrabbedItem = this->HitTest(oX, oY);
		}
	}
}

/**
* Handle a mouse movement on the game area
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
*/
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	double oX = (point.x - mXOffset) / mScale;
	double oY = (point.y - mYOffset) / mScale;

	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(oX, oY);
		}
		else // When the left button is released, we release the item.
		{
			shared_ptr<CTile> tile = TileTest(oX, oY);
			if (tile != nullptr) // Released on available tile
			{
				mGrabbedItem->SetLocation(tile->GetX(), tile->GetY());
				tile->SetAssociatedTower(mGrabbedItem);
				mGrabbedItem->SetTile(tile);

			}
			else // Released on non-available tile (delete)
			{
				DeleteItem(mGrabbedItem);
			}
			mGrabbedItem = nullptr;
		}
	}
}



/** Adding an item to the game
* \param item The item to be added
*/
void CGame::AddItem(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}


/** Delete an item from the game
* \param item The item to be removed
*/
void CGame::DeleteItem(CItem* item)
{

	// Find Item to Delete
	shared_ptr<CItem> deleteItem;
	for (auto i : mItems)
	{
		if (i.get() == item)
		{
			deleteItem = i;
		}
	}

	// Erase Item
	auto loc = find(::begin(mItems), ::end(mItems), deleteItem);
	if (loc != ::end(mItems))
	{
		mItems.erase(loc);
	}
}

/**
 * Moved passed item to front (end of mItems) if in mItems
 * \param item Item in control panel to be moved to front */
void CGame::MoveToFront(CItem* item)
{
	// Find Item to Move
	for (auto i : mItems)
	{
		if (i.get() == item)
		{
			// Move Item
			auto loc = find(begin(mItems), end(mItems), i);
			if (loc != end(mItems))
			{
				mItems.erase(loc);
				mItems.push_back(i);
			}
			break;
		}
	}
}


/** Test an x,y click location to see if it clicked on some item in the grid.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none. */
CTower* CGame::HitTest(int x, int y)
{
	// visitor to make a collection of towers
	CTowerCounter visitor;
	this->Accept(&visitor);
	vector<CTower*> towers = visitor.GetTowers();

	for (auto i = towers.rbegin(); i != towers.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			CTower* tower = *i;

			//TODO Fix Downcasting
			//shared_ptr<CTower> tower = std::dynamic_pointer_cast<CTower>(clickedItem);

			// Get old tile, set valid to true and set tower to nullptr
			shared_ptr<CTile> tile = tower->GetTile();
			tile->SetAssociatedTower(nullptr);
			tile->SetValidSpot(true);

			// Set tower's tile to nullptr
			tower->SetTile(nullptr);
			MoveToFront(tower);

			return tower;
		}
	}
	return nullptr;
}

/** Checking if the tower is dropped on available space
* \param x The X coordinate
* \param y The Y coordinate
* \returns Pointer to item we clicked on or nullptr if none. */
shared_ptr<CTile> CGame::TileTest(int x, int y)
{
	return mGrid->TileTest(x, y);
}


/** Check if any item is colliding (projectiles and balloons) */
void CGame::CollisionCheck()
{
	vector<CBalloon*> balloonsToDelete;
	CProjectileCounter projectileVisitor;
	CBalloonCounter balloonVisitor;
	Accept(&projectileVisitor);
	Accept(&balloonVisitor);

	for (auto projectile : projectileVisitor.GetProjectiles())
	{
		for (auto balloon : balloonVisitor.GetBalloons())
		{
			bool checkX = projectile->GetX() >= balloon->GetX() - 24
				&& projectile->GetX() <= balloon->GetX() + 24;
			bool checkY = projectile->GetY() >= balloon->GetY() - 24
				&& projectile->GetY() <= balloon->GetY() + 24;
			if (checkX && checkY) // both items colliding
			{
				balloonsToDelete.push_back(balloon);
				mControlPanel->GetScoreboard()->UpdateScore(projectile->GetPoints());
			}
		}
	}
	for (auto balloon : balloonsToDelete)
	{
		balloon->GetTileOn()->DeleteBalloon(balloon);
		DeleteItem(balloon);
	}
}

/**
* Checks every balloon's distance to a specific tower (for wave and bomb tower)
* \param x x position of tower
* \param y y position of tower
* \param maxDistance maximum distance a balloon can be to be popped
* \param score Point value associated with tower's shooting mechanism
*/
void CGame::BalloonChecker(int x, int y, double maxDistance, int score)
{
	CBalloonCounter counter;
	Accept(&counter);
	std::vector<CBalloon*> toRemove;
	for (auto balloon : counter.GetBalloons())
	{
		//Distance is the distance between the two objects minus 24 due to balloon size
		double distance = sqrt(pow(x - balloon->GetX(), 2) + pow(y - balloon->GetY(), 2) * 1.0) - 24;

		//If distance is less or equal than maxDistance, pop balloon
		if (distance <= maxDistance)
		{
			toRemove.push_back(balloon);
		}

	}

	for (auto balloon : toRemove)
	{
		balloon->GetTileOn()->DeleteBalloon(balloon);
		DeleteItem(balloon);
		mControlPanel->GetScoreboard()->UpdateScore(score);
	}
}

/** Used by SniperTower. Finds closest balloon to its position
 * \param x X coordinate of Tower
 * \param y Y coordinate of Tower
 * \returns Balloon closest to tower */
CBalloon* CGame::GetClosestBalloon(int x, int y)
{
	CBalloonCounter balloonVisitor;
	Accept(&balloonVisitor);
	CBalloon* closestBalloon = nullptr;
	double minDist = std::numeric_limits<double>::infinity();
	for (auto balloon : balloonVisitor.GetBalloons())
	{
		double dist = sqrt(pow((balloon->GetX() - x), 2) + pow((balloon->GetY() - y), 2));
		if (dist < minDist)
		{
			minDist = dist;
			closestBalloon = balloon;
		}
	}
	return closestBalloon;
}


/** Loading the game
* \param filename The filename of the file to load into the game
*/
void CGame::Load(const std::wstring& filename)
{
	Clear();

	if (filename == L"levels/level0a.xml" || filename == L"levels/level0.xml")
	{
		mLevel = 0;
	}
	else if (filename == L"levels/level1.xml")
	{
		mLevel = 1;
	}
	else if (filename == L"levels/level2.xml")
	{
		mLevel = 2;
	}
	else
	{
		mLevel = 3;
	}

	mGrid->Load(filename);
}

/**
*  Clear the game data.
*
* Deletes all known items in the game.
*/
void CGame::Clear()
{
	mGrid->Clear();
	mActive = false;
	mItems.clear();
	mControlPanel->Reset();
	mBalloonCount = 5;
	mLevelTimer = 0;
}

/** Handle updates for animation
* \param elapsed The time since the last update */
void CGame::Update(double elapsed)
{
	mControlPanel->Update(elapsed);

	mLevelTimer = mLevelTimer + elapsed;

	// While game is active, call update on item list
	if (mActive == true)
	{
		if (mBalloonCount != 0)
		{
			mBalloonCount--;
			shared_ptr<CBalloon> balloon = make_shared<CBalloon>(this, mGrid->GetStartX(), mGrid->GetStartY());
			AddItem(balloon);
			mGrid->GetStartTile()->AddBalloon(balloon.get());
		}

		mGrid->Update(elapsed);

		//Use visitors for projectiles and towers
		CProjectileCounter projectileVisitor;
		Accept(&projectileVisitor);
		std::vector<CProjectile*> projectileVector = projectileVisitor.GetProjectiles();
		CTowerCounter towerVisitor;
		Accept(&towerVisitor);
		std::vector<CTower*> towerVector = towerVisitor.GetTowers();

		//Projectile Updates
		for (auto projectile : projectileVector)
		{
			projectile->Update(elapsed);
			CollisionCheck();
		}
		
		//Tower Updates
		for (auto tower : towerVector)
		{
			tower->Update(elapsed);
		}
		
		// End of the level check
		CBalloonCounter ballooncounter;
		Accept(&ballooncounter);
		// No more balloons to spawn and no more in the game
		if (mBalloonCount == 0 && ballooncounter.GetNumBalloons() == 0)
		{
			mLevelTimer = 0;
			mLevel++;
			switch (mLevel)
			{
			case(1):
				Load(L"levels/level1.xml");
				break;
			case(2):
				Load(L"levels/level2.xml");
				break;
			default:
				Load(L"levels/level3.xml");
				break;
			}
		}
	}
}


/**
 * Accept Visitor into Game
 * \param visitor Derived visitor class
 */
void CGame::Accept(CItemVisitor* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}



/**
* Draws the level X on the screen
* \param graphics The graphics system
* \param level Which level does it draw
*/
void CGame::Transition(Gdiplus::Graphics* graphics, int width, int height)
{
	FontFamily  fontFamily(L"Arial");
	Gdiplus::Font        font(&fontFamily, 100, FontStyleRegular, UnitPixel);
	PointF      pointF(width/4, height/2);
	SolidBrush  solidBrush(Color::Maroon);

	//Display the words of the level on the string
	switch (mLevel)
	{
		case(0):
			graphics->DrawString(L"Level 0 Begin", -1, &font, pointF, &solidBrush);
			break;
		case(1): 
			graphics->DrawString(L"Level 1 Begin", -1, &font, pointF, &solidBrush);
			break;
		case(2): 
			graphics->DrawString(L"Level 2 Begin", -1, &font, pointF, &solidBrush);
			break;
		case(3): 
			graphics->DrawString(L"Level 3 Begin", -1, &font, pointF, &solidBrush);
			break;
		default: 
			graphics->DrawString(L"Level 3 Begin", -1, &font, pointF, &solidBrush);
			break;
	}
}
