#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;


void tempoVolo() {
    float p=1.57083;
    float err_p=0.5084;
    float m=0.1001;
    float err_m=0.00243;
    // float delta_t[] = {m*291.64+p-30,m*304.228+p-30,m*316.847+p-30,m*340.999+p-30}; //occhio agli errori
    // float err_delta_t[] = {pow(pow(err_p,2)+pow(err_m*291.64,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*304.228,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*316.847,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*340.999,2)+0.25,0.5)};
    float delta_t[] = {m*292.58+p-30,m*308.179+p-30,m*317.74+p-30,m*340.999+p-30}; //occhio agli errori
    float err_delta_t[] = {pow(pow(err_p,2)+pow(err_m*292.58,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*308.179,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*317.74,2)+0.25,0.5),pow(pow(err_p,2)+pow(err_m*340.999,2)+0.25,0.5)};
    float dist[] = {12.2,63.5,87.5,161};
    float err_dist[] = {0.1,0.1,0.1,0.1};

    //float err_CHN[] = {0.289}


    TCanvas *grafico = new TCanvas("grafico","tempo di volo",200,10,600,400);
    grafico->SetFillColor(0);
    grafico->cd();
    TGraphErrors *punti = new TGraphErrors(4,dist,delta_t,err_dist,err_delta_t);
    punti->SetMarkerSize(0.7);
    punti->SetMarkerStyle(21);
    punti->SetTitle("tempo di volo");
    punti->GetXaxis()->SetTitle("distanze scintillatori [cm]");
    punti->GetYaxis()->SetTitle("tempi [ns]");
    punti->Draw("AP");





    TF1 *funz1 = new TF1("funz1","[1]*x+[0]",10,180);

	funz1->SetParameter(0,0.);
	funz1->SetParameter(1,0.03);

    funz1->SetLineColor(3);


    punti->Fit(funz1,"RM+");
    cout << "X^2: " << funz1->GetChisquare() << ", gradi di libert�: " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;
    cout << "velocita' della luce: [" << 1./funz1->GetParameter(1)*(pow(10,-2)/pow(10,-9)) << " +- " << pow(1./funz1->GetParameter(1),2)*funz1->GetParError(1)*(pow(10,-2)/pow(10,-9)) << "] m/s " << endl;
    cout << "test Z: " << ((1./funz1->GetParameter(1)*(pow(10,-2)/pow(10,-9)))-299792458.)/(pow(1./funz1->GetParameter(1),2)*funz1->GetParError(1)*(pow(10,-2)/pow(10,-9)));



}
