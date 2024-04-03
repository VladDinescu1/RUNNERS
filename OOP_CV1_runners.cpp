
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;


class Alergator {
protected:
    string ID;
    double greutate;
    double energie;
    double distanta;
public:
    Alergator(string ID, double greutate, double energie) {
        this->ID = ID;
        this->greutate = greutate;
        this->energie = energie;
        distanta = 0;
    }
    virtual void prelucrare() = 0;
    virtual string nume() = 0;
    virtual double eenergie() = 0;
    virtual double ddistanta() = 0;
};

class Maratonist :public Alergator {
public:
    Maratonist(string ID, double greutate, double energie) :Alergator(ID, greutate, energie) {};
    void prelucrare() {
        if (energie >= 1)
        {
            double deltadistanta = exp(40 / greutate) + energie * 2.0;
            double deltaenergie = sqrt(deltadistanta) / 3.0;
            distanta += deltadistanta;
            energie -= deltaenergie;
            if (energie < 0)
                energie = 0;
            /*double l= energie * 1000;
            int rot = l;
            if (rot % 10 >= 5) {
                int y = 10 - rot % 10;
                energie = energie + (double)y / 1000;
            }
            else
            {
                int y = 10 - rot % 10;
                energie = energie - (double)y / 1000;
            }*/
        }
        else
            energie += 2;
    }
    double ddistanta() {
        return distanta;
    }
    double eenergie() {
        return energie;
    }
    string nume() {
        return ID;
    }
};

class Sprinter :public Alergator {
public:
    Sprinter(string ID, double greutate, double energie) :Alergator(ID, greutate, energie) {};

    void prelucrare() {
        if (energie >= 1)
        {
            double deltadistanta = 100.0 / greutate + energie * 3.0;
            double deltaenergie = deltadistanta / 10.0;
            distanta += deltadistanta;
            energie -= deltaenergie;
            if (energie < 0)
                energie = 0;
        }
        else
            energie += 1.5;
    }
    double ddistanta() {
        return distanta;
    };
    double eenergie() {
        return energie;
    }
    string nume() {
        return ID;
    };
};

int main()
{
    vector<Alergator*> participanti;

    string x, ID;
    double greutate, energie;
    int N; cin >> N;
    string* tipalergator = new string[N];
    for (int i = 0; i < N; i++)
    {
        cin >> x >> ID >> greutate >> energie;
        if (x == "SPRINTER") {
            participanti.push_back(new Sprinter(ID, greutate, energie));
            tipalergator[i] = "SPRINTER";
        }
        else if (x == "MARATONIST") {
            participanti.push_back(new Maratonist(ID, greutate, energie));
            tipalergator[i] = "MARATONIST";
        }
    }

    ///////////SUBIECTUL 1///////////
    /*double max = 0;
    int z=0;
    for (int i = 0; i < N; i++)
    {
        participanti[i]->prelucrare();
        if (participanti[i]->ddistanta() > max)
        {
            max = participanti[i]->ddistanta();
            z = i;
        }
    }
    cout << participanti[z]->nume();*/
    //////////////////////////////////


    //////////SUBIECTUL 2/////////////

    int* V = new int[N];
    for (int i = 0; i < N; i++)
    {
        V[i] = 1;
    }
    int K; cin >> K;
    bool g = 1;
    double min = (double)INT_MAX;
    while (K) {
        if (g == 0) {
            for (int i = 0; i < N; i++) {
                if (tipalergator[i] == "MARATONIST")
                {
                    if (participanti[i]->ddistanta() < min)
                        min = participanti[i]->ddistanta();
                }
            }
            cout << min << endl;
            for (int i = 0; i < N; i++)
            {
                if (tipalergator[i] == "SPRINTER")
                    if (participanti[i]->ddistanta() < min)
                    {
                        V[i] = 0;
                    }

            }
        }
        for (int i = 0; i < N; i++) {
            participanti[i]->prelucrare();
            cout << participanti[i]->nume() << ":" << participanti[i]->ddistanta() << " " << participanti[i]->eenergie() << endl;
        }
        cout << endl;
        g = 0;
        min = INT_MAX;
        K--;
    }
    double max = 0;
    int h = 0;
    for (int i = 0; i < N; i++) {
        if (V[i] == 1)
        {
            if (participanti[i]->eenergie() > max)
            {
                max = participanti[i]->eenergie();
                h = i;
            }
        }
    }

    cout << participanti[h]->nume();
    delete[]V;
    V = nullptr;
    //////////////////////////////////


    return 0;
}


