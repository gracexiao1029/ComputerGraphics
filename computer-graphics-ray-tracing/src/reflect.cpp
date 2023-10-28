#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
	// out = in - 2(in.n)n
	Eigen::Vector3d out = in - 2 * (in.dot(n)) * n;
	return out.normalized();
}
