#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
using pairii = pair<int, int>;
struct arey
{
    pairii size, xy;
    arey(const pairii& t1, const pairii& t2) :size(t1), xy(t2) {};
};

class Packing
{ 
    //����������� �� y ����� ��  x ������ ��������� ������� ��� ������� 
    map<int, map<int, pairii>> data;
    map<int, map<int, pairii>> datas;
    //����������� �� x ������ y ����������� ������ �� x
    multimap<int, int> mapxy;
    pairii plate;

    //�������� ����������� �������
    bool check(const pairii&, const pairii&);
    //������� 
    void insert(const arey&);

public:
    Packing(const pairii& p);
    vector<arey> pack(const pairii&, const vector<pairii>&, vector<pairii>&);
};

