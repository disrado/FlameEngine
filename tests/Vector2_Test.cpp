#include <system/Vector2.hpp>

#include <gtest/gtest.h>

#include <memory>


TEST(Vector2Test, Construction)
{
    ae::Vector2i vec;

    ASSERT_TRUE((vec.x == 0) && (vec.y == 0));

    vec = ae::Vector2i{ 5, 6 };

    ASSERT_TRUE((vec.x == 5) && (vec.y == 6));

    ae::Vector2f fvec{ vec };

    ASSERT_TRUE((fvec.x == 5.0) && (fvec.y == 6.0));
}


TEST(Vector2Test, Negation)
{
    ae::Vector2i posVec2{ 1, 2 };
    ae::Vector2i negVec2{ -1, -2 };

    ASSERT_TRUE(-posVec2 == negVec2);
}


TEST(Vector2Test, Addition)
{
    ae::Vector2i posVec2{ 1, 2 };
    ae::Vector2i negVec2{ -1, -2 };

    ASSERT_EQ(posVec2 + negVec2, ae::Vector2i(0, 0));
}


TEST(Vector2Test, AdditionAndAssigning)
{
    ae::Vector2i posVec2{ 1, 2 };
    ae::Vector2i vec10{ 10, 10 };

    posVec2 += ae::Vector2i{ 9, 8 };

    ASSERT_EQ(posVec2, vec10);
}


TEST(Vector2Test, Subtraction)
{
    ae::Vector2i posVec2{ 1, 10 };

    ASSERT_EQ(posVec2 - ae::Vector2i( 5, 5 ), ae::Vector2i( -4, 5 ));
}


TEST(Vector2Test, SubtractionAndAssignment)
{
    ae::Vector2i posVec2{ 1, 2 };

    posVec2 -= ae::Vector2i{ 3, 3 };

    ASSERT_EQ(posVec2, ae::Vector2i(-2, -1));
}


TEST(Vector2Test, Multiplication)
{
    ae::Vector2i posVec2{ 1, 2 };

    ASSERT_EQ(posVec2 * 5, 5 * posVec2);
}


TEST(Vector2Test, MultiplicationAndAssignment)
{
    ae::Vector2i posVec2{ 1, 2 };

    posVec2 *= 4;

    ASSERT_EQ(posVec2, ae::Vector2i(4, 8));
}


TEST(Vector2Test, Division)
{
    ae::Vector2i negVec2{ -8, -8 };

    ASSERT_EQ(negVec2 / ae::Vector2i(-4, -4), ae::Vector2i(2, 2));

    ASSERT_EQ(negVec2 / 2, ae::Vector2i(-4, -4));
}


TEST(Vector2Test, DivisionAndAssignment)
{
    ae::Vector2i negVec2{ -8, -8 };

    negVec2 /= 4;

    ASSERT_EQ(negVec2, ae::Vector2i(-2, -2));

    ASSERT_TRUE(negVec2 == ae::Vector2i(-2, -2));
}