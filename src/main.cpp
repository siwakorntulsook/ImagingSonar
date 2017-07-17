#include "functionalCore.hpp"
void graph() {
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
   // c1->SetGrid();
   const Int_t n = 20;
   Double_t x[n], y[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.1;
     y[i] = 10*sin(x[i]+0.2);
     printf(" i %i %f %f \n",i,x[i],y[i]);
   }
   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("a simple graph");
   gr->GetXaxis()->SetTitle("X title");
   gr->GetYaxis()->SetTitle("Y title");
   gr->Draw("ACP");
   // TCanvas::Update() draws the frame, after which one can change it

}

int main(int argc, char **argv){
	FunctionalCore f = FunctionalCore();
	// f.ConnectCV();	
	TApplication theApp("tapp", &argc, argv);
	f.InitialImageProcessing();

	// graph();
   	theApp.Run();
	return 0;
}
// TCanvas* graph2dfit()
// {
//    TCanvas *c1 = new TCanvas("c1","Graph2D example",0,0,1000,800);
//    Double_t P = 5.;
//    Int_t npx  = 100 ;
//    Int_t npy  = 100 ;
//    Double_t x = -P;
//    Double_t y = -P;
//    Double_t z;
//    Int_t k = 0;
//    Double_t dx = (2*P)/npx;
//    Double_t dy = (2*P)/npy;
//    TGraph2D *dt = new TGraph2D(npx*npy);
//    dt->SetNpy(41);
//    dt->SetNpx(40);
//    for (Int_t i=0; i<npx; i++) {
//       for (Int_t j=0; j<npy; j++) {
//          z = sin(sqrt(x*x+y*y))+1;
//          dt->SetPoint(k,x,y,z);
//          k++;
//          y = y+dy;
//       }
//       x = x+dx;
//       y = -P;
//    }
//    gStyle->SetPalette(1);
//    dt->SetMarkerStyle(20);
//    dt->Draw("pcol");
//    return c1;
// }
