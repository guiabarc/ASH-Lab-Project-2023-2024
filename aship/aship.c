#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Image size: use this size for IP implementation
#define NROWS  512
#define NCOLS  512

// Full image size, use this for profilling
//#define NROWS  1844
//#define NCOLS  4000

// Comment this line to use the input data from the include file datain.h
// Uncomment to load data from file and write data to file
#define LOAD_FROM_FILE



#ifndef LOAD_FROM_FILE
#include "datain.h"
#endif

#ifdef LOAD_FROM_FILE
int Min[NROWS][NCOLS];
#endif


volatile int Mout[NROWS][NCOLS];

int Ma[NROWS][NCOLS];
int Mb[NROWS][NCOLS];

//-------------------------------------------------------------------
#ifdef LOAD_FROM_FILE
void
LoadData( char *filename, int Min[NROWS][NCOLS] )
{
	FILE *fpin;
	int x;
	int i, j;
	
	if( ( fpin = fopen( filename, "r" ) ) == NULL )
	{
		printf("Input file %s not found. Exiting...\n", filename );
		exit( -1 );
	}

    // Init	matrix:
	for(i=0; i<NROWS; i++)
		for(j=0; j<NCOLS; j++)
			Min[i][j] = 0;
		
	// Load matrix from text file:
	for(i=0; i<NROWS; i++)
		for(j=0; j<NCOLS; j++)
		{
			if ( fscanf(fpin, "%d", &x ) != 1 )
				return;
			Min[i][j] = x;		

		}
		
	fclose( fpin );
}
#endif

//-------------------------------------------------------------------
int
Saturate_int8( int pixout )
{ 
   return( pixout > 255 ? 255 : ( pixout < 0 ? 0 : pixout ) );
}

//-------------------------------------------------------------------
void
DetectEdges5( int Min[NROWS][NCOLS], int Mout[NROWS][NCOLS] )
{
	int i, j, k, l;
	
	int kernel[5][5], pixout;
	
	int kernel_size = 5;
	
	kernel[0][0] = -7;
	kernel[0][1] = -7;
	kernel[0][2] = -7;
	kernel[0][3] = -7;
	kernel[0][4] = -7;
	
	kernel[1][0] = -5;
	kernel[1][1] = 0;
	kernel[1][2] = 0;
	kernel[1][3] = 0;
	kernel[1][4] = -5;
	
	kernel[2][0] = -5;
	kernel[2][1] = 0;
	kernel[2][2] = 90;
	kernel[2][3] = 0;
	kernel[2][4] = -5;
	
	kernel[3][0] = -5;
	kernel[3][1] = 0;
	kernel[3][2] = 0;
	kernel[3][3] = 0;
	kernel[3][4] = -5;
	
	kernel[4][0] = -7;
	kernel[4][1] = -7;
	kernel[4][2] = -7;
	kernel[4][3] = -7;
	kernel[4][4] = -7;

	for(i=0+kernel_size/2; i < NROWS - kernel_size/2; i++ )
	   for(j=0+kernel_size/2; j < NCOLS - kernel_size/2; j++ )
	   {
		   pixout = 0;
		   for( k=-2; k<=2; k++ )
			   for( l=-2; l<=2; l++ )
				   pixout = pixout + kernel[k+2][l+2] *
			               Min[i+k][j+l];
 		   Mout[i][j] = Saturate_int8( pixout );

	   }
		
}


//-------------------------------------------------------------------
void
DetectEdges3( int Min[NROWS][NCOLS], int Mout[NROWS][NCOLS] )
{
	int i, j, k, l;
	
	int kernel[3][3], pixout;
	
	int kernel_size = 3;
	
	kernel[0][0] = 1;
	kernel[0][1] = 1;
	kernel[0][2] = 1;
	
	kernel[1][0] = 1;
	kernel[1][1] = -8;
	kernel[1][2] = 1;
	
	kernel[2][0] = 1;
	kernel[2][1] = 1;
	kernel[2][2] = 1;

	for(i=0+kernel_size/2; i < NROWS - kernel_size/2; i++ )
	   for(j=0+kernel_size/2; j < NCOLS - kernel_size/2; j++ )
	   {
		   pixout = 0;
		   for( k=-1; k<=1; k++ )
			   for( l=-1; l<=1; l++ )
				   pixout += kernel[k+1][l+1] *
			               Min[i+k][j+l];
		   Mout[i][j] = (pixout) > 255 ? 255 : ( pixout < 0 ? 0 : pixout );
		   
		   // Negative image
		   Mout[i][j] = 255 - Mout[i][j];
	   }
		
}


//-------------------------------------------------------------------
void
Blur( int Min[NROWS][NCOLS], volatile int Mout[NROWS][NCOLS] )
{
	int i, j, k, l;
	
	int kernel[3][3], pixout;
	
	int kernel_size = 3;
	
	kernel[0][0] = 1;
	kernel[0][1] = 1;
	kernel[0][2] = 1;
	
	kernel[1][0] = 1;
	kernel[1][1] = 1;
	kernel[1][2] = 1;
	
	kernel[2][0] = 1;
	kernel[2][1] = 1;
	kernel[2][2] = 1;

	for(i=0+kernel_size/2; i < NROWS - kernel_size/2; i++ )
	   for(j=0+kernel_size/2; j < NCOLS - kernel_size/2; j++ )
	   {
		   pixout = 0;
		   for( k=-1; k<=1; k++ )
			   for( l=-1; l<=1; l++ )
				   pixout += kernel[k+1][l+1] *
			               Min[i+k][j+l];
						   
		   pixout = pixout / 9;
		   Mout[i][j] = (pixout) > 255 ? 255 : ( pixout < 0 ? 0 : pixout );

	   }
		
}

//-------------------------------------------------------------------
void
Binarize( int Min[NROWS][NCOLS], int Mout[NROWS][NCOLS] )
{
	int i, j;
	
	for(i=0; i < NROWS; i++ )
	   for(j=0; j < NCOLS ; j++ )
	   {
		   Mout[i][j] = Min[i][j] > 128 ? 255 : 0;
	   }
		
}


//-------------------------------------------------------------------
void
Erode( int Min[NROWS][NCOLS], volatile int Mout[NROWS][NCOLS] )
{
	int i, j, k, l;
	
	float pixout;
	
	int kernel_size = 5;

	for(i=0+kernel_size/2; i < NROWS - kernel_size/2; i++ )
	   for(j=0+kernel_size/2; j < NCOLS - kernel_size/2; j++ )
	   {
		   if ( Min[i][j] < 128 )
		   {
		     for( k=-2; k<=2; k++ )
			     for( l=-2; l<=2; l++ )
				     Mout[i+k][j+l] = 0;
		   }
		   else
			   Mout[i][j] = Min[i][j];
	   }
		
}

//-------------------------------------------------------------------
#ifdef LOAD_FROM_FILE
void
WriteData( char *filename, volatile int Mout[NROWS][NCOLS] )
{
	FILE *fpout;
	int i, j;
	
	if( ( fpout = fopen( filename, "w" ) ) == NULL )
	{
		printf("Can't create output file %s. Exiting...\n", filename );
		exit( -1 );
	}

		
	// Write matrix to text file:
	for(i=0; i<NROWS; i++)
	{
		for(j=0; j<NCOLS; j++)
		{
			fprintf(fpout,"%3d ", Mout[i][j] );
		}
		fprintf(fpout, "\n");
    }
		
	fclose( fpout );
}
#endif

//-------------------------------------------------------------------
int
main( int argc, char **argv)
{
	if ( argc != 3 )
	{
		printf("Usage: aship infile outfile\n");
		return 0;
	}
	

	
#ifdef LOAD_FROM_FILE
	printf("Loading data...\n");
	LoadData( argv[1], Min );
#endif
	
	printf("Processing data...\n");
	
	Blur( Min, Mb );
	Blur( Mb, Ma );
	Blur( Ma, Mb );

	DetectEdges5( Mb, Ma ); 

	DetectEdges3( Ma, Mb );
    Binarize( Mb, Ma );

	Erode( Ma, Mout );

#ifdef LOAD_FROM_FILE
	printf("Writing data...\n");
	WriteData( argv[2], Mout );
#endif
	
	return 1;
}
