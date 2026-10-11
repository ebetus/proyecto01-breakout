#include "Math/Vector2.hpp"


Vector2 Vector2::operator+(const Vector2 &other) const {
  return {x + other.x, y + other.y};
}

Vector2 Vector2::operator-(const Vector2 &other) const {
  return {x - other.x , y - other.y};
}

Vector2 Vector2::operator*(float scalar) const {
  return {x * scalar , y * scalar};
}

float Vector2::length_squared() const {
  return x * x + y * y;
}

float Vector2::length() const{
  return std::sqrt(length_squared());
}

Vector2 Vector2::normalized() const {
  float len = length();
  if(len > 0.0001f) {
    return {x / len , y / len};
  }
  return {0.0f , 0.0f};
}




