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

int shortest_path(const graph_t& g, uint32_t u, uint32_t v) {
  // check if u exists and has outgoing edges
  auto it = g.find(u);
  if (it == g.end() || (it->second).size() == 0)
    return -1;

  // find shortest path distance from u to v with a DFS
  stack<uint32_t> s;
  unordered_map<uint32_t,uint32_t> d;
  s.push(u);
  d[u] = 0;
  while (!s.empty()) {
    uint32_t m = s.top();
    s.pop();

    if (m == v) {
      break;
    }

    it = g.find(m);
    if (it == g.end()) {
      continue;
    }

    for (auto n : g.at(m)) {
      uint32_t d1 = d[m];
      
      auto d_n = d.find(n);
      uint32_t d2;
      if (d_n == d.end())
        d2 = numeric_limits<uint32_t>::max();
      else
        d2 = d_n->second;
      
      if (d1 + 1 < d2) {
        d[n] = d1 + 1;
        s.push(n);
      }
    }
  }

  auto d_v = d.find(v);
  if (d_v == d.end())
    return -1;
  return d_v->second;
}

} // namespace std
