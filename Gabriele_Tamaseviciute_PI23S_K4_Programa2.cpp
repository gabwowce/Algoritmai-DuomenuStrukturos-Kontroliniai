/*Pašalinti paskutinį lyginį elementą.

Visuose uzdaviniuose reikia naudoti vienkrypcius sarasus bei funkcijas, kuriose turi buti
realizuoti prasomi veiksmai. Taip turi buti realizuotos ivedimo bei spausdinimo funkcijos.*/

#include <iostream>

using namespace std;

struct Mazgas {
	int duomuo;
	Mazgas* kitas;
};


Mazgas* SukurtiMazga(int duomuo) {
	Mazgas* newMazgas = new Mazgas;
	newMazgas->duomuo = duomuo;
	newMazgas->kitas = nullptr;
	return newMazgas;
}

void PridetiElementa(Mazgas*& pradzia, int duomuo) {
	Mazgas* naujasMazgas = SukurtiMazga(duomuo);
	if (pradzia == nullptr) {
		pradzia = naujasMazgas;
	}
	else {
		Mazgas* dabartinis = pradzia;
		while (dabartinis->kitas != nullptr) {
			dabartinis = dabartinis->kitas;
		}
		dabartinis->kitas = naujasMazgas;
	}
	naujasMazgas->kitas = nullptr;
}


void RodytiVisaSarasa(Mazgas* pradzia) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	while (dabartinis != nullptr) {
		cout << dabartinis->duomuo << " ";
		dabartinis = dabartinis->kitas;
	}
	cout << endl;
}

void PasalintiPaskutiniLyginiElementa(Mazgas*& pradzia) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias. Nera ka salinti." << endl;
		return;
	}

	Mazgas* dabartinis = pradzia;
	Mazgas* paskutinisLyginis = nullptr;
	Mazgas* paskutinioLyginioAnkstesnis = nullptr;

	while (dabartinis != nullptr) {
		if (dabartinis->duomuo % 2 == 0) {
			paskutinioLyginioAnkstesnis = paskutinisLyginis;
			paskutinisLyginis = dabartinis;
		}
		if (dabartinis->kitas != nullptr && dabartinis->kitas->duomuo % 2 == 0) {
			paskutinioLyginioAnkstesnis = dabartinis;
		}
		dabartinis = dabartinis->kitas;
	}

	if (paskutinisLyginis != nullptr) {
		if (paskutinioLyginioAnkstesnis != nullptr) {
			paskutinioLyginioAnkstesnis->kitas = paskutinisLyginis->kitas;
		}
		else {
			pradzia = paskutinisLyginis->kitas;
		}
		delete paskutinisLyginis;
	}
}



int main() {
	Mazgas* pradzia = nullptr;
	int N;
	int num;

	cout << "Iveskite sveikuju skaiciu kieki N: ";
	cin >> N;

	cout << "Iveskite " << N << " sveikuosius skaicius:" << endl;
	for (int i = 0; i < N; i++) {
		cout << "Iveskite " << i + 1 << "-aji skaiciu: ";
		cin >> num;
		PridetiElementa(pradzia, num);
	}

	cout << "\nSarasas dabar atrodo taip: ";
	RodytiVisaSarasa(pradzia);

	PasalintiPaskutiniLyginiElementa(pradzia);

	cout << "\nSarasas po paskutintojo lyginio skaiciaus pasalinimo atrodo taip: ";
	RodytiVisaSarasa(pradzia);



	return 0;
}
