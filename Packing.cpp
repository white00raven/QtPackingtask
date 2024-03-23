#include "Packing.h"

Packing::Packing(const pairii& t) : plate(t)
{

    map<int, pairii> td;
    td.insert(pair<int, pairii>({ 0, t }));
    data[0] = td;
    datas[0] = td;
    mapxy.emplace(0, 0);
}
//проверка возможности вставки
bool Packing::check(const pairii& coord, const pairii& size)
{
    int x = plate.first, y, sizey = 0;
    auto it = datas.find(coord.second);
    y = it->first;
    for (; it != datas.end(); it++)
    {
        if (y != it->first && y < size.second)
            return false;
        auto i = it->second.upper_bound(coord.first);
        if (i == it->second.begin())
        {
            return false;
        }
        i--;
        if (x > i->second.first - (coord.first - i->first))
        {
            x = i->second.first - (coord.first - i->first);
        }
        y += i->second.second;
        sizey += i->second.second;
        if (x < size.first)
        {
            return false;
        }
        if (x >= size.first && sizey >= size.second)
        {
            return true;
        }



    }
    return false;

    
}

//функци€ вставки деталей в лист 
vector<arey> Packing::pack(const pairii& plate, const vector<pairii>& vec,  vector<pairii>& vecout)
{
    vector<arey> ret;
    for (auto it : vec)
    {
        int minx = plate.first,miny=plate.second;
        arey minarey{ {-1,-1},{-1,-1} };
        for (auto j = mapxy.begin(); j != mapxy.end() ; j++)
        {
            if (check({ j->first,j->second }, it))
            {
                if ((j->first + it.first) < minx)
                {
                    minx = j->first + it.first;
                    miny = j->second + it.second;
                    minarey = arey{ it, {j->first,j->second } };
                }
                else 
                {
                    if ((j->first + it.first) == minx && (j->second + it.second) < miny)
                    {
                        miny = j->second + it.second;
                        minarey = arey{ it, {j->first,j->second } };
                    }
                }
            }
            if (it.second != it.first&&check({ j->first,j->second }, { it.second,it.first }))
            {
                if ((j->first + it.second) < minx)
                {
                    minx = j->first + it.second;
                    miny = j->second + it.first;
                    minarey = arey{ {it.second,it.first}, {j->first,j->second } };
                }
                else 
                {
                    if ((j->first + it.second) == minx && (j->second + it.first) < miny)
                    {
                        miny = j->second + it.first;
                        minarey = arey{ {it.second,it.first}, {j->first,j->second } };
                    }
                }
            }

        }

        if (minarey.xy.first == -1)
        {
            vecout.push_back(it);
        }
        else
        {
            ret.push_back(minarey);
            insert(minarey);

        }

    }
    return ret;
}


//вставка элемента и сопутствующие операции
void Packing::insert(const arey& ar)
{
    vector<pairii> vecdel;
    vector<pair<pairii, pairii>> vecin;
    auto it = data.find(ar.xy.second);
    //удал€ем все €чейки внутри выделенной области и добавл€ем новые €чейки которые обрезались
    for (; it != data.end() && (it->first + it->second.begin()->second.second) < (ar.xy.second + ar.size.second); it++)
    {
        auto i = it->second.find(ar.xy.first);
        for (; i != it->second.end() && (i->first + i->second.first) <= (ar.xy.first + ar.size.first); i++)
        {
            
            vecdel.push_back({ it->first,i->first });
            
        }

        i = it->second.upper_bound(ar.xy.first + ar.size.first);

        if (i != it->second.end() && i->first != (ar.xy.first + ar.size.first))
        {
            i--;
            vecin.push_back({ {it->first,ar.xy.first + ar.size.first},
    { i->second.first - (ar.xy.first + ar.size.first - i->first),i->second.second} });

            vecdel.push_back({ it->first,i->first });
        }
        else
        {

            i--;
            if (i->first != (ar.xy.first + ar.size.first))
            {
                vecin.push_back({ {it->first,ar.xy.first + ar.size.first},
        { i->second.first - (ar.xy.first + ar.size.first - i->first),i->second.second} });

                vecdel.push_back({ it->first,i->first });
            }


        }
       
    }

    if ((it->first + it->second.begin()->second.second) > (ar.xy.second + ar.size.second)) {
        auto i = it->second.find(ar.xy.first);
        int x = 0;// i->first;
        for (; i != it->second.end(); i++)
        {
            x += i->second.first;
            if (x >= ar.size.first)
            {
                vecdel.push_back({ it->first,i->first });
                if (x != ar.size.first)
                {
                    vecin.push_back({ {ar.xy.second + ar.size.second,i->first},
                        {ar.size.first - (i->first - ar.xy.first),
                        (it->first + i->second.second) - (ar.xy.second + ar.size.second)} });

                    vecin.push_back({ {it->first,ar.xy.first + ar.size.first },
                        { (i->second.first + i->first) - (ar.size.first + ar.xy.first),
                        (ar.xy.second + ar.size.second) - it->first} });

                    vecin.push_back({ {ar.xy.second + ar.size.second,ar.xy.first + ar.size.first },
                        { (i->second.first + i->first) - (ar.size.first + ar.xy.first),
                       (it->first + i->second.second) - (ar.xy.second + ar.size.second)} });
                }
                else
                {
                    vecin.push_back({ {ar.xy.second + ar.size.second,i->first}
                ,{i->second.first,i->second.second - (ar.xy.second + ar.size.second - (it->first))} });
                }
                break;
            }
            else
            {
                vecin.push_back({ {ar.xy.second + ar.size.second,i->first}
                ,{i->second.first,i->second.second - (ar.xy.second + ar.size.second - (it->first))} });
                vecdel.push_back({ it->first,i->first });
            }
        }
    }
    else
    {
       
        if (it->first + it->second.begin()->second.second == (ar.xy.second + ar.size.second)) {
            
            for (auto i = it->second.find(ar.xy.first); i != it->second.end() && (i->first + i->second.first) <= (ar.xy.first + ar.size.first); i++)
            {
               
                vecdel.push_back({ it->first,i->first });
               
            }
            auto i = it->second.upper_bound(ar.xy.first + ar.size.first);
            if (i != it->second.end() && i->first != (ar.xy.first + ar.size.first))
            {
                i--;
                vecin.push_back({ {it->first,ar.xy.first + ar.size.first},
        { i->second.first - (ar.xy.first + ar.size.first - i->first),i->second.second} });

                vecdel.push_back({ it->first,i->first });
            }
            else
            {

                i--;
                if (i->first != (ar.xy.first + ar.size.first))
                {
                    vecin.push_back({ {it->first,ar.xy.first + ar.size.first},
            { i->second.first - (ar.xy.first + ar.size.first - i->first),i->second.second} });

                    vecdel.push_back({ it->first,i->first });
                }

            }
        }
    }


    //разделение €чеек 
    //по x
    for (auto it : data)
    {
        auto i = it.second.upper_bound(ar.xy.first + ar.size.first);

        if (i != it.second.begin())
        {
            i--;
            if (find(vecdel.begin(), vecdel.end(), pairii({ it.first,i->first })) == vecdel.end() &&
                it.second.find(ar.xy.first + ar.size.first) == it.second.end()) {

                vecin.push_back({ {it.first,i->first }, { ar.xy.first + ar.size.first - i->first,i->second.second } });

                vecin.push_back({ {it.first,ar.xy.first + ar.size.first},
{ i->second.first - (ar.xy.first + ar.size.first - i->first),i->second.second} });

                vecdel.push_back({ it.first,i->first });
            }
        }

    }
    //по y
    
    it = --(data.upper_bound(ar.xy.second + ar.size.second));

    for (auto i = it->second.begin(); i != it->second.end(); i++)
    {
        if (find(vecdel.begin(), vecdel.end(), pairii({ it->first,i->first })) == vecdel.end()) {

            vecin.push_back({ {ar.xy.second + ar.size.second,i->first},
    { i->second.first,
                (i->second.second + it->first) - (ar.xy.second + ar.size.second)} });

            vecin.push_back({ {it->first,i->first }, { i->second.first,ar.xy.second + ar.size.second - it->first } });

            vecdel.push_back({ it->first,i->first });
        }

    }
   //удаление €чеек
    for (auto j : vecdel)
    {
        data[j.first].erase(j.second);
        if (data[j.first].empty())
        {
            data.erase(j.first);
        }
    }
    sort(vecin.begin(), vecin.end(), [](pair<pairii, pairii> l, pair<pairii, pairii> r)
        {
            return l.first.first == r.first.first ? l.first.second < r.first.second : l.first.first < r.first.first;
        });
    //вставка новых
    int y = vecin.begin()->first.first;
    map<int, pairii> td;
    for (auto i : vecin)
    {
        if (i.first.first == plate.second)
            break;
        if (y == i.first.first) {
            td.insert(pair<int, pairii>({ i.first.second,i.second }));
        }
        else
        {
            data[y].insert(td.begin(), td.end());
            td.clear();
            y = i.first.first;
            td.insert(pair<int, pairii>({ i.first.second,i.second }));
        }

    }
    if (!td.empty())
    {
        data[y].insert(td.begin(), td.end());
    }

    //соединение р€дом сто€щих €чеек
    datas.clear();
    mapxy.clear();
    for (auto it : data)
    {
        map<int, pairii> tempm;
        int x, size = 0;
        auto j = it.second.begin();
        x = j->first;
        for (; j != it.second.end(); j++)
        {
            mapxy.insert(pairii(j->first, it.first));
            if (x + size != j->first)
            {
                tempm.insert({ x,{size,j->second.second } });
                size = j->second.first;
                x = j->first;
            }
            else
            {
                size += j->second.first;
            }
        }
        if (size > 0)
        {
            tempm.insert({ x,{size,it.second.begin()->second.second} });
        }
        datas[it.first] = tempm;

    }

}
