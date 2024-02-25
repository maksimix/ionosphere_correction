using namespace std;
#include "mytrek.h"
#include <iostream>
#include <iomanip>

extern MyTrek *mytrek_ext;

MyTrek::MyTrek(double f, double Fh, double H[3], double Dh[3][3], double Dh2[3][3][3], double Delt, double Eps, double Ep, double Ep1) :
               fr(f), fh(Fh), delt(Delt), eps(Eps), ep(Ep), ep1(Ep1)
{
    fr2=f*f;
    u1=fh/fr;
    u=u1*u1;
    e=.0625;
    e=e*eps;
    pointTr=0;
    for(int i=0; i<3; i++)
    {
        h[i]=H[i];
        for(int j=0; j<3; j++)
        {
            dh[i][j]=Dh[i][j];
            for(int k=0; k<3; k++)
                dh2[i][j][k]=Dh2[i][j][k];
        }
    }
    iri_3dbase=0;
    iri_3dbase2=0;
    //copy_iri_model();
}


MyTrek::MyTrek(double Delt, double Eps, double Ep, double Ep1) :
    delt(Delt), eps(Eps), ep(Ep), ep1(Ep1)
{

    e=.0625;
    e=e*eps;
    pointTr=0;
    fr=fr2=1.;
    iri_3dbase=0;
    iri_3dbase2=0;   
    //copy_iri_model();
}

void MyTrek::copy_iri_model()
{
    //cout<<endl<<"1 new IRI_3D"<<flush;
    iri_3dbase =new IRI_3D(*::iri_3dbase);
    //cout<<endl<<"2 new IRI_3D"<<flush;
    iri_3dbase2=new IRI_3D(*::iri_3dbase2);    
    //cout<<endl<<"3 new IRI_3D"<<flush;
    //iri_3dbase =::iri_3dbase;
    //iri_3dbase2=::iri_3dbase2;
}

MyTrek::~MyTrek()
{
	if(iri_3dbase)
	{
		//cout<<endl<<"1 delete IRI_3D"<<flush;
		delete iri_3dbase;
		//cout<<endl<<"2 delete IRI_3D"<<flush;
		iri_3dbase=0;
	}
	if (iri_3dbase2)
	{
		//cout<<endl<<"1 delete IRI_3D2"<<flush;
		delete iri_3dbase2;
		//cout<<endl<<"2 delete IRI_3D2"<<flush;
		iri_3dbase2=0;
	}
	//cout<<endl<<"~MyTrek()"<<flush;
}
