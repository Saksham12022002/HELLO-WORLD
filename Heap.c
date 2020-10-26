#include <stdio.h>
void restoreup ( int, int * ) ;
void restoredown ( int, int *, int ) ;
void makeheap ( int *, int ) ;
void add ( int, int *, int * ) ;
int replace ( int, int *, int ) ;
int del ( int *, int * ) ;
void main( )
{
 int arr [20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 } ;
 int i, n = 15 ;
 makeheap ( arr, n ) ;
 printf ("Heap:\n" ) ;
 for ( i = 1 ; i <= n ; i++ )
 printf ( "%d\t", arr [i] ) ;
 i = 5 ;
 add ( i, arr, &n ) ;
 printf ( "\nElement added %d.\n", i ) ;
 printf ( "\nHeap after addition of an element:\n" ) ;
 for ( i = 1 ; i <= n ; i++ )
 printf ( "%d\t", arr [i] ) ; 
 i = replace ( 2, arr, n ) ;
 printf ( "\n\nElement replaced %d.\n", i ) ;
 printf ( "\nHeap after replacement of an element:\n" ) ;
 for ( i = 1 ; i <= n ; i++ )
 printf ( "%d\t", arr [i] ) ;
 i = del ( arr, &n ) ;
 printf ( "\nElement deleted %d.\n", i ) ;
 printf ( "\nHeap after deletion of an element:\n" ) ;
 for ( i = 1 ; i <= n ; i++ )
 printf ( "%d\t", arr [i] ) ;
}
void restoreup ( int i, int *arr )
{
 int val ;
 val = arr [i] ;
 while ( arr [i / 2] <= val )
 {
 arr [i] = arr [i / 2] ;
 i = i / 2 ;
 }
 arr [i] = val ;
}
void restoredown ( int pos, int *arr, int n )
{
 int i, val ;
 val = arr [pos] ;
 while ( pos <= n / 2 )
 {
 i = 2 * pos ;
 if ( ( i < n ) && ( arr [i] < arr [i + 1] ) )
 i++ ;
 if ( val >= arr [i] )
 break ;
 arr [pos] = arr [i] ;
 pos = i ; 
 }
 arr [pos] = val ;
}
void makeheap ( int *arr, int n )
{
 int i ;
 for ( i = n / 2 ; i >= 1 ; i-- )
 restoredown ( i, arr, n ) ;
}
void add ( int val, int *arr, int *n )
{
 ( *n ) ++ ;
 arr [*n] = val ;
 restoreup ( *n, arr ) ;
}
int replace ( int i, int *arr, int n )
{
 int r = arr [1] ;
 arr [1] = i ;
 for ( i = n / 2 ; i >= 1 ; i-- )
 restoredown ( i, arr, n ) ;
 return r ;
}
int del ( int *arr, int *n )
{
 int val ;
 val = arr [1] ;
 arr [1] = arr [*n] ;
 ( *n ) -- ;
 restoredown ( 1, arr, *n ) ;
 return val ;
}
