#ifndef STORY_IN_ALGORITHMS_RANDOM_CONTRACTION_H_
#define STORY_IN_ALGORITHMS_RANDOM_CONTRACTION_H_

#include <algorithm>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>

namespace algos {

struct Edge {
    int begin;
    int end;
    int weight;

    void ReplaceVertices(int old_v, int new_v) {
        begin = begin == old_v ? new_v : begin;
        end = end == old_v ? new_v : end;
    }
};

using AdjacencyList = std::unordered_map<int, std::list<Edge>>;

void PrintAdjecencyList_(const AdjacencyList &l) {
    for (const auto &adj_pair : l) {
        std::cout << "Vertex: " << adj_pair.first << "\n";
        for (const auto &vertex : adj_pair.second) {
            std::cout << "\t{" << vertex.begin << ", " << vertex.end << ", " << vertex.weight << "}\n";
        }
    }
}

void Contraction_(AdjacencyList &adj_list, int src_vertex, int dst_vertex) {
    auto &dst_list = adj_list[dst_vertex];
    auto &src_list = adj_list[src_vertex];
    auto rm_iter = std::remove_if(dst_list.begin(), dst_list.end(), [=](const Edge &edge) {
        return edge.begin == src_vertex || edge.end == src_vertex;
    });
    dst_list.erase(rm_iter, dst_list.end());
    rm_iter = std::remove_if(src_list.begin(), src_list.end(), [=](const Edge &edge) {
        return edge.begin == dst_vertex || edge.end == dst_vertex;
    });
    src_list.erase(rm_iter, src_list.end());
    std::copy(src_list.begin(), src_list.end(), std::back_inserter(dst_list));
    for (auto &adj_pair : adj_list) {
        for (Edge &edge : adj_pair.second) {
            edge.ReplaceVertices(src_vertex, dst_vertex);
        }
    }
}

AdjacencyList RandomContraction(const AdjacencyList &adj_list) {
    AdjacencyList new_adj_list = adj_list;
    std::vector<Edge> edges;
    for (const auto &adj_pair : new_adj_list) {
        std::copy(adj_pair.second.begin(), adj_pair.second.end(), std::back_inserter(edges));
    }
    while (edges.size() != 0 && new_adj_list.size() > 2) {
        int random_edge_n = std::rand() % edges.size();
        auto random_edge = edges[random_edge_n];
        int src_vertex = random_edge.begin;
        int dst_vertex = random_edge.end;
        edges.erase(edges.begin() + random_edge_n);
        Contraction_(new_adj_list, src_vertex, dst_vertex);
        new_adj_list.erase(src_vertex);
    }
    return new_adj_list;
}

}  // namespace algos

#endif  // STORY_IN_ALGORITHMS_RANDOM_CONTRACTION_H_