#include "Inscription.h"
#include <algorithm>

using namespace std;
Inscription::Inscription(){}
Inscription::~Inscription(){}
void Inscription::inscrire(Person& person)
{
    personName.push_back(person);
}
void Inscription::desabonner(Person& person)
{
    auto p = find(personName.begin(), personName.end(), person);
    personName.erase(p);
}
void Inscription::lister()
{
    cout << "Liste des personnes inscrites :" << endl;
    for (vector<Person>::iterator i = personName.begin(); i != personName.end(); ++i)
    {
        cout << i->getName() << endl;
    }
}
void Inscription::search(Person& person)
{
    auto p = find(personName.begin(), personName.end(), person);
    if (p == personName.end())
    {
        cout << person.getName() << " n'est pas inscrit(e)" << endl;
        return;
    }
    cout << p->getName() << " est inscrit(e)" << endl;
}