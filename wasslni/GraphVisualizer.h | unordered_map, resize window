// GraphVisualizer.h
#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include <QPushButton>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QTimer>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>

using AdjacencyList = std::unordered_map<std::string, std::vector<std::pair<std::string, float>>>;

class GraphVisualizer : public QMainWindow {
    Q_OBJECT

public:
    explicit GraphVisualizer(const AdjacencyList&, QWidget* parent = nullptr);
    void setAdjacencyList(const AdjacencyList&);
    virtual ~GraphVisualizer();

signals:
    void returnToOptionsWindow();

private slots:
    void startForceLayout();
    void updateForceLayout();
    void onReturnClicked();
    void onZoomIn();
    void onZoomOut();
    void onResetZoom();

private:
    // Node representation
    struct Node {
        QGraphicsEllipseItem* circle;
        QGraphicsTextItem* label;
        double x, y;
        double vx, vy;  // Velocity for force layout

        Node(QGraphicsEllipseItem* c = nullptr, QGraphicsTextItem* l = nullptr, double x = 0, double y = 0)
            : circle(c), label(l), x(x), y(y), vx(0), vy(0) {}
    };

    // Data
    AdjacencyList adjacencyList;
    std::unordered_map<std::string, Node> nodes;
    std::vector<QGraphicsItem*> edges;

    // UI elements
    QPushButton* returnButton;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QPushButton* resetZoomButton;
    QTimer* animationTimer;

    // Functions
    void createInitialGraph();
    void drawEdges();
};

#endif // GRAPHVISUALIZER_H
