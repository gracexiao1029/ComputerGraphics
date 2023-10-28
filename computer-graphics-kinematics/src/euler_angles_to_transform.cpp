#include "euler_angles_to_transform.h"
#include <Eigen/Geometry> 
#include <igl/PI.h>

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
	// twist-bend-twist matrix
	Eigen::Matrix4d rotation_x1, rotation_z, rotation_x2;
	rotation_x1 << 1, 0, 0, 0,
		0, cos(xzx(0) / 180 * igl::PI), -sin(xzx(0) / 180 * igl::PI), 0,
		0, sin(xzx(0) / 180 * igl::PI), cos(xzx(0) / 180 * igl::PI), 0,
		0, 0, 0, 1;
	rotation_z << cos(xzx(1) / 180 * igl::PI), -sin(xzx(1) / 180 * igl::PI), 0, 0,
		sin(xzx(1) / 180 * igl::PI), cos(xzx(1) / 180 * igl::PI), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	rotation_x2 << 1, 0, 0, 0,
		0, cos(xzx(2) / 180 * igl::PI), sin(xzx(2) / 180 * igl::PI), 0,
		0, sin(xzx(2) / 180 * igl::PI), cos(xzx(2) / 180 * igl::PI), 0,
		0, 0, 0, 1;

	// construct rotation matrix
	Eigen::Affine3d m;
	/*m = Eigen::AngleAxisd(xzx(2) / 180 * igl::PI, Eigen::Vector3d::UnitZ())
		* Eigen::AngleAxisd(xzx(1) / 180 * igl::PI, Eigen::Vector3d::UnitY())
		* Eigen::AngleAxisd(xzx(0) / 180 * igl::PI, Eigen::Vector3d::UnitX());*/
	m = rotation_x2 * rotation_z * rotation_x1;
	return m;
}
