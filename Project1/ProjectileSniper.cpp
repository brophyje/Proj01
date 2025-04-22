/**
 * \file ProjectileSniper.cpp
 *
 * \author Jacob Theobald
 */


#include "pch.h"
#include "ProjectileSniper.h"
#include "Game.h"


/**
 * Derived Constructor
 * Sets the image of the bullet
 * \param game Game to add to
 * \param x x position
 * \param y y position
 * \param angle angle in radians used to draw
 * \param speedX speed in x direction
 * \param speedY speed in y direction
 */
CProjectileSniper::CProjectileSniper(CGame* game, const double x, const double y, double angle, 
    double speedX, double speedY) : CProjectile(game, Points, x, y, angle, speedX, speedY)
{
    this->SetImage(L"bullet.png");
}

 /**
 *  Destructor
 */
CProjectileSniper::~CProjectileSniper()
{
}

 /** Handle updates in time of our projectile
  *
  * This is called before we draw and allows us to move our projectile.
  * We add our speed times the amount of time that has elapsed.
  *
  * \param elapsed Time elapsed since the class call
  */
void CProjectileSniper::Update(double elapsed)
{
    //Call base class to change position
    CProjectile::Update(elapsed);

    //If sniper bullet hits any edge of game window, delete the object
    if (this->GetX() <= 0 || this->GetX() >= 1024 || this->GetY() <= 0 || this->GetY() >= 1024)
    {
        GetGame()->DeleteItem(this);
    }
}