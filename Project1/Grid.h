/**
 * \file Grid.h
 *
 * \author Nicholas Aaltonen
 *
 *  Class that implements grid with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <string>

#include "XmlNode.h"
#include "Tile.h"
#include "RoadTile.h"

class CGame;

 /**
  *  Implements a grid with tiles we can manipulate
  */
class CGrid
{
public:
    CGrid() = delete;
    CGrid(const CGrid&) = delete;
    virtual ~CGrid();

    CGrid(CGame* game);

    /// The spacing between grid locations
    static const int GridSpacing = 32;


    void Add(std::shared_ptr<CTile> item);

    void OnDraw(Gdiplus::Graphics* graphics);
    virtual void Update(double elapsed);

    void Load(const std::wstring& filename);
    void Clear();

    virtual void Accept(CItemVisitor* visitor);
    CTile* TileFinder(int x, int y);
    void BuildRoadList();

    std::shared_ptr<Gdiplus::Bitmap> GetDeclaration(std::wstring id);
    std::wstring GetFile(std::wstring id);


    /**  The X location of the starting tile
    * \returns X location of start tile */
    int GetStartX() { return mStartX; };

    /**  The Y location of the starting tile
    * \returns Y location of start tile */
    int GetStartY() { return mStartY; };

    /** The Starting Tile of the Game
    * \returns Start tile pointer */
    CRoadTile* GetStartTile() { return mStartTile; };

    std::shared_ptr<CTile> TileTest(int x, int y);

    /**  Gets Game pointer
    * \returns mGame pointer to game */
    CGame* GetGame() { return mGame; }

    /** Iterator that iterates over the tiles in the grid */
    class Iter
    {
    public:
        /** Constructor
         * \param grid The grid we are iterating over
         * \param pos the position in the grid we are at*/
        Iter(CGrid* grid, int pos) : mGrid(grid), mPos(pos) {}

        /** Test for end of the iterator
        *  \param other checks if we are at the end of the thing we are iterating over
         * \returns True if we this position equals not equal to the other position */
        bool operator!=(const Iter& other) const
        {
            return mPos != other.mPos;
        }

        /** Get value at current position
         * \returns Value at mPos in the collection */
        std::shared_ptr<CTile> operator *() const { return mGrid->mTiles[mPos]; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const Iter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        CGrid* mGrid;   ///< Grid we are iterating over
        int mPos;       ///< Position in the collection
    };

    /** Get an iterator for the beginning of the collection
    * \returns Iter object at position 0 */
    Iter begin() { return Iter(this, 0); }

    /** Get an iterator for the end of the collection
     * \returns Iter object at position past the end */
    Iter end() { return Iter(this, mTiles.size()); }

private:
    /// The game this grid is contained in
    CGame* mGame;

    void XmlTile(const std::shared_ptr<xmlnode::CXmlNode>& node);

    // Start Tile Position
    int mStartX = 0; ///< Starting Tile X position
    int mStartY = 0; ///< Starting Tile Y position
    CRoadTile* mStartTile = nullptr; ///< Starting Tile

    /// All of the tiles that make up our grid
    std::vector<std::shared_ptr<CTile> > mTiles;

    /// Adjacency lookup support
    std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;

    /// File name lookup (from XML file)
    std::map<std::wstring, std::wstring> mFiles;
};
