/**
 * \file Tile.h
 *
 * \author Jacob Theobald
 *
 * Base class for all derivative tiles used to build map.
 */


#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "ItemVisitor.h"

class CGrid;
class CTower;

/**
 * Base class for any tile in our grid
 */
class CTile
{
public:

    /// How much we offset drawing the tile to the left of the center
    const static int OffsetLeft = 32;

    /// How much we offset drawing the tile above the center
    const static int OffsetDown = 32;



    ///  Default constructor (disabled)
    CTile() = delete;

    ///  Copy constructor (disabled)
    CTile(const CTile&) = delete;

    virtual ~CTile();

    //void SetImage(const std::wstring& file);void SetImage(const std::wstring& file);

    /**  Get the file name for this tile image
     * \returns Filename or blank if none */
    std::wstring GetFile() { return mFile; }

    /**  Set the file name for this tile image
     * \param file Name of file */
    void SetFile(std::wstring file) { mFile = file; }


    /**  The X location of the center of the tile
    * \returns X location in pixels */
    int GetX() const { return mX; }

    /**  The Y location of the center of the tile
    * \returns Y location in pixels */
    int GetY() const { return mY; }

    /**  The Height of the tile image
    * \returns Tile height */
    int GetHeight() const { return mTileImage->GetHeight(); }

    /**  The Width of the tile image
    * \returns Tile width */
    int GetWidth() const { return  mTileImage->GetWidth(); }


    /**  Set the item location
    * \param x X location
    * \param y Y location */
    void SetLocation(int x, int y) { mX = x; mY = y; }

    /**  Set if the tile can hold a tower
    * \param validity Whether or not a tower can exist on the tile */
    void SetValidSpot(bool validity) { mValidTowerSpot = validity; }

    /**  Get if the tile can hold a tower
    * \returns validity Whether or not a tower can exist on the tile */
    bool GetValidSpot() { return mValidTowerSpot; }


    /**  Set the tower associated with the tile
    * \param tower pointer to tower associated with tile */
    void SetAssociatedTower(CTower* tower)
    { if (mValidTowerSpot == true) { mAssociatedTower = tower; mValidTowerSpot = false; } }


    /** Getter for associated tower
    * \return pointer to tower associated with tile */
    CTower* GetAssociatedTower() { return mAssociatedTower; }

    /**  Draw this item
    * \param graphics The graphics context to draw on */
    virtual void Draw(Gdiplus::Graphics* graphics);

    /** Handle updates for animation
    * \param elapsed The time since the last update */
    virtual void Update(double elapsed) {};

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) {};

protected:
    CTile(CGrid *grid);

private:
    /// The grid this item is contained in
    CGrid* mGrid;

    // Tile location on screen
    int   mX = 0;     ///< X location for the center of the tile
    int   mY = 0;     ///< Y location for the center of the tile

    /// The image of this tile
    std::shared_ptr<Gdiplus::Bitmap> mTileImage;

    /// The file for this tile
    std::wstring mFile;

    /// pointer to tower associated with tile
    CTower* mAssociatedTower = nullptr;

    /// bool that determines whether the tile can have a tower placed there
    bool mValidTowerSpot = true;
};