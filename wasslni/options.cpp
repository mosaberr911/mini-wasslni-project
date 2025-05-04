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
#include <QVBoxLayout>
#include <QSpacerItem>

Options::Options(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 700);
    setWindowTitle("Options");

    // الخلفية
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 700);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // Layout رئيسي
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(100, 30, 100, 30);  // هوامش داخلية

    // إعدادات الحجم والخط
    int elementHeight = 50;
    int elementWidth = 350;
    QFont font;
    font.setPointSize(12);

    // زر Show Shortest Path
    showShortestPathButton = new QPushButton("Show Shortest Path");
    showShortestPathButton->setStyleSheet("background-color: green; color: white;");
    showShortestPathButton->setFixedSize(elementWidth, elementHeight);
    showShortestPathButton->setFont(font);
    mainLayout->addWidget(showShortestPathButton, 0, Qt::AlignHCenter);

    // حقول إدخال المدن
    startCityLineEdit = new QLineEdit();
    startCityLineEdit->setPlaceholderText("Enter Start City");
    startCityLineEdit->setVisible(false);
    startCityLineEdit->setFixedSize(elementWidth, elementHeight);
    startCityLineEdit->setFont(font);
    mainLayout->addWidget(startCityLineEdit, 0, Qt::AlignHCenter);

    endCityLineEdit = new QLineEdit();
    endCityLineEdit->setPlaceholderText("Enter End City");
    endCityLineEdit->setVisible(false);
    endCityLineEdit->setFixedSize(elementWidth, elementHeight);
    endCityLineEdit->setFont(font);
    mainLayout->addWidget(endCityLineEdit, 0, Qt::AlignHCenter);

    // زر Show Path
    showPathButton = new QPushButton("Show Path");
    showPathButton->setStyleSheet("background-color: green; color: white;");
    showPathButton->setVisible(false);
    showPathButton->setEnabled(false);
    showPathButton->setFixedSize(elementWidth, elementHeight);
    showPathButton->setFont(font);
    mainLayout->addWidget(showPathButton, 0, Qt::AlignHCenter);

    // زر Display Map
    displayMapButton = new QPushButton("Display Map");
    displayMapButton->setStyleSheet("background-color: green; color: white;");
    displayMapButton->setFixedSize(elementWidth, elementHeight);
    displayMapButton->setFont(font);
    mainLayout->addWidget(displayMapButton, 0, Qt::AlignHCenter);

    // زر Add City
    addCityButton = new QPushButton("Add City");
    addCityButton->setStyleSheet("background-color: green; color: white;");
    addCityButton->setFixedSize(elementWidth, elementHeight);
    addCityButton->setFont(font);
    mainLayout->addWidget(addCityButton, 0, Qt::AlignHCenter);

    // حقل إضافة مدينة
    addCityLineEdit = new QLineEdit();
    addCityLineEdit->setPlaceholderText("Enter City Name");
    addCityLineEdit->setVisible(false);
    addCityLineEdit->setFixedSize(elementWidth, elementHeight);
    addCityLineEdit->setFont(font);
    mainLayout->addWidget(addCityLineEdit, 0, Qt::AlignHCenter);

    // زر Save City (يكون مخفيًا في البداية)
    saveCityButton = new QPushButton("Save City");
    saveCityButton->setStyleSheet("background-color: green; color: white;");
    saveCityButton->setFixedSize(elementWidth, elementHeight);
    saveCityButton->setFont(font);
    saveCityButton->setVisible(false);  // زر "Save City" مخفي
    mainLayout->addWidget(saveCityButton, 0, Qt::AlignHCenter);

    // ربط الإشارات بالأحداث
    connect(showShortestPathButton, &QPushButton::clicked, this, &Options::onShowShortestPathClicked);
    connect(showPathButton, &QPushButton::clicked, this, &Options::onShowPathClicked);
    connect(displayMapButton, &QPushButton::clicked, this, &Options::onDisplayMapClicked);
    connect(addCityButton, &QPushButton::clicked, this, &Options::onAddCityClicked);
    connect(saveCityButton, &QPushButton::clicked, this, &Options::onSaveCityClicked);  // ربط الزر هنا
}

void Options::onShowShortestPathClicked()
{
    isPathInputVisible = !isPathInputVisible;

    startCityLineEdit->setVisible(isPathInputVisible);
    endCityLineEdit->setVisible(isPathInputVisible);
    showPathButton->setVisible(isPathInputVisible);
    showPathButton->setEnabled(isPathInputVisible);

    if (isPathInputVisible) {
        showShortestPathButton->setText("Hide Path Input");
    } else {
        showShortestPathButton->setText("Show Shortest Path");
    }
}

void Options::onShowPathClicked()
{
    QString startCity = startCityLineEdit->text().trimmed();
    QString endCity = endCityLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Both cities must be entered!");
        return;
    }

    // هنا يجب عليك استخدام الكود الخاص بك لتمرير البيانات والبحث عن أقصر طريق
    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    // افترض أن لديك دالة dijkstra لتحديد أقصر طريق
    std::string result = graph.dijkstra(startCity.toStdString(), endCity.toStdString());
    QMessageBox::information(this, "Shortest Path", QString::fromStdString(result));
}

void Options::onDisplayMapClicked()
{
    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");

    if (edges.isEmpty()) {
        QMessageBox::warning(this, "File Error", "No edges were loaded from the file. Please check the file format.");
        return;
    }

    try {
        graph.addGraphFromUI(edges);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "An error occurred while adding the graph: " + QString(e.what()));
        return;
    }

    try {
        QString mapRepresentation = QString::fromStdString(graph.displayMap());
        QMessageBox::information(this, "Map Display", mapRepresentation);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "An error occurred while displaying the map: " + QString(e.what()));
    }
}

void Options::onAddCityClicked()
{
    isAddCityInputVisible = !isAddCityInputVisible;
    addCityLineEdit->setVisible(isAddCityInputVisible);
    saveCityButton->setVisible(isAddCityInputVisible);  // إظهار زر "Save City" عند الضغط على زر "Add City"

    if (isAddCityInputVisible) {
        addCityButton->setText("Hide Add City");
    } else {
        addCityButton->setText("Add City");
    }
}

void Options::onSaveCityClicked()
{
    QString cityName = addCityLineEdit->text().trimmed();

    if (!cityName.isEmpty()) {
        // تأكد من أن الجراف موجود هنا
        Graph graph;
        QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
        graph.addGraphFromUI(edges);

        // تحقق مما إذا كانت المدينة موجودة بالفعل
        bool cityExists = graph.containsCity(cityName.toStdString());  // تحقق من وجود المدينة

        if (cityExists) {
            QMessageBox::warning(this, "City Exists", "The city '" + cityName + "' already exists in the graph.");
            return;  // لا تضيف المدينة إذا كانت موجودة
        }

        // إضافة المدينة إلى الجراف بشكل صحيح
        bool cityAdded = graph.addCity(cityName.toStdString());

        if (cityAdded) {
            QMessageBox::information(this, "City Added", "City '" + cityName + "' has been saved to the graph.");

            // حفظ المدينة في الملف
            saveCityToFile(cityName);
        } else {
            QMessageBox::warning(this, "City Add Error", "Failed to add the city '" + cityName + "' to the graph.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "Please enter a city name.");
    }
}

// دالة لحفظ المدينة في الملف
void Options::saveCityToFile(const QString& cityName)
{
    QFile file("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << cityName << ", ,10\n";  // إضافة المدينة إلى الملف مع مسافة 10
    file.close();
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
            int weight = parts[2].toInt();
            edges.append(std::make_tuple(a, b, weight));
        }
    }
    return edges;
}
