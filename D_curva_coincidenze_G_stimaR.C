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

cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;







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

cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;



cout<<"fit della zona destra con la formula del passa alto di covarelli"<<endl;
TF1 *funz1 = new TF1("funz1","[0]/(1+exp((x-[1])/[2]))+[3]",14,68);// 2.9361 sarebbe il rate di fondo

  funz1->SetParameter(0,18);
  funz1->SetParameter(1,18);
  funz1->SetParameter(2,3);
  funz1->SetParameter(3,1);
  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;
  
    cout<<"l'ascissa di metà altezza nella parte destra vale: "<<funz1->GetParameter(1)<<endl;



cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;


 cout<<"fit della zona sinistra con la formula del passa basso di covarelli"<<endl;
TF1 *funz3 = new TF1("funz3","[0]/(1+exp(([1]-x)/[2]))+[3]",-80,10);

  funz3->SetParameter(0,16);
  funz3->SetParameter(1,-28);
  funz3->SetParameter(2,3);		
  funz3->SetParameter(3,1);
  funz3->SetLineColor(1); 
  

  punti->Fit(funz3,"RM+");
  cout << "X^2: " << funz3->GetChisquare() << ", gradi di libertà: " << funz3->GetNDF() << " (p-value: " << funz3->GetProb() << ")."<<endl;
  
  cout<<"l'ascissa di metà altezza nella parte sinistra vale: "<<funz3->GetParameter(1)<<endl;
  




cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;





cout<<"fit della parte sinistra del plateau con una retta orizzontale"<<endl;
TF1 *funz2 = new TF1("funz2","[0]",-28,13);

  funz2->SetParameter(0,16);

  punti->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di libertà: " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;



cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;




  cout<<"stima del flusso di muoni dalla parte sinistra"<<endl;
  float Rmis=funz3->GetParameter(0);
  float sRmis=funz3->GetParError(0);
  float ε=0.90522;
  float err_ε=0.01674;
  float etaG=0.419;
  float err_etaG=0.024;
  float S=0.2;
  float rate_def=(((Rmis)/(ε*etaG)))/S; //sono 0.2 m^2 ovvero l'area della coppia degli scintillatori

  
  float δRmis=(1/(ε*etaG*S))*sRmis;
  float δε=((Rmis)/(etaG*S*ε*ε))*err_ε;
  float δetaG=((Rmis)/(ε*S*etaG*etaG))*err_etaG;
  
  
   float err_rate_def=sqrt(pow(δRmis,2)+pow(δε,2)+pow(δetaG,2));

  cout << endl <<"il rate al livello del mare per unita' di superficie vale: (" << rate_def << " +- " << err_rate_def<<") conteggi/(m^2*s)"<< endl << "guarda lascia perdere, vedi se almeno con test Z e' compatibile: " << (180-rate_def)/err_rate_def<< endl;
  
  
  cout<<endl;
  cout<<endl;
  cout<<endl;
  cout<<endl;
  cout<<endl;
  cout<<endl;
  
  
  
  cout<<"stima del flusso di muoni dalla parte destra"<<endl;
  float Rmis_d=funz1->GetParameter(0);
  float sRmis_d=funz1->GetParError(0);

  
  float rate_def_d=(((Rmis_d)/(ε*etaG)))/S; 

  
  float δRmis_d=(1/(ε*etaG*S))*sRmis_d;
  float δε_d=((Rmis_d)/(etaG*S*ε*ε))*err_ε;
  float δetaG_d=((Rmis_d)/(ε*S*etaG*etaG))*err_etaG;
  
  
   float err_rate_def_d=sqrt(pow(δRmis_d,2)+pow(δε_d,2)+pow(δetaG_d,2));

  cout << endl <<"il rate al livello del mare per unita' di superficie vale: (" << rate_def_d << " +- " << err_rate_def_d<<") conteggi/(m^2*s)"<< endl << "guarda lascia perdere, vedi se almeno con test Z e' compatibile: " << (180-rate_def_d)/err_rate_def_d<< endl;
  
  
  
  
  


}
