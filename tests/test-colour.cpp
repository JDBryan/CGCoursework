#include <gtest/gtest.h>
#include <CanvasLine.h>
#include <Colour.h>
#include <math.h>

TEST(ColourTest, TestPackAndUnpack) {
  Colour red = Colour(255, 0, 0);
  Colour green = Colour(0, 255, 0);
  Colour blue = Colour(0, 0, 255);
  Colour white = Colour(200, 255, 100);

  ASSERT_EQ(red.red(), Colour(red.pack()).red());
  ASSERT_EQ(red.green(), Colour(red.pack()).green());
  ASSERT_EQ(red.blue(), Colour(red.pack()).blue());

  ASSERT_EQ(green.red(), Colour(green.pack()).red());
  ASSERT_EQ(green.green(), Colour(green.pack()).green());
  ASSERT_EQ(green.blue(), Colour(green.pack()).blue());

  ASSERT_EQ(blue.red(), Colour(blue.pack()).red());
  ASSERT_EQ(blue.green(), Colour(blue.pack()).green());
  ASSERT_EQ(blue.blue(), Colour(blue.pack()).blue());

  ASSERT_EQ(white.red(), Colour(white.pack()).red());
  ASSERT_EQ(white.green(), Colour(white.pack()).green());
  ASSERT_EQ(white.blue(), Colour(white.pack()).blue());
};
