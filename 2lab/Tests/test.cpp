#include "gtest/gtest.h"
#include "../Library/Line.h"
#include "../Library/auxFuncs.h"
#include <iostream>

TEST(Constructor, Constructor) {
	Line line;
	EXPECT_EQ(line.get_radius(), 1);
	EXPECT_THROW({
			Line(-1);
		}, std::exception);
	Line line1(2);
	EXPECT_EQ(line1.get_radius(), 2);
}

TEST(Methods, Setter) {
	Line line;
	line.set_radius(2);
	EXPECT_EQ(line.get_radius(), 2);
	EXPECT_EQ(line.set_radius(-1), false);
	EXPECT_EQ(line.get_radius(), 2);
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

	Coords* coords = safety_alloc<Coords>(2);
	coords = line.farthest_points();
	if (coords) {
		EXPECT_NEAR(coords[0].x, -0.5, err);
		EXPECT_NEAR(coords[0].y, -2.59808, err);
		EXPECT_NEAR(coords[1].x, -0.5, err);
		EXPECT_NEAR(coords[1].y, 2.59808, err);
	}
	delete[] coords;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}