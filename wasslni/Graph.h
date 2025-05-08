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

class Graph
{
public:
    Graph(const std::string& userEmail = "");  // Constructor with optional userEmail

    void setUserEmail(const std::string& email);  // Setter for userEmail
    std::string getUserGraphPath() const;  // Getter for user graph file path

    void addGraphFromUI(const QVector<std::tuple<QString, QString, int>>& edges);
    std::string dijkstra(const std::string& start, const std::string& end);
    std::string displayMap();
    void BFS(const QString& startNode, QTextEdit* output);
    void DFS(const QString& startNode, QTextEdit* output);

    bool addCity(std::string cityName);
    bool addEdge(std::string city1, std::string city2, float distance);
    bool containsCity(std::string cityName);
    bool deleteEdge(std::string city1, std::string city2);
    bool deleteCity(std::string cityName);

private:
    std::string userEmail;  // User email for file path creation
    std::map<std::string, std::vector<std::pair<std::string, float>>> adj;
    std::map<std::string, double> dis;
    std::map<std::string, bool> vis;
    std::map<std::string, std::string> parent;
};

#endif // GRAPH_H
