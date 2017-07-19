#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definicion Constantes

#define n 91250
#define G 39.47841760
#define PI 3.14159

// Funcion aceleracion

void aceleracion(int i, int dn, float *ax, float *ay, float *az, float *x, float *y, float *z, float *masas)
{
  float factor = 0;
  int ii;
  int j;

  int posi1 = n * ii + j;
  int posi2 = n * i + j;

  for (j = 0; j < dn; j++)
  {
    for (ii = 0; ii < 10; ii++)
      {
	if (ii != i)
	  {
	    factor += (G * masas[ii]) / pow(pow(x[posi1] - x[posi2], 2.0) + pow(y[posi1] - y[posi2], 2.0) + pow(z[posi1] - z[posi2], 2.0), (3.0 / 2.0));
	  }
      }
  }

  *ax += factor * (x[posi1] - x[posi2]);
  *ay += factor * (y[posi1] - y[posi2]);
  *az += factor * (z[posi1] - z[posi2]);
}

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
    
  float dt = 1. / 365.;
  float *masas;
  
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

  float *vx_05 = malloc(n * sizeof(float));
  float *vy_05 = malloc(n * sizeof(float));
  float *vz_05 = malloc(n * sizeof(float));

  for (i = 0; i < 7; i ++)
  {
    x[pos(i, 0)] = matriz[i][1];
    y[pos(i, 0)] = matriz[i][2];
    z[pos(i, 0)] = matriz[i][3];
    vx[pos(i, 0)] = matriz[i][4];
    vy[pos(i, 0)] = matriz[i][5];
    vz[pos(i, 0)] = matriz[i][6];
  }

  float m_sol = matriz[0][0];

  for (i = 0; i < 10; i++)
  {
    matriz[i][0] = matriz[i][0] / m_sol;
  }

  /*/ Imprimir Matriz
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 7; j++)
    {
      printf("%e\n", matriz[i][j]);
    }
  }
  */// Final Imprimir Matriz

  for (i = 0; i < 10; i ++)
  {
    masas[i] = matriz[i][0];
  }

  float ax, ay, az;

  for (j = 0; j < n; j ++)
  {
    ax = 0;
    ay = 0;
    az = 0;
    for (i = 0; i < 10; i ++)
    {
      aceleracion(i, n, &ax, &ay, &az, x, y, z, masas);
      vx_05[i] = vx[pos(i, j)] + 0.5 * ax * dt;
      vy_05[i] = vy[pos(i, j)] + 0.5 * ay * dt;
      vz_05[i] = vz[pos(i, j)] + 0.5 * az * dt;

      x[pos(i, j + 1)] = x[pos(i, j)] + vx_05[i] * dt;
      y[pos(i, j + 1)] = y[pos(i, j)] + vy_05[i] * dt;
      z[pos(i, j + 1)] = z[pos(i, j)] + vz_05[i] * dt;
    }
    
    for (i = 0; i < n; i ++)
    {
      aceleracion(i, (n + 1), &ax, &ay, &az, x, y, z, masas);
      vx[pos(i, n + 1)] = vx_05[i] + 0.5 * ax * dt;
      vy[pos(i, n + 1)] = vy_05[i] + 0.5 * ay * dt;
      vz[pos(i, n + 1)] = vz_05[i] + 0.5 * ay * dt;
    }
  }
  return 0;
}
