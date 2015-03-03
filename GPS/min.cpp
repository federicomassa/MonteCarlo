#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;
// dichiara var globali e funzioni
int t =0;
int r = 6370.;
double c = 299792.458;
// vettore posizione tempi satelliti 
int n = 4; 
double xs[4]; double ys[4]; double zs[4]; double ts[4]; 
double p[3];

double funchi(double x, double y, double z, double *xs, double *ys, double *zs, double *ts, double t);
void min(double *xs, double *ys, double *zs, double *ts, double t);


int main(){
// inizializza
//cout<<"numero dei satelliti =   "<<endl;
//cin>>n;

double xp;//=906.10;
double yp;//=634.45;
double zp;//=6273.23;
float thetap;
float phip;
cout << "theta punto :";
cin >> thetap;
cout << "phi punto :";
cin >> phip;

thetap = thetap*3.1415926/180.;
phip = phip*3.1415926/180.;
xp = r*sin(thetap)*cos(phip);
yp = r*sin(thetap)*sin(phip);
zp = r*cos(thetap);
cout << "(x,y,z) = " << xp <<" "<<yp<<" "<<zp<<" "<< endl;
//cout << "x punto :";
//cin >> xp;
//cout << "y punto :";
//cin >> yp;
//cout << "z punto :";
//cin >> zp;

xs[1]=-15185;
ys[1]=0;
zs[1]=26301.19;

xs[2]=20179.74;
ys[2]=-7344.82;
zs[2]=21474.83;

xs[3]=0;
ys[3]=0;
zs[3]=30370;

xs[4]=16906.08;
ys[4]=20147.88;
zs[4]=15185;
for (int i = 0; i < n; i++) { 
//	cout<<"x satellite"<<i+1<<endl;
//	cin >> xs[i];
//	cout<<"y satellite"<<i+1<<endl;
//	cin >> ys[i];
//	cout<<"z satellite"<<i+1<<endl;
//	cin >> zs[i];
//	cout<<"tempo segnale satellite"<<i+1<<endl;
//	cin >> ts[i];	
	ts[i]=sqrt( ((xs[i]-xp)*(xs[i]-xp)+(ys[i]-yp)*(ys[i]-yp)+(zs[i]-zp)*(zs[i]-zp))/ 89875517873.6817);

	}
p[0]=0;
p[1]=0;
p[2]=0; 
// chiama funzione
min( xs, ys, zs, ts, t);
// restituisci x y z  minimo 
cout<<"coordinate punto =  ("<<p[0]<<", "<<p[1]<<", "<<p[2]<< ")"<<endl;
 return 0;
}




// funzione minimizza
void min(double *xs, double *ys, double *zs, double *ts, double t )
	{

////////////////////////////////////////////////////////
///  DEFINIZIONE VARIABILI\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// in entrata : posizioni satelliti(visti), tempi, t0  
// inizializza x y z ?
	double xm=0; 
	double ym=0; 
	double zm=0;
	double chi1 ; double theta1 ; double phi1 ;
	double chi2 ; double theta2 ; double phi2 ;
	double chi3 ; double theta3 ; double phi3 ;
	double chi4 ; double theta4 ; double phi4 ;
	double x1 ; double y1; double z1;
	double x2 ; double y2; double z2;
	double x3 ; double y3; double z3;
	double x4 ; double y4; double z4;
	double chi_temp ; double theta_temp ; double phi_temp;
	double chi ; double theta; double phi;
	double dtheta; double dphi;
	int passo_theta = 1;
	int passo_phi = 1;
//proiezione xmedio ymedio zmedio satelliti  sulla superficie della terra!!! fissa r , ricavo theta e phi e ricalcola x y z
	for (int i = 0; i < n; i++) { 
		xm =xm+xs[i];
		ym =ym+ys[i];
		zm =zm+zs[i];
		}
	xm=xm/n;	
	ym=ym/n;
	zm=zm/n;
	cout<<"punto medio: "<<xm<<"  "<<ym<<"  "<<zm<<endl;
	cout << "tan(theta): " << (sqrt(xm*xm + ym*ym)/zm) <<endl;
	cout << "tan(phi): " << (ym/xm) <<endl; 	
	theta = atan(sqrt((xm*xm + ym*ym)/zm)); 
	phi= atan(ym/xm);
	cout << "theta: " << theta<< endl;
	cout << "phi: " << phi<< endl;
	double x = r *sin(theta)*cos(phi);
	double y = r *sin(theta)*sin(phi);
	double z = r *cos(theta);
	chi= funchi(x,y,z,xs,ys,zs,ts,t);
	cout<<"coordinate pto medio sulla terra: "<<x<< " "<<y<<" "<<z<<endl;
	chi1 = chi2=chi3=chi4=chi-1;
	chi_temp=chi;
	int k=0;
// incrementa dx dy dz su superficie terrestre = coordinate polari sferiche  r cost(?) dtheta dphi
//		passo =1;
		double dcostheta = passo_theta/6370;
		dtheta = sin(theta)*dcostheta; 
		dphi = passo_phi / 6370.;
//		cout << "dtheta,dphi" << dtheta << "," << dphi << endl;
	// calcolo chi 4 punti vicini: 0+-dtheta 0+-dphi
		// 0+dtheta
		theta1=theta+dtheta;
		if(theta1 < 0 or theta1 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 1: " << theta1 << endl;
			}
		phi1=phi;
		if(phi1 < -3.1415926 or phi1 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 1: " << phi1 << endl;
			}
		x1 = r*sin(theta1)*cos(phi1);
		y1 = r*sin(theta1)*sin(phi1);
		z1 = r*cos(theta1);
//		cout << "theta,phi,x,y,z=" << theta1 << "," << phi1 << "," << x1 << "," << y1 << "," << z1 << "," << endl;	
		chi1 = funchi(x1,y1,z1,xs,ys,zs,ts,t);
//		cout<<"chi1 "<<chi1<<endl;
		//0-dtheta
		theta2=theta-dtheta;
		if(theta2 < 0 or theta2 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore: theta 2: " << theta2 << endl;
			}
		phi2=phi;
		if(phi2 < -3.1415926 or phi2 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 2: " << phi2 << endl;
			}
		x2 = r *sin(theta2)*cos(phi2);
		y2 = r *sin(theta2)*sin(phi2);
		z2 = r *cos(theta2);
				
		chi2 = funchi(x2,y2,z2,xs,ys,zs,ts,t);
//		cout<<"chi2 "<<chi2<<endl;
		// 0+dphi
		theta3=theta;
		if(theta3 < 0 or theta3 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 3: " << theta3 << endl;
			}
		phi3=phi+dphi;
		if(phi3 < -3.1415926 or phi3 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 3: " << phi3 << endl;
			}
		x3 = r *sin(theta3)*cos(phi3);
		y3 = r *sin(theta3)*sin(phi3);
		z3 = r *cos(theta3);
//		cout << "theta,phi,x,y,z=" << theta3 << "," << phi3 << "," << x3 << "," << y3 << "," << z3 << "," << endl;
		chi3 = funchi(x3,y3,z3,xs,ys,zs,ts,t);
//		cout<<"chi3 "<<chi3<<endl;
		// 0-dphi
		theta4=theta;
		if(theta4 < 0 or theta4 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 4: " << theta4 << endl;
			}
		phi4=phi-dphi;
		if(phi4 < -3.1415926 or phi4 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 4: " << phi4 << endl;
			
		x4 = r *sin(theta4)*cos(phi4);
		y4 = r *sin(theta4)*sin(phi4);
		z4 = r *cos(theta4);
		chi4 = funchi(x4,y4,z4,xs,ys,zs,ts,t);

//		cout<<"chi4 "<<chi4<<endl;
//ciclo tentativi : esci con criterio tutti punti vicini chi magg
	while ( chi1<chi or chi2<chi or chi3<chi or chi4<chi ){
//		chi = chi_temp;
		k++;

		// confronto
		chi_temp = chi;  
		theta_temp = theta;
		phi_temp = phi;
		if (chi1<chi_temp) {
			chi_temp = chi1;  
			theta_temp=theta1; 
			phi_temp=phi1;
				   }    
		if (chi2<chi_temp) {
			chi_temp = chi2;  
			theta_temp=theta2; 
			phi_temp=phi2;
				   }
		if (chi3<chi_temp) {
			chi_temp = chi3;  
			theta_temp=theta3; 
			phi_temp=phi3;
				   }
		if (chi4<chi_temp) {
			chi_temp = chi4;
			theta_temp=theta4;
			phi_temp=phi4;
				   }
//conserva chi minimo alla fine di ogni confronto
		chi= chi_temp; 
		theta=theta_temp; 
		phi=phi_temp;
//		if(k<500){
			cout<<"k, theta, phi = "<<k<< ", " << theta << ", " << phi<<endl;
//			}	
		dtheta = sin(theta)*dcostheta;
		// 0+dtheta
		theta1=theta+dtheta;
		if(theta1 < 0 or theta1 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 1: " << theta1 << endl;
			}
		phi1=phi;
		if(phi1 < -3.1415926 or phi1 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 1: " << phi1 << endl;
			}
		x1 = r *sin(theta1)*cos(phi1);
		y1 = r *sin(theta1)*sin(phi1);
		z1 = r *cos(theta1);
		chi1 = funchi(x1,y1,z1,xs,ys,zs,ts,t);
//		cout<<"chi1 "<<chi1<<endl;
		//0-dtheta
		theta2=theta-dtheta;
		if(theta2 < 0 or theta2 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 2: " << theta2 << endl;
			}
		phi2=phi;
		if(phi2 < -3.1415926 or phi2 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 2: " << phi2 << endl;
			}
		x2 = r *sin(theta2)*cos(phi2);
		y2 = r *sin(theta2)*sin(phi2);
		z2 = r *cos(theta2);
		chi2 = funchi(x2,y2,z2,xs,ys,zs,ts,t);
//		cout<<"chi2 "<<chi2<<endl;
		// 0+dphi
		theta3=theta;
		if(theta3 < 0 or theta3 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 3: " << theta3 << endl;
			}
		phi3=phi+dphi;
		if(phi3 < -3.1415926 or phi3 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 3: " << phi3 << endl;
			}
		x3 = r *sin(theta3)*cos(phi3);
		y3 = r *sin(theta3)*sin(phi3);
		z3 = r *cos(theta3);
		chi3 = funchi(x3,y3,z3,xs,ys,zs,ts,t);
//		cout<<"chi3 "<<chi3<<endl;
		// 0-dphi
		theta4=theta;
		if(theta4 < 0 or theta4 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:theta 4: " << theta4 << endl;
			}
		phi4=phi-dphi;
		if(phi4 < -3.1415926 or phi4 > 3.1415926)
			{
			cout << "Oh, oh...mi è sembrato di vedere un errore:phi 4: " << phi4 << endl;
			}
		x4 = r *sin(theta)*cos(phi4);
		y4 = r *sin(theta)*sin(phi4);
		z4 = r *cos(theta);
		chi4 = funchi(x4,y4,z4,xs,ys,zs,ts,t);
//		cout<<"i vari theta al passaggio "<<chi4<<endl;

		}
	p[0]=r*sin(theta)*cos(phi);
	p[1]=r*sin(theta)*sin(phi);
	p[2]=r*cos(theta); 
			}
	}


// funzione calcola chi( x,y,z )
double funchi(double x, double y, double z, double *xs, double *ys, double *zs, double *ts, double t)
	  {
	   double chi_v = 0;
	   double c = 299792.458;
	   double xx; double yy; double zz; double tt;
//		cout << "Nel calcolo del chi abbiamo:" <<endl;
//		cout << "x = " << x << "y " << y << "z = " << z << endl;
	   for (int i = 0; i < n; i++) { //n satelliti
//	     cout << "Satellite " << i+1 << " " << xs[i] << " " << ys[i] << " " << zs[i] << " " << endl; 
	     xx = (xs[i] -x)*(xs[i] -x);
	     yy = (ys[i] -y)*(ys[i] -y);
	     zz = (zs[i] -z)*(zs[i] -z);
	     tt = (ts[i] -t)*(ts[i] -t);
	     chi_v = (chi_v + pow(sqrt(xx + yy + zz)- sqrt(c*c*tt),2));
	   }
	   return chi_v;
	  }


// funzione coordinate sferiche (r,theta,phi)  -> x y z 
