#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (width == 0 || height == 0){
    fprintf(stderr, "Cannot save an empty image\n");
    return false;
  }
  
  std::ofstream file;
  try {
    file.open(filename, std::ios::binary);
    if (file.fail()){
      throw("Cannot open file.");
    }

    if (num_channels == 3){
      file << "P6" << "\n";
      file << width << " " << height << "\n";
      file << 255 << "\n";
    }
    else{
      file << "P5" << "\n";
      file << width << " " << height << "\n";
      file << 255 << "\n";
    }

    for (int i = 0; i < width * height * num_channels; i++){
      file << data[i];
    }

    return true;
    
  } catch (const char *err) {
    fprintf(stderr, "%s\n", err);
    file.close();
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
