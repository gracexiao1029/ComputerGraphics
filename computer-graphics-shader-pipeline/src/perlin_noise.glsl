// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
	vec3 seed = floor(st);
	// corners
	vec3 c1 = seed;
	vec3 c2 = vec3(seed.x + 1, seed.y, seed.z);
	vec3 c3 = vec3(seed.x, seed.y + 1, seed.z);
	vec3 c4 = vec3(seed.x + 1, seed.y + 1, seed.z);
	vec3 c5 = vec3(seed.x, seed.y, seed.z + 1);
	vec3 c6 = vec3(seed.x + 1, seed.y, seed.z + 1);
	vec3 c7 = vec3(seed.x, seed.y + 1, seed.z + 1);
	vec3 c8 = vec3(seed.x + 1, seed.y + 1, seed.z + 1);

	// directions
	vec3 d1 = random_direction(c1);
	vec3 d2 = random_direction(c2);
	vec3 d3 = random_direction(c3);
	vec3 d4 = random_direction(c4);
	vec3 d5 = random_direction(c5);
	vec3 d6 = random_direction(c6);
	vec3 d7 = random_direction(c7);
	vec3 d8 = random_direction(c8);

	vec3 frac = fract(st);
	// fractions
	vec3 f1 = st - c1;
	vec3 f2 = st - c2;
	vec3 f3 = st - c3;
	vec3 f4 = st - c4;
	vec3 f5 = st - c5;
	vec3 f6 = st - c6;
	vec3 f7 = st - c7;
	vec3 f8 = st - c8;

	// mix across all three dimensions
	float mixed_x1 = mix(dot(d1, f1), dot(d2, f2), smooth_step(frac).x);
	float mixed_x2 = mix(dot(d3, f3), dot(d4, f4), smooth_step(frac).x);
	float mixed_x3 = mix(dot(d5, f5), dot(d6, f6), smooth_step(frac).x);
	float mixed_x4 = mix(dot(d7, f7), dot(d8, f8), smooth_step(frac).x);
	float mixed_y1 = mix(mixed_x1, mixed_x2, smooth_step(frac).y);
	float mixed_y2 = mix(mixed_x3, mixed_x4, smooth_step(frac).y);
	float mixed_z = mix(mixed_y1, mixed_y2, smooth_step(frac).z);

	return mixed_z / sqrt(3);
}

