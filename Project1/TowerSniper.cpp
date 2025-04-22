/**
 * \file TowerSniper.cpp
 *
 * \author Jered Brophy
 */

#include "pch.h"
#include "TowerSniper.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;


/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;

/**
*  Destructor
*/
CTowerSniper::~CTowerSniper()
{
}

/** Constructor
 * \param game pointer to game tower is in
 * \param x X location
 * \param y Y location 
 */
CTowerSniper::CTowerSniper(CGame* game, int x, int y) : CTower(game, x, y)
{
    SetImage(L"towersniper.png");
}


/**
 * Shoot the Bullets out of the Tower
 */
void CTowerSniper::Shoot()
{
    CBalloon* balloon = GetGame()->GetClosestBalloon(GetX(), GetY());
    if (balloon == nullptr)
    {
        return;
    }

    double xDiff = balloon->GetX() - GetX();
    double yDiff = balloon->GetY() - GetY();

    double xSpeed;
    double ySpeed;

    if (xDiff >= 0 && yDiff >= 0)
    {
        mAngle = atan(yDiff / xDiff);
    }
    else if (xDiff >= 0 && yDiff <= 0)
    {
        mAngle = atan(yDiff / xDiff) + 270;
        mAngle = (mAngle + atan(yDiff / xDiff) - 270) / 2;
    }
    else if (xDiff <= 0 && yDiff <= 0)
    {
        mAngle = atan(yDiff / xDiff) + (2 * asin(1.0));
    }
    else if (xDiff <= 0 && yDiff >= 0)
    {
        mAngle = atan(yDiff / xDiff) + (2 * asin(1.0));
    }

    ySpeed = OverallSpeed * sin(mAngle);
    xSpeed = OverallSpeed * cos(mAngle);

    auto bullet = make_shared<CProjectileSniper>(GetGame(), GetX(), GetY(), mAngle, xSpeed, ySpeed);
    GetGame()->AddItem(bullet);
}


/**
 * Handle updates for shooting darts
 * \param elapsed The time since the last update
 */
void CTowerSniper::Update(double elapsed)
{
    mTimeTillFire -= elapsed;
    if (mTimeTillFire <= 0)
    {
        mTimeTillFire += TimeBetweenShots;
        Shoot();
    }
}

/** Draw the rotated tower. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on. */
void CTowerSniper::Draw(Gdiplus::Graphics* graphics)
{
    int wid = GetImage()->GetWidth();
    int hit = GetImage()->GetHeight();
    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)(GetX()),
                                 (REAL)(GetY()));
    graphics->RotateTransform((REAL)(mAngle * RtoD));
    graphics->DrawImage(GetImage().get(), -OffsetLeft, -OffsetDown, wid, hit);
    graphics->Restore(save);
}
