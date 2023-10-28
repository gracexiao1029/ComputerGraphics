// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
    float heavi, x, t, noise;
    if (is_moon) {
        x = improved_perlin_noise(s);
        t = 60;
        heavi = 0.1 * smooth_heaviside(x, t);
    } else {
        x = improved_perlin_noise(s * 2);
        t = 50;
        heavi = 0.01 * smooth_heaviside(x, t);
    }
    
    return heavi;
}
