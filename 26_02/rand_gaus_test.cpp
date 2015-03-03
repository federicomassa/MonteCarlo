#include <TMath.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <TFile.h>
#include <TF1.h>
#include <TStyle.h>
void rand_gaus() {
  TRandom3 rndgen;
  int imax = 10000000;
  double x;
  double r1, r2;
  double sigma = 1;
  double pi = 4*TMath::ATan(1);
  TH1F* hist = new TH1F("histo","Generazione distribuzione gaussiana",1000,-5,5);
  TFile out("rand_gaus.root","RECREATE");
  TF1* fit = new TF1("Gaussiana","gaus",-5,5);
  for (int i = 0; i < imax; i++) {
    r1 = rndgen.Uniform();
    r2 = rndgen.Uniform();
    x = sigma*TMath::Sqrt(-2*TMath::Log(r2))*TMath::Cos(2*pi*r1);
    hist->Fill(x);
  }

  hist->Fit(fit,"R");
  gStyle->SetOptFit(11111);
  hist->Write();
  out.Close();

}
