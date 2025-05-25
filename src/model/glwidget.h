#ifndef S21_3DVIEWER_V2_0_SRC_MODEL_GLWIDGET_H_
#define S21_3DVIEWER_V2_0_SRC_MODEL_GLWIDGET_H_

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE_
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#elif __linux__
#include <GL/gl.h>
#endif

#include <QOpenGLWidget>
#include <QtOpenGL>

struct Colors {
  QColor background;
  QColor vertices;
  QColor edges;
};

struct Sizes {
  int line_width_;
  int size_vertices_;
};

struct Types {
  int type_projection_;
  int type_edge_;
  int type_vertices;
};

namespace s21 {
class GlWidget : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  GlWidget(QWidget* parent = nullptr);
  ~GlWidget() = default;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void Normalize();
  void Centralization();
  std::vector<float>& GetVertices();
  QColor GetColors(int num_color);
  int GetSizes(int num_size);
  int GetTypes(int num_type);
  void SetVertices(std::vector<float> vertices);
  void SetColors(QColor color, int num_color);
  void SetSizes(int size, int num_size);
  void SetTypes(int type, int num_type);
  void SetEdges(std::vector<unsigned int> edges);
  void SetMinMax(float min_max[6]);

 private:
  void DrawEdges();
  void DrawVertices();
  void ResetTransformation();
  float normalize_;
  std::vector<float> vertices_;
  std::vector<unsigned int> edges_;
  float min_max_[6];
  Colors colors_;
  Sizes sizes_;
  Types types_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_0_SRC_MODEL_GLWIDGET_H_
