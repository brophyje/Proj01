/**
 * \file GoButton.h
 *
 * \author Jacob Theobald
 *
 * Class used to make a button appear to start the level.
 */

#pragma once
#include "Item.h"


/// Length of level transition, used for determining activity of button
const double LevelTransitionLength = 2.0;

/**
 * Class derived from CItem that implements the Go Button
 */
class CGoButton : public CItem
{
public:
	CGoButton() = delete;
	CGoButton(const CGoButton&) = delete;
	virtual ~CGoButton();

	CGoButton(CGame* game, int x, int y);

	///  Handle updates for animation
	/// \param elapsed The time since the last update
	void Update(double elapsed);

	/** Whether or not GoButton is Active or not
	 \returns Boolean if GoButton is Active */
	bool GetActive() { return mActive; }

	/** Set GoButton to Active/Not-Active
	 \param b Boolean to set mActive to */
	void SetActive(bool b) { mActive = b; }

	virtual bool HitTest(int x, int y) override;

	void Draw(Gdiplus::Graphics* graphics);

	/** Accept function to prevent Go Button from being abstract
	* \param visitor pointer to visitor
	*/
	virtual void Accept(CItemVisitor* visitor) override {}

private:
	/// Total time level has been running
	double mTotalElapsed = 0.0;

	/// Whether the button is active or not
	bool mActive = false;
};

