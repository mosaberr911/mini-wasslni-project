#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>
#include "Graph.h"
#include "GraphVisualizer.h"
using namespace std;

using AdjacencyList = unordered_map<string, vector<pair<string, float> > >;

class User
{
private:
    string email;
    string password;
    Graph graph;
public:
    User();
    User(const string& email, const string& password);
    string getEmail() const;
    string getPassword() const;
    void setEmail(const string&);
    void setPassword(const string&);
    AdjacencyList& getAdjacencyList();
    void setAdjacencyList(const AdjacencyList&);

    // Graph manipulation/display functions
    void addGraph(const QVector<std::tuple<QString, QString, float>>& edges);
    string displayMap();
    string showShortestPath(const string&, const string&);
    string showMinimumSpanningTree();
    void addCity(const string&);
    void deleteCity(const string&);
    void addRoad(const string&, const string&, float);
    void deleteRoad(const string&, const string&);
    const Graph &getGraph() const;
    void setGraph(const Graph&);
    string displayDfs(const string&);
    string displayBfs(const string&);
    bool hasGraph();
    void clearGraph();

    vector<string> getConvertedAdjacencyList();
    void parseLoadedGraphLines(const vector<string>&);
};

#endif // USER_H
