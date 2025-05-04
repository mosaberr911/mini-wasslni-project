#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QVector>
#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <limits>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Graph
{
public:
    void addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges);
    std::string dijkstra(const std::string& start, const std::string& end);
    std::string displayMap();

    bool addCity(std::string cityName);
    bool addEdge(std::string city1, std::string city2, float distance);
    bool containsCity(std::string cityName);
    bool deleteEdge(std::string city1, std::string city2);  // الدالة المضافة

private:
    std::map<std::string, std::vector<std::pair<std::string, float>>> adj;  // تغيير int إلى float لتتناسب مع الدوال
    std::map<std::string, double> dis;
    std::map<std::string, bool> vis;
    std::map<std::string, std::string> parent;
};

#endif // GRAPH_H
