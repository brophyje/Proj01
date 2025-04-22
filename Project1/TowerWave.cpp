/**
 * \file TowerWave.cpp
 *
 * \author Nicholas Aaltonen
 */

#include "pch.h"
#include "TowerWave.h"
#include "Game.h"

using namespace Gdiplus;

/** Constructor
 * \param game pointer to game this tower is in
 * \param x X location
 * \param y Y location */
CTowerWave::CTowerWave(CGame* game, int x, int y) : CTower(game, x, y)
{
    mTimeTillFire = TimeBetweenShots;
    SetImage(L"tower-rings.png");
}

/**
 *  Destructor
 */
CTowerWave::~CTowerWave()
{
}

/**
 * Shoot a ring around the tower
 */
void CTowerWave::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);

    if (mFiring)
    {
        Pen redPen(Color::Red);
        graphics->DrawEllipse(&redPen, GetX() - (mDiameter / 2), GetY() - (mDiameter / 2), mDiameter, mDiameter);

        // If any balloons are close enough to tower destroy them
        CItem::GetGame()->BalloonChecker(GetX(), GetY(), mDiameter / 2, Points);
        if (mDiameter >= 200)
        {
            mFiring = false;
            mDiameter = 20;
        }
    }
}


/**
 * Handle updates for shooting a wave
 * \param elapsed The time since the last update
 */
void CTowerWave::Update(double elapsed)
{
    mTimeTillFire -= elapsed;
    if (mTimeTillFire <= 0)
    {
        mFiring = true;
        mTimeTillFire += TimeBetweenShots;
    }
    if (mFiring)
    {
        mDiameter += elapsed * mSpeed;
    }
}