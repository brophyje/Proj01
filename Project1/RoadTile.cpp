/**
 * \file RoadTile.cpp
 *
 * \author Jered Brophy
 */

#pragma once
#include "pch.h"
#include "RoadTile.h"
#include <string>
#include <memory>
#include "Item.h"

using namespace std;
using namespace Gdiplus;


/** Constructor
* \param grid The grid this is a member of
*/
CRoadTile::CRoadTile(CGrid* grid) : CTile(grid)
{
	this->SetValidSpot(false);
}


/**
*  Destructor
*/
CRoadTile::~CRoadTile()
{
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CRoadTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CTile::XmlLoad(node);
	mType = this->GetFile().substr(4, 2);
}


/** Delete Balloon from Tile List
 * \param balloon Balloon to be deleted */
void CRoadTile::DeleteBalloon(CBalloon* balloon)
{
    auto loc = find(::begin(mBalloons), ::end(mBalloons), balloon);
    if (loc != ::end(mBalloons))
    {
        mBalloons.erase(loc);
    }
}

/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNW(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();

    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY()-32 + t * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally left
        x = GetX()-32 + (1 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the South/West tile, where
 * forward motion is assumed to be from a South entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonSW(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();

    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically up
        y = GetY()-32 + (1 - t) * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally left
        x = GetX()-32 + (1 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the East/West tile, where
 * forward motion is assumed to be from a East entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonEW(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();


    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 1.0)
    {
        // First half of path
        // Moving horizontally right
        x = GetX()-32 + t * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the North/South tile, where
 * forward motion is assumed to be from a Noth entrance
 * to a South exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNS(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();

    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 1.0)
    {
        // First half of path
        // Moving vertically down
        y = GetY()-32 + t * GetHeight();
    }

    balloon->SetLocation(x, y);
}


/**
 * Place the balloon on the North/East tile, where
 * forward motion is assumed to be from a North entrance
 * to a East exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNE(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();

    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY()-32 + t * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally right
        x = GetX()-32 + t * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the South/East tile, where
 * forward motion is assumed to be from a South entrance
 * to a East exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonSE(CBalloon* balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY();
    auto x = GetX();

    if (!balloon->IsForward(t))
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically up
        y = GetY()-32 + (1 - t) * GetHeight();
    }
    else 
    {
        // Second half of path
        // Moving horizontally right
        x = GetX()-32 + (t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/** Handle updates for animation
* \param elapsed The time since the last update */
void CRoadTile::Update(double elapsed)
{
    vector<CBalloon*> balloonsToDelete;
    for (auto balloon : mBalloons)
    {
        balloon->Update(elapsed);
        if (balloon->GetT() >= 1.0)
        {
            if (mNext != nullptr)
            {
                balloon->ResetT();
                mNext->AddBalloon(balloon);
                balloonsToDelete.push_back(balloon);
            }
            else
            {
                // delete balloon from game, update score by -1
                //GetGame()->GetScoreBoard()->DecrementScore();
                DeleteBalloon(balloon);
            }
        }
        else
        {
            if (mType == L"EW")
            {
                PlaceBalloonEW(balloon);
            }
            else if (mType == L"NS")
            {
                PlaceBalloonNS(balloon);
            }
            else if (mType == L"NE")
            {
                PlaceBalloonNE(balloon);
            }
            else if (mType == L"NW")
            {
                PlaceBalloonNW(balloon);
            }
            else if (mType == L"SE")
            {
                PlaceBalloonSE(balloon);
            }
            else if (mType == L"SW")
            {
                PlaceBalloonSW(balloon);
            }
        }
    }
    for (auto balloon : balloonsToDelete)
    {
        DeleteBalloon(balloon);
    }
}


