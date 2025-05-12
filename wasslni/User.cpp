#include "User.h"
#include <string>
#include <iostream>
using namespace std;

User::User() = default;

User::User(const string &email, const string &password) {
    this->email = email;
    this->password = password;
}

string User::getEmail() const {
    return email;
}

string User::getPassword() const {
    return password;
}

void User::setEmail(const string& email) {
    this->email = email;
}

void User::setPassword(const string& password) {
    this->password = password;
}

AdjacencyList User::getAdjacencyList() const {
    return graph.getAdjacencyList();
}

void User::setAdjacencyList(const AdjacencyList& adj) {
    graph.setAdjacencyList(adj);
}

void User::addGraph(const QVector<std::tuple<QString, QString, int>>& edges) {
    try {
        graph.addGraphFromUI(edges);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::addGraph:" << e.what();
        throw;
    }
}

string User::displayMap() {
    return graph.displayMap();
}

string User::showShortestPath(const string& start, const string& end) {
    try {
        return graph.dijkstra(start, end);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::showShortesPath:" << e.what();
        throw;
    }
}

void User::addCity(const string& city) {
    try {
        graph.addCity(city);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::addCity:" << e.what();
        throw;
    }
}

void User::deleteCity(const string& city) {
    try {
        graph.deleteCity(city);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::deleteCity:" << e.what();
        throw;
    }
}

void User::addRoad(const string& startCity, const string& endCity, float distance) {
    try {
        graph.addEdge(startCity, endCity, distance);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::addRoad:" << e.what();
        throw;
    }
}

void User::deleteRoad(const string& startCity, const string& endCity) {
    try {
        graph.deleteEdge(startCity, endCity);
    } catch (const std::exception& e) {
        qWarning() << "Error in User::deleteRoad:" << e.what();
        throw;
    }
}

const Graph& User::getGraph() const {
    return graph;
}

void User::setGraph(const Graph& graph) {
    this->graph = graph;
}

void User::displayDfs(const QString& startNode, QTextEdit* output) {
    graph.DFS(startNode, output);
}

void User::displayBfs(const QString& startNode, QTextEdit* output) {
    graph.BFS(startNode, output);
}

bool User::hasGraph() {
    return !graph.isEmpty();
}

void User::clearGraph() {
    graph.clear();
}

vector<string> User::getConvertedAdjacencyList() {
    return graph.convertAdjListToGraphLines();
}

void User::parseLoadedGraphLines(const vector<string>& graphLines) {
    return graph.parseGraphLines(graphLines);
}
