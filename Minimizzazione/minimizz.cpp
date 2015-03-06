#include <iostream>
#include <TMath.h>
#include <TRandom3.h>

double min_func(int nmeas, double x[], double y[],double sigma, int npars, double pars[]) {
  
  double chi2 = 0;

  for (int i = 0; i < nmeas; i++) {
    
    chi2 += TMath::Power((y[i]-pars[0]*x[i])/sigma,2);

      }

  return chi2;
  
}


void minimizz() {
  TRandom3 rndgen;
  double* m = new double;
  double m_t = 1;
  double m_best;
  double m_step = 0.01;
  double m_min = 0.5;
  double m_max = 1.5;
  double x[10];
  double y[10];
  double sigma = 0.05;

  int n_step = int((m_max - m_min)/m_step);
  
  double chi2_old = 1E7;
  double chi2 = 0;


  for (int i = 0; i < 10; i++){
    x[i] = double(i);
    y[i] = rndgen.Gaus(m_t*x[i],sigma);
  }


  for (int i = 0; i < n_step; i++) {
    *m = m_min + m_step*double(i);
    chi2 = min_func(10,x,y,sigma,1,m);
    std::cout << chi2 << std::endl;
    if(chi2 < chi2_old) {chi2_old = chi2; m_best = *m;}
  }
  
  std::cout << "m minimo: " << m_best << std::endl;

}
