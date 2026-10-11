#pragma once
#include <cmath>

struct Vector2 {
  float x{0.0f};
  float y{0.0f};

  constexpr Vector2() = default;
  constexpr Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator+(const Vector2 &other) const;

  Vector2 operator-(const Vector2 &other) const;

  Vector2 operator*(float scalar) const;

  float length_squared() const;

  float length() const;

  Vector2 normalized() const;

  constexpr float clamp(const float &v , const float &lo , const float &hi) const{
    if (v < lo) {
      return lo;
    } else if (hi < v) {
      return hi;
    } else {
      return v;
    }
  }

  constexpr Vector2 clamp(const Vector2 &vectorMIN , const Vector2 &vectorMAX) const{
    return {
      clamp(x , vectorMIN.x , vectorMAX.x),
      clamp(y , vectorMIN.y , vectorMAX.y)
    };
  }  
};

