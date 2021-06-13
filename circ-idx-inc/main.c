#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int const N = 10;

  int index_zero_based = 0;
  int index = 1;


  // Круговой 0-based и 1-based indexing с использованием цикла while:
  while (1)
  {
    index_zero_based = (index_zero_based + 1) % N;
    printf("index_zero_based = %d\n", index_zero_based);

    index = (index % N) + 1;
    printf("index = %d\n", index);
  }


  // Круговой one-based indexing с использованием цикла for:
  for (index = 1; 1; index = index % N + 1 /* у % приоритет выше чем у + */ )
  {
    printf("index = %d\n", index);
  }


  return EXIT_SUCCESS;
}

/*
Если index < N, то выражение index % N будет равно исходному значению index.
Если index = N, то выражение index % N будет равно 0.
Если index > N, то выражение index % N будет равно index - N * n.
*/
