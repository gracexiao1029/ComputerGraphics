#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
	Eigen::Vector3d light_vector = p - q;
	d = light_vector.normalized();
	max_t = light_vector.norm();
}
