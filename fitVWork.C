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


void fitVWork(){

float HV_work [] = {1949 , 2000 , 2049 , 2100 , 2149 , 2199 , 2250 , 2300 , 2350};
float err_HV_work[] = {24.49 , 25 , 25.49 , 26 , 26.49 , 26.99 , 27.5 , 28 , 28.5};
float err_eff[] = {0 , 0.013457659 , 0.027367159 , 0.038573104 , 0.031176257 , 0.018041619 , 0.013457659 , 0.014401703 , 0.010825957};
float eff[] = {0 , 0.03626943 , 0.163934426 , 0.494047619 , 0.789473684 , 0.93 , 0.96373057 , 0.964071856 , 0.975490196};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("V_work","efficienza(V)",200,10,600,400);
cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(9,HV_work,eff,err_HV_work,err_eff);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("efficienza(V)");
gG1f->GetXaxis()->SetTitle("log(V)");
gG1f->GetYaxis()->SetTitle("eff");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0]/(1+exp(([1]-x)/[2])) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1","[0]/(1+exp(([1]-x)/[2]))",0,250000);

funz1->SetParameter(0,0.95);
funz1->SetParameter(1,2100.);
funz1->SetParameter(2,30.);
funz1->SetParLimits(0,0.,1.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

}

