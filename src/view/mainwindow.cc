#include "mainwindow.h"

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent, s21::Controller& controller)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  timer = new QTimer(0);
  timecount = 0;
  controller_.SetGlWidget(ui->openGLWidget);
  settings = new QSettings("Settings.ini", "Settings", this);
  connect(ui->radioButton_solid, SIGNAL(clicked()), this, SLOT(SetTypeEdges()));
  connect(ui->radioButton_dashed, SIGNAL(clicked()), this,
          SLOT(SetTypeEdges()));
  connect(ui->radioButton_none, SIGNAL(clicked()), this, SLOT(SetVertices()));
  connect(ui->radioButton_circle, SIGNAL(clicked()), this, SLOT(SetVertices()));
  connect(ui->radioButton_square, SIGNAL(clicked()), this, SLOT(SetVertices()));
  connect(ui->radioButton_parallel, SIGNAL(clicked()), this,
          SLOT(SetTypeProjection()));
  connect(ui->radioButton_central, SIGNAL(clicked()), this,
          SLOT(SetTypeProjection()));
  LoadSettings();
  connect(timer, SIGNAL(timeout()), this, SLOT(StartTimerGif()));
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete settings;
  timer->stop();
  delete timer;
  delete ui;
}

void MainWindow::on_open_file_clicked() {
  QString file_path_q = QFileDialog::getOpenFileName(
      this, "Выберите файл", "/home/momzh228/project/vie/src/obj",
      "Файлы (*.obj)");
  if (!file_path_q.isEmpty()) {
    std::string file_path = file_path_q.toStdString();
    controller_.ParsFile(file_path);
    QString count_edge =
        QString::number(controller_.GetVertices().size(), 'g', 15);
    QString count_vertices =
        QString::number(controller_.GetEdges().size(), 'g', 15);
    ui->label_count_edge->setText(count_edge);
    ui->label_count_vertices->setText(count_vertices);
    QFileInfo file_name(file_path_q);
    ui->label_file_name->setText(file_name.baseName());
    ResetTransformation();
  }
}

void MainWindow::ResetTransformation() {
  ui->doubleSpinBox_move_x->setValue(0);
  ui->doubleSpinBox_move_y->setValue(0);
  ui->doubleSpinBox_move_z->setValue(0);
  ui->doubleSpinBox_rotate_x->setValue(0);
  ui->doubleSpinBox_rotate_y->setValue(0);
  ui->doubleSpinBox_rotate_z->setValue(0);
  ui->spinBox_line_width->setValue(1);
  ui->spinBox_size_vertices->setValue(1);
  ui->doubleSpinBox_scale->setValue(50);
}

void MainWindow::on_doubleSpinBox_move_x_valueChanged(double arg1) {
  controller_.MoveX(arg1);
}

void MainWindow::on_doubleSpinBox_move_y_valueChanged(double arg1) {
  controller_.MoveY(arg1);
}

void MainWindow::on_doubleSpinBox_move_z_valueChanged(double arg1) {
  controller_.MoveZ(arg1);
}

void MainWindow::on_doubleSpinBox_rotate_x_valueChanged(double arg1) {
  controller_.RotateX(arg1);
}

void MainWindow::on_doubleSpinBox_rotate_y_valueChanged(double arg1) {
  controller_.RotateY(arg1);
}

void MainWindow::on_doubleSpinBox_rotate_z_valueChanged(double arg1) {
  controller_.RotateZ(arg1);
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  controller_.Scale(arg1);
}

void MainWindow::on_spinBox_line_width_valueChanged(int arg1) {
  controller_.SetSizes(arg1, 0);
}

void MainWindow::on_spinBox_size_vertices_valueChanged(int arg1) {
  controller_.SetSizes(arg1, 1);
}

void MainWindow::SetTypeEdges() {
  if (ui->radioButton_solid->isChecked()) {
    controller_.SetTypes(0, 1);
  } else if (ui->radioButton_dashed->isChecked()) {
    controller_.SetTypes(1, 1);
  }
}

void MainWindow::SetTypeProjection() {
  if (ui->radioButton_parallel->isChecked()) {
    controller_.SetTypes(0, 0);
  } else if (ui->radioButton_central->isChecked()) {
    controller_.SetTypes(1, 0);
  }
}

void MainWindow::SetVertices() {
  if (ui->radioButton_none->isChecked()) {
    controller_.SetTypes(0, 2);
  } else if (ui->radioButton_circle->isChecked()) {
    controller_.SetTypes(1, 2);
  } else if (ui->radioButton_square->isChecked()) {
    controller_.SetTypes(2, 2);
  }
}

void MainWindow::on_color_background_clicked() {
  QColor ColorValue =
      QColorDialog::getColor(Qt::black, this, tr("Select Color"));
  if (ColorValue.isValid()) {
    controller_.SetColors(ColorValue, 0);
  }
}

void MainWindow::on_color_edge_clicked() {
  QColor ColorValue =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  if (ColorValue.isValid()) {
    controller_.SetColors(ColorValue, 2);
  }
}

void MainWindow::on_color_vertex_clicked() {
  QColor ColorValue = QColorDialog::getColor(Qt::red, this, tr("Select Color"));
  if (ColorValue.isValid()) {
    controller_.SetColors(ColorValue, 1);
  }
}

void MainWindow::SaveSettings() {
  settings->setValue("TypeProjection", controller_.GetTypes(0));
  settings->setValue("TypeEdge", controller_.GetTypes(1));
  settings->setValue("TypeVertices", controller_.GetTypes(2));
  settings->setValue("ThicknessOfEdge", controller_.GetSizes(0));
  settings->setValue("SizeVertices", controller_.GetTypes(1));
  settings->setValue("ColorBackground",
                     controller_.GetColors(0).name(QColor::HexRgb));
  settings->setValue("ColorVertices",
                     controller_.GetColors(1).name(QColor::HexRgb));
  settings->setValue("ColorEdge",
                     controller_.GetColors(2).name(QColor::HexRgb));
}

void MainWindow::LoadSettings() {
  controller_.SetTypes(settings->value("TypeProjection", 0).toInt(), 0);
  controller_.SetTypes(settings->value("TypeEdge", 0).toInt(), 1);
  controller_.SetTypes(settings->value("TypeVertices", 0).toInt(), 2);
  controller_.SetSizes(settings->value("ThicknessOfEdge", 0).toInt(), 0);
  controller_.SetSizes(settings->value("SizeVertices", 0).toInt(), 1);
  controller_.SetColors(settings->value("ColorBackground").toString(), 0);
  controller_.SetColors(settings->value("ColorVertices").toString(), 1);
  controller_.SetColors(settings->value("ColorEdge").toString(), 2);
  SetRadioButtonChecked(ui->radioButton_parallel, controller_.GetTypes(0) == 0);
  SetRadioButtonChecked(ui->radioButton_central, controller_.GetTypes(0) == 1);
  SetRadioButtonChecked(ui->radioButton_solid, controller_.GetTypes(1) == 0);
  SetRadioButtonChecked(ui->radioButton_dashed, controller_.GetTypes(1) == 1);
  SetRadioButtonChecked(ui->radioButton_none, controller_.GetTypes(1) == 0);
  SetRadioButtonChecked(ui->radioButton_circle, controller_.GetTypes(2) == 1);
  SetRadioButtonChecked(ui->radioButton_square, controller_.GetTypes(2) == 2);
  ui->spinBox_size_vertices->setValue(controller_.GetSizes(0));
  ui->spinBox_size_vertices->setValue(controller_.GetSizes(1));
}

void MainWindow::SetRadioButtonChecked(QRadioButton* radioButton,
                                       bool checked) {
  if (radioButton) {
    radioButton->setChecked(checked);
  }
}

void MainWindow::on_SCREEN_clicked() {
  QString filePath = QFileDialog::getSaveFileName(
      this, tr("Save File"), "/", tr("Text Files (*.jpeg);;Файлы (*.bmp)"));
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly)) {
    QImage img = ui->openGLWidget->grabFramebuffer();
    if (img.save(filePath)) {
      QMessageBox::information(this, tr("Success"),
                               tr("Image saved successfully."));
    } else {
      QMessageBox::warning(this, tr("Error"), tr("Failed to save the image."));
    }
    file.close();
  } else {
    QMessageBox::warning(this, tr("Error"), tr("Could not save the file."));
  }
}

void MainWindow::on_gif_clicked() {
  filePat = QFileDialog::getSaveFileName(this, tr("Save File"), "/",
                                         tr("Файлы (*.gif)"));

  if (filePat.isEmpty()) {
    QMessageBox::warning(this, tr("Error"), tr("Could not save the file."));
  } else {
    ui->gif->setEnabled(false);
    gif_frame = new QGifImage;
    gif_frame->setDefaultDelay(10);
    timer->setInterval(100);
    timecount = 0;
    timer->start();
  }
}

void MainWindow::StartTimerGif() {
  if (gif_frame && timer) {
    QImage img = ui->openGLWidget->grabFramebuffer();
    QSize img_size(640, 480);
    QImage scaled_img = img.scaled(img_size);
    gif_frame->addFrame(scaled_img);
    const int MaxFrames = 50;
    if (timecount == MaxFrames) {
      timer->stop();
      gif_frame->save(filePat);
      QMessageBox::information(0, "/", "Gif animation saved successfully");
      delete gif_frame;
      gif_frame = nullptr;
      ui->gif->setEnabled(true);
    }
    timecount++;
  }
}
