#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <tuple>
#include "graph.h"
#include "Options.h"  // ✅ تضمين ملف نافذة Options

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);

private slots:
    void onSubmitEdgeCount();     // دالة للتعامل مع الضغط على زر Submit
    void onSaveClicked();         // دالة لحفظ البيانات
    void onContinueClicked();     // دالة للانتقال إلى الصفحة التالية (فتح نافذة Options)

private:
    void saveGraphData(const QVector<std::tuple<QString, QString, int>> &edges);  // دالة لحفظ البيانات في الملف

    QLineEdit *edgeCountField;       // حقل إدخال عدد الحواف
    QVBoxLayout *inputsLayout;        // تخطيط إدخال البيانات
    QScrollArea *scrollArea;         // منطقة التمرير لإدخال الحواف

    QPushButton *submitButton;       // زر Submit
    QPushButton *saveButton;         // زر حفظ البيانات
    QPushButton *continueButton;     // زر الاستمرار

    struct EdgeInput {
        QLineEdit *cityA;           // حقل إدخال المدينة A
        QLineEdit *cityB;           // حقل إدخال المدينة B
        QLineEdit *distance;        // حقل إدخال المسافة
    };

    QVector<EdgeInput> edgeInputs;   // لتخزين الحواف المدخلة

    Graph graph;  // كائن من كلاس Graph (يفترض أنك قمت بتعريف هذا الكلاس)
};

#endif // MAP_H
