#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <math.h>
#include <istream>
#include <fstream> 
#include <ios>
#include <iostream>
#include <string>
#include <sstream>

#include "equation.h"
#include "outdata.h"
#include "init.h"
#include "psd.h"

int timedata[8];

int materials_flaq;  // materials_flaq = 1 Zr-Al      
                     // materials_flaq = 2 Mo-Si
                     
int buffer_flaq;

void DegreeR( double check, double degree )
{
  int i;
  
  double value;
  
   
  int r_int, r_int1, r_int2, r_int3;
   
   for(i = 0; i < 8; i++)
      timedata[i] = '0';
          
          
   value = pow(10,degree);
   r_int1 = (int)(check / value);
   timedata[0] = r_int1 + 48;
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 1.0);
   r_int1 = (int)(check / value);
   timedata[0] = r_int1 + 48;    
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 2.0);
   r_int1 = (int)(check / value);
   timedata[1] = r_int1 + 48;  
   check = check - ((double)r_int1) * value;
   
   ///
   value = pow(10,degree - 3.0);
   r_int1 = (int)(check / value);
   timedata[2] = r_int1 + 48;
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 4.0);
   r_int1 = (int)(check / value);
   timedata[3] = r_int1 + 48;    
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 5.0);
   r_int1 = (int)(check / value);
   timedata[4] = r_int1 + 48;  
   check = check - ((double)r_int1) * value;
   
   ///
   value = pow(10,degree - 6.0);
   r_int1 = (int)(check / value);
   timedata[5] = r_int1 + 48;
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 7.0);
   r_int1 = (int)(check / value);
   timedata[6] = r_int1 + 48;    
   check = check - ((double)r_int1) * value;
       
   value = pow(10,degree - 8.0);
   r_int1 = (int)(check / value);
   timedata[7] = r_int1 + 48;  
   check = check - ((double)r_int1) * value;
}


void OutStep( void )
{
   int i, j, k;
   char filename1[15];
   char filename2[15];
   char filename3[15];
   char filename4[15];
   char filename5[15];
   int ggp_flaq;
   double Zr_Al_profile_points = 10000.0;
   double Mo_Si_profile_points = 136.0;  
   double W_B4C_profile_points = 400; //402; //402;
   int deriv_flaq;
   int add_flaq;
   int ggp_sign_flaq = 2;
   
   std::ostringstream buffer1, buffer2, buffer3, buffer4;  // add #include <sstream> at the top of 
                            // the file for this
   std::string fileN1, fileN2, fileN3, fileN4;
   
   std::fstream file;
   std::fstream file2;
   std::fstream file3;
   std::fstream file4;
   std::fstream file5;
   //std::fstream file2;
   
  
   filename3[0] = 'd';
   filename3[1] = 'e';
   filename3[2] = 'r';
   filename3[11] = '.';
   filename3[12] = 'd';
   filename3[13] = 'a';
   filename3[14] = 't';  
      
   for(i = 3; i < 11 ; i++)
   {
     filename1[i] = timedata[i-3]; 
     filename2[i] = timedata[i-3];
     //filename3[i] = timedata[i-3]; 
   }  
   
   ggp_flaq = 3;
   ggp_sign_flaq = 1;
   
   
   filename1[0] = 'o';
   filename1[1] = 'u';
   filename1[2] = 't';
   filename1[11] = '.';
   filename1[12] = 'g';
   filename1[13] = 'g';
   filename1[14] = 'p';
   
   filename2[0] = 'o';
   filename2[1] = 'u';
   filename2[2] = 't';
   filename2[11] = '.';
   filename2[12] = 'd';
   filename2[13] = 'a';
   filename2[14] = 't';
   
   
   /*
   if(ggp_flaq == 1)
   { 
     file.open(filename1,std::ios::out);
     file.precision(10);
     
     OnePeriodProfileData();
     if(ggp_sign_flaq == 1)
     {
       file<< "3 0 - Polygonal type" <<"\n";
       file<<"Period: 1 PSC: 1"<<"\n";
     }
     if(ggp_sign_flaq == 2)
     {
       file<<"3 0 - Polygonal type (was randomized)"<<"\n";
       file<<"Randomize options: 1 0 0 1 1001 0.0001 0.001 3"<<"\n"; 
       file<<"Period: 1.000000 PSC: 1.000000"<<"\n";
     }  
     if(materials_flaq == 1)
     {
       for(i=0; i<= N_ggp_Zr_Al; i++)
         file<< i / Zr_Al_profile_points << "   " << one_period_ggp[i]  <<"\n"; //Zr-Al
     }    
     
     if(materials_flaq == 2)  
     {
       for(i=0; i<= Mo_Si_profile_points; i++)  
         file<< i / Mo_Si_profile_points << "   " << one_period_ggp[i]  <<"\n";  //Mo-Si       
     }
     
     file.close();
   } 
    
   
   if(ggp_flaq == 2)
   {
     file.open(filename2,std::ios::out);
     
     file.precision(10);
     
     for(i=0; i< N; i++)
       file<< i << "   " << hNew[i]  <<"\n";
     file.close();
   }
   */
   
   if(ggp_flaq == 3)
   {
     //printf("check3 output\n");
	 for(int i = 0; i < 15; i++)
     {
       buffer1 << filename1[i];
       buffer2 << filename2[i];
       //buffer3 << filename3[i];
       //buffer4 << filename4[i];
     }
	 
	 fileN1 = buffer1.str();
     fileN2 = buffer2.str();
     
     file.open(fileN1.c_str(),std::ios::out);
     file2.open(fileN2.c_str(),std::ios::out);
     
     //OnePeriodProfileData();  //check what function to use
     MacroProfileData(); 
     
     //printf("check4 output\n");
     if(ggp_sign_flaq == 1)
     {
       file << "3 0 - Polygonal type" <<"\n";
       file <<"Period: 1 PSC: 1"<<"\n";
     } 
     if(ggp_sign_flaq == 2)
     {
       file<<"3 0 - Polygonal type (was randomized)"<<"\n";
       file<<"Randomize options: 1 0 0 1 1001 0.0001 0.001 3"<<"\n"; 
       file<<"Period: 1.000000 PSC: 1.000000"<<"\n";
     }  
     
     //normal output
     for(i=0; i< N; i++)
       file2<< i << "   " << hNew[i]  <<"\n"; 
     //".ggp" output  
     /*
	 if(materials_flaq == 1)
     {
       for(i=0; i<= N_ggp_Zr_Al; i++)
         fileN1<< i / Zr_Al_profile_points << "   " << one_period_ggp[i]  <<"\n"; //Zr-Al
     }    
     
     if(materials_flaq == 2)  
     {
       for(i=0; i<= N_ggp_Mo_Si; i++)  
         file<< i / Mo_Si_profile_points << "   " << one_period_ggp[i]  <<"\n";  //Mo-Si       
     }
     */
     
     if(materials_flaq == 3 || materials_flaq == 4 || materials_flaq == 5)  
     {
     	for(i=0; i<= N_ggp_W_B4C; i++)  
          file<< i / W_B4C_profile_points << "   " << one_period_ggp[i]  <<"\n";  //Mo-Si 
	 }
     
     
     file.close();
     file2.close();
   } 
   
}

void GlobalDataOut( void )
{
   int i, j, k;
   char filename[11];
        
   std::fstream file, file2;
   //std::fstream file2;

   for(i = 0; i < 8; i++)
     filename[i] = ' ';
     
   filename[0] = 'G';
   filename[1] = 'V';
   filename[2] = 'O';
   
   
   for(i = 3; i < 11 ; i++)
     filename[i] = timedata[i-3]; 
   
   file.open(filename,std::ios::out);
  
   
   for(i=0; i< N; i++)
   {
      file<< i << "\n";
      file<< "p0 = " << p0  <<"\n";
      file<< "p1 = " << p1  <<"\n";      
      file<< "p2 = " << p2  <<"\n";
      file<< "p3 = " << p3  <<"\n";      
      file<< "p4 = " << p4  <<"\n";
      file<< "p2n2 = " << p2n2  <<"\n";      
      file<< "t0 = " << t0  <<"\n";
      file<< "t2 = " << t2  <<"\n";      
      file<< "t4 = " << t4  <<"\n";
      file<< "tn = " << tn  <<"\n";   
      file<< "sum = " << hOld[i] + t0 + t2 + t4 + tn  <<"\n";    
      file<< "hOld[" << i << "] = " << hOld[i]  <<"\n";
      //file<< i << "   " << hOld[i] << "   " << h2Old[i] <<"\n";
   }
   
   file.close();
  
}

void FinalOutput( int bilayerN )
{
  int i,j;
  double OnePeriodShift;

  std::fstream file;
  std::fstream file2;
  
  file.open("final_output.dat",std::ios::out);
  file2.open("XZshift_ggp.dat",std::ios::out);
     
  file.precision(10);
     
  for(i=0; i< N; i++)
     file<< i << "   " << hNew[i]  <<"\n";
  file.close();
  
  for(i = 0; i <= bilayerN; i++)
  {
    OnePeriodShift = (double)(Xmax[i])/N_ggp;
    if(OnePeriodShift > 1)
      OnePeriodShift = OnePeriodShift - 1.0;
    if(OnePeriodShift < 0)
      OnePeriodShift = OnePeriodShift + 1.0;  
	file2<< i << "   " << Xmax[i] << "   " << Xmax[i] - XmaxInit << "   " << OnePeriodShift << "   " << Hmax[i] - 11.36916 << "  " << Hmax[i] <<"\n"; //11.36916 is the height of 1.76-19.4 triangle
  }
  file2.close();
  
  
  
}


void InitialProfileOutput( int ProfilePoints )
{
    int i, j, k;
    double dProfilePoints;
    
	FILE *FCopy;
    std::fstream file;
    /*
	FCopy = fopen("profile.ggp","w+");
    fclose(FCopy);	
    */
    dProfilePoints = (double)ProfilePoints;
    
    file.open("initial_profile.ggp",std::ios::out);
    file << "3 0 - Polygonal type" <<"\n";
    file <<"Period: 1 PSC: 1"<<"\n";
    OnePeriodProfileData();
    //MacroProfileData
    for(i=0; i<= N_ggp; i++)  
        file<< i / dProfilePoints << "   " << one_period_ggp[i]  <<"\n"; 
    
    file.close();
}

void SawParams ( int WorkAngle, int nonWorkAngle )
{
  int i,j, ip2, ip3, ip1, im1, im2, im3, k;
  double local_angle;
  FILE *FAngle;
  
  FAngle = fopen("SawAngle","w+");
  
  for(i = 0; i < N; i++)
   {
     
     ip1 = i+1;
     ip2 = i+2;
     ip3 = i+3;
     im1 = i-1;
     im2 = i-2;
     im3 = i-3;
     
     if(i == 0)
     {          
       im3 = N-3;
       im2 = N-2;
       im1 = N-1;       
     }
     if( i == 1)
     {
       im3 = N-2;
       im2 = N - 1;       
     }
     if(i == 2)
       im3 = N-1;       
     if(i == N-3)
       ip3 = 0;
     if(i == N-2)
     {
       ip2 = 0;
       ip3 = 1;
     }    
     if(i == N-1)
     {
       ip1 = 0;
       ip2 = 1;
       ip3 = 2;
     } 	
     
     FullPeriodProfileData();
     p1 = (-1.0 * hOld[ip2] + 8.0 * hOld[ip1] - 8.0 * hOld[im1] + hOld[im2]) / (12.0);
     local_angle = atan(fabs(p1)) * 180 / pi; 
     if(p1 >= 0)
       fprintf(FAngle,"%d  %f  %f\n", i, local_angle, local_angle - WorkAngle);
     if(p1 < 0)  
       fprintf(FAngle,"%d  %f  %f\n", i, local_angle, local_angle - nonWorkAngle);
   }
   
   fclose(FAngle);
}

