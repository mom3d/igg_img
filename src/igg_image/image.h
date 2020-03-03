#pragma once

#include <string>
#include <vector>
namespace igg {

class Image {
 public:
  ///////////////////// Create the public interface here ///////////////////////
  Image() {}
  Image(int rows, int cols) : rows_(rows), cols_(cols) {
    data_.reserve(rows_ * cols_ + 1);
  }
  // Getters
  int rows() const { return rows_; }
  int cols() const { return cols_; }
  const int& at(int row, int col) const {
    int index = rowMajor(row, col);
    return data_[index];
  }
  int& at(int row, int col) {
    int index = rowMajor(row, col);
    return data_[index];
  }
  bool FillFromPgm(const std::string& file_name);
  void WriteToPgm(const std::string& file_name) const;
  void DownScale(int scale);
  void UpScale(int scale);
  std::vector<float> ComputeHistogram(int bins) const;

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
  int rowMajor(int row, int col) const { return row * cols_ + col; }
};

}  // namespace igg
