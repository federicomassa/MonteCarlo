#include <TMath.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TCanvas.h>
#include <iostream>
#include <TGraph.h>
#include <TF1.h>

double pi = 4*TMath::ATan(1);

double logL(double slope, double x[], double y_g[][3], double sigma);


void retta() {
  TRandom3 rndgen;
  double m = 1;
  const int dim = 10;
  double sigma = 0.1;
  const int camp = 3;
  int imax = 0;
  
  double x[dim] = {1,2,3,4,5,6,7,8,9,10};
  double y_t[dim];
  double y_g[dim][camp];
  double mean[dim];
  double s2[dim];
  double sum2[dim];
  double err_mean[dim];
  double err_s2[dim];
  double sum_yx = 0;
  double sum_x2 = 0;
  double m_ML = 0;
  double mean_s2 = 0;
  double mean_err_s2 = 0;
  double maxL = -1E9;

  for (int i = 0; i< dim; i++) {
    y_t[i] = m*x[i];
    mean[i] = 0;
    s2[i] = 0;
    sum2[i] = 0;
    sum_x2 += x[i]*x[i];
  }
  
  for (int i = 0; i < dim; i++) { 
  for (int j = 0; j < camp; j++) {
    y_g[i][j] = rndgen.Gaus(y_t[i],sigma);
  }
  }

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < camp; j++) {
      mean[i] += (y_g[i][j])/camp; 
      sum2[i] += y_g[i][j]*y_g[i][j];
      sum_yx += y_g[i][j]*x[i];

  }   
  }

   

  for (int i = 0; i < dim; i++) {
    s2[i] = (sum2[i] - camp*mean[i]*mean[i])/(camp-1); 
    err_mean[i] = TMath::Sqrt(s2[i]/camp);
    err_s2[i] = TMath::Sqrt(2/(camp-1)*s2[i]*s2[i]); 
    mean_s2 += s2[i]/dim;
    mean_err_s2 += err_s2[i]/dim;    
  }
  
  //calcolo pendenza retta
  m_ML = sum_yx/sum_x2;

  //GRAFICO LIKELIHOOD//
  double func_L[101];
  double func_m[101];
  
  for (int i = 0; i < 101; i++) {
    func_m[i] = 0.99 + double(i)/100*0.02;
    func_L[i] = logL(func_m[i],x,y_g,sigma);
    if (func_L[i] > maxL) {maxL = func_L[i]; imax = i;}
  }
 
  //TRASLAZIONE logL
 for (int i = 0; i < 101; i++) {    
    func_L[i] -= maxL;
  }
  //FINE TRASLAZIONE
 
 TF1* CL = new TF1("CL","-0.5",0.5,1.5);
  TGraph* lk_graph = new TGraph(100,func_m,func_L);
  TCanvas* lk = new TCanvas();
  lk_graph->SetTitle("logL(m);m;logL(m)");
  lk_graph->SetMarkerStyle(7);
  lk_graph->DrawClone("AP");
  CL->DrawClone("SAME");
  //FINE GRAFICO LIKELIHOOD


  TGraphErrors* mean_graph = new TGraphErrors(dim,x,mean,NULL,err_mean);
  mean_graph->SetTitle("Grafico medie");
  mean_graph->SetMarkerStyle(2);
  TGraphErrors* s2_graph = new TGraphErrors(dim,x,s2,NULL,err_s2);
  s2_graph->SetTitle("Grafico s2");
  s2_graph->SetMarkerStyle(2);

  TCanvas* c1 = new TCanvas();
  mean_graph->DrawClone("APE");
  TCanvas* c2 = new TCanvas();
  s2_graph->DrawClone("APE");

  std::cout << "Media s2: " << mean_s2 << std::endl;
  std::cout << "CL 68%" << '\n' << mean_s2/1.309 << " < " << "s2 < " << mean_s2/0.69 << std::endl; //valori calcolati col metodo dei CL di Neyman, vedi quaderno
}


  /////////////////////LIKELIHOOD////////////////////

double logL(double slope, double x[3], double y_g[10][3],double sigma) {
  double like = 1;
  int dim = 10;
  int camp = 3;
     for (int i = 0; i < dim; i++) {
      for (int j = 0; j < camp; j++) {
	
	like = like*TMath::Exp(-(y_g[i][j]- slope*x[i])*(y_g[i][j]- slope*x[i])/(2*sigma*sigma));
	
      }
    }

  
     return TMath::Log(like*pow((1/TMath::Sqrt(2*pi)/sigma),camp*dim));
    


}

  /////////////////FINE LIKELIHOOD//////////////////
