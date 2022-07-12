#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

bool isInteger(char* s){ // converteste siruri de caractere la int
    for(int i = 0; i < strlen(s); i++)
        if(!isdigit(s[i]))
            return false;
    return true;
}
bool isReal(char* s){ //converteste siruri de caractere la float
    if(s[0] == '.' && !s[1])
        return false;
    int nr_points = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == '.'){
            nr_points++;
            if(nr_points > 1) //verific daca utilizatorul introduce mai multe virgule la numere reale
                return false;
            continue;
        }
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

class Produs{
private:
    char* denumire = NULL;
    char* descriere = NULL;
    float pret_cumparare = -1;
    float pret_vanzare = -1;
    int cantitate = -1;

    const int id;
    static int id_crt;
    static vector<Produs*> obiecte; //vector ce memoreaza un pointer pentru toate obiectele create
public:
    Produs();
    Produs(char* denumire, char* descriere, float pret_cumparare, float pret_vanzare, int cantitate);
    Produs(char* denumire, float pret_cumparare, float pret_vanzare, int cantitate);
    Produs(char* denumire);
    Produs(const Produs& p);
    ~Produs();
    int getID();
    char* getDenumire();
    char* getDescriere();
    float getPretCumparare();
    float getPretVanzare();
    int getCantitate();
    int getIDCurent();
    void setDenumire(char* denumire);
    void setDescriere(char* descriere);
    void setPretCumparare(float pret_cumparare);
    void setPretVanzare(float pret_vanzare);
    void setCantitate(int cantitate);
    Produs& operator=(const Produs& p);
    friend istream& operator>>(istream& in, Produs& p);
    friend ostream& operator<<(ostream& out, Produs& p);
    Produs& operator[](int id);
    Produs& operator++();
    Produs& operator++(int dummy);
    Produs& operator--();
    Produs& operator--(int dummy);
    int operator+(const Produs& p2);
    int operator*(const Produs& p2);
    Produs& operator+=(int x);
    Produs& operator-=(int x);
    operator int() const;
    bool operator<(const Produs& p2);
    bool operator==(const Produs& p2);

    static void Afiseaza_Toate_Produsele();
    static void Afiseaza_Stoc_Epuizat();
    static float Profit_Maxim_Disponibil();
};

int Produs::id_crt = 0;
vector<Produs*> Produs::obiecte;
Produs::Produs():id(id_crt++){ //constructor fara parametrii
    obiecte.push_back(this);
}
Produs::Produs(char* denumire, char* descriere, float pret_cumparare, float pret_vanzare, int cantitate):id(id_crt++){ //constructor cu toti parametrii
    this->denumire = new char[strlen(denumire) + 1];
    strcpy(this->denumire, denumire);
    this->descriere = new char[strlen(descriere) + 1];
    strcpy(this->descriere, descriere);
    this->cantitate = cantitate;
    this->pret_cumparare = pret_cumparare;
    this->pret_vanzare = pret_vanzare;
    obiecte.push_back(this);
}
Produs::Produs(char* denumire, float pret_cumparare, float pret_vanzare, int cantitate):id(id_crt++){
    this->denumire = new char[strlen(denumire) + 1];
    strcpy(this->denumire, denumire);
    this->pret_cumparare = pret_cumparare;
    this->pret_vanzare = pret_vanzare;
    this->cantitate = cantitate;
    obiecte.push_back(this);
}
Produs::Produs(char* denumire):id(id_crt++){
    this->denumire = new char[strlen(denumire) + 1];
    strcpy(this->denumire, denumire);
    obiecte.push_back(this);
}
Produs::Produs(const Produs& p):id(p.id){ //constructor de copiere
    this->denumire = new char[strlen(p.denumire) + 1];
    strcpy(this->denumire, p.denumire);
    if(p.descriere){
        this->descriere = new char[strlen(p.descriere) + 1];
        strcpy(this->descriere, p.descriere);
    }
    this->cantitate = p.cantitate;
    this->pret_cumparare = p.pret_cumparare;
    this->pret_vanzare = p.pret_vanzare;
}
Produs::~Produs(){ //destructor
    if(this->denumire)
        delete[] this->denumire;
    if(this->descriere)
        delete[] this->descriere;
    this->cantitate = -1;
}
int Produs::getID(){
    return this->id;
}
char* Produs::getDenumire(){
    if(this->denumire)
        return this->denumire;
    else
        return "Denumire indisponibila";
}
char* Produs::getDescriere(){
    if(this->descriere)
        return this->descriere;
    else
        return "Descriere indisponibila";
}
float Produs::getPretCumparare(){
    return this->pret_cumparare;
}
float Produs::getPretVanzare(){
    return this->pret_vanzare;
}
int Produs::getCantitate(){
    return this->cantitate;
}
int Produs::getIDCurent(){
    return id_crt;
}
void Produs::setDenumire(char* denumire){
    if(this->denumire)
        delete[] this->denumire;
    this->denumire = new char[strlen(denumire) + 1];
    strcpy(this->denumire, denumire);
}
void Produs::setDescriere(char* descriere){
    if(this->descriere)
        delete[] this->descriere;
    this->descriere = new char[strlen(descriere) + 1];
    strcpy(this->descriere, descriere);
}
void Produs::setPretCumparare(float pret_cumparare){
    this->pret_cumparare = pret_cumparare;
}
void Produs::setPretVanzare(float pret_vanzare){
    this->pret_vanzare = pret_vanzare;
}
void Produs::setCantitate(int cantitate){
    this->cantitate = cantitate;
}
Produs& Produs::operator=(const Produs& p){
    if(this != &p){
        if(this->descriere)
            delete[] this->descriere;
        if(this->denumire)
            delete[] this->denumire;
        if(p.descriere){
            this->descriere = new char[strlen(p.descriere) + 1];
            strcpy(this->descriere, p.descriere);
        }
        this->denumire = new char[strlen(p.denumire) + 1];
        strcpy(this->denumire, p.denumire);
        this->cantitate = p.cantitate;
        this->pret_cumparare = p.pret_cumparare;
        this->pret_vanzare = p.pret_vanzare;
    }

    return *this;
}





istream& operator>>(istream& in, Produs& p){
    char denumire[101], descriere[101], cantitate[10], pret[10];
    strcpy(denumire, "");
    strcpy(descriere, "");
    while(strcmp("", denumire) == 0){
        cout << "Introduceti denumirea: ";
        in.getline(denumire, 101);
    }
    while(strcmp("", descriere) == 0){
        cout << "Introduceti descrierea: ";
        in.getline(descriere, 101);
    }
    if(p.denumire)
        delete[] p.denumire;
    p.denumire = new char[strlen(denumire + 1)];
    strcpy(p.denumire, denumire);
    if(p.descriere)
        delete[] p.descriere;
    p.descriere = new char[strlen(descriere) + 1];
    strcpy(p.descriere, descriere);
    while(true){
        cout << "Introduceti cantitatea(numar intreg): ";
        in.getline(cantitate, 10);
        if(strcmp("", cantitate) == 0){
            cout << '\n';
            continue;
        }
        if(isInteger(cantitate))
            break;
    }
    p.cantitate = atoi(cantitate);
    while(true){
        cout << "Introduceti pretul de cumparare(numar real): ";
        in.getline(pret, 10);
        if(strcmp("", pret) == 0){
            cout << '\n';
            continue;
        }
        if(isReal(pret))
            break;
    }
    p.pret_cumparare = (float)atof(pret);
    while(true){
        cout << "Introduceti pretul de vanzare(numar real): ";
        cin.getline(pret, 10);
        if(strcmp("", pret) == 0){
            cout << '\n';
            continue;
        }
        if(isReal(pret))
            break;
    }
    cout << '\n';
    p.pret_vanzare = (float)atof(pret);

    return in;
}
ostream& operator<<(ostream& out, Produs& p){
    out << "ID: " << p.getID() << '\n';
    out << "Denumire: " << p.getDenumire() << '\n';
    out << "Descriere: "<< p.getDescriere() << '\n';
    out << "Cantitate: " << p.getCantitate()<< '\n';
    out << "Pret cumparare: " << p.getPretCumparare() << '\n';
    out << "Pret vanzare: " << p.getPretVanzare() << '\n';

    return out;
}
Produs& Produs::operator[](int i){ //supraincarc operatorul de indexare pentru vectorul de pointeri
    if(i < Produs::id_crt)
        return *obiecte.at(i);
    else return *obiecte.at(Produs::id_crt - 1);
}
Produs& Produs::operator++(){
    this->cantitate = this->cantitate + 1;
    return *this;
}
Produs& Produs::operator++(int dummy){
    this->cantitate = this->cantitate + 1;
    return *this;
}
Produs& Produs::operator--(){
    this->cantitate = this->cantitate - 1;
    return *this;
}
Produs& Produs::operator--(int dummy){
    this->cantitate = this->cantitate - 1;
    return *this;
}
int Produs::operator+(const Produs& p2){
    return (this->pret_vanzare - this->pret_cumparare) + (p2.pret_vanzare - p2.pret_cumparare);
}
int Produs::operator*(const Produs& p2){
    return (this->pret_vanzare - this->pret_cumparare) * (p2.pret_vanzare - p2.pret_cumparare);
}
Produs& Produs::operator+=(int x){
    this->cantitate = this->cantitate + x;
    return *this;
}
Produs& Produs::operator-=(int x){
    this->cantitate = this->cantitate - x;
    return *this;
}
Produs::operator int() const{
    return this->pret_vanzare - this->pret_cumparare;
}
bool Produs::operator<(const Produs& p2){
    bool r = (this->pret_vanzare - this->pret_cumparare) < (p2.pret_vanzare - p2.pret_cumparare);
    return r;
}
bool Produs::operator==(const Produs& p2){
    bool r = (this->pret_vanzare - this->pret_cumparare) == (p2.pret_vanzare - p2.pret_cumparare);
    return r;
}
void Produs::Afiseaza_Toate_Produsele(){
    for(int i = 1; i < id_crt; i++){
            if(obiecte.at(i)->cantitate >= 0){
                cout << *obiecte.at(i);
                cout << "......................................." << '\n';
            }
    }
}
void Produs::Afiseaza_Stoc_Epuizat(){
    for(int i = 1; i < id_crt; i++)
        if(obiecte.at(i)->getCantitate() == 0)
            cout << obiecte.at(i)->getID() << " " << obiecte.at(i)->getDenumire() << '\n';
}
float Produs::Profit_Maxim_Disponibil(){ //calculez cat as obtine daca as vinde toate produsele de pe stoc
    float profit = 0;
    for(int i = 1; i < id_crt; i++)
        if(obiecte.at(i)->cantitate > 0)
            profit += (obiecte.at(i)->pret_vanzare - obiecte.at(i)->pret_cumparare) * obiecte.at(i)->cantitate;
    return profit;
}

class Venit{
private:
    double suma = -1;
    Produs& produs_cumparat; //o referinta catre produsul care este vandut

    const int id;
    static int id_crt;
    static double total; //o variabila utila ce retine totalul de venituri
    static vector<Venit*> obiecte;

public:
    //nu am constructor fara parametrii, deoarece trebuie sa initializez referinta
    Venit(Produs& p);
    Venit(double suma, Produs& p);
    Venit(const Venit& v);
    ~Venit();
    int getID();
    double getSuma();
    Produs& getProdus();
    void setSuma(double x);
    Venit& operator=(const Venit& v);
    friend istream& operator>>(istream& in, Venit& p);
    friend ostream& operator<<(ostream& out, Venit& p);
    Venit& operator[](int i);
    Venit& operator++();
    Venit& operator++(int dummy);
    Venit& operator--(int dummy);
    Venit& operator--();
    double operator+(const Venit& v2);
    double operator*(const Venit& v2);
    operator double() const;
    bool operator<(const Venit& v2);
    bool operator==(const Venit& v2);

    static double getTotal();
    static void Afiseaza_Venituri();
};

int Venit::id_crt = 0;
double Venit::total = 0;
vector<Venit*> Venit::obiecte;

Venit::Venit(Produs& p):id(id_crt++), produs_cumparat(p){
    obiecte.push_back(this);
}
Venit::Venit(double suma, Produs& p):id(id_crt++), produs_cumparat(p){
    this->suma = suma;
    total = total + suma;
    obiecte.push_back(this);
}
Venit::Venit(const Venit& v):id(v.id), produs_cumparat(v.produs_cumparat){
    this->suma = v.suma;
    total = total + v.suma;
    obiecte.push_back(this);
}
Venit::~Venit(){
    total = total - this->suma;
    this->suma = -1;
}
int Venit::getID(){
    return this->id;
}
double Venit::getSuma(){
    return this->suma;
}
double Venit::getTotal(){
    return total;
}
Produs& Venit::getProdus(){
    return this->produs_cumparat;
}
void Venit::setSuma(double x){
    total = total - this->suma + x;
    this->suma = x;
}
Venit& Venit::operator=(const Venit& v){
    if(this != &v){
        this->suma = v.suma;
        total = total + v.suma; //aceasta adunare se va anula cu scaderea din destructor
    }
}
istream& operator>>(istream& in, Venit& v){
    char s[10];
    while(true){
        cout << "Introduceti suma(numar real): ";
        in.getline(s, 10);
        if(strcmp("", s) == 0){
            cout << '\n';
            continue;
        }
        if(isReal(s))
            break;
    }
    cout << '\n';
    v.suma = atof(s);
    in >> v.produs_cumparat;

    return in;
}
ostream& operator<<(ostream& out, Venit& v){
    out << "ID venit: " << v.id << '\n';
    out << "Suma: " << v.suma << '\n';
    out << "Detalii produs:\n";
    out << v.produs_cumparat << '\n';

    return out;
}
Venit& Venit::operator[](int i){
    if(i < Venit::id_crt)
        return *obiecte.at(i);
    else return *obiecte.at(Venit::id_crt - 1);
}
Venit& Venit::operator++(){
    this->suma = this->suma + 1;
    total++;
    return *this;
}
Venit& Venit::operator++(int dummy){
    this->suma = this->suma + 1;
    total++;
    return *this;
}
Venit& Venit::operator--(){
    this->suma = this->suma - 1;
    total--;
    return *this;
}
Venit& Venit::operator--(int dummy){
    this->suma = this->suma - 1;
    total--;
    return *this;
}
double Venit::operator+(const Venit& v2){
    return this->suma + v2.suma;
}
double Venit::operator*(const Venit& v2){
    return this->suma * v2.suma;
}
Venit::operator double() const{
    return this->suma;
}
bool Venit::operator<(const Venit& v2){
    bool r = (this->suma) < (v2.suma);
    return r;
}
bool Venit::operator==(const Venit& v2){
    bool r = (this->suma) == (v2.suma);
    return r;
}
void Venit::Afiseaza_Venituri(){
    for(int i = 1; i < id_crt; i++)
        if(obiecte.at(i)->suma >= 0){
            cout << *obiecte.at(i);
        }
}
class Cost{
private:
    double suma = -1;
    Produs& produs_vandut;

    const int id;
    static int id_crt;
    static double total;
    static vector<Cost*> obiecte;

public:
    Cost(Produs& p);
    Cost(double suma, Produs& c);
    Cost(const Cost& c);
    ~Cost();
    int getID();
    double getSuma();
    Produs& getProdus();
    void setSuma(double x);
    Cost& operator=(const Cost& c);
    friend istream& operator>>(istream& in, Cost& c);
    friend ostream& operator<<(ostream& out, Cost& c);
    Cost& operator[](int i);
    Cost& operator++();
    Cost& operator++(int dummy);
    Cost& operator--(int dummy);
    Cost& operator--();
    double operator+(const Cost& c2);
    double operator*(const Cost& c2);
    operator double() const;
    bool operator<(const Cost& c2);
    bool operator==(const Cost& c2);

    static double getTotal();
    static void Afiseaza_Costuri();
};

int Cost::id_crt = 0;
double Cost::total = 0;
vector<Cost*> Cost::obiecte;

Cost::Cost(Produs& p):id(id_crt++), produs_vandut(p){
    obiecte.push_back(this);
}
Cost::Cost(double suma, Produs& p):id(id_crt++), produs_vandut(p){
    this->suma = suma;
    total = total + suma;
    obiecte.push_back(this);
}
Cost::Cost(const Cost& c):id(c.id), produs_vandut(c.produs_vandut){
    this->suma = c.suma;
    total = total + c.suma;
    obiecte.push_back(this);
}
Cost::~Cost(){
    total = total - this->suma;
    this->suma = -1;
}
int Cost::getID(){
    return this->id;
}
double Cost::getSuma(){
    return this->suma;
}
double Cost::getTotal(){
    return total;
}
Produs& Cost::getProdus(){
    return this->produs_vandut;
}
void Cost::setSuma(double x){
    total = total - this->suma + x;
    this->suma = x;
}
Cost& Cost::operator=(const Cost& c){
    if(this != &c){
        this->suma = c.suma;
        total = total + c.suma;
    }
}
istream& operator>>(istream& in, Cost& c){
    char s[10];
    while(true){
        cout << "Introduceti suma(numar real): ";
        in.getline(s, 10);
        if(strcmp("", s) == 0){
            cout << '\n';
            continue;
        }
        if(isReal(s))
            break;
    }
    cout << '\n';
    c.suma = atof(s);
    in >> c.produs_vandut;

    return in;
}
ostream& operator<<(ostream& out, Cost& c){
    out << "ID cost: " << c.id << '\n';
    out << "Suma: " << c.suma << '\n';
    out << "Detalii produs:\n";
    out << c.produs_vandut << '\n';

    return out;
}
Cost& Cost::operator[](int i){
    if(i < Cost::id_crt)
        return *obiecte.at(i);
    else return *obiecte.at(Cost::id_crt - 1);
}
Cost& Cost::operator++(){
    this->suma = this->suma + 1;
    total++;
    return *this;
}
Cost& Cost::operator++(int dummy){
    this->suma = this->suma + 1;
    total++;
    return *this;
}
Cost& Cost::operator--(){
    this->suma = this->suma - 1;
    total--;
    return *this;
}
Cost& Cost::operator--(int dummy){
    this->suma = this->suma - 1;
    total--;
    return *this;
}
double Cost::operator+(const Cost& c2){
    return this->suma + c2.suma;
}
double Cost::operator*(const Cost& c2){
    return this->suma * c2.suma;
}
Cost::operator double() const{
    return this->suma;
}
bool Cost::operator<(const Cost& c2){
    bool r = (this->suma) < (c2.suma);
    return r;
}
bool Cost::operator==(const Cost& c2){
    bool r = (this->suma) == (c2.suma);
    return r;
}
void Cost::Afiseaza_Costuri(){
    for(int i = 1; i < id_crt; i++)
        if(obiecte.at(i)->suma >= 0){
            cout << *obiecte.at(i);
        }
}
double operator+(Venit& v, Cost& c){
    return v.getSuma() + c.getSuma();
}
double operator+(Cost& c, Venit& v){
    return v.getSuma() + c.getSuma();
}

class Buget{
private:
    double investitie = 0; //suma investitiei
    char* investitor = NULL; //numele investitorului

    const int id;
    static int id_crt;
    static double capital;
    static vector<Buget*> obiecte;
public:
    Buget();
    Buget(double investitie);
    Buget(double investitie, char* investitor);
    Buget(const Buget& b);
    ~Buget();
    int getID();
    double getInvestitie();
    char* getInvestitor();
    void setInvestitie(double x);
    void setInvestitor(char* nume);
    Buget& operator=(const Buget& b);
    friend istream& operator>>(istream& in, Buget& b);
    friend ostream& operator<<(ostream& out, Buget& b);
    Buget& operator[](int i);
    Buget& operator++();
    Buget& operator++(int dummy);
    Buget& operator--(int dummy);
    Buget& operator--();
    double operator+(const Buget& b2);
    double operator*(const Buget& b2);
    operator double() const;
    bool operator<(const Buget& b2);
    bool operator==(const Buget& b2);


    static double getCapital();
    static void setCapital(double x);
    static double getProfit();
    static void Raport();
    static void Afiseaza_Investitii();
};

int Buget::id_crt = 0;
double Buget::capital = 1000;
vector<Buget*> Buget::obiecte;

Buget::Buget():id(id_crt++){
    obiecte.push_back(this);
}
Buget::Buget(double investitie):id(id_crt++){
    this->investitie = investitie;
    capital = capital + investitie;
    obiecte.push_back(this);
}
Buget::Buget(double investitie, char* investitor):id(id_crt++){
    this->investitie = investitie;
    capital = capital + investitie;
    this->investitor = new char[strlen(investitor) + 1];
    strcpy(this->investitor, investitor);
    obiecte.push_back(this);
}
Buget::Buget(const Buget& b):id(b.id){
    this->investitie = b.investitie;
    capital = capital + b.investitie;
    this->investitor = new char[strlen(b.investitor) + 1];
    strcpy(this->investitor, b.investitor);
    obiecte.push_back(this);
}
Buget::~Buget(){
    capital = capital - this->investitie;
    this->investitie = 0;
    if(this->investitor)
        delete[] this->investitor;
}
int Buget::getID(){
    return this->id;
}
double Buget::getInvestitie(){
    return this->investitie;
}
char* Buget::getInvestitor(){
    if(this->investitor)
        return this->investitor;
    else return "Anonim";
}
void Buget::setInvestitie(double x){
    capital = capital - this->investitie + x;
    this->investitie = x;
}
void Buget::setInvestitor(char* nume){
    if(this->investitor)
        delete[] this->investitor;
    this->investitor = new char[strlen(nume) + 1];
    strcpy(this->investitor, nume);
}
void Buget::setCapital(double x){
    capital = x;
}
Buget& Buget::operator=(const Buget& b){
    if(this != &b){
        this->investitie = b.investitie;
        if(this->investitor)
            delete[] this->investitor;
        this->investitor = new char[strlen(b.investitor) + 1];
        strcpy(this->investitor, b.investitor);
    }
    return *this;
}
istream& operator>>(istream& in, Buget& b){
    char s[10], n[101];
    while(true){
        cout << "Introduceti valoarea investitiei(numar real): ";
        in.getline(s, 10);
        if(strcmp("", s) == 0){
            cout << '\n';
            continue;
        }
        if(isReal(s))
            break;
    }
    b.investitie = atof(s);
    strcpy(n, "");
    while(strcmp("", n) == 0){
        cout << "Introduceti numele investitorului: ";
        in.getline(n, 101);
    }
    cout << '\n';
    if(b.investitor)
        delete[] b.investitor;
    b.investitor = new char(strlen(n) + 1);
    strcpy(b.investitor, n);

    return in;
}
ostream& operator<<(ostream& out, Buget& b){
    out << "ID investitie: " << b.id << '\n';
    out << "Valoarea investita: " << b.investitie << '\n';
    out << "Numele investitorului: " << b.getInvestitor() << '\n';
}
Buget& Buget::operator[](int i){
    if(i < Buget::id_crt)
        return *obiecte.at(i);
    else return *obiecte.at(Buget::id_crt - 1);
}
Buget& Buget::operator++(){
    this->investitie = this->investitie + 1;
    capital++;
    return *this;
}
Buget& Buget::operator++(int dummy){
    this->investitie = this->investitie + 1;
    capital++;
    return *this;
}
Buget& Buget::operator--(){
    this->investitie = this->investitie - 1;
    capital--;
    return *this;
}
Buget& Buget::operator--(int dummy){
    this->investitie = this->investitie - 1;
    capital--;
    return *this;
}
double Buget::operator+(const Buget& b2){
    return this->investitie + b2.investitie;
}
double Buget::operator*(const Buget& b2){
    return this->investitie * b2.investitie;
}
Buget::operator double() const{
    return this->investitie;
}
bool Buget::operator<(const Buget& b2){
    bool r = (this->investitie) < (b2.investitie);
    return r;
}
bool Buget::operator==(const Buget& b2){
    bool r = (this->investitie) == (b2.investitie);
    return r;
}
double Buget::getCapital(){
    return capital;
}
double Buget::getProfit(){
    return Venit::getTotal() - Cost::getTotal();
}
void Buget::Raport(){
    cout << "Venituri:\n\n";
    Venit::Afiseaza_Venituri();
    cout << "Cheltuieli:\n\n";
    Cost::Afiseaza_Costuri();
}
void Buget::Afiseaza_Investitii(){
    for(int i = 1; i < id_crt; i++)
        if(obiecte.at(i)->investitie >= 0){
            cout << *obiecte.at(i) << '\n';
        }
}
int main()
{
    Produs manager_produse;
    Venit manager_venituri(manager_produse[0]);
    Cost manager_costuri(manager_produse[0]);
    Buget manager_buget;

    vector<Produs> p; //creez un vector pentru fiecare clasa
    vector<Buget> b; //in acest fel ma asigur ca obiectele nu vor fi distruse pana la finalul programului
    vector<Venit> v;
    vector<Cost> c;
    vector<int> x;

    Produs p1("Ceai verde", "Stimuleaza activitatea cerebrala", 10.0, 12.0, 20);
    p.push_back(p1);
    Produs p2("Ceai negru", "Beneficii maxime la nivel de metabolism", 5.0, 6.0, 40);
    p.push_back(p2);

    while(true){
        char s[11];
        while(true){
            cout << "Capital: " << manager_buget.getCapital() << '\n';
            cout << "Introduceti litera corespunzatoare actiunii dorite:\n";
            cout << "I: pentru a introduce date in sistem\n";
            cout << "P: pentru a gestiona produsele\n";
            cout << "F: pentru departamentul financiar\n";
            cout << "E: pentru a incheia sesiunea\n";
            cin.getline(s, 11);  cout << '\n';
            if(s[0] == 'I' || s[0] == 'i' || s[0] == 'P' || s[0] == 'p' ||
               s[0] == 'F' || s[0] == 'f' || s[0] == 'E' || s[0] == 'e')
                    break;
        }
        if(s[0] == 'I' || s[0] == 'i'){
            char s[101];
            while(true){
                cout << "I: pentru a introduce o investitie\n";
                cout << "A: pentru a introduce o achizitie\n";
                cout << "V: pentru a introduce o vanzare\n";
                cout << "B: pentru a merge inapoi la meniul principal\n";
                cin.getline(s, 101); cout << '\n';
                if(s[0] == 'I' || s[0] == 'i'){
                    Buget b_temp;
                    cin >> b_temp;
                    b.push_back(b_temp);
                    manager_buget.setCapital(manager_buget.getCapital() + b_temp.getInvestitie());
                }
                else if(s[0] == 'A' || s[0] == 'a'){
                    vector<Produs>::iterator i;
                    for(i = p.begin(); i != p.end(); i++)
                        if(i->getCantitate() >= 0)
                            cout << *i << '\n';
                    char s_id[10], s_cantitate[10];
                    int id;
                    while(true){
                        cout << "Introduceti ID produs: ";
                        cin.getline(s_id, 10);
                        if(!isInteger(s_id))
                            continue;
                        id = atoi(s_id);
                        if(id >= manager_produse.getIDCurent() || id == 0) //daca nu este un camp valid, ii cer utilizatorului sa introduca
                            cout << "Eroare, id incorect\n";               //din nou o valoare
                        else break;
                    }
                    int cantitate;
                    while(true){
                        cout << "Introduceti cantitatea(numar intreg): ";
                        cin.getline(s_cantitate, 10);
                        if(!isInteger(s_cantitate))
                            continue;
                        cantitate = atoi(s_cantitate);
                        if((manager_buget.getCapital() - cantitate * manager_produse[id].getPretCumparare()) < 0){
                            cout << "Eroare, fonduri insuficiente\n";
                        }
                        else break;
                    }
                    cout << '\n';
                    manager_produse[id].setCantitate(manager_produse[id].getCantitate() + cantitate);
                    p[id - 1].setCantitate(p[id - 1].getCantitate() + cantitate);
                    manager_buget.setCapital(manager_buget.getCapital() - cantitate * manager_produse[id].getPretCumparare());
                    Cost c_temp((double)cantitate * manager_produse[id].getPretCumparare(), p[id - 1]); // creez un obiect de tip cost
                    c.push_back(c_temp); //memorez acest obiect creand un altul prin constructorul de copiere

                }
                else if(s[0] == 'V' || s[0] == 'v'){
                    vector<Produs>::iterator i;
                    for(i = p.begin(); i != p.end(); i++)
                        if(i->getCantitate() >= 0)
                            cout << *i << '\n';
                    char s_id[10], s_cantitate[10];
                    int id;
                    while(true){
                        cout << "Introduceti ID produs: ";
                        cin.getline(s_id, 10);
                        if(!isInteger(s_id))
                            continue;
                        id = atoi(s_id);
                        if(id >= manager_produse.getIDCurent() || id == 0)
                            cout << "Eroare, id incorect\n";
                        else break;
                    }
                    int cantitate;
                    while(true){
                        cout << "Introduceti cantitatea(numar intreg): ";
                        cin.getline(s_cantitate, 10);
                        if(!isInteger(s_cantitate))
                            continue;
                        cantitate = atoi(s_cantitate);
                        if(manager_produse[id].getCantitate() < cantitate){
                            cout << "Eroare, cantitate indisponibila\n";
                        }
                        else break;
                    }
                     cout << '\n';
                    manager_produse[id].setCantitate(manager_produse[id].getCantitate() - cantitate);
                    p[id - 1].setCantitate(p[id - 1].getCantitate() - cantitate);
                    manager_buget.setCapital(manager_buget.getCapital() + cantitate * manager_produse[id].getPretVanzare());
                    Venit v_temp((double)cantitate * manager_produse[id].getPretVanzare(), p[id - 1]);
                    v.push_back(v_temp);
                }
                else if(s[0] == 'B' || s[0] == 'b'){
                    break;
                }
            }
        }
        else if(s[0] == 'P' || s[0] == 'p'){
            char s[101];
            while(true){
                vector<Produs>::iterator i;
                for(i = p.begin(); i != p.end(); i++)
                    if(i->getCantitate() >= 0)
                        cout << *i << '\n';
                cout << "C: pentru a crea un nou produs\n";
                cout << "U: pentru a modifica detaliile unui produs\n";
                cout << "S: pentru a sterge un produs\n";
                cout << "B: pentru a merge inapoi la meniul principal\n";
                cin.getline(s, 101); cout << '\n';
                if(s[0] == 'C' || s[0] == 'c'){
                    Produs p_temp;
                    cin >> p_temp;
                    p.push_back(p_temp);
                }
                else if(s[0] == 'U' || s[0] == 'u'){
                    char s_id[10];
                    int id;
                    while(true){
                        cout << "Introduceti ID produs: ";
                        cin.getline(s_id, 10);
                        if(!isInteger(s_id))
                            continue;
                        id = atoi(s_id);
                        if(id >= manager_produse.getIDCurent() || id == 0)
                            cout << "Eroare, id incorect\n";
                        else break;
                    }
                    cin >> p[id - 1];
                }
                else if(s[0] == 'S' || s[0] == 's'){
                    char s_id[10];
                    int id;
                    while(true){
                        cout << "Introduceti ID produs: ";
                        cin.getline(s_id, 10);
                        if(!isInteger(s_id))
                            continue;
                        id = atoi(s_id);
                        if(id >= manager_produse.getIDCurent() || id == 0)
                            cout << "Eroare, id incorect\n";
                        else break;
                    }
                    cout << '\n';
                    p[id - 1].setCantitate(-1); //pare destul de superficial, dar daca incercam sa elimin elementul din vector
                }                               //aparea problema ca operatorul = apelat de vector.erase nu putea sa modifice const int id
                else if(s[0] == 'B' || s[0] == 'b'){
                    break;
                }
            }
        }
        else if(s[0] == 'F' || s[0] == 'f'){
            char s[101];
            while(true){
                cout << "V: pentru a afisa toate veniturile\n";
                cout << "C: pentru a afisa toate cheltuielile\n";
                cout << "I: pentru a afisa toate investiile\n";
                cout << "P: pentru a calcula profitul\n";
                cout << "B: pentru a merge inapoi la meniul principal\n";
                cin.getline(s, 101); cout << '\n';
                if(s[0] == 'V' || s[0] == 'v'){
                    vector<Venit>::iterator i; //afisez lista cu veniturile generate de utilizator prin introducerea unor vanzari
                    for(i = v.begin(); i != v.end(); i++)
                        cout << *i << '\n';
                }
                else if(s[0] == 'C' || s[0] == 'c'){
                    vector<Cost>::iterator i;
                    for(i = c.begin(); i != c.end(); i++)
                        cout << *i << '\n';
                }
                else if(s[0] == 'I' || s[0] == 'i'){
                    vector<Buget>::iterator i;
                    for(i = b.begin(); i != b.end(); i++)
                        cout << *i << '\n';
                }
                else if(s[0] == 'P' || s[0] == 'p'){
                    cout << manager_buget.getProfit() << '\n' << '\n';
                }
                else if(s[0] == 'B' || s[0] == 'b'){
                    cout << '\n';
                    break;
                }
            }
        }
        else if(s[0] == 'E' || s[0] == 'e'){
            break; //daca utilizatorul introduce litera e in meniul pricipal, programul se incheie
        }
    }
    return 0;
}
