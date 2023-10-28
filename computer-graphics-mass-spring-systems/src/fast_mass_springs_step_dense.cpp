#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
    Eigen::MatrixXd y = Eigen::MatrixXd::Zero(V.rows(), 3);
    y = M * (2 * Ucur - Uprev) / pow(delta_t, 2) + fext;
    Unext = Ucur;
    for (int iter = 0; iter < 50; iter++)
    {
        Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3);
        for (int j = 0; j < E.rows(); j++) {
            Eigen::MatrixXd e_next = Unext.row(E(j, 0)) - Unext.row(E(j, 1));
            d.row(j) = e_next / e_next.norm() * r[j];
        }
        const Eigen::MatrixXd l = k * A.transpose() * d + y + 1e10 * C.transpose() * C * V;
        Unext = prefactorization.solve(l);
    }
}
