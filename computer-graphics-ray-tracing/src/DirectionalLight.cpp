#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
	Eigen::Vector3d toward_light_d = - this -> d;
	d = toward_light_d.normalized();
	max_t = std::numeric_limits<double>::infinity();
}

