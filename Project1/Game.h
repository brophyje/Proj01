/**
 * \file Game.h
 *
 * \author Zachary Morris
 *
 * The class that holds the entire game data
 */

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "Tile.h"
#include "Balloon.h"
#include "XmlNode.h"
#include "Tower.h"
#include "Grid.h"
#include "ControlPanel.h"
#include "ItemVisitor.h"



/**
 * The class that holds the entire game data
 */
class CGame
{
public:

	/// Game area in virtual pixels
	const static int Width = 1224;

	/// Game area height in virtual pixels
	const static int Height = 1024;

	
	CGame();
	CGame(const CGame&) = delete;
	virtual ~CGame();

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	std::shared_ptr<Gdiplus::Bitmap> SetImage(const std::wstring& id, const std::wstring& file);
	std::shared_ptr<Gdiplus::Bitmap> GetDeclaration(const std::wstring file);

	void OnLButtonDown(int x, int y);
	void OnMouseMove(UINT nFlags, CPoint point);

	void AddItem(std::shared_ptr<CItem> item);
	void DeleteItem(CItem* item);

	void MoveToFront(CItem* item);

	CTower* HitTest(int x, int y);
	std::shared_ptr<CTile> TileTest(int x, int y);

	void CollisionCheck();
	void BalloonChecker(int x, int y, double maxDistance, int score);
	CBalloon* GetClosestBalloon(int x, int y);

	void Load(const std::wstring& filename);
	void Clear();


	//REMOVE GETTERS AND SETTERS AFTER NEW SOLUTION

	/** Getter for Game's active status
	* \returns Active status boolean of Game */
	bool GetActive() { return mActive; }

	/** Setter for Game's active status
	* \param active Active status boolean of Game */
	void SetActive(bool active) { mActive = active; }

	void Update(double elapsed);

	void Accept(CItemVisitor* visitor);

	void Transition(Gdiplus::Graphics* graphics,int width, int height);

private:
	/// The grid (holds all the tiles)
	std::shared_ptr<CGrid> mGrid;

	/// The control panel
	std::shared_ptr<CControlPanel> mControlPanel;

	/// The items (balloons and towers) in the game
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Boolean for whether game is currently playing
	bool mActive = true;

	/// Image Bitmap lookup (cannot load file more than once)
	std::map<std::wstring, std::shared_ptr<Gdiplus::Bitmap> > mDeclarations;

	/// currently grabbed tower from control panel
	CTower* mGrabbedItem = nullptr;

	float mScale;   ///< Virtual Pixel Scale
	float mXOffset; ///< Virtual Pixel X Offset
	float mYOffset; ///< Virtual Pixel Y Offset

	/// The level we are on
	int mLevel = 1;

	int mBalloonCount; ///< Number of balloons left to spawn

	/// How long the level timer is on the board
	double mLevelTimer = 0;
};

