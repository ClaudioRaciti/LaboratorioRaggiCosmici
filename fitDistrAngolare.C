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


void fitDistrAngolare(){

float angolo [] = {0.,15.,30.,45.,60.};
float err_angolo[] = {1.,1.,1.,1.,1.};
float err_rate[] = {0.0433 , 0.0421 , 0.0419 , 0.0396 , 0.0375};
float rate[] = {0.3673,0.3034,0.2275,0.1509,0.0418};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("cos $\th$","rate",200,10,600,400);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(5,angolo,rate,err_angolo,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("rate");
gG1f->GetXaxis()->SetTitle("cos($\th$)");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0] * pow(cos(x),[1]) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1","[0] * pow(cos(x*3.141592/180),[1])",-0.1,250000);

funz1->SetParameter(0,0.5);
funz1->SetParameter(1,2.);
funz1->SetParLimits(0,0.,1.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

}

