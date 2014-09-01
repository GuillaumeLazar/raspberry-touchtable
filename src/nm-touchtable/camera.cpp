#include "camera.h"

bool initCamera()
{
    int size_w = 320;
    int size_h = 240;

    cap = VideoCapture(-1);

    if (!cap.isOpened())
    {
        cout << "ERRO Camera cannot be opened" << endl;


        return false;
    }else{
        printf("Camera is opened\n");
    }

    cap.set(CV_CAP_PROP_FRAME_WIDTH, size_w);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, size_h);

    return true;
}

bool initFakeCamera()
{
    frame = imread("fakeCamera.jpg");
    return frame.cols > 0;
}

bool acqFrameFromCamera()
{
  bool isReadOk = false;

  if (cap.isOpened()){
      isReadOk = cap.read(frame);

      if (!isReadOk)
      {
          cout << "Cannot read a frame from camera" << endl;
      }else{
        //printf("New frame!\n");
      }
  }else{

      isReadOk = frame.cols > 0;
      if (!isReadOk)
      {
          cout << "Cannot read a frame from file" << endl;
      }else{
        //printf("New frame!\n");
      }

  }

  return isReadOk;
}

void processFrame(int, void*)
{        
  // original to grayscale
  cvtColor(frame, frameGray, CV_BGR2GRAY);
  
  // horizontal flip
  flip(frameGray, frameGray, 1);
  
  // extract roi
  //Rect roi = Rect(90, 58, 156, 96);

  frameROI = frameGray(roi).clone();
  //cvtColor(frameROI, frameCrop, CV_GRAY2RGB);
  //resize(frameCrop, frameCrop, Size(320, 240));
  
  //imwrite("frameGray.jpg", frameGray);
  
  // binary
  adaptiveThreshold(frameROI, frameROI, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 3, 5);
  
  // dilate + erode
  dilate(frameROI, frameROI, dummyMat, Point(-1, -1), 4);
  erode(frameROI, frameROI, dummyMat, Point(-1, -1), 2);
  
  // resize
  resize(frameROI, frameROI, Size(320, 240));
  
  // find contours

  frameContours = frameROI;//.clone();
  findContours(frameContours, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
  vector<vector<Point> > contours_poly( contours.size() );
  //vector<Rect> boundRect( contours.size() );
  
  boundCount = contours.size();
  boundRect = vector<Rect>(contours.size());
  
  for( int i = 0; i < contours.size(); i++ )
  {
    approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
    boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    //printf("[%d] x:y=%d:%d  w:h=%d:%d\n", i, boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height);
    //minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
  }
}

vector<Rect>* getBoundRect()
{
  return &boundRect;
}

int getBoundCount()
{
  return boundCount;
}

Mat getFrame()
{
    return frame;
}

Mat getFrameROI()
{
    //return frameROI;
    return frameCrop;
}
