#include "graph.h"
#include <stdexcept>
#include <limits>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>  // لإظهار رسائل الخطأ والنجاح

// دالة لإضافة مدينة بدون تكرار
bool Graph::addCity(std::string cityName) {
    if (containsCity(cityName)) {
        std::cerr << "City '" << cityName << "' already exists in the graph." << std::endl;  // رسالة خطأ في حال وجود المدينة
        return false;  // المدينة موجودة بالفعل
    }
    adj[cityName];  // تضاف كـ مفتاح جديد بدون جيران حالياً
    return true;  // تم إضافة المدينة بنجاح
}

// دالة لحذف مدينة مع إزالة جميع الإشارات لها في باقي المدن
void Graph::deleteCity(std::string cityName) {
    if (!containsCity(cityName)) {
        std::cerr << "Error: City '" << cityName << "' does not exist in the graph." << std::endl;
        return;  // لا تقوم بإزالة المدينة إذا لم تكن موجودة
    }

    for (auto& cityPair : adj) {
        std::string neighbour = cityPair.first;

        if (neighbour != cityName) {
            auto& neighborCities = cityPair.second;
            for (auto it = neighborCities.begin(); it != neighborCities.end();) {
                if (it->first == cityName)
                    it = neighborCities.erase(it);
                else
                    ++it;
            }
        }
    }
    adj.erase(cityName);
}

// فحص إذا كانت المدينة موجودة
bool Graph::containsCity(std::string cityName) {
    return adj.find(cityName) != adj.end();
}

// دالة لإضافة الرسم البياني من واجهة المستخدم
void Graph::addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges)
{
    for (const auto& edge : edges) {
        QString cityA = std::get<0>(edge).trimmed();
        QString cityB = std::get<1>(edge).trimmed();
        int distance = std::get<2>(edge);

        std::string s1 = cityA.toStdString();
        std::string s2 = cityB.toStdString();

        if (s1 == s2) {
            std::cerr << "Self-loop is not allowed (city connected to itself)." << std::endl;
            continue;  // تخطي هذه الحافة
        }

        if (distance <= 0) {
            std::cerr << "Distance must be a positive number." << std::endl;
            continue;  // تخطي هذه الحافة
        }

        for (const auto& neighbor : adj[s1]) {
            if (neighbor.first == s2) {
                std::cerr << "Edge already exists between " << s1 << " and " << s2 << "." << std::endl;
                continue;  // تخطي هذه الحافة
            }
        }

        adj[s1].push_back({ s2, distance });
        adj[s2].push_back({ s1, distance });
    }
}

// دالة خوارزمية Dijkstra لإيجاد أقصر مسار
std::string Graph::dijkstra(const std::string& start, const std::string& end) {
    if (adj.find(start) == adj.end() || adj.find(end) == adj.end()) {
        return "Error: One or both cities do not exist in the graph.";
    }

    // إعدادات Dijkstra
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

    std::string result;
    if (dis[end] == std::numeric_limits<double>::infinity()) {
        return "No path from " + start + " to " + end + ".";
    }

    result = "Distance from " + start + " to " + end + " is: " + std::to_string(dis[end]) + "\n";

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

// عرض خريطة الرسم البياني
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
