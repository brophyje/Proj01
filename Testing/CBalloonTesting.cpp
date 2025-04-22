#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Ballooncounter.h"
#include "Balloon.h"

#include<memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CBalloonCounterTest)
	{
	public:

		TEST_METHOD(BalloonCounterTest)
		{
			CGame game;

			auto B1 = std::make_shared<CBalloon>(&game, 0, 0);
			auto B2 = std::make_shared<CBalloon>(&game, 0, 0);

			CBalloonCounter visitor1;
			game.Accept(&visitor1);

			Assert::IsTrue(visitor1.GetNumBalloons() == 0);

			game.AddItem(B1);
			game.AddItem(B2);

			CBalloonCounter visitor2;
			game.Accept(&visitor2);

			Assert::IsTrue(visitor2.GetNumBalloons() == 2);
		}

	};
}