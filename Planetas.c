#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// DEFINICIONES

#define n 91250
#define G 39.47841760

// FUNCIONES

// Indices para la lectura de la matriz como arreglo lineal

int pos(int i, int j)
{
  return n * i + j;
}

// Aceleracion

void aceleracion(int i, int k, float masas, float *ax, float *ay, float *az, float *x, float *y, float *z)
{
  float ax1 = *ax;
  float ay1 = *ay;
  float az1 = *az;

  ax1 = 0;
  ay1 = 0;
  az1 = 0;
  
  int pos1;
  int pos2;

  int ii = 0;
  float factor;
  float p = 3 / 2;
  
  for(ii = 1; ii < 11; ii++)
  {
    if(ii != i)
    {
      pos1 = n * ii + k;
      pos2 = n * i + k; 
      factor += (G * masas) / (pow(pow(x[pos1] - x[pos2], 2) + pow(y[pos1] - y[pos2], 2) + pow(z[pos1] - z[pos2],2), p));
    }
    *ax = factor * (x[pos1] - x[pos2]);
    *ay = factor * (y[pos1] - y[pos2]);
    *az = factor * (z[pos1] - z[pos2]);
  }
  *ax = ax1;
  *ay = ay1;
  *az = az1;
}

// FUNCION MAIN

int main(void)
{
  // Definicion de variables y constantes
  
  int i = 0, j = 0;
  float dt = 1.0 / 365.0;

  float ax1;
  float ay1;
  float az1;

  float *ax = malloc(sizeof(float));
  float *ay = malloc(sizeof(float));
  float *az = malloc(sizeof(float));

  float *x = malloc((n * 10) * sizeof(float));
  float *y = malloc((n * 10) * sizeof(float));
  float *z = malloc((n * 10) * sizeof(float));

  float *vx = malloc((n * 10) * sizeof(float));
  float *vy = malloc((n * 10) * sizeof(float));
  float *vz = malloc((n * 105) * sizeof(float));
	
  float *vx_05 = malloc(10 * sizeof(float));
  float *vy_05 = malloc(10 * sizeof(float));
  float *vz_05 = malloc(10 * sizeof(float));

  // Inicializacion de lectura para el archivo
  
  FILE *file;
  file = fopen("coordinates.csv", "r");
  int len = 250;

  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;
  delimiter = ",";

  double matriz[10][7];
  
  // Lectura del archivo
  
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

  // Cambio de unidades a unidades solares (Dividir todas las masas por la masa del sol)

  float msol = matriz[0][0];
  
  for (i = 0; i < 10; i++)
  {
    matriz[i][0] = matriz[i][0] / msol;
  }

  // Incluir condiciones iniciales en variables

  for (i = 0; i < 10; i++)
  {
    x[pos(i, 0)] = matriz[i][1];	
    y[pos(i, 0)] = matriz[i][2];
    z[pos(i, 0)] = matriz[i][3];
    vx[pos(i, 0)] = matriz[i][4];
    vy[pos(i, 0)] = matriz[i][5];
    vz[pos(i, 0)] = matriz[i][6];
  }

  // Calcular velocidad media, velocidad y posicion usando la funcion de aceleracion
  
  for (int w = 0; w < n - 1; w++)
  {
    for (i = 0; i < 10; i++)
    {
      aceleracion(i, w, matriz[i][0], ax, ay, az, x, y, z);
      ax1 = *ax;
      ay1 = *ay;
      az1 = *az;

      vx_05[i] = vx[pos(i, w)] + 0.5 * ax1 * dt;
      vy_05[i] = vy[pos(i, w)] + 0.5 * ay1 * dt;
      vz_05[i] = vz[pos(i, w)] + 0.5 * az1 * dt;

      x[pos(i, w + 1)] = x[pos(i, w)] + vx_05[i] * dt;
      y[pos(i, w + 1)] = y[pos(i, w)] + vy_05[i] * dt;	
      z[pos(i, w + 1)] = z[pos(i, w)] + vz_05[i] * dt;

      *ax = ax1;
      *ay = ay1;
      *az = az1;

      aceleracion(i, w + 1, matriz[i][0], ax, ay, az, x, y, z);
      vx[pos(i, w+1)] = vx_05[i] + 0.5 * ax1 * dt;	
      vy[pos(i, w+1)] = vy_05[i] + 0.5 * ay1 * dt;
      vz[pos(i, w+1)] = vz_05[i] + 0.5 * az1 * dt;
    }
  }

  // Imprimir posiciones X, Y y Z para cada planeta
  
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%f %f %f \n", x[pos(i, j)], y[pos(i, j)], z[pos(i, j)]);
    }
  }
  return 0;
}
