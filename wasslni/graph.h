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

class Graph
{
public:
    void addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges);
    std::string dijkstra(const std::string& start, const std::string& end);  // دالة Dijkstra

private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> adj;  // قائمة الجوار
    std::map<std::string, double> dis;  // لتخزين المسافات
    std::map<std::string, bool> vis;  // لتخزين إذا تم زيارة العقدة
    std::map<std::string, std::string> parent;  // لتخزين الأب لكل عقدة
};

#endif // GRAPH_H
