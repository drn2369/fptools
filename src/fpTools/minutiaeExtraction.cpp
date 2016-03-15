/*!
 *    \file  minutiaeExtraction.cpp
 *   \brief  Implimentation file for minutiaeExtraction class
 *  
 *  \author  David Nilosek (drn), david.nilosek@pictometry.com
 *  
 *  \internal
 *       Created:  01/10/2016
 *      Revision:  none
 *      Compiler:  gcc
 */
//STL
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>

//Eigen3
#include <Eigen/Core>

//fpTools
#include "fpTools/minutiaeExtraction.h"

namespace fpTools{

//Constructor
minutiaeExtraction::minutiaeExtraction()
{
}

//Binarize image
void minutiaeExtraction::binarize(Eigen::MatrixXi &image)
{
	//Compute histogram (using 256 bins)
	std::vector<int> hist = this->computeHistogram(image);

	//Calculate threshold
	int thresh = this->otsuThreshCalc(hist);

	//Threshold the image
	for(size_t i = 0; i < image.rows(); i++)
	{
		for(size_t j = 0; j < image.cols(); j++)
		{
			if(image(i,j) < thresh)
			{
				image(i,j) = 0;
			}else
			{
				image(i,j) = 255;
			}
		}
	}
}

//Compute threshold
int minutiaeExtraction::otsuThreshCalc(std::vector<int> &histogram)
{
	//Return var
	int thresh = 0;

	//Compute total and sum
	int total = std::accumulate(histogram.begin(), histogram.end(), 0);
	float sum = 0;

	//Compute sum weight
	for(size_t i = 0; i < histogram.size(); i++)
	{
		sum += (float)i*histogram[i];
	}

	//Init for computation
	float varMax = 0;
	float sumB = 0;
	int weightB = 0;
	int weightF = 0;

	//Run Otsu thresholding computation
	for( size_t i = 0; i < histogram.size(); i++)
	{
		weightB += histogram[i]; //Background weight
		if(weightB == 0) continue; // Skip to first value

		weightF = total - weightB; //Foreground weight
		if(weightF == 0) break; // Stopping condition

		sumB += (float)( i*histogram[i]); //Background summation

		//Compute means
		float meanBackground = sumB/weightB;
		float meanForground = (sum - sumB)/weightF;

		//Compute interclas variance
		float interVar = (float)weightB * (float)weightF * (meanBackground - meanForground) * (meanBackground  - meanForground);
		std::cout << interVar << std::endl;
		//Check if new max
		if( interVar > varMax)
		{
		  //If yes, this is new threshold
		  varMax = interVar;
		  thresh = i;
		}
	}

	//Return
	return thresh;
}

//Compute histogram
std::vector<int> minutiaeExtraction::computeHistogram(Eigen::MatrixXi &image)
{
	//Create histogram vector
	std::vector<int> hist(256, 0);

	//Calculate histogram
	for(int i = 0; i < image.rows(); i++)
	{
		for(int j = 0; j < image.cols(); j++)
		{
			//increment
			hist[image(i,j)] += 1;	
		}
	}
	//Return histogram
	return hist;
}

} //End namespace fpTools

