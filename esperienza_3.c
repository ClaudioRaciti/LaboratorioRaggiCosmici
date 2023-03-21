#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <cmath>

using namespace std;


// Corpo del programma. La funzione qui sotto deve avere lo stesso nome del file .C
void esperienza_3()
{

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


cout << "\n\n --- Ipotesi  x/(pow(pow(x,2) + [0],0.5)) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1","x/(pow(pow(x,2) + [0],0.5))",0,250000);
gG1f->Fit(funz1,"RM+");
funz1->SetParameter(0,29484900);
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

cout << "\n\n --- Ipotesi  [0]/(1+exp(([1]-x)/[2])) --- \n" <<endl;

TF1 *funz1 = new TF1("funz1","[0]/(1+exp(([1]-x)/[2]))",0,250000);
gG1f->Fit(funz1,"RM+");
funz1->SetParameter(0,1);
funz1->SetParameter(1,1);
funz1->SetParameter(2,1);
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
}
