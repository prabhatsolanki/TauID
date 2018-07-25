#include "HttStylesNew.cc"
#include "CMS_lumi.C"

void PlotNLL(TString fileList = "tauMom_TightMva_1prongUpTo4pizeros") 
{

  SetStyle();
  gStyle->SetOptFit(0000);
  gStyle->SetErrorX(0.5);

  TString FileList = TString(fileList);


  float x0   = 0.92;
  float step = 0.01;
  float yMax = 10;

  const int nPoints = 30;

  // signal strength limits sigma*BR / sigma*BR (at tanb=30)
  double scale[nPoints];      
  double nll[nPoints];
  std::ifstream inputList(fileList);

  TString fileName;

  double MH;
  double LIMIT;

  int counter = 0;
  double scaleCounter = x0;
  double min2NLL = 1e+10;

  while (inputList >> fileName) {

       std::cout << fileName << std::endl;

    TFile * file = new TFile(fileName);

    TTree * tree = (TTree*)file->Get("tree_fit_sb");

  //     std::cout << "file : " << file << std::endl;
  //     std::cout << "tree : " << tree << std::endl;

    tree->SetBranchAddress("nll_min",&LIMIT);
    tree->GetEntry(0);
    cout<<LIMIT<<endl;
    scale[counter] = scaleCounter;

    nll[counter] = -2*LIMIT;

    if (nll[counter]<min2NLL)
      min2NLL = nll[counter];

    scaleCounter += step;
    counter++; 
      
  }


  for (int i=0; i<counter; ++i) {

    nll[i] -= min2NLL;

    char strOut[200];
    sprintf(strOut,"%5.3f  %6.3f",
	    scale[i],nll[i]);
    std::cout << strOut << std::endl;

  }

  int nPointsX = counter;
  TGraph * obsG = new TGraph(nPointsX, scale, nll);
  obsG->SetLineWidth(3);
  obsG->SetLineColor(1);
  obsG->SetLineWidth(2);
  obsG->SetMarkerColor(1);
  obsG->SetMarkerStyle(20);
  obsG->SetMarkerSize(1.4);



  TH2F * frame = new TH2F("frame","",2,x0,x0+step*(counter-0.99),4,0,yMax);
  frame->GetXaxis()->SetTitle("scale");
  frame->GetYaxis()->SetTitle("-2logL");
  frame->GetXaxis()->SetNdivisions(505);
  frame->GetYaxis()->SetNdivisions(206);
  frame->GetYaxis()->SetTitleOffset(1.25);  
  

  TCanvas *canv = MakeCanvas("canv", "histograms", 600, 600);

  frame->Draw();

  obsG->Draw("lpsame");

  TLine * line = new TLine(x0,1,x0+(counter-1)*step,1);
  line->SetLineColor(2);
  line->Draw();

  canv->Print(TString(fileList)+TString(".png"));

}
