#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");

  std::ofstream file;
  file.open(filename, std::ios::binary);
  if (!file) {
      std::cout << "Can't open file";
      return false;
  }

  for (int i = 0; i < V.rows(); i++) {
      file << "v " << V.row(i)[0] << " " << V.row(i)[1] << " " << V.row(i)[2] << "\n";
  }
  for (int i = 0; i < UV.rows(); i++) {
      file << "vt " << UV.row(i)[0] << " " << UV.row(i)[1] << "\n";
  }
  for (int i = 0; i < NV.rows(); i++) {
      file << "vn " << NV.row(i)[0] << " " << NV.row(i)[1] << " " << NV.row(i)[2] << "\n";
  }
  for (int i = 0; i < F.rows(); i++) {
      file << "f ";
      for (int j = 0; j < F.cols(); j++) {
          file << F.row(i)[j] + 1 << "/" << UF.row(i)[j] + 1 << "/" << NF.row(i)[j] + 1 << " ";
      }
      file << "\n";
  }
  file.close();
  return true;
}
