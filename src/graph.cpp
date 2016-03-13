/*
 * Copyright 2016 Emaad Ahmed Manzoor
 * License: Apache License, Version 2.0
 * https://github.com/emaadmanzoor/sigmod16
 */
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

#include "graph.h"

namespace std {

graph_t construct_graph(const vector<edge_t>& edges) {
  graph_t g;
  for (const auto& e : edges) {
    g[e.first].push_back(e.second);
  }
  return g;
}

void print_graph(const graph_t& g) {
  for (auto kv : g) {
    cerr << kv.first << ": ";
    for (auto e : kv.second) {
      cerr << e << " ";
    }
    cerr << endl;
  }
}

void add_edge(graph_t& g, uint32_t u, uint32_t v) {
  g[u].push_back(v);
}

void delete_edge(graph_t& g, uint32_t u, uint32_t v) {
  auto it = g.find(u);
  
  // u does not exist
  if (it == g.end()) {
    return;
  }

  vector<uint32_t>& neighbors = it->second;
  neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                            [v](uint32_t n) {return n == v;}),
                  neighbors.end());
}

int shortest_path(const graph_t& g, const graph_t& g_r, uint32_t u, uint32_t v) {
  // check if u exists and has outgoing edges
  auto it = g.find(u);
  if (it == g.end() || (it->second).size() == 0)
    return -1;

  // check if v exists and has incoming edges
  it = g_r.find(v);
  if (it == g_r.end() || (it->second).size() == 0)
    return -1;

  // find shortest path distance from u to v with a bidi-BFS
  vector<uint32_t> f {u}; // forward fringe
  vector<uint32_t> r {v}; // reverse fringe
  unordered_map<uint32_t,bool> visited_f;
  unordered_map<uint32_t,bool> visited_r;
  visited_f[u] = true;
  visited_r[v] = true;

  int path_length_f = 0;
  int path_length_r = 0;
  while (f.size() > 0 && r.size() > 0) {
    if (f.size() <= r.size()) {
      // expand the forward fringe
      /*cout << "f: ";
      for (uint32_t i : f)
        cout << i << " ";
      cout << endl;*/
      path_length_f++;
      auto this_level = move(f); // f is now empty
      for (auto node : this_level) {
        if (g.find(node) == g.end())
          continue;
        for (auto neighbor : g.at(node)) {
          if (!visited_f[neighbor]) {
            f.push_back(neighbor);
            visited_f[neighbor] = true;
          }
          if (visited_r[neighbor]) {
            return path_length_f + path_length_r;
          }
        }
      }
    } else {
      /*cout << "r: ";
      for (uint32_t i : r)
        cout << i << " ";
      cout << endl;*/
      path_length_r++;
      auto this_level = move(r);
      for (auto node : this_level) {
        if (g_r.find(node) == g_r.end())
          continue;
        for (auto neighbor : g_r.at(node)) {
          if (!visited_r[neighbor]) {
            r.push_back(neighbor);
            visited_r[neighbor] = true;
          }
          if (visited_f[neighbor]) {
            return path_length_f + path_length_r;
          }
        }
      }
    }
  }

  return -1;
}

} // namespace std
