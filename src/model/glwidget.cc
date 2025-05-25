#include "glwidget.h"

namespace s21 {
GlWidget::GlWidget(QWidget* parent) : QOpenGLWidget(parent) {
  colors_.background = Qt::black;
  colors_.edges = Qt::white;
  colors_.vertices = Qt::red;
  sizes_.line_width_ = 1;
  sizes_.size_vertices_ = 1;
  types_.type_projection_ = 0;
  types_.type_edge_ = 0;
  types_.type_vertices = 0;
  normalize_ = 0;
};
void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
};
void GlWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); };
void GlWidget::paintGL() {
  glClearColor(colors_.background.redF(), colors_.background.greenF(),
               colors_.background.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glEnableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();
  glVertexPointer(3, GL_FLOAT, 0, vertices_.data());
  float aspect = (float)width() / (float)height();

  if (types_.type_projection_ == 0) {
    glFrustum(-1 * aspect * normalize_, 1 * normalize_ * aspect,
              -1 * normalize_, 1 * normalize_, normalize_, 1000 * normalize_);
    glTranslatef(0, 0, -2 * normalize_);
    glRotatef(30, 1, 0, 0);
  } else if (types_.type_projection_ == 1) {
    glOrtho(-1 * normalize_ * aspect, 1 * normalize_ * aspect, -1 * normalize_,
            1 * normalize_, -1000 * normalize_, 1000 * normalize_);
    glTranslatef(0, -normalize_ / 2.0, 0);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  DrawEdges();
  if (types_.type_vertices) {
    DrawVertices();
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}
void GlWidget::DrawEdges() {
  if (types_.type_edge_) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0b1111000011110000);
  }
  glLineWidth(sizes_.line_width_);
  glColor3f(colors_.edges.redF(), colors_.edges.greenF(),
            colors_.edges.blueF());
  glDrawElements(GL_LINES, edges_.size(), GL_UNSIGNED_INT, edges_.data());
  if (types_.type_edge_) {
    glDisable(GL_LINE_STIPPLE);
  }
}
void GlWidget::DrawVertices() {
  if (types_.type_vertices == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(sizes_.size_vertices_);
  glColor3f(colors_.vertices.redF(), colors_.vertices.greenF(),
            colors_.vertices.blueF());
  glDrawArrays(GL_POINTS, 0, vertices_.size() / 3.0);
  if (types_.type_vertices == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void GlWidget::Normalize() {
  normalize_ = 0;
  const unsigned int vertexCount = vertices_.size();
  for (unsigned int i = 0; i < vertexCount; i++) {
    const float vertexValue = fabs(vertices_[i]);
    if (vertexValue > normalize_) {
      normalize_ = vertexValue;
    }
  }
}

void GlWidget::Centralization() {
  float center_x = (min_max_[0] + min_max_[1]) / 2;
  float center_y = (min_max_[2] + min_max_[3]) / 2;
  float center_z = (min_max_[4] + min_max_[5]) / 2;
  for (unsigned int i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] -= center_x;
    vertices_[i + 1] -= center_y;
    vertices_[i + 2] -= center_z;
  }

  float max_dim =
      std::max({min_max_[1] - min_max_[0], min_max_[3] - min_max_[2],
                min_max_[5] - min_max_[4]});
  float scale = 1.0 / max_dim;
  for (unsigned int i = 0; i < vertices_.size(); ++i) {
    vertices_[i] *= scale;
  }
}

std::vector<float>& GlWidget::GetVertices() { return vertices_; }

void GlWidget::SetMinMax(float min_max[6]) {
  min_max_[0] = min_max[0];
  min_max_[1] = min_max[1];
  min_max_[2] = min_max[2];
  min_max_[3] = min_max[3];
  min_max_[4] = min_max[4];
  min_max_[5] = min_max[5];
}

void GlWidget::SetVertices(std::vector<float> vertices) {
  vertices_ = vertices;
  update();
}
void GlWidget::SetEdges(std::vector<unsigned int> edges) {
  edges_ = edges;
  update();
}

QColor GlWidget::GetColors(int num_color) {
  QColor res;
  if (num_color == 0) {
    res = colors_.background;
  } else if (num_color == 1) {
    res = colors_.vertices;
  } else {
    res = colors_.edges;
  }
  return res;
}

void GlWidget::SetColors(QColor color, int num_color) {
  if (num_color == 0) {
    colors_.background = color;
  } else if (num_color == 1) {
    colors_.vertices = color;
  } else {
    colors_.edges = color;
  }
  update();
};

int GlWidget::GetSizes(int num_size) {
  int size;
  if (num_size == 0) {
    size = sizes_.line_width_;
  } else {
    size = sizes_.size_vertices_;
  }
  return size;
};

void GlWidget::SetSizes(int size, int num_size) {
  if (num_size == 0) {
    sizes_.line_width_ = size;
  } else {
    sizes_.size_vertices_ = size;
  }
  update();
};

int GlWidget::GetTypes(int num_type) {
  int type;
  if (num_type == 0) {
    type = types_.type_projection_;
  } else if (num_type == 1) {
    type = types_.type_edge_;
  } else {
    type = types_.type_vertices;
  }
  return type;
}

void GlWidget::SetTypes(int type, int num_type) {
  if (num_type == 0) {
    types_.type_projection_ = type;
  } else if (num_type == 1) {
    types_.type_edge_ = type;
  } else {
    types_.type_vertices = type;
  }
  update();
}

}  // namespace s21
