#include "graph.h"
#include <stdexcept>
#include <limits>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

void Graph::addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges)
{
    for (const auto& edge : edges) {
        QString cityA = std::get<0>(edge).trimmed();
        QString cityB = std::get<1>(edge).trimmed();
        int distance = std::get<2>(edge);

        std::string s1 = cityA.toStdString();
        std::string s2 = cityB.toStdString();

        if (s1 == s2) {
            throw std::runtime_error("Self-loop is not allowed (city connected to itself).");
        }

        if (distance <= 0) {
            throw std::runtime_error("Distance must be a positive number.");
        }

        // Check if the edge already exists
        for (const auto& neighbor : adj[s1]) {
            if (neighbor.first == s2) {
                throw std::runtime_error("This edge already exists.");
            }
        }

        // Add the edge in both directions (undirected graph)
        adj[s1].push_back({ s2, distance });
        adj[s2].push_back({ s1, distance });
    }
}

std::string Graph::dijkstra(const std::string& start, const std::string& end) {
    if (adj.find(start) == adj.end() || adj.find(end) == adj.end()) {
        return "Error";
    }

    // Initialize all nodes
    for (auto& [node, _] : adj) {
        dis[node] = std::numeric_limits<double>::infinity();  // set to infinity
        vis[node] = false;
        parent[node] = "";
    }

    // Priority queue to store (cost, node)
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> pq;
    pq.push({0.0, start});
    dis[start] = 0.0;

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (vis[node]) continue;
        vis[node] = true;

        // Iterate over neighbors
        for (auto& [neighbor, weight] : adj[node]) {
            if (!vis[neighbor] && dis[node] + weight < dis[neighbor]) {
                dis[neighbor] = dis[node] + weight;
                pq.push({dis[neighbor], neighbor});
                parent[neighbor] = node;
            }
        }
    }

    std::string result;
    if (dis[end] == std::numeric_limits<double>::infinity()) {
        result = "No path from " + start + " to " + end + ".";
        return result;
    }

    result = "Distance from " + start + " to " + end + " is: " + std::to_string(dis[end]) + "\n";
    std::vector<std::string> path;
    for (std::string at = end; !at.empty(); at = parent[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());

    result += "Path: ";
    for (int i = 0; i < path.size(); ++i) {
        result += path[i];
        if (i + 1 < path.size()) result += " -> ";
    }
    return result;
}
