'''
#####################################################################
MIT License

Copyright (c) 2016 SevData

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
#####################################################################
'''

import numpy as np
import matplotlib.pyplot as plt
import random
from Cfast_km import Cfast_km

nb_cluster = 4

X = [[random.random() for i in range(4)] for j in range(100)]

            
#randomly assign mu if not setup
mu = random.sample(X, nb_cluster)


X = np.array(X, dtype="double")
mu = np.array(mu, dtype="double")
labels = np.zeros(len(X), dtype="int")

weights = np.array([1,1,1,1], dtype="double")

Cfast_km(X , mu , labels, weights, 0)


X1 = np.transpose(X[:,0]).tolist()
X2 = np.transpose(X[:,1]).tolist()
mu1 = np.transpose(mu[:,0]).tolist()
mu2 = np.transpose(mu[:,1]).tolist()

fig = plt.figure(figsize=(5,5))
plt.xlim(0,1)
plt.ylim(0,1)
plt.plot(X1, X2, '.', alpha=0.5)
plt.plot(mu1, mu2, 'ro')

plt.show()



