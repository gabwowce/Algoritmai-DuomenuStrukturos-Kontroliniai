
/* 1.Sukurti cikliná vienkryptá sàraðà, realizuojant duomenø ávedimà, áterpimà prieð ir po nurodyto
elemento, norimo elemento paðalinimà bei didþiausio elemento radimà.Realizuoti funkcijas,
kurios:
	a.Pirmus 6 neigiamus skaièius perkelia á dvikryptá cikliná sàraðà.

	b.Apskaièiuoja kiek dvikrypèiame cikliniame sàraðe esanèiø lyginiø elementø pagal
	absoliuèià reikðmæ suma yra didesnë uþ vienkrypèio ciklinio sàraðo visø nelyginiø
	elementø sumà.

	c.Panaikina ciklinio sàraðo pirmàjá, viduriná ir paskutiná elementà, ir atspausdina juos
	ekrane

Pastaba.Ðioje uþduotyje negalima naudoti STL bibliotekø. */



#include <iostream>
#include <limits>
#include <string>
#include <climits>
using namespace std;

struct Mazgas {
	int duomuo;
	Mazgas* kitas;
};


Mazgas* SukurtiMazga(int duomuo) {
	Mazgas* newMazgas = new Mazgas;
	newMazgas->duomuo = duomuo;
	newMazgas->kitas = newMazgas; 
	return newMazgas;
}

struct DvikryptisMazgas {
	int duomuo;
	DvikryptisMazgas* ankstesnis;
	DvikryptisMazgas* kitas;

};

DvikryptisMazgas* SukurtiDvikryptiMazga(int duomuo) {
	DvikryptisMazgas* naujasMazgas = new DvikryptisMazgas; // Sukuriamas naujas mazgas naudojant numatytàjá konstruktoriø
	naujasMazgas->duomuo = duomuo; // Priskiriama duomenø reikðmë
	naujasMazgas->ankstesnis = nullptr; // Ankstesnis narys nustatomas á nullptr
	naujasMazgas->kitas = nullptr; // Kitas narys nustatomas á nullptr
	return naujasMazgas; // Gràþinamas sukurtas mazgas
}

void PridetiElementa(Mazgas*& pradzia, int duomuo) {
	Mazgas* newsMazgas = SukurtiMazga(duomuo);
	if (pradzia == nullptr) {
		pradzia = newsMazgas;
	}
	else {
		Mazgas* dabartinis = pradzia;
		while (dabartinis->kitas != pradzia) {
			dabartinis = dabartinis->kitas;
		}
		dabartinis->kitas = newsMazgas;
		newsMazgas->kitas = pradzia;
	}
}

void RodytiVisaSarasa(Mazgas* pradzia) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	do {
		cout << dabartinis->duomuo << " ";
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);
	cout << endl;
}

void IterptiPo(Mazgas*& pradzia, int ieskomasDuomuo, int naujasDuomuo) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	do {
		if (dabartinis->duomuo == ieskomasDuomuo) {
			Mazgas* naujasMazgas = SukurtiMazga(naujasDuomuo);
			naujasMazgas->kitas = dabartinis->kitas;
			dabartinis->kitas = naujasMazgas;

			cout << "\033[32mElementas " << naujasDuomuo << " iterptas po " << ieskomasDuomuo << ".\033[0m" << endl;
			cout << "Dabar sarasas atrodo taip: ";
			RodytiVisaSarasa(pradzia);
			return;
		}
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	cout << "Elementas " << ieskomasDuomuo << " nerastas." << endl;
}


void IterptiPries(Mazgas*& pradzia, int ieskomasDuomuo, int naujasDuomuo) {

	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	Mazgas* priestai = nullptr;

	do {
		if (dabartinis->duomuo == ieskomasDuomuo) {
			Mazgas* newMazgas = SukurtiMazga(naujasDuomuo);

			if (dabartinis == pradzia) {
				Mazgas* paskutinis = pradzia;
				while (paskutinis->kitas != pradzia) {
					paskutinis = paskutinis->kitas;
				}
				paskutinis->kitas = newMazgas;
				newMazgas->kitas = pradzia;
				pradzia = newMazgas;
			}
			else {
				priestai->kitas = newMazgas;
				newMazgas->kitas = dabartinis;
			}
			cout << "\033[32mElementas " << naujasDuomuo << " iterptas pries " << ieskomasDuomuo << ".\033[0m" << endl;
			cout << "Dabar sarasas atrodo taip: ";
			RodytiVisaSarasa(pradzia);
			return;

		}
		priestai = dabartinis;
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	cout << "Elementas " << ieskomasDuomuo << " nerastas." << endl;
}

void PasalintiElementa(Mazgas*& pradzia, int salinamasDuomuo) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	Mazgas* priestai = nullptr;
	bool arPasalinta = false;

	do {
		if (dabartinis->duomuo == salinamasDuomuo) {
			arPasalinta = true;

			if (dabartinis == pradzia) {
				Mazgas* paskutinis = pradzia;
				while (paskutinis->kitas != pradzia) { 
					paskutinis = paskutinis->kitas;
				}
				if (paskutinis == pradzia) { 
					pradzia = nullptr;
				}
				else {
					pradzia = dabartinis->kitas;
					paskutinis->kitas = pradzia;
				}
			}
			else {
				priestai->kitas = dabartinis->kitas;
			}

			delete dabartinis;
			break;
		}

		priestai = dabartinis;
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	if (arPasalinta) {
		cout << "\033[32mElementas " << salinamasDuomuo << " pasalintas.\033[0m" << endl;
		if (pradzia == nullptr) {
			cout << "Sarasas dabar yra tuscias." << endl;
		}
		else {
			cout << "Dabar sarasas atrodo taip: ";
			RodytiVisaSarasa(pradzia);
		}
	}
	else {
		cout << "Elementas " << salinamasDuomuo << " nerastas." << endl;
	}
}


int RastiDidziausia(Mazgas* pradzia) {
	if (pradzia == nullptr) {
		return INT_MIN;
	}

	int didziausias = pradzia->duomuo;
	Mazgas* dabartinis = pradzia->kitas;
	do {
		if (dabartinis->duomuo > didziausias) {
			didziausias = dabartinis->duomuo;
		}
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	return didziausias;
}


void PerkeltiNeigiamus(Mazgas*& vienkryptisPradzia, DvikryptisMazgas*& dvikryptisPradzia) {
	Mazgas* dabartinis = vienkryptisPradzia;
	int neigiamuSkaicius = 0;

	if (dabartinis == nullptr) {
		cout << "Vienkryptis sarasas yra tuscias." << endl;
		return;
	}

	do {
		if (dabartinis->duomuo < 0 && neigiamuSkaicius < 6) {
			DvikryptisMazgas* naujas = SukurtiDvikryptiMazga(dabartinis->duomuo);

			if (dvikryptisPradzia == nullptr) {
				dvikryptisPradzia = naujas;
				naujas->kitas = naujas; 
				naujas->ankstesnis = naujas; 
			}
			else {
				DvikryptisMazgas* paskutinis = dvikryptisPradzia->ankstesnis;
				paskutinis->kitas = naujas;
				naujas->ankstesnis = paskutinis;
				naujas->kitas = dvikryptisPradzia;
				dvikryptisPradzia->ankstesnis = naujas;
			}
			cout << "Perkeltas neigiamas skaicius: " << dabartinis->duomuo << endl;

			neigiamuSkaicius++;
		}
		dabartinis = dabartinis->kitas;
	} while (dabartinis != vienkryptisPradzia && neigiamuSkaicius < 6);

	if (neigiamuSkaicius == 0) {
		cout << "Neigiamu skaiciu nerasta." << endl;
	}
}



int ApskaiciuotiSumuSkirtuma(Mazgas* pradzia) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return 0;
	}

	int lyginiuSuma = 0, nelyginiuSuma = 0;
	Mazgas* dabartinis = pradzia;
	do {
		if (dabartinis->duomuo % 2 == 0) {
			lyginiuSuma += dabartinis->duomuo;
		}
		else {
			nelyginiuSuma += dabartinis->duomuo;
		}
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	cout << "Lyginiu ir nelyginiu elementu sumu skirtumas: " << lyginiuSuma - nelyginiuSuma << endl;
	
}

void PasalintiIrAtspausdinti(Mazgas*& pradzia) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	cout << "Pasalinamas pirmasis elementas: " << dabartinis->duomuo << endl;
	if (dabartinis->kitas == pradzia) { 
		delete dabartinis;
		pradzia = nullptr;
		return;
	}
	else {
		Mazgas* paskutinis = pradzia;
		while (paskutinis->kitas != pradzia) {
			paskutinis = paskutinis->kitas;
		}
		pradzia = dabartinis->kitas;
		paskutinis->kitas = pradzia;
		delete dabartinis;
	}

	dabartinis = pradzia;
	while (dabartinis->kitas->kitas != pradzia) {
		dabartinis = dabartinis->kitas;
	}
	Mazgas* paskutinis = dabartinis->kitas;
	cout << "Pasalinamas paskutinis elementas: " << paskutinis->duomuo << endl;
	dabartinis->kitas = pradzia;
	delete paskutinis;

	int ilgis = 1;
	dabartinis = pradzia;
	while (dabartinis->kitas != pradzia) {
		dabartinis = dabartinis->kitas;
		ilgis++;
	}
	int vidurioIndeksas = ilgis / 2;
	dabartinis = pradzia;
	for (int i = 0; i < vidurioIndeksas - 1; i++) {
		dabartinis = dabartinis->kitas;
	}
	Mazgas* vidurinis = dabartinis->kitas;
	cout << "Pasalinamas vidurinis elementas: " << vidurinis->duomuo << endl;
	dabartinis->kitas = vidurinis->kitas;
	delete vidurinis;
}



void isvalytiIvesti() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void rodytiPagrindiniMeniu() {
	cout << "\n\033[96m***********************************\033[0m\n";
	cout << "\033[96m*   Ciklinio Vienkrypcio Saraso Meniu   *\033[0m\n";
	cout << "\033[96m***********************************\033[0m\n";
	cout << "\033[93mElementu manipuliavimas:\033[0m\n";
	cout << "  \033[92m1. Rodyti visa sarasa\033[0m\n";
	cout << "  \033[92m2. Iterpti elementa pries nurodyta\033[0m\n";
	cout << "  \033[92m3. Iterpti elementa po nurodytu\033[0m\n";
	cout << "  \033[92m4. Pasalinti elementa\033[0m\n";
	cout << "  \033[92m5. Rasti didziausia elementa sarase\033[0m\n";
	cout << "\033[93mSpecialios uzduotys:\033[0m\n";
	cout << "  \033[92m6. Perkelti pirmus 6 neigiamus skaicius i dvikrypti ciklini sarasa\033[0m\n";
	cout << "  \033[92m7. Apskaiciuoti lyginiu ir nelyginiu elementu sumu skirtuma\033[0m\n";
	cout << "  \033[92m8. Panaikinti pirmaji, vidurini ir paskutini elementa ir juos atspausdinti\033[0m\n";
	cout << "\033[93mKitos operacijos:\033[0m\n";
	cout << "  \033[91m9. Baigti darba\033[0m\n\n";
	cout << "\033[97mJUSU PASIRINKIMAS: \033[0m";
}

void IsvalytiEkrana() {
#ifdef _WIN32
	system("CLS");
#else
	system("clear");
#endif
}




int main(){

	Mazgas* pradzia = nullptr;
	DvikryptisMazgas* dvikryptisPradzia = nullptr;

	cout << "Pradziai, iveskite duomenis i sarasa.\n";
	cout << "Noredami nutraukti duomenu ivedima, iveskite ne skaiciu\n\n";

	int elementas;
	while (true) {
		cout << "Iveskite elementa: ";
		cin >> elementas;
		if (cin.fail()) {
			isvalytiIvesti();
			break;
		}

		PridetiElementa(pradzia, elementas);
	}
		


	int pasirinkimas;
	do {
		IsvalytiEkrana();
		rodytiPagrindiniMeniu();
		cin >> pasirinkimas;
		if (cin.fail()) {
			isvalytiIvesti();
			continue;
		}

		if (pasirinkimas == 1) {
			cout << endl;
			RodytiVisaSarasa(pradzia);
		}

		else if (pasirinkimas == 2) {
			cout << endl;
			int ieskomasDuomuo, naujasDuomuo;
			cout << "Iveskite elemento reiksme, pries kuria norite iterpti nauja elementa: ";
			cin >> ieskomasDuomuo;
			if (cin.fail()) {
				isvalytiIvesti();
				cout << "Netinkama ivestis. Bandykite dar karta." << endl;
				continue;
			}

			cout << "Iveskite naujo elemento reiksme: ";
			cin >> naujasDuomuo;
			if (cin.fail()) {
				isvalytiIvesti();
				cout << "Netinkama ivestis. Bandykite dar karta." << endl;
				continue;
			}

			IterptiPries(pradzia, ieskomasDuomuo, naujasDuomuo);
		}

		else if (pasirinkimas == 3) {
			cout << endl;
			int ieskomasDuomuo, naujasDuomuo;
			cout << "Iveskite elemento reiksme, po kuria norite iterpti nauja elementa: ";
			cin >> ieskomasDuomuo;
			if (cin.fail()) {
				isvalytiIvesti();
				cout << "Netinkama ivestis. Bandykite dar karta." << endl;
				continue;
			}

			cout << "Iveskite naujo elemento reiksme: ";
			cin >> naujasDuomuo;
			if (cin.fail()) {
				isvalytiIvesti();
				cout << "Netinkama ivestis. Bandykite dar karta." << endl;
				continue;
			}

			IterptiPo(pradzia, ieskomasDuomuo, naujasDuomuo);
		}


		else if (pasirinkimas == 4) {
			cout << endl;
			int salinamasDuomuo;
			cout << "Iveskite elemento reiksme, kuri norite pasalinti: ";
			cin >> salinamasDuomuo;
			if (cin.fail()) {
				isvalytiIvesti();
				cout << "Netinkama ivestis. Bandykite dar karta." << endl;
				continue;
			}

			PasalintiElementa(pradzia, salinamasDuomuo);

		}

		else if (pasirinkimas == 5) {
			if (pradzia == nullptr) {
				cout << "Sarasas yra tuscias. Nera ko ieskoti." << endl;
			}
			else {
				int didziausias = RastiDidziausia(pradzia);
				cout << "Didziausias elementas sarase yra: " << didziausias << endl;
			}
		}

		else if (pasirinkimas == 6) {
			cout << endl;
			PerkeltiNeigiamus(pradzia, dvikryptisPradzia);
		}

		else if (pasirinkimas == 7) {
			cout << endl;
			int sumuSkirtumas = ApskaiciuotiSumuSkirtuma(pradzia);
		}

		else if (pasirinkimas == 8) {
			cout << endl;
			PasalintiIrAtspausdinti(pradzia);
		}

		else if (pasirinkimas == 9) {
			cout << endl;
			cout << "Programa baigiama..." << endl;
		}
		else {
			cout << "Neteisingas pasirinkimas. Bandykite dar kartà." << endl;
		}

		cout << endl << "Paspauskite bet kuri klavisa norint testi..." << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		cin.get(); 
	} while (pasirinkimas != 9);


	return 0;
}