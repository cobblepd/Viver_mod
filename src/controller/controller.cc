#include "controller.h"
namespace s21 {
Controller::Controller(s21::Parser& parser, s21::AffineTransformation& affine)
    : parser_(parser), affine_(affine) {}

void Controller::ParsFile(const std::string file_path) {
  parser_.ParsFile(file_path);
  glwidget_->SetVertices(parser_.GetVertices());
  glwidget_->SetEdges(parser_.GetEdges());
  glwidget_->SetMinMax(parser_.GetMinMax());
  glwidget_->Centralization();
  glwidget_->Normalize();
  glwidget_->update();
};

void Controller::MoveX(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.MoveX(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::MoveY(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.MoveY(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::MoveZ(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.MoveZ(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::RotateX(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.RotateX(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::RotateY(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.RotateY(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::RotateZ(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.RotateZ(value);
  glwidget_->SetVertices(affine_.GetVertices());
}
void Controller::Scale(float value) {
  affine_.SetVertices(glwidget_->GetVertices());
  affine_.Scale(value);
  glwidget_->SetVertices(affine_.GetVertices());
}

int Controller::GetSizes(int num_size) { return glwidget_->GetSizes(num_size); }
void Controller::SetSizes(int size, int num_size) {
  glwidget_->SetSizes(size, num_size);
}

int Controller::GetTypes(int num_type) { return glwidget_->GetTypes(num_type); }
void Controller::SetTypes(int type, int num_type) {
  glwidget_->SetTypes(type, num_type);
}

QColor Controller::GetColors(int num_color) {
  return glwidget_->GetColors(num_color);
};

void Controller::SetColors(QColor color, int num_color) {
  glwidget_->SetColors(color, num_color);
};

void Controller::SetGlWidget(GlWidget* gl) { glwidget_ = gl; };
const std::vector<float>& Controller::GetVertices() {
  return parser_.GetVertices();
}
const std::vector<unsigned int>& Controller::GetEdges() {
  return parser_.GetEdges();
}
}  // namespace s21
