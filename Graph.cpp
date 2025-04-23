#include "bits/stdc++.h"
using namespace std;
#include "Graph.h"
Graph::Graph(){
    for (int i = 0; i < N; ++i) {
        vis[i] = false;
        dis[i] = INT_MAX;
    }

}
void Graph :: dijkstra(int start){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,start});
    while (!pq.empty()){
        pair<int,int>p=pq.top();
        pq.pop();
        int node = p.second,cost = p.first ;
        if (vis[node])continue;
        vis[node] = 1;
        dis[node] = cost ;
        for(auto [a,b] : adj[node]){
            if (!vis[a]){
                pq.push({cost+b,a});
            }
        }
    }

}