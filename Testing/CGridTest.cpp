#include "pch.h"
#include "CppUnitTest.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <memory>

#include "CppUnitTest.h"
#include "Game.h"
#include "Grid.h"
#include "Tile.h"
#include "GrassTile.h"
#include "RoadTile.h"
#include "SceneryTile.h"
#include "TowerWave.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CGridTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCGridIterator)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);

			// Add some tiles
			auto tile1 = make_shared<CRoadTile>(&grid);
			auto tile2 = make_shared<CRoadTile>(&grid);
			auto tile3 = make_shared<CRoadTile>(&grid);

			grid.Add(tile1);
			grid.Add(tile2);
			grid.Add(tile3);

			// Begin points to the first item
			auto iter1 = grid.begin();

			// End points after the last item
			auto iter2 = grid.end();

			Assert::IsTrue(tile1 == *iter1, L"First item correct");
			++iter1;
			Assert::IsTrue(tile2 == *iter1, L"Second item correct");
			++iter1;
			Assert::IsTrue(tile3 == *iter1, L"Third item correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);


		}

		TEST_METHOD(TestCGridTowerPlacement)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);

			// Add some tiles
			auto tile1 = make_shared<CGrassTile>(&grid);
			auto tile2 = make_shared<CRoadTile>(&grid);
			auto tile3 = make_shared<CSceneryTile>(&grid);

			grid.Add(tile1);
			grid.Add(tile2);
			grid.Add(tile3);

			// Make tower types
			auto tower1 = make_shared<CTowerWave>(&game, tile1->GetX(), tile1->GetY());
			auto tower2 = make_shared<CTowerWave>(&game, tile1->GetX(), tile1->GetY());
			auto tower3 = make_shared<CTowerWave>(&game, tile2->GetX(), tile2->GetY());
			auto tower4 = make_shared<CTowerWave>(&game, tile3->GetX(), tile3->GetY());

			//Should associate tower1 to tile1
			tile1->SetAssociatedTower(tower1.get());
			//Will not associate the tower due to already having a tower
			tile1->SetAssociatedTower(tower2.get());

			//Shouldn't associate either as roads and scenery can't have towers
			tile2->SetAssociatedTower(tower3.get());
			tile3->SetAssociatedTower(tower4.get());

			Assert::IsNotNull(tile1->GetAssociatedTower());
			Assert::IsTrue(tile1->GetAssociatedTower() == tower1.get());
			Assert::IsNull(tile2->GetAssociatedTower());
			Assert::IsNull(tile3->GetAssociatedTower());
		}

		TEST_METHOD(TestCGridTileTest)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);

			wstring filename = L"levels/level1.xml";
			grid.Load(filename);

			// Available tiles
			Assert::IsTrue(grid.TileTest(32,32) != nullptr); // middle
			Assert::IsTrue(grid.TileTest(0, 0) != nullptr); // top left
			Assert::IsTrue(grid.TileTest(63, 63) != nullptr); // bottom right

			// --Non-available tiles--
			// Scenery tiles
			Assert::IsTrue(grid.TileTest(96, 32) == nullptr); // tree
			Assert::IsTrue(grid.TileTest(416, 32) == nullptr); // house
			Assert::IsTrue(grid.TileTest(96, 416) == nullptr); // castle

			//// Road tiles
			Assert::IsTrue(grid.TileTest(288, 96) == nullptr); // SE
			Assert::IsTrue(grid.TileTest(224, 288) == nullptr); // EW
			Assert::IsTrue(grid.TileTest(160, 416) == nullptr); // NS

			// Tower already on tile
			shared_ptr<CGrassTile> tile = make_shared<CGrassTile>(&grid);
			tile->SetLocation(-32, -32);
			shared_ptr<CTowerWave> tower = make_shared<CTowerWave>(&game, -32,-32);
			tower->SetTile(tile);
			tile->SetAssociatedTower(tower.get()); // auto sets mValidTowerSpot to false

			Assert::IsTrue(grid.TileTest(-32, -32) == nullptr);

		}
	};
}