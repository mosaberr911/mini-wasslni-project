#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
using namespace std;

class Graph {
private:
    static const int N = 1e5+5;
    map<string, vector<pair<string, int> > > adj;
    map<string, bool> vis;
    map<string,int>dis;
public:
    
    void traverse_graph();
    void BFS(const string& StartNode);
    void DFS(const string& StartNode);
    void Addgraph(int);
    void addCity(string cityName);
    void deleteCity(string cityName);
    bool containsCity(string cityName);
    void dijkstra(const string& start); // declaration
    Graph();
};
