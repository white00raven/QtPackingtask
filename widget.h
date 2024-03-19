#ifndef WIDGET_H
#define WIDGET_H
#include <vector>
#include <QWidget>
#include <map>
#include <QTextEdit>
#include <QtWidgets>
#include "Packing.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
virtual void paintEvent(QPaintEvent*)override;
private:
    QLineEdit *linef,*lines;
    QTableWidget *table;
    QTextEdit *text1,*text2;
    std::vector<arey>vec;
    int countrow=100;
public slots:
    void slot();
};
#endif // WIDGET_H
