#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

class Graph
{
	map<string, vector<pair<string, int>>> graph;
public:
	public:
	Graph();
	void Addgraph(int);
	void displaygraph();
};

