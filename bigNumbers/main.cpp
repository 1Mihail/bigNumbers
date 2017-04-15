#include <iostream>
#include <string.h>
#include <cstdlib>
#include"valid.h"
/*============================================================================================================
Big Numbers
a) Sum
b) Diference
c) Maximum absolute value

*Info: Diference shows if:
-a number has sign + and the other  -
-a number has no sign and the other -
Otherwise it shows sum.
==============================================================================================================*/
using namespace std;
class Nod
{
    int info;
    Nod *st,*dr;
public:
    void setInfo(int x);
    int getInfo();
    Nod *getSt();
    Nod *getDr();
    void setSt(Nod *x);
    void setDr(Nod *x);
};
void Nod::setInfo(int x)
{
    info=x;
}
int Nod::getInfo()
{
    return info;
}
Nod* Nod::getSt()
{
    return st;
}
Nod* Nod::getDr()
{
    return dr;
}
void Nod::setSt(Nod *x)
{
    st=x;
}
void Nod::setDr(Nod *x)
{
    dr=x;
}
class NumarMare
{
    int semn,lungime;
    char numar[10000];
    Nod *pr,*ul;
public:
    NumarMare(char *s);
    NumarMare operator +(const NumarMare &x);
    NumarMare operator -(const NumarMare &x);
    NumarMare operator >(const NumarMare &x);
    Nod* getPr() const;
    Nod* getUl() const;
    int GetLungime() const;
    void initSemn(char s[]);
    void ScoateSemn(char s[]);
    int GetSemn();
    string getNumar();
    void FormareLista();
    void AfisareListaSD();
    void AfisareListaDS();
    ~NumarMare();
};
Nod* NumarMare::getPr() const
{
    return pr;
}
Nod* NumarMare::getUl() const
{
    return ul;
}
int NumarMare::GetLungime() const
{
    return lungime;
}
void NumarMare::ScoateSemn(char s[])
{
    if(s[0]=='+'||s[0]=='-')
        memmove (s, s+1, strlen(s));
    lungime=strlen(s);
}
void NumarMare::initSemn(char s[])
{
    if(s[0]=='-')
        semn=-1;
    else semn=1;
}
int NumarMare::GetSemn()
{
    return semn;
}
string NumarMare::getNumar()
{
    return numar;
}
void NumarMare::FormareLista()
{
    int i;
    Nod *p,*c,*u;
    for(i=0; i<GetLungime(); i++)
    {
        c=new Nod;
        c->setInfo(numar[i]-'0');
        if(i==0)
        {
            p=c;
            p->setDr(NULL);
            p->setSt(NULL);
            u=p;
        }
        else
        {
            u->setDr(c);
            c->setSt(u);
            u=c;
            u->setDr(NULL);
        }
    }
    pr=p;
    ul=u;
}
void NumarMare::AfisareListaSD()
{
    Nod *c;
    c=pr;
    while(c)
    {
        cout<<c->getInfo();
        c=c->getDr();
    }
}
void NumarMare::AfisareListaDS()
{
    Nod *c;
    c=ul;
    while(c)
    {
        cout<<c->getInfo();
        c=c->getSt();
    }
}
NumarMare::NumarMare(char s[])
{
    pr=NULL;
    ul=NULL;
    initSemn(s);
    ScoateSemn(s);
    strcpy(numar,s);
    FormareLista();
}
NumarMare NumarMare::operator +(const NumarMare &x)
{
    int s=0,i=0;
    Nod *p1=this->ul;
    Nod *p2=x.getUl();
    int a[100];
    while(p1!=NULL&&p2!=NULL)
    {
        a[i++]=(p1->getInfo()+p2->getInfo())%10+s;
        s=(p1->getInfo()+p2->getInfo())/10;
        p1=p1->getSt();
        p2=p2->getSt();
    }
    if(this->lungime==x.GetLungime()&&s>0)
        a[i++]=s;
    else if(this->lungime>x.GetLungime())
    {
        while(p1!=NULL)
        {
            a[i++]=p1->getInfo()+s;
            s=0;
            p1=p1->getSt();
        }
    }
    else
        while(p2!=NULL)
        {
            a[i++]=p2->getInfo()+s;
            s=0;
            p2=p2->getSt();
        }
    int n=i;
    char aux[100];
    int t=0;
    for(i=n-1; i>=0; i--)
        aux[t++]=a[i]+'0';
    aux[n]=NULL;
    NumarMare rez(aux);
    return rez;
}
NumarMare NumarMare::operator >(const NumarMare &x)
{
    Nod *p1=this->pr;
    Nod *p2=x.getPr();
    int ok=0;
    if(this->lungime > x.GetLungime())
        ok=1;
    else if(this->lungime < x.GetLungime())
        ok=2;
    else
    {
        while(p1!=NULL&&p2!=NULL)
        {
            if(p1->getInfo()>p2->getInfo())
                ok=1;
            else if(p1->getInfo()<p2->getInfo())
                ok=2;
            if(ok)
                break;
            p1=p1->getDr();
            p2=p2->getDr();
        }
    }
    if(ok==1)
        return *this;
    else return x;
}
NumarMare NumarMare::operator -(const NumarMare &x)
{
    int n,i=0,dif=0,ok=1;
    Nod *p1=this->pr;
    Nod *p2=x.getPr();
    if(this->lungime<x.GetLungime())
        ok=0;
    else if(this->lungime==x.GetLungime())
        while(p1!=NULL&&p2!=NULL)
        {
            if(p1->getInfo()<p2->getInfo())
            {
                ok=0;
                break;
            }
            p1=p1->getDr();
            p2=p2->getDr();
        }
    if(ok==0)
    {
        p1=x.getUl();
        p2=this->ul;
    }
    else
    {
        p1=this->ul;
        p2=x.getUl();
    }
    int a[100];
    while(p1!=NULL&&p2!=NULL)
    {
        dif=(p1->getInfo() - p2->getInfo());
        if(dif<0)
        {
            if(p1->getSt()!=NULL)
            {
                p1->getSt()->setInfo(p1->getSt()->getInfo()-1);
            }
            dif+=10;
        }
        a[i++]=dif;
        p1=p1->getSt();
        p2=p2->getSt();
    }
    while(p1!=NULL)
    {
        a[i++]=p1->getInfo();
        p1=p1->getSt();
    }
    while(p2!=NULL)
    {
        a[i++]=p2->getInfo();
        p2=p2->getSt();
    }
    n=i;
    if(ok==0) cout<<"-";
    for(i=n-1; i>=1; i--)
        if(a[i]==0) n--;
        else break;
    for(i=n-1; i>=0; i--)
        cout<<a[i];
}
NumarMare::~NumarMare() {}
int main()
{
    char x[10000],y[10000];
    cout<<"Number 1: ";
    cin>>x;
    if(VerifValid(x)!=1)
    {
        cout<<"Invalid number!";
        return 0;
    }
    cout<<"Number 2: ";
    cin>>y;
    if(VerifValid(y)!=1)
    {
        cout<<"Invalid number!";
        return 0;
    }
    //=======================================================================
    NumarMare nr1(x);
    NumarMare nr2(y);
    system("CLS");
    cout<<"Numbers:"<<endl;
    if(nr1.GetSemn()==1) cout<<"+";
    else cout<<"-";
    nr1.AfisareListaSD();
    cout<<" having length of "<<nr1.GetLungime()<<".\n";
    if(nr2.GetSemn()==1) cout<<"+";
    else cout<<"-";
    nr2.AfisareListaSD();
    cout<<" having length of "<<nr2.GetLungime()<<".\n";
    cout<<"\n======================================================\n";
    cout<<"Absolute maximum: ";
    (nr1>nr2).AfisareListaSD();
    cout<<endl;
    if(nr1.GetSemn()==nr2.GetSemn())
    {
        if(nr1.GetSemn()<0)
            cout<<"Diference: -";
        else cout<<"Sum: +";
        (nr1 + nr2).AfisareListaSD();
    }
    else
    {
        if(nr1.GetSemn()<0)
            cout<<"Diference: ";
        else cout<<"Diference: ";
        nr1 - nr2;
    }
    cout<<"\n======================================================\n";
    cout<<"MihailProductions.com 03.2016\n";
    return 0;
}
