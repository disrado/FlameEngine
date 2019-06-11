#include "pch.hpp"

#include <util/Id.hpp>

TEST(Vector2Test, UniqueId)
{
    std::vector<flm::Id> ids;

    for (size_t i{ 0 }; i < 100; ++i) {
        ids.push_back(flm::UniqueId());
    }

    for (size_t i{ 0 }; i < 100; ++i) {
        for (size_t j{ i + 1 }; j < 100; ++j) {
            ASSERT_NE(ids[i], ids[j]);
        }
    }
}


TEST(Vector2Test, TypeId)
{
    ASSERT_NE(flm::TypeId<int>(), flm::TypeId<double>());
    ASSERT_NE(flm::TypeId<std::vector<int>>(), flm::TypeId<std::vector<double>>());
}