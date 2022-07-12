#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

bool isInteger(char* s){ // converteste siruri de caractere la int
    for(unsigned i = 0; i < strlen(s); i++)
        if(!isdigit(s[i]))
            return false;
    return true;
}

bool isString(char* s){
    for(unsigned i = 0; i < strlen(s); i++)
        if(s[i] == ' ') // verific daca sirul contine spatiu
            return false;
    return true;
}

class Interfata_IO{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class IsNotInteger: public exception{
public:
    virtual const char* what() const throw(){
        return "Va rugam sa introduceti un numar intreg";
    }
}isNotInteger;

class HasSpace: public exception{
public:
    virtual const char* what() const throw(){
        return "Va rugam sa nu introduceti spatiu";
    }
}hasSpace;

class IsNotIntegerAndHasSpace: public IsNotInteger, public HasSpace{
public:
    virtual const char* what() const throw(){
        return "Va rugam sa introduceti un numar intreg fara spatii";
    }
}isNotIntegerAndHasSpace;


class Utilizator: public Interfata_IO{
private:
    string nume, descriere;
    int varsta;
    vector<Utilizator*> prieteni;
public:
    Utilizator(){
        this->nume = "anonim";
    }
    Utilizator(string nume, string descriere, int varsta){
        this->nume = nume;
        this->descriere = descriere;
        this->varsta = varsta;
    }
    Utilizator(const Utilizator& u){
        this->nume = u.nume;
        this->descriere = u.descriere;
        this->varsta = u.varsta;
    }
    ~Utilizator(){}
    string getNume() const{
        return this->nume;
    }
    string getDescriere() const{
        return this->descriere;
    }
    int getVarsta() const{
        return this->varsta;
    }
    vector<Utilizator*> getPrieteni() const{
        return this->prieteni;
    }
    void setNume(string nume){
        this->nume = nume;
    }
    void setDescriere(string descriere){
        this->descriere = descriere;
    }
    void setVarsta(int varsta){
        this->varsta = varsta;
    }
    void setPrieteni(vector<Utilizator*> p){
        this->prieteni = p;
    }
    Utilizator& operator=(const Utilizator& u){
        if(this != &u){
            this->nume = u.nume;
            this->descriere = u.descriere;
            this->varsta = u.varsta;
        }
        return *this;
    }
    istream& citire(istream& in){
        while(true){
            try{
                char s[101];
                cout << "Introduceti numele:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw hasSpace;
                this->nume = (string)s;
                break;
            }
            catch(HasSpace){
                cout << hasSpace.what() << '\n';
            }
        }
        while(true){
            try{
                char s[101];
                cout << "Introduceti descrierea:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw hasSpace;
                this->descriere = (string)s;
                break;
            }
            catch(HasSpace){
                cout << hasSpace.what() << '\n';
            }
        }
        while(true){
            try{
                char s[101];
                cout << "Introduceti varsta:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw isNotIntegerAndHasSpace;
                else if(!isInteger(s))
                    throw isNotInteger;
                this->varsta = atoi(s);
                break;
            }
            catch(IsNotIntegerAndHasSpace){
                cout << isNotIntegerAndHasSpace.what() << '\n';
            }
            catch(IsNotInteger){
                cout << isNotInteger.what() << '\n';
            }
        }

        return in;
    }
    ostream& afisare(ostream& out) const{
        out << "Numele: " << this->nume << '\n';
        out << "Descrierea: " << this->descriere << '\n';
        out << "Varsta: " << this->varsta << '\n';

        return out;
    }
    friend istream& operator>>(istream& in, Utilizator& u){
        u.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Utilizator& u){
        u.afisare(out);
        return out;
    }
    Utilizator& operator+=(Utilizator& u){
        this->prieteni.push_back(&u);
        return *this;
    }
    Utilizator& operator-=(Utilizator& u){
        vector<Utilizator*>::iterator i;
        for(i = this->prieteni.begin(); i != this->prieteni.end(); i++){
            if(*i == &u)
                this->prieteni.erase(i);
        }
        return *this;
    }
    bool operator<(Utilizator& u) const{
        if(this->varsta < u.varsta)
            return true;
        return false;
    }
    void afiseaza_prieteni(){
        vector<Utilizator*>::iterator i;
        for(i = this->prieteni.begin(); i != this->prieteni.end(); i++)
            cout << **i << '\n';
    }
};


class Actiune: public Interfata_IO{
protected:
    string data;
    Utilizator* u;
public:
    Actiune(){
        this->data = "neprecizat";
    }
    Actiune(string data, Utilizator* u){
        this->data = data;
        this->u = u;
    }
    Actiune(const Actiune& a){
        this->data = a.data;
        this->u = a.u;
    }
    ~Actiune(){}
    string getData() const{
        return this->data;
    }
    Utilizator* getUtilizator() const{
        return this->u;
    }
    void setData(string data){
        this->data = data;
    }
    void setUtilizator(Utilizator* u){
        this->u = u;
    }
    virtual Actiune& operator=(const Actiune& a){
        if(this != &a){
            this->data = a.data;
            this->u = a.u;
        }
        return *this;
    }
    virtual istream& citire(istream& in){
        while(true){
            try{
                char s[101];
                cout << "Introduceti data:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw hasSpace;
                this->data = (string)s;
                break;
            }
            catch(HasSpace){
                cout << hasSpace.what() << '\n';
            }
        }
        return in;
    }
    virtual ostream& afisare(ostream& out) const{
        out << "Data: " << this->data << '\n';
        if(this->u)
            out << *this->u;
        return out;
    }
    friend istream& operator>>(istream& in, Actiune& a){
        a.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Actiune& a){
        a.afisare(out);
        return out;
    }
};


class Postare: virtual public Actiune{
protected:
    char* text;
public:
    Postare():Actiune(){
        this->text = new char[strlen("Ceva pe aici") + 1];
        strcpy(this->text, "Ceva pe aici");
    }
    Postare(string data, Utilizator* u, char* text): Actiune(data, u){
        this->text = new char[strlen(text) + 1];
        strcpy(this->text, text);
    }
    Postare(const Postare& p): Actiune(p){
        this->text = new char[strlen(p.text) + 1];
        strcpy(this->text, p.text);
    }
    ~Postare(){
        if(this->text)
            delete[] this->text;
    }
    char* getText() const{
        return this->text;
    }
    void setText(char* s){
        if(this->text)
            delete[] this->text;
        this->text = new char[strlen(s) + 1];
        strcpy(this->text, s);
    }
    virtual Postare& operator=(const Postare& p){
        if(this != &p){
            Actiune::operator=(p);
            if(this->text)
                delete[] this->text;
            this->text = new char[strlen(p.text) + 1];
            strcpy(this->text, p.text);
            this->u = p.u;
        }
        return *this;
    }
    virtual istream& citire(istream& in){
        Actiune::citire(in);
        cout << "Introduceti postarea:\n";
        char s[101];
        in.getline(s, 101);
        this->text = new char[strlen(s) + 1];
        strcpy(this->text, s);

        return in;
    }
    virtual ostream& afisare(ostream& out) const{
        Actiune::afisare(out);
        if(this->text)
            out << "Postarea:\n" << this->text << '\n';
        return out;
    }
    friend istream& operator>>(istream& in, Postare& p){
        p.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Postare& p){
        p.afisare(out);
        return out;
    }
};


class Distribuire: virtual public Actiune{
protected:
    Postare* p;
public:
    Distribuire(): Actiune(){}
    Distribuire(string data, Utilizator* u, Postare* p): Actiune(data, u){
        this->p = p;
    }
    Distribuire(const Distribuire& d): Actiune(d){
        this->p = d.p;
    }
    ~Distribuire(){}
    Postare* getPostare() const{
        return this->p;
    }
    void setPostare(Postare* p){
        this->p = p;
    }
    virtual Distribuire& operator=(const Distribuire& d){
        if(this != &d){
            Actiune::operator=(d);
            this->p = d.p;
        }
        return *this;
    }
    virtual istream& citire(istream& in){
        Actiune::citire(in);
        return in;
    }
    virtual ostream& afisare(ostream& out)const{
        out << "(Distribuit)\n";
        Actiune::afisare(out);
        out << "Postarea distribuita:\n" << *this->p << '\n';
        return out;
    }
    friend istream& operator>>(istream& in, Distribuire& d){
        d.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Distribuire& d){
        d.afisare(out);
        return out;
    }
};


class Comentariu: public Postare, public Distribuire{
private:
    int relevanta;
public:
    Comentariu(): Postare(), Distribuire(), Actiune(){
        this->relevanta = 0;
    }
    Comentariu(string data, Utilizator* u, char* text, Postare* p, int relevanta): Postare(data, u, text), Distribuire(data, u, p), Actiune(data, u){
        this->relevanta = relevanta;
    }
    Comentariu(const Comentariu& c): Postare(c), Distribuire(c), Actiune(c){
        this->relevanta = c.relevanta;
    }
    ~Comentariu(){}
    int getRelevanta(){
        return this->relevanta;
    }
    void setRelevanta(int relevanta){
        this->relevanta = relevanta;
    }
    Comentariu& operator=(const Comentariu& c){
        if(this != &c){
            Postare::operator=(c);
            this->p = c.p;
            this->relevanta = c.relevanta;
        }
        return *this;
    }
    istream& citire(istream& in){
        Postare::citire(in);
        while(true){
            try{
                char s[101];
                cout << "Introduceti relevanta:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw isNotIntegerAndHasSpace;
                else if(!isInteger(s))
                    throw isNotInteger;
                this->relevanta = atoi(s);
                break;
            }
            catch(IsNotIntegerAndHasSpace){
                cout << isNotIntegerAndHasSpace.what() << '\n';
            }
            catch(IsNotInteger){
                cout << isNotInteger.what() << '\n';
            }
        }
        return in;
    }
    ostream& afisare(ostream& out) const{
        cout << "(Comentariu)\n";
        Postare::afisare(out);
        out << "Postarea comentata:\n" << *this->p;
        out << "Relevanta comentariu: " << this->relevanta << '\n';
        return out;
    }
    friend istream& operator>>(istream& in, Comentariu& c){
        c.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Comentariu& c){
        c.afisare(out);
        return out;
    }
};


template<class Type>
class Like: public Interfata_IO{
private:
    int nota;
    Type* target;
public:
    Like(){
        this->nota = 0;
    }
    Like(int nota, Type* target){
        this->nota = nota;
        this->target = target;
    }
    Like(const Like& l){
        this->nota = l.nota;
        this->target = l.target;
    }
    ~Like(){}
    int getNota() const{
        return this->nota;
    }
    Type* getTarget() const{
        return this->target;
    }
    void setNota(int nota){
        this->nota = nota;
    }
    void setTarget(Type* target){
        this->target = target;
    }
    Like& operator=(const Like& l){
        if(this != &l){
            this->nota = l.nota;
            this->target = l.target;
        }
        return *this;
    }
    istream& citire(istream& in){
        while(true){
            try{
                char s[101];
                cout << "Introduceti nota:\n";
                in.getline(s, 101);
                if(!isString(s))
                    throw isNotIntegerAndHasSpace;
                else if(!isInteger(s))
                    throw isNotInteger;
                this->nota = atoi(s);
                break;
            }
            catch(IsNotIntegerAndHasSpace){
                cout << isNotIntegerAndHasSpace.what() << '\n';
            }
            catch(IsNotInteger){
                cout << isNotInteger.what() << '\n';
            }
        }
        return in;
    }
    ostream& afisare(ostream& out) const{
        out << *this->target << '\n';
        out << "Nota: " << this->nota << '\n';

        return out;
    }
    friend istream& operator>>(istream& in, Like& l){
        l.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Like& l){
        l.afisare(out);
        return out;
    }
};


template<class type1, class type2>
bool same_user(const type1& a1, const type2& a2){
    if(a1.getUtilizator() == a2.getUtilizator())
        return true;
    return false;
}

template<class Type>
bool peste_medie(const Type& l1){
    if(l1.getNota() > 8)
        return true;
    else return false;
}


class MeniuAplicatie{
private:
    static MeniuAplicatie* instanta;
    MeniuAplicatie(){}
    MeniuAplicatie(const MeniuAplicatie&){}
public:
    static MeniuAplicatie* getInstance(){
        if(!instanta){
            instanta = new MeniuAplicatie();
        }
        return instanta;
    }
    void getMeniu(){

        Utilizator* u1 = new Utilizator("A", "Alerg", 25);
        Utilizator* u2 = new Utilizator("B", "Dorm", 22);
        Utilizator* u3 = new Utilizator("C", "Mananc", 44);
        Actiune* a1 = new Actiune("06", u2);
        Postare* p1 = new Postare("05", u1, "Aceasta este p1");

        // Utilizez vector deoarece vreau sa accesez utilizatorii dupa ID
        vector<Utilizator*> u;
        vector<Actiune*> a;
        // Utilizez list deoarece vreau doar sa afisez toate aprecierile
        list<Like<Postare> > l;
        // Asociez fiecarei postari comentariile aferente, comentariile trebuie sa fie unice
        map<Postare*, set<Comentariu*> > c;

        u.push_back(u1);
        u.push_back(u2);
        u.push_back(u3);
        a.push_back(a1);
        a.push_back(p1);

        while(true){
            cout << "Introduceti 1 pentru a afisa toti utilizatorii\n";
            cout << "Introduceti 2 pentru a afisa fluxul de stiri\n";
            cout << "Introduceti 3 pentru a scrie o postare\n";
            cout << "Introduceti 4 pentru a afisa toate postarile\n";
            cout << "Introduceti 5 pentru a comenta o postare\n";
            cout << "Introduceti 6 pentru a afisa toate comentariile unei anumite postari\n";
            cout << "Introduceti 7 pentru a crea un utilizator\n";
            cout << "Introduceti 8 pentru a aprecia o postare\n";
            cout << "Introduceti 9 pentru a afisa toate aprecierile\n";
            cout << "Introduceti 10 pentru a incheia sesiunea\n\n";

            int optiune;
            while(true){
                try{
                    char s[101];
                    cout << "Introduceti optiunea dorita:\n";
                    cin.getline(s, 101);
                    if(!isString(s))
                        throw isNotIntegerAndHasSpace;
                    else if(!isInteger(s))
                        throw isNotInteger;
                    optiune = atoi(s);
                    if(optiune > 10)
                        continue;
                    break;
                }
                catch(IsNotIntegerAndHasSpace){
                    cout << isNotIntegerAndHasSpace.what() << '\n';
                }
                catch(IsNotInteger){
                    cout << isNotInteger.what() << '\n';
                }
            }

            if(optiune == 1){
                for(int i = 0; i < u.size(); i++){
                    cout << "ID: " << i << '\n';
                    cout << *u[i] << '\n';
                }

            }
            else if(optiune == 2){
                vector<Actiune*>::iterator i;
                int j;
                for(i = a.begin(), j = 0; i != a.end(); i++, j++){
                    cout << "ID Actiune: " << j << '\n';
                    cout << **i << '\n';
                }
            }
            else if(optiune == 3){
                int id;
                while(true){
                    try{
                        char s[101];
                        cout << "Introduceti id utilizator:\n";
                        cin.getline(s, 101);
                        if(!isString(s))
                            throw isNotIntegerAndHasSpace;
                        else if(!isInteger(s))
                            throw isNotInteger;
                        id = atoi(s);
                        if(id >= u.size())
                            continue;
                        break;
                    }
                    catch(IsNotIntegerAndHasSpace){
                        cout << isNotIntegerAndHasSpace.what() << '\n';
                    }
                    catch(IsNotInteger){
                        cout << isNotInteger.what() << '\n';
                    }
                }
                Actiune* p1 = new Postare();
                cin >> *p1;
                p1->setUtilizator(u[id]);
                a.push_back(p1);
            }
            else if(optiune == 4){
                vector<Actiune*>::iterator i;
                int j;
                for(i = a.begin(), j = 0; i != a.end(); i++, j++){
                    Actiune* a1 = *i;
                    if(dynamic_cast<Postare*>(a1)){
                        Postare* p1 = dynamic_cast<Postare*>(a1);
                        cout << "ID Postare: " << j << '\n';
                        cout << *p1 << '\n';
                    }
                }
            }
            else if(optiune == 5){
                int id;
                while(true){
                    try{
                        char s[101];
                        cout << "Introduceti id postare:\n";
                        cin.getline(s, 101);
                        if(!isString(s))
                            throw isNotIntegerAndHasSpace;
                        else if(!isInteger(s))
                            throw isNotInteger;
                        id = atoi(s);
                        if(id >= u.size())
                            continue;
                        if(!dynamic_cast<Postare*>(a[id]))
                            continue;
                        break;
                    }
                    catch(IsNotIntegerAndHasSpace){
                        cout << isNotIntegerAndHasSpace.what() << '\n';
                    }
                    catch(IsNotInteger){
                        cout << isNotInteger.what() << '\n';
                    }
                }
                int id_utilizator;
                while(true){
                    try{
                        char s[101];
                        cout << "Introduceti id utilizator:\n";
                        cin.getline(s, 101);
                        if(!isString(s))
                            throw isNotIntegerAndHasSpace;
                        else if(!isInteger(s))
                            throw isNotInteger;
                        id_utilizator = atoi(s);
                        if(id >= u.size())
                            continue;
                        if(!dynamic_cast<Postare*>(a[id]))
                            continue;
                        break;
                    }
                    catch(IsNotIntegerAndHasSpace){
                        cout << isNotIntegerAndHasSpace.what() << '\n';
                    }
                    catch(IsNotInteger){
                        cout << isNotInteger.what() << '\n';
                    }
                }
                Postare* p1 = dynamic_cast<Postare*>(a[id]);
                Comentariu* c1 = new Comentariu();
                cin >> *c1;
                c1->setUtilizator(u[id]);
                c1->setPostare(p1);
                c[p1].insert(c1);
            }
            else if(optiune == 6){
                int id;
                while(true){
                    try{
                        char s[101];
                        cout << "Introduceti id postare:\n";
                        cin.getline(s, 101);
                        if(!isString(s))
                            throw isNotIntegerAndHasSpace;
                        else if(!isInteger(s))
                            throw isNotInteger;
                        id = atoi(s);
                        if(id >= u.size())
                            continue;
                        if(!dynamic_cast<Postare*>(a[id]))
                            continue;
                        break;
                    }
                    catch(IsNotIntegerAndHasSpace){
                        cout << isNotIntegerAndHasSpace.what() << '\n';
                    }
                    catch(IsNotInteger){
                        cout << isNotInteger.what() << '\n';
                    }
                }
                Postare* p1 = dynamic_cast<Postare*>(a[id]);
                set<Comentariu*>::iterator i;
                for(i = c[p1].begin(); i != c[p1].end(); i++)
                    cout << **i << '\n';

            }
            else if(optiune == 7){
                Utilizator* u1 = new Utilizator();
                cin >> *u1;
                u.push_back(u1);
            }
            else if(optiune == 8){
                int id;
                while(true){
                    try{
                        char s[101];
                        cout << "Introduceti id postare:\n";
                        cin.getline(s, 101);
                        if(!isString(s))
                            throw isNotIntegerAndHasSpace;
                        else if(!isInteger(s))
                            throw isNotInteger;
                        id = atoi(s);
                        if(id >= u.size())
                            continue;
                        if(!dynamic_cast<Postare*>(a[id]))
                            continue;
                        break;
                    }
                    catch(IsNotIntegerAndHasSpace){
                        cout << isNotIntegerAndHasSpace.what() << '\n';
                    }
                    catch(IsNotInteger){
                        cout << isNotInteger.what() << '\n';
                    }
                }
                Postare* p1 = dynamic_cast<Postare*>(a[id]);
                Like<Postare> l1;
                cin >> l1;
                l1.setTarget(p1);
                l.push_back(l1);

            }
            else if(optiune == 9){
                list<Like<Postare> >::iterator i;
                for(i = l.begin(); i != l.end(); i++)
                    cout << *i << '\n';
            }
            else if(optiune == 10){
                break;
            }
        }
    }
};
MeniuAplicatie* MeniuAplicatie::instanta = 0;

int main()
{
    MeniuAplicatie* meniu = meniu->getInstance();
    meniu->getMeniu();
    return 0;
}
