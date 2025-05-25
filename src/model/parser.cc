#include "parser.h"

namespace s21 {
Parser::Parser() {
  for (int i = 0; i < 6; ++i) {
    min_max_[i] = 0;
  }
}
int Parser::ParsFile(const std::string file_path) {
  vertices_.clear();
  edges_.clear();
  std::ifstream file(file_path);
  if (!file.is_open()) {
    error_ = true;
    return 1;
  }
  std::string ch;
  while (file >> ch) {
    if (ch == "v") {
      ProcessingVertices(file);
    }
    if (ch == "f") {
      ProcessingIndexes(file);
    }
  }
  return 0;
}

void Parser::ProcessingVertices(std::ifstream& file) {
  float x, y, z;
  if (file >> x >> y >> z) {
    if (vertices_.empty()) {
      min_max_[0] = x;
      min_max_[1] = x;
      min_max_[2] = y;
      min_max_[3] = y;
      min_max_[4] = z;
      min_max_[5] = z;
    } else {
      min_max_[0] = std::min(min_max_[0], x);
      min_max_[1] = std::max(min_max_[1], x);
      min_max_[2] = std::min(min_max_[2], y);
      min_max_[3] = std::max(min_max_[3], y);
      min_max_[4] = std::min(min_max_[4], z);
      min_max_[5] = std::max(min_max_[5], z);
    }
    vertices_.push_back(x);
    vertices_.push_back(y);
    vertices_.push_back(z);
  }
}

void Parser::ProcessingIndexes(std::ifstream& file) {
  std::string line;
  getline(file, line);
  std::string token;
  line.erase(line.begin());
  expression_.str(line);
  while (expression_ >> token) {
    int value = std::stoul(token.c_str());
    if (value < 0) {
      value = vertices_.size() / 3.0 + value + 1;
    }
    value -= 1;
    edges_.push_back(value);
  }
  expression_.clear();
}

std::vector<float>& Parser::GetVertices() { return vertices_; }
std::vector<unsigned int>& Parser::GetEdges() { return edges_; }
float* Parser::GetMinMax() { return min_max_; }
}  // namespace s21
