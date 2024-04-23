#include <iostream>
using namespace std;

struct Mazgas {
    int duomuo;
    Mazgas* kitas;
};

void iterpti(Mazgas*& galva, int duomuo) {
    Mazgas* naujasMazgas = new Mazgas;
    naujasMazgas->duomuo = duomuo;
    naujasMazgas->kitas = nullptr;

    if (galva == nullptr) {
        galva = naujasMazgas;
    }
    else {
        Mazgas* dabartinis = galva;
        while (dabartinis->kitas != nullptr) {
            dabartinis = dabartinis->kitas;
        }
        dabartinis->kitas = naujasMazgas;
    }
}


void spausdinti(Mazgas* galva) {
    while (galva != nullptr) {
        cout << galva->duomuo << " ";
        galva = galva->kitas;
    }
    cout << endl;
}

void salintiPasikartojimus(Mazgas*& galva) {
    Mazgas* dabartinis = galva;
    while (dabartinis != nullptr && dabartinis->kitas != nullptr) {
        if (dabartinis->duomuo == dabartinis->kitas->duomuo) {
            Mazgas* istrinti = dabartinis->kitas;
            dabartinis->kitas = dabartinis->kitas->kitas;
            delete istrinti;
        }
        else {
            dabartinis = dabartinis->kitas;
        }
    }
}

void isvalytiIvesti() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Mazgas* galva = nullptr;

    int elementas;

    cout << "Pradziai, iveskite duomenis i sarasa.\n";
    cout << "Noredami nutraukti duomenu ivedima, iveskite ne skaiciu\n\n";

    while (true) {
        cout << "Iveskite elementa: ";
        cin >> elementas;
        if (cin.fail()) {
            isvalytiIvesti();
            break;
        }

        iterpti(galva, elementas);
    }

    cout << "Originalus sarasas: ";
    spausdinti(galva);

    salintiPasikartojimus(galva);

    cout << "Sarasas be pasikartojimu: ";
    spausdinti(galva);

    return 0;
}
