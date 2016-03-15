/*!
 *    \file  minutiaeExtration.h
 *   \brief Class to handle extraction of minutiae from fingerprint images 
 *  
 *  \author  David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  01/10/2016
 *      Revision:  none
 *      Compiler:  gcc
 */
//STL
#include <vector>

//Eigen3
#include <Eigen/Core>

#ifndef MINUTIAEEXTRACTION_H
#define MINUTIAEEXTRACTION_H

namespace fpTools{


	/*!
	 *  \brief  Class to handle the extraction of minutiae from fingerprints
	 */
	class minutiaeExtraction
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			
			/*!
			 *  \brief  Default constructor
			 */
			minutiaeExtraction ();                             /* constructor */

			/* ====================  ACCESSORS     ======================================= */

			/* ====================  MUTATORS      ======================================= */

			/* ====================  OPERATORS     ======================================= */
			
			/*!
			 *  \brief  Binarizes the input image using the Otsu thresholding method
			 *  
			 *  \param[in,out] image Eigen::MatrixXi The input image
			 */
			void binarize(Eigen::MatrixXi &image);

		protected:
			/* ====================  METHODS       ======================================= */


			/*!
			 *  \brief  Compute image histogram
			 *  
			 *  \param[in]  image Eigen::MatrixXi The image to compute the histogram of
			 *
			 *  \return std::vector<int> The histogram
			 *
			 *  Assumes image values range from 0 to 255
			 */
			std::vector<int> computeHistogram(Eigen::MatrixXi &image);


			/*!
			 *  \brief  Cacluate the threshold automatically based on Otsu's method from a histogram
			 *  
			 *  \param  histogram std::vector<int> The histogram to use
			 *
			 *  \return int The calculated threshold
			 *
			 *   Assumes image values range from 0 to 255
			 */
			int otsuThreshCalc(std::vector<int> &histogram);

			/* ====================  DATA MEMBERS  ======================================= */

		private:
			/* ====================  METHODS       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */

	}; /* -----  end of class MinutiaeExtraction  ----- */


}
#endif //MINUTIAEEXTRACTION_H
