#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
    // reference: https://web.cse.ohio-state.edu/~dey.8/course/784/note20.pdf

    // return if apply 0 iteration
    if (num_iters == 0) {
        return;
    }

    // compute new face points
    // v_F = Sum(i=1 to i=n)[v_i/n]
    std::unordered_map<int, Eigen::RowVector3d> new_face_points;
    std::unordered_map<int, std::vector<int>> adj_faces;
    for (int i = 0; i < F.rows(); i++) {
        Eigen::RowVector3d total_vertices(0, 0, 0);
        double num_vertices = 0.0;
        for (int j = 0; j < F.cols(); j++) {
            total_vertices += V.row(F(i, j));
            num_vertices++;
            adj_faces[F(i, j)].push_back(i);
        }
        new_face_points[i] = total_vertices / num_vertices;
    }
    
    // edge index corresponds to its endpoints in pairs
    std::vector<std::pair<int, int>> edge_vertices;
    // edge index corresponds to its adjacent faces in pairs
    std::vector<std::pair<int, int>> edge_adj_faces;
    // for each face, identify it's vertices and link each pair of adjacent vertices as an edge
    for (int i = 0; i < F.rows(); i++) {
        for (int j = 0; j < F.cols(); j++) {
            int v1 = F(i, j);
            int v2;
            if (j == F.cols() - 1) { // case 1: F[1, 2, 3] v1=3, v2=1
                v2 = F(i, 0);
            } else { // case 2: F[1, 2, 3] v1=1, v2=2 or v1=2, v2=3
                v2 = F(i, j + 1);
            }
            std::pair<int, int> vertex_pair = std::make_pair(v1, v2);
            std::pair<int, int> reverse_vertex_pair = std::make_pair(v2, v1);

            // pair is found
            bool pair_is_found = std::find(edge_vertices.begin(), edge_vertices.end(), vertex_pair) != edge_vertices.end() || 
                std::find(edge_vertices.begin(), edge_vertices.end(), reverse_vertex_pair) != edge_vertices.end();
            int edge_index = std::find(edge_vertices.begin(), edge_vertices.end(), vertex_pair) - edge_vertices.begin();
            int reverse_edge_index = std::find(edge_vertices.begin(), edge_vertices.end(), reverse_vertex_pair) - edge_vertices.begin();

            if (!pair_is_found) { // if vertex pair not in edge_vertices, push it in the array
                edge_vertices.push_back(vertex_pair);
                // no adjacent faces assigned to the edge
                edge_adj_faces.push_back(std::make_pair(i, -1));
            } else if (std::find(edge_vertices.begin(), edge_vertices.end(), vertex_pair) != edge_vertices.end()) { // one face exists
                edge_adj_faces[edge_index] = std::make_pair(edge_adj_faces[edge_index].first, i);
            } else if (std::find(edge_vertices.begin(), edge_vertices.end(), reverse_vertex_pair) != edge_vertices.end()) {
                edge_adj_faces[reverse_edge_index] = std::make_pair(edge_adj_faces[reverse_edge_index].first, i);
            }
        }
    }

    // compute new edge points: the average of points edge endpoints v and w, face points v_F1 and v_F2 of adjacent faces.
    // v_E = (v + w + v_F1 + v_F2) / 4
    std::unordered_map<int, Eigen::RowVector3d> new_edge_points;
    // for each edge, find the new edge point
    for (int i = 0; i < edge_vertices.size(); i++) {
        Eigen::RowVector3d v = V.row(edge_vertices[i].first);
        Eigen::RowVector3d w = V.row(edge_vertices[i].second);
        Eigen::RowVector3d v_F1 = new_face_points[edge_adj_faces[i].first];
        Eigen::RowVector3d v_F2 = new_face_points[edge_adj_faces[i].second];

        new_edge_points[i] = (v + w + v_F1 + v_F2) / 4.0;
    }

    // compute new vertex point
    // v' = (1/n)Q + (2/n)R + [(n-3)/n]v
    std::vector<Eigen::RowVector3d> new_vertex_points;
    new_vertex_points.reserve(V.rows());
    for (int i = 0; i < V.rows(); i++) {
        Eigen::RowVector3d new_vertex_point;
        double n = adj_faces[i].size();
        // compute Q: average of all face points adjacent to the vertex
        Eigen::RowVector3d total_face_points(0, 0, 0);
        for (int j = 0; j < adj_faces[i].size(); j++) {
            total_face_points += new_face_points[adj_faces[i][j]];
        }
        Eigen::RowVector3d Q = total_face_points / n;
        //compute R: average of all midpoints of edges incident with the vertex
        Eigen::RowVector3d total_midpoints(0, 0, 0);
        for (int k = 0; k < edge_vertices.size(); k++) {
            if (edge_vertices[k].first == i || edge_vertices[k].second == i) {
                total_midpoints += (V.row(edge_vertices[k].first) + V.row(edge_vertices[k].second)) / 2.0;
            }
        }
        Eigen::RowVector3d R = total_midpoints / n;

        new_vertex_point = Q / n + 2 * R / n + (n - 3) * V.row(i) / n;
        new_vertex_points.push_back(new_vertex_point);
    }

    // build new SV and SF
    SV.resize(V.rows() + F.rows() + edge_vertices.size(), 3);
    SF.resize(F.rows() * F.cols(), 4);
    // SV
    for (int i = 0; i < V.rows(); i++) {
        SV.row(i) = new_vertex_points[i];
    }
    int face_i = 0;
    for (int i = V.rows(); i < V.rows() + F.rows(); i++) {
        SV.row(i) = new_face_points[face_i];
        face_i++;
    }
    int edge_i = 0;
    for (int i = V.rows() + F.rows(); i < V.rows() + F.rows() + edge_vertices.size(); i++) {
        SV.row(i) = new_edge_points[edge_i];
        edge_i++;
    }

    // SF
    int face_num = 0;
    for (int i = 0; i < F.rows(); i++) {
        for (int j = 0; j < F.cols(); j++) {
            Eigen::RowVector4i new_face(0, 0, 0, 0);

            int v_1 = F(i, j);
            int v_2, v_3;
            if (j == F.cols() - 1) { // case 1: F[1, 2, 3] v1=3, v2=1
                v_2 = F(i, 0);
            } else { // case 2: F[1, 2, 3] v1=1, v2=2 or v1=2, v2=3
                v_2 = F(i, j + 1);
            }
            if (j == 0) { // case 1: F[1, 2, 3] v1=1, v3=3
                v_3 = F(i, F.cols() - 1);
            } else { // case 2: F[1, 2, 3] v1=2, v3=1 or v1=3, v3=2
                v_3 = F(i, j - 1);
            }

            std::pair<int, int> first_pair = std::make_pair(v_1, v_2);
            std::pair<int, int> reverse_first_pair = std::make_pair(v_2, v_1);
            std::pair<int, int> second_pair = std::make_pair(v_1, v_3);
            std::pair<int, int> reverse_second_pair = std::make_pair(v_3, v_1);

            int first_index = 0;
            int second_index = 0;
            for (int k = 0; k < edge_vertices.size(); k++) {
                bool edge_is_found = edge_vertices[k] == first_pair || edge_vertices[k] == reverse_first_pair;
                bool reverse_edge_is_found = edge_vertices[k] == second_pair || edge_vertices[k] == reverse_second_pair;
                if (edge_is_found) {
                    first_index = k;
                }
                if (reverse_edge_is_found) {
                    second_index = k;
                }
            }

            // construct the new face
            new_face[0] = F(i, j);
            new_face[1] = V.rows() + F.rows() + first_index;
            new_face[2] = V.rows() + i;
            new_face[3] = V.rows() + F.rows() + second_index;

            SF.row(face_num) = new_face;
            face_num++;
        }
    }

    // recursive step
    catmull_clark(SV, SF, num_iters - 1, SV, SF);
}