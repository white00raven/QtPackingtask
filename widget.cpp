#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *lab5=new QLabel("Ввод целыми в одной ед.из. ");
     QLabel *lab6=new QLabel("Разметка с шагом в 10 ");
    QLabel *lab1=new QLabel("Введите размер листа");
    linef=new QLineEdit;
    lines=new QLineEdit;
    QLabel *lab7=new QLabel("Введите количество строк ввода");
    linecou=new QLineEdit;
     QPushButton *button2=new QPushButton("ввод");
      QWidget::connect(button2,&QPushButton::clicked,this,&Widget::setcount);
    QLabel *lab2=new QLabel("Введите размер деталей(1,2) и их количество(3)");
    table=new QTableWidget(0,3);
    QLabel *lab3=new QLabel("Вывод вставленных деталей");
    text1=new QTextEdit;
    text1->setReadOnly(true);
    QLabel *lab4=new QLabel("Вывод не вставленных деталей");
     text2=new QTextEdit;
     text2->setReadOnly(true);
    linef->setMaximumSize(240,20);
    lines->setMaximumSize(240,20);
    linecou->setMaximumSize(240,20);
    text1->setMaximumSize(240,100);
    text2->setMaximumSize(240,100);
    table->setMaximumSize(240,100);
    QVBoxLayout *box=new QVBoxLayout;

    QPushButton *button=new QPushButton("Старт");
     QWidget::connect(button,&QPushButton::clicked,this,&Widget::slot);
     box->addWidget(lab5);
     box->addWidget(lab6);
     box->addWidget(lab1);
     box->addWidget(linef);
     box->addWidget(lines);
     box->addWidget(lab7);
     box->addWidget(linecou);
     box->addWidget(button2);
     box->addWidget(lab2);
     box->addWidget(table);
     box->addWidget(lab3);
     box->addWidget(text1);
     box->addWidget(lab4);
     box->addWidget(text2);
     box->addWidget(button);

     box->setAlignment(Qt::AlignTop);
   this->setLayout(box);
}

Widget::~Widget()
{


}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!vec.empty())
    {


        auto it=--vec.end();
        painter.setPen(QPen(Qt::red));
        for(int i=10;i<it->size.first;i+=10)
        {
           painter.drawLine(270+i,20,270+i,20+it->size.second);
        }
        for(int i=10;i<it->size.second;i+=10)
        {
            painter.drawLine(270,20+i,270+it->size.first,20+i);
        }
        painter.setPen(QPen(Qt::black,3));
        for(auto it:vec)
            painter.drawRect(270+it.xy.first,20+it.xy.second,it.size.first,it.size.second);
    }
QWidget::paintEvent(event);

}

void Widget::slot()
{
    std::vector<pairii>in,out;
    pairii plate;
    QString str1="",str2="";

    str1=linef->text();
    str2=lines->text();
    if(str1.size()==0 || str2.size()==0)
        return;
    int fir=str1.toUInt(),sec=str2.toUInt();
    plate={max(fir,sec),min(fir,sec)};

    for(int i=0;i<table->rowCount();i++)
    {
        if(table->item(i,0)==0 || table->item(i,1)==0 || table->item(i,2)==0)
            break;
        str1=table->item(i,0)->text();
        str2=table->item(i,1)->text();

         fir=str1.toInt(),sec=str2.toInt();
         int col=table->item(i,2)->text().toUInt();


             if (min(fir,sec)<=0 || min(fir,sec) > plate.second || max(fir,sec)>plate.first)
         {
                 for(int i=0; i<col;i++)
                     {
                     out.push_back({fir,sec});
                      }
         }
         else
         {
                 for(int i=0; i<col;i++)
                                  {
                                   in.push_back({max(fir,sec),min(fir,sec)});
                                   }
         }

    }
        sort(in.begin(), in.end(), [](const pairii& r1, const pairii& r2)
            {
                return r1.first == r2.first ? r1.second > r2.second:r1.first > r2.first;
             });
        Packing p(plate);
         vec=p.pack(plate, in, out);
         str1="";
         for(auto it:vec)
         {
         str1+="(";
         str1+=QString::number(it.size.first);
         str1+=",";
         str1+=QString::number(it.size.second);
         str1+=")";
         str1+=",";
         }
         text1->setText(str1);
         vec.push_back({{plate.first,plate.second},{0,0}});
        str1="";
        for(auto it:out)
        {
            str1+="(";
        str1+=QString::number(it.first);
        str1+=",";
        str1+=QString::number(it.second);
        str1+=")";
        str1+=",";
        }
         text2->setText(str1);
         this->showNormal();
         this->resize(270+plate.first,20+ plate.second);
    this->update();
}

void Widget::setcount()
{
    QString str=linecou->text();
    if(str.size()>0)
    {
        table->setRowCount(str.toUInt());
    }
}
