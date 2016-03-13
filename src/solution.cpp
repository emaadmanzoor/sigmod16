/* 
 * Copyright 2016 Emaad Ahmed Manzoor
 * License: Apache License, Version 2.0
 * https://github.com/emaadmanzoor/sigmod16
 */
#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "graph.h"
#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
  // For timing
  chrono::time_point<chrono::steady_clock> start;
  chrono::time_point<chrono::steady_clock> end;
  chrono::milliseconds diff;

  // Read input
  start = chrono::steady_clock::now();

  vector<edge_t> edges;
  vector<edge_t> edges_r;
  char line[BUFSZ];
  fgets(line, BUFSZ, stdin);
  while (strlen(line) != 2) { // break on "S\n"
    uint32_t u, v;
    sscanf(line, "%u %u", &u, &v);
    edges.push_back(make_pair(u, v));
    edges_r.push_back(make_pair(v, u));
    fgets(line, BUFSZ, stdin);
  }

  end = chrono::steady_clock::now();
  diff = chrono::duration_cast<chrono::milliseconds>(end - start);
  cerr << "Reading edges: " << static_cast<double>(diff.count()) << "ms" << endl;

#ifdef DEBUG
  for (auto e : edges) {
    cerr << e.first << " " << e.second << endl;
  }
#endif

  // Construct graph
  start = chrono::steady_clock::now();
  graph_t g = construct_graph(edges);
  graph_t g_r = construct_graph(edges_r);
  end = chrono::steady_clock::now();
  diff = chrono::duration_cast<chrono::milliseconds>(end - start);
  cerr << "Constructing graph: " <<
    static_cast<double>(diff.count()) << "ms" << endl;

#ifdef DEBUG
  print_graph(g);
#endif

  // Signify that we are ready for queries
  printf("R\n");
  fflush(stdout);

  // Iterate through all the queries/updates
  int batchnum = 1;
  while (fgets(line, BUFSZ, stdin) != NULL) {
    cerr << "Batch " << batchnum << endl;
    batchnum++;
    while (strlen(line) != 2) { // single batch, break on "F\n"
      char type;
      uint32_t u, v;
      sscanf(line, "%c %u %u", &type, &u, &v);

      switch (type) {
        case 'A': // add edge u-v
          add_edge(g, u, v);
          add_edge(g_r, v, u);
          break;
        case 'D': // delete edge u-v
          delete_edge(g, u, v);
          delete_edge(g_r, v, u);
          break;
        case 'Q': // shortest-path-distance from u to v
          printf("%d\n", shortest_path(g, g_r, u, v));
          break;
      }
      fflush(stdout);
      fgets(line, BUFSZ, stdin);
    } // end of batch
  } // end of all queries

  return 0;
}
