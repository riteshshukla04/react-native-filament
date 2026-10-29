#pragma once

#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

#include <array>
#include <tuple>

namespace margelo::nitro::filament::physics {

using Mat4Tuple = std::tuple<double, double, double, double, double, double, double, double, double, double, double, double, double, double,
                             double, double>;

inline btVector3 toBtVector3(const std::tuple<double, double, double>& value) {
  auto [x, y, z] = value;
  return {static_cast<btScalar>(x), static_cast<btScalar>(y), static_cast<btScalar>(z)};
}

inline std::tuple<double, double, double> fromBtVector3(const btVector3& value) {
  return {value.x(), value.y(), value.z()};
}

inline btQuaternion toBtQuaternion(const std::tuple<double, double, double, double>& value) {
  auto [x, y, z, w] = value;
  return {static_cast<btScalar>(x), static_cast<btScalar>(y), static_cast<btScalar>(z), static_cast<btScalar>(w)};
}

inline std::array<float, 16> toColumnMajor(const btTransform& transform) {
  std::array<float, 16> matrix;
  transform.getOpenGLMatrix(matrix.data());
  return matrix;
}

inline Mat4Tuple toMat4Tuple(const btTransform& transform) {
  std::array<float, 16> m = toColumnMajor(transform);
  return {m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]};
}

inline btTransform toBtTransform(const Mat4Tuple& values) {
  std::array<btScalar, 16> m =
      std::apply([](auto... element) { return std::array<btScalar, 16>{static_cast<btScalar>(element)...}; }, values);
  for (int column = 0; column < 3; column++) {
    btVector3 axis = btVector3(m[column * 4], m[column * 4 + 1], m[column * 4 + 2]).normalized();
    m[column * 4] = axis.x();
    m[column * 4 + 1] = axis.y();
    m[column * 4 + 2] = axis.z();
  }
  btTransform transform;
  transform.setFromOpenGLMatrix(m.data());
  return transform;
}

} // namespace margelo::nitro::filament::physics
