#include "graph.h"
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

Graph::Graph(const std::string& userEmail) : userEmail(userEmail) {}

void Graph::setUserEmail(const std::string& email) {
    userEmail = email;
}

bool Graph::addCity(std::string cityName) {
    if (containsCity(cityName)) {
        std::cerr << "City '" << cityName << "' already exists in the graph." << std::endl;
        return false;
    }
    adj[cityName];
    return true;
}

bool Graph::addEdge(std::string city1, std::string city2, float distance) {
    if (!containsCity(city1)) return false;
    if (!containsCity(city2)) return false;
    if (city1 == city2) return false;
    if (distance <= 0) return false;

    for (const auto& neighbor : adj[city1]) {
        if (neighbor.first == city2) {
            return false;
        }
    }

    adj[city1].push_back({city2, distance});
    adj[city2].push_back({city1, distance});
    return true;
}

bool Graph::containsCity(std::string cityName) {
    if (adj.find(cityName) != adj.end()) {
        return true;
    }

    std::string filePath = getUserGraphPath();
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open user graph file: " + filePath);
    }

    std::unordered_set<std::string> cities;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string city1, city2;
        float distance;

        std::getline(ss, city1, ',');
        std::getline(ss, city2, ',');
        ss >> distance;

        cities.insert(city1);
        cities.insert(city2);
    }

    file.close();

    for (const auto& city : cities) {
        adj[city];
    }

    return cities.find(cityName) != cities.end();
}

bool Graph::deleteEdge(std::string city1, std::string city2) {
    if (!containsCity(city1) || !containsCity(city2) || city1 == city2) return false;

    bool edgeRemoved = false;

    auto& neighbors1 = adj[city1];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); ++it) {
        if (it->first == city2) {
            neighbors1.erase(it);
            edgeRemoved = true;
            break;
        }
    }

    if (edgeRemoved) {
        auto& neighbors2 = adj[city2];
        for (auto it = neighbors2.begin(); it != neighbors2.end(); ++it) {
            if (it->first == city1) {
                neighbors2.erase(it);
                break;
            }
        }
    }

    return edgeRemoved;
}

bool Graph::deleteCity(std::string cityName) {
    if (!containsCity(cityName))
        throw std::runtime_error("City does not exist in the graph.");

    for (auto& cityPair : adj) {
        std::string neighbour = cityPair.first;
        if (neighbour != cityName) {
            auto &neighborCities = cityPair.second;
            for (auto it = neighborCities.begin(); it != neighborCities.end();) {
                if (it->first == cityName)
                    it = neighborCities.erase(it);
                else
                    ++it;
            }
        }
    }

    adj.erase(cityName);
    return true;
}

void Graph::addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges) {
    for (const auto& edge : edges) {
        QString cityA = std::get<0>(edge).trimmed();
        QString cityB = std::get<1>(edge).trimmed();
        int distance = std::get<2>(edge);

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
            adj[s1].push_back({s2, static_cast<float>(distance)});
            adj[s2].push_back({s1, static_cast<float>(distance)});
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
        ss << "City: " << it->first << ":\n";
        for (auto t : it->second) {
            ss << "  - Road to " << t.first << " (Distance: " << t.second << ")\n";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::string Graph::getUserGraphPath() const {
    if (userEmail.empty()) {
        throw std::runtime_error("User email not set");
    }

    std::string sanitizedEmail = userEmail;
    size_t pos = 0;
    while ((pos = sanitizedEmail.find("@", pos)) != std::string::npos) {
        sanitizedEmail.replace(pos, 1, "_at_");
        pos += 4;
    }
    pos = 0;
    while ((pos = sanitizedEmail.find(".", pos)) != std::string::npos) {
        sanitizedEmail.replace(pos, 1, "_dot_");
        pos += 5;
    }

    for (char& c : sanitizedEmail) {
        if (!isalnum(c) && c != '_') {
            c = '_';
        }
    }

    return "C:/Users/A/OneDrive/Documents/wasslni/maps/" + sanitizedEmail + "_graph.txt";
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
    vis[startNode.toStdString()] = true;
    QString result = "DFS Traversal:\n";
    result += startNode + "\n";

    for (auto [child, weight] : adj[startNode.toStdString()]) {
        QString qChild = QString::fromStdString(child);
        result += " -> " + qChild + " (Weight: " + QString::number(weight) + ")\n";
        if (!vis[qChild.toStdString()]) {
            result += "Exploring " + qChild + "\n";
            DFS(qChild, output);
        }
    }
    output->append(result);
}
