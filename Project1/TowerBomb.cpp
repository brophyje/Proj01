/**
 * \file TowerBomb.cpp
 *
 * \author Zachary Morris
 */

#include "pch.h"
#include "TowerBomb.h"
#include "Explosive.h"
#include "Game.h"

/**
* Destructor
*/
CTowerBomb::~CTowerBomb()
{
}

/** Constructor
* \param game pointer to game tower is in
* \param x X location
* \param y Y location
* \param c The count of bomb towers for timer
*/
CTowerBomb::CTowerBomb(CGame* game, int x, int y, int c) : CTower(game, x, y)
{
	mTimer = c * mTimerConst;
	SetImage(L"tower-bomb.png");
}

/**
 * The explosion
 */
void CTowerBomb::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);

    if (mFiring)
    {
		Gdiplus::SolidBrush brush(Gdiplus::Color(128, 0, 0));
		graphics->FillEllipse(&brush, GetX() - OffsetLeft * 3, GetY() - OffsetDown * 3, Radius * 2, Radius * 2);
    }
}

/** Handle updates in time of our bomb
 *
 * This is called to explode bomb with amount of time that has elasped.
 *
 * \param elapsed Time elapsed since the class call
 */
void CTowerBomb::Update(double elapsed)
{
	mTimer -= elapsed;
	if (!mFiring && mTimer <= 0)
	{
		mTimer = 0.25;
        mFiring = true;
		GetGame()->BalloonChecker(GetX(), GetY(), 100, Points);
	}
	if (mFiring && mTimer <= 0)
	{
		mFiring = false;
		GetGame()->DeleteItem(this);
	}
}
