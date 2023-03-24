#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;

float incertezza_volmetro(float );

float incertezza_volmetro(float V){
	if (V<1)		return V*0.001+5e-4;
	else if(V<10) 		return V*0.001+5e-3;
	else 			return V*0.001+5e-2;
}





	
void D_efficienza_Vtrh(){
float Vtrh[]={34.9/1000,50.6/1000,100.4/1000,150.3/1000,249.9/1000,350.2/1000,450.5/1000};
float triple[]={286,277,232,193,89,61,24};
float doppie[]={305,306,293,329,288,278,290};

float Eff[7];

for (int j=0;j<7;j++){
	Eff[j]=triple[j]/doppie[j];
	}
	
float sVtrh[7] , sEff[7];

for(int j=0;j<7;j++){
	sVtrh[j]=incertezza_volmetro(10*Vtrh[j])/10;
	sEff[j]=pow(Eff[j]*(1-Eff[j])/doppie[j],0.5);
	}
	

for(int j=0;j<7;j++){
	cout<<Vtrh[j]<<"±"<<sVtrh[j]<<"\t"<<Eff[j]<<"±"<<sEff[j]<<endl;
	}
	
TCanvas *grafico = new TCanvas("grafico" , "efficienza - Vtrh" , 200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(7,Vtrh,Eff,sVtrh,sEff);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("Efficienza/tensione di soglia");
punti->GetXaxis()->SetTitle("tensione [V]");
punti->GetYaxis()->SetTitle("efficienza");
punti->Draw("AP");
	
	
TF1 *funz1 = new TF1("funz1" , "[0]/pow(pow((x),2)+pow([1],2),0.5)", 0 , 0.5); 
funz1->SetParLimits(0,0,5000);
funz1->SetLineColor(5);
punti->Fit(funz1,"RM+");
cout<<"χ^2: "<<funz1->GetChisquare()<<"\t gradi di libertà: "<<funz1->GetNDF()<<"\t p-value: "<<funz1->GetProb()<<endl;
cout<<"la tensione di taglio vale: "<<funz1->GetParameter(0)<<"V"<<endl;
	
TF1 *funz2 = new TF1("funz2" , "[0]/(1+exp((x-[1])/[2]))", 0 , 0.5);
// l'efficienza deve valere al più 1 quindi il parametro 0 lo si inizializza a 1 
//il parametro 1 trasla semplicemente la funzione, lo inizializzo a 2000 perchè lo scintillatore inizia a funzionare in quella zona
//il parametro 2 dà un'idea dello spessore della zona in cui lo scintillatore passa da essere "spento" a essere "acceso" se non si iniializza root caccia fuori un 5 miliardi e direi che non va bene.
funz2->SetParameter(0,1);
funz2->SetParameter(1,0);
funz2->SetParameter(2,3);
funz2->SetLineColor(6);
punti->Fit(funz2,"RM+");
cout<<"χ^2: "<<funz2->GetChisquare()<<"\t gradi di libertà: "<<funz2->GetNDF()<<"\t p-value: "<<funz2->GetProb()<<endl;

	
cout<<incertezza_volmetro(0.350);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	






