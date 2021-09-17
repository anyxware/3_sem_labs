#include "gtest/gtest.h"
#include "../Library/Line.h"
#include <iostream>

TEST(Constructor, Constructor) {
	Line line;
	ASSERT_EQ(line.get_radius(), 1);
	EXPECT_THROW({
		try
		{
			Line(-1);
		}
		catch (std::exception& e)
		{
			EXPECT_STREQ("invalid radius", e.what());
			throw;
		}
		}, std::exception);
	Line line1(2);
	ASSERT_EQ(line1.get_radius(), 2);
}

TEST(Methods, Setter) {
	Line line;
	line.set_radius(2);
	ASSERT_EQ(line.get_radius(), 2);
}

TEST(Methods, OtherMethods) {
	double err = 0.000001;
	Line line;
	ASSERT_NEAR(line.area(1, 2), 1.89564427, err);
	ASSERT_NEAR(line.length(1, 2), 2.698242, err);
	ASSERT_NEAR(line.curvature(1), 1.2784681, err);
	ASSERT_NEAR(line.distance(1), 0.9193953, err);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}