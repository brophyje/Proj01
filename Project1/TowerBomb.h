/**
 * \file TowerBomb.h
 *
 * \author Zachary Morris
 *
 * Derived Tower class for Bomb Tower
 */

#pragma once
#include "Tower.h"
#include "Explosive.h"

/**
 * Derived Tower class for Bomb Tower
 */
class CTowerBomb : public CTower
{
public:

	/// Points for popping a balloon w/ this tower
	const static int Points = 7;

	/// Time in seconds between shots for this tower
	const static int Radius = 100;

	/// Disabling default constructor
	CTowerBomb() = delete;

	/// Disabling copy constructor
	CTowerBomb(const CTowerBomb&) = delete;
	virtual ~CTowerBomb();

	CTowerBomb(CGame* game, int x, int y, int c);

	/** Makes the bomb tower explode, overrides CItem's function
	* \param graphics pointer to graphics being drawn on */
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	virtual void Update(double elapsed) override;

	/** Accept function for item visitors, overrides CItem's accept
	* \param visitor pointer to visitor being accepted */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerBomb(this); }

private:
	const static int mTimerConst = 3; ///< Initial constant timer for bomb #1

	double mTimer; ///< current timer for bomb object

	bool mFiring = false; ///< Determines whether tower is in firing state
};

