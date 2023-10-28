// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
    vec3 temp_t = normalize(cross(N, vec3(0, 0, 1)));
    if (temp_t == vec3(0)) {
      T = normalize(cross(N, vec3(0, 1, 0)));
    } else {
      T = normalize(cross(N, vec3(0, 0, 1)));
    }
    B = normalize(cross(N, T));
}
