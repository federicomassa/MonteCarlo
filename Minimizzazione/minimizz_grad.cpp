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



void minimizz() {
  bool sign;
  double norm_grad;
  int npars = 2;
  int nmeas = 5;
  TRandom3 rndgen;
  double* pars = new double[npars];
  double m_t = 6;
  double a_t = -4;
  double pars_best[npars];
  double pars_step[npars];  //per calcolo derivata
  double radius = 0.01;
  double pars_init[npars];
  double pars_start[npars];
  double chi2_up[npars];
  double chi2_down[npars];
  double grad_up[npars];
  double grad_down[npars];
  double x[nmeas];
  double y[nmeas];
  double sigma = 0.1;
  bool end_cycle = true; // è true quando ha trovato il minimo di tutti i parametri 
  double chi2;


  for (int i = 0; i < nmeas; i++){
    x[i] = double(i);
    y[i] = m_t*x[i]+a_t*x[i]*x[i];
  }

  //grafico chi2
  TH2F* chi2_hist = new TH2F("chi2_hist","Grafico Chi2;m;a;Chi2",100,5.999,6.005,100,-4.001,-3.999);
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= 100; j++) {
      pars[0] = 5.999 + double(i)/100*0.006;
      //pars[0] = 6;
      pars[1] = -4.001 + double(j)/100*0.002;
	    // pars[1] = -4;
      chi2_hist->SetBinContent(i,j,min_func(nmeas,x,y,sigma,pars));
    }
  }

  chi2_hist->Draw();


  //inizializzazione parametri
  for (int i = 0; i < npars; i++) {
    pars_step[i] = 0.00001;
    pars_init[0] = 8;
    pars_init[1] = -6;
    pars[i] = pars_init[i];
    chi2 = min_func(nmeas,x,y,sigma,pars);
  }

  do {
    end_cycle = true;
    for (int i = 0; i < npars; i++) {
      pars_start[i] = pars[i];}

    chi2 = min_func(nmeas,x,y,sigma,pars);

    for (int i = 0; i < npars; i++){
      pars[i] = pars_start[i] + pars_step[i];
      chi2_up[i] = min_func(nmeas,x,y,sigma,pars);
      pars[i] = pars_start[i] - pars_step[i];
      chi2_down[i] = min_func(nmeas,x,y,sigma,pars);
      pars[i] = pars_start[i];
      grad_up[i] = (chi2_up[i]-chi2)/pars_step[i];
      grad_down[i] = (chi2 - chi2_down[i])/pars_step[i];
      
    }

    norm_grad = 0;
    for (int i = 0; i < npars; i++)
      norm_grad += grad_up[i]*grad_up[i];

    for (int i = 0; i < npars; i++)
      grad_up[i] = grad_up[i]/norm_grad*radius;
    
    

  sign = true;
  for (int i = 0; i < npars; i++) {
    sign = sign && (grad_up[i] > 0 && grad_down[i] < 0);}

  if (sign) { //siamo nel minimo
    end_cycle = true;
    for (int i = 0; i < npars; i++) {
      pars_best[i] = pars_start[i];
    }
    break;
  }

  else { 
    end_cycle = false;
    for (int i = 0; i < npars; i++) {
      pars[i] = pars_start[i] - grad_up[i]; // segno - per andare verso il minimo
    }
  }

 
    
    
    
  }



  while (!end_cycle);
  
  std::cout << "m minimo: " << pars_best[0] << std::endl;
  std::cout << "a minimo: " << pars_best[1] << std::endl;
  std::cout << "chi2 minimo: " << chi2 << std::endl;
}
