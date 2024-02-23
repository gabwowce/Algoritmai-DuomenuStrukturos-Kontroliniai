/* 2. Sukurti sàraðà, realizuojant duomenø ávedimà, áterpimà prieð ir po nurodyto elemento, norimo
elemento paðalinimà bei didþiausio elemento radimà. Realizuoti funkcijas, kurios:

	a. Visus skaièius nuo paskutiniojo 0 perkelia á vienkryptá cikliná sàraðà.

	b. Apskaièiuoja kiek cikliniame sàraðe esanèiø elementø kurie yra didesná uþ dvikrypèio
	sàraðo visø elementø vidurká.

	c. Panaikina ciklinio sàraðo visus elementus esanèios tarp treèiojo ir prieðpaskutinio
	elemento bei atspausdina juos ekrane.

Pastaba. Ðioje uþduotyje galima naudoti STL bibliotekas. */

#include <iostream>
#include <list>
#include <numeric> 
#include <algorithm> 
#include <limits>


using namespace std;

list<int> ciklinisSarasas;

void isvalytiIvesti() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}



void pridetiElementa(list<int>& sarasas, int elementas) {
    sarasas.push_back(elementas);
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
    if (sarasas.empty()) {
        cout << "\033[93mSarasas yra tuscias.\033[0m" << endl;
        return;
    }

    cout << "\033[92mDabartinis sarasas:\033[0m ";
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
        cout << "Elementas nerastas. Naujas elementas neiterptas." << endl;
    }
}

void iterptiPo(list<int>& sarasas, int nurodytasElementas, int naujasElementas) {
    auto it = find(sarasas.begin(), sarasas.end(), nurodytasElementas);
    if (it != sarasas.end()) {
        sarasas.insert(next(it), naujasElementas);
    }
    else {
        cout << "Elementas nerastas. Naujas elementas neiterptas." << endl;
    }
}

void pasalintiElementa(list<int>& sarasas, int elementasPasalinimui) {
    sarasas.remove(elementasPasalinimui);
}

int rastiDidziausia(list<int>& sarasas) {
    if (!sarasas.empty()) {
        return *max_element(sarasas.begin(), sarasas.end());
    }
    else {
        cout << "Sarasas tuscias." << endl;
        return -1; 
    }
}

void perkeltiElementusPoNulio(list<int>& dvikryptisSarasas, list<int>& ciklinis) {
    auto iter = find(dvikryptisSarasas.rbegin(), dvikryptisSarasas.rend(), 0);  
    bool rastaNulis = (iter != dvikryptisSarasas.rend());

    if (rastaNulis) {
        iter++;  
        for (; iter != dvikryptisSarasas.rend(); ++iter) {
            ciklinis.push_back(*iter);  
        }
    }
    else {
        cout << "Sarase 0 nerasta, elementai neperkelti." << endl;
    }
}

int apskaiciuotiVidurki(const list<int>& sarasas) {
    if (sarasas.empty()) return 0;  

    int suma = accumulate(sarasas.begin(), sarasas.end(), 0);
    return suma / sarasas.size();
}

int kiekDidesniuUzVidurki(const list<int>& ciklinisSarasas, int vidurkis) {
    return count_if(ciklinisSarasas.begin(), ciklinisSarasas.end(), [vidurkis](int elem) { return elem > vidurkis; });
}

void panaikintiTarpiniusElementus(list<int>& sarasas) {
    if (sarasas.size() < 4) {
        cout << "\033[93mSarase per mazai elementu, kad butu galima panaikinti tarpinius.\033[0m\n";
        return;
    }

    auto it = sarasas.begin();
    advance(it, 2);  

    auto priesPaskutinisIt = sarasas.end();
    advance(priesPaskutinisIt, -2);  

    cout << "\033[92mPanaikinti elementai:\033[0m ";
    while (it != priesPaskutinisIt) {
        cout << *it << " ";
        it = sarasas.erase(it);  
    }
    cout << endl;
}

void rodytiPagrindiniMeniu() {
    cout << "\n\033[96m***********************************\033[0m\n";
    cout << "\033[96m*         Saraso Meniu         *\033[0m\n";
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
    cout << "\033[97mJusu pasirinkimas:\033[0m ";
}

void IsvalytiEkrana() {
    system("cls"); 
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

    IsvalytiEkrana(); 
    cout << "Dabar iveskite saraso elementus. Ivedus ne skaiciu, duomenu ivedimas bus baigtas." << endl;
    duomenuIvedimas(dvikryptisSarasas);

    do {
        IsvalytiEkrana(); 
        rodytiPagrindiniMeniu();
        cin >> pasirinkimas;

        if (pasirinkimas == 1) {
            int nurodytasElementas, naujasElementas;
            cout << "\033[93mIveskite elementa, pries kuri norite iterpti nauja elementa:\033[0m ";
            cin >> nurodytasElementas;
            cout << "\033[93mIveskite nauja elementa:\033[0m ";
            cin >> naujasElementas;

            iterptiPries(dvikryptisSarasas, nurodytasElementas, naujasElementas);
            isvestiSarasa(dvikryptisSarasas);
            lauktiVartotojo();  
        }
        if (pasirinkimas == 2) {
            int nurodytasElementas, naujasElementas;
            cout << "\033[93mIveskite elementa, po kurio norite iterpti nauja elementa:\033[0m ";
            cin >> nurodytasElementas;
            cout << "\033[93mIveskite nauja elementa:\033[0m ";
            cin >> naujasElementas;

            iterptiPo(dvikryptisSarasas, nurodytasElementas, naujasElementas);
            isvestiSarasa(dvikryptisSarasas);
            lauktiVartotojo();
        }
        if (pasirinkimas == 3) {
            int salinamasElementas;
            cout << "\033[93mIveskite elementa, kuri norite pasalinti:\033[0m ";
            cin >> salinamasElementas;

            pasalintiElementa(dvikryptisSarasas, salinamasElementas);
            cout << "\033[92mElementai su reiksme " << salinamasElementas << " buvo pasalinti.\033[0m" << endl;

            isvestiSarasa(dvikryptisSarasas);
            lauktiVartotojo(); 
        }

        if (pasirinkimas == 4) {
            int didziausias = rastiDidziausia(dvikryptisSarasas);
            if (didziausias != -1) {  
                cout << "\033[92mDidziausias elementas ssraðe yra: \033[0m" << didziausias << endl;
            }
            else {
                cout << "\033[91mSarasas tuscias.\033[0m" << endl;
            }

            lauktiVartotojo();  
        }

        if (pasirinkimas == 5) {
            list<int> ciklinisSarasas;  
            perkeltiElementusPoNulio(dvikryptisSarasas, ciklinisSarasas);

            cout << "\033[92mElementai po paskutiniojo 0 perkelti i ciklini ssrasa.\033[0m" << endl;
            cout << "\033[93mCiklinio saraso elementai:\033[0m ";
            isvestiSarasa(ciklinisSarasas);  

            lauktiVartotojo(); 
        }

        if (pasirinkimas == 6) {
            int vidurkis = apskaiciuotiVidurki(dvikryptisSarasas);
            int didesniuUzVidurkiSkaicius = kiekDidesniuUzVidurki(ciklinisSarasas, vidurkis);

            cout << "\033[92mCikliniame sàraðe elementø, kurie yra didesni uþ dvikrypèio sàraðo vidurká (" << vidurkis << "), yra: \033[0m" << didesniuUzVidurkiSkaicius << endl;
            lauktiVartotojo();  
        }

        if (pasirinkimas == 7) {
            panaikintiTarpiniusElementus(ciklinisSarasas); 
            isvestiSarasa(ciklinisSarasas);  
            lauktiVartotojo();  
        }
        

    } while (pasirinkimas != 8);

    cout << "Programa baigiama..." << endl;
    return 0;
}
