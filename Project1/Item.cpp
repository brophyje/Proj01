/**
 * \file Item.cpp
 *
 * \author Jacob Theobald
 */


#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;



/**
 * Constructor
 * \param game pointer to game item is a part of
 * \param x X position of item
 * \param y Y position of item
 */
CItem::CItem(CGame* game, int x, int y) : mGame(game), mX(x), mY(y)
{
}

/** The way you set the image
* \param file The file being opened
*/
void CItem::SetImage(const std::wstring& file)
{
    mItemImage = mGame->GetDeclaration(file);
    if (mItemImage == 0)
    {
        mItemImage = mGame->SetImage(file, file);
    }
    mFile = file;
}

/** The drawing function
* \param graphics The graphics that is being used
*/
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    if (mItemImage != nullptr)
    {
        int wid = mItemImage->GetWidth();
        int hit = mItemImage->GetHeight();

        graphics->DrawImage(mItemImage.get(),
            mX - OffsetLeft, mY + OffsetDown - hit,
            wid, hit);
    }
}

/**  Test this item to see if it has been clicked on
    * \param x X location on the game to test
    * \param y Y location on the game to test
    * \return true if clicked on */
bool CItem::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - mX + wid / 2;
    double testY = y - mY + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mItemImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mItemImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

