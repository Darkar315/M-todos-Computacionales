#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 1000
#define G 39,47841760

int pos(int i, int j)
{
  return n * i + j;
}

int main(void)
{
  FILE *file;
  file = fopen("coordinates.csv", "r");

  int len = 250;
  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;
  delimiter = ",";
  
  int i = 0, j = 0;
  double matriz[10][7];

  while (fgets(line_buffer, len, file))
  {
    j = 0;
    split_buffer = strtok(line_buffer, delimiter);
    while (split_buffer != NULL)
    {
      if (j != 0)
      {
	matriz[i][j - 1] = atof(split_buffer);
      }
      split_buffer = strtok(NULL, delimiter);

      j += 1;
    }
    i += 1;
  }

  float *x = malloc((10 * n) * sizeof(float));
  float *y = malloc((10 * n) * sizeof(float));
  float *z = malloc((10 * n) * sizeof(float));

  float *vx = malloc((10 * n) * sizeof(float));
  float *vy = malloc((10 * n) * sizeof(float));
  float *vz = malloc((10 * n) * sizeof(float));

  float *vx_05 = malloc(10 * sizeof(float));
  float *vy_05 = malloc(10 * sizeof(float));
  float *vz_05 = malloc(10 * sizeof(float));

  float m_sol = matriz[0][0];

  for (i = 0; i < 10; i++)
  {
    matriz[i][0] = matriz[i][0] / m_sol;
  }

  // Imprimir Matriz
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 7; j++)
    {
      printf("%f\n", matriz[i][j]);
    }
  }
  // Final Imprimir Matriz
  
  return 0;
}
