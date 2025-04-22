/**
 * \file RoadCounter.cpp
 *
 * \author Connor Mears
 */

#include "pch.h"
#include "RoadCounter.h"

/** Visit a CRoadTile object
* \param tile Tile we are visiting
*/
void CRoadCounter::VisitRoadTile(CRoadTile* tile)
{
	mRoadCount++;
	mRoad = tile;
	mAdjacent.push_back(tile);
}
