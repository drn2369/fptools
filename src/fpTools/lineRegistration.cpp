/*!
 *    \file  lineRegistration.cpp
 *   \brief  Implimentation of line registration class
 *  
 *  \author  David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  08/13/2015
 *      Revision:  none
 *      Compiler:  gcc
 *  
 */
//STL
#include <iostream>
#include <vector>

//Eigen3
#include <Eigen/Core>
#include <unsupported/Eigen/FFT>

//fpTools
#include "fpTools/lineRegistration.h"

namespace fpTools{

//Constructor
lineRegistration::lineRegistration(int lengthOfScan){
	setLengthOfScan(lengthOfScan);
}

//Register scanlines
bool lineRegistration::registerLines(Eigen::MatrixXi &image)
{
	//Check bounds
	if( image.rows() % m_lengthOfScan != 0)
	{
		std::cerr << "LineReg: Scan length incorrect" << std::endl;
		return false;
	}

	//Calculate number of scan lines and shifts
	int scanLines = image.rows()/m_lengthOfScan;
	std::vector<int> vShiftX(scanLines-1);
	std::vector<int> vShiftY(scanLines-1);

	/**<TODO: This is the part that uses too much memory */
	//Preallocate mats for fft
	Eigen::MatrixXf subCurrent(m_lengthOfScan, image.cols());
	Eigen::MatrixXf subNext(m_lengthOfScan, image.cols());
	Eigen::MatrixXf correlation(m_lengthOfScan, image.cols());
	Eigen::MatrixXcf currentLine(m_lengthOfScan, image.cols());
	Eigen::MatrixXcf nextLine(m_lengthOfScan, image.cols());

	//Subset first line and do fft
	subsetImage(0,0,m_lengthOfScan, image.cols(),image, subCurrent);
	fft2dFwd(subCurrent, currentLine);

	//Vars for shifts
	int halfRow = m_lengthOfScan/2;
	int halfCol = image.cols()/2;
	
	//Track deviations and total translation 
	//to calculate nominal composite size
	int maxXShift = 0; //For tracking max deviation in X
	int maxYShift = 0; //For tracking max deviation in Y
	int minXShift = 10000; //For tracking min deviation in X
	int minYShift = 10000; //For tracking min deviation in Y

	int totalShiftX = 0;
	int totalShiftY = 0;

	for(size_t i = 1; i < scanLines; i++)
	{
		//Shifts
		int shiftX, shiftY;

		//Subset next line and do fft
		subsetImage(i*m_lengthOfScan, 0, m_lengthOfScan, image.cols(), image, subNext);
		fft2dFwd(subNext, nextLine);

		//Do correlation
		currentLine = currentLine.cwiseProduct( nextLine.conjugate() ); // CC = A*conj(B)
		currentLine *= (currentLine.rows() * currentLine.cols()); // Scale
		
		//Do inverse fft
		fft2dInv(currentLine, correlation);

		//Peak value will correspond to match
		//Shift can be caculated assuming scans are shifted from center
		Eigen::MatrixXf::Index rowM, colM;
		correlation.maxCoeff( &rowM, &colM);

		//Calculate Shift
		if( rowM > halfRow )
		{
			shiftY = rowM - m_lengthOfScan;
		}else
		{	
			shiftY = rowM;
		}

		if( colM > halfCol )
		{
			shiftX = colM - image.cols();
		}else
		{
			shiftX = colM;
		}
	
		//Track shift
		vShiftX[i-1] = shiftX; 
		vShiftY[i-1] = shiftY;

		//Track total shift
		totalShiftX += shiftX;
		totalShiftY += shiftY;

		//Track shift deviation
		if( totalShiftX > maxXShift ) maxXShift = totalShiftX;
		if( totalShiftX < minXShift ) minXShift = totalShiftX;
		
		if( totalShiftY > maxYShift ) maxYShift = totalShiftY;
		if( totalShiftY < minYShift ) minYShift = totalShiftY;
		//Set next line to current line
		currentLine = nextLine;
	}

	//Make sure we start at 0,0
	if (minYShift > 0) minYShift = 0;
	if (minXShift > 0) minXShift = 0;

	//Calculate nominal size
	int nomY = m_lengthOfScan + (maxYShift - minYShift);
	int nomX = image.cols() + (maxXShift - minXShift);

	/**TODO: There must be a better way to do this without making a 
	 * new matrix */
	//Register image using shifts
	Eigen::MatrixXi regImage = Eigen::MatrixXi::Zero(nomY, nomX);
	
	//Determine starting position in X (assuming 0 for y)
	int posX, posY;
	(minXShift > 0) ? posX = 0 : posX = -1*minXShift; 
	(minYShift > 0) ? posY = 0 : posY = -1*minYShift; 

	//Copy data
	regImage.block(posY, posX, m_lengthOfScan, image.cols()) =
		image.block( 0, 0, m_lengthOfScan, image.cols());
	for(size_t i = 0; i < vShiftX.size(); i++)
	{
		//Update pos
		posY += vShiftY[i];
		posX += vShiftX[i];

		//Copy data
		regImage.block(posY, posX, m_lengthOfScan, image.cols()) = 
			image.block( m_lengthOfScan*(i+1), 0, m_lengthOfScan, image.cols());

	}

	//Replace image
	image = regImage;
	return true;
}

/**<TODO: This subsetting method uses too much memory, need to find a better way */
//Private functions
void lineRegistration::subsetImage(int startRow, int startCol, int rows, int cols, Eigen::MatrixXi &image, Eigen::MatrixXf &sub)
{
	//Subset image
	for(int i = 0; i < rows; i++)
	{
		for( int j = 0; j < cols; j++)
		{
			sub(i,j) = static_cast<float>(image(startRow+i,startCol+j));
		}
	}
}

/**<TODO: Better memory management with this function */
//Foward 2d FFT
void lineRegistration::fft2dFwd(Eigen::MatrixXf &mat, Eigen::MatrixXcf &matCF)
{
	//Define FFT function
	Eigen::FFT<float> fft;

	int nRows = mat.rows();
	int nCols = mat.cols();

	//Perform ft on rows then cols
	for(size_t k = 0; k < mat.rows(); k++)
	{
		Eigen::VectorXcf tmpOut(nCols);
		fft.fwd(tmpOut, mat.row(k));
		matCF.row(k) = tmpOut;
	}

	for(size_t k=0; k < mat.cols(); k++)
	{
		Eigen::VectorXcf tmpOut(nRows);
		fft.fwd(tmpOut, matCF.col(k));
		matCF.col(k) = tmpOut;
	}
}

/**<TODO: Better memory management with this function */
//Inverse 2d FFT

void lineRegistration::fft2dInv(Eigen::MatrixXcf &matCF, Eigen::MatrixXf &mat)
{
	//Define FFT function
	Eigen::FFT<float> fft;
	
	int nRows = mat.rows();
	int nCols = mat.cols();

	//Perform ft on rows then cols
	for(size_t k = 0; k < mat.rows(); k++)
	{
		Eigen::VectorXcf tmpOut(nCols);
		fft.inv(tmpOut, matCF.row(k));
		matCF.row(k) = tmpOut;
	}

	for(size_t k=0; k < mat.cols(); k++)
	{
		Eigen::VectorXf tmpOut(nRows);
		fft.inv(tmpOut, matCF.col(k));
		mat.col(k) = tmpOut;
	}
}

} // End namespace fpTools
