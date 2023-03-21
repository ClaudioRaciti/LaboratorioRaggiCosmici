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


void fitAccDist(){

float dist [] = {40.4 , 30. , 24.9 , 19.7 , 15. };
float err_dist[] = {0.14,0.14,0.14,0.14,0.14};
float err_rate_normalized[] = {0.0222,0.0230,0.0510,0.0754,0.0791};
float rate_normalized[] = {0.677,1.,1.573,2.418,3.094};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("Distanza","Rate normalizzato(d)",200,10,600,400);
cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(5,dist,rate_normalized,err_dist,err_rate_normalized);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("Rate normalizzato(d)");
gG1f->GetXaxis()->SetTitle("d");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");
}

