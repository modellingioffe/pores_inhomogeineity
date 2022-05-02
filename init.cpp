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

using namespace std;

double Xc[10000], Yc[10000], Zc[10000];
double Height[10000], Radius[10000];
double XcCurr[10000], YcCurr[10000];
int N;


//initialisation of the hOld and hNew: read from file or generating profile
void Init ( void )
{
  int i,j;
  double rand_max;
  double val;
  double Area, dump1, dump2, dump3, dump4, dump5, dump6;
  FILE *hO;
  FILE *htemp;
  FILE * profF;
  double temp;
  int num[100];
  double read[500];
  int k;
  int psd_calc_flaq;
    
  
  std::fstream file;
  std::string str;
  
  for( i = 0; i < 10000; i++)
  {
    
	LocalDensity[i] = 0.0; 
	hOffsetMax[i] = 0.0;	
	Height[i] = 0.0;
	Radius[i] = 0.0;
	Xc[i] = -1;
	Yc[i] = -1;
  } 
  
  	for(i = 0; i <= 1500000; i++)
	  LocalNodeNumber[i] = 0;
 
  file.open("data.dat",std::ios::in); 
  
    i = 0;
    while(true) //while(read_from_file != 1) //while(!file.eof())
    {   
      printf("%d  read...\n",i);
      //getch();
      //file >> Xc[i] >> Yc[i];
      //file>> Xc[i] >> Yc[i] >> Height[i] >> Radius[i];
      //file>> Xc[i] >> Yc[i] >> dump1 >> dump2 >> dump3 >> dump4 >> dump5 >> dump6;
      file>> Xc[i] >> Yc[i] >> dump1 >> dump2 >> dump3 >> dump4;
      if(file.eof()) break;
      i++; 
    }
    file.close(); 
    N = i - 1; //зависит от файла. для некоторых i-1 для некоторых i. проверка по data2.dat
    printf("%d  %d", N, i);
    //getch();
    
}

void Out( void )
{
	int i, j, k;
	double p;
	
	std::fstream file;
	
	i = 0;
	p = 4E-6;
	file.open("data2.dat",std::ios::out);
	for(i = 0; i <= N; i++)
	  file << 1 << "  " << Xc[i]/p << "   "  <<Yc[i]/p << "   " << "0.1"  <<  "\n";
	
	file.close();
	
}

void GenerationNodes( void )
{
   int i, j, k, n;
   double xp, yp, l, m;
   double rand_max = (double)RAND_MAX;
   
   xp = 10;
   yp = 10;
   k = 0;
   //double half_amplitude = (double)RAND_MAX / (2.0 * rand_noise_amplitude);
   
   //mesh nodes pattern
   /*
   for(i = 0; i < 100; i++)
    for(j = 0; j < 100; j++)
    {
   	  l = double(i);
   	  m = double(j);
	  Xc[k] = 2.5 + xp * (l - 1.0);
	  Yc[k] = 2.5 + yp * (m - 1.0);
	  k++;
    }
    */
    
    //random cluster distribution
    srand(time(NULL)); 
    for(i = 0; i < 63; i++)
     for(j = 0; j < 63; j++)
     {
    	//printf("%f  %f\n", rand()/rand_max, rand_max);
    	//getch();
		Xc[k] = rand()/rand_max * XLength; 
    	Yc[k] = rand()/rand_max * YLength; 
    	Zc[k] = 1.0;
    	//printf("%f  %f\n", Xc[k], Yc[k]);
    	//getch();
    	k++;
      }
      
    n = 0;
    while(n < k)
    {
     for(i = n + 1; i < k; i++)
     {
       if(Xc[n] == Xc[i] && Yc[n] == Yc[i])
       {
         //printf("%d  %d\n", n, i);
	     printf("Matching values!!!!\n");	  	
	     getch();
       }  
	 }
	 n++;  
    }
      
      
      
    /*
	//cluster nodes pattern
	for(i = 0; i < 20; i++)
     for(j = 0; j < 20; j++)
     {
    	  l = double(i);
    	  m = double(j);
    	  Xc[k] = 2.5 + xp * l;
    	  Yc[k] = 2.5 + yp * m;
    	  Zc[k] = 1.0;
    	  k++;
      }
    */  
       
      
   std::fstream file;
	
	N = k - 1;

	file.open("data2.dat",std::ios::out);
	for(i = 0; i <= N; i++)
	  file << i << "  " << Xc[i] << "   "  <<Yc[i] << "  " << Zc[i] << "\n";
	
	file.close(); 
}


void GenerationNodesR( int qsize ) 
{
   int i, j, k, n, m;
   double xp, yp, l, dx, dy, el;
   double rand_max = (double)RAND_MAX;
   
   xp = 10;
   yp = 10;
   k = qsize * qsize;
   
    
    //random cluster distribution
    srand(time(NULL)); 
    
    n = 0;
    el = 5;
    while(n < k)
    {
     Xc[n] = rand()/rand_max * XLength; 
     Yc[n] = rand()/rand_max * YLength; 
     Zc[n] = 1.0;
     m = 0;
	 //printf("%f  %f  %d\n", Xc[n], Yc[n], n);
	 //getch();
	 
	 if(n > 0)
	 {
	   for(i = 0; i < n; i++)
       {
        dx = fabs(Xc[n] - Xc[i]) * 1E6;
		dy = fabs(Yc[n] - Yc[i]) * 1E6;
		printf("dx = %f  dy = %f  %d  %d  %d\n", dx, dy, n, m, i);
		//getch();
		 if((dx > el && dy <= el) || (dx <= el && dy > el) || (dx > el && dy > el))
         {
		   m++;
		   //dx = fabs(Xc[n] - Xc[i]) * 1E6;
		   //dy = fabs(Yc[n] - Yc[i]) * 1E6;
		   //printf("dx = %f  dy = %f  %d  %d  %d\n", dx, dy, n, m, i);
	       //getch();
         }  
	   }
	   
	   if(m == n)
	   {
	     n++;
	     //printf("check\n");
       }
	     
     }
     
     if(n == 0)
	   n++;
	}
      
    
   std::fstream file;
	
	N = k - 1;

	file.open("data2R.dat",std::ios::out);
	for(i = 0; i <= N; i++)
	  file << i << "  " << Xc[i] << "   "  <<Yc[i] << "  " << Zc[i] << "\n";
	
	file.close(); 
}
