#ifndef _H_INIT_H_
#define _H_INIT_H_

extern double Xc[10000], Yc[10000];
extern double Height[10000], Radius[10000];
extern double XcCurr[10000], YcCurr[10000];
extern int N;

void Init ( void );

void Out( void );

void GenerationNodes( void );

void GenerationNodesR( int qsize );

#endif
