#include "Graph.h"

Graph::Graph(){}

void Graph::Addgraph(int edges) {
	while (edges--) {
		cout << "Enter the name of cities then distance\n";
		string s1, s2;
		int w;
		cin >> s1 >> s2 >> w;
		graph[s1].push_back({ s2,w });
		graph[s2].push_back({ s1,w });
	}
}

void Graph::displaygraph() {
	auto it = graph.begin();
	while (it != graph.end()) {
		cout << it->first;
		for (auto t : it->second) {
			cout << " (" << t.first<<" : " << t.second << ")";
		}
		cout << endl;
		it++;

	}
}
