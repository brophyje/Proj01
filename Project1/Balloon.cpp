/**
 * \file Balloon.cpp
 *
 * \author Jacob Theobald
 */



#include "pch.h"
#include "Balloon.h"
#include "RoadTile.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game pointer to the game this balloon is a part of
* \param x  X position
* \param y Y position */
CBalloon::CBalloon(CGame* game, const int x, const int y) : CItem(game, x, y)
{
    int color = rand() % mColors.size();
    wstring filename = mColors.at(color) + L"-balloon.png";
    SetImage(filename);
}

/**
*  Destructor
*/
CBalloon::~CBalloon()
{
}

void CBalloon::SetTileOn(CRoadTile* tile)
{
    if (mTileOn == nullptr)
    {
        mIsForward = true;
        mTileOn = tile;
        return;
    }
    // The balloon has entered a tile from the east
    if (tile->GetX() < mTileOn->GetX())
    {
        mIsForward = true; //false;
    }
    // Entering the new tile from the west
    else if (tile->GetX() > mTileOn->GetX())
    {
        mIsForward = false; // true;
    }
    // Entering the new tile from the north
    else if (tile->GetY() > mTileOn->GetY())
    {
        mIsForward = false; // true;
    }
    // Entering the new tile from the south
    else if (tile->GetY() > mTileOn->GetY())
    {
        mIsForward = true; // true;
    }
}


bool CBalloon::IsForward(double T) {
    return mIsForward;
}

/** Handle updates for balloon movement
* \param elapsed The time since the last update */
void CBalloon::Update(double elapsed)
{
    mT += 2.0 * elapsed;
}
