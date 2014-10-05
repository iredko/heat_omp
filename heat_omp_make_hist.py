__author__ = 'asus'
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

temp = np.genfromtxt(fname='data.out').T

plt.imshow(temp, cmap=cm.hot)
#plt.show()

res = np.genfromtxt(fname='research.out')
means = [(np.array([i[1] for i in res if i[0]==j]).mean()) for j in range(1,40)]
print means.__len__()
stds = [(np.array([i[1] for i in res if i[0]==j]).std()) for j in range(1,40)]
max_n_threads = 39

fig, ax = plt.subplots()

index = np.arange(max_n_threads)
bar_width = 0.35

opacity = 0.4
error_config = {'ecolor': '0.3'}

rects1 = plt.bar(index, means, bar_width,
                 alpha=opacity,
                 color='b',
                 yerr=stds,
                 error_kw=error_config
                 )

plt.xlabel('Threads')
plt.ylabel('Time in seconds')
plt.title('Execution time by number of threads')
plt.xticks(index + bar_width, range(1,40))
plt.legend()

plt.tight_layout()
plt.show()
