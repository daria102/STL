#include<iostream>
#include <stack>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct doctor {
    string nume;
    string specializare;
    int start = 9;
    int finish = 17;
    int rezolvate = 0;
    vector<string>boli;
};


struct pacient {
    string boala;
    string specializare_necesara;
    int durata;
    int prioritate;
};
bool operator==(const pacient& p, const doctor& d)
{
    if (d.specializare == p.specializare_necesara)
        return true;
    else
        return false;
}
ifstream fin("input.txt");

int main()
{
    int nrp, nrd;
    fin >> nrp;
    vector<pacient>pacienti;
    vector<doctor>doctori;
    for (int i = 0; i < nrp; i++)
    {
        pacient p;
        fin >> p.boala >> p.specializare_necesara >> p.durata >> p.prioritate;
        pacienti.push_back(p);
    }
    fin >> nrd;
    for (int i = 0; i < nrd; i++)
    {
        doctor d;
        fin >> d.nume >> d.specializare;
        d.start = 9;
        d.finish = 17;
        doctori.emplace_back(d);
    }
    sort(pacienti.begin(), pacienti.end(), [](pacient a, pacient b) {
        return a.prioritate > b.prioritate;
        });//sortez dupa prioritate

    for (auto i : pacienti)
    {
        auto it = find_if(doctori.begin(), doctori.end(), [&i](const doctor& d) {
            if (d.specializare == i.specializare_necesara && d.start + i.durata <= d.finish)
                return 1;
            else
                return 0;
            });
        if (it != doctori.end())
        {
            (it).start += i.durata;
            (it).boli.push_back(i.boala);
            (*it).rezolvate++;
        }
    }

    for (auto i : doctori)
    {
        if (i.rezolvate > 0)
        {
            cout << i.nume << " " << i.rezolvate << " ";
            for (auto j : i.boli)
                cout << j << " ";
            cout << '\n';
        }
    }

}