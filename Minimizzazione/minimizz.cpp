#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <cmath>
#include <TH2F.h>


double min_func(int nmeas, double x[], double y[],double sigma, double pars[]) {
  
  double chi2 = 0;

  for (int i = 0; i < nmeas; i++) {
    
    chi2 += TMath::Power((y[i]-pars[0]*x[i]-pars[1]*x[i]*x[i])/sigma,2);

      }

  return chi2;
  
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
  int npars = 2;
  int nmeas = 5;
  int step[npars];
  TRandom3 rndgen;
  double* pars = new double[npars];
  double m_t = 6;
  double a_t = -4;
  double pars_best[npars];
  double pars_step = 0.1;
  double pars_init[npars];
  double pars_start[npars];
  double x[nmeas];
  double y[nmeas];
  double sigma = 0.1;
  bool end_cycle = true; // è true quando ha trovato il minimo di tutti i parametri 
  bool first = true;
  double chi2_old;
  double chi2;


  for (int i = 0; i < nmeas; i++){
    x[i] = double(i);
    y[i] = m_t*x[i]+a_t*x[i]*x[i];
  }

  //grafico chi2
  TH2F* chi2_hist = new TH2F("chi2_hist","Grafico Chi2;m;a;Chi2",100,5.999,6.001,100,-4.001,-3.999);
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= 100; j++) {
      pars[0] = 5.999 + double(i)/100*0.002;
      pars[1] = -4.001 + double(j)/100*0.002;
      chi2_hist->SetBinContent(i,j,min_func(nmeas,x,y,sigma,pars));
    }
  }

  chi2_hist->Draw();


  //inizializzazione parametri
  for (int i = 0; i < npars; i++) {
    pars_init[0] = 7;
    pars_init[1] = -5;
    pars[i] = pars_init[i];
    chi2 = min_func(nmeas,x,y,sigma,pars);
    chi2_old = chi2;
  }

  do {
    end_cycle = true;
    for (int i = 0; i < npars; i++) {
      pars_start[i] = pars[i];}

    for (int i = 0; i < TMath::Nint(TMath::Power(3,double(npars))) ; i++) {

      iter(i,step,npars,first);
      for(int k = 0; k < npars; k++)
	pars[k] = pars_start[k] + double((step[npars-k-1]-1))*pars_step; //step è 0,1,2
      
      chi2 = min_func(nmeas,x,y,sigma,pars);
      //        std:: cout << "i: " << i << " chi2: " << chi2 << " m: " << pars[0] << " a: " << pars[1] << std::endl;
      if(chi2 <= chi2_old) {chi2_old = chi2; for (int k = 0; k < npars; k++) pars_best[k] = pars[k]; /*std::cout << "SCELTO" << std::endl;*/}
      
    }
    
    //  std::cout << std::endl;
   
    for (int i = 0; i < npars; i++) {
      pars[i] = pars_best[i];}
    
    for (int i = 0; i < npars; i++) {
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
