// Remi Andruccioli
// June 2023
// Public domain
//
// This program finds the biggest square we can draw on a crossword grid,
// covering only white squares.
// Interview question.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERBOSE (0)

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define GRID_LENGTH (10u)
#define GRID_HEIGHT (10u)

#define _ (false)
#define O (true)

static const bool grid[GRID_LENGTH][GRID_HEIGHT] = {
       //   1  2  3  4  5  6  7  8  9  10
 /*  1 */ { O, O, _, _, _, _, _, _, _, _ },
 /*  2 */ { O, _, _, _, O, _, _, _, _, _ },
 /*  3 */ { _, _, _, _, _, _, _, O, _, _ },
 /*  4 */ { _, _, O, _, _, _, _, _, _, _ },
 /*  5 */ { _, _, _, _, O, _, _, _, _, _ },
 /*  6 */ { _, _, O, _, _, _, _, _, _, _ },
 /*  7 */ { O, _, _, _, _, _, _, _, O, _ },
 /*  8 */ { _, _, O, _, _, _, _, O, _, _ },
 /*  9 */ { _, _, _, _, _, _, _, _, _, O },
 /* 10 */ { O, _, _, _, _, O, _, O, _, _ }
};

#undef _
#undef O

static bool
contains_black_square(const unsigned int x,
                      const unsigned int y,
                      const unsigned int side,
                      unsigned int * const max_y)
{
  bool has_black_square = false;

  *max_y = y;
  unsigned int next_j = y;
  
  if (VERBOSE) {
      fprintf(stdout, "Testing x = %u, y = %u, side = %u\n", x + 1, y + 1, side);
  }

  for (unsigned int i = x, max_i = x + side; i < max_i; ++i) {
    for (unsigned int j = next_j, max_j = *max_y + side; j < max_j; ++j) {
      if (grid[i][j]) {
        if (j == max_j) {
          *max_y = j;
          
          return true;
        }
        
        if (j > *max_y) {
          *max_y = j;
          next_j = j + 1u;
        }
        
        has_black_square = true;
      }
    }
  }

  return has_black_square;
}

static void
find_square(void)
{
  unsigned int x = 0u;
  unsigned int y = 0u;
  unsigned int max_side = 0u;
  
  for (unsigned int i = 0u; i < GRID_LENGTH; ++i) {
    for (unsigned int j = 0u; j < GRID_HEIGHT; ++j) {
      for (unsigned int side = max_side + 1u;
           side <= MIN(MIN(MIN(GRID_LENGTH, GRID_HEIGHT), (GRID_LENGTH - i)), (GRID_HEIGHT - j));
           ++side) {
        unsigned int max_y;
        
        if (contains_black_square(i, j, side, &max_y)) {
          j = max_y;

          break;
        } else {
          max_side = side;
          x = i;
          y = j;

          if (VERBOSE) {
              fprintf(stdout, "New record!\n");
          }
        }
      }
    }
  }

  fprintf(stdout, "x = %u, y = %u, side = %u\n", x + 1u, y + 1u, max_side);
}

int
main(void)
{
  find_square();

  return EXIT_SUCCESS;
}
