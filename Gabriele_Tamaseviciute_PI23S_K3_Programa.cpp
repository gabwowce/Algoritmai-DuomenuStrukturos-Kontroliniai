/* 1.	Sukurti dvejetainá medá, kurio elementai sveiki skaièiai.  Realizuoti áterpimo, paieðkos, spausdinimo ir  ðalinimo operacijas bei atlikti ðiuos veiksmus:

a.	Áraðyti ið medþio  visus skaièius, kurie priklauso intervalui [a;b] á dekà, realizuotà kaip sàraðas, á pradþià.

b.	Áraðyti ið medþio  visus skaièius, kurie priklauso intervalui [0;a] á dekà, realizuotà kaip sàraðas, á pabaigà.

c.	Paðalinti ið medþio visus skaièius, kurie priklauso intervalui [b;c] ið medþio, áraðant juos á eilæ, realizuotà kaip sàraðas. 

d.	Spausdinti dekà ir eilæ
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
using namespace std;

//Medis ---------------------->
struct MedzioMazgas {
    int duomuo;
    MedzioMazgas* left;
    MedzioMazgas* right;

};

MedzioMazgas* SukurtiMedzioMazga(int duomuo) {
    MedzioMazgas* newMedzioMazgas = new MedzioMazgas;
    newMedzioMazgas->duomuo = duomuo;
    newMedzioMazgas->left = nullptr;
    newMedzioMazgas->right = nullptr;
    return newMedzioMazgas;
}


MedzioMazgas* IterptiMedzioMazga(MedzioMazgas* root, int duomuo) {
    if (root == nullptr) {
        return SukurtiMedzioMazga(duomuo);
    }

    if (duomuo < root->duomuo) {
        root->left = IterptiMedzioMazga(root->left, duomuo);
    }

    else if (duomuo > root->duomuo) {
        root->right = IterptiMedzioMazga(root->right, duomuo);
    }

    return root;
}


bool RastiElementa(MedzioMazgas* root, int duomuo) {
    if (root == nullptr) {
        return false;
    }

    if (root->duomuo == duomuo) {
        return true;
    }
    else if (duomuo < root->duomuo) {
        return RastiElementa(root->left, duomuo);
    }
    else {
        return RastiElementa(root->right, duomuo);
    }
}

MedzioMazgas* RastiMinimalu(MedzioMazgas* node) {
    MedzioMazgas* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

MedzioMazgas* SalintiMedzioMazga(MedzioMazgas* root, int duomuo) {
    if (root == nullptr) return root;

    if (duomuo < root->duomuo) {
        root->left = SalintiMedzioMazga(root->left, duomuo);
    }
    else if (duomuo > root->duomuo) {
        root->right = SalintiMedzioMazga(root->right, duomuo);
    }
    else {
        // Mazgas neturi vaikø
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // Mazgas turi vienà vaikà
        else if (root->left == nullptr) {
            MedzioMazgas* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            MedzioMazgas* temp = root->left;
            delete root;
            return temp;
        }
        // Mazgas turi du vaikus
        MedzioMazgas* temp = RastiMinimalu(root->right);
        root->duomuo = temp->duomuo;
        root->right = SalintiMedzioMazga(root->right, temp->duomuo);
    }
    return root;
}

// ---  Medzio strukturos spausdinimas --- //
int _print_t(MedzioMazgas* tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf_s(b, sizeof(b), "(%03d)", tree->duomuo);


    int left = _print_t(tree->left, 1, offset, depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    }
    else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}

void print_t(MedzioMazgas* tree) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf_s(s[i], sizeof(s[i]), "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++) {
        // Tikriname, ar eilutë yra kitokia nei tik tuðèiai uþpildyta
        if (strstr(s[i], "(") || strstr(s[i], "-") || strstr(s[i], "+")) {
            printf("%s\n", s[i]);
        }
    }
}

void SpausdintiInOrder(MedzioMazgas* root) {
    if (root != nullptr) {
        SpausdintiInOrder(root->left);
        cout << root->duomuo << " ";
        SpausdintiInOrder(root->right);
    }
}

void atnaujintiMedi(MedzioMazgas* root) {
    cout << "\033[96mDvejetainis Medis:\033[0m " << endl;
    if (root == nullptr) {
        cout << "(tuscias)" << endl;
    }
    else {
        print_t(root);
    }
}







//Dekas ---------------------->
struct DekoMazgas {
    int duomuo;
    DekoMazgas* ankstesnis;
    DekoMazgas* sekantis;
};

struct Dekas {
    DekoMazgas* priekis;
    DekoMazgas* galas;
};

DekoMazgas* SukurtiDekoMazga(int duomuo) {
    DekoMazgas* newDekoMazgas = new DekoMazgas;
    newDekoMazgas->duomuo = duomuo;
    newDekoMazgas->ankstesnis = nullptr;
    newDekoMazgas->sekantis = nullptr;
    return newDekoMazgas;
}

void InicializuotiDeka(Dekas& dekas) {
    dekas.priekis = nullptr;
    dekas.galas = nullptr;
}

void PridetiIPrieki(Dekas& dekas, int duomuo) {
    DekoMazgas* newDekoMazgas = SukurtiDekoMazga(duomuo);
    if (dekas.priekis == nullptr) {
        dekas.priekis = newDekoMazgas;
        dekas.galas = newDekoMazgas;
    }
    else {
        newDekoMazgas->sekantis = dekas.priekis;
        dekas.priekis->ankstesnis = newDekoMazgas;
        dekas.priekis = newDekoMazgas;
    }
}

void PridetiIGala(Dekas& dekas, int duomuo) {
    DekoMazgas* newDekoMazgas = SukurtiDekoMazga(duomuo);
    if (dekas.galas == nullptr) {
        dekas.priekis = newDekoMazgas;
        dekas.galas = newDekoMazgas;
    }
    else {
        dekas.galas->sekantis = newDekoMazgas;
        newDekoMazgas->ankstesnis = dekas.galas;
        dekas.galas = newDekoMazgas;
    }
}

void SpausdintiDeka(Dekas& dekas) {
    DekoMazgas* dabartinis = dekas.priekis;
    while (dabartinis != nullptr) {
        cout << dabartinis->duomuo << " ";
        dabartinis = dabartinis->sekantis;
    }
    cout << endl;
}

void IrasytiIPrieki(MedzioMazgas* root, Dekas& dekas, int a, int b) {
    if (root != nullptr) {
        IrasytiIPrieki(root->left, dekas, a, b);
        if (root->duomuo >= a && root->duomuo <= b) {
            PridetiIPrieki(dekas, root->duomuo);
        }
        IrasytiIPrieki(root->right, dekas, a, b);
    }
}

void IrasytiIDekaIGala(MedzioMazgas* root, Dekas& dekas, int a) {
    if (root != nullptr) {
        IrasytiIDekaIGala(root->left, dekas, a);
        if (root->duomuo <= a) {
            PridetiIGala(dekas, root->duomuo);
        }
        IrasytiIDekaIGala(root->right, dekas, a);
    }
}



//Eile ---------------------->
struct EilesMazgas {
    int duomuo;
    EilesMazgas* sekantis;
};

EilesMazgas* SukurtiEilesMazga(int duomuo) {
    EilesMazgas* newMazgas = new EilesMazgas;
    newMazgas->duomuo = duomuo;
    newMazgas->sekantis = nullptr;
    return newMazgas;
}

struct Eile {
    EilesMazgas* priekis;
    EilesMazgas* galas;
};

void InicializuotiEile(Eile& eile) {
    eile.priekis = nullptr;
    eile.galas = nullptr;
}

void IdetiIEile(Eile& eile, int duomuo) {
    EilesMazgas* newMazgas = SukurtiEilesMazga(duomuo);
    if (eile.galas == nullptr) {
        eile.priekis = newMazgas;
        eile.galas = newMazgas;
    }
    else {
        eile.galas->sekantis = newMazgas;
        eile.galas = newMazgas;
    }
}

void SpausdintiEile(Eile& eile) {
    EilesMazgas* dabartinis = eile.priekis;
    while (dabartinis != nullptr) {
        cout << dabartinis->duomuo << " ";
        dabartinis = dabartinis->sekantis;
    }
    cout << endl;
}

void SalintiIrIdetiIEile(MedzioMazgas*& root, Eile& eile, int b, int c) {
    if (root == nullptr) return;

    SalintiIrIdetiIEile(root->left, eile, b, c);
    SalintiIrIdetiIEile(root->right, eile, b, c);

    if (root->duomuo >= b && root->duomuo <= c) {
        IdetiIEile(eile, root->duomuo); // Ádeda elemento vertæ á eilæ
        root = SalintiMedzioMazga(root, root->duomuo); // Jûsø esama funkcija elemento paðalinimui ið medþio
    }
}


//Kitos funkcijos ---------------------->
void isvalytiIvesti() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void IsvalytiEkrana() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}


void lauktiVartotojo() {
    cout << "\nPaspauskite bet kuri klavisa norint testi...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void rodytiPagrindiniMeniu() {
    cout << "\n\033[96m***********************************\033[0m\n";
    cout << "\033[96m*   Dvejetainio Medzio Menu   *\033[0m\n";
    cout << "\033[96m***********************************\033[0m\n";
    cout << "\033[93mElementu manipuliavimas:\033[0m\n";
    cout << "  \033[92m1. Iterpti papildoma elementa\033[0m\n";
    cout << "  \033[92m2. Surasti ar medyje yra nurodytas elementas\033[0m\n";
    cout << "  \033[92m3. Pasalinti nurodyta elementa\033[0m\n";
    cout << "  \033[92m4. Spausdinti medzio elementus kaip sarasa\033[0m\n";
    cout << "\033[93mSpecialios uzduotys:\033[0m\n";
    cout << "  \033[92m5. Irasyti is medzio  visus skaicius, kurie priklauso intervalui [a;b] i deka, realizuota kaip sarasas, i pradzia\033[0m\n";
    cout << "  \033[92m6. Irasyti is medzio  visus skaicius, kurie priklauso intervalui [0;a] i deka, realizuota kaip sarasas, i pabaiga\033[0m\n";
    cout << "  \033[92m7. Pasalinti is medzio visus skaicius, kurie priklauso intervalui [b;c] is medzio, irasant juos i eile, realizuota kaip sarasas\033[0m\n";
    cout << "  \033[92m8. Spausdinti deka ir eile\033[0m\n";
    cout << "\033[93mKitos operacijos:\033[0m\n";
    cout << "  \033[91m9. Baigti darba\033[0m\n\n";
    cout << "\033[97mJUSU PASIRINKIMAS: \033[0m";
}






int main() {
    MedzioMazgas* root = nullptr;
    Dekas dekas; 
    InicializuotiDeka(dekas); 
    Eile eile;
    InicializuotiEile(eile);

    cout << "Pradziai, iveskite duomenis i dvejetaini medi.\n";
    cout << "Noredami nutraukti duomenu ivedima, iveskite ne skaiciu\n\n";

    int elementas;
    while (true) {
        cout << "Iveskite elementa: ";
        cin >> elementas;
        if (cin.fail()) {
            isvalytiIvesti();
            break;
        }

        root = IterptiMedzioMazga(root, elementas);
    }


    int pasirinkimas;
    do {
        IsvalytiEkrana();
        atnaujintiMedi(root);
        rodytiPagrindiniMeniu();
        cin >> pasirinkimas;
        if (cin.fail()) {
            isvalytiIvesti();
            continue;
        }

        if (pasirinkimas == 1) {
            int naujasElementas;
            cout << "Iveskite elementa, kuri norite iterpti: ";
            cin >> naujasElementas;
            
            root = IterptiMedzioMazga(root, naujasElementas); // Atnaujina medþio ðakná su nauju elementu
            cout << "\nELEMENTAS " << naujasElementas << " IVESTAS I MEDI\n";
            lauktiVartotojo();
            
        }
        else if (pasirinkimas == 2) {
            int ieskomasElementas;
            cout << "Iveskite elementa, kuri ieskote: ";
            cin >> ieskomasElementas;
            
            bool rasta = RastiElementa(root, ieskomasElementas);
            if (rasta) {
                cout << "ELEMENTAS " << ieskomasElementas << " RASTAS MEDYJE." << endl;
            }
            else {
                cout << "ELEMENTAS " << ieskomasElementas << " NERASTAS MEDYJE." << endl;
            }
            lauktiVartotojo();
        }
        else if (pasirinkimas == 3) {
            int salinamasElementas;
            cout << "Iveskite elementa, kuri norite pasalinti: ";
            cin >> salinamasElementas;

            root = SalintiMedzioMazga(root, salinamasElementas);  // Atnaujina medþio ðakná po elemento paðalinimo
            cout << "Elementas " << salinamasElementas << " pasalintas is medzio.\n";
            lauktiVartotojo();
        }
        else if (pasirinkimas == 4) {
            cout << "Medþio elementai (in-order): ";
            SpausdintiInOrder(root);
            cout << endl;
            lauktiVartotojo();
        }
        else if (pasirinkimas == 5) {
            int a, b;
            cout << "Iveskite intervalo pradzia (a): ";
            cin >> a;
            cout << "Iveskite intervalo pabaiga (b): ";
            cin >> b;

            IrasytiIPrieki(root, dekas, a, b);
            cout << "Elementai intervale [" << a << "; " << b << "] irasyti i deka: ";
            SpausdintiDeka(dekas);
            lauktiVartotojo();
        }
        else if (pasirinkimas == 6) {
            int a;
            cout << "Iveskite intervalo riba (a): ";
            cin >> a;

            IrasytiIDekaIGala(root, dekas, a);
            cout << "Elementai intervale [0; " << a << "] irasyti i deko gala: ";
            SpausdintiDeka(dekas);
            lauktiVartotojo();
        }
        else if (pasirinkimas == 7) {
            int b, c;
            cout << "Iveskite intervalo pradzia (b): ";
            cin >> b;
            cout << "Iveskite intervalo pabaiga (c): ";
            cin >> c;

            SalintiIrIdetiIEile(root, eile, b, c); 
            cout << "Elementai intervale [" << b << "; " << c << "] pasalinti is medzio ir irasyti i eile: ";
            SpausdintiEile(eile); 
            lauktiVartotojo();
        }
        else if (pasirinkimas == 8) {
            cout << "Dekos turinys: ";
            SpausdintiDeka(dekas);

            cout << "Eilës turinys: ";
            SpausdintiEile(eile);

            lauktiVartotojo();
        }



    } while (pasirinkimas != 9);





    return 0;
}