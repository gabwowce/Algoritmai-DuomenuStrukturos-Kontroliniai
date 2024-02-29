#include <iostream>
using namespace std;

struct Mazgas {
    int duomuo; 
    Mazgas* kitas;  
};

void append(Mazgas** pradzia, int new_duomuo) {

    Mazgas* new_mazgas = new Mazgas();
    new_mazgas->duomuo = new_duomuo;
    new_mazgas->kitas = nullptr;

    // Jei sarasas tuscias, pradzia tampa naujas mazgas
    if (*pradzia == nullptr) {
        *pradzia = new_mazgas;
        return;
    }

    // Rasti paskutini mazga
    Mazgas* paskutinis = *pradzia;
    while (paskutinis->kitas != nullptr) {
        paskutinis = paskutinis->kitas;
    }

    // prideti nauja mazga prie paskutiniojo `kitas`
    paskutinis->kitas = new_mazgas;

}

void RastiMinMax(Mazgas* pradzia, int& min, int& max) {
 
    if (pradzia == nullptr) return;

   
    min = pradzia->duomuo;
    max = pradzia->duomuo;

    Mazgas* dabartinis = pradzia->kitas;
    while (dabartinis != nullptr) {
        if (dabartinis->duomuo < min) {
            min = dabartinis->duomuo;  
        }
        if (dabartinis->duomuo > max) {
            max = dabartinis->duomuo;  
        }
        dabartinis = dabartinis->kitas;  
    }
}

void IsvestiMinMaxKiekius(Mazgas* pradzia, int min, int max) {
    int minCount = 0;
    int maxCount = 0;

    while (pradzia != nullptr) {
        if (pradzia->duomuo == min) {
            minCount++;
        }
        if (pradzia->duomuo == max) {
            maxCount++;
        }
        pradzia = pradzia->kitas;
    }

    cout << "Minimalus elementas: " << min << ", pasikartoja: " << minCount << " kartus." << endl;
    cout << "Maksimalus elementas: " << max << ", pasikartoja: " << maxCount << " kartus." << endl;
}

void IsvedimasBeMinMax(Mazgas* mazgas, int min, int max) {
    while (mazgas != nullptr) {
        if (mazgas->duomuo != min && mazgas->duomuo != max) {
            cout << mazgas->duomuo << " ";
        }
        mazgas = mazgas->kitas;
    }
    
}

void IterptiPoMax(Mazgas** pradzia, int max, int naujasDuomuo) {
    Mazgas* dabartinis = *pradzia;
    while (dabartinis != nullptr) {
 
        if (dabartinis->duomuo == max) {
            
            Mazgas* naujasMazgas = new Mazgas();
            naujasMazgas->duomuo = naujasDuomuo;

            naujasMazgas->kitas = dabartinis->kitas;
            dabartinis->kitas = naujasMazgas;

            break;
        }
        dabartinis = dabartinis->kitas;
    }
}

void SarasoSpausdinimas(Mazgas* mazgas) {
    while (mazgas != nullptr) {
        cout << mazgas->duomuo << " ";
        mazgas = mazgas->kitas;
    }
    cout << endl;
}

void SalintiMazesniusUz(Mazgas** pradzia, int riba) {
    Mazgas* dabartinis = *pradzia;
    Mazgas* ankstesnis = nullptr;

    while (dabartinis != nullptr) {
        if (dabartinis->duomuo < riba) {
            if (ankstesnis == nullptr) { 
                *pradzia = dabartinis->kitas;
                delete dabartinis; 
                dabartinis = *pradzia; 
            }
            else {
                ankstesnis->kitas = dabartinis->kitas;
                delete dabartinis; 
                dabartinis = ankstesnis->kitas;
            }
        }
        else {
            ankstesnis = dabartinis;
            dabartinis = dabartinis->kitas;
        }
    }
}


int main() {
    Mazgas* pradzia = nullptr;  
    int N;
    int num;
    int pasirinkimas;
    cout << "Iveskite skaiciu N: " << endl;
    cin >> N;

    cout << "Iveskite " << N << " sveikuosius skaicius: ";
    for (int i = 0; i < N; i++) {
        cin >> num;
        append(&pradzia, num);
    }

    int min, max;
    RastiMinMax(pradzia, min, max);

    do {
        cout << endl;
        cout << "PASIRINKITE NORIMA FUNKCIJA " << endl;
        cout << "1 - Isvesti elementus lygius maksimumui ir minimumui, bei ju kieki." << endl;
        cout << "2 - Isvesti sarasa, be elementu lygiu maksimumui ir minimumui" << endl;
        cout << "3 - Iterpti skaiciu po didziausio elemento." << endl;
        cout << "4 - Pasalinti is vienkrypcio saraso visus elementus, kurie yra mazesni uz ivesta skaiciu." << endl;
        cout << "0 - Iseiti" << endl << endl;
        cout << "Iveskite savo pasirinkima: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 1) {
            IsvestiMinMaxKiekius(pradzia, min, max);
            cout << endl;
        }
        if (pasirinkimas == 2) {
            cout << "Elementu sarasas be min ir max: ";
            IsvedimasBeMinMax(pradzia, min, max);
            cout << endl;
        }
        if (pasirinkimas == 3) {
            int x;
            cout << "Iveskite skaiciu kuri norite iterpti: ";
            cin >> x;
            RastiMinMax(pradzia, min, max);
            IterptiPoMax(&pradzia, max, x);
            cout << "Skaicius: " << x << " buvo sekmingai iterptas po didziausio elemento!" << endl;
            cout << "Dabar sarasas atrodo taip: ";
            SarasoSpausdinimas(pradzia);

        }
        if (pasirinkimas == 4) {
            int n;
            cout << "Iveskite skaiciu: ";
            cin >> n;
            cout << endl;
            SalintiMazesniusUz(&pradzia, n);
            cout << "Elementai mazesni uz " << n << " buvo pasalinti." << endl;
            if (pradzia != nullptr) {
                cout << "Dabar sarasas atrodo taip: ";
                SarasoSpausdinimas(pradzia);
            }
            else {
                cout << "Dabar sarasas yra tuscias " <<endl;
            }
        }
    } while (pasirinkimas != 0);

    

    return 0;
}
