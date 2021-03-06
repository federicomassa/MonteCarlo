#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <cmath>
#include <TH2F.h>
#include <TMinuit.h>

double sigma = 0.01;
const int nmeas = 5;
Double_t x[nmeas], y[nmeas];

void min_func(Int_t &npars, Double_t* gin, Double_t &f, Double_t* pars, Int_t iflag) {
  
  double chi2 = 0;

  for (int i = 0; i < nmeas; i++) {
    
    chi2 += TMath::Power((y[i]-pars[0]*x[i]-pars[1]*x[i]*x[i])/sigma,2);

      }

  f = chi2;
  
}

// double min_func(int nmeas, double x[], double y[],double sigma, double pars[]) {
  
//   double chi2 = 0;

//   chi2 = (pars[0]-3.2)*(pars[0]-3.2) + (pars[1]+2.5)*(pars[1]+2.5);

      

//   return chi2;
  
// }

void iter(int i, int* step, int npars, bool &first) { //in pratica un convertitore di numeri decimali in ternari
  double id = double(i);
  int id_int;
  Int_t k;
  double log_id = TMath::Log(id);
  double log3 = TMath::Log(3);

  if (first) {
    for (int j = 0; j < npars; j++) step[j] = 0;}

  if (id != 0) {
    if (TMath::Abs(log_id/log3 - double(TMath::Nint(log_id/log3))) < 1E-10 ) {step[TMath::Nint(log_id/log3)] += 1; first = true;}
    else {

      k = TMath::CeilNint(TMath::Log(id)/TMath::Log(3));
      step[k-1] += 1;
      id -= TMath::Power(3,k-1);
      id_int = int(id);
      first = false;
      iter(id_int, step, npars,first);
  
    }
  }
  else first = true;

}


void minimizz() {
const int npars = 2;
  Int_t ierflg = 0;
  int step[npars];
  TRandom3 rndgen;
  double* pars = new double[npars];
  double m_t = 6;
  double a_t = -4;
  double pars_step[npars] = {0.0001,0.0001};
  double pars_init[npars];
  double pars_start[npars];

  TMinuit* minuit = new TMinuit(2);
  minuit->SetFCN(min_func);
  
  for (int i = 0; i < nmeas; i++){
    x[i] = double(i);
    y[i] = m_t*x[i]+a_t*x[i]*x[i];
  }

  

  //inizializzazione parametri
  for (int i = 0; i < npars; i++) {
    pars_init[0] = 8;
    pars_init[1] = -6;
    pars[i] = pars_init[i];
  }

  minuit->mnparm(0,"m",pars_init[0],pars_step[0],0,0,ierflg);
  minuit->mnparm(1,"a",pars_init[1],pars_step[1],0,0,ierflg);

  minuit->mnexcm("MIGRAD", NULL, 0, ierflg);

  Double_t amin, edm, errdef;
  Int_t nvpar, nparx, icstat;
  minuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  minuit->mnprin(3,amin);
  
  
}
