/*!
 *    \file  lineRegistration.h
 *   \brief  Class to handle registration of scanlines
 *  
 *  \author David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  08/13/15
 *      Revision:  none
 *      Compiler:  gcc
 *  
 */

//Eigen3
#include <Eigen/Core>

#ifndef LINEREGISTRATION_H
#define LINEREGISTRATION_H

namespace fpTools{
/*!
 *  \brief  Class to handle registration of scanlines
 */
class lineRegistration
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		
		/*!
		 *  \brief  Default constructor
		 */
		lineRegistration(){}

		/*!
		 *  \brief  Constructor
		 *  
		 *  \param  lengthOfScan int The length of the scanline in pixels, defined by the hardware
		 */
		lineRegistration (int lengthOfScan);                             /* constructor */

		/* ====================  ACCESSORS     ======================================= */
		
		/*!
		 *  \brief  Get scanlength
		 *  
		 *  \return Scanlength in pixels
		 */
		int getLengthOfScan(){return m_lengthOfScan;}

		/* ====================  MUTATORS      ======================================= */

		/*!
		 *  \brief  Set scanlength
		 *  
		 *  \param  lengthOfScan int The scanlength in pixels
		 */
		void setLengthOfScan(int lengthOfScan){m_lengthOfScan = lengthOfScan;}
		/* ====================  OPERATORS     ======================================= */
		
		/*!
		 *  \brief  Function to register multiple line scans contained in a single 2D array
		 *		in which the scans are stacked in a column
		 *  
		 *  \param[in,out]  image Eigen::MatrixXi The 2d array which contains the unregistered scans,
		 *  					will be replaced by registered scans
		 *
		 *  \return bool If the registration was succesful, 
		 *  		will return false if one scanline fails to register well.
		 */
		bool registerLines(Eigen::MatrixXi &image);

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */
	
		
		/*!
		 *  \brief  Subset eigen matrix into another matrix (because block is prohibitive to addtional operations)
		 *  
		 *  \param  startRow int The starting row to subset
		 *  \param  startCol int The starting column to subset
		 *  \param  rows int The number of rows to subset
		 *  \param  cols int The number of cols to subset
		 *  \param[in] image Eigen::MatrixXi The image to subset
		 *  \param[out] sub Eigen::MatrixXi The subsetted part of the image
		 *
		 *  User needs to init sub size
		 */
		void subsetImage(int startRow, int startCol, int rows, int cols, Eigen::MatrixXi &image, Eigen::MatrixXf &sub);

		/*!
		 *  \brief  Performs foward 2d FFT
		 *  
		 *  \param[in]  mat Eigen::Block<int> Input int matrix (subset from mat)
		 *  \param[out] matCF Eigen::MatrixXcf Output complex float matrix 
		 *
		 *  User responsible for sizing matCF
		 */
		void fft2dFwd(Eigen::MatrixXf &mat, Eigen::MatrixXcf &matCF);


		/*!
		 *  \brief  Performs inverse 2d FFT
		 *  
		 *  \param[in]  matCF Eigen::MatrixXcf Input complex matrix
		 *  \param[out] mat Eigen::MatrixXo Output int matrix 
		 *
		 *  User responsible for sizing matCF
		 */
		void fft2dInv(Eigen::MatrixXcf &matCF, Eigen::MatrixXf &mat);

		/* ====================  DATA MEMBERS  ======================================= */
		int m_lengthOfScan; /**< Length of scan */
}; /* -----  end of class LineRegistration  ----- */

} // End namespace fpTools

#endif //LINEREGISTRATION_H
