#include "pch.h"
#include "CppUnitTest.h"

#include <cmath>
#include <string>
#include "Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RendererQA
{
	TEST_CLASS(RendererQA)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);		//Pass if 1 is equal to one
			Assert::AreNotEqual(1, 5);	//Pass if 5 is not equal to 1
		}
	};
}
