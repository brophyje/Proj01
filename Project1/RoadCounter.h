/**
 * \file RoadCounter.h
 *
 * \author Connor Mears
 *
 * Derived visitor to count number of roads
 */

#pragma once
#include "ItemVisitor.h"
#include <vector>

/**
 * Derived visitor to count number of roads
 */
class CRoadCounter : public CItemVisitor
{
public:

	virtual void VisitRoadTile(CRoadTile* tile) override;

	/** Gets the number of roads
	* \returns Number of roads */
	int GetRoadCount() const { return mRoadCount; }

	/** Gets list of adjacent road tiles
	* \returns Collection of roads */
	std::vector<CRoadTile*> GetAdjacent() { return mAdjacent; }

	/** Gets the last road found
	* \returns Last checked road */
	CRoadTile* GetRoad() { return mRoad; }

private:

	int mRoadCount = 0; ///< Count of Road Tiles

	std::vector<CRoadTile*> mAdjacent; ///< Adjacent Road Tiles

	/// RoadTile checked
	CRoadTile* mRoad = nullptr;
};

