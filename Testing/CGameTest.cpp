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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:

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


	};
}