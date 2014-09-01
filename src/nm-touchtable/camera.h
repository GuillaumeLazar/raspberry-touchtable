#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

bool initCamera();
bool initFakeCamera();
bool acqFrameFromCamera();
void processFrame(int, void*);
vector<Rect>* getBoundRect();
int getBoundCount();
Mat getFrame();
Mat getFrameROI();

static VideoCapture cap;
static Mat frame;
static Mat frameGray;
static Mat frameROI;
static Mat frameBlur;

static Mat frameCrop;
static vector<Rect> boundRect;
static int boundCount = 0;
static Rect roi = Rect(92, 65, 148, 95);

static Mat dummyMat;
static vector<vector<Point> > contours;
static vector<Vec4i> hierarchy;
static Mat frameContours;

#endif


