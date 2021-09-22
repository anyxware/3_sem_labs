#include "gtest/gtest.h"
#include "../Library/Line.h"
#include "../Library/auxFuncs.h"
#include <iostream>

TEST(Constructor, Constructor) {
	Line line;
	double err = 0.000001;
	EXPECT_NEAR(line.get_radius(), 1, err);
	EXPECT_THROW({
			Line(-1);
		}, std::exception);
	Line line1(2);
	EXPECT_NEAR(line1.get_radius(), 2, err); 
	Line line2(3.1415);
	EXPECT_NEAR(line1.get_radius(), 3.1415, err);
	Line  line3(9 * 10);
	EXPECT_NEAR(line1.get_radius(), 90, err);
}

TEST(Methods, Setter) {
	double err = 0.00001;
	Line line;
	line.set_radius(2);
	EXPECT_NEAR(line.get_radius(), 2, err);
	EXPECT_THROW({
			line.set_radius(-1);
		}, std::exception);
	EXPECT_NEAR(line.get_radius(), 2, err);
	line.set_radius(3.1415);
	EXPECT_NEAR(line.get_radius(), 2, err);
}

TEST(Methods, OtherMethods) {
	double err = 0.00001;
	Line line;
	EXPECT_NEAR(line.area(1, 2), 1.89564427, err);
	EXPECT_NEAR(line.length(1, 2), 2.698242, err);
	EXPECT_NEAR(line.curvature(1), 1.2784681, err);
	EXPECT_NEAR(line.distance(1), 0.9193953, err);
	EXPECT_NEAR(line.area(2, 3), 6.3114, err);
	EXPECT_NEAR(line.length(2, 3), 3.75652, err);
	EXPECT_NEAR(line.curvature(2), 2.24392, err);
	EXPECT_NEAR(line.distance(2), 2.83229, err);

	Coords coords1, coords2;
	line.farthest_points(coords1, coords2);
	EXPECT_NEAR(coords1.x, -0.5, err);
	EXPECT_NEAR(coords1.y, -2.59808, err);
	EXPECT_NEAR(coords2.x, -0.5, err);
	EXPECT_NEAR(coords2.y, 2.59808, err);
	line.set_radius(2);
	line.farthest_points(coords1, coords2);
	EXPECT_NEAR(coords1.x, -1, err);
	EXPECT_NEAR(coords1.y, -5.19616, err);
	EXPECT_NEAR(coords2.x, -1, err);
	EXPECT_NEAR(coords2.y, 5.19616, err);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}