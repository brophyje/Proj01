/**
 * \file Balloon.h
 *
 * \author Jacob Theobald
 *
 * Base class for balloons
 */


#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Item.h"


/**
 * Class that implements a balloon that moves along road tiles.
 */
class CBalloon : public CItem
{
public:

    /// How much we offset drawing the balloon to the left of the center
    const static int OffsetLeft = 32;

    /// How much we offset drawing the balloon above the center
    const static int OffsetDown = 32;


    CBalloon(CGame* game, const int x, const int y);

    /// Default constructor (disabled)
    CBalloon() = delete;

    /// Copy constructor (disabled)
    CBalloon(const CBalloon&) = delete;

    /// Destructor
    virtual ~CBalloon();


    /**  The scalar T used for road traversal
    * \returns T a double scalar */
    double GetT() const { return mT; }

    /** Reset T value when moving to next tile */
    void ResetT() { mT -= 1.0; }

    /** Getter for current Tile Balloon is on
    * \return Tile of balloon */
    CRoadTile* GetTileOn() { return mTileOn; }

    /** Setter for tile balloon is on
    * \param tile Next Road Tile */
    void SetTileOn(CRoadTile* tile);

    /** Determine direction balloon enters tile
    * \param T tile from front or back
    * \returns boolean of if balloon is moving forward */
    bool IsForward(double T);

    void Update(double elapsed);

    /** Accept function for visitors, overrides base item accept
    * \param visitor pointer to visitor that visits this balloon */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBalloon(this); }

private:

    /// The T scalar used for path calculation for the balloon
    double mT = 0.0;

    CRoadTile* mTileOn = nullptr; ///< Current Tile Balloon is On

    bool mIsForward = true;

    /// List of balloon colors
    std::vector<std::wstring> mColors {L"black", L"blue", L"red"};
};