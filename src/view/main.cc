#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Parser parser;
  s21::AffineTransformation affine;
  s21::Controller controller(parser, affine);
  MainWindow w(nullptr, controller);
  w.show();
  return a.exec();
}
