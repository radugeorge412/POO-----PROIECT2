#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//---------------------------CLASA LOCUINTA (BAZA) ---------------------------------

class Locuinta
{
protected:
    string numeClient;
    int suprafataUtila;
    float discount;
public:
    Locuinta(string, int, float);
    Locuinta(Locuinta&);
    virtual ~Locuinta();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, Locuinta& z);
    friend ostream& operator<<(ostream&, Locuinta& z);
    Locuinta &operator=(const Locuinta& z);
    virtual float CalculChirie(int x, bool y)=0;

    friend class AgentieImobiliara;

    int get_suprafata()
    {
        return suprafataUtila;
    }

};

//CONSTRUCTOR INITIALIZARE
Locuinta::Locuinta(string nume="", int suprafata=0, float discount=0)
{
    numeClient = nume;
    suprafataUtila = suprafata;
    this->discount = discount;
}
//CONSTRUCTOR COPIERE
Locuinta::Locuinta(Locuinta& z)
{
    numeClient = z.numeClient;
    suprafataUtila = z.suprafataUtila;
    discount = z.discount;
}

//DESTRUCTOR
Locuinta::~Locuinta()
{
    numeClient="";
    suprafataUtila=0;
    discount=0;
};

//CITIRE/AFISARE/OPERATORI I/O
void Locuinta::citire(istream& in)
{
    string nume;
    cout<<"Numele proprietarului: ";
    in.get();
    in>>nume;
    numeClient = nume;
    cout<<endl;

    cout<<"Suprafata utila: ";
    in>>suprafataUtila;
    cout<<endl;

    cout<<"Discount: ";
    in>>discount;
    cout<<endl;
}

istream& operator>>(istream& in, Locuinta& z)
{
    z.citire(in);
    return in;
}

void Locuinta::afisare(ostream& out)
{
    out<<"Nume Client: "<<numeClient<<endl;
    out<<"Suprafata utila: "<<suprafataUtila<<endl;
    out<<"Discount: "<<discount<<endl;
}

ostream& operator<<(ostream& out, Locuinta& z)
{
    z.afisare(out);
    return out;
}

//SUPRAINCARCARE PE =
Locuinta &Locuinta::operator=(const Locuinta& z)
{
    if(this==&z)
        return *this;
    else
    {
        numeClient = z.numeClient;
        suprafataUtila = z.suprafataUtila;
        discount = z.discount;
    }
    return *this;
}


//-------------------------CLASA APARTAMENT------------------------------


class Apartament: public Locuinta
{
private:
    int etaj;

public:
    Apartament(string, int, float, int);
    ~Apartament();
    Apartament(Apartament& z);
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream& in, Apartament& z);
    friend ostream& operator<<(ostream& out, Apartament& z);
    Apartament& operator=(const Apartament& z);
    float CalculChirie(int x, bool y);
};


//CONSTRUCTOR INITIALIZARE
Apartament::Apartament(string nume="", int suprafata=0, float discount=0, int etaj=0):Locuinta(nume,suprafata,discount)
{
    this->etaj = etaj;
}


//DESTRUCTOR
Apartament::~Apartament()
{
    numeClient = "";
    suprafataUtila = 0;
    discount = 0;
    etaj = 0;
}

//CONSTRUCTOR COPIERE
Apartament::Apartament(Apartament &z)
{
    numeClient = z.numeClient;
    suprafataUtila = z.suprafataUtila;
    discount = z.discount;
    etaj = z.etaj;
}

//CITIRE/AFISARE/IN/OUT
void Apartament::citire(istream& in)
{
    Locuinta::citire(in);
    cout<<"Etaj: ";
    in>>etaj;
    cout<<endl;

}

istream& operator>>(istream &in, Apartament& z)
{
    z.citire(in);
    return in;
}

void Apartament::afisare(ostream &out)
{
    Locuinta::afisare(out);
    out<<"Etaj: "<<etaj<<endl;
}

ostream& operator<<(ostream& out, Apartament& z)
{
    z.afisare(out);
    return out;
}

//SUPRAINCARCARE OPERATOR =
Apartament &Apartament::operator=(const Apartament& z)
{
    if(this==&z)
        return *this;
    else
    {
        numeClient = z.numeClient;
        suprafataUtila = z.suprafataUtila;
        discount = z.discount;
        etaj = z.etaj;
    }
    return *this;
}

float Apartament::CalculChirie(int x, bool y)
{
    return x*suprafataUtila*(1-y*discount/100.0);
}


//-------------------------CLASA CASA--------------------------
class Casa: public Locuinta
{
private:
    int suprafataCurte;

public:
    Casa(string, int, float, int);
    ~Casa();
    Casa(Casa&);
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream& in, Casa& z);
    friend ostream& operator<<(ostream& out, Casa& z);
    Casa& operator=(const Casa& z);
    float CalculChirie(int, bool);



};

//CONSTRUCTOR DE INITIALIZARE
Casa::Casa(string nume="", int suprafata=0, float discount=0, int supC=0):Locuinta(nume,suprafata,discount)
{
    this->suprafataCurte = supC;
}

//DESTRUCTOR
Casa::~Casa()
{
    numeClient="";
    suprafataCurte=0;
    suprafataUtila=0;
    discount=0;

}

//CONSTRUCTOR DE COPIERE
Casa::Casa(Casa& z)
{
    suprafataUtila = z.suprafataUtila;
    suprafataCurte = z.suprafataCurte;
    discount = z.discount;
    numeClient = z.numeClient;
}

//CITIRE/AFISARE/IN/OUT
void Casa::citire(istream& in)
{
    Locuinta::citire(in);
    cout<<"Suprafata curte: ";
    in>>suprafataCurte;
    cout<<endl;

}

istream& operator>>(istream& in, Casa &z)
{
    z.citire(in);
    return in;
}

void Casa::afisare(ostream& out)
{
    Locuinta::afisare(out);
    out<<"Suprafata curte: "<<suprafataCurte<<endl;
}

ostream& operator<<(ostream &out,Casa &z)
{
    z.afisare(out);
    return out;
}

float Casa::CalculChirie(int x, bool y)
{
    return x*(suprafataUtila + 0.2*suprafataCurte)*(1-y*discount/100.0);
}

Casa &Casa::operator=(const Casa& z)
{
    if(this==&z)
        return *this;
    else
    {
        numeClient = z.numeClient;
        suprafataUtila = z.suprafataUtila;
        discount = z.discount;
        suprafataCurte = z.suprafataCurte;
    }
    return *this;

}

//-------------------------CLASA AGENTIE IMOBILIARA------------------------------

void tip(Locuinta *&p, int &i)
{
    string s;
    cout<<endl;
    cout<<"Introduce-ti tipul locuintei "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="casa")
        {
            p = new Casa;
            cin>>*p;
            i++;
        }
        else if(s=="apartament")
        {
            p = new Apartament;
            cin>>*p;
            i++;
        }
        else
            throw 10;
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip de locuinta valid. Posibilitatile sunt casa sau apartament"<<endl;
    }
}


class AgentieImobiliara
{
private:
    int nrLoc;
    Locuinta **v;
    static int pret;
    static bool dis;
public:
    AgentieImobiliara(int, Locuinta**);
    ~AgentieImobiliara();
    AgentieImobiliara(AgentieImobiliara&);
    friend istream& operator>>(istream& in,AgentieImobiliara& z);
    friend ostream& operator<<(ostream& out,AgentieImobiliara& z);
    void citire_agentii(istream &in);
    void afisare_agentii(ostream &out);
};

int AgentieImobiliara::pret;
bool AgentieImobiliara::dis;

AgentieImobiliara::AgentieImobiliara(int nrLoc=0, Locuinta **v=NULL)
{
    this->nrLoc=nrLoc;
    this->v=0;
}

AgentieImobiliara::~AgentieImobiliara()
{
    int i;
    for(i=0; i<nrLoc; i++)
        delete []v[i];
    delete[]v;
    nrLoc=0;
}

AgentieImobiliara::AgentieImobiliara(AgentieImobiliara& z)
{
    this->nrLoc=z.nrLoc;
    int i;
    for(i=0; i<nrLoc; i++)
    {
        v[i]=z.v[i];
    }
}

void AgentieImobiliara::citire_agentii(istream& in)
{
    cout<<"Da-ti numarul de locuinte ale agentiei: ";
    in>>nrLoc;
    cout<<endl;


    v=new Locuinta*[nrLoc];
    for(int i=0; i<nrLoc;)
        tip(v[i],i);


}

istream& operator>>(istream& in, AgentieImobiliara& z)
{
    z.citire_agentii(in);
    return in;
}

void AgentieImobiliara::afisare_agentii(ostream& out)
{
    out<<"Agentia are "<<nrLoc<<" locuinte"<<endl;
    int i;
    out<<"Da-ti pretul standard/mp al chirie: ";
    cin>>pret;
    out<<endl;

    out<<"Se tine cont de discount in calculul chirie? (1/0)";
    cin>>dis;
    out<<endl;
    for(i=0; i<nrLoc; i++)
    {
        out<<endl<<"Detalii locuinta nr. "<<i+1<<" :"<<endl;
        out<<*v[i]<<endl;
        out<<"Chiria acestei locuinte este: ";
        out<<v[i]->CalculChirie(pret,dis);
        out<<endl;


    }
    out<<endl;
}

ostream& operator<<(ostream& out, AgentieImobiliara& z)
{
    z.afisare_agentii(out);
    return out;
}

//-------------------------------------MENU----------------------------------------

void menu_output()
{
    cout<<"RADU GEORGE DANIEL, GRUPA 211, PROIECT NR. 7"<<endl;
    cout<<"Option 0: EXIT"<<endl;
    cout<<"Option 1: Cititi datele agentiilor imobiliare"<<endl;
    cout<<"Option 2: Afisati datele agentiilor imobiliare si chiria pentru fiecare locuinta"<<endl;

}

void menu()
{
    int option=0,ok=0,nr_agentii,i=0,j=0;
    string tip;
    menu_output();
    AgentieImobiliara *a;
    do
    {
        cout<<"Cititi optiunea: ";
        cin>>option;
        cout<<endl;
        if(option==1)
        {
            cout<<"Introduce-ti numarul de agentii imobiliare dorit: ";
            cin>>nr_agentii;
            cout<<endl;

            a=new AgentieImobiliara[nr_agentii];

            for(i=0; i<nr_agentii; i++)
            {
                cout<<"Detalii agentie nr. "<<i+1<<" :"<<endl;
                cin>>a[i];
            }

            ok=1;

        }

        if(option==2)
        {
            if(ok==0)
                cout<<"Nu s-au citit datele"<<endl;
            else
            {
                for(i=0; i<nr_agentii; i++)
                {
                    cout<<"Agentia nr. "<<i+1<<" are urmatoarele date: "<<endl;
                    cout<<a[i]<<endl;

                }
            }
        }
    }
    while(option!=0);


}

int main()
{
    menu();
    return 0;
}
