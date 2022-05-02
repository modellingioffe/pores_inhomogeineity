#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <istream>
#include <fstream> 
#include <ios>
#include <string.h>
#include <iostream>

#include "init.h"
#include "inhom.h"

int LocalNodeNumber[1500000]; // number of nodes in cell
double LocalDensity[100000]; // local nodes density
double AverageDensity; //average nodes density
double XLength, YLength; // size of the analized sample
double cellXS, cellYS; //x and y sizes of the cell
int hOffsetMax[100000]; // hOffset to find maximum
double XOffset, YOffset; // values of the current offsets along X and Y 
double h; // inhomogeinity
int PositionAreaFlag;   // indication of calculation of position inhomogeinity or pores area inhomogeinity


int IntPower( int base, int power )
{
	int i;
	int base2;
	
	if(power == 1)
	  return base;
	if(power != 1)
	{  
    	base2 = base;
		for(i = 2; i <= power; i++)
     	{
	     base2 = base2 * base;	
	    }
        return base2;
	}
	
}

double Segmentation( double cellXS, double cellYS, int jN, double XOffset, double YOffset, int CellN  )
{
	int i, j, k, l;
	double xCell, yCell; // x and y coordinates of cell thah contains specific node (pore)
	int xCellNumber, yCellNumber; // x and y cell coordinates in the cell grid 	
	int CellNumber;     //number of the cell in the cell list, range from 1 to 2^2jN
	double CellSquare;  // square of the cell
	double hOffset;     // calculation of the inhomogeinity for the specific offset and specific number of subdivision
	double localdensity2;
	
	hOffset = 0.0;	
	for(i = 0; i <= CellN; i++)
	  LocalNodeNumber[i] = 0;
	
	for(i = 0; i <= N; i++)
	{
	  //printf("Test2  %d  %d\n", i, N);
	  //getch();
	  XcCurr[i] = Xc[i] + XOffset;
	  YcCurr[i] = Yc[i] + YOffset;
	  if(XcCurr[i] > XLength)
	    XcCurr[i] = XcCurr[i] - XLength;
	  if(YcCurr[i] > YLength)
	    YcCurr[i] = YcCurr[i] - YLength;  
	  xCell = XcCurr[i] / cellXS;
	  yCell = YcCurr[i] / cellYS;
	  xCellNumber = int(xCell);
	  yCellNumber = int(yCell);	
	  //printf("%f  %f %f  %f\n", xCell, yCell);
	  //getch();
	  CellNumber = (xCellNumber + 1)  + yCellNumber * IntPower(2,jN);
	  //printf("%d  %d  %d  %d\n", xCellNumber+1, yCellNumber * IntPower(2,jN), CellNumber, jN);
	  //getch();
	  LocalNodeNumber[CellNumber] = LocalNodeNumber[CellNumber] + 1;
	  //printf("%d  %d\n",LocalNodeNumber[CellNumber], CellNumber);
	  //getch();
	}
	
	//printf("Test3\n");
	//getch();
	for(i = 1; i <= CellN; i++)
	{
	   localdensity2 = double(LocalNodeNumber[i]) - AverageDensity;
	   //printf("%f  %d  %f\n",localdensity2, LocalNodeNumber[i], AverageDensity);
	   //getch();
	   if( localdensity2 < 0)
	     localdensity2 = -1 *  localdensity2;
	    
	  hOffset = hOffset + localdensity2; 
    }
    //printf("check1\n");
    
    return hOffset;
}

double MaxValue( int n )
{
  int i;
  double MaxVal;
  
  MaxVal = hOffsetMax[1];
  for(i = 2; i < n; i++)
  {
  	if(hOffsetMax[i] > MaxVal)
  	  MaxVal = hOffsetMax[i];
  }
  
  return MaxVal;
  	
}

void InhomCalc( void )
{
   int i, j, k, k1, jN, l;
   int r;
   int hoff;
   int CellN;
   
   double offsetX, offsetY; //value of the minimum offset for the specific subdivision, it is equal for x and y directions
   double offset;
   int offN; // number of offset along each directions (x or y)
   double hcurr; //h value for the current subdivision;
   double w = 4.79129; //weight coefficient
   
   r = 10; //10;
   offN = 10; //10;
   h = 0.0;
   
   //ЦИКЛ по разбиениям, 10 - максимальное разбиение
   for(jN = 1; jN <= r; jN++)
   {
    k = 2 * jN;
    k1 = IntPower(2, jN);
    CellN = IntPower(2, k);
    cellXS = XLength / double(k1);
    cellYS = YLength / double(k1);
    AverageDensity = double(N) / double(CellN);
    offsetX = cellXS / double(offN);
	offsetY = cellYS / double(offN);
	l = 1;
	/*
	for(i = 0; i <= N + 10; i++)
	{
	  printf("%d\n",LocalNodeNumber[i]);
	  LocalNodeNumber[i] = 0;
    }
    getch();
	//CYCLE по оффсету для заданного разбиения!!!!!!!!!!!!
	for(i = 0; i <=1500000; i++)
	  LocalNodeNumber[i] = 0;
	*/  
	for(i = 0; i < offN; i++) //смещение вдоль x
	{
	  for(j = 0; j < offN; j++)
	  { 
	    XOffset = double(j) * offsetX; 
		YOffset = double(i) * offsetY; 
		//printf("Test1\n");
		//getch();
		hOffsetMax[l] = Segmentation( cellXS, cellYS, jN, XOffset, YOffset, CellN );
		//printf("%d\n",hOffsetMax[l]);
		//getch();
		printf("l = %d  jN = %d\n", l, jN);
		//getch();
		//for(i = 0; i <= N; i++)
	      //LocalNodeNumber[i] = 0;
		l++;	
      }
    }
      ///поиск максимума коэффициента неодноодности!!!!
      hcurr = MaxValue(l);
      printf("%f\n",hcurr);
      
      /// умножение на весовой коэффициент 
      hcurr = pow(w, 1-jN) * hcurr; 
      
      /// суммирование умноженных значений с последующей нормировкой
     h = h + hcurr;
   }
   
   h = (1.0 / (2 * double(N))) * h;
}


void SelectionR( double ThresV, int LowHighFlag )
{
	int i, j, k;
	double Radius1[10000], Height1[10000]; //double Rad1[10000], Rad2[10000], Rad3[10000], Rad4[10000];
	double Xc1[10000], Yc1[10000];
	
	std::fstream file;
	
	k = 0;
	for(i = 0; i <= N; i++)
	{
	  if(LowHighFlag == 0)
	  {
	    if(Radius[i] <= ThresV)
	    {
	  	   Xc1[k] = Xc[i];
	  	   Yc1[k] = Yc[i];
	  	   Radius1[k] = Radius[i];
	  	   k++;
	    }
      }
      
      if(LowHighFlag == 1)
	  {
	    if(Radius[i] > ThresV)
	    {
	  	   Xc1[k] = Xc[i];
	  	   Yc1[k] = Yc[i];
	  	   Radius1[k] = Radius[i];
	  	   k++;
	    }
      }
      
	} 
	
	N = k - 1;
	
	for(i = 0; i <= N; i++)
	{
	  Xc[i] = Xc1[i];
	  Yc[i] = Yc1[i];	
	}
	
	file.open("dataThr.dat",std::ios::out);
	for(i = 0; i <= N; i++)
	  file << i << "  " << Xc[i] << "   "  <<Yc[i] << "  " << Radius1[i] << "\n";
	
	file.close(); 
}

void SelectionH( double ThresV, int LowHighFlag )
{
	int i, j, k;
	double Radius1[10000], Height1[10000]; // Rad2[10000], Rad3[10000], Rad4[10000];
	double Xc1[10000], Yc1[10000];
	
	std::fstream file;
	
	k = 0;
	for(i = 0; i <= N; i++)
	{
	  if(LowHighFlag == 0)
	  {
	    if(Height[i] <= ThresV)
	    {
	  	   Xc1[k] = Xc[i];
	  	   Yc1[k] = Yc[i];
	  	   Height1[k] = Height[i];
	  	   k++;
	    }
      }
      
      if(LowHighFlag == 1)
	  {
	    if(Height[i] > ThresV)
	    {
	  	   Xc1[k] = Xc[i];
	  	   Yc1[k] = Yc[i];
	  	   Height1[k] = Height[i];
	  	   k++;
	    }
      }
      
      N = k - 1;
	} 
	
	for(i = 0; i <= N; i++)
	{
	  Xc[i] = Xc1[i];
	  Yc[i] = Yc1[i];	
	}
	
	file.open("dataThr.dat",std::ios::out);
	for(i = 0; i <= N; i++)
	  file << i << "  " << Xc[i] << "   "  <<Yc[i] << "  " << Height1[i] << "\n";
	
	file.close(); 
}
