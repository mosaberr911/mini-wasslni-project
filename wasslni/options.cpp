#include "options.h"
#include "graph.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Options::Options(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);
    setWindowTitle("Options");

    // الخلفية
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // زر Show Shortest Path
    showShortestPathButton = new QPushButton("Show Shortest Path", this);
    showShortestPathButton->setStyleSheet("background-color: green; color: white;");
    showShortestPathButton->setGeometry(200, 50, 200, 40);

    // حقول إدخال المدن
    startCityLineEdit = new QLineEdit(this);
    startCityLineEdit->setPlaceholderText("Enter Start City");
    startCityLineEdit->setGeometry(150, 120, 300, 40);
    startCityLineEdit->setVisible(false);

    endCityLineEdit = new QLineEdit(this);
    endCityLineEdit->setPlaceholderText("Enter End City");
    endCityLineEdit->setGeometry(150, 180, 300, 40);
    endCityLineEdit->setVisible(false);

    // زر Show Path
    showPathButton = new QPushButton("Show Path", this);
    showPathButton->setStyleSheet("background-color: lightblue; color: black;");
    showPathButton->setGeometry(200, 240, 200, 40);
    showPathButton->setVisible(false);
    showPathButton->setEnabled(false);

    // الربط بالأحداث
    connect(showShortestPathButton, &QPushButton::clicked, this, &Options::onShowShortestPathClicked);
    connect(showPathButton, &QPushButton::clicked, this, &Options::onShowPathClicked);
}

void Options::onShowShortestPathClicked()
{
    // تبديل الحالة بين الإظهار والإخفاء
    isPathInputVisible = !isPathInputVisible;

    startCityLineEdit->setVisible(isPathInputVisible);
    endCityLineEdit->setVisible(isPathInputVisible);
    showPathButton->setVisible(isPathInputVisible);
    showPathButton->setEnabled(isPathInputVisible);

    if (isPathInputVisible) {
        // توسيط العناصر عند الإظهار
        int centerX = (width() - startCityLineEdit->width()) / 2;
        startCityLineEdit->move(centerX, 120);
        endCityLineEdit->move(centerX, 180);
        showPathButton->move((width() - showPathButton->width()) / 2, 240);

        // تغيير نص الزر
        showShortestPathButton->setText("Hide Path Input");
    } else {
        // إعادة نص الزر
        showShortestPathButton->setText("Show Shortest Path");
    }
}

QVector<std::tuple<QString, QString, int>> Options::loadEdgesFromFile(const QString& filePath)
{
    QVector<std::tuple<QString, QString, int>> edges;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filePath;
        return edges;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if (parts.size() == 3) {
            QString a = parts[0].trimmed();
            QString b = parts[1].trimmed();
            int dist = parts[2].trimmed().toInt();
            edges.append({a, b, dist});
        }
    }

    file.close();
    return edges;
}

void Options::onShowPathClicked()
{
    QString startCity = startCityLineEdit->text().trimmed();
    QString endCity = endCityLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Both cities must be entered!");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    std::string result = graph.dijkstra(startCity.toStdString(), endCity.toStdString());
    QMessageBox::information(this, "Shortest Path", QString::fromStdString(result));
}
