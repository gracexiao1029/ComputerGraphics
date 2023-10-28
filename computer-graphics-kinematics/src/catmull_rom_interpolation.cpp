#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
    if (keyframes.empty()) {
        return Eigen::Vector3d(0, 0, 0);
    }

    // find the four points and key-times
    std::vector<Eigen::Vector3d> points(4);
    std::vector<double> key_times(4);
    double t_temp = std::fmod(t, keyframes.back().first);
    int n = 0;
    for (int i = 0; i < keyframes.size() - 1; i++) {
        if (t_temp >= keyframes[i].first && t_temp < keyframes[i + 1].first) {
            n = i;
        }
    }
    if (n - 1 < 0 && n + 2 >= keyframes.size()) { // reach upper-bound and lower-bound
        key_times[0] = keyframes[n].first;
        points[0] = keyframes[n].second;
        key_times[1] = keyframes[n].first;
        points[1] = keyframes[n].second;
        key_times[2] = keyframes[n + 1].first;
        points[2] = keyframes[n + 1].second;
        key_times[3] = keyframes[n + 1].first;
        points[3] = keyframes[n + 1].second;
    }
    else if (n - 1 < 0) { // reach lower-bound
        key_times[0] = keyframes[n].first;
        points[0] = keyframes[n].second;
        for (int i = 1; i < 4; i++) {
            key_times[i] = keyframes[n - 1 + i].first;
            points[i] = keyframes[n - 1 + i].second;
        }
    }
    else if (n + 2 >= keyframes.size()) { // reach upper-bound
        for (int i = 0; i < 3; i++) {
            key_times[i] = keyframes[n - 1 + i].first;
            points[i] = keyframes[n - 1 + i].second;
        }
        key_times[3] = keyframes[n + 1].first;
        points[3] = keyframes[n + 1].second;
    }
    else {
        for (int i = 0; i < 4; i++) {
            key_times[i] = keyframes[n - 1 + i].first;
            points[i] = keyframes[n - 1 + i].second;
        }
    } 

    Eigen::Vector3d m0 = (points[2] - points[0]) / (key_times[2] - key_times[0]);
    Eigen::Vector3d m1 = (points[3] - points[1]) / (key_times[3] - key_times[1]);
    double time = (t_temp - key_times[1]) / (key_times[2] - key_times[1]);

    return (2 * pow(time, 3) - 3 * pow(time, 2) + 1) * points[1] + (pow(time, 3) - 2 * pow(time, 2) + time) * m0 + \
        (-2 * pow(time, 3) + 3 * pow(time, 2)) * points[2] + (pow(time, 3) - pow(time, 2)) * m1;
}
