/**
 * \file Tile.cpp
 *
 * \author Jacob Theobald
 */



#include "pch.h"
#include "Tile.h"
#include "Grid.h"
#include "Tower.h"


using namespace std;
using namespace Gdiplus;




/**  Constructor
 * \param grid The grid this item is a member of
 */
CTile::CTile(CGrid* grid) : mGrid(grid)
{
}

/**
* Destructor
*/
CTile::~CTile()
{
}

void CTile::Draw(Gdiplus::Graphics* graphics)
{
    if (mTileImage != nullptr)
    {
        int wid = mTileImage->GetWidth();
        int hit = mTileImage->GetHeight();

        graphics->DrawImage(mTileImage.get(),
            mX - OffsetLeft, mY - OffsetDown,
            wid+1, hit+1);
    }
}


/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mX = node->GetAttributeIntValue(L"x", 0);
    mY = node->GetAttributeIntValue(L"y", 0);
    wstring id = node->GetAttributeValue(L"id", L"");
    mTileImage = mGrid->GetDeclaration(id);
    mFile = mGrid->GetFile(id);
    
    // Set X and Y to center of tile
    mX = mX * mTileImage->GetWidth() + OffsetLeft;
    mY = mY * mTileImage->GetHeight() + OffsetDown;
}
