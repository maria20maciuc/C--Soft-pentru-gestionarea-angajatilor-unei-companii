#include "Header.h"
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <set>

Angajat::Angajat::Angajat(const char* nume, int salariu, const char* functie, const char* departament, vector<int>listaSubordonati) {
	this->salariu = salariu;
	this->nume = new char[strlen(nume) + 1];
	strcpy(this->nume, nume);
	this->functie = new char[strlen(functie) + 1];
	strcpy(this->functie, functie);
	this->departament = new char[strlen(departament) + 1];
	strcpy(this->departament, departament);
	this->listaSubordonati = listaSubordonati;
}


char* Angajat::getNume()
{
	return nume;
}

void Angajat::setSalariu(int salariu)
{
	this->salariu = salariu;
}
int Angajat::getSalariu()
{
	return salariu;
}

char* Angajat::getFunctie()
{
	return functie;
}
char* Angajat::getDepartament()
{
	return departament;
}

void Angajat::setNume(char* nume) {
	if (this->nume) { delete[] this->nume; }
	this->nume = new char[strlen(nume) + 1];
	strcpy(this->nume, nume);
}

void Angajat::setDepartament(char* departament) {
	if (this->departament) { delete[] this->departament; }
	this->departament = new char[strlen(departament) + 1];
	strcpy(this->departament, departament);
}

istream& operator>>(istream& in, Angajat& angajat) {
	string nume, departament;
	unsigned int salariu;
	//cout << "Da nume: " << endl;
	getline(in, nume, '\t');
	//cout << "Da departament: " << endl;
	getline(in, departament, '\t');
	//cout << "Da salariu: " << endl;
	in >> salariu;

	//if(angajat.nume) { delete[] angajat.nume; } de revazut
	angajat.nume = new char[nume.size() + 2];
	strcpy(angajat.nume, nume.c_str());

	//if(angajat.departament) { delete[] angajat.departament; } de revazut
	angajat.departament = new char[departament.size() + 2];
	strcpy(angajat.departament, departament.c_str());

	angajat.salariu = salariu;

	//cout << salariu << '\n';

	int nrSubordonati, id;
	//cout << "Da numar subordonati: " << endl;
	in >> nrSubordonati;
	//cout << "Da id-ul subordonatilor: " << endl;
	for (int i = 0; i < nrSubordonati; i++) {
		in >> id;
		angajat.adaugaSubordonat(id); // angajat.listaSubordonati.push_back(id);
	}

	return in;
}



Manager::Manager(const char* nume, int salariu, const char* functie, const char* departament, vector<int> listaSubordonati) : Angajat(nume, salariu, functie, departament, listaSubordonati)
{
}

vector<int> Manager::getListaSubordonati()
{
	return listaSubordonati;
}

void Manager::stergeAngajat(int i) {
	listaSubordonati.erase(listaSubordonati.begin() + i);
}

Muncitor::Muncitor() : Angajat() {
	this->functie = new char[strlen("muncitor") + 1];
	strcpy(this->functie, "muncitor");
}

Muncitor::Muncitor(const char* nume, int salariu, const char* departament) : Angajat(nume, salariu, "muncitor", departament, {})
{
}

CEO::CEO(const char* nume, int salariu, vector<int> listaSubordonati) : Manager(nume, salariu, "CEO", "ce sa pun aici?", listaSubordonati)
{
}

void CEO::adaugaSubordonat(int p)
{
	//if (strcmp(p->getFunctie(), "SefDepartament") == 0)

	listaSubordonati.push_back(p);

}

SefDepartament::SefDepartament(const char* nume, int salariu, const char* departament, vector<int>) : Manager(nume, salariu, "CEO", departament, listaSubordonati)
{
}
void SefDepartament::adaugaSubordonat(int p)
{
	//if (strcmp(p->getFunctie(), "TeamLeader") == 0)

	listaSubordonati.push_back(p);

}

Manager::Manager() : Angajat() {

}

TeamLeader::TeamLeader() : Manager() {
	this->functie = new char[strlen("team leader") + 1];
	strcpy(this->functie, "team leader");
}

SefDepartament::SefDepartament() : Manager() {
	this->functie = new char[strlen("sef departament") + 1];
	strcpy(this->functie, "sef departament");
}

CEO::CEO() : Manager() {
	this->functie = new char[strlen("CEO") + 1];
	strcpy(this->functie, "CEO");
}

TeamLeader::TeamLeader(const char* nume, int salariu, const char* departament, vector<int> listaSubordonati) : Manager(nume, salariu, "TeamLeader", departament, listaSubordonati)
{
}

void TeamLeader::adaugaSubordonat(int p)
{
	// if (strcmp(p->getFunctie(), "muncitor") == 0)

	listaSubordonati.push_back(p);
}


template<typename T>
int Meniu<T>::index = 0;

template<typename T>
void Meniu<T>::operator+=(T p)
{
	index++;
	ListaAngajati.push_back(p);
}


template<typename T>
int Meniu<T>::totalCheltuieliSalarii()
{
	int s = 0;
	for (int i = 0; i < ListaAngajati.size(); i++)
		s += ListaAngajati[i].getSalariu();
	return s;
}

template<typename T>
void Meniu<T>::modificaSalariu(int i, int salariu)
{
	ListaAngajati[i].setSalariu(salariu);
}

template<typename T>
void Meniu<T>::afiseazaInfo(int p)
{
	T temp = ListaAngajati[p];
	cout << "--------------------------------\n";
	cout << "Nume: " << temp.getNume() << '\n';
	cout << "Functie: " << temp.getFunctie() << '\n';
	cout << "Departament: " << temp.getDepartament() << '\n';
	cout << "Salariu: " << temp.getSalariu() << '\n';

	cout << "Are " << temp.getListaSubordonati().size() << " angajati";
	if (temp.getListaSubordonati().size() == 0) {
		cout << ".\n";
	}
	else {
		cout << " cu id-urile: ";
		vector<int> listaSubordonati = temp.getListaSubordonati();
		for (int i = 0; i < (listaSubordonati.size()); i++) {
			cout << listaSubordonati[i] << ' ';
		}

		cout << '\n';
	}

}

template<typename T>
void Meniu<T>::afiseazaInfoToti()
{
	for (int i = 0; i < ListaAngajati.size(); i++)
		afiseazaInfo(i);
}

template<typename T>
vector<T> Meniu<T>::getListaAngajati() {
	return this->ListaAngajati;
}
template<typename T>
T* Meniu<T>::getAngajat(int id) {
	return &(this->ListaAngajati[id]);
}

Angajat::Angajat(const Angajat& angajat) {
	this->salariu = angajat.salariu;
	this->nume = new char[strlen(angajat.nume) + 1];
	strcpy(this->nume, angajat.nume);
	this->functie = new char[strlen(angajat.functie) + 1];
	strcpy(this->functie, angajat.functie);
	this->departament = new char[strlen(angajat.departament) + 1];
	strcpy(this->departament, angajat.departament);
	this->listaSubordonati = angajat.listaSubordonati;
}

Muncitor::Muncitor(const Muncitor& angajat) {
	this->salariu = angajat.salariu;
	this->nume = new char[strlen(angajat.nume) + 1];
	strcpy(this->nume, angajat.nume);
	this->functie = new char[strlen(angajat.functie) + 1];
	strcpy(this->functie, angajat.functie);
	this->departament = new char[strlen(angajat.departament) + 1];
	strcpy(this->departament, angajat.departament);
	this->listaSubordonati = angajat.listaSubordonati;
}

set<string> setDepartament;


void citire(istream& in, Meniu<Muncitor>& meniuMuncitori, Meniu<TeamLeader>& meniuTL,
	Meniu<SefDepartament>& meniuSD, Meniu<CEO>& meniuCEO) {
	string functie;

	while (in) {
		getline(in, functie, '\t');


		if (!functie.compare("Muncitor")) {
			Muncitor temp;
			in >> temp;
			meniuMuncitori += temp;
		}
		else if (!functie.compare("Team Leader")) {
			TeamLeader temp;
			in >> temp;
			meniuTL += temp;
		}
		else if (!functie.compare("Sef Departament")) {
			SefDepartament temp;
			in >> temp;
			meniuSD += temp;

			string departament = temp.getDepartament();
			if (setDepartament.count(departament) == 0)
				setDepartament.insert(departament);

		}
		else if (!functie.compare("CEO")) {
			CEO temp;
			in >> temp;
			meniuCEO += temp;
		}

		string temp;
		getline(in, temp);
	}
}

int main()
{
	int oper;
	Meniu<Muncitor> meniuMuncitori;
	Meniu<TeamLeader> meniuTL;
	Meniu<SefDepartament> meniuSD;
	Meniu<CEO> meniuCEO;

	ifstream fin("Angajati.txt");
	citire(fin, meniuMuncitori, meniuTL, meniuSD, meniuCEO);
	fin.close();
	//Verificare corectitudine fisier
	cout << "Verificari fisier:" << endl;
	//sunt muncitori cu mai multi team leaderi?
	int areSuperior[100] = { 0 };
	for (int j = 0; j < meniuTL.getListaAngajati().size(); j++) {//parcurg lista de TM
		vector<int> listaSub = meniuTL.getListaAngajati()[j].getListaSubordonati();//subordonatii unui TL cu id=j
		//meniuTL.getAngajat(j)->getListaSubordonati();
		//meniuTL.getListaAngajati()[j].getListaSubordonati()
		for (int k = 0; k < listaSub.size(); k++) {
			if (listaSub[k]>= meniuMuncitori.index) {
				cout << "Nu exista muncitorul cu id="<< listaSub[k] <<" pentru ca id > (index muncitori -1)."<<endl;
			}
			else {
				if (areSuperior[listaSub[k]]) {
					//cout << areSuperior[listaSub[k]] << endl;
					cout << "Eroare fisier. Muncitorul cu id=" << listaSub[k] << " are mai multi Team Leader." << endl;
					meniuTL.getAngajat(j)->stergeAngajat(k);
					cout << "Stergem muncitorul de pe pozitia " << k << " in lista de subordonati al Team Leader-ului cu id=" << j<<endl;
					/*for (int p = 0; p < listaSub.size(); p++)
						cout << listaSub[p] << " ";
					cout << endl;*/
				}
				else areSuperior[listaSub[k]] = 1;
			}
		}
	}
	//Sunt muncitori care nu au team leader?
	for (int i = 0; i < meniuMuncitori.index; i++)
		if (areSuperior[i] == 0)
			cout << "Muncitorul cu id=" << i << " nu exista pentru ca nu are Team Leader." << endl;


	//sunt team leaderi cu mai multi sefi departament?
	for(int i=0;i<100;i++)
	areSuperior[i]=0;

	for (int j = 0; j < meniuSD.getListaAngajati().size(); j++) {//parcurg lista de SD
		vector<int> listaSub = meniuSD.getListaAngajati()[j].getListaSubordonati();//subordonatii unui SD cu id=j
		for (int k = 0; k < listaSub.size(); k++) {
			if (listaSub[k] >= meniuTL.index) {//exista id-ul acestui TL
				cout << "Nu exista team leader-ul cu id=" << listaSub[k] << " pentru ca id > (index team leader -1)." << endl;
			}
			else {
				if (areSuperior[listaSub[k]]) {
					//cout << areSuperior[listaSub[k]] << endl;
					cout << "Eroare fisier. Team leader-ul cu id=" << listaSub[k] << " are mai multi Sefi Departament." << endl;
					meniuSD.getAngajat(j)->stergeAngajat(k);
					cout << "Stergem team leader-ul de pe pozitia " << k << " in lista de subordonati al Sefului de Departament cu id=" << j << endl;
					/*for (int p = 0; p < listaSub.size(); p++)
						cout << listaSub[p] << " ";
					cout << endl;*/
				}
				else areSuperior[listaSub[k]] = 1;
			}
		}
	}
	//Sunt muncitori care nu au team leader?
	for (int i = 0; i < meniuTL.index; i++)
		if (areSuperior[i] == 0)
			cout << "Team Leader-ul cu id=" << i << " nu exista pentru ca nu are sef Departament." << endl;

	//meniuMuncitori.afiseazaInfoToti();
	//meniuTL.afiseazaInfoToti();
	while (true) {
		bool exit = 0;
		cout << "Meniu\n" << "1. Afiseaza informatii\n";
		cout << "2. Adauga angajat\n";
		cout << "3. Modifica salariu\n";
		cout << "4. Afiseaza cheltuieli\n";
		cout << "5. Exit\n";
		cout << "Introdu optiunea ";
		cin >> oper;
		cin.get();
		switch (oper) {
		case 1: {

			string functie;
			//getline(cin, functie);
			cout << "Intodu functie(Muncitor, Team Leader, Sef Departament,CEO):" << endl;
			getline(cin, functie);
			int id;
			cout << "Intodu id<0 daca vrei sa afli informatii despre toti angajatii." << endl;
			cout << "Intodu id>=0 daca vrei sa afli informatii despre angajatul cu acest id." << endl;
			cin >> id;
			if (id < 0) {
				//cout << "Sunt aici" << endl;
				if (!functie.compare("Muncitor")) {

					meniuMuncitori.afiseazaInfoToti();
				}
				else if (!functie.compare("Team Leader")) {

					meniuTL.afiseazaInfoToti();
				}
				else if (!functie.compare("Sef Departament")) {

					meniuSD.afiseazaInfoToti();
				}
				else if (!functie.compare("CEO")) {

					meniuCEO.afiseazaInfoToti();
				}

			}
			else {//folosesc ListaAngajati de la superior?
				//vreau sa afisez info pt angajatul cu id dat
				if (!functie.compare("Muncitor")) {
					meniuMuncitori.afiseazaInfo(id);
				}
				else if (!functie.compare("Team Leader")) {
					meniuTL.afiseazaInfo(id);
				}
				else if (!functie.compare("Sef Departament")) {
					meniuSD.afiseazaInfo(id);
				}
				else if (!functie.compare("CEO")) {
					meniuCEO.afiseazaInfo(id);
				}
			}

			break;
		}
		case 2: {
			string functie;
			cout << "Introdu functia(Muncitor, Team Leader, Sef Departament,CEO):" << endl;
			getline(cin, functie);
			int idSef;
			cout << "Introdu idSef:" << endl;
			cin >> idSef;
			//cout << meniuTL.index << endl;
			
				if (!functie.compare("Muncitor")) {
					if ((meniuTL.index - 1) >= idSef && idSef >= 0) {
						Muncitor temp;
						cout << "Da informatiile noului angajat:" << endl;
						cout << "	1.da_nume+apasa tasta tab" << endl;
						cout << "	2.da_departament+apasa tasta tab" << endl;
						cout << "	3.da_salariu+apasa tasta space/enter" << endl;
						cout << "	4.da_nr_subordonati+apasa tasta space/enter" << endl;
						cout << "	4.da_id_subordonati+apasa tasta space/enter intre valorile furnizate" << endl;
						cin >> temp;

						if (strcmp(temp.getDepartament(), meniuTL.getListaAngajati()[idSef].getDepartament()) == 0) {
							meniuMuncitori += temp;
							meniuTL.getListaAngajati()[idSef].adaugaSubordonat(meniuMuncitori.index);
						}
						else
							cout << "Nu se poate adauga. Departamentul nu coincide cu al Team Leader-ului."<<endl;
					}
					else
					cout << "Nu se poate adauga. Nu exista acest Team Leader." << endl;
				
				}
			
			else if (!functie.compare("Team Leader")) {
					if ((meniuTL.index - 1) >= idSef && idSef >= 0) {
						TeamLeader temp;
						cout << "Da informatiile noului angajat:" << endl;
						cout << "	1.da_nume+apasa tasta tab" << endl;
						cout << "	2.da_departament+apasa tasta tab" << endl;
						cout << "	3.da_salariu+apasa tasta space/enter" << endl;
						cout << "	4.da_nr_subordonati+apasa tasta space/enter" << endl;
						cout << "	4.da_id_subordonati+apasa tasta space/enter intre valorile furnizate" << endl;
						cin >> temp;
						if (strcmp(temp.getDepartament(), meniuSD.getListaAngajati()[idSef].getDepartament()) == 0) {
							meniuTL += temp;
							meniuSD.getListaAngajati()[idSef].adaugaSubordonat(meniuTL.index);
						}
						else
							cout << "Nu se poate adauga. Departamentul nu coincide cu al Team Leader-ului." << endl;
					}
					else
						cout << "Nu se poate adauga. Nu exista acest Sef Departament." << endl;
			}
			else if (!functie.compare("Sef Departament")) {
				SefDepartament temp;
				cout << "Da informatiile noului angajat:" << endl;
				cout << "	1.da_nume+apasa tasta tab" << endl;
				cout << "	2.da_departament+apasa tasta tab" << endl;
				cout << "	3.da_salariu+apasa tasta space/enter" << endl;
				cout << "	4.da_nr_subordonati+apasa tasta space/enter" << endl;
				cout << "	4.da_id_subordonati+apasa tasta space/enter intre valorile furnizate" << endl;
				cin >> temp;
				string departament = temp.getDepartament();
				if (setDepartament.count(departament) == 0) {
					meniuSD += temp;
					meniuCEO.getListaAngajati()[idSef].adaugaSubordonat(meniuSD.index);
					setDepartament.insert(departament);
				}
				else
					cout << "Nu poate fi adaugat. Exista deja un sef la acest departament."<<endl;

			}
			else if (!functie.compare("CEO")) {
				if (meniuCEO.getListaAngajati().size() == 0) {
					CEO temp;
					cout << "Da informatiile noului angajat:" << endl;
					cout << "	1.da_nume+apasa tasta tab" << endl;
					cout << "	2.da_departament+apasa tasta tab" << endl;
					cout << "	3.da_salariu+apasa tasta space/enter" << endl;
					cout << "	4.da_nr_subordonati+apasa tasta space/enter" << endl;
					cout << "	4.da_id_subordonati+apasa tasta space/enter intre valorile furnizate" << endl;
					cin >> temp;
					meniuCEO += temp;
				}
				else
					cout << "Nu pot aduga alt CEO." << endl;
			}
			break;
		}
		case 3: {
			string functie;
			cout << "Da functia angajatului caruia vrei sa-i schimbi salariul (Muncitor, Team Leader, Sef Departament,CEO):"<<endl;
			getline(cin, functie);
			int id;
			cout << "Da id-ul angajatului caruia vrei sa-i schimbi salariul."<<endl;
			cin >> id;
			int s;
			cout << "Da noul salariu: ";
			cin >> s;

			if (!functie.compare("Muncitor")) {

				meniuMuncitori.modificaSalariu(id, s);
			}
			else if (!functie.compare("Team Leader")) {

				meniuTL.modificaSalariu(id, s);
			}
			else if (!functie.compare("Sef Departament")) {

				meniuSD.modificaSalariu(id, s);
			}
			else if (!functie.compare("CEO")) {

				meniuCEO.modificaSalariu(id, s);
			}
			break;
		}
		case 4: {
			int id;//1 sau 2
			cout << "Introdu 1 daca vrei sa vezi totalul salariilor unui anumit tip de angajati, sau 2 pentru toti angajatii: ";
			cin >> id;
			cin.get();
			if (id == 1) {
				string functie;
				cout << "Introdu functia: ";
				getline(cin, functie);

				cout << "Total salariu " << functie << ": ";
				if (!functie.compare("Muncitor")) {
					cout << meniuMuncitori.totalCheltuieliSalarii();
				}
				else if (!functie.compare("Team Leader")) {
					cout << meniuTL.totalCheltuieliSalarii();
				}
				else if (!functie.compare("Sef Departament")) {
					cout << meniuSD.totalCheltuieliSalarii();
				}
				else if (!functie.compare("CEO")) {
					cout << meniuCEO.totalCheltuieliSalarii();
				}
				cout << '\n';
			}
			else {
				int s;
				s = meniuMuncitori.totalCheltuieliSalarii() +
					meniuTL.totalCheltuieliSalarii() +
					meniuSD.totalCheltuieliSalarii() +
					meniuCEO.totalCheltuieliSalarii();
				cout << s<<endl;
			}
			break;
		}
		default: {
			exit = 1;
			cout << "Vei iesi din meniu.\n";
			break;
		}
		}
		if (exit) break;
	}

	return 0;
}
