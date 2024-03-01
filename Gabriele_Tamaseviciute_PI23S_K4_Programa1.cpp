/* Ivesti sveika skaiciu N. Ivesti N sveiku skaiciu a1, a2, ... aN. Sekoje a1, a2, ... aN visus
narius, mazesnius uz didziausia sekos nari, padvigubinti. Isvesti gauta seka.


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



void apdorojimas(Mazgas* pradzia) {
	if (!pradzia) return;

	int didziausias = pradzia->duomuo;
	Mazgas* dabartinis = pradzia;

	// Rasti didþiausià skaièiø
	while (dabartinis != nullptr) {
		if (dabartinis->duomuo > didziausias) {
			didziausias = dabartinis->duomuo;
		}
		dabartinis = dabartinis->kitas;
	}


	dabartinis = pradzia;
	while (dabartinis != nullptr) {
		if (dabartinis->duomuo < didziausias) {
			dabartinis->duomuo *= 2;
		}
		dabartinis = dabartinis->kitas;
	}
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

	apdorojimas(pradzia);


	cout << "\nModifikuotas sarasas: ";
	RodytiVisaSarasa(pradzia);


	return 0;
}
