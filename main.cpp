#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
struct doctors {
    string nume;
    string specializare;
};
struct problems {
    string problema;
    string specialitateNecesara;
};
/// overloaded function
bool operator==(const problems& p, const doctors& d)
{
    return p.specialitateNecesara == d.specializare;
}
int main()
{

    vector<problems> probleme;
    vector<doctors> doctori;
    ifstream inFile("input.txt");
    int no_problems, no_doctors;
    string name, speciality;
    inFile >> no_problems;
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        probleme.emplace_back(name, speciality);
    }
    inFile >> no_doctors;
    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        doctori.emplace_back(name, speciality);
    }

    for (auto& i : probleme)
    {
        auto it = find(doctori.begin(), doctori.end(), i);
        if (it == doctori.end())
            cout << i.problema << " " << "Respins\n";
        else
            cout << i.problema << " " << "Acceptat\n";
    }
    return 0;
}