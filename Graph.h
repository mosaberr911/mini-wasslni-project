#pragma once
#include<iostream>
#include<vector>
#include<map>
#include <unordered_map>
#include<set>
#include<string>
#include "bits/stdc++.h"
using namespace std;
struct User {
    string password;
    string role;
};

class Graph {
private:
    static const int N = 1e5+5;
    map<string, vector<pair<string, float> > > adj;
    map<string, bool> vis;
    map<string,int>dis;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<>> pq;
    unordered_map<string, string> parent;
public:
    void traverseGraph();//
    void bfs(const string& StartNode);//
    void dfs(const string& StartNode);//
    void addGraph();//
    void displayGraph();//
    void modify_distance(string,string);
    void addCity(string cityName);
    void deleteCity(string cityName);
    void addEdge(string city1, string city2, float distance);
    void deleteEdge(string city1, string city2);
    bool containsCity(string cityName);//
    string dijkstra(const string& start,const string& end); // declaration//
};
