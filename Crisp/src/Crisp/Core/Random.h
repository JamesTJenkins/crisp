#pragma once
#include <random>

// GLM messes with numeric limits max so temp disable
#pragma push_macro("max")
#undef max

class Random {
public:
	// @breif Get a random value between 0 and 1
	// @return Float value between 0 and 1
	static float Value() {
		rng.seed(std::random_device()());
		return (float)udist(rng) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	inline static std::mt19937 rng;
	inline static std::uniform_int_distribution<std::mt19937::result_type> udist;
};

#pragma pop_macro("max")
