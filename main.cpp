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
#include "distr.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main( void ) 
{
   int i, j, k, rNum;
   int test;
   int RandDistrFlag;
   
   
   double Randh;
   
   std::fstream fileC;
   std::string str;
   FILE *F;

  /*
  XLength = 256.0 * 1E-6;
  YLength = 256.0 * 1E-6;
  */
  
  RandDistrFlag = 2;
    
  // calculatoin of inhomogeinity for all pores
  if(RandDistrFlag == 0)
  {
    XLength = 256 * 1E-6; // 428; //128.0 * 1E-6 ;
    YLength = 256 * 1E-6; //506; //128.0 * 1E-6;
	Init();
    Out(); 
    PositionAreaFlag = 2;
    InhomCalc();
    printf("h = %f\n", h);
    F = fopen("h.dat","w+");
    fprintf(F,"%f",h);
    fclose(F);
    //getch();
    return 0;   
  }
  
  
  // Calculation of inhomogeinity for different ranges of pores radiuses
  if(RandDistrFlag == 1)
  {
    XLength = 256.0;
    YLength = 256.0;
	Init();
    Out(); 
    PositionAreaFlag = 2;
    //SelectionR( 2.0, 1 );
    SelectionR( 2.0, 1 );
    InhomCalc();
    printf("h = %f\n", h);
    
    //getch();
    return 0;   
  }
  
  // Calculation of inhomogeinity for random uniform distirbution
  if(RandDistrFlag == 2)
  {
  	Randh = 0.0;
	XLength = 258.0 * 1E-6;
    YLength = 258.0 * 1E-6;
    rNum = 100;
    /* генерация распределения точек*/
    //fileC.open("dataC.dat",std::ios::in); 
    F = fopen("dataC.dat","w+");
	for(i = 1; i <= rNum; i++)
    { 
      GenerationNodesR(20); 
      PositionAreaFlag = 2;
      InhomCalc();
      Randh = Randh + h;
      //fileC << i << "  " << h << "\n";
      fprintf(F,"%d  %f\n",i, h);
    }
	//Randh = Randh / (double)rNum;
	printf("%f  h = %f\n", Randh, Randh / (double)rNum);
    getch();
    //fileC.close();
    fclose(F);
    return 0;      
  }
  
  
  
  
  //test = IntPower(3,15);
  //printf("%d", test);
  //getch();
  
  
  
  //XLength = 200; 
  //YLength = 200;
  
}
