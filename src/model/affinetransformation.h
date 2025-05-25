#ifndef S21_3DVIEWER_V2_0_SRC_MODEL_AFFINETRANSFORMATION_H_
#define S21_3DVIEWER_V2_0_SRC_MODEL_AFFINETRANSFORMATION_H_

#include <cmath>
#include <vector>

namespace s21 {
class AffineTransformation {
 public:
  AffineTransformation()
      : scale_(50),
        move_x_(0),
        move_y_(0),
        move_z_(0),
        rotate_x_(0),
        rotate_y_(0),
        rotate_z_(0),
        normalize_(0){};
  ~AffineTransformation(){};
  void MoveX(float value);
  void MoveY(float value);
  void MoveZ(float value);
  void RotateX(float value);
  void RotateY(float value);
  void RotateZ(float value);
  void Scale(float value);
  void ResetTransformation();
  void Normalize();
  float DegreesToRadians(float degrees);
  void SetVertices(std::vector<float>& vertices);
  std::vector<float>& GetVertices();

 private:
  std::vector<float> vertices_;
  float scale_;
  float move_x_;
  float move_y_;
  float move_z_;
  float rotate_x_;
  float rotate_y_;
  float rotate_z_;
  float normalize_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_0_SRC_MODEL_AFFINETRANSFORMATION_H_
