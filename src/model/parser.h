#ifndef S21_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_
#define S21_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  Parser();
  ~Parser() = default;
  int ParsFile(const std::string file_path);
  std::vector<float>& GetVertices();
  std::vector<unsigned int>& GetEdges();
  float* GetMinMax();

 private:
  void ProcessingVertices(std::ifstream& file);
  void ProcessingIndexes(std::ifstream& file);
  std::vector<float> vertices_;
  std::vector<unsigned int> edges_;
  std::istringstream expression_;
  float min_max_[6];
  bool error_;
};
}  // namespace s21

#endif  // S21_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_
