/**
 * \file ControlPanel.h
 *
 * \author Connor Mears
 *
 * Class for the sidebar control panel of the game.
 * 
 * Draws the pallette of towers
 * Handles grabbing a tower to drag and drop
 * Stores the score
 * Draw the scores on the screen
 * Draws the Go! button when appropriate
 * Detects clicks on the Go! button
 */

#pragma once


#include <memory>
#include <vector>
#include "Tower.h"
#include "GoButton.h"
#include "Scoreboard.h"

class CGame;

/**
 * Class for the sidebar control panel of the game.
 */
class CControlPanel
{
public:

    CControlPanel() = delete;
    CControlPanel(const CControlPanel&) = delete;
    virtual ~CControlPanel();

    CControlPanel(CGame *game);

    void Reset();

    void OnDraw(Gdiplus::Graphics* graphics);

    CTower* HitTest(int x, int y);

    void Update(double elapsed);

    /** Gets the scoreboard object to modify / get score
    * \return scoreboard object */
    std::shared_ptr<CScoreboard> GetScoreboard() { return mScoreboard; }

    /** Gets the go button object
    * \return GoButton object */
    CGoButton* GetGoButton() { return mGoButton.get(); }

private:
    /// The game this control panel is contained in
    CGame* mGame;

    /// Scoreboard to display in the Control Panel
    std::shared_ptr<CScoreboard> mScoreboard;

    /// Go Button to start the level
    std::unique_ptr<CGoButton> mGoButton;

    /// Includes items located in Control Panel
    std::vector<std::shared_ptr<CTower> > mControlTowers;

    int mBombCount = 0; ///< Count of Bomb Towers Placed
};

