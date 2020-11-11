# Thanks to: https://matplotlib.org/gallery/api/two_scales.html
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def preprocess_data(container, func):
    times = np.loadtxt(f'./measurements/{container}_{func}.txt')
    avg = np.median(times, axis=0)
    return pd.Series(avg).rolling(10).median()


#%%
# Create prepend plots
func = 'prepend'
lst = preprocess_data('list', func)
deque = preprocess_data('deque', func)
vector = preprocess_data('vector', func)

fig, ax1 = plt.subplots(figsize=(12, 4))
ax1.set_xlabel('Container Size')
ax1.set_ylabel('Nanoseconds - List & Deque')
ax1.plot(list(range(len(lst))), lst, color='orange', label='List')
ax1.plot(list(range(len(deque))), deque, color='blue', label='Deque')

ax2 = ax1.twinx()
ax2.set_ylabel('Nanoseconds - Vector')
ax2.plot(list(range(len(vector))), vector, color='red', label='Vector')

fig.tight_layout()
ax2.legend()
ax1.legend(loc='center left')
plt.title(f'Comparison of containers for ${func}$ -- Vector is not a suitable choice')
plt.savefig(f'./figures/{func}', bbox_inches='tight')
plt.show()
#%%
# Create append plots
func = 'append'
lst = preprocess_data('list', func)
deque = preprocess_data('deque', func)
vector = preprocess_data('vector', func)

plt.figure(figsize=(12, 4))
plt.xlabel('Container Size')
plt.ylabel('Nanoseconds')
plt.ylim(0, 200)
plt.plot(list(range(len(lst))), lst, color='orange', label='List')
plt.plot(list(range(len(deque))), deque, color='blue', label='Deque')
plt.plot(list(range(len(vector))), vector, color='red', label='Vector')

plt.tight_layout()
plt.legend()
plt.title(f'Comparison of containers for ${func}$ -- Constant of list is higher')
plt.savefig(f'./figures/{func}', bbox_inches='tight')
plt.show()
#%%
# Create middle plots
func = 'middle'
lst = preprocess_data('list', func)
deque = preprocess_data('deque', func)
vector = preprocess_data('vector', func)
#%%
fig, ax1 = plt.subplots(figsize=(12, 4))
ax1.set_xlabel('Container Size')
ax1.set_ylabel('Nanoseconds - List & Vector')
ax1.plot(list(range(len(lst))), lst, color='orange', label='List')
ax1.plot(list(range(len(vector))), vector, color='red', label='Vector')
ax1.set_ylim(0, 75000)

ax2 = ax1.twinx()
ax2.set_ylabel('Nanoseconds - Deque')
ax2.plot(list(range(len(deque))), deque, color='blue', label='Deque')

fig.tight_layout()
ax2.legend(loc='center left')
ax1.legend(loc='upper left')
plt.title(f'Comparison of containers for ${func}$ insertion -- List is the way to go')
plt.savefig(f'./figures/{func}', bbox_inches='tight')
plt.show()
