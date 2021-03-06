#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"

void WToMuNuMeasurement() {

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  initCuts();
  loadkFactors("kfactor_mu.root");

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data;
  //data.push_back("SingleMuon_Run2017F");
  //data.push_back("SingleMuon_Run2017D");
  //data.push_back("SingleMuon_Run2017E");
  data.push_back("SingleMuon_Run2017_0");
  data.push_back("SingleMuon_Run2017_1");
  data.push_back("SingleMuon_Run2017_2");
  data.push_back("SingleMuon_Run2017_3");
  data.push_back("SingleMuon_Run2017_4");
  data.push_back("SingleMuon_Run2017_5");
  data.push_back("SingleMuon_Run2017_6");
  data.push_back("SingleMuon_Run2017_7");
  data.push_back("SingleMuon_Run2017_8");
  data.push_back("SingleMuon_Run2017_9");

  std::vector<TString> ewk;
  ewk.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-800To1200_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-1200To2500_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph");
  ewk.push_back("ZZ_TuneCP5_13TeV-pythia8");
  ewk.push_back("WW_TuneCP5_13TeV-pythia8");
  ewk.push_back("WZ_TuneCP5_13TeV-pythia8");
  ewk.push_back("DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8");
  ewk.push_back("DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8");
  ewk.push_back("DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8");
  ewk.push_back("DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8");
  ewk.push_back("DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8");

  std::vector<TString> tt;
  tt.push_back("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8");
  tt.push_back("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8");
  tt.push_back("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8");
  tt.push_back("ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8");
  tt.push_back("ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8");
  tt.push_back("ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");
  tt.push_back("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");

  std::vector<TString> WToMuNu;
  WToMuNu.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8");

  std::vector<TString> WToMuNu_jesUp;
  WToMuNu_jesUp.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_jesUp");
  std::vector<TString> WToMuNu_jesDown;
  WToMuNu_jesDown.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_jesDown");
  std::vector<TString> WToMuNu_muUp;
  WToMuNu_muUp.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_muUp");
  std::vector<TString> WToMuNu_muDown;
  WToMuNu_muDown.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_muDown");
  std::vector<TString> WToMuNu_uesUp;
  WToMuNu_uesUp.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_uesUp");
  std::vector<TString> WToMuNu_uesDown;
  WToMuNu_uesDown.push_back("WToMuNu_M-200_TuneCP5_13TeV-pythia8_uesDown");

  samples.push_back(make_pair("data_obs" , data));
  samples.push_back(make_pair("EWK" , ewk));
  samples.push_back(make_pair("TT" , tt));
  samples.push_back(make_pair("W" , WToMuNu));
  samples.push_back(make_pair("W_jesUp" , WToMuNu_jesUp));
  samples.push_back(make_pair("W_jesDown" , WToMuNu_jesDown));
  samples.push_back(make_pair("W_muUp" , WToMuNu_muUp));
  samples.push_back(make_pair("W_muDown" , WToMuNu_muDown));
  samples.push_back(make_pair("W_uesUp" , WToMuNu_uesUp));
  samples.push_back(make_pair("W_uesDown" , WToMuNu_uesDown));

  TString var = "mtmuon";

  THStack *stack = new THStack("stack_mtmuon","");
  TH1D* h_data = 0;
  std::map<TString,TH1D*> histoMap;

  for (unsigned int i=0; i<samples.size(); ++i) {
    
    cout<<"Process "<<samples[i].first<<endl;
    
    TH1D* histoSamples = new TH1D(samples[i].first,"",10,0,1000);
    
    for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){

      cout<<".............. Sample : "<<samples[i].second[idx_list]<<endl;

      TH1D* histo = new TH1D(samples[i].second[idx_list],samples[i].second[idx_list],10,0,1000);
      selectionCuts select = sr_munu;
      makeSelection(dir+"/"+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),"Tight",select,histo,var,var,var);
      histoSamples->Add(histo);
      histoSamples->SetFillStyle(1001);
      if(samples[i].first.Contains("TT"))       histoSamples->SetFillColor(TColor::GetColor("#FFCCFF"));
      else if(samples[i].first.Contains("EWK")) histoSamples->SetFillColor(TColor::GetColor("#6F2D35"));
      else if(samples[i].first.Contains("W"))   histoSamples->SetFillColor(TColor::GetColor("#FFCC66"));
    }

    histoMap[samples[i].first] = histoSamples;
    if(!samples[i].first.Contains("data_obs") && !samples[i].first.Contains("Up") && !samples[i].first.Contains("Down")){
      stack->Add(histoSamples);
    }
    else if(samples[i].first.Contains("data_obs")) h_data = (TH1D*) histoSamples->Clone(); 
    cout<<samples[i].first<<" = "<<histoSamples->GetSumOfWeights()<<" ( Entries = "<<histoSamples->GetEntries()<<" )"<<endl<<endl;
  }

  // ------------------ Computation of all uncertainties : START  -------
  TH1D * bkgdErr = (TH1D*)stack->GetStack()->Last()->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);  
  double addErr = 0;
  for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
    // 1.) Uncertainty on JES, Mu, UES
    addErr = histoMap["W_jesUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));      
    addErr = histoMap["W_muUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
    addErr = histoMap["W_uesUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
  }
  // ------------------ Computation of all uncertainties : END  -------

  TCanvas * canv = new TCanvas("canv","",700,800);
  TPad* upper = new TPad("upper","pad",0,0.19,1,1);
  upper->Draw();
  upper->cd();

  stack->Draw("hist");
  stack->SetMaximum(stack->GetMaximum()*1.2);
  stack->GetXaxis()->SetTitle("");
  stack->GetYaxis()->SetTitle("Events");
  stack->GetXaxis()->SetLabelSize(0.);
  gPad->Modified(); 
  if(h_data){
    h_data->Draw("e1 same");
    bkgdErr->Draw("e2same");
  }

  TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
  SetLegendStyle(leg);
  leg->SetTextSize(0.047);
  if(h_data)          leg->AddEntry(h_data,"Data","lp");
  if(histoMap["W"])   leg->AddEntry(histoMap["W"],"W#rightarrow#mu#nu","f");
  if(histoMap["TT"])  leg->AddEntry(histoMap["TT"],"tt + single top","f");
  if(histoMap["EWK"]) leg->AddEntry(histoMap["EWK"],"electroweak","f");
  writeExtraText = true;
  extraText = "Internal";
  CMS_lumi(upper,5,33);
  leg->Draw("same");

  TH1D * ratioH = 0;
  if(h_data){
    ratioH = (TH1D*) h_data->Clone("ratioH");
    ratioH->Divide((TH1D*)stack->GetStack()->Last());
    ratioH->GetYaxis()->SetTitle("Obs./Exp.");
    //ratioH->GetXaxis()->SetTitle("m_{T} [GeV]");
    ratioH->GetXaxis()->SetTitle(var);
    ratioH->GetXaxis()->SetTitleOffset(3.5);
    ratioH->GetYaxis()->SetNdivisions(505);
    ratioH->GetYaxis()->SetRangeUser(0.4,1.6);
    ratioH->GetYaxis()->CenterTitle();
    ratioH->GetXaxis()->SetLabelSize(30);
  }
  TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
  for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
    ratioErrH->SetBinError(i,bkgdErr->GetBinError(i)/bkgdErr->GetBinContent(i));
    if(bkgdErr->GetBinContent(i)==0) ratioErrH->SetBinError(i,0);
    ratioErrH->SetBinContent(i,1);
  }
  ratioErrH->SetFillStyle(3013);
  ratioErrH->SetFillColor(1);
  ratioErrH->SetMarkerStyle(21);
  ratioErrH->SetMarkerSize(0);

  canv->cd();
  TPad * lower = new TPad("lower", "pad",0,0,1,0.31);
  lower->SetBottomMargin(0.32);
  lower->SetGridy();
  lower->Draw();
  lower->cd();
  if(h_data) ratioH->Draw("e1");
  ratioErrH->Draw("e2 same");
  canv->cd();
  canv->Modified();
  canv->SetSelected(canv);
  canv->Update();
  canv->Print("figures/" + var + "_WToMuNu.pdf");


  // Get bin-by-bin uncertainties for WMuNu
  TH1D* histo = 0;
  for(int i =1; i<=histoMap["W"]->GetNbinsX(); i++){
    histo = (TH1D*) histoMap["W"]->Clone();
    histo->SetBinContent(i,histoMap["W"]->GetBinContent(i)+histoMap["W"]->GetBinError(i));
    histo->SetName(Form("W_Bin%i_WToMuNuUp",i));
    histoMap[histo->GetName()] = histo;
    histo = (TH1D*) histoMap["W"]->Clone();
    histo->SetBinContent(i,histoMap["W"]->GetBinContent(i)-histoMap["W"]->GetBinError(i));
    histo->SetName(Form("W_Bin%i_WToMuNuDown",i));
    histoMap[histo->GetName()] = histo;
  }
  for(int i =1; i<=histoMap["TT"]->GetNbinsX(); i++){
    histo = (TH1D*) histoMap["TT"]->Clone();
    histo->SetBinContent(i,histoMap["TT"]->GetBinContent(i)+histoMap["TT"]->GetBinError(i));
    histo->SetName(Form("TT_Bin%i_TTUp",i));
    histoMap[histo->GetName()] = histo;
    histo = (TH1D*) histoMap["TT"]->Clone();
    histo->SetBinContent(i,histoMap["TT"]->GetBinContent(i)-histoMap["TT"]->GetBinError(i));
    histo->SetName(Form("TT_Bin%i_TTDown",i));
    histoMap[histo->GetName()] = histo;
  }
  for(int i =1; i<=histoMap["EWK"]->GetNbinsX(); i++){
    histo = (TH1D*) histoMap["EWK"]->Clone();
    histo->SetBinContent(i,histoMap["EWK"]->GetBinContent(i)+histoMap["EWK"]->GetBinError(i));
    histo->SetName(Form("EWK_Bin%i_EWKUp",i));
    histoMap[histo->GetName()] = histo;
    histo = (TH1D*) histoMap["EWK"]->Clone();
    histo->SetBinContent(i,histoMap["EWK"]->GetBinContent(i)-histoMap["EWK"]->GetBinError(i));
    histo->SetName(Form("EWK_Bin%i_EWKDown",i));
    histoMap[histo->GetName()] = histo;
  }

  // Save all histograms in one file
  TFile *out = new TFile("output/" + var + "_WToMuNu_shapes.root","RECREATE");
  out->cd();

  map<TString,TH1D*>::iterator it;
  for ( it = histoMap.begin(); it != histoMap.end(); it++ )
    {
      histoMap[it->first]    ->Write(it->first);
    }
}
