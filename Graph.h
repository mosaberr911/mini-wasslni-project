
#ifndef MINI_WASSLNI_PROJECT_GRAPH_H
#define MINI_WASSLNI_PROJECT_GRAPH_H

#include "bits/stdc++.h"
class Graph {
private:
    static const int N = 1e5 + 5;
    bool vis[N];
    int dis[N];
    std::vector<std::pair<int, int>> adj[N];
public:
    void dijkstra(int node); // declaration
    Graph();
};


#endif
