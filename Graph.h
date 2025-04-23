#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
using namespace std;

class Graph {
private:
    map<string, vector<pair<string, int>>> adj;
   map<string, bool> vis;
public:
    
    void traverse_graph();
    void BFS(const string& StartNode);
    void DFS(const string& StartNode);
    void Addgraph(int);
};
