#ifndef DRAWING_H
#define DRAWING_H
/*!
 * @name		Drawing.hpp
 * @author		Fernando Hermosillo.
 * @brief		This file is part of Vehicle Detection and Classification System project.
 * @date		25/11/2016
 *
 * @version
 * @history
 *	26/11/2016: Initial version.
 */
#pragma once


/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


/*!
 * @namespace 	sdcv.
 * @brief 		Vehicle Detection and Classification System.
 */
namespace sdcv {
    /*!
     * @name	imLine.
     * @version	1.0
     * @brief	This function returns a set of points for a line that you will set in an image.
     * @param	frame (Input) - Frame where line is gonna be gotten.
     * @param	WindowName (Input) - A string that contains the name of the window in case of line is gonna be dram
     * @param	initialConditions (Input) -
     *
     * @return 	A set of points
     */
    std::vector<cv::Point> imLine(cv::OutputArray frame, cv::String WindowName, cv::Point initialConditions = cv::Point(-1, -1));

    /*!
     * @name	vertices2polygon.
     * @version	1.0.
     * @brief	This function converts a set of points into a polygon.
     * @param	vertices: As Input is a set of points.
     * @param	frameSize: As Input is the frame's size to be generated.
     * @param	polygon: As Output is the frame object to be generated.
     *
     * @return None.
     */
    void vertices2polygon(std::vector<cv::Point> vertices, cv::Size frameSize, cv::OutputArray polygon);
};

#endif
