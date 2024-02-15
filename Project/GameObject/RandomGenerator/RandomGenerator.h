#pragma once

#include <iostream>
#include <random>

#include "Vector2.h"
#include "Vector3.h"


// �͈�
struct Scope {
	float min;
	float max;
};
struct ScopeVec4 {
	Scope X;
	Scope Y;
	Scope Z;
	Scope W;
};
struct ScopeVec3 {
	Scope X;
	Scope Y;
	Scope Z;
};
struct ScopeVec2 {
	Scope X;
	Scope Y;
};


inline Scope operator+(const Scope& s, const float& n) {
	return { s.min + n, s.max + n };
}

class RandomGenerator {

public:

	~RandomGenerator() {};


	static RandomGenerator* GetInstance() {
		static RandomGenerator instance;
		return &instance;
	}


	static float getRandom(Scope scope) {

		std::uniform_real_distribution<float>
			distribution(scope.min, scope.max);

		float result = distribution(RandomGenerator::GetInstance()->randomEngine);

		return result;
	}

	static Vector2 getRandom(ScopeVec2 scope) {

		std::uniform_real_distribution<float>
			distributionA(scope.X.min, scope.X.max);
		std::uniform_real_distribution<float>
			distributionB(scope.Y.min, scope.Y.max);

		Vector2 result = {
			distributionA(RandomGenerator::GetInstance()->randomEngine),
			distributionB(RandomGenerator::GetInstance()->randomEngine),
		};

		return result;
	}

	static Vector3 getRandom(ScopeVec3 scope) {

		std::uniform_real_distribution<float>
			distributionA(scope.X.min, scope.X.max);
		std::uniform_real_distribution<float>
			distributionB(scope.Y.min, scope.Y.max);
		std::uniform_real_distribution<float>
			distributionC(scope.Z.min, scope.Z.max);

		Vector3 result = {
			distributionA(RandomGenerator::GetInstance()->randomEngine),
			distributionB(RandomGenerator::GetInstance()->randomEngine),
			distributionC(RandomGenerator::GetInstance()->randomEngine),
		};

		return result;
	}

	static Scope convertToVec2(float val) {

		Scope result = {
			.min = -val,
			.max = std::abs(val),
		};

		return result;
	}

	//static Vector4 getColorRandom(ScopeVec4 scope) {

	//	std::uniform_real_distribution<float>
	//		distributionA(scope.X.min, scope.X.max);
	//	std::uniform_real_distribution<float>
	//		distributionB(scope.Y.min, scope.Y.max);
	//	std::uniform_real_distribution<float>
	//		distributionC(scope.Z.min, scope.Z.max);
	//	std::uniform_real_distribution<float>
	//		distributionD(scope.W.min, scope.W.max);

	//	Vector4 randColor = {
	//		distributionA(RandomGenerator::GetInstance()->randomEngine),
	//		distributionB(RandomGenerator::GetInstance()->randomEngine),
	//		distributionC(RandomGenerator::GetInstance()->randomEngine),
	//		distributionD(RandomGenerator::GetInstance()->randomEngine),
	//	};
	//	//randColor / 256.0f;
	//		Vector4 resultColor = {
	//			.x randColor
	//		
	//		}

	//	return resultColor;
	//}

private:

	RandomGenerator() {
		std::random_device seedGenerator;
		randomEngine.seed(seedGenerator());
	}

	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator& operator= (const RandomGenerator&) = delete;

private:

	std::mt19937 randomEngine;
};

