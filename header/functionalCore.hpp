#ifndef FUNCTIONALCORE_H
#define FUNCTIONALCORE_H


// include local LIBS
#include "functionalCV.hpp"

// include functionLIBS
#include <stdlib.h>
#include <bvt_sdk.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

// include ROOT_CERN Test Environment
#include <root/TApplication.h>
#include <root/TMath.h>
#include <root/TGraph2D.h>
#include <root/TGraph.h>
#include <root/TFrame.h>
#include <root/TRandom.h>
#include <root/TStyle.h>
#include <root/TCanvas.h>
#include <root/TF2.h>
#include <root/TH1.h>

class FunctionalCore
{
	public:
        FunctionalCore();
        ~FunctionalCore();
    public:

    	void loopRun();
        void LiveSonar();
        void ConnectCV(cv::Mat image);
        void InitialImageProcessing();
    	
    private:
        void imageshow(cv::Mat img , std::string s);
    	void imagingRead();
        int CVCheckKey(int waittime);

        cv::Mat GetMag(BVTSDK::MagImage mag , int height , int width);
        cv::Mat GetColor(BVTSDK::ColorImage cimg , int height , int width);

    	static void cv_SpeedChange( int , void*) ;
        static void cv_ScaleChange( int , void*) ;
    	static void cv_OffSetChange( int , void*) ;
        
        BVTSDK::Sonar sonar;
    public:
        int soundspeed;
        int scale;
        int tiltoffset;
        BVTSDK::ImageGenerator img;
        FunctionalCV CVCore;
        std::string rootPath = "/home/turk/Thesis/";
        std::string dataPath = rootPath + "dat/";
        std::string mapperPath = rootPath + "bvtsdk/colormaps/copper.cmap";
        std::string fileName = "Apr_25_2017_234905_4.son";
        std::string fullPath = dataPath + fileName;

    private:
        
        BVTSDK::ColorMapper map;
};

#endif
