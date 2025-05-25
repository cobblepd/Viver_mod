#ifndef S21_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
#define S21_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/affinetransformation.h"
#include "../model/glwidget.h"
#include "../model/parser.h"
namespace s21 {
class Controller {
 public:
  Controller(s21::Parser& parser, s21::AffineTransformation& affine);
  ~Controller() = default;
  void ParsFile(const std::string file_path);
  void MoveX(float value);
  void MoveY(float value);
  void MoveZ(float value);
  void RotateX(float value);
  void RotateY(float value);
  void RotateZ(float value);
  void Scale(float value);

  QColor GetColors(int num_color);
  void SetColors(QColor color, int num_color);

  int GetSizes(int num_size);
  void SetSizes(int size, int num_size);

  int GetTypes(int num_type);
  void SetTypes(int type, int num_type);

  void SetGlWidget(GlWidget* gl);
  const std::vector<float>& GetVertices();
  const std::vector<unsigned int>& GetEdges();

 private:
  s21::Parser& parser_;
  s21::AffineTransformation& affine_;
  s21::GlWidget* glwidget_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
