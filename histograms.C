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

void histograms() {
  string input = "distanza_minima.mca";
  // file di test contiene:
  //    > more test.txt
  // 4
  // 5
  // 6
  static const int nBins = 512;
  int y[nBins];
  ifstream parInput(input.c_str());
  int i = 0;

  if (parInput.is_open()) {
    while ( parInput.good() ) {
      parInput >> y[i];
      cout << i << " " << y[i] << endl;
      i++;   if (i == nBins) break;
    }
    parInput.close();
  }

  // come si riempie un TH1
  TH1F *myHisto = new TH1F("myHisto","myHisto",nBins,1,nBins);
  for (int j=0;j<nBins;j++) {
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
  myHisto->Fit("gaus","ME");

  TF1 *fitA = myHisto->GetFunction("gaus");
  fitA->SetLineColor(1);

  cout << "Chi^2:" << fitA->GetChisquare() << ", number of DoF: " << fitA->GetNDF() << " (Probability: " << fitA->GetProb() << ")." << endl;

}
