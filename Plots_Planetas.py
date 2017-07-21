import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Constantes

N = 912500
NN = N / 10

# Lectura de datos

datos = np.genfromtxt('datos.txt')

datos_x = datos[:, 0]
datos_y = datos[:, 1]
datos_z = datos[:, 2]

# Listas para los indices

l_0 = []
l_1 = []
l_2 = []
l_3 = []
l_4 = []
l_5 = []
l_6 = []
l_7 = []
l_8 = []
l_9 = []

# Matrices para las posiciones en x, y, z

sol_m = np.ones((NN, 3))
mercurio_m = np.ones((NN, 3))
venus_m = np.ones((NN, 3))
tierra_m = np.ones((NN, 3))
marte_m = np.ones((NN, 3))
jupiter_m = np.ones((NN, 3))
saturno_m = np.ones((NN, 3))
uranio_m = np.ones((NN, 3))
neptuno_m = np.ones((NN, 3))
pluton_m = np.ones((NN, 3))

# Metodo para almacenar los indices en las listas

def listas(lista, n):
    for i in range(10):
        j = 0
        if (i == n):
            for j in range(NN):
                num = i + (10 * j)
                lista.append(num)
    return lista

sol_l = listas(l_0, 0)
mercurio_l = listas(l_1, 1)
venus_l = listas(l_2, 2)
tierra_l = listas(l_3, 3)
marte_l = listas(l_4, 4)
jupiter_l = listas(l_5, 5)
saturno_l = listas(l_6, 6)
uranio_l = listas(l_7, 7)
neptuno_l = listas(l_8, 8)
pluton_l = listas(l_9, 9)

# Metodo para cambiar los valores en las matrices

def posiciones(lista, matriz):
    j = 0
    for i in lista:
        matriz[j, 0] = datos_x[i]
        matriz[j, 1] = datos_y[i]
        matriz[j, 2] = datos_z[i]
        j += 1
    return matriz

sol = posiciones(sol_l, sol_m)
mercurio = posiciones(mercurio_l, mercurio_m)
venus = posiciones(venus_l, venus_m)
tierra = posiciones(tierra_l, tierra_m)
marte = posiciones(marte_l, marte_m)
jupiter = posiciones(jupiter_l, jupiter_m)
saturno = posiciones(saturno_l, saturno_m)
uranio = posiciones(neptuno_l, neptuno_m)
neptuno = posiciones(uranio_l, uranio_m)
pluton = posiciones(pluton_l, pluton_m)

# Grafica en 3D de las orbitas de los planetas

figura_3d = plt.figure()
ax = figura_3d.gca(projection='3d')

ax.plot(sol[:, 0], sol[:, 1], sol[:, 2], label = 'Sol')
ax.plot(mercurio[:, 0], mercurio[:, 1], mercurio[:, 2], label = 'Mercurio')
ax.plot(venus[:, 0], venus[:, 1], venus[:, 2], label = 'Venus')
ax.plot(tierra[:, 0], tierra[:, 1], tierra[:, 2], label = 'Tierra')
ax.plot(marte[:, 0], marte[:, 1], marte[:, 2], label = 'Marte')
ax.plot(jupiter[:, 0], jupiter[:, 1], jupiter[:, 2], label = 'Jupiter')
ax.plot(saturno[:, 0], saturno[:, 1], saturno[:, 2], label = 'Saturno')
ax.plot(uranio[:, 0], uranio[:, 1], uranio[:, 2], label = 'Uranio')
ax.plot(neptuno[:, 0], neptuno[:, 1], neptuno[:, 2], label = 'Neptuno')
ax.plot(pluton[:, 0], pluton[:, 1], pluton[:, 2], label = 'Pluton')
ax.legend()

plt.savefig('Orbitas.pdf')
plt.close()
