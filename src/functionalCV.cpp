#include "functionalCV.hpp"

FunctionalCV::FunctionalCV()
{
}
FunctionalCV::~FunctionalCV()
{
}
void FunctionalCV::AnalyticRootGraph(cv::Mat img ,int row ,int startCol ,int endCol){
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
   // c1->SetGrid();
   const Int_t n = 1000;
   Double_t x[n], y[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.1;
     y[i] = 10*sin(x[i]+0.2);
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

	c1->Print("name.png");
   // TCanvas::Update() draws the frame, after which one can change it
}
cv::Mat FunctionalCV::FilterThresholdMorp(cv::Mat img ,int scale)
{
	cv::Mat dst;
	cv::Mat MorpKernal;


	cv::GaussianBlur(img,dst, cv::Size(5,5) , 0 , 0);
	
	dst.convertTo(dst , CV_8UC1 , 255.0/scale);
	imshow("BlurScale",dst);

	cv::threshold(dst , dst, 10 , 255,cv::THRESH_BINARY);
	imshow("Segment",dst);
	MorpKernal = cv::getStructuringElement(cv::MORPH_RECT , cv::Size(3	,3));
	cv::morphologyEx( dst , dst , cv::MORPH_OPEN , MorpKernal , cv::Point(-1,-1) , 2);
	imshow("MorpOpen",dst);
	cv::morphologyEx( dst , dst , cv::MORPH_CLOSE , MorpKernal , cv::Point(-1,-1) , 2);
	imshow("MorpClose",dst);

	return dst;

}
cv::Mat FunctionalCV::debug(cv::Mat img ,cv::Mat cimg , int scale)
{

	// cv::namedWindow("Debug" , cv::WINDOW_NORMAL);
	cv::namedWindow("BlurScale" , cv::WINDOW_NORMAL);
	cv::namedWindow("Segment" , cv::WINDOW_NORMAL);
	cv::namedWindow("MorpOpen" , cv::WINDOW_NORMAL);
	cv::namedWindow("MorpClose" , cv::WINDOW_NORMAL);
	
	cv::RNG rng(12345);
	cv::RotatedRect rect;
	
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Mat dst = FilterThresholdMorp(img, scale);
	cv::findContours( dst , contours , hierarchy , CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE );
	// std::cout << contours.size() << std::endl;

	int largest_index = 0;
	double largest_area = 0;
	if (contours.size() != 0){
		for(int i = 0 ; i < contours.size() ; i++){
			double area = cv::contourArea(contours[i]);
			// std::cout << area << std::endl;
			if( area > largest_area )
	        {
	            largest_area = area;
	            largest_index = i;
				// std::cout << largest_area << std::endl;
				// std::cout << largest_index << std::endl;
	        }
		}

	    rect = cv::minAreaRect(cv::Mat(contours[largest_index]));
		// std::cout << largest_index << std::endl;
		// cv::Mat drawing = cv::Mat::zeros( img.size(), CV_8UC3 );
		// for( int i = 0; i< contours.size(); i++ )
	 //    {
		cv::Scalar color = cv::Scalar( 0, 0, 0 );
		// cv::drawContours( cimg, contours, largest_index, color, 2, 8, hierarchy, 0, cv::Point() );
		
		cv::Point2f rect_points[4]; 
		rect.points( rect_points );
		for( int j = 0; j < 4; j++ ){
			cv::line( cimg, rect_points[j], rect_points[(j+1)%4], color, 3, 8 );
		}

		// }
		// cv::Canny(res,dst,50,150,3);
	}
	return cimg;
}