/*!
 *    \file  pgmIO.cpp
 *   \brief  Implimentation of IO functions for PGM image format
 *  
 *  \author David Nilosek (drn), david.nilosek@gmail.com	
 *  
 *  \internal
 *       Created:  08/31/2015
 *      Revision:  none
 *      Compiler:  gcc
 */

//STL
#include <cstdio>
#include <cstring>

//Eigen3
#include <Eigen/Core>

//fpTools
#include "fpTools_utility/pgmIO.h"

namespace fpTools{

//Constructor
pgmIO::pgmIO(const char* fN)
{
	setFN(fN);
}

//Function to skip comments
void pgmIO::skipComments(FILE *fP){

	while(std::getc(fP) == '#'){
		while(std::getc(fP) != '\n');
	}

	std::fseek(fP, -1, SEEK_CUR);
}

//Function to read PGM image into Eigen int matrix
void pgmIO::read(Eigen::MatrixXi &image)
{
	/*Def */
	FILE *fileVar;
	char version[3];
	int i, j;
	int h, l;

	/* Open and start reading */
	fileVar = std::fopen(m_fN, "rb");
	if (fileVar == NULL){
		std::fprintf(stderr,"Unable to open file");
		return;
	}

	/*Get Version*/
	std::fgets(version, sizeof(version), fileVar);
	if( std::strcmp(version, "P5") ){
		std::fprintf(stderr,"Unknown file type");
		return;
	}

	std::fgetc(fileVar); /*burn off \n */
	/*Skip through comments*/
	skipComments(fileVar);
	/*Get row, col and max grey value*/
	int col, row, max;
	std::fscanf(fileVar, "%i", &col);
	std::fscanf(fileVar, "%i", &row);
	std::fscanf(fileVar, "%i", &max);
	std::fgetc(fileVar); /*burn off \n */

	/* Create image array */
	image= Eigen::MatrixXi::Zero(row,col);

	/* Read image array */
	
	/* If max is above 255, then calculate value above 8 bits */ 
	if( max > 255 ){
		for(i = 0; i < row; i++){
			for(j = 0; j < col; j++){
				/* Get both values */
				h = fgetc(fileVar);
				l = fgetc(fileVar);
			
				/* Store image */
				image(i,j) = (h << 8) + l;
			}
		}
	/* If max is below 255, read as normal */
	}else{
		for(i = 0; i < row; i++){
			for(j = 0; j < col; j++){
				l = std::fgetc(fileVar);
				image(i,j) = l;
			}
		}
	}

	std::fclose(fileVar);


}

//Function to write PGM data
void pgmIO::write(Eigen::MatrixXi &image){

	/* Define */
	FILE *fileVar;
	int i, j;
	int h, l;

	/* Open file for writing */
	fileVar = fopen(m_fN, "wb");
	if(fileVar == NULL){
		std::fprintf(stderr,"Cannot open file to write");
		return;
	}	

	/*Write header*/
	std::fprintf(fileVar, "P5 ");
	std::fprintf(fileVar, "%i %i ", (int)image.cols(), (int)image.rows());
	std::fprintf(fileVar, "%i ", 255);
	
	/*Write data*/
	for( i = 0; i < image.rows(); i++){
		for( j = 0; j < image.cols(); j++){
			l = (image(i,j)  & 0x000000FF );
			std::fputc(l, fileVar);
		}
	}
	
	/* Close */
	std::fclose(fileVar);
}
} //End namespace fpTools
