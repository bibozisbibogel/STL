#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
struct doctors {
    string nume;
    int nr_specializari = 0;
    int start = 9;
    int finish = 17;
    vector<string>specializari;
    vector<pair<string, int>>boli;
    int pacienti_rezolvati = 0;
};
struct problems {
    string problema;
    string specialitateNecesara;
    int durata;
    int priority_number;
    int ora_sosire;
};
/// overloaded function
bool operator==(const problems& p, const doctors& d)
{
    for (auto& specializare : d.specializari) {
        if (p.specialitateNecesara == specializare)
            return 1;
    }
    return 0;
}
int main(){
    vector<problems> probleme;
    vector<doctors> doctori;
    ifstream inFile("input4_bonus.txt");
    int no_problems, no_doctors, arrival_time,nr_prioritate,duration;
    string name, speciality;
    inFile >> no_problems;
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> arrival_time;
        inFile >> duration;
        inFile >> nr_prioritate;
        probleme.emplace_back(name, speciality,duration,nr_prioritate,arrival_time);
    }
    int specializarile_doctorului;
    inFile >> no_doctors;
    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> specializarile_doctorului;
        int incepere = 9;
        int terminare = 17;
        vector<string>Specializare_Doctor;
        Specializare_Doctor.clear();
        for (int j = 0; j < specializarile_doctorului; j++)
        {
            string numele_domeniului;
            inFile >> numele_domeniului;
            Specializare_Doctor.emplace_back(numele_domeniului);
        }
        doctori.emplace_back(name, specializarile_doctorului, incepere, terminare, Specializare_Doctor);
    }
    /// sortam dupa ora_sosire si daca sunt egale, sortam dupa prioritate (Descrescator)
    sort(probleme.begin(), probleme.end(), [](problems a, problems b)
        {
            if (a.ora_sosire != b.ora_sosire)
                return a.ora_sosire < b.ora_sosire;
            return a.priority_number > b.priority_number;
        });
    for (auto& pacient : probleme)
    {
        auto it = find_if(doctori.begin(), doctori.end(), [&pacient](const doctors& d) {
            if (d.start <= pacient.ora_sosire && pacient.ora_sosire + pacient.durata <= d.finish) // are timp
            {
                for (int k = 0; k < d.nr_specializari; k++)
                {
                    if (d.specializari[k] == pacient.specialitateNecesara)
                        return 1;
                }
            }
            return 0;
            });
        if (it != doctori.end()) // am gasit
        {
            (*it).start = pacient.ora_sosire + pacient.durata;
            (*it).pacienti_rezolvati++;
            (*it).boli.emplace_back(pacient.problema, pacient.ora_sosire);
        }
    }
    for (auto& d : doctori)
    {
        if (d.pacienti_rezolvati != 0)
        {
            cout << d.nume << " " << d.pacienti_rezolvati << " ";
            for (auto& pereche : d.boli)
            {
                cout << pereche.first << " " << pereche.second << " ";
            }
            cout << '\n';
        }
    }
    return 0;
}
