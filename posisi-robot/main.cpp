#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;
using namespace chrono;

string toString(double value) {
    ostringstream out;

    if (value == round(value)){
        out << fixed << setprecision(0) << value;
        return out.str();
    }

    out << fixed << setprecision(2) << value;
    return out.str();
}

float distance(float a, float b){
    return sqrt(a*a + b*b);
}

int main(){

    VideoCapture cap("../Video-asli.avi");

    Mat frame;
    Mat HSV;
    Mat thres;

    vector<vector<Point>> contours;

    int h[2] = {100,255};
    int s[2] = {170,255};
    int v[2] = {200,255};

    namedWindow("trackbar");

    createTrackbar("h min", "trackbar", &h[0], 255);
    createTrackbar("s min", "trackbar", &s[0], 255);
    createTrackbar("v min", "trackbar", &v[0], 255);
    createTrackbar("h max", "trackbar", &h[1], 255);
    createTrackbar("s max", "trackbar", &s[1], 255);
    createTrackbar("v max", "trackbar", &v[1], 255);

    Point2f center;
    Moments m;
    float radius = 0;
    vector<float> posAwal;
    float posBefore[2] = {0,0};
    steady_clock::time_point tawal = steady_clock::now();

    //frame = imread("/home/abrar/Documents/robotik/P2/posisi/foto.png");

    while (true)
    {
        cap >> frame;

        cvtColor(frame, HSV, COLOR_RGB2HSV);
        inRange(HSV,Scalar(h[0], s[0], v[0]),Scalar(h[1], s[1], v[1]),thres);

        findContours(thres, contours, RETR_TREE, CHAIN_APPROX_NONE);

        if (contours.size()>0){
            minEnclosingCircle(contours[0], center, radius);
            m = moments(contours[0]);
            drawContours(frame, contours, -1, Scalar(255,0,0), 2);
            circle(frame, center, cvRound(radius), Scalar(0,255,0), 2);

            if (posAwal.size() == 0){
                posAwal.push_back(m.m10/m.m00);
                posAwal.push_back(m.m01/m.m00);
            }

            double x = cvRound(posAwal[0]-(m.m10/m.m00));
            double y = cvRound((m.m01/m.m00)-posAwal[1]);

            Point l1((1280/2),(720/2));
            Point l2((m.m10/m.m00), (m.m01/m.m00));
            line(frame, l1, l2, Scalar(255,0,0));

            //float x = round((posAwal[0]-center.x)*100);
            //float y = round((center.y-posAwal[1])*100);
            
            if (m.m00 != 0){
                Point tKoor(30,30);
                Point sKoor(30,60);
                Point jKoor(30, 90);
                putText(frame, "Posisi: (" + toString(x/10) + ", " + toString(y/10) + ")", tKoor, QT_FONT_NORMAL, 1, Scalar(0,0,255), 1);
                //cout<<posBefore[0]<<", "<<posBefore[1]<<endl;
                //cout<<(x/10)<<", "<<(y/10)<<endl;

                steady_clock::time_point tnow = steady_clock::now();
                nanoseconds dur = tnow - tawal;
                tawal = tnow;

                float speed = (distance(((x/10) - posBefore[0]), ((y/10) - posBefore[1])))/(dur.count()/pow(10,9));
                //cout<<(dur.count()/pow(10,9))<<endl;
                //cout<<speed<<endl;

                posBefore[0] = x/10;
                posBefore[1] = y/10;

                putText(frame, "Speed: " + toString(speed)+"m/s", sKoor, QT_FONT_NORMAL, 1, Scalar(0,0,255), 1);
                //cout<<toString(x/10) + ", " + toString(y/100)<<endl;

                float jarak = distance(((posAwal[0]-(1280/2)) - x), ((720/2) - posAwal[1]) - y)/10;
                putText(frame, "distance: " + toString(jarak) +"m", jKoor, QT_FONT_NORMAL, 1, Scalar(0,0,255), 1);

                
            }
        }



        imshow("video", frame);
        //imshow("hsv", HSV);
        //imshow("thres", thres);

        if(waitKey(1) == 'q'){
            break;
        }
    }
    

    return 0;
}