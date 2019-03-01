#include <iostream>
#include <string.h>
#define max 50
using namespace std;
class automobil
{
protected:
    float lungime;
public:
    automobil(int x=0) {lungime=x;};
    automobil(automobil&x) {lungime=x.lungime;};
    virtual ~automobil() {lungime=0;};
    virtual void afisare() {cout<<"Lungime: "<<lungime<<endl;};
    friend int operator==(automobil&,automobil&);
    automobil& operator=(const automobil&);
    friend istream& operator>>(istream&,automobil&);
    virtual void citire() {};
    virtual void set_lungime(float a) {lungime=a;};
    void afis() {cout<<"Automobil"<<endl<<"Lungime: "<<lungime<<endl;}
};
class mini:public automobil
{
public:
    mini(float x=0):automobil(x){};
    mini(mini&x):automobil(x) {};
    void afisare() {cout<<"Masina mini"<<endl; automobil::afisare();}
};
class mica:public automobil
{
public:
    mica(float x=0):automobil(x) {};
    mica(mica&x):automobil(x) {};
    void afisare() {cout<<"Masina mica"<<endl; automobil::afisare();}
};
class compacta:public automobil
{
    char tip[30];
public:
    compacta(float x=0,char a[30]="sedan"):automobil(x)
    {
        try
        {
            if (strcmp(a,"hatchback")!=0&&strcmp(a,"combi")!=0&&strcmp(a,"sedan")!=0) throw 'a';
        }
        catch(char c)
        {
            cout<<"Nu exista tipul de masina!"<<endl;
            cin>>a;
        }
        catch(...) {cout<<"Eroare"<<endl;}
        strcpy(tip,a);
    };
    compacta(compacta&x):automobil(x) {strcpy(tip,x.tip);};
    void afisare() {cout<<"Masina compacta"<<endl; automobil::afisare(); cout<<"Tip: "<<tip<<endl;};
    friend int operator==(compacta&,compacta&);
    compacta& operator=(const compacta&);
    friend istream& operator>>(istream&,compacta&);
    void citire();
};
class monovolum:public automobil
{
    int an_fabr;
public:
    monovolum(float x=0,int a=2018):automobil(x) {an_fabr=a;};
    monovolum(monovolum&x):automobil(x) {an_fabr=x.an_fabr;};
    void afisare() {cout<<"Masina monovolum"<<endl; automobil::afisare(); cout<<"An fabricatie: "<<an_fabr<<endl;}
    friend int operator==(monovolum&,monovolum&);
    monovolum& operator=(const monovolum&);
    void discount();
    friend istream& operator>>(istream&,monovolum&);
    void citire();
};
template <class T> class vanzare
{
    int nr_stoc;
    int nr_vanz;
    automobil* v_stoc[50];
    automobil* v_vanz[50];
public:
    vanzare(int a=0,int b=0):nr_stoc(a),nr_vanz(b)
    {
        try
        {
            if (a<0||b<0) throw -1;
            if (a>50||b>50) throw 50;
        }
        catch(int x)
        {
            if (x==-1) cout<<"Numarul de elemente al vectorului trebuie sa fie pozitiv!"<<endl;
            if (x==50) cout<<"Numarul de elemente al vectorului trebuie sa fie mai mic decat 50!"<<endl;
        }
        catch(...) {cout<<"Eroare"<<endl;}
    };
    void adauga_stoc(float a)
    {
        v_stoc[nr_stoc]=new T;
        v_stoc[nr_stoc]->set_lungime(a);
        v_stoc[nr_stoc]->citire();
        nr_stoc++;
    };
    vanzare& operator-=(T a)
    {
        int i;
        v_vanz[nr_vanz]=new T;
        *v_vanz[nr_vanz]=a;
        nr_vanz++;
        for (i=0;i<nr_stoc;i++)
            if (*v_stoc[i]==a) break;
        for (int j=i;j<nr_stoc-1;j++) *v_stoc[j]=*v_stoc[j+1];
        nr_stoc--;
        return *this;
    };
    int afisare_stoc()
    {
        if (nr_stoc==0) {cout<<"Nu exista in stoc!"<<endl; return 0;}
        else
        {
            cout<<"Stoc:"<<endl;
            for (int i=0;i<nr_stoc;i++) v_stoc[i]->afisare();
        }
        return 1;
    }
    void afisare_vanz()
    {
        if (nr_vanz==0) cout<<"Nu exista vanzari!"<<endl;
        else
            for (int i=0;i<nr_vanz;i++) v_vanz[i]->afisare();
    }
};
template <> class vanzare <int>
{
    int nr_stoc;
    int nr_vanz;
    automobil* v_stoc[50];
    automobil* v_vanz[50];
    public:
    vanzare(int a=0,int b=0):nr_stoc(a),nr_vanz(b)
    {
        try
        {
            if (a<0||b<0) throw -1;
            if (a>50||b>50) throw 50;
        }
        catch(int x)
        {
            if (x==-1) cout<<"Numarul de elemente al vectorului trebuie sa fie pozitiv!"<<endl;
            if (x==50) cout<<"Numarul de elemente al vectorului trebuie sa fie mai mic decat 50!"<<endl;
        }
        catch(...) {cout<<"Eroare"<<endl;}
    };
    void adauga_stoc(float a)
    {
        v_stoc[nr_stoc]=new monovolum;
        v_stoc[nr_stoc]->set_lungime(a);
        v_stoc[nr_stoc]->citire();
        nr_stoc++;
    };
    vanzare& operator-=(monovolum a)
    {
        int i;
        v_vanz[nr_vanz]=new monovolum;
        *v_vanz[nr_vanz]=a;
        nr_vanz++;
        for (i=0;i<nr_stoc;i++)
            if (*v_stoc[i]==a) break;
        a.discount();
        for (int j=i;j<nr_stoc-1;j++) *v_stoc[j]=*v_stoc[j+1];
        nr_stoc--;
        return *this;
    };
    int afisare_stoc()
    {
        if (nr_stoc==0) {cout<<"Nu exista in stoc!"<<endl; return 0;}
        else
        {
            cout<<"Stoc:"<<endl;
            for (int i=0;i<nr_stoc;i++) v_stoc[i]->afisare();
        }
        return 1;
    };
    void afisare_vanz()
    {
        if (nr_vanz==0) cout<<"Nu exista vanzari!"<<endl;
        else
            for (int i=0;i<nr_vanz;i++) v_vanz[i]->afisare();
    }
};
int operator==(automobil&a,automobil&b)
{
    if (a.lungime==b.lungime) return 1;
    return 0;
}
 automobil& automobil::operator=(const automobil&x)
 {
     if (this!=&x) lungime=x.lungime;
     return *this;
 }
istream& operator>>(istream&in,automobil&a)
 {
     cout<<"Lungime: ";
     in>>a.lungime;
     return in;
 }
int operator==(compacta&a,compacta&b)
{
    if (a.lungime==b.lungime&&strcmp(a.tip,b.tip)==0) return 1;
    return 0;
}
compacta& compacta::operator=(const compacta&x)
{
    if (this!=&x)
    {
        lungime=x.lungime;
        strcpy(tip,x.tip);
    }
    return *this;
}
istream& operator>>(istream&in,compacta&a)
{
     cout<<"Lungime: ";
     in>>a.lungime;
     cout<<"Tip (hatchback/combi/sedan): ";
     in>>a.tip;
     try
    {
        if (strcmp(a.tip,"hatchback")!=0&&strcmp(a.tip,"combi")!=0&&strcmp(a.tip,"sedan")!=0) throw 'a';
    }
    catch(char c)
    {
        cout<<"Nu exista tipul de masina!"<<endl<<"Introduceti un tip de masina compacta existent"<<endl;
        in>>a.tip;
    }
    catch(...) {cout<<"Eroare"<<endl;}
    return in;
}
void compacta::citire()
{
    cout<<"Tip (hatchback/combi/sedan): ";
    cin>>tip;
    try
        {
            if (strcmp(tip,"hatchback")!=0&&strcmp(tip,"combi")!=0&&strcmp(tip,"sedan")!=0) throw 'a';
        }
        catch(char c)
        {
            cout<<"Nu exista tipul de masina!"<<endl<<"Introduceti un tip de masina compacta existent"<<endl;
            cin>>tip;
        }
        catch(...) {cout<<"Eroare"<<endl;}
}
int operator==(monovolum&a,monovolum&b)
{
    if (a.lungime==b.lungime&&a.an_fabr==b.an_fabr) return 1;
    return 0;
}
monovolum& monovolum::operator=(const monovolum&x)
{
    if (this!=&x)
    {
        lungime=x.lungime;
        an_fabr=x.an_fabr;
    }
    return *this;
}
void monovolum::discount()
{
    int x=0;
    char rasp[2];
    cout<<"Este zi de vara? (da/nu)"<<endl;
    cin>>rasp;
    if (rasp[0]=='d') x=10;
    x+=2018-an_fabr;
    cout<<"Aveti discount de "<<x<<"%!"<<endl;
}
istream& operator>>(istream&in,monovolum&a)
{
     cout<<"Lungime: ";
     in>>a.lungime;
     cout<<"An fabricatie: ";
     in>>a.an_fabr;
     return in;
}
void monovolum::citire()
{
    cout<<"An fabricatie: ";
    cin>>an_fabr;
}
int main()
{
    vanzare<mini> v1;
    vanzare<mica> v2;
    vanzare<compacta> v3;
    vanzare<int> v4;
    int stop=1,rasp,exista;
    char m[10];
    float l;
    cout<<"Exemplu dynamic_cast (downcasting de la automobil la monovolum):"<<endl;
    automobil *a=new monovolum(3,2005);
    monovolum *b=dynamic_cast<monovolum*>(a);
    cout<<"Functie nevirtuala:"<<endl;
    b->afis();
    cout<<"Functie virtuala:"<<endl;
    b->afisare();
    while (stop)
    {
        cout<<"1. Adaugare stoc"<<endl<<"2. Vanzare"<<endl<<"3. Verificare stoc"<<endl<<"4. Verificare vanzari"<<endl<<"5. Stop"<<endl;
        cin>>rasp;
        switch (rasp)
        {
        case 1:
            cout<<"Lungime: ";
            cin>>l;
            if (l<3.85)
            {
                cout<<"Ati adaugat o masina mini"<<endl;
                v1.adauga_stoc(l);
            }
            if (l>=3.85&&l<4.2)
            {
                cout<<"Ati adaugat o masina mica"<<endl;
                v2.adauga_stoc(l);
            }
             if (l>=4.2&&l<4.5)
            {
                cout<<"Ati adaugat o masina compacta"<<endl;
                v3.adauga_stoc(l);
            }
            if (l>=4.5)
            {
                cout<<"Ati adaugat un monovolum"<<endl;
                v4.adauga_stoc(l);
            }
            break;
        case 2:
            cout<<"Ce masina doriti sa cumparati? (mini/mica/compacta/monovolum)"<<endl;
            cin>>m;
             try
            {
                if (strcmp(m,"mini")!=0&&strcmp(m,"mica")!=0&&strcmp(m,"compacta")!=0&&strcmp(m,"monovolum")!=0) throw 'e';
            }
            catch(char c)
            {
                cout<<"Nu exista tipul de masina!"<<endl<<"Introduceti un tip de masina existent"<<endl;
                cin>>m;
            }
            catch(...) {cout<<"Eroare"<<endl;}
            if (strcmp(m,"mini")==0)
            {
                exista=v1.afisare_stoc();
                if (exista==1)
                {
                    cout<<"Introduceti datele masinii dorite: "<<endl;
                    mini a;
                    cin>>a;
                    v1-=a;
                    v1.afisare_stoc();
                }
            }
            if (strcmp(m,"mica")==0)
            {
                exista=v2.afisare_stoc();
                if (exista==1)
                {
                    cout<<"Introduceti datele masinii dorite: "<<endl;
                    mica a;
                    cin>>a;
                    v2-=a;
                    v2.afisare_stoc();
                }
            }
            if (strcmp(m,"compacta")==0)
            {
                exista=v3.afisare_stoc();
                if (exista==1)
                {
                    cout<<"Introduceti datele masinii dorite: "<<endl;
                    compacta a;
                    cin>>a;
                    v3-=a;
                    v3.afisare_stoc();
                }
            }
            if (strcmp(m,"monovolum")==0)
            {
                exista=v4.afisare_stoc();
                if (exista==1)
                {
                    cout<<"Introduceti datele masinii dorite: "<<endl;
                    monovolum a;
                    cin>>a;
                    v4-=a;
                    v4.afisare_stoc();
                }
            }
            break;
        case 3:
            cout<<"La ce tip de masina doriti sa verificati stocul? (mini/mica/compacta/monovolum)"<<endl;
            cin>>m;
             try
            {
                if (strcmp(m,"mini")!=0&&strcmp(m,"mica")!=0&&strcmp(m,"compacta")!=0&&strcmp(m,"monovolum")!=0) throw 'e';
            }
            catch(char c)
            {
                cout<<"Nu exista tipul de masina!"<<endl<<"Introduceti un tip de masina existent"<<endl;
                cin>>m;
            }
            catch(...) {cout<<"Eroare"<<endl;}
            if (strcmp(m,"mini")==0) v1.afisare_stoc();
            if (strcmp(m,"mica")==0) v2.afisare_stoc();
            if (strcmp(m,"compacta")==0) v3.afisare_stoc();
            if (strcmp(m,"monovolum")==0) v4.afisare_stoc();
            break;
        case 4:
            cout<<"La ce tip de masina doriti sa verificati vanzarile? (mini/mica/compacta/monovolum)"<<endl;
            cin>>m;
             try
            {
                if (strcmp(m,"mini")!=0&&strcmp(m,"mica")!=0&&strcmp(m,"compacta")!=0&&strcmp(m,"monovolum")!=0) throw 'e';
            }
            catch(char c)
            {
                cout<<"Nu exista tipul de masina!"<<endl<<"Introduceti un tip de masina existent"<<endl;
                cin>>m;
            }
            catch(...) {cout<<"Eroare"<<endl;}
            if (strcmp(m,"mini")==0) v1.afisare_vanz();
            if (strcmp(m,"mica")==0) v2.afisare_vanz();
            if (strcmp(m,"compacta")==0) v3.afisare_vanz();
            if (strcmp(m,"monovolum")==0) v4.afisare_vanz();
            break;
        case 5:
            stop=0;
            break;
        }
    }
    return 0;
}
