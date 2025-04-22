/**
 * \file TowerCounter.h
 *
 * \author Connor Mears
 *
 * Derived Item Visitor to Get Tower Items
 */


#pragma once
#include "ItemVisitor.h"
#include <vector>
#include "Tower.h"
#include "Tower8Shot.h"
#include "TowerBomb.h"
#include "TowerSniper.h"
#include "TowerWave.h"


/**
 * Derived Item Visitor to Get Tower Items
 */
class CTowerCounter : public CItemVisitor
{
public:

	/** Visit a CTower8Shot object
	\param tower Tower we are visiting */
	virtual void VisitTower8Shot(CTower8Shot* tower) override;

	/** Visit a CTowerBomb object
	\param tower Tower we are visiting */
	virtual void VisitTowerBomb(CTowerBomb* tower) override;

	/** Visit a CTowerSniper object
	\param tower Tower we are visiting */
	virtual void VisitTowerSniper(CTowerSniper* tower) override;

	/** Visit a CTowerWave object
	\param tower Tower we are visiting */
	virtual void VisitTowerWave(CTowerWave* tower) override;

	/** Getter for mTowers
	* \returns collection of all towers */
	std::vector<CTower*> GetTowers() { return mTowers; }

private:

	std::vector<CTower*> mTowers; ///< Collection of towers in Game
};

