/* 
 * Copyright 2016 Emaad Ahmed Manzoor
 * License: Apache License, Version 2.0
 * https://github.com/emaadmanzoor/sigmod16
 */
#ifndef SIGMOD16_GRAPH_H_
#define SIGMOD16_GRAPH_H_

#include <unordered_map>
#include <vector>

namespace std {

typedef pair<uint32_t,uint32_t> edge_t;
typedef unordered_map<uint32_t, vector<uint32_t>> graph_t; 

graph_t construct_graph(const vector<edge_t>& edges);
void    print_graph(const graph_t& g);
void    add_edge(graph_t& g, uint32_t u, uint32_t v);
void    delete_edge(graph_t& g, uint32_t u, uint32_t v);
int     shortest_path(const graph_t& g, uint32_t u, uint32_t v);

} // namespace std

#endif
