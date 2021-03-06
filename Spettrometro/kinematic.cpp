#include <TH1F.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TMath.h>

void kinematic() {

  TRandom3 rndgen;
  const int nmeas = 10000000;
  double sigma_E = 1;
  double E_tot = 100;
  double mean_E1 = 75;
  double mean_E2 = E_tot - mean_E1;
  double E1[nmeas];
  double E1_k[nmeas]; //kinematic fit
  double E2[nmeas];
  double E2_k[nmeas]; //kinematic fit
  double E_rec[nmeas];

  double E1_u[nmeas];
  double E1_k_u[nmeas]; //kinematic fit
  double E2_u[nmeas];
  double E2_k_u[nmeas]; //kinematic fit
  double E_rec_u[nmeas];
  
  
  TFile* f_out = new TFile("kinematic_fit.root","RECREATE");

  TH1F* E_rec_hist = new TH1F("E_rec_hist","Reconstructed total energy histogram",1000,E_tot-10*sigma_E, E_tot + 10*sigma_E);

  TH1F* E1_k_hist = new TH1F("E1_k_hist","E1 kinematic fit",1000,mean_E1-10*sigma_E, mean_E1 + 10*sigma_E);

  TH1F* E2_k_hist = new TH1F("E2_k_hist","E2 kinematic fit",1000,mean_E2-10*sigma_E, mean_E2 + 10*sigma_E);

 TH1F* E_rec_u_hist = new TH1F("E_rec_u_hist","Reconstructed total energy histogram",1000,E_tot-10*sigma_E, E_tot + 10*sigma_E);

  TH1F* E1_k_u_hist = new TH1F("E1_k_u_hist","E1 kinematic fit",1000,mean_E1-10*sigma_E, mean_E1 + 10*sigma_E);

  TH1F* E2_k_u_hist = new TH1F("E2_k_u_hist","E2 kinematic fit",1000,mean_E2-10*sigma_E, mean_E2 + 10*sigma_E);

  

  //simulazione misure gaussiane
  for (int i = 0; i < nmeas; i++) {

     E1[i] = rndgen.Gaus(mean_E1,sigma_E);
     E2[i] = rndgen.Gaus(mean_E2,sigma_E);

    E1_u[i] = mean_E1 + rndgen.Uniform(TMath::Sqrt(12)*sigma_E) - TMath::Sqrt(12)*sigma_E/2;
    E2_u[i] = mean_E2 + rndgen.Uniform(TMath::Sqrt(12)*sigma_E) - TMath::Sqrt(12)*sigma_E/2;

    E_rec[i] = E1[i] + E2[i];
    E_rec_hist->Fill(E_rec[i]);

    E1_k[i] = E1[i]/E_rec[i]*E_tot;
    E2_k[i] = E_tot - E1_k[i];

    E1_k_hist->Fill(E1_k[i]);
    E2_k_hist->Fill(E2_k[i]);

E_rec_u[i] = E1_u[i] + E2_u[i];
    E_rec_u_hist->Fill(E_rec_u[i]);

    E1_k_u[i] = E1_u[i]/E_rec_u[i]*E_tot;
    E2_k_u[i] = E_tot - E1_k_u[i];

    E1_k_u_hist->Fill(E1_k_u[i]);
    E2_k_u_hist->Fill(E2_k_u[i]);
  }


  E_rec_hist->Write();
  E1_k_hist->Write();
  E2_k_hist->Write();
  E_rec_u_hist->Write();
  E1_k_u_hist->Write();
  E2_k_u_hist->Write();
  f_out->Close();

}
