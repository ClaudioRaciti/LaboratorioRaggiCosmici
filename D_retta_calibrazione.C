#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;


void D_retta_calibrazione() 
{


float CH[11]={298,279,259,239.69,219,200,179,160,138.01,119.01,99};
float sCH[11]={1,1,1,1.4,1,1,1,1,1.0032,1.0035,1};// in teoria con un certo ritardo avrebbe dovuto accendersi sempre lo stesso canale e quindi la dispersione sarebbe dovuta sempre essere 1 canale. Tuttavia in un paio di casi un paio di segnali sono finiti in altri canali quindi la dispersione è leggermente maggiore di 1

float t[11]={31.5,29.5,27.5,25.5,23.5,21.5,19.5,17.5,15.5,13.5,11.5}; // in nanosecondi
float st[11];
for (int j=0;j<11;j++){
st[j]=0.5;//i moduli di delay avevano una risoluzione di sensibilità di 0.5 ns
}




TCanvas *grafico = new TCanvas("grafico","retta di calibrazione",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(11,CH,t,sCH,st);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("retta di calibrazione");
punti->GetYaxis()->SetTitle("ritardo [ns]");
punti->GetXaxis()->SetTitle("canali");
punti->Draw("AP");





TF1 *funz1 = new TF1("funz1","[1]*x+[0]",0,400);

	funz1->SetParameter(0,-15);
	funz1->SetParameter(1,10);

  funz1->SetLineColor(3); 
  

  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di libertà: " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;


}


	
