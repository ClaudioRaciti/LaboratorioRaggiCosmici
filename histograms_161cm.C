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

void histograms_161cm() {
  string input = "distanza_161cm.mca";
  // file di test contiene:cm
  //    > more test.txt
  // 4
  // 5
  // 6
  static const int nBins = 512;
  static const int usedBins = 512;
  int y[usedBins],ally[nBins];
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
  myHisto->Rebin(8);
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
  TF1 *g1 = new TF1("g1","gaus",260,420);

  g1->SetLineColor(1);
  myHisto->Fit(g1,"R+");

  cout << "Chi^2:" << g1->GetChisquare() << ", number of DoF: " << g1->GetNDF() << " (Probability: " << g1->GetProb() << ")." << endl;
  
  TH1F *completeHisto = new TH1F("completeHisto","completeHisto",nBins,1,nBins);
  for (int j=0;j<nBins;j++) {
    completeHisto->SetBinContent(j+1,ally[j]);
  }
  // come si accorpano gli eventi in bin adiacenti
  completeHisto->Rebin(4);
  // ora completeHisto ha nBins/4 classi e ognuna contiene gli eventi di 4 adiacenti

  TCanvas *cX1 = new TCanvas("cx1","cx1",200,10,600,400);
  cX1->cd();

  completeHisto->GetYaxis()->SetRangeUser(0,completeHisto->GetMaximum()+1.);
  completeHisto->SetStats(kFALSE);
  completeHisto->GetXaxis()->SetTitle("bin [CHN]");
  completeHisto->GetYaxis()->SetTitle("Conteggi");


  completeHisto->SetLineColor(2);
  completeHisto->SetLineWidth(2);
  completeHisto->Draw();
}
