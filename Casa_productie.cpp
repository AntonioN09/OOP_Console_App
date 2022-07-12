#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Interfata_IO{
public:
	virtual istream& citire(istream& in) = 0;
	virtual ostream& afisare(ostream& out)  = 0;
};


class Persoana: public Interfata_IO{
protected:
    string nume;
    double pret; //suma ceruta de fiecare persoana pentru a participa la producerea filmului(la producator ma refer si la alte costuri de productie: echipament etc.)
    int nr_filme;
    string* filme; //o lista cu filmele in care a mai jucat actorul anterior

public:
    Persoana(){
        this->nume = "anonim";
        this->pret = 0;
        this->nr_filme = 0;
        this->filme = new string[5];
    }

    Persoana(string nume, double pret, int nr_filme, string* filme){
        this->nume = nume;
        this->pret = pret;
        this->nr_filme = nr_filme;
        this->filme = new string[nr_filme];
        for(int i = 0; i < nr_filme; i++)
            this->filme[i] = filme[i];
    }

    Persoana(const Persoana& p){
        this->nume = p.nume;
        this->pret = p.pret;
        this->nr_filme = p.nr_filme;
        this->filme = new string[p.nr_filme];
        for(int i = 0; i < p.nr_filme; i++){
            this->filme[i] = p.filme[i];
        }
    }

    virtual ~Persoana(){
        if(this->filme != NULL){
            delete[] this->filme;
        }
    }

    string getNume() const{
        return this->nume;
    }

    double getPret() const{
        return this->pret;
    }

    int getNrFilme() const{
        return this->nr_filme;
    }

    string* getFilme() const{
        return this->filme;
    }

    void setNume(string nume){
        this->nume = nume;
    }

    void setPret(double pret){
        this->pret = pret;
    }

    void setNrFilme(int nr){
        this->nr_filme = nr;
    }

    void setFilme(string* filme, int nr){
        this->nr_filme = nr;
        if(this->filme){
            delete[] this->filme;
        }
        this->filme = new string[nr];
        for(int i = 0; i < nr; i++){
            this->filme[i] = filme[i];
        }
    }

    virtual Persoana& operator=(const Persoana& p){
        if(this != &p){
            this->nume = p.nume;
            this->pret = p.pret;
            this->nr_filme = p.nr_filme;
            this->filme = new string[p.nr_filme];
            for(int i = 0; i < p.nr_filme; i++){
                this->filme[i] = p.filme[i];
            }
        }

        return *this;
    }

    virtual istream& citire(istream& in){
        cout << "Introduceti numele: ";
        in >> this->nume;
        cout << "Introduceti pretul: ";
        in >> this->pret;
        cout << "Introduceti numarul de filme: ";
        in >> this->nr_filme;
        if(this->filme){
            delete[] this->filme;
        }
        this->filme = new string[this->nr_filme];
        cout << "Introduceti denumirea filmelor:\n";
        for(int i = 0; i < this->nr_filme; i++){
            in >> this->filme[i];
        }

        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        out << "Numele: " << this->nume << '\n';
        out << "Pretul: " << this->pret << '\n';
        out << "Numarul de filme: " << this->nr_filme << '\n';
        out << "Denumirea filmelor:" << '\n';
        for(int i = 0; i < this->nr_filme; i++)
            out << "\t-> " << this->filme[i] << '\n';

        return out;
    }

    friend istream& operator>>(istream& in, Persoana& p){
        return p.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Persoana& p){
        return p.afisare(out);
    }
};


class Actor: virtual public Persoana{
protected:
    int rating_actor; //de la 1 la 10(maxim)
    string motto;

public:
    Actor(): Persoana(){
        this->rating_actor = 0;
        this->motto = "Top";
    }

    Actor(string nume, double pret, int nr_filme, string* filme, int rating, string motto):Persoana(nume, pret, nr_filme, filme){
        this->rating_actor = rating;
        this->motto = motto;
    }

    Actor(const Actor& a):Persoana(a){
        this->rating_actor = a.rating_actor;
        this->motto = a.motto;
    }

    virtual ~Actor(){}

    int getRatingActor() const{
        return this->rating_actor;
    }

    string getMotto() const{
        return this->motto;
    }

    void setRatingActor(int rating){
        this->rating_actor = rating;
    }

    void setMotto(string s){
        this->motto = s;
    }

    virtual Actor& operator=(const Actor& a){
        if(this != &a){
            Persoana::operator=(a);
            this->rating_actor = a.rating_actor;
            this->motto = a.motto;
        }

        return *this;
    }

    virtual istream& citire(istream& in){
        Persoana::citire(in);
        cout << "Introduceti rating actor: ";
        in >> this->rating_actor;
        cout << "Introduceti motto: ";
        in >> this->motto;

        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        Persoana::afisare(out);
        cout << "Rating actor: " << this->rating_actor << '\n';
        cout << "Motto: " << this->motto << '\n';

        return out;
    }

    friend istream& operator>>(istream& in, Actor& a){
        return a.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Actor& a){
        return a.afisare(out);
    }
};


class Regizor: virtual public Persoana{
protected:
    int rating_regizor;
    string stil; //maniera de a regiza - libera, riguroasa, perfecta, etc

public:
    Regizor(): Persoana(){
        this->rating_regizor = 0;
        this->stil = "Top";
    }

    Regizor(string nume, double pret, int nr_filme, string* filme, int rating, string stil):Persoana(nume, pret, nr_filme, filme){
        this->rating_regizor = rating;
        this->stil = stil;
    }

    Regizor(const Regizor& r):Persoana(r){
        this->rating_regizor = r.rating_regizor;
        this->stil = r.stil;
    }

    virtual ~Regizor(){}

    int getRatingRegizor() const{
        return this->rating_regizor;
    }

    string getStil() const{
        return this->stil;
    }

    void setRatingRegizor(int rating){
        this->rating_regizor = rating;
    }

    void setStil(string s){
        this->stil = s;
    }

    virtual Regizor& operator=(const Regizor& r){
        if(this != &r){
            Persoana::operator=(r);
            this->rating_regizor = r.rating_regizor;
            this->stil = r.stil;
        }

        return *this;
    }

    virtual istream& citire(istream& in){
        Persoana::citire(in);
        cout << "Introduceti rating regizor: ";
        in >> this->rating_regizor;
        cout << "Introduceti stil: ";
        in >> this->stil;

        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        Persoana::afisare(out);
        cout << "Rating regizor: " << this->rating_regizor << '\n';
        cout << "Stil: " << this->stil << '\n';

        return out;
    }

    friend istream& operator>>(istream& in, Regizor& r){
        return r.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Regizor& r){
        return r.afisare(out);
    }
};


class Producator: public Actor, public Regizor{
private:
    int rating_producator;
    double profit; //procentul de profit al fiecarui producator

public:
    Producator(): Persoana(), Actor(), Regizor(){
        this->rating_producator = 0;
        this->profit = 1;
    }

    Producator(string nume, double pret, int nr_filme, string* filme, int rating_actor,
               string motto, int rating_regizor, string stil, int rating_producator, double profit):
               Persoana(nume, pret, nr_filme, filme),
               Actor(nume, pret, nr_filme, filme, rating_actor, motto),
               Regizor(nume, pret, nr_filme, filme, rating_regizor, stil){
        this->rating_producator = rating_producator;
        this->profit = profit;
    }

    Producator(const Producator& pro): Persoana(pro), Actor(pro), Regizor(pro){
        this->rating_producator = pro.rating_producator;
        this->profit = pro.profit;
    }

    ~Producator(){}

    int getRatingProducator(){
        return this->rating_producator;
    }

    int getProfit(){
        return this->profit;
    }

    void setRatingProducator(int rating){
        this->rating_producator = rating;
    }

    void setProfit(int p){
        this->profit = profit;
    }

    Producator& operator=(const Producator& pro){
        if(this != &pro){
            Actor::operator=(pro);
            this->rating_regizor = pro.rating_regizor;
            this->stil = pro.stil;
            this->rating_producator = pro.rating_producator;
            this->profit = pro.profit;
        }

        return *this;
    }

    istream& citire(istream& in){
        Actor::citire(in);
        cout << "Introduceti rating regizor: ";
        in >> this->rating_regizor;
        cout << "Introduceti Stil: ";
        in >> this->stil;
        cout << "Introduceti rating producator: ";
        in >> this->rating_producator;
        cout << "Introduceti procentajul de profit: ";
        in >> this->profit;

        return in;
    }

    ostream& afisare(ostream& out) const{
        Actor::afisare(out);
        cout << "Rating regizor: " << this->rating_regizor << '\n';
        cout << "Stil: " << this->stil << '\n';
        cout << "Rating producator: " << this->rating_producator << '\n';
        cout << "Procentaj profit: " << this->profit  << '\n';
        return out;
    }

    friend istream& operator>>(istream& in, Producator& pro){
        return pro.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Producator& pro){
        return pro.afisare(out);
    }
};



class Film: public Interfata_IO{
    double cost; //costul de productie determinat de pretul solicitat de fiecare persoana
    double venit; //venitul determinat in functie de cost si de procentul de profit al producatorului (nu tocmai realist, dar ma refer la un venit potential)
    int nr_actori; //ajuta cand creez un film, deoarece interoghez inainte cati actori vor urma sa fie introdusi
    vector<Actor*> actori; //pointeri catre actorii din vectorul din main
    Regizor* regizor; //pointer catre regizorul ales de utilizator din vectorul din main
    Producator* producator;

public:
    Film(){
        cost = 0;
        venit = 0;
        nr_actori = -1;
    }

    Film(int nr_actori, vector<Actor*> actori, Regizor* regizor, Producator* producator){
        this->nr_actori = nr_actori;
        this->actori = actori;
        this->regizor = regizor;
        this->producator = producator;
        double cost = 0;
        for(int i = 0; i < nr_actori; i++){
            cost += actori[i]->getPret();
        }
        cost += regizor->getPret();
        cost += producator->getPret();
        this->cost = cost;
        this->venit = cost * producator->getProfit();
    }

    Film(const Film& f){
        this->nr_actori = f.nr_actori;
        this->actori = f.actori;
        this->regizor = f.regizor;
        this->producator = f.producator;
        this->cost = f.cost;
        this->venit = f.venit;
    }

    ~Film(){
        this->nr_actori = -1;
        this->actori.clear();
        this->regizor = NULL;
        this->producator = NULL;
    }

    double getCost(){
        return this->cost;
    }

    double getVenit(){
        return this->venit;
    }

    int getNrActori(){
        return this->nr_actori;
    }

    vector<Actor*>& getActori(){ //util pentru a adauga si sterge actorii dintr-un film
        return this->actori;
    }

    Regizor* getRegizor(){
        return this->regizor;
    }

    Producator* getProducator(){
        return this->producator;
    }

    void setNrActori(int nr){
        this->nr_actori = nr;
    }

    void setActori(vector<Actor*> actori){
        this->actori = actori;
    }

    void setRegizor(Regizor* r){
        this->regizor = r;
    }

    void setProducator(Producator* p){
        this->producator = p;
        this->venit = this->cost * p->getProfit();
    }

    Film& operator=(const Film& f){
        if(this != &f){
            this->nr_actori = f.nr_actori;
            this->actori = f.actori;
            this->regizor = f.regizor;
            this->producator = f.producator;
            this->cost = f.cost;
            this->venit = f.venit;
        }

        return *this;
    }

    istream& citire(istream& in){
        cout << "Introduceti numarul de actori: ";
        in >> this->nr_actori;
        cout << "Introduceti actorii:\n";
        for(int i = 0; i < this->nr_actori; i++){
            cout << "\nIntroduceti urmatorul actor:\n";
            Actor *a = new Actor;
            in >> *a;
            this->actori.push_back(a);
        }
        cout << "\nIntroduceti regizorul:\n";
        this->regizor = new Regizor;
        in >> *this->regizor;
        cout << "\nIntroduceti producatorul:\n";
        this->producator = new Producator;
        in >> *this->producator;
        double cost = 0;
        for(int i = 0; i < nr_actori; i++){
            cost += actori[i]->getPret();
        }
        cost += regizor->getPret();
        cost += producator->getPret();

        this->cost = cost;
        this->venit = cost * producator->getProfit();

        return in;
    }
    ostream& afisare(ostream& out) const{
        out << "Venit potential: " << this->venit << '\n';
        out << "Costuri productie: " << this->cost << '\n';
        out << "Numar actori: " << this->nr_actori << '\n';
        out << "\nDistributia:\n";
        for(int i = 0; i < this->nr_actori; i++){
            out << *this->actori[i] << '\n';
        }
        out << "Regizor\n";
        out << *this->regizor;
        out << "\nProducator\n";
        out << *this->producator;

        return out;
    }

    friend istream& operator>>(istream& in, Film& f){
        return f.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Film& f){
        return f.afisare(out);
    }
};


class Buget: Interfata_IO{
private:
    double investitie; //suma investitiei
    char* investitor; //numele investitorului
    static double capital;

public:
    Buget(){
        investitie = 0;
        investitor = (char*)"Anonim";
    }

    Buget(double investitie){
        this->investitie = investitie;
        capital = capital + investitie;
    }

    Buget(double investitie, char* investitor){
        this->investitie = investitie;
        capital = capital + investitie;
        this->investitor = new char[strlen(investitor) + 1];
        strcpy(this->investitor, investitor);
    }

    Buget(const Buget& b){
        this->investitie = b.investitie;
        capital = capital + b.investitie;
        this->investitor = new char[strlen(b.investitor) + 1];
        strcpy(this->investitor, b.investitor);
    }

    ~Buget(){
        capital = capital - this->investitie; //actualizez capitalul automat, cand sterg o investitie din vector
        this->investitie = 0;
        if(this->investitor){
            delete[] this->investitor;
        }
    }

    double getInvestitie() const{
        return this->investitie;
    }

    char* getInvestitor() const{
        return this->investitor;
    }

    void setInvestitie(double x){
        capital = capital - this->investitie + x;
        this->investitie = x;
    }

    void setInvestitor(char* nume){
        if(this->investitor){
            delete[] this->investitor;
        }
        this->investitor = new char[strlen(nume) + 1];
        strcpy(this->investitor, nume);
    }

    Buget& operator=(const Buget& b){
        if(this != &b){
            this->investitie = b.investitie;
            if(this->investitor)
                delete[] this->investitor;
            this->investitor = new char[strlen(b.investitor) + 1];
            strcpy(this->investitor, b.investitor);
        }

        return *this;
    }

    istream& citire(istream& in){
        cout << "Introduceti valoarea investita: ";
        in >> this->investitie;
        this->capital += this->investitie;
        char s[20];
        cout << "Introduceti numele investitorului: ";
        in >> s;
        if(this->investitor){
            delete[] this->investitor;
        }
        this->investitor = new char(strlen(s) + 1);
        strcpy(this->investitor, s);

        return in;
    }

    ostream& afisare(ostream& out) const{
        out << "Valoarea investita: " << this->investitie << '\n';
        out << "Numele investitorului: " << this->getInvestitor() << '\n';

        return out;
    }

    friend istream& operator>>(istream& in, Buget& b){
        return b.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Buget& b){
        return b.afisare(out);
    }

    /*

    Buget& operator++(int dummy){
        this->investitie = this->investitie + 1;
        capital++;
        return *this;
    }
    Buget& operator--(int dummy){
        this->investitie = this->investitie - 1;
        capital--;
        return *this;
    }

    double operator+(const Buget& b2) const{
        return this->investitie + b2.investitie;
    }

    operator double() const{
        return this->investitie;
    }

    bool operator<(const Buget& b2){
        bool r = (this->investitie) < (b2.investitie);
        return r;
    }

    bool operator==(const Buget& b2){
        bool r = (this->investitie) == (b2.investitie);
        return r;
    }

    */

    static double getCapital(){
        return capital;
    }

    static void setCapital(double x){
        capital = x;
    }
};

double Buget::capital = 20000;

int main()
{
    vector<Actor> a;
    vector<Regizor> r;
    vector<Producator> p;
    vector<Film> f;
    vector<Buget> b;

    string nume_filme1[] = {"Viteza", "Lacul"};
    Actor *a1 = new Actor("John", 2000, 2, nume_filme1, 8, "Go");

    string nume_filme2[] = {"Arca"};
    Actor *a2 = new Actor("Giovanni", 5000, 1, nume_filme2, 9, "Neincetat");

    string nume_filme3[] = {"Arca", "Lorena", "Abis"};
    Regizor *r1 = new Regizor("Lena", 8000, 3, nume_filme3, 10, "Perfect");

    string nume_filme4[] = {"Abis"};
    Producator *p1 = new Producator("Artois", 9000, 1, nume_filme4, 10, "Comeback", 10, "Perfect", 10, 2);

    vector<Actor*> a_ref;
    a_ref.push_back(a1);
    a_ref.push_back(a2);
    Film *f1 = new Film(2, a_ref, r1, p1);

    a.push_back(*a1);
    a.push_back(*a2);
    r.push_back(*r1);
    p.push_back(*p1);
    f.push_back(*f1);

    while(true){
        cout << "\nCapital: " << Buget::getCapital() << '\n';
        cout << "Introduceti 1 pentru resurse umane\n";
        cout << "Introduceti 2 pentru gestiunea filmelor\n";
        cout << "Introduceti 3 pentru departamentul financiar\n";
        cout << "Introduceti 4 pentru incheierea sesiunii\n";

        int alegere;
        cin >> alegere;
        while(alegere > 4){
            cin >> alegere;
        }

        if(alegere == 1){ //resurse umane
            while(true){
                cout << "\nIntroduceti 1 pentru gestiunea actorilor\n";
                cout << "Introduceti 2 pentru gestiunea regizorilor\n";
                cout << "Introduceti 3 pentru gestiunea producatorilor\n";
                cout << "Introduceti 4 pentru intoarcerea la meniul principal\n";

                int alegere;
                cin >> alegere;
                while(alegere > 4){
                    cin >> alegere;
                }

                if(alegere == 1){ //actor
                    while(true){
                        cout << '\n';
                        for(unsigned i = 0; i < a.size(); i++){
                            cout << "ID: " << i << '\n'; //prefer sa generez id-ul aici si nu in clasa, deoarece este mai usor de eliminat elementul din vector
                            cout << a[i] << '\n';
                        }

                        cout << "Introduceti 1 pentru introducerea in sistem a unui actor\n";
                        cout << "Introduceti 2 pentru modificarea profilului unui actor\n";
                        cout << "Introduceti 3 pentru eliminarea unui actor din sistem\n";
                        cout << "Introduceti 4 pentru intoarcerea la resurse umane\n";

                        int alegere;
                        cin >> alegere;
                        while(alegere > 4){
                            cin >> alegere;
                        }

                        if(alegere == 1){ //creare actor
                            cout << '\n';
                            Actor a1;
                            cin >> a1;
                            a.push_back(a1);
                        }
                        else if(alegere == 2){ //modificare actor
                            cout << "\nIntroduceti ID: ";
                            unsigned id;
                            cin >> id;
                            while(id >= a.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }
                            cout << '\n';
                            cin >> a[id];
                        }
                        else if(alegere == 3){ //stergere actor
                            cout << "\nIntroduceti ID: ";

                            unsigned id;
                            cin >> id;
                            while(id >= a.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }

                            a.erase(a.begin() + id);
                        }
                        else if(alegere == 4){ //catre resurse umane
                            break;
                        }
                    }
                }
                else if(alegere == 2){ //regizor
                    while(true){
                        cout << '\n';
                        for(unsigned i = 0; i < r.size(); i++){
                            cout << "ID: " << i << '\n';
                            cout << r[i] << '\n';
                        }

                        cout << "Introduceti 1 pentru introducerea in sistem a unui regizor\n";
                        cout << "Introduceti 2 pentru modificarea profilului unui regizor\n";
                        cout << "Introduceti 3 pentru eliminarea unui regizor din sistem\n";
                        cout << "Introduceti 4 pentru intoarcerea la resurse umane\n";

                        int alegere;
                        cin >> alegere;
                        while(alegere > 4){
                            cin >> alegere;
                        }

                        if(alegere == 1){ //creare regizor
                            cout << '\n';
                            Regizor r1;
                            cin >> r1;
                            r.push_back(r1);
                        }
                        else if(alegere == 2){ //modificare regizor
                            cout << "\nIntroduceti ID: ";

                            unsigned id;
                            cin >> id;
                            while(id >= r.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }

                            cout << '\n';
                            cin >> r[id];
                        }
                        else if(alegere == 3){ //stergere regizor
                            cout << "\nIntroduceti ID: ";

                            unsigned id;
                            cin >> id;
                            while(id >= r.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }

                            r.erase(r.begin() + id);
                        }
                        else if(alegere == 4){ //catre resurse umane
                            break;
                        }
                    }
                }
                else if(alegere == 3){ //producator
                    while(true){
                        cout << '\n';
                        for(unsigned i = 0; i < p.size(); i++){
                            cout << "ID: " << i << '\n';
                            cout << p[i] << '\n';
                        }

                        cout << "Introduceti 1 pentru introducerea in sistem a unui producator\n";
                        cout << "Introduceti 2 pentru modificarea profilului unui producator\n";
                        cout << "Introduceti 3 pentru eliminarea unui producator din sistem\n";
                        cout << "Introduceti 4 pentru intoarcerea la resurse umane\n";

                        int alegere;
                        cin >> alegere;
                        while(alegere > 4){
                            cin >> alegere;
                        }

                        if(alegere == 1){ //creare producator
                            cout << '\n';
                            Producator p1;
                            cin >> p1;
                            p.push_back(p1);
                        }
                        else if(alegere == 2){ //modificare producator
                            cout << "\nIntroduceti ID: ";

                            unsigned id;
                            cin >> id;
                            while(id >= p.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }

                            cout << '\n';
                            cin >> p[id];
                        }
                        else if(alegere == 3){ //stergere producator
                            cout << "\nIntroduceti ID: ";

                            unsigned id;
                            cin >> id;
                            while(id >= p.size()){
                                cout << "\nIntroduceti ID: ";
                                cin >> id;
                            }

                            p.erase(p.begin() + id);
                        }
                        else if(alegere == 4){ //catre resurse umane
                            break;
                        }
                    }
                }
                else if(alegere == 4){ //catre meniul principal
                    break;
                }
            }
        }
        else if(alegere == 2){ //gestiune filme
            while(true){
                cout << '\n';
                for(unsigned i = 0; i < f.size(); i++){
                    cout << "ID: " << i << '\n';
                    cout << f[i] << '\n';
                }

                cout << "Introduceti 1 pentru producerea unui film\n";
                cout << "Introduceti 2 pentru modificarea unui film\n";
                cout << "Introduceti 3 pentru vanzarea unui film\n";
                cout << "Introduceti 4 pentru intoarcerea la meniul principal\n";

                int alegere;
                cin >> alegere;
                while(alegere > 4){
                    cin >> alegere;
                }

                if(alegere == 1){ //creare film
                    cout << '\n';
                    cout << "Introduceti numarul de actori\n";

                    vector<Actor*> a_ref;

                    unsigned nr_actori;
                    cin >> nr_actori;
                    while(nr_actori > a.size()){
                        cout << "Introduceti numarul de actori\n";
                        cin >> nr_actori;
                    }

                    for(unsigned i = 0; i < nr_actori; i++){
                        cout << "\nIntroduceti ID pentru actor " << i + 1 << ": ";

                        unsigned id;
                        cin >> id;
                        while(id >= a.size()){
                            cout << "\nIntroduceti ID pentru actor " << i + 1 << ": ";
                            cin >> id;
                        }

                        a_ref.push_back(&a[id]);
                    }
                    cout << "Introduceti ID pentru regizor:\n";

                    unsigned id_r;
                    cin >> id_r;
                    while(id_r >= r.size()){
                        cout << "Introduceti ID pentru regizor:\n";
                        cin >> id_r;
                    }

                    cout << "Introduceti ID pentru producator:\n";

                    unsigned id_p;
                    cin >> id_p;
                    while(id_p >= p.size()){
                        cout << "Introduceti ID pentru producator:\n";
                        cin >> id_p;
                    }

                    Film f1(nr_actori, a_ref, &r[id_r], &p[id_p]);
                    f.push_back(f1);


                }
                else if(alegere == 2){ //modificare film
                    cout << "\nIntroduceti ID film: ";

                    unsigned id;
                    cin >> id;
                    while(id >= f.size()){
                        cout << "\nIntroduceti ID: ";
                        cin >> id;
                    }

                    cout << "\nIntroduceti 1 pentru adaugarea unui actor\n";
                    cout << "Introduceti 2 pentru excluderea unui actor\n";
                    cout << "Introduceti 3 pentru modificarea regizorului\n";
                    cout << "Introduceti 4 pentru modificarea producatorului\n";

                    int alegere;
                    cin >> alegere;
                    while(alegere > 4){
                        cin >> alegere;
                    }

                    if(alegere == 1){ //adaugare actor
                        f[id].setNrActori(f[id].getNrActori() + 1);

                        cout << "\nIntroduceti ID actor:\n";

                        unsigned id_actor;
                        cin >> id_actor;
                        while(id_actor >= a.size()){
                            cout << "\nIntroduceti ID actor:\n";
                            cin >> id_actor;
                        }

                        f[id].getActori().push_back(&a[id_actor]);
                    }
                    else if(alegere == 2){ //stergere actor
                        f[id].setNrActori(f[id].getNrActori() - 1);

                        cout << "\nIntroduceti ID actor:\n";

                        unsigned id_actor;
                        cin >> id_actor;
                        while(id_actor >= a.size()){
                            cout << "\nIntroduceti ID actor:\n";
                            cin >> id_actor;
                        }

                        f[id].getActori().erase(f[id].getActori().begin() + id_actor);
                    }
                    else if(alegere == 3){ //modificare regizor
                        cout << "\nIntroduceti ID regizor:";

                        unsigned id_regizor;
                        cin >>id_regizor;
                        while(id_regizor >= r.size()){
                            cout << "\nIntroduceti ID regizor:";
                            cin >> id_regizor;
                        }

                        f[id].setRegizor(&r[id_regizor]);
                    }
                    else if(alegere == 4){ //modificare producator
                        cout << "\nIntroduceti ID producator:";

                        unsigned id_producator;
                        cin >>id_producator;
                        while(id_producator >= p.size()){
                            cout << "\nIntroduceti ID producator:";
                            cin >> id_producator;
                        }

                        f[id].setProducator(&p[id_producator]); //atributul producator pointeaza catre un element din vectorul de producatori din main
                    }

                }
                else if(alegere == 3){ //vanzare film
                    cout << "\nIntroduceti ID film: ";

                    unsigned id;
                    cin >> id;
                    while(id >= f.size()){
                        cout << "\nIntroduceti ID film: ";
                        cin >> id;
                    }

                    Buget::setCapital(Buget::getCapital() + f[id].getVenit());
                    f.erase(f.begin() + id);
                }
                else if(alegere == 4){ //catre resurse umane
                    break;
                }
            }
        }
        else if(alegere == 3){ //departamentul financiar
            while(true){
                cout << "\nIntroduceti 1 pentru afisarea investitiilor\n";
                cout << "Introduceti 2 pentru introducerea unei investitii\n";
                cout << "Introduceti 3 pentru stergerea unei investitii\n";
                cout << "Introduceti 4 pentru intoarcerea la meniul principal\n";

                int alegere;
                cin >> alegere;
                while(alegere > 4){
                    cin >> alegere;
                }

                if(alegere == 1){ //afisare investitii
                    cout << '\n';
                    for(unsigned i = 0; i < b.size(); i++){
                        cout << "ID investitie: " << i << '\n';
                        cout << b[i] << '\n';
                    }
                }
                else if(alegere == 2){ //creare investitie
                    Buget b1;
                    cout << '\n';
                    cin >> b1;

                    b.push_back(b1);
                }
                else if(alegere == 3){
                    cout << "\nIntroduceti ID investitie: ";

                    unsigned id;
                    cin >> id;
                    while(id >= f.size()){
                        cout << "\nIntroduceti ID investitie: ";
                        cin >> id;
                    }

                    b.erase(b.begin() + id);
                }
                else if(alegere == 4){ //intoarcere meniu principal
                    break;
                }

            }
        }
        else if(alegere == 4){ //final
            break;
        }
    }

    return 0;
}
