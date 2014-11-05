//
//  main.cpp
//  SLICSuperpixel Superpixels
//
//  Created by Saburo Okita on 22/04/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tbb/tbb.h>

#include "slicsuperpixel.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    Mat image = imread( "/home/prassanna/Development/DataTest/Lenna.png" );
    imshow( "Original RGB", image );
    waitKey();


    /* Generate super pixels */
    SLICSuperpixel slic( image, 400 );
    slic.generateSuperPixels();
    Mat segments = slic.getClustersIndex();



    int inp = 0;
    Mat neigh = slic.getNeighbours();
    //Interface to check the neigbhours
    do
    {
        cout<<endl<<endl<<"Enter a superpixel value : ";
        cin>>inp;
        cout<<endl<<"printing Neighbours....";
        int nbr;
        int c= 0;
        do
        {
            nbr = neigh.at<int>(inp,c);
            c++;
            cout<<nbr<<", ";

        }while (nbr>=0);
    cout<<endl;
    }while (inp>=0);

    cv::imwrite("/home/prassanna/Development/Lenna_400sup.png", slic.getClustersIndex());
    return 0;
}
