/*!
 *    \file  demoExtract.cpp
 *   \brief  Demo app to show extraction of minutiae from binarized image
 *  
 *  \author  David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  01/10/2016
 *      Revision:  none
 *      Compiler:  gcc
 */

//Eigen
#include <Eigen/Core>

//fpTools
#include <fpTools_utility/pgmIO.h>
#include <fpTools/minutiaeExtraction.h>

/*!
 *  \brief  App to demo minutiae extraction
 *  
 *  \param  argv[1] Path to scan
 *  \param  argv[2] Output pgm path for demo
 */
int main ( int argc, char *argv[] )
{
	//Create IO
	fpTools::pgmIO imgIO(argv[1]);

	//Read image
	Eigen::MatrixXi testImage;
	imgIO.read(testImage);

	//Do binarization
	fpTools::minutiaeExtraction extract;

	extract.binarize(testImage);

	//Write test image
	imgIO.setFN(argv[2]);
	imgIO.write(testImage);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

