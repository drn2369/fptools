/*!
 *    \file  lineReg.cpp
 *   \brief  App to demo line scan registration
 *  
 *  \author  David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  08/13/2015
 *      Revision:  none
 *      Compiler:  gcc
 */

//Eigen
#include <Eigen/Core>

//fpTools
#include <fpTools_utility/pgmIO.h>
#include <fpTools/lineRegistration.h>

/*!
 *  \brief  App to demo line scan registration
 *  
 *  \param  argv[1] Path to unregistered scans
 *  \param  argv[2] Path to write registered scans
 *
 */
int main ( int argc, char *argv[] )
{
	//Define
	int lengthOfScan = 8; //Defined by scanner hardware
	Eigen::MatrixXi testImage;

	//Create IO
	fpTools::pgmIO imgIO(argv[1]);

	//Read test image
	imgIO.read(testImage);

	//Do registration
	fpTools::lineRegistration reg(lengthOfScan);
	reg.registerLines(testImage);

	//Write test image
	imgIO.setFN(argv[2]);
	imgIO.write(testImage);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
