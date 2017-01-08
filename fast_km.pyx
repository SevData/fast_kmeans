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

cimport numpy as np 
import numpy as np

cdef extern from "fast_km.h":
	void fast_km(double *data_in, int n, int m, int k, double t, double *init_centers,long *labels_output, double *weights)

def Cfast_km(np.ndarray[np.float64_t, ndim=2, mode="c"] a not None, np.ndarray[np.float64_t, ndim=2, mode="c"] centroids not None,\
		np.ndarray[long, ndim=1, mode="c"] labels_output not None, np.ndarray[np.float64_t, ndim=1, mode="c"] weights not None, tolerance ):
	return fast_km(<double*> a.data, a.shape[0], a.shape[1], centroids.shape[0], tolerance,<double*> centroids.data,  <long *> labels_output.data,\
		<double*> weights.data)