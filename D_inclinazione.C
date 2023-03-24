#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;

void D_inclinazione(){

float a[5]={0,15,30,45,60}; // angolo di inclinazione dei rilevatori dalla verticale
float t[5]={760,794,636,837,1337}; // tempo di acquisizione dei conteggi
float Cont[5]={307,270,168,157,105}; //numero di conteggi effettuati

float sa[5]={1,1,1,1,1}; //incertezza sull'angolo

float sCont[5];
for(int j=0;j<5;j++){
sCont[j]=sqrt(Cont[j]);
}

float r[5] , sr[5]; // rateo misurato
for(int j=0;j<5;j++){
r[j]=Cont[j]/t[j];
sr[j]=sCont[j]/t[j];
cout<<"il rateo a: "<<a[j]<<" gradi vale: "<<r[j]<<"±"<<sr[j]<<endl;
}
cout<<endl;
cout<<endl;
cout<<endl;

float t0=409, Cont0=15; //conteggi con rilevatore orizzontale
float r0=Cont0/t0;
float sr0=pow(Cont0,0.5)/t0;

cout<<"il rateo a 90 gradi vale: "<<r0<<"±"<<sr0<<endl;

cout<<endl;
cout<<endl;
cout<<endl;

cout<<"tolto il rateo di fondo si ha che:"<<endl;
float R[5] , sR[5];
for (int j=0; j<5;j++){

R[j]=r[j]-r0;
sR[j]=sqrt(sr[j]*sr[j]+sr0*sr0);

cout<<"il rateo a: "<<a[j]<<" gradi vale: "<<R[j]<<"±"<<sR[j]<<endl;
}


TCanvas *grafico = new TCanvas("grafico","rateo in funzione dell'angolo",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(5,a,R,sa,sR);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("rateo - angolo");
punti->GetXaxis()->SetTitle("anoglo [deg]");
punti->GetYaxis()->SetTitle("rateo [conteggi/s]");
punti->Draw("AP");



TF1 *funz1 = new TF1("funz1","[0]*pow(cos(x*pi/180),[1])+[2]",0,90);
  
  funz1->SetParameter(0,0.4);
  funz1->SetParameter(1,2);
  
  funz1->SetLineColor(4); // Blu
  
  punti->Fit(funz1,"RM+");
  cout << "Chi^2: " << funz1->GetChisquare() << ", gradi di libertà: " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;







}
