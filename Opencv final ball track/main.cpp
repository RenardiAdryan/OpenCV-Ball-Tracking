#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
using namespace cv;
using namespace std;
int h,j;
int main() {

    VideoCapture capWebcam(0);		// declare a VideoCapture object to associate webcam, 0 means use 1st (default) webcam
    //VideoCapture capWebcam_1(1);
    if (capWebcam.isOpened() == false)	 //  To check if object was associated to webcam successfully
    {
        cout << "error: Webcam connect unsuccessful\n";	// if not then print error message
        return(0);												// and exit program
    }

    Mat imgOriginal;		        // Input image
    Mat hsvImg;				// HSV Image
    Mat threshImg;			// Thresh Image

    vector<Vec3f> v3fCircles;		// 3 element vector of floats, this will be the pass by reference output of HoughCircles()

    char charCheckForEscKey = 0;

    int lowH = 139;							// Set Hue
    int highH = 255;

    int lowS = 86;							// Set Saturation
    int highS = 255;

    int lowV = 114;							// Set Value
    int highV = 255;
    // HUE for YELLOW is 21-30.
    // Adjust Saturation and Value depending on the lighting condition of the environment as well as the surface of the object.

    while (charCheckForEscKey != 27 && capWebcam.isOpened()) {				// until the Esc is pressed or webcam connection is lost
        bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);		// get next frame

        if (!blnFrameReadSuccessfully || imgOriginal.empty()) {				// if frame read unsuccessfully
            std::cout << "error: frame can't read \n";						// print error message
            break;															// jump out of loop
        }

        cvtColor(imgOriginal, hsvImg, CV_BGR2HSV);						// Convert Original Image to HSV Thresh Image

        inRange(hsvImg, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), threshImg);

        GaussianBlur(threshImg, threshImg, cv::Size(3, 3), 0);			//Blur Effect
        dilate(threshImg, threshImg, 0);								// Dilate Filter Effect
        erode(threshImg, threshImg, 0);									// Erode Filter Effect

        // fill circles vector with all circles in processed image
        HoughCircles(threshImg,v3fCircles,CV_HOUGH_GRADIENT,2,threshImg.rows / 4,100,50,10,800);  // algorithm for detecting circles

        for (int i = 0; i < v3fCircles.size(); i++) {						// for each circle
	
	h = 150 - v3fCircles[i][2];
	j = (h*5/7);
//            cout << "Ball position X = "<< v3fCircles[i][0]			// x position of center point of circle
//           cout    <<",\tY = "<< v3fCircles[i][1]								// y position of center point of circle
           cout     <<",\tRadius = "<< v3fCircles[i][2]<< "\n";					// radius of circle
           cout     <<",\tJarak = "<< j<< " cm\n";					// radius of circle
/*
            if(v3fCircles[i][2]>=20 && v3fCircles[i][2]<=30){
                cout << "Bola Jauh" << std::endl;
            }
            else if(v3fCircles[i][2]>=50) {
                cout << "Bola Dekat" << std::endl;
            }*/
                                                                                // draw small green circle at center of object detected
            circle(imgOriginal,												// draw on original image
                Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
                3,																// radius of circle in pixels
             Scalar(0, 255, 0),											// draw green
                CV_FILLED);														// thickness

                                                                                // draw red circle around object detected
            circle(imgOriginal,												// draw on original image
                Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
                (int)v3fCircles[i][2],											// radius of circle in pixels
                Scalar(0, 0, 255),											// draw red
                3);																// thickness
        }

        // declare windows
        namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);
        namedWindow("threshImg", CV_WINDOW_AUTOSIZE);

        /* Create trackbars in "threshImg" window to adjust according to object and environment.*/
        createTrackbar("LowH", "threshImg", &lowH, 255);	//Hue (0 - 255)
        createTrackbar("HighH", "threshImg", &highH, 255);

        createTrackbar("LowS", "threshImg", &lowS, 255);	//Saturation (0 - 255)
        createTrackbar("HighS", "threshImg", &highS, 255);

        createTrackbar("LowV", "threshImg", &lowV, 255);	//Value (0 - 255)
        createTrackbar("HighV", "threshImg", &highV, 255);


        imshow("imgOriginal", imgOriginal);					// show windows
        imshow("threshImg", threshImg);

        charCheckForEscKey = cv::waitKey(1);					// delay and get key press
    }

    return(0);
}
