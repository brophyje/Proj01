/**
 * \file GoButton.cpp
 *
 * \author Jacob Theobald
 */

#include "pch.h"
#include "GoButton.h"


/**
 *  Destructor
 */
CGoButton::~CGoButton()
{
}

/** Constructor
 * \param game pointer to game this button is in
 * \param x X location
 * \param y Y location */
CGoButton::CGoButton(CGame* game, int x, int y) : CItem(game, x, y)
{
    SetImage(L"button-go.png");
}


void CGoButton::Update(double elapsed)
{
    mTotalElapsed += elapsed;

    if (mTotalElapsed >= LevelTransitionLength) 
    {
        mActive = true;
    }
}

/** The drawing function
* \param graphics The graphics that is being used
*/
void CGoButton::Draw(Gdiplus::Graphics* graphics)
{
    if (mActive) 
    {
        CItem::Draw(graphics);
    }
}

/**  Test this item to see if it has been clicked on
    * \param x X location on the game to test
    * \param y Y location on the game to test
    * \return true if clicked on */
bool CGoButton::HitTest(int x, int y)
{
    //If button is visible allow hit test
    if (mActive)
    {
        return CItem::HitTest(x, y);
    }
    else
    {
        return false;
    }
}