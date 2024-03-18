#ifndef WIDGET_H
#define WIDGET_H
#include <vector>
#include <QWidget>
#include <map>
#include <QTextEdit>
#include <QtWidgets>
#include "Packing.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
virtual void paintEvent(QPaintEvent*)override;
private:
    QLineEdit* line;
    QTextEdit *text1,*text2,*text3;
    std::vector<arey>vec;
public slots:
    void slot();
};
#endif // WIDGET_H
