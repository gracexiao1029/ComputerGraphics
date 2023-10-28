#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
    std::vector<Eigen::Triplet<double>> ijv;
    const int n = V.rows();
    for (int i = 0; i < n; i++) ijv.emplace_back(i, i, 1);
    Eigen::SparseMatrix<double> Q(n,n);
    Q.setFromTriplets(ijv.begin(), ijv.end());

    r.resize(E.rows());
    for (int i = 0; i < r.size(); i++) {
        r[i] = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
    }

    std::vector<Eigen::Triplet<double>> m_ijv;
    for (int i = 0; i < n; i++) {
        m_ijv.emplace_back(i, i, m[i]);
    }
    M.resize(n, n);
    M.setFromTriplets(m_ijv.begin(), m_ijv.end());
    
    signed_incidence_matrix_sparse(n, E, A);

    std::vector<Eigen::Triplet<double>> c_ijv;
    for (int i = 0; i < b.rows(); i++) {
        c_ijv.emplace_back(i, b[i], 1);
    }
    C.resize(b.size(), n);
    C.setFromTriplets(c_ijv.begin(), c_ijv.end());

    Q = k * A.transpose() * A + M / pow(delta_t, 2) + 1e10 * C.transpose() * C;
    prefactorization.compute(Q);
    return prefactorization.info() != Eigen::NumericalIssue;
}
