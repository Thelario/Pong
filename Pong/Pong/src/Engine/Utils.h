#pragma once

#include <glm/glm.hpp>

class Utils
{
	public:	
		static bool CheckCollisionAABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
		static bool CheckCollisionAABB(bool center_aligned, glm::vec2 p1, int w1, int h1, glm::vec2 p2, int w2, int h2);
		static bool CheckCollisionAABB(bool center_aligned, glm::vec2 p1, glm::vec2 s1, glm::vec2 p2, glm::vec2 s2);

		static void TestMethod1();
		static void TestMethod2();
		static void TestMethod3();
};