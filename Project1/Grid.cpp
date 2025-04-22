/**
 * \file Grid.cpp
 *
 * \author Nicholas Aaltonen
 */

#include "pch.h"
#include <algorithm>
#include <string>
#include <map>
#include <algorithm>

#include "XmlNode.h"
#include "Grid.h"
#include "Tile.h"
#include "GrassTile.h"
#include "RoadTile.h"
#include "SceneryTile.h"
#include "Game.h"
#include "RoadCounter.h"

using namespace std;
using namespace xmlnode;
using namespace Gdiplus;


/// Destructor
CGrid::~CGrid()
{
}

/**
* Constructor
* \param game Game the control panel is contained in
*/
CGrid::CGrid(CGame* game)
{
    mGame = game;
}


/**  Draw the grid
* \param graphics The GDI+ graphics context to draw on
*/
void CGrid::OnDraw(Gdiplus::Graphics* graphics)
{

    for (auto item : mTiles)
    {
        item->Draw(graphics);
    }
}

/** Handle updates for animation
* \param elapsed The time since the last update */
void CGrid::Update(double elapsed)
{
    for (auto tile : mTiles)
    {
        tile->Update(elapsed);
    }
}


/**  Add a tile to the grid
* \param tile New tile to add
*/
void CGrid::Add(std::shared_ptr<CTile> tile)
{
    mTiles.push_back(tile);
}


/**  Load the grid from a .xml XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the grid from.
*/
void CGrid::Load(const std::wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        mStartX = stoi(root->GetAttributeValue(L"start-x", L""));
        mStartY = (stoi(root->GetAttributeValue(L"start-y", L"")) * 64) + GridSpacing;


        auto declarations = root->GetChild(0); // declaration section of XML
        auto items = root->GetChild(1); // items section of XML

        for (auto node : declarations->GetChildren()) // create declarations
        {
            if (node->GetType() == NODE_ELEMENT)
            {
                wstring id = node->GetAttributeValue(L"id", L"");

                // check if image has already been loaded (for when level changes)
                if (mGame->GetDeclaration(id) == 0)
                {
                    wstring file = node->GetAttributeValue(L"image", L"");
                    mFiles.insert(pair<wstring, wstring>(id, file));
                    std::shared_ptr<Gdiplus::Bitmap> bitmap = mGame->SetImage(id, file);

                }

            }
        }

        for (auto node : items->GetChildren()) // create items
        {
            if (node->GetType() == NODE_ELEMENT)
            {
                XmlTile(node);
            }
        }

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

    BuildRoadList();

}


/**
*  Clear the grid data.
*
* Deletes all known items in the grid.
*/
void CGrid::Clear()
{
    mTiles.clear();
    mAdjacency.clear();
}

/** Accept Visitor into Grid
 * \param visitor Derived visitor class */
void CGrid::Accept(CItemVisitor* visitor)
{
    for (auto tile : mTiles)
    {
        tile->Accept(visitor);
    }
}


/**
 * Finds the Tile the X, Y coordinates point to
 * \param x X coordinate
 * \param y Y coordinate
 * \returns The tile found
 */
CTile* CGrid::TileFinder(int x, int y)
{
    CTile* foundTile = nullptr;
    for (auto tile : mTiles)
    {
        bool checkX = x >= tile->GetX() - GridSpacing && x <= tile->GetX() + GridSpacing;
        bool checkY = y >= tile->GetY() - GridSpacing && y <= tile->GetY() + GridSpacing;
        if (checkX && checkY) // found tile
        {
            foundTile = tile.get();
            break;
        }
    }
    return foundTile;
}

/// Builds Road List for Balloons to Traverse
void CGrid::BuildRoadList()
{
    // Get Start Tile as RoadTile
    CRoadCounter startVisitor;
    CTile* tile = TileFinder(mStartX, mStartY);
    tile->Accept(&startVisitor);
    mStartTile = startVisitor.GetRoad();

    // Get Road Tile Count
    CRoadCounter roadVisitor;
    Accept(&roadVisitor);

    vector<CRoadTile*> visited; // List of Visited Roads
    CRoadTile* currentRoad = mStartTile; // Current Road we're on
    for (int i = 0; i<roadVisitor.GetRoadCount(); i++)
    {
        visited.push_back(currentRoad);

        // Used to Grab RoadTiles surrounding currentRoad
        CRoadCounter adjacencyVisitor;

        int X = currentRoad->GetX();
        int Y = currentRoad->GetY();
        wstring type = currentRoad->GetType();

        // Go Through Types (an EW Type can only connect to East and West)
        if (type == L"EW")
        {
            CTile* east = TileFinder(X + 64, Y);
            if (east != nullptr) { east->Accept(&adjacencyVisitor); }
            CTile* west = TileFinder(X - 64, Y);
            if (west != nullptr) { west->Accept(&adjacencyVisitor); }
        }
        else if (type == L"NS")
        {
            CTile* north = TileFinder(X, Y - 64);
            if (north != nullptr) { north->Accept(&adjacencyVisitor); }
            CTile* south = TileFinder(X, Y + 64);
            if (south != nullptr) { south->Accept(&adjacencyVisitor); }
        }
        else if (type == L"NE")
        {
            CTile* north = TileFinder(X, Y - 64);
            if (north != nullptr) { north->Accept(&adjacencyVisitor); }
            CTile* east = TileFinder(X + 64, Y);
            if (east != nullptr) { east->Accept(&adjacencyVisitor); }
        }
        else if (type == L"NW")
        {
            CTile* north = TileFinder(X, Y - 64);
            if (north != nullptr) { north->Accept(&adjacencyVisitor); }
            CTile* west = TileFinder(X - 64, Y);
            if (west != nullptr) { west->Accept(&adjacencyVisitor); }
        }
        else if (type == L"SE")
        {
            CTile* south = TileFinder(X, Y + 64);
            if (south != nullptr) { south->Accept(&adjacencyVisitor); }
            CTile* east = TileFinder(X + 64, Y);
            if (east != nullptr) { east->Accept(&adjacencyVisitor); }
        }
        else if (type == L"SW")
        {
            CTile* south = TileFinder(X, Y + 64);
            if (south != nullptr) { south->Accept(&adjacencyVisitor); }
            CTile* west = TileFinder(X - 64, Y);
            if (west != nullptr) { west->Accept(&adjacencyVisitor); }
        }

        // Go through adjacent, grab non-visited one
        for (auto tile : adjacencyVisitor.GetAdjacent())
        {
            if (count(visited.begin(), visited.end(), tile) == 0)
            {
                currentRoad->SetNext(tile);
                currentRoad = tile;
                break;
            }
        }
    }
}


/**
 *  Used by CTile object for XmlLoad to lookup image bitmap.
 * \param id Declaration id
 * \returns image bitmap
 */
std::shared_ptr<Gdiplus::Bitmap> CGrid::GetDeclaration(std::wstring id)
{
    return mGame->GetDeclaration(id);
}

/**
 *  Used by CTile object for XmlLoad to lookup image filename.
 * \param id Declaration id
 * \returns image filename
 */
std::wstring CGrid::GetFile(std::wstring id)
{
    return mFiles.at(id);
}


/**
*  Handle a tile node.
* \param node Pointer to XML node we are handling
*/
void CGrid::XmlTile(const std::shared_ptr<CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CTile> tile;

    // We have an item. What type?
    wstring type = node->GetName();
    if (type == L"road")
    {
        tile = make_shared<CRoadTile>(this);
    }
    else if (type == L"open")
    {
        tile = make_shared<CGrassTile>(this);
    }
    else if (type == L"house" || type == L"trees")
    {
        tile = make_shared<CSceneryTile>(this);
    }

    if (tile != nullptr)
    {
        tile->XmlLoad(node);
        Add(tile);
    }
}


/** Checking if the coordinates are on a valid tile
* \param x The X coordinate
* \param y The Y coordinate
* \returns Pointer to tile or nullptr if tile valid. */
std::shared_ptr<CTile> CGrid::TileTest(int x, int y)
{
    shared_ptr<CTile> valid;
    for (auto tile : mTiles)
    {
        bool checkX = x >= tile->GetX() - GridSpacing && x <= tile->GetX() + GridSpacing;
        bool checkY = y >= tile->GetY() - GridSpacing && y <= tile->GetY() + GridSpacing;
        if (checkX && checkY) // found tile
        {
            valid = tile;
        }
    }
    return valid != nullptr && valid->GetValidSpot() ? valid : nullptr;
}
