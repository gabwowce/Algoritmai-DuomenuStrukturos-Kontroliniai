
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
using namespace std;



//Medzio funkcijos ------------------------------------------------>

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


//Vienkryptis krypties sąrašas realizuotas kaip stekas ---------------------------------------------------->


struct StekoMazgas {
    int duomuo;
    StekoMazgas* kitas;
};

// Pridėti elementą į steką
void StekoIterpimas(StekoMazgas*& top, int duomuo) {
    StekoMazgas* newStekoMazgas = new StekoMazgas;
    newStekoMazgas->duomuo = duomuo;
    newStekoMazgas->kitas = top;
    top = newStekoMazgas;
}

void PerkeltiIVienkryptiSteka(MedzioMazgas* root, StekoMazgas*& top) {
    if (root != nullptr) {
        PerkeltiIVienkryptiSteka(root->right, top); // Pirma eina per dešinę pusę, kad mažiausias elementas būtų viršuje
        StekoIterpimas(top, root->duomuo);          // Įdeda root elementą į steką
        PerkeltiIVienkryptiSteka(root->left, top);  // Toliau eina per kairę pusę
    }
}

// Spausdinti steko turinį
void SpausdintiSteka(StekoMazgas* top) {
    while (top != nullptr) {
        cout << top->duomuo << " ";
        top = top->kitas;
    }
    cout << endl;
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


//Kitos funkcijos ----------------------------------------------------->
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
    cout << "\033[96m*              Menu                *\033[0m\n";
    cout << "\033[96m***********************************\033[0m\n";
    cout << "\033[93mMedzio elementu manipuliavimas:\033[0m\n";
    cout << "  \033[92m1. Iterpti papildoma elementa\033[0m\n";
    cout << "  \033[92m2. Surasti ar medyje yra nurodytas elementas\033[0m\n";
    cout << "  \033[92m3. Pasalinti nurodyta elementa\033[0m\n";
    cout << "\033[93mSteko operacijos:\033[0m\n";
    cout << "  \033[92m4. Perkelti visus medzio elementus i vienkrypti sarasa\033[0m\n";
    cout << "  \033[92m5. Spausdinti vienkryptcio saraso elementus\033[0m\n";
    cout << "\033[93mKitos operacijos:\033[0m\n";
    cout << "  \033[91m6. Baigti darba\033[0m\n\n";
    cout << "\033[97mJUSU PASIRINKIMAS: \033[0m";
}



//Main ------------------------------------------------------------->

int main() {
    MedzioMazgas* root = nullptr;
    StekoMazgas* stekoTop = nullptr;
    int elementas, pasirinkimas;

    cout << "Pradziai, iveskite duomenis i dvejetaini medi.\n";
    cout << "Noredami nutraukti duomenu ivedima, iveskite ne skaiciu\n\n";

    while (true) {
        cout << "Iveskite elementa: ";
        cin >> elementas;
        if (cin.fail()) {
            isvalytiIvesti();
            break;
        }

        root = IterptiMedzioMazga(root, elementas);
    }


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
            cout << "Iveskite elementa, kuri norite iterpti: ";
            cin >> elementas;
            root = IterptiMedzioMazga(root, elementas);
            cout << "Elementas " << elementas << " ivestas i medi.\n";
            lauktiVartotojo();

        }
        else if (pasirinkimas == 2) {
            cout << "Iveskite elementa, kurio ieskote: ";
            cin >> elementas;
            if (RastiElementa(root, elementas)) {
                cout << "Elementas " << elementas << " rastas medyje.\n";
            }
            else {
                cout << "Elementas " << elementas << " nerastas medyje.\n";
            }
            lauktiVartotojo();
        }
        else if (pasirinkimas == 3) {
            cout << "Iveskite elementa, kuri norite pasalinti: ";
            cin >> elementas;
            root = SalintiMedzioMazga(root, elementas);
            cout << "Elementas " << elementas << " pasalintas is medzio.\n";
            lauktiVartotojo();
        }
        else if (pasirinkimas == 4) {
            PerkeltiIVienkryptiSteka(root, stekoTop);
            cout << "Visi medzio elementai perkelti i vienkrypti sarasa.\n";
            lauktiVartotojo();
        }
        else if (pasirinkimas == 5) {
            cout << "Vienkryptcio saraso (steko) elementai: ";
            SpausdintiSteka(stekoTop);
            lauktiVartotojo();
        }      


    } while (pasirinkimas != 6);




    return 0;
}