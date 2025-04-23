#include "Graph.h"
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<queue>
using namespace std;
void Graph::traverse_graph() {
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
            BFS(node);
            x = false;
        }
        else if (selection == 2) {
            DFS(node);
            x = false;
        }
        else {
            cout << "Invalid selection. Please select again.\n";
        }
    }
}
void Graph::DFS( const string& startNode) {

  
	vis[startNode]=1;
	for (auto [child, weight] : adj[startNode]) {
		if (!vis[child])
		{
            cout << child;
			DFS(child);
            vis[child]=1;
		}
	}
}
void Graph::BFS(const string& startNode) {
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
void Graph::Addgraph(int edges) {
    while (edges--) {
        cout << "Enter the name of cities then distance\n";
        string s1, s2;
        int w;
        cin >> s1 >> s2 >> w;
        adj[s1].push_back({ s2,w });
        adj[s2].push_back({ s1,w });
    }
}

