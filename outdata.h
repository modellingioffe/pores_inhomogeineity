#ifndef _H_OUTDATA_H_
#define _H_OUTDATA_H_

extern int timedata[8];

extern int materials_flaq;  // materials_flaq = 1 Zr-Al      
                     // materials_flaq = 2 Mo-Si
                     
extern int buffer_flaq;

void DegreeR( double check, double degree );

void OutStep( void );

void GlobalDataOut ( void );

void FinalOutput( int bilayerN );

void InitialProfileOutput( int ProfilePoints );

void SawParams ( int WorkAngle, int nonWorkAngle );

#endif
