#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

using namespace cv;
using namespace std;

double calcDistance(float r){
    double result = 0;

    result = (1.5132851736838930*pow(10,2))+(-2.1225457381657278*r)+(1.4383492118754407*pow(10,-2)*pow(r,2))+(-4.7379848523256183*pow(10,-5)*pow(r,3))+(6.1464904018921641*pow(10,-8)*pow(r,4));
    return result;
}

int main(){
    Mat frame;
    Mat hsv;
    Mat thres;
    vector<vector<Point>> contours;

    int h[2] = {111,255};
    int s[2] = {132,255};
    int v[2] = {0,255};
    int area = 15;

    //namedWindow("trackbar");

    createTrackbar("h min", "trackbar", &h[0], 255);
    createTrackbar("s min", "trackbar", &s[0], 255);
    createTrackbar("v min", "trackbar", &v[0], 255);
    createTrackbar("h max", "trackbar", &h[1], 255);
    createTrackbar("s max", "trackbar", &s[1], 255);
    createTrackbar("v max", "trackbar", &v[1], 255);
    createTrackbar("area", "trackbar", &area, 100);

    VideoCapture cap(0);

    if (!cap.isOpened()){
        return -1;
    }

    while(true){
        cap >> frame;
        cvtColor(frame, hsv, COLOR_RGB2HSV);
        inRange(hsv, Scalar(h[0],s[0],v[0]), Scalar(h[1],s[1],v[1]), thres);
        findContours(thres, contours, RETR_TREE, CHAIN_APPROX_NONE);
        
        vector<Point2f> center(contours.size());
        vector<float> radius(contours.size(), 0); 
        vector<Moments> m(contours.size());

        if (contours.size()>0){
            for (int i=0; i<contours.size(); i++){
                minEnclosingCircle(contours[i], center[i], radius[i]);

                if (radius[i]>area){
                    //cout<<radius[i]<<endl;
                    Point tpos(static_cast<int>(center[i].x-radius[i]), static_cast<int>(center[i].y+radius[i]));
                    circle(frame, center[i], cvRound(radius[i]), Scalar(0,255,0), 2);
                    putText(frame, to_string(calcDistance(radius[i])) + " cm", tpos, QT_FONT_NORMAL, 1, Scalar(0,0,255), 2);
                }
            }

        }
        
        imshow("video", frame);
        //imshow("thres", thres);
        
        if (waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}