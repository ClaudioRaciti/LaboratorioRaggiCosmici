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


void fitVThr(){

float V_threshold [] = {34.9 , 50.6 , 100.4 , 150.3 , 249.9 , 350.2 , 450.5};
float err_V_threshold[] = {0.0849 , 0.1006 , 0.6004 , 0.6503 , 0.7499 , 0.8502 , 0.9505};
float err_eff[] = {0.01383917 , 0.016743905 , 0.023719606 , 0.027149027 , 0.02722907 , 0.024821475 , 0.016178917};
float eff[] = {0.0849 , 0.1006 , 0.6004 , 0.6503 , 0.7499 , 0.8502 , 0.9505};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("V_work","efficienza(V)",200,10,600,400);
cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(7,V_threshold,eff,err_V_threshold,err_eff);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("efficienza(V)");
gG1f->GetXaxis()->SetTitle("log(V)");
gG1f->GetYaxis()->SetTitle("eff");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0]/(1+exp((x-[1])/[2])) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1","[0]/(1+exp(([1]-x)/[2]))",0,250000);

funz1->SetParameter(0,0.95);
funz1->SetParameter(1,100.);
funz1->SetParameter(2,300.);
funz1->SetParLimits(0,0.,1.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

}

