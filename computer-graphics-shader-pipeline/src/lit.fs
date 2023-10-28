// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
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
// expects: PI, blinn_phong
void main()
{
    vec3 ka, kd, n, v, l;
    vec3 ks = vec3(1, 1, 1);
    float p = 1000;

    if (is_moon) {
        ka = vec3(0.05, 0.05, 0.05);
        kd = vec3(0.5, 0.45, 0.45);
    } else {
        ka = vec3(0.02, 0.02, 0.08);
        kd = vec3(0.2, 0.2, 0.8);
    }

    vec4 light_d = view * vec4(4 * cos(M_PI * animation_seconds / 4), 2.5, 4 * sin(M_PI * animation_seconds / 4), 1);
    n = normalize(normal_fs_in);
    v = normalize(-view_pos_fs_in).xyz;
    l = normalize(light_d - view_pos_fs_in).xyz;

    color = blinn_phong(ka, kd, ks, p, n, v, l);
}
