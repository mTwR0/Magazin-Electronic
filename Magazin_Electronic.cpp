//INSTRUCTIUNI:
// 
//  !! Fisierul ’magazin.txt’ trebuie sa se afle in folder-ul proiectului !!
//
//La prima deschidere a consolei, daca apasati '1', veti intra la ecranul de testare a functionalitatii getter - ilor, setter - ilor, a constructorilor si a operatorilor.
//Daca apasati '2', veti intra in magazinul electronic.
// 
//In magazinul electronic, exista doua tipuri de conturi : cont magazin  si cont client.
//Din acest meniu puteti creea numai conturi de tip client.
//Singura metoda de a accesa un cont de tip magazin este de a avea fisierul ’magazin.txt’ in folderul proiectului.Puteti creea un cont magazin doar cand sunteti logat in contul magazin.
//
//Contul initial magazin are numele „admin” si parola „admin”.
//
//
//Functionalitati cont magazin:
//Din contul de magazin puteti adauga produse in stoc(care vor ramane salvate in fisierul ’Stoc.txt’) si aveti alte optiuni legate de produse.Produsele salvate in ’Stoc.txt’ vor fi folosite in contul de client.
//
//
//Functionalitati cont client:
//Din contul client puteti adauga, sterge sau afisa produsele din cos si puteti plasa comanda.
//
//
//PRECIZARI:
//Pentru a putea adauga produse in cos trebuie prima data sa fie adaugate in stoc utilizand meniul din cont magazin si functia de ’Adauga produs’.



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include<istream>
#include <string>
#include <cstdlib> // Pentru system()
#include <vector>

using namespace std;

vector<string> prodCos;
vector<string> cantCos;

//Clasa are rolul de afisare a meniurilor prin utilizarea polimorfismului
class AfisareMeniu {
public:
	virtual void meniu() = 0;
	virtual ~AfisareMeniu() = default;
};

//Aceasta clasa contine detaliile despre magazin
class Magazin {
private:
	string numeMagazin;
	char* locatieMagazin;
	int nrMagazine;       //reprezinta numarul de magazine dintr-un oras

public:
	//Constructor fara parametrii
	Magazin() {
		this->numeMagazin = "X";
		this->locatieMagazin = NULL;
		this->nrMagazine = 0;
	}
	//Constructor cu parametrii
	Magazin(string numeMag, const char* locatieMag, int nrMag) {
		if (numeMag.size() >= 2) {
			this->numeMagazin = numeMag;
		}
		else {
			this->numeMagazin = "NA";
		}

		if (this->locatieMagazin != NULL) {
			delete[]this->locatieMagazin;
		}
		this->locatieMagazin = new char[strlen(locatieMag) + 1];
		strcpy(this->locatieMagazin, locatieMag);

		if (nrMag > 0) {
			this->nrMagazine = nrMag;
		}
		else {
			this->nrMagazine = 0;
		}
	}
	//Constructor de copiere
	Magazin(const Magazin& m) {
		this->numeMagazin = m.numeMagazin;
		this->locatieMagazin = new char[strlen(m.locatieMagazin) + 1];
		strcpy(this->locatieMagazin, m.locatieMagazin);
		this->nrMagazine = m.nrMagazine;
	}
	//Destructor
	~Magazin() {
		if (locatieMagazin != NULL) {
			delete[]this->locatieMagazin;
		}
	}
	//Getteri
	string getnumeMagazin() {
		return this->numeMagazin;
	}
	char* getlocatieMagazin() {
		return this->locatieMagazin;
	}
	int getnrMagazine() {
		return this->nrMagazine;
	}
	//Setteri
	void setnumeMagazin(string numeMag) {
		this->numeMagazin = numeMag;
	}
	void setlocatieMagazin(const char* listaProduse) {
		if (this->locatieMagazin != NULL) {
			delete[]this->locatieMagazin;
		}
		this->locatieMagazin = new char[strlen(listaProduse) + 1];
		strcpy(this->locatieMagazin, listaProduse);
	}
	void setnrMagazine(int nrProduse) {
		this->nrMagazine = nrProduse;
	}
	//Operatorul =
	Magazin& operator= (const Magazin& m) {
		if (this != &m) {
			if (locatieMagazin != NULL) {
				delete[]this->locatieMagazin;
			}
			this->numeMagazin = m.numeMagazin;
			this->locatieMagazin = new char[strlen(m.locatieMagazin) + 1];
			strcpy(this->locatieMagazin, m.locatieMagazin);
			this->nrMagazine = m.nrMagazine;
		}
		return *this;
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const Magazin& m) {
		out << "Numele magazinului: " << m.numeMagazin << endl;
		out << "Locatia magazinului: " << m.locatieMagazin << endl;
		out << "Nr de magazine din oras: " << m.nrMagazine << endl;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Magazin& m) {
		cout << "Introduceti numele magazinului: ";
		in >> m.numeMagazin;
		cout << "Introduceti locatia magazinului: ";
		in >> m.locatieMagazin;
		cout << "Introduceti numarul de magazine: ";
		in >> m.nrMagazine;

		if (m.locatieMagazin != NULL) {
			delete[]m.locatieMagazin;
		}

		return in;
	}
};

//Aceasta clasa contine metodele pentru adaugarea, editarea si stergerea produselor in stocul magazinului. Tot in aceasta clasa se afla si metodele pentru salvarea stocului in fisier txt si binar
class Produs {
public:
	string numeProdus;
	int cantitateProdus;
	double pretProdus;
	vector<Produs> produse;
	vector<Produs> inventar;
	//Constructor fara parametrii
	Produs() {
		this->numeProdus = "DA";
		this->cantitateProdus = 0;
		this->pretProdus = 0;
	}
	//Constructor cu parametrii
	Produs(string numeProd, int cantitateProd, double pretProd) : numeProdus(numeProd), cantitateProdus(cantitateProd), pretProdus(pretProd) {
		if (numeProd.size() >= 2) {
			this->numeProdus = numeProd;
		}
		else {
			this->numeProdus = "YES";
		}
		if (cantitateProd > 0) {
			this->cantitateProdus = cantitateProd;
		}
		else {
			this->cantitateProdus = 0;
		}
		if (pretProd > 0) {
			this->pretProdus = pretProd;
		}
		else {
			this->pretProdus = 0;
		}
	}
	//Constructor de copiere
	Produs(const Produs& p) {
		this->numeProdus = p.numeProdus;
		this->cantitateProdus = p.cantitateProdus;
		this->pretProdus = p.pretProdus;
	}
	//Destructor
	~Produs() {};
	//Getteri
	string getnumeProdus() {
		return this->numeProdus;
	}
	int getcantitateProdus() {
		return this->cantitateProdus;
	}
	double getpretProdus() {
		return this->pretProdus;
	}
	//Setteri
	void setnumeProdus(string numeProd) {
		this->numeProdus = numeProd;
	}
	void setcantitateProdus(int cantitateProd) {
		this->cantitateProdus = cantitateProd;
	}
	void setpretProdus(double pretProd) {
		this->pretProdus = pretProd;
	}
	//Operatorul =
	Produs& operator= (const Produs& p) {
		if (this != &p) {
			this->numeProdus = p.numeProdus;
			this->cantitateProdus = p.cantitateProdus;
			this->pretProdus = p.pretProdus;
			return *this;
		}
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "Numele produsului este: " << p.numeProdus << endl;
		out << "Cantitatea produsului este: " << p.cantitateProdus << endl;
		out << "Pretul produsului este: " << p.pretProdus << endl;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Produs& p) {
		cout << "Introduceti numele produsului: ";
		in >> p.numeProdus;
		cout << "Introduceti cantitatea produsului: ";
		in >> p.cantitateProdus;
		cout << "Introduceti pretul produsului: ";
		in >> p.pretProdus;
		return in;
	}

	//METODE AFISARE, ADAUGARE, EDITARE SI STERGERE PRODUSE
	//Metoda afisare detalii produs
	void afisare() const {
		cout << "Produs: " << numeProdus << ", Cantitate: " << cantitateProdus << ", Pret: " << pretProdus << endl;
	}

	// Metoda pentru adaugarea de produse
	void adaugaProdus() {
		cout << "Introduceti numele produsului: ";
		getline(cin, numeProdus);

		cout << "Introduceti cantitatea: ";
		cin >> cantitateProdus;

		cout << "Introduceti pretul: ";
		cin >> pretProdus;

		Produs produs(numeProdus, cantitateProdus, pretProdus);
		inventar.push_back(produs);

		cout << "\nProdus adaugat cu succes!\n";
	}
	// Metoda pentru editarea produselor
	void editeazaProdus() {
		getline(cin, numeProdus);
		for (size_t i = 0; i < inventar.size(); ++i) {
			if (inventar[i].numeProdus == numeProdus) {
				int nouaCantitate;
				double noulPret;

				cout << "Introduceti noua cantitate: ";
				cin >> nouaCantitate;
				inventar[i].cantitateProdus = nouaCantitate;

				cout << "Introduceti noul pret: ";
				cin >> noulPret;
				inventar[i].pretProdus = noulPret;

				cout << "\nProdus editat cu succes!\n";
				return;
			}
		}

		cout << "Produsul nu a fost gasit in inventar.\n";
	}
	// Metoda pentru stergerea de produse
	void stergeProdus() {
		getline(cin, numeProdus);

		for (auto it = inventar.begin(); it != inventar.end(); ++it) {
			if (it->numeProdus == numeProdus) {
				inventar.erase(it);
				cout << "\nProdus sters cu succes!\n";
				return;
			}
		}
		cout << "Produsul nu a fost gasit in inventar.\n";
	}
	//METODA PENTRU SALVAREA PRODUSELOR IN FISIER TXT SI BINAR
	void salveazaProduse() {
		//cod de fisier deschidere
		ofstream file("Stoc.txt");
		if (!file.is_open()) {
			cout << "Eroare";
		}

		if (inventar.empty()) {
			cout << "Inventarul este gol.\n";
			file << "Inventarul este gol.\n";
			// aici pui in txt 
		}
		else {
			cout << endl;
			cout << "Inventar:\n";
			for (const auto& produs : inventar) {
				cout << "Nume: " << produs.numeProdus << ", Cantitate: " << produs.cantitateProdus << ", Pret: " << produs.pretProdus << "\n";
				file << "Nume: " << produs.numeProdus << ", Cantitate: " << produs.cantitateProdus << ", Pret: " << produs.pretProdus << "\n";
				// pui in txt 
			}
		}

		//FISIER BINAR PENTRU PRODUSELE DIN MAGAZIN (STOC)
		ofstream fisierb2("Stoc.bin", ios::binary | ios::out);
		string text;
		if (!fisierb2.is_open()) {
			cerr << "Eroare la deschiderea fisierului.\n";
			return;
		}

		// Salveaza fiecare obiect din inventar
		for (const auto& produs : inventar) {
			text = "Nume produs: ";
			fisierb2.write(text.c_str(), text.length() + 1);

			fisierb2.write(produs.numeProdus.c_str(), produs.numeProdus.length() + 1);
			text = "\n";
			fisierb2.write(text.c_str(), text.length() + 1);

			text = "Cantitate produs: ";
			fisierb2.write(text.c_str(), text.length() + 1);
			int cantitateProd = produs.cantitateProdus;
			string cantitate = to_string(produs.cantitateProdus);
			fisierb2.write(cantitate.c_str(), cantitate.length() + 1);
			text = "\n";
			fisierb2.write(text.c_str(), text.length() + 1);

			text = "Pret produs: ";
			fisierb2.write(text.c_str(), text.length() + 1);
			int pretProd = produs.pretProdus;
			string pret = to_string(produs.pretProdus);
			fisierb2.write(pret.c_str(), pret.length() + 1);
			text = "\n";
			fisierb2.write(text.c_str(), text.length() + 1);

		}
		cout << endl;
		cout << "Stoc actualizat si salvat in fisierul txt, 'Stoc.txt' si binar, 'Stoc.bin'. " << endl;

		file.close();
	}

	Produs& operator[](int pozitie) {
		return this->inventar[pozitie];
	}

};

//Clasa derivata din Produs pentru a aplica mostenirea
class ProdusAlimentar : public Produs {
private:
	string dataProducere;
	string dataExpirare;
public:
	//Constructor fara parametrii
	ProdusAlimentar() {
		this->dataProducere = "X";
		this->dataExpirare = "Y";
	}
	//Constructor cu parametrii
	ProdusAlimentar(string numeProd, int cantitateProd, double pretProd, string dataProd, string dataExp) : Produs(numeProd, cantitateProd, pretProd), dataProducere(dataProd), dataExpirare(dataExp) {
		if (numeProd.size() >= 2) {
			this->numeProdus = numeProd;
		}
		else {
			this->numeProdus = "YES";
		}
		if (cantitateProd > 0) {
			this->cantitateProdus = cantitateProd;
		}
		else {
			this->cantitateProdus = 0;
		}
		if (pretProd > 0) {
			this->pretProdus = pretProd;
		}
		else {
			this->pretProdus = 0;
		}
		if (dataProd.size() >= 2) {
			this->dataProducere = dataProd;
		}
		else {
			this->dataProducere = "XX.XX.XXXX";
		}
		if (dataExp.size() >= 2) {
			this->dataExpirare = dataExp;
		}
		else {
			this->dataExpirare = "YY.YY.YYYY";
		}
	}
	//Constructor de copiere
	ProdusAlimentar(const ProdusAlimentar& pa) {
		this->dataProducere = pa.dataProducere;
		this->dataExpirare = pa.dataExpirare;
	}
	//Destructor
	~ProdusAlimentar() {};
	//Getteri
	string getdataProducere() {
		return this->dataProducere;
	}
	string getdataExpirare() {
		return this->dataExpirare;
	}
	//Setteri
	void setdataProducere(string dataProd) {
		this->dataProducere = dataProd;
	}
	void setdataExpirare(string dataExp) {
		this->dataExpirare = dataExp;
	}
	//Operatorul =
	ProdusAlimentar& operator= (const ProdusAlimentar& pa) {
		if (this != &pa) {
			this->dataProducere = pa.dataProducere;
			this->dataExpirare = pa.dataExpirare;
			return *this;
		}
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const ProdusAlimentar& pa) {
		out << "Data producerii: " << pa.dataProducere << endl;
		out << "Data expirarii: " << pa.dataExpirare << endl;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, ProdusAlimentar& pa) {
		cout << "Introduceti data producerii: ";
		in >> pa.dataProducere;
		cout << "Introduceti data expirarii: ";
		in >> pa.dataExpirare;
		return in;
	}
	//Metoda afisare detalii produs
	void afisare() const {
		cout << "Produs alimentar: " << numeProdus << ", Cantitate: " << cantitateProdus << ", Pret: " << pretProdus << ", Data producerii: " << dataProducere << ", Data expirarii: " << dataExpirare << endl;
	}
};

//Clasa derivata din Produs pentru a aplica mostenirea
class ProdusElectrocasnic : public Produs {
private:
	int nrAniGarantie;
public:
	//Constructor fara parametrii
	ProdusElectrocasnic() {
		this->nrAniGarantie = 0;
	}
	//Constructor cu parametrii
	ProdusElectrocasnic(string numeProd, int cantitateProd, double pretProd, int nrAniG) : Produs(numeProd, cantitateProd, pretProd), nrAniGarantie(nrAniG) {
		if (numeProd.size() >= 2) {
			this->numeProdus = numeProd;
		}
		else {
			this->numeProdus = "YES";
		}
		if (cantitateProd > 0) {
			this->cantitateProdus = cantitateProd;
		}
		else {
			this->cantitateProdus = 0;
		}
		if (pretProd > 0) {
			this->pretProdus = pretProd;
		}
		else {
			this->pretProdus = 0;
		}
		if (nrAniG > 0) {
			this->nrAniGarantie = nrAniG;
		}
		else {
			this->nrAniGarantie = 0;
		}
	}
	//Constructor de copiere
	ProdusElectrocasnic(const ProdusElectrocasnic& pe) {
		this->nrAniGarantie = pe.nrAniGarantie;
	}
	//Destructor
	~ProdusElectrocasnic() {};
	//Getteri
	int getnrAniGarantie() {
		return this->nrAniGarantie;
	}
	//Setteri
	void setnrAniGarantie(int nrAniG) {
		this->nrAniGarantie = nrAniG;
	}
	//Operatorul =
	ProdusElectrocasnic& operator= (const ProdusElectrocasnic& pe) {
		if (this != &pe) {
			this->nrAniGarantie = pe.nrAniGarantie;
			return *this;
		}
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const ProdusElectrocasnic& pe) {
		out << "Numarul de ani al garantiei: " << pe.nrAniGarantie << endl;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, ProdusElectrocasnic& pe) {
		cout << "Introduceti numarul de ani al garantiei: ";
		in >> pe.nrAniGarantie;
		return in;
	}
	//Metoda afisare detalii produs
	void afisare() const {
		cout << "Produs electrocasnic: " << numeProdus << ", Cantitate: " << cantitateProdus << ", Pret: " << pretProdus << ", Numarul de ani a garantiei: " << nrAniGarantie << endl;
	}
};

//Metoda ce are rolul de a afisa continutul unui singur fisier
void afisareContinutFisier(const string& numeFisier) {
	ifstream fisier(numeFisier);

	if (!fisier.is_open()) {
		cout << "Eroare la deschiderea fisierului." << endl;
		return;
	}

	string linie;
	while (getline(fisier, linie)) {
		cout << linie << endl;
	}

	fisier.close();
}

//Metoda ce are rolul de a afisa continutul a mai multor fisiere
void afisareContinutFisiereMultiple(const string& numeBaza, int indice) {
	string numeFisier = numeBaza + to_string(indice) + ".txt";
	cout << "---------------------------------" << endl;
	afisareContinutFisier(numeFisier);
	cout << "---------------------------------" << endl;
}

//Aceasta clasa contine metoda si meniul pentru prelucrarea comenzilor
class Comanda : public AfisareMeniu {
private:
public:
	
	//Metoda prelucrare comanda + creare txt
	void prelucrareComanda() {
		int numarComanda = 0;    //contor incrementare pentru numele fisierului
		bool continua = true;

		string numeFisier = "comenziPrelucrate.txt";
		//ofstream fisier("comenziPreluate.txt");
		ofstream fisier(numeFisier);
		if (!fisier.is_open()) {
			cout << "Eroare la deschiderea fisierului pentru scriere." << endl;

		}
		while (continua) {
			string numeFisier = "Comanda" + to_string(numarComanda) + ".txt";
			ifstream fisierComanda(numeFisier);

			if (fisierComanda.is_open()) {
				string comanda;

				if (getline(fisierComanda, comanda) && !comanda.empty()) {
					cout << "------------------------------------------" << endl;
					cout << "Comanda citita din fisierul " << numeFisier << endl;
					cout << "------------------------------------------" << endl;
					string raspuns;
					cout << endl;
					cout << "Doresti sa onorezi aceasta comanda? (da/nu): ";
					cin >> raspuns;

					if (raspuns == "da" || raspuns == "Da" || raspuns == "DA" || raspuns == "dA") {
						cout << "Comanda a fost onorata." << endl;
						fisier << "Comanda" << numarComanda << " a fost onorata. " << endl;
					}
					else {
						cout << "Comanda nu a fost onorata." << endl;
					}
				}
				else {
					fisierComanda.close();
					break;
				}

				fisierComanda.close();
			}
			else {
				cout << "----------------------------------------------------" << endl;
				cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
				cout << "----------------------------------------------------" << endl;
				break;
			}
			numarComanda++;
		}
	}


	//Meniu Comenzi
	void meniu() override {
		int optiune;
		do {
			cout << "\nMeniu comenzi:" << endl;
			cout << "1. Afisarea ultimelor 4 comenzi plasate" << endl;
			cout << "2. Prelucreaza comanda" << endl;
			cout << "0. Iesire" << endl << endl << endl;
			cout << "Alege optiunea:";

			cin >> optiune;

			switch (optiune) {
			case 1:
				for (int i = 0; i < 4; ++i) {                        //se poate mari numarul de comenzi plasate afisate
					afisareContinutFisiereMultiple("Comanda", i);
				}
				break;
			case 2:
				prelucrareComanda();
				break;
			case 0:
				cout << "La revedere!" << endl;
				break;
			default:
				cout << "Optiune invalida. Va rugam sa reincercati." << endl;
			}
		} while (optiune != 0);
	}
};

void curataConsola() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

//Aceasta clasa contine metoda pentru crearea unui cont si pentru logare
class InterfataLogare {
private:
	int nrNume;
	char* nume;
	int nrParole;
	char* parole;
	//voiam sa fac cu char * si alocare dinamica si supraincarcare += sa adaug un string la finalul lui char* dar nush cum 
	vector<string> numeUtilizatori;
	vector<string> paroleUtilizatori;
public:
	//Constructor default
	InterfataLogare() {
		this->nrNume = 0;
		this->nume = nullptr;
		this->nrParole = 0;
		this->parole = nullptr;
	}
	//Constructor cu parametrii
	InterfataLogare(int nrNume, const char* nume, int nrParole, const char* parole) {
		if (this->nume != NULL)
			delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		if (nrNume > 0)
			this->nrNume = nrNume;
		else
			this->nrNume = 0;

		if (this->parole != NULL)
			delete[] this->parole;
		this->parole = new char[strlen(parole) + 1];
		strcpy(this->parole, parole);

		if (nrParole > 0)
			this->nrParole = nrParole;
		else
			this->nrParole = 0;
	}
	//Destructor
	~InterfataLogare() {
		if (nume != NULL) {
			delete[]this->nume;
		}
		if (parole != NULL) {
			delete[]this->parole;
		}
	}
	//Constructor de copiere
	InterfataLogare(const InterfataLogare& i) {
	
		this->nume = new char[strlen(i.nume) + 1];
		strcpy(this->nume, i.nume);
		this->nrNume = i.nrNume;
		this->parole = new char[strlen(i.parole) + 1];
		strcpy(this->parole, i.parole);
		this->nrParole = i.nrParole;
	}
	//Operatorul=
	InterfataLogare& operator=(const InterfataLogare& i) {
		if (this != &i) {
			delete[]this->nume;
			delete[]this->parole;
			this->nume = new char[strlen(i.nume) + 1];
			strcpy(this->nume, i.nume);
			this->nrNume = i.nrNume;
			this->parole = new char[strlen(i.parole) + 1];
			strcpy(this->parole, i.parole);
			this->nrParole = i.nrParole;
		}
		return *this;
	}


	void inregistrareUtilizator(const string& file) {
		string nume, parola;

		cout << "Introduceti numele de utilizator: ";
		cin >> nume;

		cout << "Introduceti parola: ";
		cin >> parola;

		salvareInformatii(nume, parola, file);
	}

	void salvareInformatii(const string& nume, const string& parola, const string& file) {
		ofstream fisier(file, ios::app);

		if (fisier.is_open()) {
			fisier << "Nume: " << nume << ", Parola: " << parola << endl;
			cout << "Informatiile au fost salvate cu succes!" << endl;
			fisier.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	//Nume: zz, Parola : xx

	bool getListaNumeParole(const string& nume, const string& parola, const string& nume_fisier) {

		// deschid odata fisier + verific cate linii are sa stiu cate loopuri am
		ifstream fisier1(nume_fisier);//"utilizatori.txt"
		if (!fisier1.is_open()) {
			cout << "Eroare la deschiderea fisierului 'magazin.txt'." << endl;
			return false;
		}

		int nrlinii = 0;
		string linie;
		while (getline(fisier1, linie)) {
			nrlinii++;
		}

		fisier1.close();


		ifstream fisier(nume_fisier);
		if (!fisier.is_open()) {
			cout << "Eroare la deschiderea fisierului." << endl;
			return false;
		}
		string numeGasit = "";
		// facem loopurile si aflam toate numele si pwd
		for (int i = 0; i < nrlinii; i++) {

			char caracter;
			string content = "";

			while (fisier.get(caracter)) {
				content += caracter;

				if (content == "Nume: ") {
					content = "";
					while (fisier.get(caracter) && caracter != ',') {
						content += caracter;
					}
					//cout << "Am gasit numele: " << content << endl;
					numeUtilizatori.push_back(content);
					//adaugaNume(content);
					//nume += content;
					break;
				}
			}
			content = "";

			while (fisier.get(caracter)) {
				content += caracter;

				if (content == " Parola: ") {
					content = "";
					while (fisier.get(caracter) && caracter != '\n') {
						content += caracter;
					}
					//cout << "Am gasit parola: " << content << endl;
					paroleUtilizatori.push_back(content);

					break;
				}

			}
		}



		fisier.close();
		return true;
	}
	bool verificaInformatiiUtilizatori(string nume, string parola) {
		for (int i = 0; i < numeUtilizatori.size(); i++) {
			if (nume == numeUtilizatori[i] && paroleUtilizatori[i] == parola)
				return true;

		}
		return false;
	}
};

//Aceasta clasa contine credentialele clientului
class Client {
protected:
	string numeClient;
	int nrTelefon;                //AR TREBUI SA FIE TOT DE TIP STRING PT A PUTEA PUNE NUMERE CE INCEP CU "0"
	string adresaClient;
	string emailClient;
	double totalPlata;

public:
	//Constructor fara parametrii
	Client() {
		this->numeClient = "X";
		this->nrTelefon = 0;
		this->adresaClient = "Y";
		this->emailClient = "Z";
		this->totalPlata = 0;
	}
	//Constructor cu parametrii
	Client(string numeClient, string adresaClient, string emailClient, int nrTelefon, double totalPlata) {
		if (numeClient.size() >= 2) {
			this->numeClient = numeClient;
		}
		else {
			this->numeClient = "NA";
		}
		if (adresaClient.size() >= 2) {
			this->adresaClient = adresaClient;
		}
		else {
			this->adresaClient = "NA";
		}
		if (emailClient.size() >= 2) {
			this->emailClient = emailClient;
		}
		else {
			this->emailClient = "NA";
		}
		if (nrTelefon > 0) {
			this->nrTelefon = nrTelefon;
		}
		else {
			this->nrTelefon = 0;
		}
		if (totalPlata > 0) {
			this->totalPlata = totalPlata;
		}
		else {
			this->totalPlata = 0;
		}
	}
	//Getteri
	string getnumeClient() {
		return this->numeClient;
	}
	int getnrTelefon() {
		return this->nrTelefon;
	}
	string getadresaClient() {
		return this->adresaClient;
	}
	string getemailClient() {
		return this->emailClient;
	}
	double gettotalPlata() {
		return this->totalPlata;
	}
	//Setteri
	void setnumeClient(string numeClient) {
		this->numeClient = numeClient;
	}
	void setnrTelefon(int nrTelefon) {
		this->nrTelefon = nrTelefon;
	}
	void setadresaClient(string adresaClient) {
		this->adresaClient = adresaClient;
	}
	void setemailClient(string emailClient) {
		this->emailClient = emailClient;
	}
	void settotalPlata(double totalPlata) {
		this->totalPlata = totalPlata;
	}
	//Constructor de copiere
	Client(const Client& c) {
		this->numeClient = c.numeClient;
		this->adresaClient = c.adresaClient;
		this->emailClient = c.emailClient;
		this->nrTelefon = c.nrTelefon;
		this->totalPlata = c.totalPlata;
	}
	//Destructor
	~Client() {
	}
	//Operatorul =
	Client& operator= (const Client& c) {
		if (this != &c) {
			this->numeClient = c.numeClient;
			this->adresaClient = c.adresaClient;
			this->emailClient = c.emailClient;
			this->nrTelefon = c.nrTelefon;
			this->totalPlata = c.totalPlata;
		}
		return *this;
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const Client& c) {
		out << "Numele clientului: " << c.numeClient << endl;
		out << "Nr-ul de telefon al clientului: " << c.nrTelefon << endl;
		out << "Adresa clientului: " << c.adresaClient << endl;
		out << "Email-ul clientului: " << c.emailClient << endl;
		out << "Totalul de achitat: " << c.totalPlata << endl;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Client& c) {
		cout << "Introduceti numele: ";
		in >> c.numeClient;
		cout << "Introduceti numarul de telefon: ";
		in >> c.nrTelefon;
		cout << "Introduceti adresa: ";
		in >> c.adresaClient;
		cout << "Introduceti email-ul: ";
		in >> c.emailClient;
		cout << "Introduceti suma totala de achitat: ";
		in >> c.totalPlata;
		return in;
	}
};

//Aceasta clasa contine metodele pentru plasarea unei comenzi cu produsele din cosul electronic (client) si o salveaza in fisier txt si binar. 
//Clasa foloseste atribute si metode din clasa 'Produs'. Clasa foloseste toate atributele din clasa 'Client' pentru salvarea credentialelor.
class CosElectronic : public Client, public Produs, public AfisareMeniu {
private:
	int i; //contor pt denumire fisier iterativa
public:
	//Constructor default
	CosElectronic() {
		this->i = 0;
	}
	//Metoda adaugare produs in cos
	void adauga_produs(const string& numeProd, int cantitateProd, double pretProd) {
		produse.push_back(Produs(numeProd, cantitateProd, pretProd));
	}
	//Metoda stergere produs din cos
	void sterge_produs(const string& numeProd) {
		auto it = find_if(produse.begin(), produse.end(),
			[numeProd](const Produs& p) { return p.numeProdus == numeProd; });

		if (it != produse.end()) {
			produse.erase(it);
			cout << "Produsul '" << numeProd << "' a fost sters din cos." << endl;
		}
		else {
			cout << "Produsul '" << numeProd << "' nu exista in cos." << endl;
		}
	}
	//Metoda afisare produse din cos
	void afiseaza_cos() const {
		cout << "Cosul contine urmatoarele produse:" << endl;
		for (const auto& produs : produse) {
			cout << produs.numeProdus << " - Cantitate: " << produs.cantitateProdus
				<< ", Pret: " << produs.pretProdus << " lei" << endl;
		}
	}
	// Metoda de plasare a comenzii + creare txt
	void plaseaza_comanda() {

		if (produse.empty()) {
			cout << "Cosul este gol. Adauga produse inainte de a plasa comanda." << endl;
			return;
		}

		cout << "Introduceti numele: ";
		getline(cin, numeClient);

		cout << "Introduceti adresa: ";
		getline(cin, adresaClient);

		cout << "Introduceti adresa de email: ";
		getline(cin, emailClient);

		cout << "Introduceti numarul de telefon(sa nu depaseasca 10 cifre): ";
		cin >> nrTelefon; 
		
		cout << "\n\n\nComanda a fost plasata cu succes!" << endl << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "Detalii comanda:" << endl;
		cout << "Produse:" << endl;
		for (const auto& produs : produse) {
			cout << "- " << produs.numeProdus << " x" << produs.cantitateProdus << " - Pret: " << produs.pretProdus << " lei" << endl;
			totalPlata += produs.cantitateProdus * produs.pretProdus;
		}
		cout << "Total de plata: " << totalPlata << " lei" << endl;
		cout << "Datele clientului:" << endl;
		cout << "Nume si prenume: " << numeClient << endl;
		cout << "Adresa: " << adresaClient << endl;
		cout << "Email: " << emailClient << endl;
		cout << "Nr. telefon: " << nrTelefon << endl;
		cout << "------------------------------------------------------------------" << endl << endl;

		//Le punem intr-un fisier txt generat iterativ


		string numeFisier = "comanda" + to_string(i) + ".txt";
		i++;
		//string numeFisier = "comanda.txt";

		ofstream fisier(numeFisier);
		if (!fisier.is_open()) {
			cout << "Fisierul nu a fost deschis.";
		}

		//deschis fisier cod 


		fisier << "Detalii comanda:" << endl;
		fisier << "Produse:" << endl;
		totalPlata = 0;
		for (const auto& produs : produse) {
			fisier << "- " << produs.numeProdus << " x" << produs.cantitateProdus << " - Pret: " << produs.pretProdus << " lei" << endl;
			totalPlata += produs.cantitateProdus * produs.pretProdus;
		}
		fisier << "Total de plata: " << totalPlata << " lei" << endl;
		fisier << "Datele clientului:" << endl;
		fisier << "Nume si prenume: " << numeClient << endl;
		fisier << "Adresa: " << adresaClient << endl;
		fisier << "Email: " << emailClient << endl;
		fisier << "Nr. telefon: " << nrTelefon << endl;

		//FISIER BINAR PENTRU COMENZILE TRIMISE DE CLIENTI
		ofstream fisierb("comanda.bin", ios::binary);

		if (fisierb.is_open()) {
			string text;
			fisierb.write(text.c_str(), text.length() + 1);
			for (const auto& produs : produse) {

				text = "-";
				fisierb.write(text.c_str(), text.length() + 1);
				fisierb.write(produs.numeProdus.c_str(), produs.numeProdus.length() + 1);
				text = "x";
				fisierb.write(text.c_str(), text.length() + 1);
				int numar = produs.cantitateProdus;
				string caractere = to_string(numar);
				fisierb.write(caractere.c_str(), caractere.length() + 1);

				text = " - Pret: ";
				fisierb.write(text.c_str(), text.length() + 1);
				numar = produs.pretProdus;
				caractere = to_string(numar);
				fisierb.write(caractere.c_str(), caractere.length() + 1);
				text = "lei";
				fisierb.write(text.c_str(), text.length() + 1);
				text = "\n";
				fisierb.write(text.c_str(), text.length() + 1);

			}
			text = "Total de plata (lei) :";
			fisierb.write(text.c_str(), text.length() + 1);


			int numar = totalPlata;
			string caractere = to_string(numar);
			fisierb.write(caractere.c_str(), caractere.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);

			text = "Datele clientului:\n";
			fisierb.write(text.c_str(), text.length() + 1);
			text = "Nume si prenume: ";
			fisierb.write(text.c_str(), text.length() + 1);

			fisierb.write(numeClient.c_str(), numeClient.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);

			text = "Adresa: ";
			fisierb.write(text.c_str(), text.length() + 1);
			fisierb.write(adresaClient.c_str(), adresaClient.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);

			text = "Email: ";
			fisierb.write(text.c_str(), text.length() + 1);
			fisierb.write(emailClient.c_str(), emailClient.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);

			text = "Nr. telefon: ";
			fisierb.write(text.c_str(), text.length() + 1);
			int numarTelefon = nrTelefon;
			string caracter = to_string(numarTelefon);
			fisierb.write(caracter.c_str(), caracter.length() + 1);
			text = "\n";
			fisierb.write(text.c_str(), text.length() + 1);

			//scriem astea text

		}
		cout << "Informatiile au fost salvate in fisierul txt, '" << numeFisier << "' si binar, 'comanda.bin'. " << endl;

		fisier.close();
		produse.clear(); // Se goleste cosul dupa plasarea comenzii
	}

	//Meniu CosElectronic
	void meniu() override {
		int optiune;
		do {
			cout << "\nMeniu client:" << endl;
			cout << "1. Adauga produs in cos" << endl;
			cout << "2. Sterge produs din cos" << endl;
			cout << "3. Afiseaza cosul" << endl;
			cout << "4. Plaseaza comanda" << endl;
			cout << "0. Iesire" << endl << endl << endl;
			cout << "Alege optiunea: ";
			cin >> optiune;
			cin.ignore(); // Ignora newline-ul ramas in buffer dupa citirea optiunii numerice.

			// AICI TREBUIE SA NU POTI INTRODUCE PRETUL . 
				// SAU DAI : PUTETI ALEGE DINTRE PRODUSELE .... CU CANTITATILE SI PRETURILE ... AI SCRIS GRESIT --> TE PUNE SA SCRII ALTCV
				// SCRAPING
			vector<string> produse;
			vector<string> cantitate;
			vector<string> pret;


			ifstream fisier1("Stoc.txt");
			if (!fisier1.is_open()) {
				cout << "Eroare la deschiderea fisierului 'Stoc.txt'." << endl;
				//	return false;
			}
			int nrlinii = 0;
			string linie;
			while (getline(fisier1, linie)) {
				nrlinii++;
			}
			fisier1.close();
			ifstream fisier("Stoc.txt");
			if (!fisier.is_open()) {
				cout << "Eroare la deschiderea fisierului 'Stoc.txt'." << endl;
				//return false;
			}
			//incepem loopurile sa scoatem tot ce e nevoie din fisier
			for (int i = 0; i < nrlinii; i++) {
				char caracter;
				string content = "";
				//loop pentru nume produs
				while (fisier.get(caracter)) {
					content += caracter;

					if (content == "Nume: ") {
						content = "";
						while (fisier.get(caracter) && caracter != ',') {
							content += caracter;
						}
						produse.push_back(content);
						break;
					}
				}
				//loop pentru cantitate
				content = "";
				while (fisier.get(caracter)) {
					content += caracter;

					if (content == " Cantitate: ") {
						content = "";
						while (fisier.get(caracter) && caracter != ',') {
							content += caracter;
						}
						cantitate.push_back(content);
						break;
					}
				}
				//loop pentru pret 
				content = "";
				while (fisier.get(caracter)) {
					content += caracter;

					if (content == " Pret: ") {
						content = "";
						while (fisier.get(caracter) && caracter != '\n') {
							content += caracter;
						}
						pret.push_back(content);
						break;
					}
				}
			}

			switch (optiune) {
			case 1: {
				string nume_produs;
				int cantitate_produs;
				double pret_produs;
				// am terminat cu scraping --> afisam
				cout << "------------------------------------------------------------------" << endl;
				cout << "Produsele valabile in magazin, cantitatile si preturile lor sunt: " << endl;
				for (int i = 0; i < produse.size(); i++) {
					cout << "produs: " << produse[i] << ", cantitate: " << cantitate[i] << ", pret: " << pret[i] << endl;
					//if (nume == numeUtilizatori[i] && paroleUtilizatori[i] == parola)
				}
				cout << "------------------------------------------------------------------" << endl << endl;
				cout << "Introduceti numele produsului:  ";
				cin >> nume_produs;
				int ok = 0;
				int pozitie;
				//testare daca in lista noastra exista produsul dat de utilizator
				for (int i = 0; i < produse.size(); i++) {
					if (nume_produs == produse[i])
					{
						ok = 1;
						pozitie = i;
					}
				}
				//daca exista produsul in stocul nostru:
				if (ok == 1) {
					cout << "------------------------------------------------------------------" << endl;
					cout << "Produsul " << produse[pozitie] << " exista in magazin in cantitatea " << cantitate[pozitie] << " si pretul " << pret[pozitie] << "." << endl;
					cout << "------------------------------------------------------------------" << endl << endl;
					cout << "Introduceti cantitatea dorita din produs: ";
					cin >> cantitate_produs;
					if (cantitate_produs > stoi(cantitate[pozitie]))
					{
						cout << "Nu avem stocul necesar. Am selectat cantitatea ceruta sa fie egala cu stocul curent." << endl;
						cantitate_produs = stoi(cantitate[pozitie]);
					}
					prodCos.push_back(nume_produs);
					cantCos.push_back(to_string(cantitate_produs));
					cantitate[pozitie] = to_string(stoi(cantitate[pozitie]) - cantitate_produs);
					inventar.clear();
					for (int i = 0; i < cantitate.size(); i++) {
						Produs prod(produse[i], stoi(cantitate[i]), stof(pret[i]));
						inventar.push_back(prod);
					}
					Produs::salveazaProduse();
					//inventar[pozitie].cantitateProdus = stoi(cantitate[pozitie]) - cantitate_produs;
					//cout << inventar[pozitie].cantitateProdus << endl;

					adauga_produs(produse[pozitie], cantitate_produs, stoi(pret[pozitie]));//aa

				}
				else cout << "Produsul nu exista in stocul nostru. " << endl;
				break;
			}
			case 2: {
				string nume_produs;
				cout << "------------------------------------------" << endl;
				cout << endl;
				afiseaza_cos();
				cout << "------------------------------------------" << endl;
				cout << endl;
				cout << "Introduceti numele produsului pe care doriti sa il stergeti: ";
				getline(cin, nume_produs);
				if (prodCos.size() == 0) {
					cout << "Este gol!" << endl;
				}
				bool gasit = 0;
				int pozCos = 0;
				int pozInv = 0;
				int nrGasit = 0;
				for (int i = 0; i < prodCos.size(); i++) {
					gasit = 0;
					if (nume_produs == prodCos[i]) {
						gasit = 1;
						pozCos = i;
						nrGasit++;
					}
					if (gasit == 1) {
						for (int i = 0; i < produse.size(); i++)
						{
							if (nume_produs == produse[i]) {
								pozInv = i;
							}
						}
						cantitate[pozInv] = to_string(stoi(cantitate[pozInv]) + stoi(cantCos[pozCos]));
						sterge_produs(nume_produs);

					}
				}
				for (int i = 0; i < prodCos.size(); i++) {
					if (prodCos[i] == nume_produs) {

						prodCos.erase(prodCos.begin() + i);
						cantCos.erase(cantCos.begin() + i);
					}
				}
				inventar.clear();
				for (int i = 0; i < cantitate.size(); i++) {
					Produs prod(produse[i], stoi(cantitate[i]), stof(pret[i]));
					inventar.push_back(prod);
				}
				Produs::salveazaProduse();
				break;
			}
			case 3:
				cout << "------------------------------------------" << endl;
				afiseaza_cos();
				cout << "------------------------------------------" << endl;
				cout << endl;
				break;
			case 4:
				plaseaza_comanda();
				break;
			case 0:
				cout << "La revedere!" << endl;
				break;
			default:
				cout << "Optiune invalida. Va rugam alegeti din nou." << endl;
			}
		} while (optiune != 0);
	}
};


int main() {
	//Constructor default MAGAZIN
	Magazin m;
	//Constructor cu toti parametrii MAGAZIN
	Magazin m1("Altex", "Bucuresti", 6);
	//Constructor default CLIENT
	Client c;
	//Constructor cu toti parametrii CLIENT
	Client c1("Alexandru", "Str.Verde", "@gmail", 732257483, 450.35);
	//Constructor default PRODUS
	Produs p;
	//Constructor cu toti parametrii PRODUS 
	Produs p1("Produs generic", 100, 200);
	//Constructor default PRODUS ALIMENTAR
	ProdusAlimentar pa;
	//Constructor cu toti parametrii PRODUS ALIMENTAR
	ProdusAlimentar pa1("Lapte", 5, 7, "10.11.2022", "10.12.2023");
	//Constructor default PRODUS ELECTROCASNIC
	ProdusElectrocasnic pe;
	//Constructor cu toti parametrii PRODUS ELECTROCASNIC
	ProdusElectrocasnic pe1("Aspirator", 1, 300, 2);


	int input;
	cout << "Bine ati venit la magazinul nostru online." << endl << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "Apasati '1' pentru a testa functionalitatea getter-ilor, setter-ilor, a constructorilor si a operatorilor. \nApasati '2' pentru a va loga in contul magazinului sau al clientului. " << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "Introduceti '1' sau '2' : ";
	do {

		cin >> input;
		if (input != 1 && input != 2) {
			cout << "Introduceti '1' sau '2': ";
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');  // daca nu pun astea 2 intra in bucla infinita . 
			// clear reseteaza flagul de eroare si ignore ignora restul liniei gresite 
		}
		else
			break;

	} while (true);
	bool continuaProgram = true;
	if (input == 1) {
		continuaProgram = true;
		int optiune;
		do {
			cout << "\nApelari:" << endl;
			cout << "1. Getteri" << endl;
			cout << "2. Setteri" << endl;
			cout << "3. Constructor copiere" << endl;
			cout << "4. Apelare operatori" << endl;
			cout << "5. Apelarea metodei de afisare pentru clasele 'Produs'" << endl;
			cout << "0. Iesire" << endl << endl << endl;
			cout << "Alege optiunea:";
			cin >> optiune;
			cin.ignore();

			switch (optiune) {
			case 1: {
				//Apelare getteri MAGAZIN
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare getteri magazin: " << endl;
				cout << m1.getnumeMagazin() << endl;
				cout << m1.getlocatieMagazin() << endl;
				cout << m1.getnrMagazine() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare getteri CLIENT
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare getteri client: " << endl;
				cout << c1.getnumeClient() << endl;
				cout << c1.getadresaClient() << endl;
				cout << c1.getemailClient() << endl;
				cout << c1.getnrTelefon() << endl;
				cout << c1.gettotalPlata() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare getteri PRODUS
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare getteri produs: " << endl;
				cout << p1.getnumeProdus() << endl;
				cout << p1.getcantitateProdus() << endl;
				cout << p1.getpretProdus() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare getteri PRODUS ALIMENTAR
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare getteri produs alimentar: " << endl;
				cout << pa1.getdataProducere() << endl;
				cout << pa1.getdataExpirare() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare getteri PRODUS ELECTROCASNIC
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare getteri produs electrocasnic: " << endl;
				cout << pe1.getnrAniGarantie() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				break;
			}
			case 2: {
				//Apelare setteri MAGAZIN
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare setteri magazin: " << endl;
				m1.setnumeMagazin("MediaGalaxy");
				m1.setlocatieMagazin("Pitesti");
				m1.setnrMagazine(3);
				cout << m1.getnumeMagazin() << endl;
				cout << m1.getlocatieMagazin() << endl;
				cout << m1.getnrMagazine() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare setteri CLIENT
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare setteri client: " << endl;
				c1.setnumeClient("Maria");
				c1.setadresaClient("Str.Mov");
				c1.setemailClient("@yahoo");
				c1.setnrTelefon(727658786);
				c1.settotalPlata(234.98);
				cout << c1.getnumeClient() << endl;
				cout << c1.getadresaClient() << endl;
				cout << c1.getemailClient() << endl;
				cout << c1.getnrTelefon() << endl;
				cout << c1.gettotalPlata() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare setteri PRODUS
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare setteri produs: " << endl;
				p.setnumeProdus("Produs generic 2");
				p.setcantitateProdus(20);
				p.setpretProdus(300);
				cout << p.getnumeProdus() << endl;
				cout << p.getcantitateProdus() << endl;
				cout << p.getpretProdus() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare setteri PRODUS ALIMENTAR
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare setteri produs alimentar: " << endl;
				pa.setdataProducere("20.11.2022");
				pa.setdataExpirare("20.12.2023");
				cout << pa.getdataProducere() << endl;
				cout << pa.getdataExpirare() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare setteri PRODUS ELECTROCASNIC
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare setteri produs electrocasnic: " << endl;
				pe.setnrAniGarantie(3);
				cout << pe.getnrAniGarantie() << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				break; }
			case 3: {
				//Apelare constructor de copiere MAGAZIN
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare constructor de copiere magazin: " << endl;
				Magazin m2(m1);
				cout << m2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare constructor de copiere CLIENT
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare constructor de copiere client: " << endl;
				Client c2(c1);
				cout << c2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare constructor de copiere PRODUS
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare constructor de copiere produs: " << endl;
				Produs p2(p1);
				cout << p2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare constructor de copiere PRODUS ALIMENTAR
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare constructor de copiere produs alimentar: " << endl;
				ProdusAlimentar pa2(pa1);
				cout << pa2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare constructor de copiere PRODUS ELECTROCASNIC
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare constructor de copiere produs electrocasnic: " << endl;
				ProdusElectrocasnic pe2(pe1);
				cout << pe2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				break;
			}
			case 4: {
				//Apelare constructor de copiere MAGAZIN
				Magazin m2(m1);
				//Apelare constructor de copiere CLIENT
				Client c2(c1);
				//Apelare constructor de copiere PRODUS
				Produs p2(p1);
				//Apelare constructor de copiere PRODUS ALIMENTAR
				ProdusAlimentar pa2(pa1);
				//Apelare constructor de copiere PRODUS ELECTROCASNIC
				ProdusElectrocasnic pe2(pe1);


				//Apelare operator= MAGAZIN
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator= magazin: " << endl;
				m = m2;
				cout << m;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator<< MAGAZIN
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator<< magazin: " << endl;
				cout << m2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator>> MAGAZIN
				//cout << "Apelare operator>> magazin: " << endl;
				//cin >> m;
				//cout << endl << endl;
				//Apelare operator= CLIENT
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator= client: " << endl;
				c = c2;
				cout << c;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator<< CLIENT
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator<< client: " << endl;
				cout << c2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator>> CLIENT
				//cout << "--------------------------------------------------------------" << endl;
				//cout << "Apelare operator>> client: " << endl;
				//cin >> c;
				//cout << "--------------------------------------------------------------" << endl;
				//cout << endl << endl;
				//Apelare operator= PRODUS
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator= produs: " << endl;
				p = p2;
				cout << p;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator<< PRODUS
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator<< produs: " << endl;
				cout << p2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator>> PRODUS
				//cout << "--------------------------------------------------------------" << endl;
				//cout << "Apelare operator>> produs: " << endl;
				//cin >> p;
				//cout << "--------------------------------------------------------------" << endl;
				//cout << endl << endl;
				//Apelare operator= PRODUS ALIMENTAR
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator= produs alimentar: " << endl;
				pa = pa2;
				cout << pa;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator<< PRODUS ALIMENTAR
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator<< produs alimentar: " << endl;
				cout << pa2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator>> PRODUS ALIMENTAR
				//cout << "--------------------------------------------------------------" << endl;
				//cout << "Apelare operator>> produs alimentar: " << endl;
				//cin >> m;
				//cout << "--------------------------------------------------------------" << endl;
				//cout << endl << endl;
				//Apelare operator= PRODUS ELECTROCASNIC
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator= produs electrocasnic: " << endl;
				pe = pe2;
				cout << pe;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator<< PRODUS ELECTROCASNIC
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apelare operator<< produs electrocasnic: " << endl;
				cout << pe2;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl;
				//Apelare operator>> PRODUS ELECTROCASNIC
				//cout << "--------------------------------------------------------------" << endl;
				//cout << "Apelare operator>> produs electrocasnic: " << endl;
				//cin >> pe;
				//cout << "--------------------------------------------------------------" << endl;
				//cout << endl << endl;
				break;
			}
			case 5: {
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				p1.afisare();
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				pa1.afisare();
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				pe1.afisare();
				cout << "--------------------------------------------------------------------------------------------------------" << endl;
				break;
			}
			case 0: {
				continuaProgram = false;
				break;
			}
			default:
				cout << "Optiune invalida! Va rugam selectati o optiune valida." << endl;
				break;
			}
		} while (continuaProgram);

	}
	input = 2;
	if (input == 2 or !continuaProgram) {

		InterfataLogare interfata;
		bool loop = true;
		while (loop) {
			// curata consola
			curataConsola();
			cout << "\nDin acest meniu puteti creea doar cont client." << endl;;
			cout << "\nPentru crearea unui cont de magazin, logati-va intr-un cont magazin si alegeti optiunea 'creare cont magazin'." << endl;;
			cout << "\nContul initial magazin are numele 'admin' si parola 'admin' si necesita fisierul 'magazin.txt' din arhiva." << endl;

			cout << "------------------------------------------" << endl;
			cout << "Apasati '1' pentru a va loga intr-un cont. \nApasati '2' pentru a creea un cont de client." << endl;
			cout << "------------------------------------------" << endl;


			int input;
			cout << endl;
			cout << "Introduceti '1' sau '2' : ";

			do {

				cin >> input;
				if (input != 1 && input != 2) {
					cout << "Introduceti '1' sau '2' : ";
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');  // daca nu pun astea 2 intra in bucla infinita . 
					// clear reseteaza flagul de eroare si ignore ignora restul liniei gresite 
				}
				else
					break;
			} while (true);

			if (input == 2)
				interfata.inregistrareUtilizator("utilizatori.txt");

			else if (input == 1)

			{
				cout << endl << endl << endl;
				cout << "In ce tip de cont vreti sa va logati?" << endl << endl;
				cout << "------------------------------------------" << endl;
				cout << "Apasati '1' pentru cont magazin. \nApasati '2' pentru cont client." << endl;
				cout << "------------------------------------------" << endl;

				// apesi 1 --> string nume fisier = cont_maagzin.txt else = utilizatori.txt ? si rulezi pt nume fisier ca parametru . ? 
				cout << "Introduceti '1' sau '2' : ";
				do {

					cin >> input;
					if (input != 1 && input != 2) {
						cout << "Introduceti '1' sau '2' : ";
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');  // daca nu pun astea 2 intra in bucla infinita . 
						// clear reseteaza flagul de eroare si ignore ignora restul liniei gresite 
					}
					else
						break;
				} while (true);

				if (input == 1)
				{
					cout << "\nVa logati intr-un cont magazin:" << endl;

					// pune ca parametru la Metoda numele fisierului cu conturile de la magazin magazin.txt

					interfata.getListaNumeParole("nume", "parola", "magazin.txt");
					cout << "scrieti numele:";
					string numeLogin;
					cin >> numeLogin;
					cout << "scrieti parola:";
					string pwdLogin;
					cin >> pwdLogin;
					if (interfata.verificaInformatiiUtilizatori(numeLogin, pwdLogin))
					{

						int optiune;
						do {
							cout << endl << endl;
							cout << "\nMeniu magazin:" << endl;
							cout << "1. Adauga produs" << endl;
							cout << "2. Editeaza produs" << endl;
							cout << "3. Sterge produs" << endl;
							cout << "4. Afiseaza produse" << endl;
							cout << "5. Prelucrare comanda" << endl;
							cout << "6. Creeaza cont magazin" << endl;
							cout << "0. Iesire" << endl << endl << endl;
							cout << "Alege optiunea:";
							cin >> optiune;
							cin.ignore();

							switch (optiune) {
							case 1:
								cout << "------------------------------------------" << endl;
								cout << "Produsele curente sunt: ";
								cout << endl;
								afisareContinutFisier("Stoc.txt");
								cout << "------------------------------------------" << endl;
								cout << endl;
								p.adaugaProdus();
								p.salveazaProduse();
								break;
							case 2:
								cout << "------------------------------------------" << endl;
								cout << "Produsele curente sunt: ";
								cout << endl;
								afisareContinutFisier("Stoc.txt");
								cout << "------------------------------------------" << endl;
								cout << endl;
								cout << "Introduceti numele produsului de editat: ";
								p.editeazaProdus();
								p.salveazaProduse();
								break;
							case 3:
								cout << "------------------------------------------" << endl;
								cout << "Produsele curente sunt: ";
								cout << endl;
								afisareContinutFisier("Stoc.txt");
								cout << "------------------------------------------" << endl;
								cout << endl;
								cout << "Introduceti numele produsului de sters: ";
								p.stergeProdus();
								p.salveazaProduse();
								break;
							case 4:
								cout << "------------------------------------------" << endl;
								cout << "Produsele curente sunt: ";
								cout << endl;
								afisareContinutFisier("Stoc.txt");
								cout << "------------------------------------------" << endl;
								break;
							case 5:
							{
								Comanda comenzi;
								int stocDisponibil = 20;
								cout << endl << endl;
								comenzi.meniu();                //Am afisat meniul comenzii prin utilizarea polimorfismului
								break;
							}
							case 6: {
								cout << "Vom creea un cont magazin." << endl;
								interfata.inregistrareUtilizator("magazin.txt");
							}
							case 0: {
								cout << "La revedere!" << endl;
								break;
							}
							default:
								cout << "Optiune invalida! Va rugam selectati o optiune valida." << endl;
								break;
							}
						} while (optiune != 0);
					}
				}
				else
					if (input == 2)
					{
						cout << "\nVa logati intr-un cont client: " << endl;
						interfata.getListaNumeParole("nume", "parola", "utilizatori.txt");
						cout << "scrieti numele:";
						string numeLogin;
						cin >> numeLogin;
						cout << "scrieti parola:";
						string pwdLogin;
						cin >> pwdLogin;
						if (interfata.verificaInformatiiUtilizatori(numeLogin, pwdLogin))
						{
							int optiune;
							do {
								cout << endl << endl;
								CosElectronic cos;
								cos.meniu();           //Am afisat meniul cosului electronic prin utilizarea polimorfismului
								break;

							} while (optiune != 0);
						}
						else cout << "Nu a mers. Mai incearca . " << endl;
					}
			}

			char x;

			cout << "Daca vreti sa reveniti la pagina de login introduceti 'y', iar daca nu vreti, introduceti 'n' : ";
			do {

				cin >> x;
				if (x != 'n' && x != 'y') {
					cout << "Introduceti '1' sau '2' : " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
					break;
			} while (true);


			if (x == 'n')
				loop = false;

		}
	}
	return 0;
}
