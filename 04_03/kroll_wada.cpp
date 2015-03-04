#include <TMath.h>
#include <TRandom3.h>
#include <TF1.h>
#include <TCanvas.h>
#include <ctime>
#include <TH1F.h>


double kroll_wada(double mee) {
  double me = 0.5109989; //electron mass (MeV)
  double M = 134.9766; //pi0 mass (MeV)
  double kroll;
  
  kroll = TMath::Sqrt(1-4*me*me/(mee*mee))*(1+2*me*me/(mee*mee))*1/me*(1-mee*mee/(M*M));

  return kroll;

}

double kroll_wada1(double* mee, double* pars) {
  double me = 0.5109989; //electron mass (MeV)
  double M = 134.9766; //pi0 mass (MeV)
  double kroll; 

  kroll = TMath::Sqrt(1-4*me*me/(mee[0]*mee[0]))*(1+2*me*me/(mee[0]*mee[0]))*1/me*(1-mee[0]*mee[0]/(M*M));

  return kroll;

}

void kroll_wada() {
  double me = 0.5109989;
  double M = 134.9766;
  TRandom3 rndgen;
  int i = 0;
  int trials = 0;
  int imax = 5E7; //eventi da generare
  double r1,r2;
  double kroll_max;
  long init_time;
  long end_time;

  TH1F* kroll_hist = new TH1F("kroll_hist","Distribuzione secondo Kroll-Wada",140,0,140);

  //Grafico funzione Kroll-Wada, determinazione del massimo
  TF1* kroll_wada_func = new TF1("kroll_wada_func",kroll_wada1,2*me,M,0);
  kroll_max = kroll_wada_func->GetMaximum(4,6);
  TCanvas* kroll_canv = new TCanvas("kroll_canv","Kroll-Wada");
  kroll_canv->cd();
  kroll_wada_func->SetNpx(10000);
  kroll_wada_func->Draw();
  //fine Grafico
  
  init_time = std::time(0);
  do{
    trials += 1;
    r1 = rndgen.Uniform(2*me,M);
    r2 = rndgen.Uniform();
    if (kroll_wada(r1)/kroll_max > r2) {
      i += 1;
      kroll_hist->Fill(r1);
    } 

  }

  while(i < imax);
  
  TCanvas* kroll_hist_canv = new TCanvas("kroll_hist_canv","Distribuzione secondo Kroll-Wada");
  kroll_hist_canv->cd();
  
  kroll_hist->Draw();

  end_time = std::time(0) - init_time;
  std::cout << "Tempo (s) impiegato a produrre " << imax << " eventi: " << end_time << std::endl;
  
  std::cout << "Efficienza: " << double(imax)/double(trials) << std::endl;

}
