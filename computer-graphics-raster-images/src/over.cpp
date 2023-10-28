#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int src = 0, dst = 0, compos = 0;
  for (int x = 0; x < height; x++){
    for (int y = 0; y < width; y++){
      double src_r = (double)A[src++];
      double src_g = (double)A[src++];
      double src_b = (double)A[src++];
      double src_a = (double)A[src++] / 255.0;
      
      double dst_r = (double)B[dst++];
      double dst_g = (double)B[dst++];
      double dst_b = (double)B[dst++];
      double dst_a = (double)B[dst++] / 255.0;

      double a = src_a + dst_a * (1.0 - src_a);
      double r = ((src_a * src_r) + (1.0 - src_a) * dst_a * dst_r) / a;
      double g = ((src_a * src_g) + (1.0 - src_a) * dst_a * dst_g) / a;
      double b = ((src_a * src_b) + (1.0 - src_a) * dst_a * dst_b) / a;

      C[compos++] = (unsigned char)(r);
      C[compos++] = (unsigned char)(g);
      C[compos++] = (unsigned char)(b);
      C[compos++] = (unsigned char)(a * 255.0);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
