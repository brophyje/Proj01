/**
 * \file ProjectileDart.cpp
 *
 * \author Nicholas Aaltonen
 */

#include "pch.h"
#include "ProjectileDart.h"
#include "Game.h"


/**
 * Derived Constructor
 * Sets the image of the dart
 * \param game Game to add to
 * \param x X position
 * \param y Y position
 * \param angle Angle in radians used to draw
 * \param speedX Speed in x direction
 * \param speedY Speed in y direction
 */
CProjectileDart::CProjectileDart(CGame* game, const double x, const double y, double angle, double speedX, double speedY) 
    : CProjectile(game, Points, x, y, angle, speedX, speedY)
{
    mXStart = x;
    mYStart = y;
    this->SetImage(L"dart.png");
}

/**
*  Destructor
*/
CProjectileDart::~CProjectileDart()
{
}

/** Handle updates in time of our projectile
 *
 * This is called before we draw and allows us to move our projectile.
 * We add our speed times the amount of time that has elapsed.
 *
 * \param elapsed Time elapsed since the class call
 */
void CProjectileDart::Update(double elapsed)
{
    //Call base class to change position
    CProjectile::Update(elapsed);

    //If the dart travels 100 pixels away from tower, delete the object
    if (sqrt(pow((GetX() - mXStart),2) + pow((GetY() - mYStart),2)) >= 90)
    {
        GetGame()->DeleteItem(this);
    }
}