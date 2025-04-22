/**
 * \file SceneryTile.cpp
 *
 * \author Nicholas Aaltonen
 */

#include "pch.h"
#include "SceneryTile.h"


/** Constructor
* \param grid The grid this is a member of
*/
CSceneryTile::CSceneryTile(CGrid* grid) : CTile(grid)
{
	this->SetValidSpot(false);
}


/**
*  Destructor
*/
CSceneryTile::~CSceneryTile()
{
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CSceneryTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CTile::XmlLoad(node);
	// any specific attributes we wanna add to the SceneryTile
}