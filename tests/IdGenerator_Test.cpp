#include <util/IdGenerator.hpp>

#include <gtest/gtest.h>

#include <vector>


// Ids for different template parameters starts from 0.
TEST(Vector2Test, Construction)
{
	std::vector<flm::Id> validIds{};
	std::vector<flm::Id> firstTypeIds{};
	std::vector<flm::Id> secondTypeIds{};
	
	for (size_t i{ 0 }; i < 100; ++i) {
		validIds.push_back(i);
	}

	for (size_t i{ 0 }; i < 100; ++i) {
		firstTypeIds.push_back(flm::IdGenerator::TypeId<int>());
	}

	for (size_t i{ 0 }; i < 100; ++i) {
		secondTypeIds.push_back(flm::IdGenerator::TypeId<float>());
	}

	ASSERT_EQ(validIds, firstTypeIds);
	ASSERT_EQ(validIds, secondTypeIds);
}