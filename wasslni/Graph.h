#ifndef GRAPH_H
#define GRAPH_H
#include <queue>
#include <QString>
#include <QVector>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <QTextEdit>
#include <limits>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <stdexcept>

using AdjacencyList = std::unordered_map<std::string, std::vector<std::pair<std::string, float> > >;
using namespace std;

class Graph
{
public:
    Graph();

    void addGraphFromUI(const QVector<std::tuple<QString, QString, float>>& edges);
    std::string dijkstra(const std::string& start, const std::string& end);
    pair<AdjacencyList, float> kruskal();
    std::string displayMap();
    std::string bfs(const string&);
    std::string dfs(const string&);

    void addCity(const std::string& cityName);
    void addEdge(const std::string& start, const std::string& end, float distance);
    bool containsCity(const std::string& cityName);
    bool containsEdge(const std::string& start, const std::string& end);
    void deleteEdge(const std::string& start, const std::string& end);
    void deleteCity(const std::string& cityName);

    AdjacencyList& getAdjacencyList();
    void setAdjacencyList(const AdjacencyList&);
    bool isEmpty() const;
    void clear();

    vector<string> convertAdjListToGraphLines();
    void parseGraphLines(const vector<string>& graphLines);
private:
    AdjacencyList adj;
    std::map<std::string, double> dis;
    std::map<std::string, bool> vis;
    std::map<std::string, std::string> parent;
};

#endif 
