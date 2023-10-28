// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
	vec2 rand_vec = random2(seed);
	float x, y, z, theta, phi;

	theta = 2 * M_PI * rand_vec.x;
	phi = 2 * M_PI * rand_vec.y;
	x = cos(theta) * sin(phi);
	y = sin(theta) * sin(phi);
	z = cos(phi);

	return normalize(vec3(x, y, z));
}
