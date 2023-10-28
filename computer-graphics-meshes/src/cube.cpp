#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
    V.resize(8, 3);
    V << 0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1,
        1, 1, 1,
        0, 1, 1,
        1, 1, 0,
        0, 1, 0;

    F.resize(6, 4);
    F << 0, 1, 2, 3, // blue
        0, 3, 5, 7, // green
        2, 4, 5, 3, // yellow
        0, 7, 6, 1, // white
        1, 6, 4, 2, // orange
        4, 6, 7, 5; // red
        
        

    UV.resize(14, 2);
    UV << 0, 1,
        0, 2,
        1, 0,
        1, 1,
        1, 2,
        1, 3,
        2, 0,
        2, 1,
        2, 2,
        2, 3,
        3, 1,
        3, 2,
        4, 1,
        4, 2;
    for (int i = 0; i < UV.rows(); i++) {
        UV.row(i) = UV.row(i) * 0.25;
    }

    UF.resize(6, 4);
    UF << 7, 10, 11, 8, // blue
        3, 7, 8, 4, // green
        4, 8, 9, 5, // yellow
        2, 6, 7, 3, // white
        10, 12, 13, 11, // orange
        0, 3, 4, 1; // red
        
        
    NV.resize(6, 3);
    NV << 0, -1, 0, // b
        -1, 0, 0, // g
        0, 0, 1, // y
        0, 0, -1, // w
        1, 0, 0, // o
        0, 1, 0; // r
        

    NF.resize(6, 4);
    NF << 0, 0, 0, 0,
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4,
        5, 5, 5, 5;
}
