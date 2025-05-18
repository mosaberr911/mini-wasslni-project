#include "Graph.h"
#include <stdexcept>
#include <limits>
#include <queue>
#include <vector>
#include <QString>
#include <string>
#include <algorithm>
#include <sstream>
#include <QTextEdit>
#include <iostream>
#include <regex>

using namespace std;

Graph::Graph() : adj({}) {}

void Graph::addCity(const string& cityName) {
    if (containsCity(cityName))
        throw invalid_argument("City already exists: " + cityName);
    adj[cityName];
}

void Graph::addEdge(const string& start, const string& end, float distance) {
    if (start == end)
        throw invalid_argument("Cannot add an edge between a city and itself");

    if (distance <= 0)
        throw invalid_argument("Invalid distance value");

    if (containsEdge(start, end))
        throw invalid_argument("Road already exists between those cities");

    adj[start].push_back({end, distance});
    adj[end].push_back({start, distance});
}

bool Graph::containsCity(const string& cityName) {
    return adj.find(cityName) != adj.end();
}

void Graph::deleteEdge(const string& start, const string& end) {
    if (!containsCity(start) || !containsCity(end))
        throw invalid_argument("One or both of the cities does not exist");

    if (!containsEdge(start, end))
        throw invalid_argument("Road does not exist between those cities");

    auto& neighbors1 = adj[start];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); ++it) {
        if (it->first == end) {
            neighbors1.erase(it);
            break;
        }
    }

    auto& neighbors2 = adj[end];
    for (auto it = neighbors2.begin(); it != neighbors2.end(); ++it) {
        if (it->first == start) {
            neighbors2.erase(it);
            break;
        }
    }
}

bool Graph::containsEdge(const string& start, const string& end) {
    bool edgeExists = false;
    for (const auto& neighbor : adj[start]) {
        if (neighbor.first == end) {
            edgeExists = true;
            break;
        }
    }
    return edgeExists;
}

void Graph::deleteCity(const string& cityName) {
    if (!containsCity(cityName))
        throw invalid_argument("City does not exist in graph");

    for (auto& cityPair : adj) {
        string neighbour = cityPair.first;

        if (neighbour != cityName) {
            auto &neighborCities = cityPair.second;

            for (auto it = neighborCities.begin(); it != neighborCities.end();) {
                if (it->first == cityName)
                    it = neighborCities.erase(it);
                else
                    it++;
            }
        }
    }
    adj.erase(cityName);
}

void Graph::addGraphFromUI(const QVector<tuple<QString, QString, float>>& edges) {
    for (const auto& edge : edges) {
        QString cityA = get<0>(edge).trimmed();
        QString cityB = get<1>(edge).trimmed();
        float distance = get<2>(edge);

        if (cityA.isEmpty() || cityB.isEmpty()) {
            throw std::invalid_argument("Empty city field");
        }

        std::string s1 = cityA.toStdString();
        std::string s2 = cityB.toStdString();

        if (s1 == s2)
            throw std::invalid_argument("Cannot add an edge between a city and itself");

        if (distance <= 0)
            throw std::invalid_argument("Distance must be a positive number");

        if (!containsEdge(s1, s2)) {
            adj[s1].push_back({s2, distance});
            adj[s2].push_back({s1, distance});
        }
    }
}

string Graph::dijkstra(const string& start, const string& end) {
    if (!containsCity(start) || !containsCity(end)) {
        return "Error: One or both cities do not exist in the graph.";
    }

    for (auto& [node, _] : adj) {
        dis[node] = std::numeric_limits<double>::infinity();
        vis[node] = false;
        parent[node] = "";
    }

    priority_queue<pair<double, string>,
                        vector<pair<double, string>>,
                        greater<pair<double, string>>> pq;

    pq.push({0.0, start});
    dis[start] = 0.0;

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (vis[node]) continue;
        vis[node] = true;

        for (auto& [neighbor, weight] : adj[node]) {
            if (!vis[neighbor] && dis[node] + weight < dis[neighbor]) {
                dis[neighbor] = dis[node] + weight;
                pq.push({dis[neighbor], neighbor});
                parent[neighbor] = node;
            }
        }
    }

    if (dis[end] == numeric_limits<double>::infinity()) {
        return "No path from " + start + " to " + end + ".";
    }

    string finalDistance = to_string(dis[end]);
    size_t dot_pos = finalDistance.find('.');
    if (dot_pos != string::npos) {
        size_t end_pos = min(dot_pos + 3, finalDistance.size());
        finalDistance = finalDistance.substr(0, end_pos);
    }

    string result = "Distance from " + start + " to " + end + " is: " + finalDistance + "\n";

    vector<string> path;
    for (string at = end; !at.empty(); at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    result += "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        result += path[i];
        if (i + 1 < path.size()) result += " -> ";
    }

    return result;
}

string Graph::kruskal() {
    if (isEmpty()) {
        return "Empty graph";
    }

    stringstream result;
    struct Edge {
        string src, dest;
        float weight;
        Edge(const string& s, const string& d, float w) : src(s), dest(d), weight(w) {}
        bool operator<(const Edge& other) const { return weight < other.weight; }
    };

    vector<Edge> edges;
    unordered_map<string, string> parent;

    for (const auto& node : adj) {
        parent[node.first] = node.first;
    }

    for (const auto& node : adj) {
        const string& u = node.first;
        for (const auto& neighbor : node.second) {
            if (u < neighbor.first) {
                if (neighbor.second < 0) {
                    return "Error: Negative weights not allowed";
                }
                edges.emplace_back(u, neighbor.first, neighbor.second);
            }
        }
    }

    sort(edges.begin(), edges.end());

    auto findRoot = [&parent](string x) -> string {
        string root = x;
        while (root != parent[root]) {
            root = parent[root];
        }
        string current = x;
        while (current != root) {
            string next = parent[current];
            parent[current] = root;
            current = next;
        }
        return root;
    };

    float totalCost = 0;
    vector<Edge> mst_edges;
    for (const auto& edge : edges) {
        string rootSrc = findRoot(edge.src);
        string rootDest = findRoot(edge.dest);
        if (rootSrc != rootDest) {
            mst_edges.push_back(edge);
            totalCost += edge.weight;
            parent[rootSrc] = rootDest;
        }
    }

    set<string> components;
    for (const auto& node : adj) {
        components.insert(findRoot(node.first));
    }

    result << fixed << setprecision(2);
    for (const auto& edge : mst_edges) {
        result << edge.src << " --> " << edge.dest << " (distance: " << edge.weight << ")\n";
    }
    if (components.size() > 1) {
        result << "\nNote: Graph has " << components.size() << " components. Created a minimum spanning forest.\n";
    }
    //result << "\nTotal MST Cost: " << totalCost << "\n";

    return result.str();
}

string Graph::displayMap() {
    stringstream ss;
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        ss << "City: " << it->first << "\n";

        if (it->second.empty())
            continue;

        for (auto t : it->second) {
            ss << "  - Road to " << t.first << " (Distance: " << t.second << ")\n";
        }
        ss << endl;
    }
    return ss.str();
}

string Graph::bfs(const string& startNode) {
    if (!containsCity(startNode)) {
        throw invalid_argument("Start city not found in graph");
    }

    queue<string> q;
    vis.clear();
    vector<string> traversal_order;
    q.push(startNode);
    vis[startNode] = true;

    while (!q.empty()) {
        string node = q.front();
        q.pop();

        if (node != startNode) {
            traversal_order.push_back(node);
        }

        for (const auto& [child, weight] : adj[node]) {
            if (!vis[child]) {
                vis[child] = true;
                q.push(child);
            }
        }
    }

    stringstream ss;
    ss << "BFS Traversal from city \"" << startNode << "\":\n\n";
    int count = 1;
    for (const auto& node : traversal_order) {
        ss << count++ << ". " << node << "\n";
    }
    ss << "\nTraversal complete.\n";

    return ss.str();
}
string Graph::dfs(const string& startNode) {
    if (!containsCity(startNode))
        throw invalid_argument("Start node not found in graph");

    vis.clear();
    vector<string> traversal_order;
    stack<string> s;
    s.push(startNode);
    vis[startNode] = true;

    while (!s.empty()) {
        string node = s.top();
        s.pop();

        if (node != startNode) {
            traversal_order.push_back(node);
        }

        vector<string> neighbors;
        for (const auto& [child, weight] : adj[node]) {
            if (!vis[child]) {
                neighbors.push_back(child);
                vis[child] = true;
            }
        }
        std::reverse(neighbors.begin(), neighbors.end());
        for (const auto& child : neighbors) {
            s.push(child);
        }
    }

    stringstream ss;
    ss << "DFS Traversal from city \"" << startNode << "\":\n\n";
    int count = 1;
    for (const auto& node : traversal_order) {
        ss << count++ << ". " << node << "\n";
    }
    ss << "\nTraversal complete.\n";

    return ss.str();
}

bool Graph::isEmpty() const {
    return adj.empty();
}

AdjacencyList& Graph::getAdjacencyList() {
    return adj;
}

void Graph::setAdjacencyList(const AdjacencyList &adj) {
    this->adj = adj;
}

vector<string> Graph::convertAdjListToGraphLines() {
    vector<string> graphLines;

    if (adj.empty()) {
        return graphLines;
    }

    for (const auto& [city, neighbors] : adj) {
        string line = city;
        for (const auto& [neighbor, distance] : neighbors) {
            line += " (" + neighbor + ":" + to_string(distance) + ")";
        }
        graphLines.push_back(line);
    }
    return graphLines;
}

void Graph::parseGraphLines(const vector<string> &graphLines) {
    regex pattern(R"(\(([^:]+):([0-9]+(?:\.[0-9]+)?)\))");

    for (const string& line : graphLines) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        istringstream iss(line);
        string city;
        iss >> city;

        if (city.empty()) {
            continue;
        }

        if (adj.find(city) == adj.end()) {
            adj[city] = vector<pair<string, float>>();
        }

        auto matches_begin = sregex_iterator(line.begin(), line.end(), pattern);
        auto matches_end = sregex_iterator();

        int connectionCount = 0;
        for (sregex_iterator i = matches_begin; i != matches_end; ++i) {
            smatch match = *i;
            string destCity = match[1];
            float weight = stof(match[2]);
            adj[city].emplace_back(destCity, weight);
            connectionCount++;
        }
    }
}

void Graph::clear() {
    if (isEmpty())
        throw invalid_argument("Graph is already empty");
    adj.clear();
}
