#include <stdio.h>

/* always assuming int is at least 32 bits */
int rseed = 0;

inline void srand(int x)
{
    rseed = x;
}
 
#define RAND_MAX_32 ((1U << 31) - 1)
#define RAND_MAX ((1U << 15) - 1)
 
inline int rand()
{
	return (rseed = (rseed * 214013 + 2531011) & RAND_MAX_32) >> 16;
}
