#include <TRandom3.h>
#include <TH1F.h>
#include <TMath.h>
#include <TCanvas.h>

void s2() {
  int imax = 10000000;
  double sigma = 1;
  double mu = 10;
  TRandom3 rndgen;
  int camp = 3;
  double x[3];
  double s2 = 0;
  double mean_x = 0;
  double s = 0;

  TH1F* s2_hist = new TH1F("s2_hist","s2 Histogram;s2;#",1000,0,10);
  TH1F* s_hist = new TH1F("s_hist","s Histogram;s;#",1000,0,5);

  for (int i = 0; i < imax; i++) {
    for (int c = 0; c < camp; c++) {

      x[c] = rndgen.Gaus(mu,sigma);
      mean_x += x[c]/camp;
    }

   for (int c = 0; c < camp; c++) {
     
     s2 += TMath::Power((x[c]-mean_x),2)/(camp-1);
   }
   s = TMath::Sqrt(s2);
  
   s_hist->Fill(s);
   s2_hist->Fill(s2);

   s = 0;
   s2 = 0;
   mean_x = 0;
  }

  TCanvas* c_s = new TCanvas();
  c_s->cd();
  s_hist->Draw();

  TCanvas* c_s2 = new TCanvas();
  c_s2->cd();
  s2_hist->Draw();
 

}
