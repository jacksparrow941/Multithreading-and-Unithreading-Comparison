#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include<sys/time.h>
#include"func.h"
const double micro = 1.0e-6;
long long Num_of_thread,n;
double sum,sum1=1.0;
sem_t sem;

double calculateTime()
{
 struct timeval TV;
 struct timezone TZ;
 int RC = gettimeofday(&TV,&TZ);
 if (RC == -1){
 printf("Bad call to gettimeofday\n");
 return(-1);
 }
 return(((double)TV.tv_sec)+micro*((double) TV.tv_usec));
}

double Wallies(long long n) 
{
   double sum=1.0,k;
   long long i;
  for (i=1;i<n;i++)
   {
   	k=2.0*(double)i;
        sum*=(k/(k+1.0))*(k/(k-1.0));
   }
   return 2.0*sum;
}

double EulerSerial(long long n) 
{
   double sum=0.0,sign,k;
   long long i;
  for (i=0;i<n;i++)
   {
   	if(i%2==0)
   	 sign=+1;
   	else
   	 sign=-1;
   	k=2*i+1;
   sum+=(sign)*(pow(0.5,k))/(k)+(sign)*(pow(0.3333333,k))/(k);
   }
   return 4.0*sum;
}
void* Eulerparall(void* rank) 
{
   long int thrno= (long int)rank;
   double partsum=0.0,sign,k;
   long long int i,part,thr_start,thr_end;
   
   part=n/Num_of_thread;
   thr_start=part*thrno;
   thr_end=thr_start+part;

  for(i=thr_start;i<thr_end;i++) 
  {
   	if(i%2==0)
   	  sign=+1;
   	else
   	 sign=-1;
    
	k=2*i+1;
        partsum+=(sign)*(pow(0.5,k))/(k)+(sign)*(pow(0.3333333,k))/(k);
   }
   sem_wait(&sem);
   sum+=partsum;
   sem_post(&sem);
   return NULL;
} 
void* Walliesparall(void* rank) {
   long int thrno=(long int)rank;
   double partsum=1.0,k;
   long long int i,part,thr_start,thr_end;
 
   part=n/Num_of_thread;
   thr_start=part*thrno;
   thr_end=thr_start+part;

  for (i=thr_start+1;i<=thr_end;i++)
   {
   	k=2.0*(double)i;
    partsum*=(k/(k+1.0))*(k/(k-1.0));

   }
   
   sem_wait(&sem);
   sum1=sum1*partsum;
   sem_post(&sem);
   return NULL;
}
