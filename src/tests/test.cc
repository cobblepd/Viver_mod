
#include "../model/affinetransformation.h"
#include "../model/parser.h"
#include "gtest/gtest.h"

TEST(ParserTest, Parsing) {
  s21::Parser parser;
  int result = parser.ParsFile("obj/Cube.obj");
  EXPECT_EQ(result, 0);
  std::vector<float> vertices_test = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                      0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                      0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<double> edges_test = {1, 7, 5, 1, 3, 7, 1, 4, 3, 1,
                                    2, 4, 3, 8, 7, 3, 4, 8, 5, 7,
                                    8, 5, 8, 6, 1, 5, 6, 1, 6, 2};
  std::vector<float> vertices = parser.GetVertices();
  std::vector<unsigned int> edges = parser.GetEdges();
  EXPECT_EQ(vertices.size(), vertices_test.size());
  EXPECT_EQ(edges.size(), edges_test.size());
  for (unsigned int i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(vertices[i], vertices_test[i]);
  }
  for (unsigned int i = 0; i < edges.size(); i++) {
    EXPECT_EQ(edges[i] + 1, edges_test[i]);
  }
}

TEST(ParserTest, Empty) {
  s21::Parser parser;
  int result = parser.ParsFile("obj/aboba.obj");
  EXPECT_EQ(result, 1);
}

TEST(Affine, AffineTestMove) {
  s21::Parser parser;
  s21::AffineTransformation affine;
  int result = parser.ParsFile("obj/Cube.obj");
  EXPECT_EQ(result, 0);
  std::vector<float> vertices_test = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                      0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                      0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<double> edges_test = {1, 7, 5, 1, 3, 7, 1, 4, 3, 1,
                                    2, 4, 3, 8, 7, 3, 4, 8, 5, 7,
                                    8, 5, 8, 6, 1, 5, 6, 1, 6, 2};
  std::vector<float> vertices = parser.GetVertices();
  std::vector<unsigned int> edges = parser.GetEdges();
  affine.SetVertices(vertices);
  affine.MoveX(1);
  std::vector<float> vertices1 = affine.GetVertices();
  affine.SetVertices(vertices);
  affine.MoveY(1);
  std::vector<float> vertices2 = affine.GetVertices();
  affine.SetVertices(vertices);
  affine.MoveZ(1);
  std::vector<float> vertices3 = affine.GetVertices();
  EXPECT_EQ(vertices.size(), vertices_test.size());
  EXPECT_EQ(vertices1.size(), vertices_test.size());
  EXPECT_EQ(vertices2.size(), vertices_test.size());
  EXPECT_EQ(vertices3.size(), vertices_test.size());
  EXPECT_EQ(edges.size(), edges_test.size());

  for (unsigned int i = 0; i < vertices1.size(); i += 3) {
    EXPECT_NEAR(vertices1[i], vertices_test[i] + ((1.0 - 0.0) * 2.0 / 100.0),
                1e-6);
  }
  for (unsigned int i = 1; i < vertices2.size(); i += 3) {
    EXPECT_NEAR(vertices2[i], vertices_test[i] + ((1.0 - 0.0) * 2.0 / 100.0),
                1e-6);
  }
  for (unsigned int i = 2; i < vertices3.size(); i += 3) {
    EXPECT_NEAR(vertices3[i], vertices_test[i] + ((1.0 - 0.0) * 2.0 / 100.0),
                1e-6);
  }
  for (unsigned int i = 0; i < edges.size(); i++) {
    EXPECT_EQ(edges[i] + 1, edges_test[i]);
  }
}

TEST(Affine, AffineTestRotate) {
  s21::Parser parser;
  s21::AffineTransformation affine;
  int result = parser.ParsFile("obj/Cube.obj");
  EXPECT_EQ(result, 0);
  std::vector<float> vertices_test = {0,          0,           0,
                                      0.0355034,  -0.0342904,  1.99939,
                                      -0.0342904, 1.9994,      0.0348995,
                                      0.00121294, 1.96511,     2.03429,
                                      1.99939,    0.0348995,   -0.0349048,
                                      2.03489,    0.000609081, 1.96449,
                                      1.9651,     2.0343,      -5.31599e-06,
                                      2.0006,     2.00001,     1.99939};
  std::vector<double> edges_test = {1, 7, 5, 1, 3, 7, 1, 4, 3, 1,
                                    2, 4, 3, 8, 7, 3, 4, 8, 5, 7,
                                    8, 5, 8, 6, 1, 5, 6, 1, 6, 2};
  std::vector<float> vertices = parser.GetVertices();
  std::vector<unsigned int> edges = parser.GetEdges();
  affine.SetVertices(vertices);
  affine.RotateX(1);
  affine.RotateY(1);
  affine.RotateZ(1);
  std::vector<float> vertices1 = affine.GetVertices();
  EXPECT_EQ(vertices.size(), vertices_test.size());
  EXPECT_EQ(vertices1.size(), vertices_test.size());
  EXPECT_EQ(edges.size(), edges_test.size());

  for (unsigned int i = 0; i < vertices1.size(); i++) {
    EXPECT_NEAR(vertices1[i], vertices_test[i], 1e-5);
  }
  for (unsigned int i = 0; i < edges.size(); i++) {
    EXPECT_EQ(edges[i] + 1, edges_test[i]);
  }
}

TEST(Affine, AffineTestScale) {
  s21::Parser parser;
  s21::AffineTransformation affine;
  int result = parser.ParsFile("obj/Cube.obj");
  EXPECT_EQ(result, 0);
  std::vector<float> vertices_test = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                      0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                      0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<double> edges_test = {1, 7, 5, 1, 3, 7, 1, 4, 3, 1,
                                    2, 4, 3, 8, 7, 3, 4, 8, 5, 7,
                                    8, 5, 8, 6, 1, 5, 6, 1, 6, 2};
  std::vector<float> vertices = parser.GetVertices();
  std::vector<unsigned int> edges = parser.GetEdges();
  affine.SetVertices(vertices);
  affine.Scale(1);
  std::vector<float> vertices1 = affine.GetVertices();
  EXPECT_EQ(vertices.size(), vertices_test.size());
  EXPECT_EQ(vertices1.size(), vertices_test.size());
  EXPECT_EQ(edges.size(), edges_test.size());
  for (unsigned int i = 0; i < vertices1.size(); i++) {
    EXPECT_NEAR(vertices1[i], vertices_test[i] * 1 / 50, 1e-5);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
