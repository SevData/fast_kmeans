/*
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
*/


#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "fast_km.h"



void fast_km(double *data_in, int n, int nb_dimension, int nb_cluster, double tolerance, double *init_centers, long *labels_output, double *weights)
{

   double **data = (double**)calloc(n, sizeof(double*)); /*data init*/

   double **mu = (double**)calloc(nb_cluster, sizeof(double*)); /*data init*/

   double *D2 = (double*)calloc(n, sizeof(double)); /* D2*/

   double sumD2, tempD2,  rand01 ;

   int *counts = (int*)calloc(nb_cluster, sizeof(int)); /* size of each cluster */
   double old_error, error = 99999; /* sum of squared euclidean distance */

   double **centroids_temp = (double**)calloc(nb_cluster, sizeof(double*)); /* temp centroids */
   
   /* output cluster label for each data point */
   long *labels = (long*)calloc(n, sizeof(long));
   int h, i, j, k;
   double powe;
   double distance;
   double min_distance;
   
   /* memory allocation */

   for (i = 0; i < n; i++) {
      data[i] = (double*)calloc(nb_dimension, sizeof(double));
      for (j = 0; j < nb_dimension; j++) {
         data[i][j] = data_in[i*nb_dimension + j];
      }
   }

   for (i = 0; i < nb_cluster; i++) {
      mu[i] = (double*)calloc(nb_dimension, sizeof(double));
      for (j = 0; j < nb_dimension; j++) {
         mu[i][j] = init_centers[i*nb_dimension + j];
      }
      centroids_temp[i] = (double*)calloc(nb_dimension, sizeof(double));
   }


   for (i = 1; i < nb_cluster; i++) {
      sumD2 = 0;
      for (h = 0; h < n; h++) {

         ///compute distance for nearest centroid already computed 
         min_distance = 99999;

         for (k = 0; k < i; k++) {
      
            distance = 0;
            for (j = 0; j < nb_dimension; j++) {
               powe = (data[h][j] - mu[k][j]) * weights[j];
               distance += powe*powe;
            }

            if (distance < min_distance) {
               min_distance = distance;
            }

         }

         D2[h] = min_distance ;
         sumD2 += min_distance ;  


      }
      rand01 = (double) rand() / (double) RAND_MAX ;
      
      h = 0;
      tempD2 = 0;
      do {
         tempD2 += D2[h] / sumD2 ;
         h++ ;

      } while (tempD2 < rand01);

      for (j = 0; j < nb_dimension; j++) {
         mu[i][j] = data[h-1][j];
      }


   }

   /**compute kmeans */

   do {
      /* save error from last step */
      old_error = error;
      error = 0;


      /* clear old counts and temp centroids */
      for (i = 0; i < nb_cluster; i++) {
         counts[i] = 0;
         for (j = 0; j < nb_dimension; j++) {
            centroids_temp[i][j] = 0;
         }
      }

      for (h = 0; h < n; h++) {
         /* identify the closest cluster */
         min_distance = 99999;
         for (i = 0; i < nb_cluster; i++) {
            distance = 0;

            for (j = 0; j < nb_dimension; j++) {
               powe = (data[h][j] - mu[i][j]) * weights[j];
               distance += powe*powe;
            }

            if (distance < min_distance) {
               labels[h] = i;
               min_distance = distance;
            }


         }
         error += min_distance;
         
         /* count number of X per cluster and sum of values on all dimension for mean computation*/
         for (j = 0; j < nb_dimension; j++) {
            centroids_temp[labels[h]][j] += data[h][j];
         }
         counts[labels[h]]+= 1;
      }

      /* compute mean */
      for (i = 0; i < nb_cluster; i++) { 
         for (j = 0; j < nb_dimension; j++) {
            mu[i][j] =  centroids_temp[i][j] / counts[i];
         }
      }

   } while (fabs(error-old_error) > tolerance);


   /* memory cleaning */

   for (i = 0; i < nb_cluster; i++) {
      for (j = 0; j < nb_dimension; j++) {
         init_centers[i*nb_dimension + j] = mu[i][j];
      }
   }

   for (i = 0; i < n; i++) {
      for (j = 0; j < nb_dimension; j++) {
         data_in[i*nb_dimension + j] = data[i][j] ;
      }
   }

   for (i = 0; i < n; i++) {
      labels_output[i] = labels[i];
   }

   for (i = 0; i < nb_cluster; i++) {
      free(centroids_temp[i]);
      free(mu[i]);
   }

   for (h = 0; h < n; h++) {
      free(data[h]);
   }

   free(mu);
   free(centroids_temp);
   free(counts);
   free(D2);
   free(data);
   free(labels);

   return;




}