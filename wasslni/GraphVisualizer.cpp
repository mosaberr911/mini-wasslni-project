// GraphVisualizer.cpp
#include "GraphVisualizer.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QVBoxLayout>
#include <QLabel>
#include <cmath>
#include <random>
#include <iostream>

// Force-directed layout parameters
// Increased REPULSION to push nodes further apart
const double REPULSION = 100000.0;
// Decreased ATTRACTION to reduce the pull between connected nodes
const double ATTRACTION = 0.01;
const double DAMPING = 0.80;

GraphVisualizer::GraphVisualizer(const AdjacencyList& adjacencyList, QWidget* parent)
    : QMainWindow(parent) {

    setWindowTitle("Roads Graph Visualization");
    resize(1200, 900);
    setAdjacencyList(adjacencyList);
    // Main widget and layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create top layout for button
    QHBoxLayout* topLayout = new QHBoxLayout();
    returnButton = new QPushButton("Return to Options", this);
    zoomInButton = new QPushButton("+", this);
    zoomOutButton = new QPushButton("-", this);
    resetZoomButton = new QPushButton("Reset View", this);

    topLayout->addWidget(returnButton);
    topLayout->addStretch(); // Pushes button to left
    topLayout->addWidget(zoomInButton);
    topLayout->addWidget(zoomOutButton);
    topLayout->addWidget(resetZoomButton);
    mainLayout->addLayout(topLayout);

    // Graphics scene setup
    scene = new QGraphicsScene(this);
    // Increased scene size to accommodate larger spacing
    scene->setSceneRect(-500, -400, 1000, 800);

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    // Add zoom capability
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    view->setInteractive(true);
    view->setSceneRect(-600, -450, 1200, 900);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    mainLayout->addWidget(view);

    setCentralWidget(centralWidget);

    // Create initial graph
    createInitialGraph();

    // Timer for animation
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &GraphVisualizer::updateForceLayout);
    connect(returnButton, &QPushButton::clicked, this, &GraphVisualizer::onReturnClicked);
    connect(zoomInButton, &QPushButton::clicked, this, &GraphVisualizer::onZoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &GraphVisualizer::onZoomOut);
    connect(resetZoomButton, &QPushButton::clicked, this, &GraphVisualizer::onResetZoom);

    // Automatically start force layout when visualization is shown
    QTimer::singleShot(100, this, &GraphVisualizer::startForceLayout);
}

void GraphVisualizer::setAdjacencyList(const AdjacencyList &adj) {
    this->adjacencyList = adj;
}

GraphVisualizer::~GraphVisualizer() {
    // Qt will handle deletion of UI elements
}

void GraphVisualizer::onZoomIn() {
    view->scale(1.25, 1.25);
}

void GraphVisualizer::onZoomOut() {
    view->scale(0.8, 0.8);
}

void GraphVisualizer::onResetZoom() {
    view->resetTransform();
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void GraphVisualizer::createInitialGraph() {
    // Clear previous graph
    scene->clear();
    nodes.clear();
    edges.clear();

    // Generate initial positions (random)
    std::random_device rd;
    std::mt19937 gen(rd());
    // Wider initial distribution to reduce initial overlapping
    std::uniform_real_distribution<> xDist(-400, 400);
    std::uniform_real_distribution<> yDist(-300, 300);

    // Process nodes first
    for (const auto& pair : adjacencyList) {
        const std::string& city = pair.first;

        // Check if node already exists
        if (nodes.find(city) == nodes.end()) {
            // Create node
            double x = xDist(gen);
            double y = yDist(gen);

            QGraphicsEllipseItem* circle = scene->addEllipse(-15, -15, 30, 30, QPen(Qt::white), QBrush(Qt::darkGreen));
            circle->setPos(x, y);
            circle->setZValue(1);

            QGraphicsTextItem* label = scene->addText(QString::fromStdString(city));
            label->setDefaultTextColor(Qt::white);
            // Position the label further away from the node (increased y-offset from -30 to -45)
            label->setPos(x - label->boundingRect().width()/2, y - 45);
            label->setZValue(2);

            nodes[city] = Node(circle, label, x, y);
        }

        // Also add any destination nodes that don't have outgoing edges
        for (const auto& dest : pair.second) {
            const std::string& destCity = dest.first;

            if (nodes.find(destCity) == nodes.end()) {
                double x = xDist(gen);
                double y = yDist(gen);

                QGraphicsEllipseItem* circle = scene->addEllipse(-15, -15, 30, 30, QPen(Qt::white), QBrush(Qt::darkGreen));
                circle->setPos(x, y);
                circle->setZValue(1);

                QGraphicsTextItem* label = scene->addText(QString::fromStdString(destCity));
                label->setDefaultTextColor(Qt::white);
                // Position the label further away from the node (increased y-offset from -30 to -45)
                label->setPos(x - label->boundingRect().width()/2, y - 45);
                label->setZValue(2);

                nodes[destCity] = Node(circle, label, x, y);
            }
        }
    }

    // Now process edges
    drawEdges();
}

void GraphVisualizer::drawEdges() {
    // Remove previous edges
    for (auto edge : edges) {
        scene->removeItem(edge);
        delete edge;
    }
    edges.clear();

    // Draw new edges
    for (const auto& pair : adjacencyList) {
        const std::string& sourceCity = pair.first;

        if (nodes.find(sourceCity) == nodes.end()) continue;

        const Node& source = nodes[sourceCity];

        for (const auto& dest : pair.second) {
            const std::string& destCity = dest.first;
            float distance = dest.second;

            if (nodes.find(destCity) == nodes.end()) continue;

            const Node& destination = nodes[destCity];

            // Draw edge
            QGraphicsLineItem* line = scene->addLine(
                source.x, source.y,
                destination.x, destination.y,
                QPen(QColor(100, 100, 100), 1.5)
                );
            line->setZValue(0);
            edges.push_back(line);

            // Add distance label
            QGraphicsTextItem* distLabel = scene->addText(QString::number(distance, 'f', 2));
            distLabel->setDefaultTextColor(QColor("#D3D3D3"));
            distLabel->setPos(
                (source.x + destination.x) / 2 - distLabel->boundingRect().width() / 2,
                (source.y + destination.y) / 2 - distLabel->boundingRect().height() / 2
                );
            distLabel->setZValue(2);
            edges.push_back(distLabel);
        }
    }
}

void GraphVisualizer::startForceLayout() {
    // Reset velocities
    for (auto& pair : nodes) {
        pair.second.vx = 0;
        pair.second.vy = 0;
    }

    // Start animation
    animationTimer->start(30);  // 30ms interval for about 33fps
}

void GraphVisualizer::updateForceLayout() {
    bool stable = true;

    // Calculate forces
    for (auto& nodePair1 : nodes) {
        Node& node1 = nodePair1.second;
        double fx = 0, fy = 0;

        // Repulsive forces from all other nodes
        for (auto& nodePair2 : nodes) {
            if (nodePair1.first == nodePair2.first) continue;

            Node& node2 = nodePair2.second;
            double dx = node1.x - node2.x;
            double dy = node1.y - node2.y;
            double dist = std::sqrt(dx*dx + dy*dy);

            if (dist < 1.0) dist = 1.0;  // Avoid division by zero

            // Apply repulsive force
            double force = REPULSION / (dist * dist);
            fx += force * dx / dist;
            fy += force * dy / dist;
        }

        // Attractive forces for connected nodes
        const std::string& cityName = nodePair1.first;
        if (adjacencyList.find(cityName) != adjacencyList.end()) {
            if (!adjacencyList[cityName].data()) {
                continue;
            }
            for (const auto& edge : adjacencyList[cityName]) {
                const std::string& destCity = edge.first;
                if (nodes.find(destCity) != nodes.end()) {
                    Node& node2 = nodes[destCity];

                    double dx = node1.x - node2.x;
                    double dy = node1.y - node2.y;
                    double dist = std::sqrt(dx*dx + dy*dy);

                    if (dist > 1.0) {  // Avoid division by zero
                        // Apply attractive force
                        double force = ATTRACTION * dist;
                        fx -= force * dx / dist;
                        fy -= force * dy / dist;
                    }
                }
            }
        }

        // Check for incoming edges to this node
        for (const auto& adjPair : adjacencyList) {
            if (!adjPair.second.data()) {
                continue;
            }
            if (adjPair.second.empty()) {
                continue;
            }
            for (const auto& edge : adjPair.second) {
                if (edge.first == cityName) {
                    // This node has an incoming edge from adjPair.first
                    Node& node2 = nodes[adjPair.first];

                    double dx = node1.x - node2.x;
                    double dy = node1.y - node2.y;
                    double dist = std::sqrt(dx*dx + dy*dy);

                    if (dist > 1.0) {  // Avoid division by zero
                        // Apply attractive force
                        double force = ATTRACTION * dist;
                        fx -= force * dx / dist;
                        fy -= force * dy / dist;
                    }
                }
            }
        }
        // Update velocity with damping
        node1.vx = (node1.vx + fx) * DAMPING;
        node1.vy = (node1.vy + fy) * DAMPING;

        // Check if still moving significantly
        if (std::abs(node1.vx) > 0.1 || std::abs(node1.vy) > 0.1) {
            stable = false;
        }
    }

    // Apply velocities and update positions
    for (auto& pair : nodes) {
        Node& node = pair.second;

        // Apply velocity
        node.x += node.vx;
        node.y += node.vy;

        // Constrain to scene - increased bounds to match larger scene
        node.x = std::max(-450.0, std::min(450.0, node.x));
        node.y = std::max(-350.0, std::min(350.0, node.y));

        // Update graphical elements
        node.circle->setPos(node.x, node.y);
        // Updated label position to match the increased distance set in createInitialGraph
        node.label->setPos(node.x - node.label->boundingRect().width()/2, node.y - 45);
    }

    // Redraw edges
    drawEdges();

    // Stop if stable
    if (stable) {
        animationTimer->stop();
    }
}

void GraphVisualizer::onReturnClicked() {
    emit returnToOptionsWindow();
    this->hide();
}
