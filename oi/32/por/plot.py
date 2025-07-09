import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5, 6]
#y = [3, 1, 2, 4, 6, 5]
y = [1, 3, 2, 4, 6, 5]

plt.plot(x, y, marker='o', linestyle='-', color='b', label='Data')

plt.grid(True)
plt.show()
