#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;
// this is the main function

struct problems {
    string problema;
    string specialitateNecesara;
    int durata;
    int prioritate;
    int oraSosire;

    bool operator<(const problems& b) const {
        if (oraSosire != b.oraSosire)
            return oraSosire > b.oraSosire;
        return prioritate < b.prioritate;
    }
};

struct doctors {
    string nume;
    //string specializare;
    int inceput = 9;
    int sfarsit = 17;
    int nrSpecializari;
    vector<pair<string, int>> problemeRezolvate;
    vector<string> listaSpecializari;
};

struct comparator {

};

int main()
{
    ifstream inFile("input2.txt");

    int no_problems, no_doctors;
    string name, speciality;
    int duration, priority, ora;

    inFile >> no_problems;
    priority_queue<problems> probleme;
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> ora;
        inFile >> duration;
        inFile >> priority;
        problems problema;
        problema.durata = duration;
        problema.prioritate = priority;
        problema.specialitateNecesara = speciality;
        problema.problema = name;
        problema.oraSosire = ora;
        probleme.push(problema);
    }

    inFile >> no_doctors;
    int nr;
    vector<doctors> doctori(no_doctors);

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> nr;
        for (int j = 0; j < nr; j++)
        {
            inFile >> speciality;
            doctori[i].listaSpecializari.emplace_back(speciality);
        }

        doctori[i].nume = name;
    }

    while (!probleme.empty())
    {
        problems Problema = probleme.top();
        probleme.pop();

        auto it = find_if(doctori.begin(), doctori.end(), [&](doctors& x) {
            for (auto& a : x.listaSpecializari)
            {
                if (a == Problema.specialitateNecesara && x.inceput + Problema.durata <= x.sfarsit && x.inceput <= Problema.oraSosire)
                {
                    x.inceput = Problema.oraSosire + Problema.durata;
                    x.problemeRezolvate.push_back({ Problema.problema, Problema.oraSosire });
                    return true;
                }
            }

            return false;
            });

        /* if (it != doctori.end())
         {
             (*it).inceput = Problema.oraSosire + Problema.durata;

         }*/
    }

    for (auto& i : doctori)
    {
        if (!i.problemeRezolvate.empty())
        {
            cout << i.nume << " " << i.problemeRezolvate.size() << " ";
            for (auto& j : i.problemeRezolvate)
            {
                cout << j.first << " " << j.second << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}