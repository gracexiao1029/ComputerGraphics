#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
	double l, r, t, b, u, v;
	l = -camera.width / 2;
	r = camera.width / 2;
	t = -camera.height / 2;
	b = camera.height / 2;
	u = l + (r - l) * (j + 0.5)/width;
	v = b + (t - b) * (i + 0.5)/height;

	ray.direction = -camera.d * camera.w + u * camera.u + v * camera.v;
    ray.origin = camera.e;
}