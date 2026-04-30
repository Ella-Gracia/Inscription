#include <vector>
#include <iostream>
#include "Person.h"

using namespace std;
class Inscription
{
    private:
        vector<Person> personName;
    public:
        Inscription();
        ~Inscription();
        void inscrire(Person& person);
        void desabonner(Person& person);
        void search(Person& person);
        void lister();
};