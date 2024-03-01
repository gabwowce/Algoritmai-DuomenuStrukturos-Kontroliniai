
/* Sukurti ciklinį vienkryptį sąrašą, realizuojant duomenų įvedimą, įterpimą prieš ir po nurodyto
elemento, norimo elemento pašalinimą bei didžiausio elemento radimą. Realizuoti funkcijas,
kurios:

a. Visus skaičius nuo didžiausio perkelia iš ciklinio sąrašo į steką, realizuotą kaip
vienkryptis sąrašas.
b. Įterpia skaičius iki pirmojo neigiamo į steką.
c. Panaikina visus steko elementus, juos atspausdinant ekrane. 

*/



#include <iostream>
#include <limits>
#include <string>
#include <climits>
using namespace std;



//Ciklinis vienkryptis --------------------------------------------------------------------------->
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




//Stekas ------------------------------------------------------------------------------------------------------------->
struct StekoMazgas {
	int duomuo;
	StekoMazgas* kitas;
};

void StekoPrideti(StekoMazgas*& virsus, int duomuo) {
	StekoMazgas* naujasMazgas = new StekoMazgas;
	naujasMazgas->duomuo = duomuo;
	naujasMazgas->kitas = virsus;
	virsus = naujasMazgas;
}



void PerkeltiIsCiklinioISteka(Mazgas*& pradzia, StekoMazgas*& virsus) {
	if (pradzia == nullptr) {
		cout << "Ciklinis sarasas yra tuscias." << endl;
		return;
	}

	int didziausias = RastiDidziausia(pradzia);
	Mazgas* dabartinis = pradzia;
	Mazgas* pirmasDidziausias = nullptr;

	do {
		if (dabartinis->duomuo == didziausias) {
			pirmasDidziausias = dabartinis;
			break;
		}
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);

	if (pirmasDidziausias == nullptr) {
		return;  
	}

	do {
		StekoPrideti(virsus, pirmasDidziausias->duomuo);
		pirmasDidziausias = pirmasDidziausias->kitas;
	} while (pirmasDidziausias != dabartinis);

	pradzia = dabartinis;
}



void IterptiIkiPirmojoNeigiamo(Mazgas* pradzia, StekoMazgas*& virsus) {
	if (pradzia == nullptr) {
		cout << "Ciklinis sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	do {
		if (dabartinis->duomuo < 0) {
			break;  
		}
		StekoPrideti(virsus, dabartinis->duomuo);  
		dabartinis = dabartinis->kitas;
	} while (dabartinis != pradzia);
}

void PanaikintiStekoElementus(StekoMazgas*& virsus) {
	cout << "Steko elementai pries panaikinima:" << endl;
	while (virsus != nullptr) {
		cout << virsus->duomuo << " ";  
		StekoMazgas* temp = virsus; 
		virsus = virsus->kitas;  
		delete temp;  
	}
	cout << "\nVisi steko elementai panaikinti." << endl;
}

void PerkeltiIsCiklinioIStekaNuoDidziausio(Mazgas*& pradzia, StekoMazgas*& virsus) {
	if (!pradzia) {
		cout << "Ciklinis sarasas yra tuscias." << endl;
		return;
	}

	int didziausias = RastiDidziausia(pradzia);
	Mazgas* dabartinis = pradzia;

	while (dabartinis->duomuo != didziausias) {
		dabartinis = dabartinis->kitas;
	}

	
	Mazgas* pradziosTaskas = dabartinis; 

	do {
		dabartinis = dabartinis->kitas; 
		StekoPrideti(virsus, dabartinis->duomuo);
	} while (dabartinis != pradziosTaskas);
}






//Kitos funkcijos ------------------------------------------------------------------------------------------------->


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

void AtnaujintiIrIsvesti(Mazgas* ciklinisPradzia, StekoMazgas* stekoVirsus) {
	cout << "Ciklinis sarasas: ";
	if (ciklinisPradzia != nullptr) {
		Mazgas* dabartinis = ciklinisPradzia;
		do {
			cout << dabartinis->duomuo << " ";
			dabartinis = dabartinis->kitas;
		} while (dabartinis != ciklinisPradzia);
	}
	else {
		cout << "(tuscias)";
	}
	cout << endl;

	cout << "Stekas: ";
	StekoMazgas* dabartinis = stekoVirsus;
	while (dabartinis != nullptr) {
		cout << dabartinis->duomuo << " ";
		dabartinis = dabartinis->kitas;
	}
	if (stekoVirsus == nullptr) {
		cout << "(tuscias)";
	}
	cout << "\n\n";
}


void rodytiPagrindiniMeniu() {
	cout << "\n\033[96m***********************************\033[0m\n";
	cout << "\033[96m*   Ciklinio Vienkrypcio Saraso Menu   *\033[0m\n";
	cout << "\033[96m***********************************\033[0m\n";
	cout << "\033[93mElementu manipuliavimas:\033[0m\n";
	cout << "  \033[92m1. Rodyti visa sarasa\033[0m\n";
	cout << "  \033[92m2. Iterpti elementa pries nurodyta\033[0m\n";
	cout << "  \033[92m3. Iterpti elementa po nurodytu\033[0m\n";
	cout << "  \033[92m4. Pasalinti elementa\033[0m\n";
	cout << "  \033[92m5. Rasti didziausia elementa sarase\033[0m\n";
	cout << "\033[93mSpecialios uzduotys:\033[0m\n";
	cout << "  \033[92m6. Visus skaicius nuo didziausio perkelia is ciklinio saraso i steka, realizuota kaip vienkryptis sarasas\033[0m\n";
	cout << "  \033[92m7. Iterpti skaicius iki pirmojo neigiamo i steka\033[0m\n";
	cout << "  \033[92m8. Panaikinti visus steko elementus, juos atspausdinti ekrane\033[0m\n";
	cout << "\033[93mKitos operacijos:\033[0m\n";
	cout << "  \033[91m9. Baigti darba\033[0m\n\n";
	cout << "\033[97mJUSU PASIRINKIMAS: \033[0m";
}


int main() {

	Mazgas* pradzia = nullptr;
	StekoMazgas* virsus = nullptr;

	

	cout << "Pradziai, iveskite duomenis i ciklini vienkrypti sarasa.\n";
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
		AtnaujintiIrIsvesti(pradzia, virsus);
		rodytiPagrindiniMeniu();
		cin >> pasirinkimas;
		if (cin.fail()) {
			isvalytiIvesti();
			continue;
		}

		if (pasirinkimas == 1) {
			cout << endl;
			RodytiVisaSarasa(pradzia);
			
			lauktiVartotojo();
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
			
			lauktiVartotojo();
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
			lauktiVartotojo();
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
			lauktiVartotojo();

		}

		else if (pasirinkimas == 5) {
			if (pradzia == nullptr) {
				cout << "Sarasas yra tuscias. Nera ko ieskoti." << endl;
			}
			else {
				int didziausias = RastiDidziausia(pradzia);
				cout << "Didziausias elementas sarase yra: " << didziausias << endl;
			}
			lauktiVartotojo();
		}

		else if (pasirinkimas == 6) {
			PerkeltiIsCiklinioIStekaNuoDidziausio(pradzia, virsus);
			cout << "Skaiciai sekmingai perkelti i steka!\n";
			lauktiVartotojo();
			
		}

		else if (pasirinkimas == 7) {
			IterptiIkiPirmojoNeigiamo(pradzia, virsus);
			cout << "Skaiciai sekmingai iterpti i steka!\n";

			lauktiVartotojo();
		}

		else if (pasirinkimas == 8) {
			PanaikintiStekoElementus(virsus);

			lauktiVartotojo();
		}

	} while (pasirinkimas != 9);


	return 0;
}