/**
 * \file Scoreboard.h
 *
 * \author Jacob Theobald
 *
 * Class used to implement the score on the right side of the window.
 */


#pragma once
class CControlPanel;


/**
 * Class used to keep score of game.
 * Tied to a game and draws and updates itself as score changes.
 */
class CScoreboard
{
public:

	CScoreboard();
	CScoreboard(const CScoreboard&) = delete;
	virtual ~CScoreboard();

	/**  Adds some amount to total score to scoreboard
	* \param addedScore score added to total */
	void UpdateScore(int addedScore) { mTotalScore += addedScore; };

	/** Getter for score member variable
	* \return total score of the scoreboard */
	int GetScore() { return mTotalScore; };

private:

	/// Score for the game
	int mTotalScore = 0;
};

