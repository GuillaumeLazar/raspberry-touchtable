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

    isFakeMode = false;

    return true;
}

bool initFakeCamera()
{
    frame = imread("frame.jpg");
    printf("LOAD frame.jpg\n");

    isFakeMode = true;

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
        frameCpt++;
        //printf("frameCpt = %d\n", frameCpt);
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


    int BLUR_SIZE = 1;           // 3
    double BLUR_SIGMA = 0;     //1.5
    int THRESHOLD_SIZE = 15;     //15  //10 ko
    int THRESHOLD_C = -8;        //-8


    // original to grayscale
    cvtColor(frame, frameGray, CV_BGR2GRAY);

    // horizontal flip
    flip(frameGray, frameGray, 1);

    // extract roi
    frameROI = frameGray(roi).clone();

    //DEBUG
    resize(frameROI, frameDebugRoi, Size(320, 240));

    //printf("isBalanceDone  = %d\n", isBalanceDone);
    if (!isBalanceDone ){
        if (!isFakeMode){

          char filename[100];
          //sprintf(filename, "frame_balance_%03d.jpg", frameCpt);
          sprintf(filename, "frame_balance.jpg", frameCpt);

          printf("SAVE %s\n", filename);
          imwrite(filename, frame);


          GaussianBlur(frameROI, frameBalance, cv::Size(BLUR_SIZE, BLUR_SIZE), BLUR_SIGMA, BLUR_SIGMA);

        }else{
          Mat balanceFrame = imread("frame_balance.jpg");
          cvtColor(balanceFrame, balanceFrame, CV_BGR2GRAY);
          flip(balanceFrame, balanceFrame, 1);
          Mat balanceFrameROI = balanceFrame(roi).clone();

          GaussianBlur(balanceFrameROI, frameBalance, cv::Size(BLUR_SIZE, BLUR_SIZE), BLUR_SIGMA, BLUR_SIGMA);
          printf("LOAD frame_balance.jpg\n");
        }

        isBalanceDone = true;
    }

    if (frameCpt == 50){
        imwrite("frame.jpg", frame);
        printf("SAVE frame.jpg\n");
    }

    GaussianBlur(frameROI, frameROI, cv::Size(BLUR_SIZE, BLUR_SIZE), BLUR_SIGMA, BLUR_SIGMA);
    absdiff(frameROI, frameBalance, frameROI);

    // DEBUG
    resize(frameROI, frameDebugBalance, Size(320, 240));

    // binary
    adaptiveThreshold(frameROI, frameROI, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, THRESHOLD_SIZE, THRESHOLD_C);
    //threshold(frameROI, frameROI, 150, 255, THRESH_BINARY);

    // dilate + erode
    //erode(frameROI, frameROI, dummyMat, Point(-1, -1), 1);
    //dilate(frameROI, frameROI, dummyMat, Point(-1, -1), 1);

    // DEBUG
    resize(frameROI, frameDebug, Size(320, 240));

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
    return frameDebugRoi;
    //return frameCrop;
}


Mat getFrameDebug()
{
    return frameDebug;
}

Mat getFrameDebugBalance()
{
    return frameDebugBalance;
}
