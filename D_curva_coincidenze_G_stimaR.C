#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;


void D_curva_coincidenze_G_stimaR()
{

static const int n_misure=36;

// ritardi in nanosecondi
float Rit[]={0,3,6,9,12,15,18,21,24,27,28.5,30,33,37,41,49,65,-3,-6,-9,-12,-15,-18,-21,-24,-27,-30,-33,-37,-41,-49,-65,28,29.5,26,57.5};

// tempo di acquisizione in secondi
float t[]={100,100,100,100,100,100,150,150,150,150,200,150,200,200,200,200,200,100,100,100,100,100,100,100,100,150,150,200,200,200,200,200,200,200,200,200};
float Coinc[]={1629,1573,1635,1543,1667,1764,2697,2687,2633,2345,2390,1156,1051,987,932,918,825,1562,1591,1616,1532,1567,1657,1558,1611,2317,1924,575,173,144,131,132,2754,2239,3234,867};

float sRit[n_misure] ;
float sCoinc[n_misure];

for (int j=0;j<n_misure;j++){
sRit[j]=0.5;
sCoinc[j]=sqrt(Coinc[j]);
}

float r[n_misure];
float sr[n_misure]; // rateo di conteggio e rispettiva incertezza

for (int j=0;j<n_misure;j++){
r[j]=Coinc[j]/t[j];
sr[j]=sCoinc[j]/t[j];
}

//stampo i risultati

for (int j=0;j<n_misure;j++){
cout<<"ritardo: "<<Rit[j]<<"ns \t rate: "<<r[j]<<"+-"<<sr[j]<<endl;
}







TCanvas *grafico = new TCanvas("grafico","curva delle coincidene",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(n_misure,Rit,r,sRit,sr);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("curva di coincidenze");
punti->GetXaxis()->SetTitle("ritardo [ns]");
punti->GetYaxis()->SetTitle("rate [conteggi/s]");
punti->Draw("AP");



// misura del fondo (rumore) nella coda destra

float tf=9999; //tempo di rilevazione del fondo in secondi
float Ritf=75; // ritardo impostato in nanosecondi
float Coincf=29361; //conteggi rivelati
float rf=Coincf/tf ;
float srf=sqrt(Coincf)/tf;

cout<<"misura del rate di fondo \n"<<"ritardo: "<<Ritf<<"ns \t rate: "<<rf<<"±"<<srf<<endl;



// fit della zona destra con la formula del passa alto di covarelli
TF1 *funz1 = new TF1("funz1","[0]/(1+exp((x-[1])/[2]))+2.9361+[3]",14,68);// 2.9361 sarebbe il rate di fondo

  funz1->SetParameter(0,18);
  funz1->SetParameter(1,18);
  funz1->SetParameter(2,3);
  funz1->SetParameter(3,1);
  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;


//fit della parte sinistra del plateau con una retta orizzontale
TF1 *funz2 = new TF1("funz2","[0]",-28,13);

  funz2->SetParameter(0,16);

  punti->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di libertà: " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;

  float rate=funz2->GetParameter(0);
  float err_rate=funz2->GetParError(0);
  float rate_acc=rf; //0
  float err_rate_acc=srf;//0
  float epsi=0.90522;
  float err_epsi=0.01674;
  float etaG=0.419;
  float err_etaG=0.024;
  float rate_def=(((rate-rate_acc)/(epsi*etaG)))/0.2;
  float err_rate_def=pow(pow((1/epsi*etaG)*err_rate,2) + pow((1/epsi*etaG)*err_rate_acc,2) + pow(((rate-rate_acc)/epsi*epsi*etaG)*err_epsi,2) + pow(((rate-rate_acc)/epsi*etaG*etaG)*err_etaG,2),0.5);
  float err_rate_def_sovrastm=(1/epsi*etaG)*err_rate + (1/epsi*etaG)*err_rate_acc + ((rate-rate_acc)/epsi*epsi*etaG)*err_epsi + ((rate-rate_acc)/epsi*etaG*etaG)*err_etaG;
  cout << endl <<"il rate al livello del mare per unita' di lunghezza vale: " << rate_def << " +- " << err_rate_def_sovrastm << endl << "guarda lascia perdere, vedi se almeno con test Z e' compatibile: " << (180-rate_def)/err_rate_def_sovrastm << endl;


}



