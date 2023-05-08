/*
This file contains some custom functions
which are being callle dinthe main C script
 */

void SetOverflowBin(TH1F *h){
  //Given a histogram, it sets the last bin as overflow.
  int lastbin = h->GetNbinsX();
  float lastbincontent = h->GetBinContent(lastbin);
  float overflow = h->GetBinContent(lastbin+1);
  h->SetBinContent(lastbin, lastbincontent+overflow);
}

void SetHistoStyle(TH1F *h, TString plottitle, TString ytitle, int color){
  //This is where the histograms are decorated

  TString title = "Overlay of "+plottitle+" across different masses";
  h->SetLineColor(color);
  h->SetLineWidth(3);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.2);
  h->SetTitle(title);

  //Y-axis
  h->GetYaxis()->SetTitle(ytitle);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleSize(20);
  h->GetYaxis()->SetTitleOffset(1.6);
  h->GetYaxis()->SetLabelFont(43);
  h->GetYaxis()->SetLabelSize(18);
  h->GetYaxis()->CenterTitle();

  //X-axis
  h->GetXaxis()->SetTitle(plottitle);
  h->GetXaxis()->SetTitleFont(43);
  h->GetXaxis()->SetTitleSize(20);
  h->GetXaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetLabelFont(43);
  h->GetXaxis()->SetLabelSize(18);
  //h->GetXaxis()->CenterTitle();
}
