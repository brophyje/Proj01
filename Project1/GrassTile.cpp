/**
 * \file GrassTile.cpp
 *
 * \author Jered Brophy
 */

#include "pch.h"
#include "GrassTile.h"

using namespace std;
using namespace Gdiplus;


 /** Constructor
 * \param grid The grid this is a member of
 */
CGrassTile::CGrassTile(CGrid* grid) : CTile(grid)
{
}


/**
*  Destructor
*/
CGrassTile::~CGrassTile()
{
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CGrassTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CTile::XmlLoad(node);
	// any specific attributes we wanna add to GrassTile
}

