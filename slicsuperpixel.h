//
//  SLIC.h
//  SLIC Superpixels
//
//  Created by Saburo Okita on 22/04/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//
// This is an implementation of "SLIC Superpixels Compared to State-of-the-art Superpixel Methods"
// by Radhakrishna Achanta, Appu Shaji, Kevin Smith, Aurelien Lucchi, Pascal Fua, and Sabine Su ̈sstrunk
// you can find the referenced literature here:
// http://infoscience.epfl.ch/record/177415/files/Superpixel_PAMI2011-2.pdf
//
// The code is adapted from Pascal Mettes' https://github.com/PSMM/SLIC-Superpixels

#ifndef __SLIC_Superpixels__SLIC__
#define __SLIC_Superpixels__SLIC__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <tbb/tbb.h>

using namespace std;
using namespace cv;

struct ColorRep;
#define MAX_NBRS 100
/**
 * @brief
 *
 */
class SLICSuperpixel {
public:
    Mat clusters; /**< TODO */
    Mat distances; /**< TODO */
    vector<ColorRep> centers; /**< TODO */
    vector<int> centerCounts; /**< TODO */
    Mat nbrs;
    vector<int> counts_of_nbrs;

    Mat image; /**< TODO */
    int K; /**< TODO */
    int S; /**< TODO */
    int m; /**< TODO */
    int maxIterations; /**< TODO */

    /**
     * @brief
     *
     * @param x
     * @param y
     * @return bool
     */
    inline bool withinRange( int x, int y );
    /**
     * @brief
     *
     * @param c
     * @param p
     * @param x
     * @param y
     * @return double
     */
    double calcDistance( ColorRep& c, Vec3b& p, int x, int y );
    /**
     * @brief
     *
     * @param image
     * @param center
     * @return Point2i
     */
    Point2i findLocalMinimum( Mat& image, Point2i center );

public:
    /**
     * @brief
     *
     */
    SLICSuperpixel();
    /**
     * @brief
     *
     * @param src
     * @param no_of_superpixels
     * @param m
     * @param max_iterations
     */
    SLICSuperpixel( Mat& src, int no_of_superpixels, int m = 10, int max_iterations = 10 );

    /**
     * @brief
     *
     * @param src
     * @param no_of_superpixels
     * @param m
     * @param max_iterations
     */
    void init(Mat& src, int no_of_superpixels, int m = 10, int max_iterations = 10);
    /**
     * @brief
     *
     */
    void clear();
    /**
     * @brief
     *
     */
    void generateSuperPixels();

    /**
     * @brief
     *
     * @return int
     */
    int getS();
    /**
     * @brief
     *
     * @return int
     */
    int getM();

    /**
     * @brief
     *
     * @return Mat
     */
    Mat recolor();
    /**
     * @brief
     *
     * @return Mat
     */
    Mat getClustersIndex();
    /**
     * @brief
     *
     * @return vector<ColorRep>
     */
    vector<ColorRep> getCenters();
    /**
     * @brief
     *
     * @return vector<Point2i>
     */
    vector<Point2i> getClusterCenters();
    /**
     * @brief
     *
     * @return vector<Point2i>
     */
    vector<Point2i> getContours();

    /**
     * @brief
     *
     * @return cv::Mat
     */
    Mat getNeighbours();

    /**
     * @brief
     *
     * @return Mat
     */
    Mat getImage();
};


/**
 * 5 dimension color representation, i.e
 * color represented in LAB color space and X Y coords
 * It's a struct, well struct behaves like class
 */
/**
 * @brief
 *
 */
struct ColorRep{
    float l = 0; /**< TODO */
    float a = 0; /**< TODO */
    float b = 0; /**< TODO */
    float x = 0; /**< TODO */
    float y = 0; /**< TODO */

    /**
     * @brief
     *
     */
    ColorRep(){}

    /**
     * @brief
     *
     * @param color
     * @param coord
     */
    ColorRep( Vec3b& color, Point2i coord ) {
        init( color, coord.x, coord.y );
    }

    /**
     * @brief
     *
     * @param color
     * @param x
     * @param y
     */
    ColorRep( Vec3b& color, int x, int y ) {
        init( color, x, y );
    }

    /**
     * @brief
     *
     * @param color
     * @param x
     * @param y
     */
    void init( Vec3b& color, int x, int y ) {
        this->l = color[0];
        this->a = color[1];
        this->b = color[2];
        this->x = x;
        this->y = y;
    }

    /**
     * @brief
     *
     * @param color
     * @param x
     * @param y
     */
    void add( Vec3b& color, int x, int y ) {
        this->l += color[0];
        this->a += color[1];
        this->b += color[2];
        this->x += x;
        this->y += y;
    }

    /**
     * @brief
     *
     * @param divisor
     */
    void divColor( float divisor ) {
        this->l /= divisor;
        this->a /= divisor;
        this->b /= divisor;
    }

    /**
     * @brief
     *
     * @param divisor
     */
    void div( float divisor ) {
        this->l /= divisor;
        this->a /= divisor;
        this->b /= divisor;
        this->x /= divisor;
        this->y /= divisor;
    }

    /**
     * @brief
     *
     * @param other
     * @return double
     */
    double colorDist( const ColorRep& other ) {
        return (this->l - other.l) * (this->l - other.l)
        + (this->a - other.a) * (this->a - other.a)
        + (this->b - other.b) * (this->b - other.b);
    }


    /**
     * @brief
     *
     * @param other
     * @return double
     */
    double coordDist( const ColorRep& other ) {
        return (this->x - other.x) * (this->x - other.x)
        + (this->y - other.y) * (this->y - other.y);
    }

    /**
     * @brief
     *
     * @return string
     */
    string toString() {
        stringstream ss;
        ss << l << " " << a << " " << b << " " << x << " " << y;
        return ss.str();
    }
};

#endif /* defined(__SLIC_Superpixels__SLIC__) */
