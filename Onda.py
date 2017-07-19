import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

Np = 300
a = 0
b = 30

xy = np.linspace(a, b, Np)
dxy = xy[1] - xy[0]

Nt1 = 60
Nt2 = 30

r = 0.5
dt = r * dxy
c = 1.
r_0 = ((c**2) * dt) / (2. * dxy)

barrera = np.ones((Np, Np))
barrera[200] = 0
barrera[200][135 : 165] = 1.

u_0 = np.zeros((Np, Np))
u_0[100][150] = -0.5
u_0 = u_0 * barrera

u_fut = np.zeros((Np, Np))

lis = []
lis.append(u_0)

def it_tiempo(N):
    for i in range(1, (Np - 1)):
        for j in range(1, (Np - 1)):
            u_fut[i][j] = u_0[i][j] + (r_0 * (u_0[i + 1][j] - u_0[i - 1][j] + u_0[i][j + 1] - u_0[i][j - 1]))

    u_past = u_0.copy()
    u_pres = u_fut.copy() * barrera
    lis.append(u_pres)

    for t in range(1, int(N / dt)):
        for i in range(1, Np - 1):
            for j in range(1, Np - 1):
                u_fut[i][j] = ((r**2) * (u_pres[i + 1][j] + u_pres[i - 1][j] + u_pres[i][j + 1] + u_pres[i][j - 1])) + (2. * (1. - (2. * (r**2))) * u_pres[i][j]) - u_past[i][j]
        u_past = u_pres.copy()
        u_pres = u_fut.copy() * barrera
        lis.append(u_pres)

    return lis

t_60 = it_tiempo(Nt1)
mat_30 = t_60[int(Nt2 / dt)]
mat_60 = t_60[int(Nt1 / dt)]

#plt.imshow(mat_30, cmap = 'gray')
#plt.title('Onda en t = 30s')
#plt.savefig('Ondas_30.png')
#plt.close()

#plt.imshow(mat_60, cmap = 'gray')
#plt.title('Onda en t = 60s')
#plt.savefig('Ondas_60.png')
#plt.close()

fig = plt.figure(figsize = (15, 15))
contenedor = plt.imshow(t_60[0], cmap = 'hot')
nueva_it = []

for i in range(len(t_60)):
    if (i % 50 == 0):
        nueva_it.append(t_60[i])
        i += 1
    else:
        i += 1

def func(i):
    datos = nueva_it[i]
    contenedor.set_array(datos),
    return contenedor,

anmt = animation.FuncAnimation(fig, func, np.arange(0, len(nueva_it)), interval = 200)
anmt.save('Onda.mp4')
plt.close()
