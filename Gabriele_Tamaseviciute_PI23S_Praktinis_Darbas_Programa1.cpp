#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Mazgas {
    char duomenys;
    Mazgas* kitas = nullptr;
    Mazgas* ankstesnis = nullptr;  
};

void spausdintiSarasa(Mazgas* galva) {
    Mazgas* dabartinis = galva;
    while (dabartinis != nullptr) {
        cout << dabartinis->duomenys;
        dabartinis = dabartinis->kitas;
    }
    cout << endl;
}

void sujungtiTarpus(Mazgas*& galva) {
    Mazgas* dabartinis = galva;
    while (dabartinis != nullptr && dabartinis->kitas != nullptr) {
        if (dabartinis->duomenys == ' ' && dabartinis->kitas->duomenys == ' ') {
            Mazgas* temp = dabartinis->kitas;
            dabartinis->kitas = dabartinis->kitas->kitas;
            if (dabartinis->kitas != nullptr) { // Patikriname, ar nesame pasiekæ sàraðo galo
                dabartinis->kitas->ankstesnis = dabartinis; // Atnaujiname sekantá mazgà, kad jis rodytø atgal á dabartiná
            }
            delete temp;
        }
        else {
            dabartinis = dabartinis->kitas;
        }
    }
}




void pasalintiTarpusPradziojeIrGale(Mazgas*& galva, Mazgas*& uodega) {
    // Paðalinimas pradþioje
    while (galva != nullptr && galva->duomenys == ' ') {
        Mazgas* temp = galva;
        galva = galva->kitas;
        if (galva != nullptr) {
            galva->ankstesnis = nullptr;
        }
        delete temp;
    }

    // Paðalinimas gale
    while (uodega != nullptr && uodega->duomenys == ' ') {
        Mazgas* temp = uodega;
        uodega = uodega->ankstesnis;
        if (uodega != nullptr) {
            uodega->kitas = nullptr;
        }
        delete temp;
    }
}

void rastiPirmoZodzioPradziaIrPabaiga(Mazgas* galva, Mazgas*& pirmoPradzia, Mazgas*& pirmoPabaiga) {
    // Rasti pirmojo þodþio pradþià
    for (Mazgas* dabartinis = galva; dabartinis != nullptr; dabartinis = dabartinis->kitas) {
        if (dabartinis->duomenys != ' ') {
            pirmoPradzia = dabartinis;
            cout << "pirmoPradzia: ";
            cout << pirmoPradzia->duomenys <<endl;
            break;
        }
    }

    // Rasti pirmojo þodþio pabaigà
    if (pirmoPradzia != nullptr) {
        for (Mazgas* dabartinis = pirmoPradzia; dabartinis != nullptr; dabartinis = dabartinis->kitas) {
            if (dabartinis->duomenys == ' ' || dabartinis->kitas->duomenys == ' ') {
                pirmoPabaiga = dabartinis;
                cout << "pirmopabaiga: ";
                cout << pirmoPabaiga->duomenys <<endl;
                break;
            }
        }
    }
}

void rastiPaskutinioZodzioPradziaIrPabaiga(Mazgas* galva, Mazgas*& paskutinioPradzia, Mazgas*& paskutinioPabaiga) {
    
    // Rasti paskutiniojo þodþio pabaigà
    Mazgas* dabartinis = galva;
    while (dabartinis->kitas != nullptr) { // Eiti iki sàraðo galo
        dabartinis = dabartinis->kitas;
    }
    paskutinioPabaiga = dabartinis;
    cout << "paskutinioPradzia: ";
    cout << paskutinioPabaiga->duomenys << endl;

    // Rasti paskutiniojo þodþio pradþià
    while (dabartinis != nullptr) {
        if (dabartinis->duomenys == ' ' || dabartinis == galva) { // Radome paskutinio þodþio pradþià
            paskutinioPradzia = dabartinis->duomenys == ' ' ? dabartinis->kitas : dabartinis;
            break;
        }
        dabartinis = dabartinis->ankstesnis;
    }
    cout << "paskutiniopradzia: ";
    cout << paskutinioPradzia->duomenys << endl;
}



bool arVienodiZodziai(Mazgas* pirmoPradzia, Mazgas* pirmoPabaiga, Mazgas* paskutinioPradzia, Mazgas* paskutinioPabaiga) {
    while (pirmoPradzia != pirmoPabaiga->kitas && paskutinioPradzia != paskutinioPabaiga->kitas) {
        if (tolower(pirmoPradzia->duomenys) != tolower(paskutinioPradzia->duomenys)) {
            return false;
        }
        pirmoPradzia = pirmoPradzia->kitas;
        paskutinioPradzia = paskutinioPradzia->kitas;
    }
    
    return true;
}



int main() {
    string sakinys;
    cout << "Iveskite sakini: ";
    getline(cin, sakinys); 

    Mazgas* galva = nullptr;
    Mazgas* uodega = nullptr;

    Mazgas* pirmoPradzia = nullptr;
    Mazgas* pirmoPabaiga = nullptr;
    Mazgas* paskutinioPradzia = nullptr;
    Mazgas* paskutinioPabaiga = nullptr;

    for (char simbolis : sakinys) {
        Mazgas* naujasMazgas = new Mazgas();
        naujasMazgas->duomenys = simbolis;
        if (galva == nullptr) {
            galva = naujasMazgas;
            uodega = naujasMazgas;
        }
        else {
            uodega->kitas = naujasMazgas;
            naujasMazgas->ankstesnis = uodega;  
            uodega = naujasMazgas;
        }
    }

    sujungtiTarpus(galva);
    pasalintiTarpusPradziojeIrGale(galva, uodega);

    rastiPirmoZodzioPradziaIrPabaiga(galva, pirmoPradzia, pirmoPabaiga);
    rastiPaskutinioZodzioPradziaIrPabaiga(galva, paskutinioPradzia, paskutinioPabaiga);

    if (arVienodiZodziai(pirmoPradzia, pirmoPabaiga, paskutinioPradzia, paskutinioPabaiga)) {
        Mazgas* tempPirmo = pirmoPradzia;
        Mazgas* tempPaskutinio = paskutinioPradzia;

        while (tempPirmo != pirmoPabaiga->kitas && tempPaskutinio != paskutinioPabaiga->kitas) {
            swap(tempPirmo->duomenys, tempPaskutinio->duomenys);
            tempPirmo = tempPirmo->kitas;
            tempPaskutinio = tempPaskutinio->kitas;
        }
    }


    cout << "Sutvarkytas sakinys: ";
    spausdintiSarasa(galva);


    return 0;
}