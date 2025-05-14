#ifndef GRAPH_H
#define GRAPH_H
#include <queue>
#include <QString>
#include <QVector>
#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <QTextEdit>
#include <limits>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <stdexcept>

using AdjacencyList = std::map<std::string, std::vector<std::pair<std::string, float> > >;
using namespace std;

class Graph
{
public:
    Graph();

    void addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges);
    std::string dijkstra(const std::string& start, const std::string& end);
    std::string displayMap();
    void BFS(const QString& startNode, QTextEdit* output);
    void DFS(const QString& startNode, QTextEdit* output);

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
