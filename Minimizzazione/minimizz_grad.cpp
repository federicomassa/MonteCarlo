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
  double precision = 1E-7;
  double prop = 1E-5;
  int first = 0;
  bool sign;
  double norm_grad;
  int npars = 2;
  int nmeas = 5;
  TRandom3 rndgen;
  double* pars = new double[npars];
  double m_t = 6;
  double a_t = -4;
  double pars_step[npars];  //per calcolo derivata
  double init_radius = 0.001;
  double radius;
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




  //inizializzazione parametri
  for (int i = 0; i < npars; i++) {
    pars_step[i] = 0.0001;
    pars_init[0] = 8;
    pars_init[1] = -6;
    pars[i] = pars_init[i];
    chi2 = min_func(nmeas,x,y,sigma,pars);
  }

  first = 0;

  do {
    first++;
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

        norm_grad = TMath::Sqrt(norm_grad);

    // if (first == 1) {
    //   prop = 0.0005;
    // }


    //      for (int i = 0; i < npars; i++) pars_step[i] = radius;

	    //    std::cout << prop << '\n' << first << '\n' << radius << '\n' << pars[0] << '\n' << pars[1] << '\n' << std::endl;
    

    
  

  sign = true;
  for (int i = 0; i < npars; i++) {
    sign = sign && (grad_up[i] > 0 && grad_down[i] < 0);}

  if (sign) { //siamo nel minimo
    end_cycle = true;
    break;
  }

  else { 
    sign = true;
    end_cycle = false;
    for (int i = 0; i < npars; i++) {
      pars[i] = pars_start[i] - prop*grad_up[i]; // segno - per andare verso il minimo
    
      if (TMath::Abs(grad_up[i]*prop) > precision) sign = false;
    }
    end_cycle = sign;
  }

 
    
    
    
  }



  while (!end_cycle);
  
  std::cout << "m minimo: " << pars[0] << std::endl;
  std::cout << "a minimo: " << pars[1] << std::endl;
  std::cout << "chi2 minimo: " << chi2 << std::endl;
  std::cout << "iterazioni: " << first << std::endl;
}
