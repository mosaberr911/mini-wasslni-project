#pragma once
#include<iostream>
#include<vector>
#include<map>
#include <unordered_map>
#include<set>
#include<string>
//#include "bits/stdc++.h"
using namespace std;

class Graph {
private:
    static const int N = 1e5+5;
    unordered_map<string, vector<pair<string, float> > > adj;
    unordered_map<string, bool> vis;
    unordered_map<string,int>dis;
    priority_queue<pair<float, string>, vector<pair<float, string> >, greater<pair<float, string> > > pq;
    unordered_map<string, string> parent;
public:
    void traverseGraph();//
    void bfs(const string& StartNode);//
    void dfs(const string& StartNode);//
    void addGraph();//
    void dfspaths(string current, string destination, vector<string>& path);
    void findallpaths(string , string );
    void read();
    void write();
    void displayGraph();
    void modify_distance(string,string);
    void addCity(string cityName);
    void deleteCity(string cityName);
    void addEdge(string city1, string city2, float distance);
    void deleteEdge(string city1, string city2);
    bool containsCity(string cityName);
    string dijkstra(const string& start,const string& end);
};
