#include "affinetransformation.h"

namespace s21 {
void AffineTransformation::MoveX(float value) {
  Normalize();
  float val = (value - move_x_) * normalize_ / 100.0;
  for (unsigned int i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] += val;
  }
  move_x_ = value;
}
void AffineTransformation::MoveY(float value) {
  Normalize();
  float val = (value - move_y_) * normalize_ / 100.0;
  for (unsigned int i = 1; i < vertices_.size(); i += 3) {
    vertices_[i] += val;
  }
  move_y_ = value;
}
void AffineTransformation::MoveZ(float value) {
  Normalize();
  float val = (value - move_z_) * normalize_ / 100.0;
  for (unsigned int i = 2; i < vertices_.size(); i += 3) {
    vertices_[i] += val;
  }
  move_z_ = value;
}
void AffineTransformation::RotateX(float value) {
  value -= rotate_x_;
  float cos_val = cos(DegreesToRadians(value));
  float sin_val = sin(DegreesToRadians(value));
  for (unsigned int i = 0; i < vertices_.size(); i += 3) {
    float temp_y = vertices_[i + 1];
    float temp_z = vertices_[i + 2];
    vertices_[i + 1] = cos_val * temp_y - sin_val * temp_z;
    vertices_[i + 2] = cos_val * temp_z + sin_val * temp_y;
  }
  rotate_x_ = value;
}
void AffineTransformation::RotateY(float value) {
  value -= rotate_y_;
  float cos_val = cos(DegreesToRadians(value));
  float sin_val = sin(DegreesToRadians(value));
  for (unsigned int i = 0; i < vertices_.size(); i += 3) {
    float temp_x = vertices_[i];
    float temp_z = vertices_[i + 2];
    vertices_[i] = cos_val * temp_x + sin_val * temp_z;
    vertices_[i + 2] = cos_val * temp_z - sin_val * temp_x;
  }
  rotate_y_ = value;
}
void AffineTransformation::RotateZ(float value) {
  value -= rotate_z_;
  float cos_val = cos(DegreesToRadians(value));
  float sin_val = sin(DegreesToRadians(value));
  for (unsigned int i = 0; i < vertices_.size(); i += 3) {
    float temp_x = vertices_[i];
    float temp_y = vertices_[i + 1];
    vertices_[i] = cos_val * temp_x - sin_val * temp_y;
    vertices_[i + 1] = cos_val * temp_y + sin_val * temp_x;
  }
  rotate_z_ = value;
}
void AffineTransformation::Scale(float value) {
  float val = value / scale_;
  for (unsigned int i = 0; i < vertices_.size(); i++) {
    vertices_[i] *= val;
  }
  scale_ = value;
}

void AffineTransformation::ResetTransformation() {
  move_x_ = 0;
  move_y_ = 0;
  move_z_ = 0;
  rotate_x_ = 0;
  rotate_y_ = 0;
  rotate_z_ = 0;
  scale_ = 50;
  normalize_ = 0;
}

void AffineTransformation::Normalize() {
  const unsigned int vertexCount = vertices_.size();
  for (unsigned int i = 0; i < vertexCount; i++) {
    const float vertexValue = fabs(vertices_[i]);
    if (vertexValue > normalize_) {
      normalize_ = vertexValue;
    }
  }
}
float AffineTransformation::DegreesToRadians(float degrees) {
  return degrees * M_PI / 180;
}

std::vector<float>& AffineTransformation::GetVertices() { return vertices_; };

void AffineTransformation::SetVertices(std::vector<float>& vertices) {
  vertices_ = vertices;
}
}  // namespace s21
