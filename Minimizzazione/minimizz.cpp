#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <cmath>

double min_func(int nmeas, double x[], double y[],double sigma, double pars[]) {
  
  double chi2 = 0;

  for (int i = 0; i < nmeas; i++) {
    
    chi2 += TMath::Power((y[i]-pars[0]*x[i]-pars[1]*x[i]*x[i])/sigma,2);

      }

  return chi2;
  
}

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
  int npars = 2;
  int step[npars];
  TRandom3 rndgen;
  double* pars = new double[npars];
  double m_t = 6;
  double a_t = -4;
  double pars_best[npars];
  double pars_step = 0.013;
  double pars_init[npars];
  double pars_start[npars];
  double x[100];
  double y[100];
  double sigma = 0.0001;
  bool end_cycle = true; // è true quando ha trovato il minimo di tutti i parametri 
  bool first = true;
  double chi2_old;
  double chi2;


  for (int i = 0; i < 100; i++){
    x[i] = double(i);
    y[i] = rndgen.Gaus(m_t*x[i]+a_t*x[i]*x[i],sigma);
  }

  //inizializzazione parametri
  for (int i = 0; i < npars; i++) {
    pars_init[0] = 5.9;
    pars_init[1] = -3.9;
    pars[i] = pars_init[i];
    chi2 = min_func(10,x,y,sigma,pars);
    chi2_old = chi2;
  }

  do {
    end_cycle = true;
    for (int i = 0; i < npars; i++) {
      pars_start[i] = pars[i];}

    for (int i = 0; i < TMath::Power(3,double(npars)) ; i++) {

      iter(i,step,npars,first);
      for(int k = 0; k < npars; k++)
	pars[k] = pars_start[k] + double((step[k]-1))*pars_step; //step è 0,1,2
      
      chi2 = min_func(10,x,y,sigma,pars);
      if(chi2 <= chi2_old) {chi2_old = chi2; for (int k = 0; k < npars; k++) pars_best[k] = pars[k]; std::cout << chi2 << std::endl;}
      
    }
    
   
    for (int i = 0; i < npars; i++) {
      pars[i] = pars_best[i];
      if (pars_best[i] == pars_start[i]) end_cycle = true;
      else {end_cycle = false; break;}
    }
    //alla fine del for end_cycle è vero solo se il punto migliore
    //è quello di prima
    
    
    
  }



  while (!end_cycle);
  
  std::cout << "m minimo: " << pars_best[0] << std::endl;
  std::cout << "a minimo: " << pars_best[1] << std::endl;
}
