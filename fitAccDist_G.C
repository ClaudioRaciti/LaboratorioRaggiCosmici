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


void fitAccDist_G(){

float dist [] = {15. , 19.7 , 24.9 , 30. , 40.4};
float err_dist[] = {0.14,0.14,0.14,0.14,0.14};
float err_rate_normalized[] = {0.21679 , 0.206795 , 0.141299 , 0.067861 , 0.06565};
float rate_normalized[] = {3.3036 ,2.5595, 1.6297, 1., 0.644};
float G_30= 0.131;
float err_G_30=0.011;
float G_norm[]={0.355/G_30,0.249/G_30,0.175/G_30,0.131/G_30,0.083/G_30};
float err_G_norm[]={0.015/G_30, 0.014/G_30 , 0.012/G_30 , err_G_30/G_30, 0.0087/G_30};
/*err_15=+/- 0.015;
err_19= +/- 0.014;
err_24=+/- 0.012;
err_40= +/- 0.0087;*/
//Grafico passa alto
TCanvas *cG1f = new TCanvas("Rate","Rate normalizzato(d)",200,10,600,400);
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

TF1 *funz1 = new TF1("funz1"," [0]*exp(-[1]*x)",-0.1,250000);

funz1->SetParameter(0,3.);
funz1->SetParameter(1,0.5);
//funz1->SetParLimits(0,0.,190.);
// funz1->SetParLimits(2,70.,76.);

/*TF1 *funz2 = new TF1("funz2","[0]*x+[1]",-0.1,250000);

funz2->SetParameter(0,-3.);
funz2->SetParameter(1,3);
//funz2->SetParLimits(0,0.,190.);
// funz2->SetParLimits(2,70.,76.);*/


gG1f->Fit(funz1,"RM+");
cout << endl << "tried: [0]*exp(-[1]*x)" << endl;
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
float W1= funz1->GetChisquare()/funz1->GetNDF();
/*gG1f->Fit(funz2,"RM+");
cout << endl << "tried: [0]*x+[1]" << endl;
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
*/

TCanvas *cG2f = new TCanvas("Accettanza","Accettanza normalizzata G(d)",400,10,600,400);
cG2f->SetLogx(1);
cG2f->SetFillColor(0);
cG2f->cd();
TGraphErrors *gG2f = new TGraphErrors(5,dist,G_norm,err_dist,err_G_norm);
gG2f->SetMarkerSize(0.6);
gG2f->SetMarkerStyle(21);
gG2f->SetTitle("Accettanza normalizzata G(d)");
gG2f->GetXaxis()->SetTitle("d");
gG2f->GetYaxis()->SetTitle("G");
gG2f->Draw("AP");

gG2f->Fit(funz1,"RM+");
cout << endl << "tried: [0]*exp(-[1]*x)" << endl;
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
float W2= funz1->GetChisquare()/funz1->GetNDF();
/*gG1f->Fit(funz2,"RM+");
cout << endl << "tried: [0]*x+[1]" << endl;
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;

*/

//test fisher
float t_c=9.27;
cout << 1/t_c << " < " << W1/W2 << " < " << t_c << " ? " << " I due andamenti sono compatibili " << endl;
}

