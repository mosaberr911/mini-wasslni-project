#ifndef USER_H
#define USER_H

#include <string>
#include "Graph.h"
using namespace std;

using AdjacencyList = map<string, vector<pair<string, float> > >;

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
    AdjacencyList getAdjacencyList() const;
    void setAdjacencyList(const AdjacencyList&);

    // Graph manipulation/display functions
    void addGraph(const QVector<std::tuple<QString, QString, int>>& edges);
    string displayMap();
    string showShortestPath(const string&, const string&);
    void addCity(const string&);
    void deleteCity(const string&);
    void addRoad(const string&, const string&, float);
    void deleteRoad(const string&, const string&);
    const Graph &getGraph() const;
    void setGraph(const Graph&);
    void displayDfs(const QString& startNode, QTextEdit* output);
    void displayBfs(const QString& startNode, QTextEdit* output);
    bool hasGraph();
    void clearGraph();

    vector<string> getConvertedAdjacencyList();
    void parseLoadedGraphLines(const vector<string>&);
};

#endif // USER_H
