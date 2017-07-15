import numpy as np
import matplotlib.pyplot as plt

Np = 300
a = 0
b = 30

xy = np.linspace(a, b, Np)
dxy = xy[1] - xy[0]

Nt1 = 60
Nt2 = 30
dt = 0.5 * dxy

c = 1.
r_0 = ((c**2) * dt) / (2. * dxy)
r = 0.5

u_0 = np.zeros((Np, Np))
u_0[150][100] = -0.5

u_fut = np.zeros((Np, Np))

lis = []
lis.append(u_0)

def it_tiempo(N):
    for i in range(1, (Np - 1)):
        for j in range(1, (Np - 1)):
            u_fut[i][j] = u_0[i][j] + (r_0 * (u_0[i + 1][j] - u_0[i - 1][j] + u_0[i][j + 1] - u_0[i][j - 1]))

    u_past = u_0.copy()
    u_pres = u_fut.copy()
    lis.append(u_pres)

    for t in range(N):
        for i in range(1, Np - 1):
            for j in range(1, Np - 1):
                u_fut[i][j] = ((r**2) * (u_pres[i + 1][j] + u_pres[i - 1][j] + u_pres[i][j + 1] + u_pres[i][j - 1])) + (2. * (1. - (2. * (r**2))) * u_pres[i][j]) - u_past[i][j]
        u_past = u_pres.copy()
        u_pres = u_fut.copy()
        lis.append(u_pres)

    return lis

t_60 = it_tiempo(Nt1)
mat_30 = t_60[Nt2]
mat_60 = t_60[Nt1]

print mat_30[150][100]
print mat_60[150][100]
