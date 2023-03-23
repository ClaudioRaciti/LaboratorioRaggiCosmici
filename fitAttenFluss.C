#include <iostream>           // ci serve per stampare a video il testo
//#include <TGraphErrors.h>     // ci serve per istanziare grafici
//#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
//#include <TCanvas.h>          // ci serve per disegnare i grafici
//#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;


void fitAttenFluss(){

float dist [] = {0.,0.86,0.86+0.53+0.54+0.39,0.86+0.53+0.54+0.39+0.36+0.34,0.86+0.53+0.54+0.39+0.36+0.34+0.46+0.22};
float err_dist[] = {0.01,0.01,0.02,0.0244,0.0282};
float err_rate[] = {0.0249,0.0321,0.0225,0.0252,0.0186};
float rate[] = {0.367,0.350,0.215,0.254,0.191};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("V_work","rateicienza(V)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(5,dist,rate,err_dist,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("rateicienza(V)");
gG1f->GetXaxis()->SetTitle("d");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0]*exp(-[1]*x) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1"," [0]*exp(-[1]*x)",-0.1,250000);

funz1->SetParameter(0,0.4);
funz1->SetParameter(1,0.5);
funz1->SetParLimits(0,0.,190.);
// funz1->SetParLimits(2,70.,76.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

float alfa = funz1->GetParameter(1);
float err_alfa = funz1->GetParError(1);

cout<<"\nEnergia media muoni:"<< 6.4e-3/(2*alfa*1e-2)+2<<"+-"<< 6.4e-3/(2*pow(alfa*1e-2,2))*err_alfa*1e-2<<"GeV"<<endl;

}

