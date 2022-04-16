#include<iostream>
#include<vector>
#include<fstream>
#include <cstring>
using namespace std;
#pragma warning(disable:4996)

class Angajat {
protected:
	//int id = 0;
	char* nume;
	int salariu;
	char* functie;
	char* departament;
	vector<int> listaSubordonati;
	//vector<Angajat*> listaSubordonati;
public:
	Angajat() {
		
		this->nume = new char[strlen("nume dummy") + 1];
		strcpy(this->nume, "nume dummy");
	}

	/*Angajat() {

		this->nume = new char[strlen("") + 1];
		strcpy(this->nume, "");
		this->salariu = 0;
	}*/

	Angajat(const Angajat&);
	Angajat(const char*, int, const char*, const char*, vector<int>);
	//~Angajat();
	char* getNume();
	char* getFunctie();
	char* getDepartament();
	int  getSalariu();
	virtual vector<int> getListaSubordonati() = 0;

	void setSalariu(int);
	void setNume(char*);
	void setDepartament(char*);

	virtual void adaugaSubordonat(int) = 0;
	friend istream& operator>>(istream& in, Angajat&);
	friend ostream& operator<<(ostream& out, Angajat&);

};

class Manager :public Angajat {

public:
	Manager();
	Manager(const char*, int, const char*, const char*, vector<int>);
	virtual void adaugaSubordonat(int) = 0;
	vector<int> getListaSubordonati();
	void stergeAngajat(int);//indicele din lista de subordonati
	
};

class Muncitor :public Angajat {
public:
	Muncitor();
	Muncitor(const Muncitor&);
	Muncitor(const char*, int, const char*);
	void adaugaSubordonat(int) {}
	vector<int> getListaSubordonati() { return {}; }
};

class CEO :public Manager {
public:
	CEO();
	CEO(const char*, int, vector<int>);
	void adaugaSubordonat(int);
};
class SefDepartament :public Manager {
public:
	SefDepartament();
	SefDepartament(const char*, int, const char*, vector<int>);
	void adaugaSubordonat(int);
};
class TeamLeader :public Manager {
public:
	TeamLeader();
	TeamLeader(const char*, int, const char*, vector<int>);
	void adaugaSubordonat(int);
};


template<typename T>
class Meniu {
	vector<T> ListaAngajati;
public:
	static int index;

	int totalCheltuieliSalarii();
	void afiseazaInfo(int);
	void afiseazaInfoToti();
	void modificaSalariu(int, int);
	void operator+=(T);

	vector<T> getListaAngajati();
	T* getAngajat(int);
	
};