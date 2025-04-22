/**
 * \file Projectile.cpp
 *
 * \author Connor Mears
 */

#include "pch.h"
#include "Projectile.h"

using namespace std;
using namespace Gdiplus;


/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;


/** Constructor
* \param game Game to add to
* \param points Point value associated to projectile
* \param x X position
* \param y Y position 
* \param angle Angle in radians to draw
* \param speedX Speed in x direction
* \param speedY Speed in y direction
*/
CProjectile::CProjectile(CGame* game, int points, const double x, const double y, 
    double angle, double speedX, double speedY) : CItem(game, x, y)
{
    mAngle = angle;
    mSpeedX = speedX;
    mSpeedY = speedY;
    mPoints = points;
}

/**
*  Destructor
*/
CProjectile::~CProjectile()
{
}

/** Draw the rotated projectile. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on. */
void CProjectile::Draw(Gdiplus::Graphics* graphics)
{
    int wid = GetImage()->GetWidth();
    int hit = GetImage()->GetHeight();
    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)(GetX()),
                                 (REAL)(GetY()));
    graphics->RotateTransform((REAL)(mAngle * RtoD));
    graphics->DrawImage(GetImage().get(), 0, 0, wid, hit);
    graphics->Restore(save);
}

/** Handle updates in time of our projectile
 *
 * This is called before we draw and allows us to move our projectile.
 * We add our speed times the amount of time that has elapsed.
 *
 * \param elapsed Time elapsed since the class call
 */
void CProjectile::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
        GetY() + mSpeedY * elapsed);

    // overridden for the derived classes.
    // Sniper goes to edge of screen
    // Dart goes for 100 pixels
}
