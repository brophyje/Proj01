/**
 * \file Tower8Shot.cpp
 *
 * \author Connor Mears
 */

#include "pch.h"
#include "Tower8Shot.h"
#include "Game.h"

using namespace std;

/**
 *  Destructor
 */
CTower8Shot::~CTower8Shot()
{
}

/** Constructor
 * \param game pointer to game this tower is in
 * \param x X location
 * \param y Y location */
CTower8Shot::CTower8Shot(CGame* game, int x, int y) : CTower(game, x, y)
{
	SetImage(L"tower8.png");
}


/**
 * Shoot the Darts out of the Tower
 */
void CTower8Shot::Shoot()
{
    // create 8 darts
    double DEGREE = 0.78539816;
    for (int i=1; i<=8; i++)
    {
        double angle = DEGREE * i;
        double speedX;
        double speedY;
        int offsetX;
        int offsetY;

        if (i == 1)
        {
            speedX = 141.42;
            speedY = 141.42;
            offsetX = sqrt(50);
            offsetY = sqrt(50);
        }
        else if (i == 2)
        {
            speedX = 0;
            speedY = 200;
            offsetX = 0;
            offsetY = 10;
        }
        else if (i == 3)
        {
            speedX = -141.42;
            speedY = 141.42;
            offsetX = -sqrt(50);
            offsetY = sqrt(50);
        }
        else if (i == 4)
        {
            speedX = -200;
            speedY = 0;
            offsetX = -10;
            offsetY = 0;
        }
        else if (i == 5)
        {
            speedX = -141.42;
            speedY = -141.42;
            offsetX = -sqrt(50);
            offsetY = -sqrt(50);
        }
        else if (i == 6)
        {
            speedX = 0;
            speedY = -200;
            offsetX = 0;
            offsetY = -10;
        }
        else if (i == 7)
        {
            speedX = 141.42;
            speedY = -141.42;
            offsetX = sqrt(50);
            offsetY = -sqrt(50);
        }
        else if (i == 8)
        {
            speedX = 200;
            speedY = 0;
            offsetX = 10;
            offsetY = 0;
        }
        
        auto dart = make_shared<CProjectileDart>(GetGame(), GetX() + offsetX, GetY() + offsetY, angle, speedX, speedY);
        GetGame()->AddItem(dart);
    }
}


/**
 * Handle updates for shooting darts
 * \param elapsed The time since the last update
 */
void CTower8Shot::Update(double elapsed)
{
    mTimeTillFire -= elapsed;
    if (mTimeTillFire <= 0)
    {
        mTimeTillFire += TimeBetweenShots;
        Shoot();
    }
}

