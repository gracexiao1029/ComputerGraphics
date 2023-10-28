// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
    vec3 ka, kd, n, v, l;
    vec3 ks = vec3(1, 1, 1);
    float p = 1000;
    float cloud = improved_perlin_noise(vec3(0, 6, 2) * (rotate_about_y(animation_seconds / 4) * vec4(sphere_fs_in, 1.0)).xyz);

    if (is_moon) {
        ka = vec3(0.05, 0.05, 0.05);
        kd = vec3(0.5, 0.45, 0.45);
    } else {
        if (bump_height(is_moon, sphere_fs_in) > 0.007) {
            ka = vec3(0.01, 0.05, 0.02);
            kd = vec3(0.1, 0.5, 0.2);
            ks = vec3(0.2, 0.2, 0.2);
            p = 300;
        } else if (bump_height(is_moon, sphere_fs_in) > -0.007 && bump_height(is_moon, sphere_fs_in) <= 0.007) {
            ka = vec3(0.02, 0.03, 0.04);
            kd = vec3(0.2, 0.3, 0.4);
            ks = vec3(0.2, 0.2, 0.2);
            p = 300;
        } else { // sea
            ka = vec3(0.02, 0.02, 0.08);
            kd = vec3(0.2, 0.2, 0.8);
        }
        kd = kd * (1 - cloud) + vec3(1, 1, 1) * cloud;
        ks = ks * (1 - improved_perlin_noise(vec3(5, 5, 5))) + vec3(1, 1, 1) * improved_perlin_noise(vec3(5, 5, 5));
    }
    
    vec3 T, B;
    tangent(normalize(sphere_fs_in), T, B);
    vec3 t = (bump_position(is_moon, sphere_fs_in + T * 0.0001) - bump_position(is_moon, sphere_fs_in)) / 0.0001;
    vec3 b = (bump_position(is_moon, sphere_fs_in + B * 0.0001) - bump_position(is_moon, sphere_fs_in)) / 0.0001;
    vec3 bump_normal = (transpose(inverse(view)) * transpose(inverse(model(is_moon, animation_seconds))) * vec4(normalize(cross(t, b)), 1.0)).xyz;

    vec4 light_d = view * vec4(4 * cos(M_PI * animation_seconds / 4), 2.5, 4 * sin(M_PI * animation_seconds / 4), 1);
    n = normalize(bump_normal);
    v = normalize(-view_pos_fs_in).xyz;
    l = normalize(light_d - view_pos_fs_in).xyz;

    color = blinn_phong(ka, kd, ks, p, n, v, l);
}
