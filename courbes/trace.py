import numpy as np
import matplotlib.pyplot as plt

# plt.xlim(10, 20)
plt.ylim(0, 100)

coef = np.exp(3.0)
min_lim = -5.0
max_lim = 5.0

x = np.arange(-10, 10, 0.01)
y = np.exp( -coef * (x - min_lim) ) + np.exp( -coef * (max_lim - x) )

plt.plot(x, y)
plt.show()