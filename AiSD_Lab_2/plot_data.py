import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('data.txt')
x = data[:, 0]
y = data[:, 1]

plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("y")
plt.title("График y = x^2")
plt.savefig("plot.png")
plt.show()