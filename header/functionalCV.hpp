#ifndef FUNCTIONALCV_H
#define FUNCTIONALCV_H

#include <opencv2/opencv.hpp>
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

class FunctionalCV
{
public:
    FunctionalCV();
    ~FunctionalCV();
	cv::Mat debug(cv::Mat img , cv::Mat cimg , int scale);
	cv::Mat FilterThresholdMorp(cv::Mat img , int scale);
	void AnalyticRootGraph(cv::Mat img ,int row ,int startCol ,int endCol);
private:
};


#endif