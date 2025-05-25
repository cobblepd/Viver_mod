#ifndef S21_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_
#define S21_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_

#include <qgifimage.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent, s21::Controller &controller);
  ~MainWindow();

 private slots:
  void on_open_file_clicked();
  void on_doubleSpinBox_move_x_valueChanged(double arg1);
  void on_doubleSpinBox_move_y_valueChanged(double arg1);
  void on_doubleSpinBox_move_z_valueChanged(double arg1);
  void on_doubleSpinBox_rotate_x_valueChanged(double arg1);
  void on_doubleSpinBox_rotate_y_valueChanged(double arg1);
  void on_doubleSpinBox_rotate_z_valueChanged(double arg1);
  void on_doubleSpinBox_scale_valueChanged(double arg1);
  void on_spinBox_line_width_valueChanged(int arg1);
  void on_color_background_clicked();
  void on_color_edge_clicked();
  void on_color_vertex_clicked();
  void on_spinBox_size_vertices_valueChanged(int arg1);
  void SetTypeEdges();
  void SetVertices();
  void SetTypeProjection();
  void on_SCREEN_clicked();
  void on_gif_clicked();
  void StartTimerGif();

 private:
  void ResetTransformation();
  void SaveSettings();
  void LoadSettings();

  void SetRadioButtonChecked(QRadioButton *radioButton, bool checked);
  Ui::MainWindow *ui;
  QSettings *settings;
  QGifImage *gif_frame;
  QTimer *timer;
  s21::Controller &controller_;
  int timecount;
  QString filePat;
};
#endif  // #define S21_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_
