#pragma once

namespace IET
{
	class MathUtility
	{
	public:
		template <typename T>
		static sf::Vector2<T> moveTowards(sf::Vector2<T> current, sf::Vector2<T> target, float maxDistanceDelta)
		{
			sf::Vector2<T> a = target - current;
			float magnitude = a.length();
			if (magnitude <= maxDistanceDelta || magnitude == 0.f)
			{
				return target;
			}
			return current + a / magnitude * maxDistanceDelta;
		}

		template <typename T>
		static sf::Vector3<T> moveTowards(sf::Vector3<T> current, sf::Vector3<T> target, float maxDistanceDelta)
		{
			sf::Vector3<T> a = target - current;
			float magnitude = a.length();
			if (magnitude <= maxDistanceDelta || magnitude == 0.f)
			{
				return target;
			}
			return current + a / magnitude * maxDistanceDelta;
		}

		template <typename T>
		static int sgn(T val) {
			return (T(0) < val) - (val < T(0));
		}

		static float moveTowards(float current, float target, float maxDelta)
		{
			if (abs(target - current) <= maxDelta)
			{
				return target;
			}
			return current + sgn(target - current) * maxDelta;
		}

	};
}