#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
	Eigen::RowVector3d AB = b - a;
	Eigen::RowVector3d AC = c - a;
	Eigen::RowVector3d normal = AB.cross(AC);
	return normal / 2.0;
}
