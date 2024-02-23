/* 2. Sukurti sarasa, realizuojant duomenu ivedima, iterpima pries ir po nurodyto elemento, norimo
elemento pasalinima bei didziausio elemento radima. Realizuoti funkcijas, kurios:

a. Visus skaicius nuo paskutiniojo 0 perkelia i vienkrypti ciklini sarasa.

b. Apskaičiuoja kiek cikliniame sarase esančiu elementu kurie yra didesni už dvikrypcio
saraso visu elementu vidurki.

c. Panaikina ciklinio saraso visus elementus esancios tarp treciojo ir priespaskutinio
elemento bei atspausdina juos ekrane.

Pastaba. Sioje uzduotyje galima naudoti STL bibliotekas. */

#include <iostream>
#include <list>
#include <numeric> 
#include <algorithm> 
#include <limits>


using namespace std;


void pridetiElementa(list<int>& sarasas, int elementas) {
    sarasas.push_back(elementas);
}

void isvalytiIvesti() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void duomenuIvedimas(list<int>& sarasas) {
    int elementas;
    while (true) {
        cout << "Iveskite elementa: ";
        cin >> elementas;
        if (cin.fail()) {
            isvalytiIvesti();
            break;
        }

        pridetiElementa(sarasas, elementas);
    }
}

void isvestiSarasa(const list<int>& sarasas) {

    for (int elementas : sarasas) {
        cout << elementas << " ";
    }
    cout << endl;
}


void iterptiPries(list<int>& sarasas, int nurodytasElementas, int naujasElementas) {
    auto it = find(sarasas.begin(), sarasas.end(), nurodytasElementas);

    if (it != sarasas.end()) {
        sarasas.insert(it, naujasElementas);
    }
    else {
        cout << "\033[91mElementas " << nurodytasElementas << " nerastas.\033[0m\n";
    }
}

void iterptiPo(list<int>& sarasas, int nurodytasElementas, int naujasElementas) {
    auto it = find(sarasas.begin(), sarasas.end(), nurodytasElementas);

    if (it != sarasas.end()) {
        sarasas.insert(next(it), naujasElementas);
    }
    else {
        cout << "\033[91mElementas " << nurodytasElementas << " nerastas.\033[0m\n";
    }
}

void pasalintiElementa(list<int>& sarasas, int salinamasElementas) {
    sarasas.remove(salinamasElementas);
}

int rastiDidziausia(const list<int>& sarasas) {
    if (sarasas.empty()) {
        return -1;
    }

    auto maxIt = max_element(sarasas.begin(), sarasas.end());
    return *maxIt;
}




void perkeltiElementusPoNulio(list<int>& dvikryptisSarasas, list<int>& ciklinisSarasas) {
    auto rit = find(dvikryptisSarasas.rbegin(), dvikryptisSarasas.rend(), 0);

    if (rit != dvikryptisSarasas.rend()) {

        auto it = next(rit).base();

        if (it != dvikryptisSarasas.end()) {

            ++it;
        }

        ciklinisSarasas.insert(ciklinisSarasas.end(), it, dvikryptisSarasas.end());

        cout << "\033[92mElementai po paskutiniojo 0 perkelti i ciklini sarasa, neiskaitant 0.\033[0m" << endl;
    }
    else {
        cout << "Nerasta 0. Elementai nebuvo perkelti.";
    }
}



int apskaiciuotiVidurki(const list<int>& sarasas) {
    if (sarasas.empty()) {
        return 0;
    }

    int suma = accumulate(sarasas.begin(), sarasas.end(), 0);
    int vidurkis = suma / sarasas.size();
    return vidurkis;
}

int kiekDidesniuUzVidurki(const list<int>& sarasas, int vidurkis) {
    return count_if(sarasas.begin(), sarasas.end(), [vidurkis](int elem) { return elem > vidurkis; });
}

void panaikintiTarpiniusElementus(list<int>& sarasas) {
    cout << "Pradinis ciklinio saraso turinys: ";
    isvestiSarasa(sarasas);

    if (sarasas.size() > 3) {
        auto pradzia = next(sarasas.begin(), 2);
        auto pabaiga = prev(sarasas.end(), 2);

        sarasas.erase(next(pradzia), pabaiga);

        cout << "Tarp treciojo ir priespaskutinio elemento esantys elementai buvo panaikinti.\n";
    }
    else {
        cout << "Sarase per mazai elementu, kad butu galima panaikinti elementus.\n";
    }

    cout << "Atnaujintas ciklinio saraso turinys: ";
    isvestiSarasa(sarasas);
}


void rodytiPagrindiniMeniu() {
    cout << "\n\033[96m***********************************\033[0m\n";
    cout << "\033[96m*     Dvikrypcio Saraso Meniu     *\033[0m\n";
    cout << "\033[96m***********************************\033[0m\n";
    cout << "\033[93mElementu manipuliavimas:\033[0m\n";
    cout << "  \033[92m1. Iterpti elementa pries nurodyta\033[0m\n";
    cout << "  \033[92m2. Iterpti elementa po nurodytu\033[0m\n";
    cout << "  \033[92m3. Pasalinti elementa\033[0m\n";
    cout << "  \033[92m4. Rasti didziausia elementa sarase\033[0m\n";
    cout << "\033[93mSpecialios uzduotys:\033[0m\n";
    cout << "  \033[92m5. Perkelti elementus po paskutiniojo 0 i ciklini sarasa\033[0m\n";
    cout << "  \033[92m6. Apskaiciuoja kiek cikliniame sarase esanciu elementu kurie yra didesni uz dvikrypcio saraso visu elementu vidurki.\033[0m\n";
    cout << "  \033[92m7. Panaikinti elementus tarp treciojo ir priespaskutinio cikliniame sarase\033[0m\n";
    cout << "\033[91m8. Baigti darba\033[0m\n\n";
    cout << "\033[97mJUSU PASIRINKIMAS:\033[0m ";
}

void IsvalytiEkrana() {
    system("cls");
}

void AtnaujintiSarasus(list<int>& dvikryptisSarasas, list<int>& ciklinisSarasas) {
    cout << endl;
    cout << "\033[96mDvikryptis Sarasas:\033[0m ";
    if (!dvikryptisSarasas.empty()) {
        isvestiSarasa(dvikryptisSarasas);
    }
    else {
        cout << "(tuscias)" << endl;
    }
    cout << "\033[96mCiklinis Sarasas:\033[0m ";
    if (!ciklinisSarasas.empty()) {
        isvestiSarasa(ciklinisSarasas);
    }
    else {
        cout << "(tuscias)" << endl;
    }
    cout << endl;
}


void lauktiVartotojo() {
    cout << "\nPaspauskite bet kuri klavisa norint testi...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    list<int> dvikryptisSarasas;
    list<int> ciklinisSarasas;
    int pasirinkimas;

    AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
    cout << "Dabar iveskite dvikrypcio saraso elementus. Ivedus ne skaiciu, duomenu ivedimas bus baigtas." << endl;
    duomenuIvedimas(dvikryptisSarasas);

    do {
        IsvalytiEkrana();
        AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
        rodytiPagrindiniMeniu();
        cin >> pasirinkimas;

        if (pasirinkimas == 1) {
            int nurodytasElementas, naujasElementas;
            cout << "\033[93mIveskite elementa, pries kuri norite iterpti nauja elementa:\033[0m ";
            cin >> nurodytasElementas;
            cout << "\033[93mIveskite nauja elementa:\033[0m ";
            cin >> naujasElementas;

            iterptiPries(dvikryptisSarasas, nurodytasElementas, naujasElementas);
            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }
        if (pasirinkimas == 2) {
            int nurodytasElementas, naujasElementas;
            cout << "\033[93mIveskite elementa, po kurio norite iterpti nauja elementa:\033[0m ";
            cin >> nurodytasElementas;
            cout << "\033[93mIveskite nauja elementa:\033[0m ";
            cin >> naujasElementas;

            iterptiPo(dvikryptisSarasas, nurodytasElementas, naujasElementas);
            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }
        if (pasirinkimas == 3) {
            int salinamasElementas;
            cout << "\033[93mIveskite elementa, kuri norite pasalinti:\033[0m ";
            cin >> salinamasElementas;

            pasalintiElementa(dvikryptisSarasas, salinamasElementas);
            cout << "\033[92mElementai su reiksme " << salinamasElementas << " buvo pasalinti.\033[0m" << endl;

            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }

        if (pasirinkimas == 4) {
            int didziausias = rastiDidziausia(dvikryptisSarasas);
            if (didziausias != -1) {
                cout << "\033[92mDidziausias elementas ssra�e yra: \033[0m" << didziausias << endl;
            }
            else {
                cout << "\033[91mSarasas tuscias.\033[0m" << endl;
            }
            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }

        if (pasirinkimas == 5) {
            perkeltiElementusPoNulio(dvikryptisSarasas, ciklinisSarasas);
            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }

        if (pasirinkimas == 6) {
            int vidurkis = apskaiciuotiVidurki(dvikryptisSarasas);
            int didesniuUzVidurkiSkaicius = kiekDidesniuUzVidurki(ciklinisSarasas, vidurkis);

            cout << "\033[92mCikliniame sarase elementu skaicius, kurie yra didesni uz dvikrypcio saraso vidurki (" << vidurkis << "), yra: \033[0m" << didesniuUzVidurkiSkaicius << endl;
            lauktiVartotojo();
        }

        if (pasirinkimas == 7) {
            panaikintiTarpiniusElementus(ciklinisSarasas);
            AtnaujintiSarasus(dvikryptisSarasas, ciklinisSarasas);
            lauktiVartotojo();
        }


    } while (pasirinkimas != 8);

    cout << endl << "Programa baigiama..." << endl;
    return 0;
}
