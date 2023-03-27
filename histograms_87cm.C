#include <iostream>
#include <fstream>
#include <math.h>

#include "TH1F.h"
#include "TF1.h"
#include "TLine.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"

void histograms_87cm() {
  string input = "distanza_87cm.mca";
  // file di test contiene:cm
  //    > more test.txt
  // 4
  // 5
  // 6
  static const int nBins = 512;
  static const int usedBins = 512;
  int y[usedBins];
  int ally[nBins];
  Double_t par[6]={324,290,8,241,295,20};
  ifstream parInput(input.c_str());
  int i = 0;

  if (parInput.is_open()) {
    while ( parInput.good() ) {
      parInput >> ally[i];
      cout << i << " " << ally[i] << endl;
      i++;   if (i == nBins) break;
    }
    parInput.close();
  }

  for (i = 0; i<usedBins; i++)
    y[i] = ally[0+i];

  // come si riempie un TH1
  TH1F *myHisto = new TH1F("myHisto","myHisto",usedBins,1,usedBins);
  for (int j=0;j<usedBins;j++) {
    myHisto->SetBinContent(j+1,y[j]);
  }
  // come si accorpano gli eventi in bin adiacenti
  myHisto->Rebin(4);
  // ora myHisto ha nBins/4 classi e ognuna contiene gli eventi di 4 adiacenti

  TCanvas *cX = new TCanvas("x","x",200,10,600,400);
  cX->cd();

  myHisto->GetYaxis()->SetRangeUser(0,myHisto->GetMaximum()+1.);
  myHisto->SetStats(kFALSE);
  myHisto->GetXaxis()->SetTitle("bin [CHN]");
  myHisto->GetYaxis()->SetTitle("Conteggi");


  myHisto->SetLineColor(2);
  myHisto->SetLineWidth(2);
  myHisto->Draw();
  //myHisto->Fit("gaus","ME");
  // myHisto->Fit("gaus","ME");
  TF1 *g1 = new TF1("g1","gaus",240,375);
  //TF1 *g2 = new TF1("g2","gaus",220,430);

  TF1 *g3 = new TF1("g3","gaus(0)+gaus(3)",200,450);
  g3-> SetParameters(par);
  g1->SetLineColor(1);
  g3->SetLineColor(6);

  myHisto->Fit(g1,"R+");
  
  myHisto->Fit(g3,"R+");


  cout << "Chi^2:" << g1->GetChisquare() << ", number of DoF: " << g1->GetNDF() << " (Probability: " << g1->GetProb() << ")." << endl;
  cout << "Chi^2:" << g3->GetChisquare() << ", number of DoF: " << g3->GetNDF() << " (Probability: " << g3->GetProb() << ")." << endl;
}
