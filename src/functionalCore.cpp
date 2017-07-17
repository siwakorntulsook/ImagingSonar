#include "functionalCore.hpp"

FunctionalCore::FunctionalCore()
{
}
FunctionalCore::~FunctionalCore()
{
}
void FunctionalCore::cv_SpeedChange( int v, void *ptr){
	FunctionalCore *that = (FunctionalCore *)ptr;
	that->img.SetSoundSpeedOverride(that->soundspeed);
}
void FunctionalCore::cv_ScaleChange( int v, void *ptr){
	FunctionalCore *that = (FunctionalCore *)ptr;
	that->scale = v;
}
void cv_OffSetChange( int v, void* ptr)
{
	FunctionalCore *that = (FunctionalCore *)ptr;
	that->tiltoffset = v;
}
void FunctionalCore::imageshow(cv::Mat img, std::string s){
	cv::imshow(s, img);
}
// void FunctionalCore::negative(cv::Mat img){

// }
cv::Mat FunctionalCore::GetMag(BVTSDK::MagImage mag ,int height ,int width){

	height = mag.GetHeight();
	width = mag.GetWidth();
	cv::Mat mag_image(height ,width , CV_16UC1 , mag.GetBits());
	// imageshow(mag_image , "SoundSpeedTesting");	
	
	return mag_image;
}
cv::Mat FunctionalCore::GetColor(BVTSDK::ColorImage cimg,int height ,int width){

	height = cimg.GetHeight();
	width = cimg.GetWidth();
		
	cv::Mat color_img(height , width , CV_8UC4 , cimg.GetBits());
	// imageshow(color_img , "Mapper");
	return color_img;
}
int FunctionalCore::CVCheckKey(int waittime){
	int interruptKey = 0;
	int checkKey = 1;
	interruptKey = cv::waitKey(waittime);
	if( interruptKey == 27 ){
		// cv::destroyAllWindows();
		checkKey = 0;
	}
	return checkKey;
}
// void FunctionalCore::ConnectCV(cv::Mat image){
// 	FunctionalCV CVCore = FunctionalCV();
// 	cv::Mat postimg = CVCore.debug(image , this->scale);
// }
void FunctionalCore::InitialImageAnalytic(){
	cv::namedWindow("Image" , cv::WINDOW_NORMAL);
	cv::namedWindow("GraphResult" , cv::WINDOW_NORMAL);
	this->soundspeed = 1550;
	this->scale = 15000;
	
	cv::createTrackbar("Sound Speed" , "SoundSpeedTesting" , &soundspeed , 2000 , cv_SpeedChange , this);
	cv::createTrackbar("Scale" , "SoundSpeedTesting" , &scale , 65535 , cv_ScaleChange , this);
	sonar.Open("FILE" , fullPath);
	BVTSDK::Head head = sonar.GetHead(0);
	img.SetHead(head);

	BVTSDK::ImageFilterFlags::Enum f = BVTSDK::ImageFilterFlags::None;
	img.SetImageFilterFlags(f);

	BVTSDK::ColorMapper map;
	map.Load(mapperPath);
	// map.SetAutoMode(0);
	FunctionalCV CVCore = FunctionalCV();
	
}

void FunctionalCore::InitialImageProcessing(){
	cv::namedWindow("SoundSpeedTesting" , cv::WINDOW_NORMAL);
	cv::namedWindow("CVResult" , cv::WINDOW_NORMAL);
	
	this->soundspeed = 1550;
	this->scale = 15000;
	
	cv::createTrackbar("Sound Speed" , "SoundSpeedTesting" , &soundspeed , 2000 , cv_SpeedChange , this);
	cv::createTrackbar("Scale" , "SoundSpeedTesting" , &scale , 65535 , cv_ScaleChange , this);

	sonar.Open("FILE" , fullPath);
	BVTSDK::Head head = sonar.GetHead(0);
	img.SetHead(head);

	BVTSDK::ImageFilterFlags::Enum f = BVTSDK::ImageFilterFlags::None;
	img.SetImageFilterFlags(f);

	BVTSDK::ColorMapper map;
	map.Load(mapperPath);
	// map.SetAutoMode(0);
	FunctionalCV CVCore = FunctionalCV();

	while(CVCheckKey(30)){
		BVTSDK::Ping ping = head.GetPing(-1);
		BVTSDK::MagImage mag = img.GetImageRTheta(ping);

		int height = mag.GetHeight();
		int width = mag.GetWidth();

		BVTSDK::ColorImage cimg = map.MapImage(mag);
		cv::Mat original = GetMag(mag ,height ,width);
		cv::Mat color = GetColor(cimg , cimg.GetHeight() , cimg.GetWidth());
		cv::Mat cvmag = CVCore.debug(original, color ,this->scale);

		// ConnectCV(cvmag);
		
		original.convertTo(original , CV_8UC1 , 255.0/this->scale);
		imageshow(original , "SoundSpeedTesting");
		imageshow(cvmag , "CVResult");
		// showcolor(cimg , height , width );
    }
}
// void FunctionalCore::LiveSonar(){

	
// 	this->tiltoffset = 0;
// 	cv::namedWindow("Mapper" , cv::WINDOW_NORMAL);
// 	cv::createTrackbar("TiltOffset" , "Mapper" , &tiltoffset , 50 , cv_ScaleChange , this);

// 	sonar.Open("NET" , "192.168.1.45");
// 	BVTSDK::Head head = sonar.GetHead(0);
// 	BVTSDK::ColorMapper map;
// 	BVTSDK::ImageFilterFlags::Enum f = BVTSDK::ImageFilterFlags::None;
// 	// img.SetImageFilterFlags(f);
	
// 	map.Load(mapperPath);
// 	head.SetRange(2,10);
// 	img.SetHead(head);
	
// 	int pauseKey = 1;
// 	int interruptKey = 0;
// 	std::cout << "Enter CV Loop" << std::endl;
		
// 	while(CVCheckKey(30)){

// 		BVTSDK::Ping ping = head.GetPing(-1);
// 		BVTSDK::MagImage mag = img.GetImageXY(ping);
		
// 		int height = mag.GetHeight();
// 		int width = mag.GetWidth();	
		
// 		BVTSDK::ColorImage cimg = map.MapImage(mag);
// 		cv::Mat color_img = GetColor(cimg , height , width );
// 	}
// }
// void FunctionalCore::loopRun(){

// 	this->soundspeed = 1568;
// 	this->scale = 1000;

// 	cv::namedWindow("SoundSpeedTesting" , cv::WINDOW_NORMAL);
// 	cv::namedWindow("Mapper" , cv::WINDOW_NORMAL);
	
// 	cv::createTrackbar("Sound Speed" , "SoundSpeedTesting" , &soundspeed , 2000 , cv_SpeedChange , this);
// 	cv::createTrackbar("Scale" , "SoundSpeedTesting" , &scale , 65535 , cv_ScaleChange , this);

// 	sonar.Open("FILE" , fullPath);

// 	BVTSDK::Head head = sonar.GetHead(0);
	
// 	img.SetHead(head);
// 	// BVTSDK::Imag
// 	BVTSDK::ImageFilterFlags::Enum f = BVTSDK::ImageFilterFlags::None;
// 	img.SetImageFilterFlags(f);

// 	BVTSDK::ColorMapper map;
// 	map.Load(mapperPath);
// 	// map.SetAutoMode(0);
	
// 	int pingNum = head.GetPingCount();
// 	int pauseKey = 1;
// 	int interruptKey = 0;



// 	while(CVCheckKey(30)){
// 		BVTSDK::Ping ping = head.GetPing(-1);
// 	 	// ping.SetPositionerRotations(30,30,0);

// 		BVTSDK::MagImage mag = img.GetImageRTheta(ping);
// 		// float x = img.GetNoiseThreshold();

// 		int height = mag.GetHeight();
// 		int width = mag.GetWidth();
// 		// std::cout << x << std::endl;

// 		BVTSDK::ColorImage cimg = map.MapImage(mag);
// 		cv::Mat cvmag = GetMag(mag ,height ,width);

// 		// medianBlur(this->cvmag , this->cvmag , 3);

// 		cvmag.convertTo(cvmag , CV_8UC1 , 255.0/this->scale);
// 		// bitwise_not(this->cvmag , this->cvmag);

// 		imageshow(cvmag , "SoundSpeedTesting");
// 		cv::Mat color_img = GetColor(cimg , height , width );

//     }
// }