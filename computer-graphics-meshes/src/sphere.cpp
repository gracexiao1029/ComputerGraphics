#include "sphere.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
    int num_V = (num_faces_u + 1) * (num_faces_v + 1);
    V.resize(num_V, 3);
    UV.resize(num_V, 2);
    NV.resize(num_V, 3);
    
    int count_V = 0;
    double x, y, z, u, v;
    for (int i = 0; i < num_faces_u + 1; i++) {
        u = (double)i / num_faces_u;
        double theta = u * 2.0 * M_PI;
        for (int j = 0; j < num_faces_v + 1; j++) {
            v = (double)j / num_faces_v;
            double phi = v * M_PI;
            x = -sin(phi) * cos(theta);
            y = -sin(phi) * sin(theta);
            z = -cos(phi);

            V.row(count_V) = Eigen::RowVector3d(x, y, z);
            UV.row(count_V) = Eigen::RowVector2d(u, v);
            NV.row(count_V) = Eigen::RowVector3d(x, y, z);
            count_V++;
        }
    }

    int num_F = num_faces_u * num_faces_v;
    F.resize(num_F, 4);
    UF.resize(num_F, 4);
    NF.resize(num_F, 4);

    int count_F = 0;
    int v1, v2, v3, v4;
    for (int i = 0; i < num_faces_u; i++) {
        for (int j = 0; j < num_faces_v; j++) {
            v1 = i * (num_faces_v + 1) + j;
            v2 = (i + 1) * (num_faces_v + 1) + j; 
            v3 = (i + 1) * (num_faces_v + 1) + (j + 1);
            v4 = i * (num_faces_v + 1) + (j + 1);

            F.row(count_F) = Eigen::RowVector4i(v1, v2, v3, v4);
            UF.row(count_F) = Eigen::RowVector4i(v1, v2, v3, v4);
            NF.row(count_F) = Eigen::RowVector4i(v1, v2, v3, v4);
            count_F++;
        }
    }
}
