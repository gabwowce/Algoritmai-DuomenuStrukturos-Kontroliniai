
/*
2. Įterpti skaičių x po visų lyginių elementų, kurių indeksai yra nelyginiai.

Visuose uzdaviniuose reikia naudoti vienkrypcius sarasus bei funkcijas, kuriose turi buti
realizuoti prasomi veiksmai. Taip turi buti realizuotos ivedimo bei spausdinimo funkcijos.
*/
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
	}

	Mazgas* dabartinis = pradzia;
	while (dabartinis != nullptr) {
		cout << dabartinis->duomuo << " ";
		dabartinis = dabartinis->kitas;
	}
	cout << endl;
}

void IterptiSkaiciuPoLyginiuNelyginiuIndeksu(Mazgas*& pradzia, int x) {
	if (pradzia == nullptr) {
		cout << "Sarasas yra tuscias. Nera ka iterpti." << endl;
	}

	int indeksas = 1; 
	Mazgas* dabartinis = pradzia;
	while (dabartinis != nullptr) {
		if (dabartinis->duomuo % 2 == 0 && indeksas % 2 == 1) { 
			Mazgas* naujasMazgas = SukurtiMazga(x);
			naujasMazgas->kitas = dabartinis->kitas; 
			dabartinis->kitas = naujasMazgas; 
			dabartinis = naujasMazgas->kitas; 
			
		}
		else {
			dabartinis = dabartinis->kitas; 
		}
		
	}
}



int main() {
	Mazgas* pradzia = nullptr;
	int N;
	int num;
	int x;

	cout << "Iveskite sveikuju skaiciu kieki N: ";
	cin >> N;

	cout << "Iveskite " << N << " sveikuosius skaicius:" << endl;
	for (int i = 0; i < N; i++) {
		cout << "Iveskite " << i + 1 << "-aji skaiciu: ";
		cin >> num;
		PridetiElementa(pradzia, num);
	}

	cout << "Sarasas dabar atrodo taip: ";
	RodytiVisaSarasa(pradzia);

	cout << "\nIveskite skaiciu kuri norite iterpti po visu lyginiu elementu, kuriu indeksai yra nelyginiai: ";
	cin >> x;
	IterptiSkaiciuPoLyginiuNelyginiuIndeksu(pradzia, x);
	

	cout << "Naujas sarasas atrodo taip: ";
	RodytiVisaSarasa(pradzia);



	return 0;
}