#include "MathUtils.h"

#include <glm/gtx/matrix_decompose.hpp>

bool MathUtilities::MathUtils::DecomposeTransform(const glm::mat4& transform, glm::vec3& pos, glm::vec3& rotation, glm::vec3& scale)
{
	// From glm::decompose in matrix_decompose.inl

	using namespace glm;
	using T = float;

	mat4 LocalMatrix(transform);

	// Normalize the matrix.
	if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
		return false;

	// First, isolate perspective.  This is the messiest.
	if (
		epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
		epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
		epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
	{
		// Clear the perspective partition
		LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
		LocalMatrix[3][3] = static_cast<T>(1);
	}

	// Next take care of translation (easy).
	pos = vec3(LocalMatrix[3]);
	LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

	vec3 Row[3], Pdum3;

	// Now get scale and shear.
	for (length_t i = 0; i < 3; ++i)
		for (length_t j = 0; j < 3; ++j)
			Row[i][j] = LocalMatrix[i][j];

	// Compute X scale factor and normalize first row.
	scale.x = length(Row[0]);
	Row[0] = detail::scale(Row[0], static_cast<T>(1));
	scale.y = length(Row[1]);
	Row[1] = detail::scale(Row[1], static_cast<T>(1));
	scale.z = length(Row[2]);
	Row[2] = detail::scale(Row[2], static_cast<T>(1));

	// At this point, the matrix (in rows[]) is orthonormal.
	// Check for a coordinate system flip.  If the determinant
	// is -1, then negate the matrix and the scaling factors.
#if 0
	Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
	if (dot(Row[0], Pdum3) < 0)
	{
		for (length_t i = 0; i < 3; i++)
		{
			scale[i] *= static_cast<T>(-1);
			Row[i] *= static_cast<T>(-1);
		}
	}
#endif

	rotation.y = asin(-Row[0][2]);
	if (cos(rotation.y) != 0) {
		rotation.x = atan2(Row[1][2], Row[2][2]);
		rotation.z = atan2(Row[0][1], Row[0][0]);
	}
	else {
		rotation.x = atan2(-Row[2][0], Row[1][1]);
		rotation.z = 0;
	}


	return true;
}

float MathUtilities::MathUtils::Remap(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
	if (value < inputMin) value = inputMin;
	if (value > inputMax) value = inputMax;

	float normalizedValue = (value - inputMin) / (inputMax - inputMin);

	float remapValue = outputMin + normalizedValue * (outputMax - outputMin);

	return remapValue;
}

const float MathUtilities::MathUtils::GetRandomFloatNumber(float minValue, float maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(minValue, maxValue);

	return distribution(gen);
}

const int MathUtilities::MathUtils::GetRandomIntNumber(int minValue, int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minValue, maxValue);

	return distribution(gen);
}

glm::vec3 MathUtilities::MathUtils::Lerp(const glm::vec3& start, const glm::vec3& end, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return start + t * (end - start);
}

float MathUtilities::MathUtils::Lerp(const float& start, const float& end, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return start + t * (end - start);
}

double MathUtilities::MathUtils::CalculateTForSpeed(double currentT, double deltaTime, double lerpSpeed)
{
	double step = lerpSpeed * deltaTime;

	return glm::clamp(currentT + step, 0.0, 1.0);
}
