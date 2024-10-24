
# IRIS Internship

This project is an internship assignment for the IRIS Robotics Research Team.

> Name: Abrar Rafi Dwianto <br>
> NRP: 5024241046 <br>
> Departemen: Computer Engineering

## Project Details
This project consists of two parts:

1. [Detect objects based on color and estimate the distance of the object.](##Object-Detection)
2. [Detecting the position of the robot and it's distance from the ball.](##Robot-Position)

## Object Detection
### How It Works
  - **Frame Processing:** Using OpenCV, we process the camera feed frame by frame.
  - **Color Space Conversion:** Convert the color format from RGB to YUV or HSV.
  - **Thresholding:** Transform the YUV/HSV format to a thresholded image to isolate the desired object color.
  - **Calibration:** Adjust the threshold to precisely capture the desired object's color.
  - **Contour Detection:** Identify contours within the thresholded image.
  - **Circle Creation:** Draw circles based on the detected contours.
  - **Data Collection:** Gather distance and radius data to feed into Archnoid polynomial regression for equation derivation.
  - **Distance Calculation:** Calculate the object's distance by inputting the circle's radius into the derived equation.

### How To Use
- Go to the project
  ```bash
  cd object-detection
  ```
- Make build directory
  ```bash
  mkdir build
  cd build
  ```
- run cmake, make, and run project
  ```bash
  cmake ..
  make
  ./object-detection
  ```

### Customization
  - Calibration
    - There’s a trackbar you can adjust to calibrate the color detection for different objects. Don’t forget to uncomment ```imshow("thres", thres);``` and ```namedWindow("trackbar");``` so you can see the thresholded image and fine-tune it using trackbar.
    - If you’re struggling, try changing the color format in ```cvtColor(frame, hsv, COLOR_RGB2HSV);``` from ```COLOR_RGB2HSV``` to ```COLOR_RGB2YUV.```
  - Sampling
    - Uncomment ```cout<<radius[i]<<endl;``` to display the radius in the console.
    - Measure and observe radius changes for your new object's distance.
    - Use the collected data to derive the new equation.
    - Update Function: Modify the calcDistance function with your new equation:
    ```cpp
    double calcDistance(float r) {
      double result = 0;
      result = // your new equation
      return result;
    }

## Robot Position
This project calculates the position of a moving robot on a Cartesian plane, with the point (0,0) as the initial position of the robot. The position is calculated relatively using the position of the ball in the frame. One pixel is assumed to be equivalent to 10 cm, and the ball's scale is ignored.

### How It Works
  - Using OpenCV to process video frames.
  - Converting the video color format to HSV/YUV.
  - Obtaining the thresholded image of the ball from the converted color format.
  - Detecting contours in the thresholded image.
  - Calculating moments of the contours to get the centroid, which represents the current position of the ball.
  - Determining the robot's position by mirroring the ball's position. If the ball moves down, the robot moves up and vice versa, with ```Xrobot = X0ball - Xball``` and ```Yrobot = Yball−Y0ball```
  - After obtaining the robot's position and knowing the initial position of the ball, we can calculate other parameters such as distance and speed using standard distance and speed formulas.

### How To Use
- Go to the project
  ```bash
  cd robot-position
  ```
- Make build directory
  ```bash
  mkdir build
  cd build
  ```
- run cmake, make, and run project
  ```bash
  cmake ..
  make
  ./robot-position
  ```
