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

void Graph::addCity(const std::string& cityName) {
    if (containsCity(cityName))
        throw std::invalid_argument("City already exists: " + cityName);
    adj[cityName];
}

void Graph::addEdge(const std::string& start, const std::string& end, float distance) {
    if (!containsCity(start) || !containsCity(end))
        throw std::invalid_argument("One or two of the cities does not exist");

    if (start == end)
        throw std::invalid_argument("Cannot add an edge between a city and itself");

    if (distance <= 0)
        throw std::invalid_argument("Invalid distance value");

    if (containsEdge(start, end))
        throw std::invalid_argument("Road already exists between those cities");

    adj[start].push_back({end, distance});
    adj[end].push_back({start, distance});
}

bool Graph::containsCity(const std::string& cityName) {
    return adj.find(cityName) != adj.end();
}

void Graph::deleteEdge(const std::string& start, const std::string& end) {
    if (!containsCity(start) || !containsCity(end))
        throw std::invalid_argument("One or two of the cities does not exist");

    if (!containsEdge(start, end))
        throw std::invalid_argument("Road does not exist between those cities");

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

bool Graph::containsEdge(const std::string& start, const std::string& end) {
    bool edgeExists = false;
    for (const auto& neighbor : adj[start]) {
        if (neighbor.first == end) {
            edgeExists = true;
            break;
        }
    }
    return edgeExists;
}

void Graph::deleteCity(const std::string& cityName) {
    if (!containsCity(cityName))
        throw std::invalid_argument("City does not exist in graph");

    // loop through adjacency list to find neighbors
    for (auto& cityPair : adj) {
        std::string neighbour = cityPair.first;

        if (neighbour != cityName) {
            auto &neighborCities = cityPair.second;

            // loop through neighbors vector of the neighbour city
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

void Graph::addGraphFromUI(const QVector<std::tuple<QString, QString, float>>& edges) {
    for (const auto& edge : edges) {
        QString cityA = std::get<0>(edge).trimmed();
        QString cityB = std::get<1>(edge).trimmed();
        float distance = std::get<2>(edge);

        if (cityA.isEmpty() || cityB.isEmpty()) {
            qDebug() << "Invalid input: empty QString detected";
            return; // or handle appropriately
        }

        std::string s1 = cityA.toStdString();
        std::string s2 = cityB.toStdString();

        if (s1 == s2 || distance <= 0) continue;

        bool edgeExists = false;
        for (const auto& neighbor : adj[s1]) {
            if (neighbor.first == s2) {
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists) {
            adj[s1].push_back({s2, distance});
            adj[s2].push_back({s1, distance});
        }
    }
}

std::string Graph::dijkstra(const std::string& start, const std::string& end) {
    if (adj.find(start) == adj.end() || adj.find(end) == adj.end()) {
        return "Error: One or both cities do not exist in the graph.";
    }

    for (auto& [node, _] : adj) {
        dis[node] = std::numeric_limits<double>::infinity();
        vis[node] = false;
        parent[node] = "";
    }

    std::priority_queue<std::pair<double, std::string>,
                        std::vector<std::pair<double, std::string>>,
                        std::greater<std::pair<double, std::string>>> pq;

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

    if (dis[end] == std::numeric_limits<double>::infinity()) {
        return "No path from " + start + " to " + end + ".";
    }

    std::string finalDistance = std::to_string(dis[end]);
    size_t dot_pos = finalDistance.find('.');
    if (dot_pos != std::string::npos) {
        size_t end_pos = std::min(dot_pos + 3, finalDistance.size());
        finalDistance = finalDistance.substr(0, end_pos);
    }

    std::string result = "Distance from " + start + " to " + end + " is: " + finalDistance + "\n";

    std::vector<std::string> path;
    for (std::string at = end; !at.empty(); at = parent[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());

    result += "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        result += path[i];
        if (i + 1 < path.size()) result += " -> ";
    }

    return result;
}

std::string Graph::displayMap() {
    std::stringstream ss;
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        ss << "City: " << it->first << "\n";

        if (it->second.empty())
            continue;

        for (auto t : it->second) {
            ss << "  - Road to " << t.first << " (Distance: " << t.second << ")\n";
        }
        ss << std::endl;
    }
    return ss.str();
}

void Graph::BFS(const QString& startNode, QTextEdit* output) {
    std::queue<QString> q;
    vis.clear();
    q.push(startNode);
   vis[startNode.toStdString()] = true;
    QString result = "BFS Traversal:\n";

    while (!q.empty()) {
        QString node = q.front();
        q.pop();
        result += node + "\n";

        for (auto [child, weight] : adj[node.toStdString()]) {
            QString qChild = QString::fromStdString(child);
            if (!vis[qChild.toStdString()]) {
                vis[qChild.toStdString()] = true;
                q.push(qChild);
                result += " -> " + qChild + " (Weight: " + QString::number(weight) + ")\n";
            }
        }
    }
    output->append(result);
}

void Graph::DFS(const QString& startNode, QTextEdit* output) {
    if (!output) {
        throw std::invalid_argument("Output widget is null");
    }
    if (adj.find(startNode.toStdString()) == adj.end()) {
        throw std::invalid_argument("Start node not found in graph");
    }

    // Use a stack to track recursion depth and accumulate result
    QString result = "DFS Traversal:\n";
    std::stack<std::pair<QString, int>> callStack;
    callStack.push({startNode, 0}); // Node and depth (0 for root)
    vis.clear(); // Reset visited map

    while (!callStack.empty()) {
        auto [node, depth] = callStack.top();
        callStack.pop();

        if (!vis[node.toStdString()]) {
            vis[node.toStdString()] = true;
            result += node + "\n";

            // Push children in reverse order to maintain DFS order
            std::vector<std::pair<QString, float>> children;
            for (const auto& [child, weight] : adj[node.toStdString()]) {
                QString qChild = QString::fromStdString(child);
                if (!vis[qChild.toStdString()]) {
                    children.emplace_back(qChild, weight);
                }
            }
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                result += " -> " + it->first + " (Weight: " + QString::number(it->second, 'f', 2) + ")\n";
                callStack.push({it->first, depth + 1});
            }
        }
    }

    // Append result only once after traversal
    output->append(result);
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
        cout << "WARNING: EMPTY ADJACENCY LIST!\n";
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
    regex pattern(R"(\(([^:]+):([0-9]+(?:\.[0-9]+)?)\))");  // matches (string:float)

    for (const string& line : graphLines) {
        if (line.empty() || line[0] == '#') {
            continue; // Skip empty lines and comments
        }

        istringstream iss(line);
        string city;
        iss >> city; // Extract source city

        if (city.empty()) {
            continue;
        }

        // Ensure the city exists in adj, even if it has no edges
        if (adj.find(city) == adj.end()) {
            adj[city] = std::vector<std::pair<std::string, float>>();
        }

        // Extract all (destination:distance) pairs
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
        throw std::invalid_argument("Adjacency List is already empty");
    adj.clear();
}
