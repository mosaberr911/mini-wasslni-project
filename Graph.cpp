#include "bits/stdc++.h"
#include "Graph.h"
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<queue>
using namespace std;
Graph::Graph(){
    for(auto [city,visit]:vis){
        vis[city] = false;
        dis[city] = INT_MAX;
    }
}
void Graph::dijkstra(const string& start) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});
    dis[start] = 0;

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();
        if (vis[node]) continue;
        vis[node] = true;

        for (auto &[neighbor, weight] : adj[node]) {
            if (!vis[neighbor] && dis[node] + weight < dis[neighbor]) {
                dis[neighbor] = dis[node] + weight;
                pq.push({dis[neighbor], neighbor});
            }
        }
    }

    for (auto& [city, distance] : dis) {
        cout << "Distance from " << start << " to " << city << " is: ";
        if (distance == INT_MAX) cout << "INF" << endl;
        else cout << distance << endl;
    }
}

void Graph::traverseGraph() {
    int selection;
    bool x = true;
    cout << "Enter your selection\n";
    cout << "1 - BFS\n";
    cout << "2 - DFS\n";
    while (x) {
        cin >> selection;
        string node;
        cout << "Enter start node: ";
        cin >> node;
        if (selection == 1) {
            bfs(node);
            x = false;
        }
        else if (selection == 2) {
            dfs(node);
            x = false;
        }
        else {
            cout << "Invalid selection. Please select again.\n";
        }
    }
}

void Graph::dfs( const string& startNode) {
	vis[startNode]=1;
	for (auto [child, weight] : adj[startNode]) {
		if (!vis[child])
		{
            cout << child;
			dfs(child);
            vis[child]=1;
		}
	}
}
void Graph::bfs(const string& startNode) {
    queue<string> q;
    vis.clear();
    q.push(startNode);
    vis[startNode] = true;

    while (!q.empty()) {
        string node = q.front();
        q.pop();
        cout << node << " ";
        for (auto [child, weight] : adj[node]) {
            if (!vis[child]) {
                vis[child] = true;
                q.push(child);
            }
        }
    }
    cout << endl;
}
void Graph::addGraph() {
	char ch;
	do {
		string s1, s2;
		int d;
		cout << "Enter the name of cities then the distance\n";
		cin >> s1 >> s2 >> d;
		adj[s1].push_back({ s2,d });
		adj[s2].push_back({ s1,d });
		cout << "if you want to add more enter y";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void Graph::displayGraph() {
	auto it = adj.begin();
	while (it != adj.end()) {
		cout << it->first << " ";
		for (auto t : it->second) {
			cout << "(" << t.first << ":" << t.second << ")";
		}
		cout << endl;
		it++;
	}
}

void Graph::addCity(string cityName) {
    // check if city already exists in graph
    if (containsCity(cityName))
        throw runtime_error("City already exists in graph");
    adj[cityName];
}

void Graph::deleteCity(string cityName) {
    // check if city does not exist in graph
    if (!containsCity(cityName))
        throw runtime_error("City does not exists in graph");
    // loop through adjacency list to find neighbors
    for (auto& cityPair : adj) {
        // assign "neighbour" to the city name
        string neighbour = cityPair.first;

        // check if city is not the one to be deleted
        if (neighbour != cityName) {
            // assign "neighborCities" to neighbors vector
            auto &neighborCities = cityPair.second;
            // loop through neighbors vector of the neighbour city
            for (auto it = neighborCities.begin(); it != neighborCities.end();) {
                // delete removed city from neighbor vector of the neighbour city
                if (it->first == cityName)
                    it = neighborCities.erase(it);
                // increment iterator
                else
                    it++;
            }
        }
    }
    // remove city from adjacency list
    adj.erase(cityName);
}

void Graph::addEdge(string city1, string city2, float distance) 
{

    if (!containsCity(city1) || !containsCity(city2)) {
        throw runtime_error("One or both cities do not exist.");
    }//throw exeption if the either one of the cities doesn't exist

    for (const auto& neighbor : adj[city1]) {
        if (neighbor.first == city2) {
            throw runtime_error("this edge already exists in graph");
        }
    }//check if the edge already exists

    adj[city1].push_back({ city2 ,distance });
    adj[city2].push_back({ city1 ,distance });
}

void Graph::deleteEdge(string city1, string city2) {
    if (!containsCity(city1) || !containsCity(city2)) {
        throw runtime_error("One or both cities do not exist.");
    }//throw exeption if the either one of the cities doesn't exist

    auto& neighbors1 = adj[city1];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); it++) {
        if (it->first == city2) {
            it = neighbors1.erase(it);
            break;
        }
    }//removing 2nd city from 1st city adjacency matrix

    auto& neighbors2 = adj[city2];
    for (auto it = neighbors2.begin(); it != neighbors2.end(); ) {
        if (it->first == city1) {
            it = neighbors2.erase(it);
            break;
        }
    }//removing 1st city from 2nd city adjacency matrix
}

bool Graph::containsCity(string cityName) {
    return adj.find(cityName) != adj.end();
}