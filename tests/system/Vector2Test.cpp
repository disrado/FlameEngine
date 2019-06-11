#include "pch.hpp"

#include <system/Vector2.hpp>

TEST(Vector2Test, Construction)
{
    flm::Vector2i vec;

    ASSERT_TRUE((vec.x == 0) && (vec.y == 0));

    vec = flm::Vector2i{ 5, 6 };

    ASSERT_TRUE((vec.x == 5) && (vec.y == 6));

    flm::Vector2f fvec{ vec };

    ASSERT_TRUE((fvec.x == 5.0) && (fvec.y == 6.0));
}


TEST(Vector2Test, Negation)
{
    flm::Vector2i posVec2{ 1, 2 };
    flm::Vector2i negVec2{ -1, -2 };

    ASSERT_TRUE(-posVec2 == negVec2);
}


TEST(Vector2Test, Addition)
{
    flm::Vector2i posVec2{ 1, 2 };
    flm::Vector2i negVec2{ -1, -2 };

    ASSERT_EQ(posVec2 + negVec2, flm::Vector2i(0, 0));
}


TEST(Vector2Test, AdditionAndAssigning)
{
    flm::Vector2i posVec2{ 1, 2 };
    flm::Vector2i vec10{ 10, 10 };

    posVec2 += flm::Vector2i{ 9, 8 };

    ASSERT_EQ(posVec2, vec10);
}


TEST(Vector2Test, Subtraction)
{
    flm::Vector2i posVec2{ 1, 10 };

    ASSERT_EQ(posVec2 - flm::Vector2i( 5, 5 ), flm::Vector2i( -4, 5 ));
}


TEST(Vector2Test, SubtractionAndAssignment)
{
    flm::Vector2i posVec2{ 1, 2 };

    posVec2 -= flm::Vector2i{ 3, 3 };

    ASSERT_EQ(posVec2, flm::Vector2i(-2, -1));
}


TEST(Vector2Test, Multiplication)
{
    flm::Vector2i posVec2{ 1, 2 };

    ASSERT_EQ(posVec2 * 5, 5 * posVec2);
}


TEST(Vector2Test, MultiplicationAndAssignment)
{
    flm::Vector2i posVec2{ 1, 2 };

    posVec2 *= 4;

    ASSERT_EQ(posVec2, flm::Vector2i(4, 8));
}


TEST(Vector2Test, Division)
{
    flm::Vector2i negVec2{ -8, -8 };

    ASSERT_EQ(negVec2 / flm::Vector2i(-4, -4), flm::Vector2i(2, 2));

    ASSERT_EQ(negVec2 / 2, flm::Vector2i(-4, -4));
}


TEST(Vector2Test, DivisionAndAssignment)
{
    flm::Vector2i negVec2{ -8, -8 };

    negVec2 /= 4;

    ASSERT_EQ(negVec2, flm::Vector2i(-2, -2));

    ASSERT_TRUE(negVec2 == flm::Vector2i(-2, -2));
}