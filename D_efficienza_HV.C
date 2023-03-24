#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;

	
void D_efficienza_HV(){
float V[]={2000,2049,2100,2149,2199,2250,2300,2350};
float triple[]={7,30,83,135,186,186,161,199};
float doppie[]={193,183,168,171,200,193,167,204};

float Eff[8];

for (int j=0;j<8;j++){
	Eff[j]=triple[j]/doppie[j];
	}
	
float sV[8] , sEff[8];

for(int j=0;j<8;j++){
	sV[j]=0.01*V[j]+5.;
	sEff[j]=pow(Eff[j]*(1-Eff[j])/doppie[j],0.5);
	}
	

for(int j=0;j<8;j++){
	cout<<V[j]<<"±"<<sV[j]<<"\t"<<Eff[j]<<"±"<<sEff[j]<<endl;
	}
	
TCanvas *grafico = new TCanvas("grafico" , "efficienza/HV" , 200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(8,V,Eff,sV,sEff);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("Efficienza/tensione di alimentazione");
punti->GetXaxis()->SetTitle("tensione [v]");
punti->GetYaxis()->SetTitle("efficienza");
punti->Draw("AP");
	
	
TF1 *funz1 = new TF1("funz1" , "(x-[1])/pow(pow((x-[1]),2)+pow([0]-[1],2),0.5)",0,5000); //per usare la formula del passa alto di Bellan ho dovuto traslare a destra tutta la funzione di un certo valore identificato dal parametro 1. Nel passa alto la funzione ha lo stesso segno dell'argomento; traslandola si ha che diventa negativa anche per argomenti positivi... il fatto che nel grafico all'inizio assuma valori negativi è dovuto solamente a questo.
funz1->SetParLimits(0,0,5000);
funz1->SetLineColor(5);
punti->Fit(funz1,"RM+");
cout<<"χ^2: "<<funz1->GetChisquare()<<"\t gradi di libertà: "<<funz1->GetNDF()<<"\t p-value: "<<funz1->GetProb()<<endl;
cout<<"la tensione di taglio vale: "<<funz1->GetParameter(0)<<"V"<<endl;
	
TF1 *funz2 = new TF1("funz2" , "[0]/(1+exp(([1]-x)/[2]))",0,5000);
// l'efficienza deve valere al più 1 quindi il parametro 0 lo si inizializza a 1 
//il parametro 1 trasla semplicemente la funzione, lo inizializzo a 2000 perchè lo scintillatore inizia a funzionare in quella zona
//il parametro 2 dà un'idea dello spessore della zona in cui lo scintillatore passa da essere "spento" a essere "acceso" se non si iniializza root caccia fuori un 5 miliardi e direi che non va bene.
funz2->SetParameter(0,1);
funz2->SetParameter(1,2000);
funz2->SetParameter(2,30);
funz2->SetLineColor(6);
punti->Fit(funz2,"RM+");
cout<<"χ^2: "<<funz2->GetChisquare()<<"\t gradi di libertà: "<<funz2->GetNDF()<<"\t p-value: "<<funz2->GetProb()<<endl;

	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	






