/**
 * \file ControlPanel.cpp
 *
 * \author Connor Mears
 */


#include "pch.h"
#include "Game.h"
#include "ControlPanel.h"
#include "Scoreboard.h"
#include "Tower.h"
#include "TowerWave.h"
#include "Tower8Shot.h"
#include "TowerBomb.h"
#include "TowerSniper.h"
#include "Tile.h"
#include "RoadTile.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using namespace Gdiplus;

/**
* Constructor
* \param game Game the control panel is contained in
*/
CControlPanel::CControlPanel(CGame *game)
{
	mGame = game;

	mGoButton = make_unique<CGoButton>(mGame, 1084, 875);

	mScoreboard = make_shared<CScoreboard>();
	Reset();
}


/**
* Destructor
*/
CControlPanel::~CControlPanel()
{
}


/**
 * Reset the Items, put back Control Panel Towers (for Level load)
 */
void CControlPanel::Reset()
{
	// Reset button on level transition
	mGoButton = make_unique<CGoButton>(mGame, 1084, 875);

	// Reset Bomb Tower Count
	mBombCount = 0;

	// Create Tower Items in Control Panel
	mControlTowers.push_back(make_shared<CTowerWave>(mGame, 1124, 82));
	mControlTowers.push_back(make_shared<CTower8Shot>(mGame, 1124, 182));
	mControlTowers.push_back(make_shared<CTowerBomb>(mGame, 1124, 282, 0));
	mControlTowers.push_back(make_shared<CTowerSniper>(mGame, 1124, 382));
}


/** Draw the game area
 * \param graphics The GDI+ graphics context to draw on */
void CControlPanel::OnDraw(Gdiplus::Graphics* graphics)
{
	// Draw Control Towers
	for (auto tower : mControlTowers)
	{
		tower->Draw(graphics);
	}


	// Draw Score
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 30);
	RectF        rectF(1024.0f, 470.0f, 200.0f, 140.0f);
	StringFormat stringFormat;
	SolidBrush   yellow(Color(255, 255, 0));

	// Center-justify each line of text.
	stringFormat.SetAlignment(StringAlignmentCenter);

	// Center the block of text (top to bottom) in the rectangle.
	stringFormat.SetLineAlignment(StringAlignmentCenter);

	graphics->DrawString(L"Score", -1, &font, PointF(1049, 450), &yellow);

	wstring score = to_wstring(mScoreboard->GetScore());
	graphics->DrawString(score.c_str(), -1, &font, rectF, &stringFormat, &yellow);

	// Draw Go Button (after displaying "Level X Begin")
	(mGoButton)->Draw(graphics);
}

/** Test an x,y click location to see if it clicked on some item in the control panel.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none. */
CTower* CControlPanel::HitTest(int x, int y)
{
	// If Go button is clicked, game becomes active
	if (mGoButton->HitTest(x,y))
	{
		mGame->SetActive(true);
	}

	//Cannot create towers before go button exists
	if (!mGoButton->GetActive())
	{
		return nullptr;
	}

	for (auto i = mControlTowers.rbegin(); i != mControlTowers.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			shared_ptr<CTower> tower;
			if (y < 132)
			{
				tower = make_shared<CTowerWave>(mGame, x, y);
			}
			else if (y < 232)
			{
				tower = make_shared<CTower8Shot>(mGame, x, y);
			}
			else if (y < 332)
			{
				mBombCount++;
				tower = make_shared<CTowerBomb>(mGame, x, y, mBombCount);
			}
			else if (y < 432)
			{
				tower = make_shared<CTowerSniper>(mGame, x, y);
			}
			mGame->AddItem(tower);
			return tower.get();
		}
	}
	return nullptr;
}


/**
 * Updates Go button and all items
 * \param elapsed elapsed time since last call
 */
void CControlPanel::Update(double elapsed) 
{ 
	//Button set false, update to set true only runs while game is not active
	mGoButton->SetActive(false);
	if (mGame->GetActive() == false)
	{
		mGoButton->Update(elapsed);
	}
}