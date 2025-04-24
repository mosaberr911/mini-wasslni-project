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
    map<string, vector<pair<string, float> > > adj;
    map<string, bool> vis;
    map<string,int>dis;
public:
    
    void traverseGraph();
    void bfs(const string& StartNode);
    void dfs(const string& StartNode);
    void addGraph();
    void displayGraph();
    void addCity(string cityName);
    void deleteCity(string cityName);
    void addEdge(string city1, string city2, float distance);
    void deleteEdge(string city1, string city2);
    bool containsCity(string cityName);
    void dijkstra(const string& start); // declaration
    Graph();
};
