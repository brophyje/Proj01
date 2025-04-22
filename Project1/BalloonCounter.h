/**
 * \file BalloonCounter.h
 *
 * \author Zach Morris
 *
 * Derived visitor to count number of balloons
 */

#pragma once
#include "ItemVisitor.h"
#include <vector>


/**
 * Derived visitor to count number of balloons
 */
class CBalloonCounter : public CItemVisitor
{
public:

	virtual void VisitBalloon(CBalloon* balloon) override;

	/** Gets the number of balloons
	* \returns Number of balloons */
	int GetNumBalloons() const { return mNumBalloons; }

	/** Gets the last balloon found
	* \returns Last checked balloon */
	CBalloon* GetBalloon() { return mBalloon; }

	/** Gets list of all balloons in game
	* \returns Collection of balloons */
	std::vector<CBalloon*> GetBalloons() { return mBalloons; }


private:
	/// Balloons counter
	int mNumBalloons = 0;

	/// Balloon checked
	CBalloon* mBalloon = nullptr;

	/// List of balloons in game
	std::vector<CBalloon*> mBalloons;
	
};
