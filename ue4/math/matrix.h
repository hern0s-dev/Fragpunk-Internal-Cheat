#pragma once

namespace ue4::math {
	class matrix {
	public:
		float m[4][4];
	};
}

struct uint128_t {
    uint64_t low;
    uint64_t high;

    uint128_t() : low(0), high(0) {}
    uint128_t(uint64_t value) : low(value), high(0) {}

    uint128_t operator+(const uint128_t& other) const {
        uint128_t result;
        result.low = low + other.low;
        result.high = high + other.high + (result.low < low); // Carry
        return result;
    }

    void print() const {
        return;
       // std::cout << "High: " << high << ", Low: " << low << "\n";
    }
};



#include <corecrt_math_defines.h>

namespace ue4::math {
	class vector {
	public:
		float x, y, z;

		inline ue4::math::vector operator+(const ue4::math::vector& a) const {
			return { x + a.x, y + a.y, z + a.z };
		}

		inline void operator+=(const ue4::math::vector& a) {
			x += a.x, y += a.y, z += a.z;
		}

		inline ue4::math::vector operator-(const ue4::math::vector& a) const {
			return { x - a.x, y - a.y, z - a.z };
		}

		inline void operator-=(const ue4::math::vector& a) {
			x -= a.x, y -= a.y, z -= a.z;
		}

		inline ue4::math::vector operator*(const ue4::math::vector& a) const {
			return { x * a.x, y * a.y, z * a.z };
		}

		inline void operator*=(const ue4::math::vector& a) {
			x *= a.x, y *= a.y, z *= a.z;
		}

		inline ue4::math::vector operator/(const ue4::math::vector& a) const {
			return { x / a.x, y / a.y, z / a.z };
		}

		inline void operator/=(const ue4::math::vector& a) {
			x /= a.x, y /= a.y, z /= a.z;
		}

		inline ue4::math::vector operator+(const float a) const {
			return { x + a, y + a, z + a };
		}

		inline void operator+=(const float a) {
			x += a, y += a, z += a;
		}

		inline ue4::math::vector operator-(const float a) const {
			return { x - a, y - a, z - a };
		}

		inline void operator-=(const float a) {
			x -= a, y -= a, z -= a;
		}

		inline ue4::math::vector operator*(const float a) const {
			return { x * a, y * a, z * a };
		}

		inline void operator*=(const float a) {
			x *= a, y *= a, z *= a;
		}

		inline ue4::math::vector operator/(const float a) const {
			return { x / a, y / a, z / a };
		}

		inline void operator/=(const float a) {
			x /= a, y /= a, z /= a;
		}

		inline ue4::math::vector forward() const {
			float sp{}, sy{}, cp{}, cy{};
			float angle{};

			angle = y * (M_PI / 180.0f);
			sy = sinf(angle);
			cy = cosf(angle);

			angle = -x * (M_PI / 180.0f);
			sp = sinf(angle);
			cp = cosf(angle);

			return { cp * cy, cp * sy, -sp };
		}
		bool zero(float tolerance = 0.01f) const {
			return this->x > -tolerance && this->x < tolerance &&
				this->y > -tolerance && this->y < tolerance &&
				this->z > -tolerance && this->z < tolerance;
		};
	};
}


namespace ue4::math {
	class vector_2d {
	public:
		float x, y;

		inline ue4::math::vector_2d operator+(const ue4::math::vector_2d& a) const {
			return { x + a.x, y + a.y };
		}

		inline void operator+=(const ue4::math::vector_2d& a) {
			x += a.x, y += a.y;
		}

		inline ue4::math::vector_2d operator-(const ue4::math::vector_2d& a) const {
			return { x - a.x, y - a.y };
		}

		inline void operator-=(const ue4::math::vector_2d& a) {
			x -= a.x, y -= a.y;
		}

		inline ue4::math::vector_2d operator*(const ue4::math::vector_2d& a) const {
			return { x * a.x, y * a.y };
		}

		inline void operator*=(const ue4::math::vector_2d& a) {
			x *= a.x, y *= a.y;
		}

		inline ue4::math::vector_2d operator/(const ue4::math::vector_2d& a) const {
			return { x / a.x, y / a.y };
		}

		inline void operator/=(const ue4::math::vector_2d& a) {
			x /= a.x, y /= a.y;
		}

		inline ue4::math::vector_2d operator+(const float a) const {
			return { x + a, y + a };
		}

		inline void operator+=(const float a) {
			x += a, y += a;
		}

		inline ue4::math::vector_2d operator-(const float a) const {
			return { x - a, y - a };
		}

		inline void operator-=(const float a) {
			x -= a, y -= a;
		}

		inline ue4::math::vector_2d operator*(const float a) const {
			return { x * a, y * a };
		}

		inline void operator*=(const float a) {
			x *= a, y *= a;
		}

		inline ue4::math::vector_2d operator/(const float a) const {
			return { x / a, y / a };
		}

		inline void operator/=(const float a) {
			x /= a, y /= a;
		}

		bool is_zero() const {
			if (x == 0.f && y == 0.f) return true;

			return false;
		}
	};
}

#pragma pack(push, 1)
struct FBox {
	ue4::math::vector Min;
	ue4::math::vector Max;
	char padding[8];
};
#pragma pack(pop)