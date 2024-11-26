#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Doctor
{
    std::string name;
    std::string speciality;
    int start = 9;
    int finish = 17;
    int solved_problems = 0;
    vector<string>boli;
};
struct Pacient
{
    std::string name;
    std::string disease;
    int time_to_fix;
    int priority_number;
};

bool operator==(const Pacient& p1, const Doctor& d2) {
    if (p1.disease == d2.speciality) {
        return true;
    }
    else return false;
}

int main()
{
    std::ifstream inFile("input.txt");

    int no_problems, no_doctors, time_to_solve, nr_prioritate;
    std::string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;
        inFile >> time_to_solve;
        inFile >> nr_prioritate;
        Pacient p;
        p.name = name;
        p.disease = speciality;
        p.time_to_fix = time_to_solve;
        p.priority_number = nr_prioritate;
        pacients.emplace_back(p);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++) {
        inFile >> name;
        inFile >> speciality;

        Doctor d;
        d.name = name;
        d.speciality = speciality;
        d.start = 9;
        d.finish = 17;
        doctors.emplace_back(d);
    }
    /// sortam in functie de prioritate
    sort(pacients.begin(), pacients.end(), [](Pacient a, Pacient b) {
        return a.priority_number > b.priority_number;
        });
    for (auto& pacient : pacients) {
        auto it = find_if(doctors.begin(), doctors.end(), [&pacient](const Doctor& doc) {
            if (doc.speciality == pacient.disease and doc.start+pacient.time_to_fix<=doc.finish)
                return true;
            else 
                return false;
            });

        if (it != doctors.end()) {
            (*it).start += pacient.time_to_fix;
            (*it).solved_problems++;
            (*it).boli.emplace_back(pacient.name);
        }
    }
    for (auto doc : doctors)
    {
        if (doc.solved_problems != 0)
        {
            cout << doc.name << " " << doc.solved_problems << " ";
            for (auto boala : doc.boli)
            {
                cout << boala << " ";
            }
            cout << '\n';
        }
    }
    return 0;
}