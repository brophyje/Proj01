/**
 * \file Item.h
 *
 * \author Jacob Theobald
 *
 * Base class for a game object, other than tiles
 */


#pragma once
#include <memory>
#include <string>
#include "ItemVisitor.h"
class CGame;


/**
 * Base class for balloons and towers.
 * Used to in order to put all game objects into a collection.
 */
class CItem
{
public:
	/// How much we offset drawing the item to the left of the center
	const static int OffsetLeft = 32;

	/// How much we offset drawing the item above the center
	const static int OffsetDown = 32;

	/** Handle updates for animation
	* \param elapsed The time since the last update */
    virtual void Update(double elapsed) {}

	void SetImage(const std::wstring& file);

	/**  The X location of the item
	* \returns X location in pixels */
	int GetX() const { return mX; }

	/**  The Y location of the item
	* \returns Y location in pixels */
	int GetY() const { return mY; }

	/**  Gets Game pointer
	* \returns mGame pointer to game */
	CGame* GetGame() { return mGame; }

	/**  Set the item location
	* \param x X location
	* \param y Y location */
	void SetLocation(int x, int y) { mX = x; mY = y; }

	virtual void Draw(Gdiplus::Graphics* graphics);

	virtual bool HitTest(int x, int y);

	/**  Get the file name for this image
	* \returns Filename or blank if none */
	std::wstring GetFile() { return mFile; }

	/**  Get the bitmap image of the item
	* \returns Bitmap image */
	std::shared_ptr<Gdiplus::Bitmap> GetImage() { return mItemImage; }

	/** Base Accept function for item visitors
	* \param visitor pointer to visitor being accepted */
	virtual void Accept(CItemVisitor* visitor) {};

protected:
    CItem(CGame* game, int x, int y);

private:
    /// Pointer to game this item is contained in
    CGame* mGame;

	int mX; ///< The x location of the item
	int mY; ///< The y location of the item

	/// The image of this item
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;

	/// The file for this item
	std::wstring mFile;
};

