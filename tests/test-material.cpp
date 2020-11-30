#include <gtest/gtest.h>
#include <CanvasLine.h>
#include <Material.h>
#include <math.h>

TEST(MaterialTest, TestColourGetterAndSetter) {
  Material material = Material();
  Colour colour = Colour(255, 0, 0);
  material.setColour(colour);

  ASSERT_EQ(colour.red(), material.getColour().red());

};
