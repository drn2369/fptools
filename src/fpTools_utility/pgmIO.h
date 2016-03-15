/*!
 *    \file  pgmIO.h
 *   \brief  IO for PGM Image format
 *  
 *  \author  David Nilosek (drn), david.nilosek@gmail.com
 *  
 *  \internal
 *       Created:  08/31/2015
 *      Revision:  none
 *      Compiler:  gcc
 */

//Eigen3
#include <Eigen/Core>

#ifndef PGMIO_H
#define PGMIO_H

namespace fpTools{
	
/*!
 *  \brief  Class to read/write PGM images
 */
class pgmIO
{
	public:
		/* ====================  LIFECYCLE     ======================================= */

		/*!
		 *  \brief  Constructor for pgmIO
		 *  
		 *  \param  fN const char* The file path for IO
		 */
		pgmIO (const char* fN); /* constructor      */


		/*!
		 *  \brief  Copy constructor
		 */
		pgmIO ( const pgmIO &other );   /* copy constructor */


		/*!
		 *  \brief  Destructor
		 */
		~pgmIO (){}                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		
		/*!
		 *  \brief  Get filename
		 *  
		 *  \return const char* The filename
		 *  <+DETAILED+>
		 */
		const char* getFN(){return m_fN;}
		/* ====================  MUTATORS      ======================================= */
		
		
		/*!
		 *  \brief  Set filename
		 *  
		 *  \param  fN const char* The filename for IO
		 */
		void setFN(const char* fN){ m_fN = fN;}
		/* ====================  OPERATORS     ======================================= */

		/*!
		 *  \brief  Reads a PGM image
		 *  
		 *  \param[out] image Eigen::MartixXi Empty matrix to store PGM data 
		 */
		void read(Eigen::MatrixXi &image);			
		
		/*!
		 *  \brief  Writes a PGM image
		 *  
		 *  \param[in] image Eigen::MatrixXi Data to write to PGM
		 */
		void write(Eigen::MatrixXi &image);			
		
		
		//Assignment operator.
		pgmIO& operator = ( const pgmIO &other ); /* assignment operator */

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */
		
		/*!
		 *  \brief  Skips comments in PGM file 
		 *  
		 *  \param  fP FILE* The file pointer
		 */
		void skipComments(FILE* fP);

		/* ====================  DATA MEMBERS  ======================================= */
		const char* m_fN; /**< Filename */

}; /* -----  end of class pgmIO  ----- */





} //End namespace fpTools
#endif //PGMIO_H

