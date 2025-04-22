#include "pch.h"
#include "CppUnitTest.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

#include "CppUnitTest.h"
#include "Grid.h"
#include "Tile.h"
#include "Game.h"
#include "GrassTile.h"
#include "RoadTile.h"
#include "SceneryTile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CXmlTest)
	{
	public:

		/**
		 * Read a file into a wstring and return it.
		 * \param filename Name of the file to read
		 * \return File contents
		 */
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}


		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCGameConstruct)
		{
			// Create game
			CGame game;
		}

		TEST_METHOD(TestCGridConstruct)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);
		}
		
		TEST_METHOD(TestCGridClear)
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

			grid.Clear();

			Assert::IsFalse(grid.begin() != grid.end());
		}


		TEST_METHOD(TestCGridLoad)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);

			// Test Load of Level0a
			wstring filename = L"levels/level0a.xml";
			grid.Load(filename);

			// Check count of tiles
			int items = 0;
			for (auto tile : grid)
			{
				items++;
			}
			Assert::IsTrue(items == 25);

			// Check Starting Tile position is correct
			Assert::IsTrue(grid.GetStartX() == 0);
			Assert::IsTrue(grid.GetStartY() == 7 * 64 + 32);

		}

	};
}