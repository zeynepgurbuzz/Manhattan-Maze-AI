#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

/*
   Student Name: Zeynep Gürbüz
   Course: Programming for Engineers

   Thief vs Police Maze Game (16x16)
   Escape point: (7,15) [0-based]
*/

#define ROWS 16
#define COLS 16

#define ESCAPE_ROW 7
#define ESCAPE_COL 15

#define EMPTY ' '
#define WALL  'W'
#define EXIT  'E'

typedef struct
{
   int r;
   int c;
} Position;

/* function prototypes */
int absInt( int x );
int manhattan( Position a, Position b );
int inBounds( int r, int c );

void initMaze( void );
void spawnCharacters( void );
void printMaze( void );

void moveThief( void );
void movePoliceEasy( void );
void movePoliceHard( void );

int canSpawnAt( int r, int c );
int policeCanStep( int r, int c );

int readIntRange( const char *prompt, int low, int high );
void flushLine( void );

/* global variables */
char maze[ ROWS ][ COLS ];
Position thief;
Position police;
Position prevPolice;

/* ---------- helpers ---------- */

int absInt( int x )
{
   return ( x < 0 ) ? -x : x;
}

int manhattan( Position a, Position b )
{
   return absInt( a.r - b.r ) + absInt( a.c - b.c );
}

int inBounds( int r, int c )
{
   return ( r >= 0 && r < ROWS && c >= 0 && c < COLS );
}

void flushLine( void )
{
   int ch;
   while ( ( ch = getchar() ) != '\n' && ch != EOF )
   {
      ;
   }
}

int readIntRange( const char *prompt, int low, int high )
{
   int value;

   while ( 1 )
   {
      printf( "%s", prompt );

      if ( scanf( "%d", &value ) != 1 )
      {
         flushLine();
         printf( "Please enter a number.\n" );
         continue;
      }

      if ( value < low || value > high )
      {
         printf( "Enter a value between %d and %d.\n", low, high );
         continue;
      }

      return value;
   }
}

/* ---------- maze ---------- */

void initMaze( void )
{
   int r, c;

   for ( r = 0; r < ROWS; r++ )
   {
      for ( c = 0; c < COLS; c++ )
      {
         maze[ r ][ c ] = EMPTY;
      }
   }

   maze[ ESCAPE_ROW ][ ESCAPE_COL ] = EXIT;

   Position walls[] =
   {
      { 0,  8 }, { 1,  8 },
      { 2,  2 }, { 3,  2 },
      { 2, 13 }, { 3, 13 },
      { 5,  6 }, { 5,  7 }, { 5,  8 }, { 6,  6 },
      { 8, 10 },
      { 9,  3 }, { 9,  4 }, { 9,  5 }, { 10, 5 },
      { 9, 10 }, { 10,10 }, { 11,10 }, { 11,11 },
      { 14, 2 }, { 14, 3 }, { 14, 4 }
   };

   int n = sizeof( walls ) / sizeof( walls[ 0 ] );

   for ( int i = 0; i < n; i++ )
   {
      r = walls[ i ].r;
      c = walls[ i ].c;

      if ( inBounds( r, c ) && !( r == ESCAPE_ROW && c == ESCAPE_COL ) )
      {
         maze[ r ][ c ] = WALL;
      }
   }
}

int canSpawnAt( int r, int c )
{
   if ( !inBounds( r, c ) ) return 0;
   if ( maze[ r ][ c ] == WALL ) return 0;
   if ( maze[ r ][ c ] == EXIT ) return 0;
   return 1;
}

void spawnCharacters( void )
{
   Position escape = { ESCAPE_ROW, ESCAPE_COL };

   do
   {
      thief.r = rand() % ROWS;
      thief.c = rand() % COLS;
   } while ( !canSpawnAt( thief.r, thief.c ) ||
             manhattan( thief, escape ) < 16 );

   do
   {
      police.r = rand() % ROWS;
      police.c = rand() % COLS;
   } while ( !canSpawnAt( police.r, police.c ) ||
             ( police.r == thief.r && police.c == thief.c ) ||
             manhattan( police, thief ) < 16 );

   prevPolice.r = -1;
   prevPolice.c = -1;
}

/* ---------- drawing ---------- */

void printMaze( void )
{
   system( CLEAR_COMMAND );

   printf( "    " );
   for ( int c = 0; c < COLS; c++ )
   {
      printf( "%2d ", c );
   }
   printf( "\n" );

   for ( int r = 0; r < ROWS; r++ )
   {
      printf( "%2d  ", r );

      for ( int c = 0; c < COLS; c++ )
      {
         if ( r == thief.r && c == thief.c )
            printf( " T " );
         else if ( r == police.r && c == police.c )
            printf( " P " );
         else
            printf( " %c ", maze[ r ][ c ] );
      }
      printf( "\n" );
   }

   printf( "\nUse w/a/s/d. Escape: ( %d, %d )\n",
           ESCAPE_ROW, ESCAPE_COL );
}

/* ---------- moves ---------- */

void moveThief( void )
{
   while ( 1 )
   {
      char key;
      int nr = thief.r;
      int nc = thief.c;

      printf( "Move ( w/a/s/d ): " );

      if ( scanf( " %c", &key ) != 1 )
      {
         flushLine();
         continue;
      }

      if ( key == 'w' ) nr--;
      else if ( key == 's' ) nr++;
      else if ( key == 'a' ) nc--;
      else if ( key == 'd' ) nc++;
      else
      {
         printf( "Invalid key.\n" );
         continue;
      }

      if ( !inBounds( nr, nc ) )
      {
         printf( "Out of bounds.\n" );
         continue;
      }

      if ( maze[ nr ][ nc ] == WALL )
      {
         printf( "Wall.\n" );
         continue;
      }

      thief.r = nr;
      thief.c = nc;
      break;
   }
}

int policeCanStep( int r, int c )
{
   if ( !inBounds( r, c ) ) return 0;
   if ( maze[ r ][ c ] == WALL ) return 0;
   return 1;
}

void movePoliceEasy( void )
{
   int dr[ 4 ] = { -1, 1, 0, 0 };
   int dc[ 4 ] = { 0, 0, -1, 1 };

   Position options[ 4 ];
   int count = 0;

   for ( int k = 0; k < 4; k++ )
   {
      int nr = police.r + dr[ k ];
      int nc = police.c + dc[ k ];

      if ( policeCanStep( nr, nc ) )
      {
         options[ count ].r = nr;
         options[ count ].c = nc;
         count++;
      }
   }

   if ( count == 0 ) return;

   prevPolice = police;
   police = options[ rand() % count ];
}

void movePoliceHard( void )
{
   int dr[ 4 ] = { -1, 1, 0, 0 };
   int dc[ 4 ] = { 0, 0, -1, 1 };

   Position moves[ 4 ];
   int moveCount = 0;

   for ( int k = 0; k < 4; k++ )
   {
      int nr = police.r + dr[ k ];
      int nc = police.c + dc[ k ];

      if ( policeCanStep( nr, nc ) )
      {
         moves[ moveCount ].r = nr;
         moves[ moveCount ].c = nc;
         moveCount++;
      }
   }

   if ( moveCount == 0 ) return;

   int minDist = 9999;

   for ( int i = 0; i < moveCount; i++ )
   {
      int d = manhattan( moves[ i ], thief );
      if ( d < minDist ) minDist = d;
   }

   Position best[ 4 ];
   int bestCount = 0;

   for ( int i = 0; i < moveCount; i++ )
   {
      if ( manhattan( moves[ i ], thief ) == minDist )
      {
         best[ bestCount ] = moves[ i ];
         bestCount++;
      }
   }

   Position filtered[ 4 ];
   int filteredCount = 0;

   if ( prevPolice.r != -1 )
   {
      for ( int i = 0; i < bestCount; i++ )
      {
         if ( !( best[ i ].r == prevPolice.r &&
                 best[ i ].c == prevPolice.c ) )
         {
            filtered[ filteredCount ] = best[ i ];
            filteredCount++;
         }
      }
   }

   prevPolice = police;

   if ( filteredCount > 0 )
      police = filtered[ rand() % filteredCount ];
   else
      police = best[ rand() % bestCount ];
}

/* ---------- main ---------- */

int main( void )
{
   srand( ( unsigned ) time( NULL ) );

   while ( 1 )
   {
      int difficulty =
         readIntRange( "Difficulty ( 1=Easy, 2=Hard ): ", 1, 2 );

      /* controls info (shown once per game) */
      printf( "\nControls:\n" );
      printf( "  w : move up\n" );
      printf( "  s : move down\n" );
      printf( "  a : move left\n" );
      printf( "  d : move right\n\n" );
      printf( "Press ENTER to start...\n" );
      getchar();   /* clear newline */
      getchar();   /* wait */

      initMaze();
      spawnCharacters();

      while ( 1 )
      {
         printMaze();
         moveThief();

         if ( thief.r == police.r && thief.c == police.c )
         {
            printMaze();
            printf( "You lost!\n" );
            break;
         }

         if ( thief.r == ESCAPE_ROW && thief.c == ESCAPE_COL )
         {
            printMaze();
            printf( "You won!\n" );
            break;
         }

         if ( difficulty == 1 )
            movePoliceEasy();
         else
            movePoliceHard();

         if ( thief.r == police.r && thief.c == police.c )
         {
            printMaze();
            printf( "You lost!\n" );
            break;
         }
      }

      if ( readIntRange( "Play again? ( 1=Yes, 0=No ): ", 0, 1 ) == 0 )
         break;
   }

   return 0;
}
