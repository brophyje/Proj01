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
#include "ControlPanel.h"
#include "Tile.h"
#include "GrassTile.h"
#include "RoadTile.h"
#include "SceneryTile.h"
#include "TowerWave.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CControlPanelTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCControlPanelConstruct)
		{
			// Create game
			CGame game;

			// Create control panel
			CControlPanel controlPanel(&game);

		}

		TEST_METHOD(TestCControlPanelReset)
		{
			// Create game
			CGame game;

			// Create control panel
			CControlPanel controlPanel(&game);

			controlPanel.Reset();
		}

		TEST_METHOD(TestCControlPanelHitTest)
		{
			// Create game
			CGame game;

			// Create grid
			CGrid grid(&game);

			// Create control panel
			CControlPanel controlPanel(&game);
			controlPanel.GetGoButton()->SetActive(true);

			// Test Contorl Panel Towers
			Assert::IsTrue(controlPanel.HitTest(1124, 82) != nullptr,
				L"Testing wave tower");
			Assert::IsTrue(controlPanel.HitTest(1124, 182) != nullptr,
				L"Testing 8shot tower");
			Assert::IsTrue(controlPanel.HitTest(1124, 282) != nullptr,
				L"Testing bomb tower");
			Assert::IsTrue(controlPanel.HitTest(1124, 382) != nullptr,
				L"Testing sniper tower");

			// Test Grid
			Assert::IsTrue(controlPanel.HitTest(100, 200) == nullptr,
				L"Testing empty grid");

		}

	};
}