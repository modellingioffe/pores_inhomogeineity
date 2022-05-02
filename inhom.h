#ifndef _H_INHOM_H_
#define _H_INHOM_H_


extern int LocalNodeNumber[1500000]; // number of nodes in cell
extern double LocalDensity[100000]; // local nodes density
extern double AverageDensity; //average nodes density
extern double XLength, YLength; // size of the analized sample
extern double cellXS, cellYS; //x and y sizes of the cell
extern int hOffsetMax[100000]; // hOffset to find maximum
extern double XOffset, YOffset; // values of the current offsets along X and Y
extern double h; // inhomogeinity
extern int PositionAreaFlag;   // indication of calculation of position inhomogeinity or pores area inhomogeinity

int IntPower( int base, int power );

double MaxValue( int n );

double Segmentation( double cellXS, double cellYS, int jN, double XOffset, double YOffset, int CellN );

void InhomCalc( void );

void SelectionR( double ThresV, int LowHighFlag );

void SelectionH( double ThresV, int LowHighFlag );


#endif
