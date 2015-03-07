#include <iostream>
#include <TMath.h>

void iter(int i, int* step, int npars, bool &first) { //in pratica un convertitore di numeri decimali in ternari
  double id = double(i);
  int id_int;
  Int_t k;
  double log_id = TMath::Log(id);
  double log3 = TMath::Log(3);

  if (first) {
    for (int j = 0; j < npars; j++) step[j] = 0;}

  if (id != 0) {
    if (TMath::Abs(log_id/log3 - double(TMath::Nint(log_id/log3))) < 1E-10 ) {step[TMath::Nint(log_id/log3)] += 1; std::cout << "!!!" << std::endl; first = true;}
    else {

      k = TMath::CeilNint(TMath::Log(id)/TMath::Log(3));
      step[k-1] += 1;
      id -= TMath::Power(3,k-1);
      std::cout << "ID: " << id << std::endl;
      id_int = int(id);
      first = false;
      iter(id_int, step, npars,first);
  
    }
  }
  else first = true;

}

void prova() {

  int p[2];
  int npars = 2;
  int i;
  bool first = true;

  for (int l = 0; l < 100; l++) {
  std::cout << "Numero: " << std::endl;
  cin >> i;
  iter(i,p,npars,first);

  for(int j = 0; j < npars; j++) {
    std::cout << p[npars-j-1];
  }
  std::cout << std::endl;

  }
}
