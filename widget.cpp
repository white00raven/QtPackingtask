#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *lab=new QLabel("Ввод в формате size1,size2,size1,... ");
    QLabel *lab5=new QLabel("Ввод целыми в одной ед.из. без пробелов ");
     QLabel *lab6=new QLabel("Разметка с шагом в 10 ");
    QLabel *lab1=new QLabel("Введите размер листа");
    line=new QLineEdit;
    QLabel *lab2=new QLabel("Введите размер деталей");
    text1=new QTextEdit;
    QLabel *lab3=new QLabel("Вывод вставленных деталей");
    text2=new QTextEdit;
    text2->setReadOnly(true);
    QLabel *lab4=new QLabel("Вывод не вставленных деталей");
     text3=new QTextEdit;
     text3->setReadOnly(true);
    line->setMaximumSize(200,20);
    text1->setMaximumSize(200,100);
    text2->setMaximumSize(200,100);
    text3->setMaximumSize(200,100);
    QVBoxLayout *box=new QVBoxLayout;

    QPushButton *button=new QPushButton;
     QWidget::connect(button,&QPushButton::clicked,this,&Widget::slot);
     box->addWidget(lab);
     box->addWidget(lab5);
     box->addWidget(lab6);
     box->addWidget(lab1);
     box->addWidget(line);
     box->addWidget(lab2);
     box->addWidget(text1);
     box->addWidget(lab3);
     box->addWidget(text2);
     box->addWidget(lab4);
     box->addWidget(text3);
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
           painter.drawLine(230+i,20,230+i,20+it->size.second);
        }
        for(int i=10;i<it->size.second;i+=10)
        {
            painter.drawLine(230,20+i,230+it->size.first,20+i);
        }
        painter.setPen(QPen(Qt::black,3));
        for(auto it:vec)
            painter.drawRect(230+it.xy.first,20+it.xy.second,it.size.first,it.size.second);
    }
QWidget::paintEvent(event);

}

void Widget::slot()
{


    std::vector<int> v;
    std::vector<pairii>vecin,in,out;
    pairii plate;
    QString str=line->text(),st="";
    if(str.size()==0)
        return;
    for(int i=0;i<str.size();i++)
    {
        if((str[i]>='0'&&str[i]<='9' )||str[i]==',')
        {

            if(str[i]==',')
        {
            v.push_back(st.toInt());
            st="";
        }
        else
        {
            st+=str[i];
        }
        }
        else
        {
            return;
        }
    }

    if(st.size()>0)
    {
        v.push_back(st.toInt());
    }


    if((v.size()%2))
    {
        return;
    }
    plate={max(v[0],v[1]),min(v[0],v[1])};
    v.clear();

    str=text1->toPlainText();
    st="";
    for(int i=0;i<str.size();i++)
    {
        if((str[i]>='0'&&str[i]<='9' )||str[i]==',')
        {

            if(str[i]==',')
        {
            v.push_back(st.toInt());
            st="";
        }
        else
        {
            st+=str[i];
        }
        }
        else
        {
            return;
        }
    }

    if(st.size()>0)
    {
        v.push_back(st.toInt());
    }


    if((v.size()%2))
    {
        return;
    }

    for(int i=0;i<v.size();i++)
    {

        int fir=v[i],sec=v[++i];
        vecin.push_back({max(fir,sec),min(fir,sec)});
    }
    for (auto it: vecin)
        {
            if (it.second<=0 || it.second > plate.second || it.first>plate.first)
            {
                out.push_back(it);
            }
            else
            {
                in.push_back(it);
            }
        }
        sort(in.begin(), in.end(), [](const pairii& r1, const pairii& r2)
            {
                return r1.first == r2.first ? r1.second > r2.second:r1.first > r2.first;
             });
        Packing p(plate);
         vec=p.pack(plate, in, out);
         str="";
         for(auto it:vec)
         {
         str+=QString::number(it.size.first);
         str+=",";
         str+=QString::number(it.size.second);
         str+=",";
         }
         text2->setText(str);
         vec.push_back({{plate.first,plate.second},{0,0}});
        str="";
        for(auto it:out)
        {
        str+=QString::number(it.first);
        str+=",";
        str+=QString::number(it.second);
        str+=",";
        }
         text3->setText(str);
         this->resize(230+plate.first,20+ plate.second);
    this->update();
}
