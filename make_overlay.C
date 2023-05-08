#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TF1.h"
#include "TString.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include "TMultiGraph.h"
#include "TMath.h"
#include <sys/stat.h>
#include <vector>
#include <string>
#include "settings.h"
//#include "decorations.h"
using namespace std;

/*
These are all the libraries that we need.
Now, let's call a 'Main' function.
The arguments to this main function are given in the python driver script.
*/

void make_overlay(TString channelname, TString plotname, TString plottitle, TString ofname){
  //TString channelname = "3L_onZ";
  //TString plotname = "HTlep";
  
  cout<<"\n__________________________  OVERLAY MAKER ____________________________"<<endl;
  cout<<"Making a plot for '"<<plotname<<"' in the '"<<channelname<<"' channel"<<endl;

  //Global settings:
  float binw = 5; //Set how many bins to combine. (default value =1)

  //Opening the root files:
  TFile *file100 = new TFile("inputs/hst_vllsing100_8TeV_200k.root");
  TFile *file150 = new TFile("inputs/hst_vllsing150_8TeV_200k.root");
  TFile *file200 = new TFile("inputs/hst_vllsing200_8TeV_200k.root");
  TFile *file250 = new TFile("inputs/hst_vllsing250_8TeV_200k.root");
  cout<<"The files are loaded sucessfully!"<<endl;

  //Loading the histogram from each file:
  TString plot = channelname+"_"+plotname;
  TH1F *hist100 = (TH1F*)file100->Get(plot);
  TH1F *hist150 = (TH1F*)file150->Get(plot);
  TH1F *hist200 = (TH1F*)file200->Get(plot);
  TH1F *hist250 = (TH1F*)file250->Get(plot);
  cout<<"The histograms are loaded sucessfully!"<<endl;

  //Let's decorate the histograms.
  SetHistoStyle(hist100, plottitle, "Events", kRed-4);
  SetHistoStyle(hist150, plottitle, "Events", kBlue-4);
  SetHistoStyle(hist200, plottitle, "Events", kGreen+1);
  SetHistoStyle(hist250, plottitle, "Events", kViolet+7);

  //Rebin the histograms if necessary:
  hist100->Rebin(binw);
  hist150->Rebin(binw);
  hist200->Rebin(binw);
  hist250->Rebin(binw);

  //Setting up the canvas and drawing the histograms:
  TCanvas *c1 = new TCanvas(plot,plot,800,600);

  /*
    The following algorithm picks the hist containing the highest bin
    which is to be plotted first
  */
  vector<TH1F*> hists = {hist100, hist150, hist200, hist250};
  int ind = -1;
  float entries=-1;
  for(int i=0; i<(int)hists.size(); i++){
    int firstbin = 0;
    int lastbin = hists[i]->GetNbinsX();

    for(int bin=firstbin; bin<lastbin; bin++){
      int yvalue = hists[i]->GetBinContent(bin);
      if(yvalue>entries){
	entries = yvalue;
	/*
	  We need the index of the histogram for which, 'entries' is maximum.
	  That means, we need the index 'i' for which this if condition updates 'entries'
	  for the last time.
	*/
	ind = i;
      }
    }
  }

  /*
    First draw the histogram with index 'ind'
    Then draw the rest of them.
  */
  hists[ind]->SetStats(0);
  hists[ind]->Draw("hist");
  
  hist100->Draw("hist same");
  hist150->Draw("hist same");
  hist200->Draw("hist same");
  hist250->Draw("hist same");

  //Drawing the legend:
  TLegend *lg1 = new TLegend(0.6,0.65,0.87,0.87,NULL,"NDC");

  TString name;
  name = "VLL_M-100 [" + std::to_string((int)hist100->Integral()) + "]"; lg1->AddEntry(hist100,name,"f");
  name = "VLL_M-150 [" + std::to_string((int)hist150->Integral()) + "]"; lg1->AddEntry(hist150,name,"f");
  name = "VLL_M-200 [" + std::to_string((int)hist200->Integral()) + "]"; lg1->AddEntry(hist200,name,"f");
  name = "VLL_M-250 [" + std::to_string((int)hist250->Integral()) + "]"; lg1->AddEntry(hist250,name,"f");

  lg1->Draw();

  //Saving the output
  c1->SaveAs(ofname);
  
  cout<<"_____________________________  SUCCESS _______________________________\n"<<endl;
}
