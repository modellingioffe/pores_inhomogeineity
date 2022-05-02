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

void DataRead( void )
{
   int i, j, k;
   double S, Min, Max;
   double DistrInt;  
   
   std::fstream file;
   std::string str;	
   
   
   /*
   file.open("distr.dat",std::ios::in); 
   
   
   while(true) //while(read_from_file != 1) //while(!file.eof())
    {   
      printf("%d  read...\n",i);
      //getch();
      file>> Xc[i] >> Yc[i] >> Area >> dump2;
      if(file.eof()) break;
      i++; 
    }
    file.close();
	*/
}
