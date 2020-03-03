#include "image.h"
#include <iostream>
#include <numeric>
#include "io_tools.h"

namespace igg {

bool Image::FillFromPgm(const std::string& file_name) {
  io_tools::ImageData imageData = io_tools::ReadFromPgm(file_name);
  if (imageData.data.empty()) return false;
  rows_ = imageData.rows;
  cols_ = imageData.cols;
  max_val_ = imageData.max_val;
  data_ = imageData.data;
  return true;
}
void Image::WriteToPgm(const std::string& file_name) const {
  io_tools::ImageData imageData = {rows_, cols_, max_val_, data_};
  if (!io_tools::WriteToPgm(imageData, file_name))
    std::cout << "failled to write to the file " << std::endl;
}
void Image::DownScale(int scale) {
  int new_cols = cols_ / 2;
  int new_rows = rows_ / 2;

  std::vector<int> new_data;
  new_data.reserve((new_rows * new_cols));
  for (int i = 0; i < rows_; i += scale) {
    for (int j = 0; j < cols_; j += scale) {
      int index = rowMajor(i, j);
      new_data.emplace_back(data_[index]);
      std::cout << data_[index] << std::endl;
    }
  }
  rows_ = new_rows;
  cols_ = new_cols;
  data_ = new_data;
}
void Image::UpScale(int scale) {
  int new_rows = rows_ * scale;
  int new_cols = cols_ * scale;
  std::vector<int> new_data(new_rows * new_cols + 1, 0);

  for (int i = 0; i < rows_; ++i) {
    int row_jump = i * scale;
    for (int j = 0; j < cols_; ++j) {
      int col_jump = j * scale;
      for (int k = 0; k < scale; ++k) {
        for (int l = 0; l < scale; ++l) {
          int index = rowMajor(i, j);
          int new_index = (k + row_jump) * new_cols + col_jump + l;
          new_data[new_index] = data_[index];
        }
      }
    }
  }
  cols_ = new_cols;
  rows_ = new_rows;

  data_ = new_data;
}
std::vector<float> Image::ComputeHistogram(int bins) const {
  std::vector<float> histgoram(bins);
  std::vector<int> counter(max_val_ + 1);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      ++counter[data_[rowMajor(i, j)]];
    }
  }
  float interval = 255.0 / (float)bins;
  for (int i = 0; i < bins; ++i) {
    }

  return histgoram;
}
}  // namespace igg