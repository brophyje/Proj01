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
#include "Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CScoreboardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCScoreboardConstruct)
		{
			CScoreboard scoreboard;
		}

		TEST_METHOD(TestCScoreboardUpdateScore)
		{
			CScoreboard scoreboard;

			Assert::IsTrue(scoreboard.GetScore() == 0);

			scoreboard.UpdateScore(10);
			Assert::IsTrue(scoreboard.GetScore() == 10);
			
			scoreboard.UpdateScore(100);
			Assert::IsTrue(scoreboard.GetScore() == 110);

			scoreboard.UpdateScore(-10);
			Assert::IsTrue(scoreboard.GetScore() == 100);

		}

		TEST_METHOD(TestCScoreboardFromControlPanel)
		{
			// Create game
			CGame game;

			// Create control panel
			CControlPanel controlPanel(&game);

			Assert::IsTrue(controlPanel.GetScoreboard()->GetScore() == 0);

			controlPanel.GetScoreboard()->UpdateScore(10);
			Assert::IsTrue(controlPanel.GetScoreboard()->GetScore() == 10);

			controlPanel.GetScoreboard()->UpdateScore(100);
			Assert::IsTrue(controlPanel.GetScoreboard()->GetScore() == 110);

			controlPanel.GetScoreboard()->UpdateScore(-10);
			Assert::IsTrue(controlPanel.GetScoreboard()->GetScore() == 100);

		}

	};
}