#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include<sys/time.h>
#include"func.h"
long long Num_of_thread,n,m,p;
sem_t sem;
double sum,sum1;
int main(int  argc,char* argv[])
{
  FILE *EulerData,*WalliesData;
  EulerData=fopen("Euler.dat","a+");
   WalliesData=fopen("Wallies.dat","a+");
   pthread_t* threads;
   long thrno; 
   int c=0;
   double start1,finish1,start2,finish2,accuracy,pie,spd;
   Num_of_thread=strtol(argv[1], NULL, 10);
   n=strtoll(argv[2], NULL, 10);
    pie=4.0*atan(1.0);
    p=pie*10000000000;

   threads=(pthread_t*)malloc(Num_of_thread*sizeof(pthread_t)); 
   sem_init(&sem,0,1);
   start1=calculateTime();
  
   for(thrno=0;thrno<Num_of_thread;thrno++)  
    {
    pthread_create(&threads[thrno],NULL,Eulerparall,(void*)thrno);  
    }

  for(thrno=0;thrno<Num_of_thread;thrno++) 
    {
     pthread_join(threads[thrno], NULL); 
    }
   sum=4.0*sum;
   finish1=calculateTime();
  
   accuracy=(1-fabs(pie-sum)/pie);
   c=0;
   m=sum*10000000000;
   p=pie*10000000000;
   while(m!=p)
   {c++;
    m=m/10;
    p=p/10;
   }
  
   
   printf("For n = %lld terms,\n",n);
   printf("Calculated value of pie by Parallel Euler Method  = %.15f\n",sum);
   printf(" Exact Number of bits %d\n", 10-c);
  
   printf("Time taken to execute Parallel Euler method is %lf seconds\n",finish1-start1);
   printf("accuracy of  Parallel Euler Method =%0.15lf\n",accuracy);
   start2=calculateTime();
   sum=EulerSerial(n);
   finish2=calculateTime();
   m=sum*10000000000;
   p=pie*10000000000;
   c=0;
   while(m!=p)
   {c++;
    m=m/10;
    p=p/10;
   }
   accuracy=(1-fabs(pie-sum)/pie);
   printf("Calculated value of pie by Serial Euler Method=%.15f\n",sum);
     printf(" Exact Number of bits %d\n", 10-c);
   printf("Time taken to execute serial Euler method is=%lf seconds \n",finish2-start2);
   printf("accuracy of  Parallel Euler Method =%.15lf\n",accuracy);
   printf("Value of pi = %.15f\n",pie);
     spd=(finish2-start2)/(finish1-start1);
    printf("speedup for Euler=%lf\n",spd);
  
    start1=calculateTime();
    for(thrno=0;thrno<Num_of_thread;thrno++)  
    {
    pthread_create(&threads[thrno],NULL,Walliesparall,(void*)thrno);  
    }

    for(thrno=0;thrno<Num_of_thread;thrno++) 
    {
    pthread_join(threads[thrno], NULL); 
    }
   sum1=2.0*sum1;
   finish1=calculateTime();
    m=sum1*10000000000;
     p=pie*10000000000;
    c=0;
   while(m!=p)
   {c++;
    m=m/10;
    p=p/10;
   }
   
   fprintf(EulerData,"%lld		%lf\n",Num_of_thread,finish1-start1);
   fclose(EulerData);
 
   accuracy=(1.0-fabs(pie-sum1)/pie);
   printf("Calculated value of pie by Parallel Wallies Method = %.15f\n",sum1);
     printf(" Exact Number of bits %d\n", 10-c);
   printf("Time taken to execute Parallel Wallies method is %lfseconds\n",finish1-start1);
    printf("accuracy of  Parallel  Wallies Method=%.15lf\n",accuracy);
   
    
   start2=calculateTime();
   sum=Wallies(n);
   finish2=calculateTime();
    m=sum*10000000000;
    p=pie*10000000000;
    c=0;
   while(m!=p)
   {c++;
    m=m/10;
    p=p/10;
   }
   accuracy=(1.0-fabs(pie-sum)/pie);
   
     fprintf(WalliesData,"%lld		%lf\n",Num_of_thread,finish2-start2);
     fclose(WalliesData);
  
   printf("Calculated value of pie by Serial Wallies Method = %.15f\n",sum);
     printf(" Exact Number bits %d\n", 10-c);
   printf("Time taken to execute serial Wallies method is =%lf seconds \n",finish2-start2);
   printf("accuracy of  Parallel  Wallies Method =%.15lf\n",accuracy);
   printf("Value of pi = %.15f\n",pie);
   
   spd=(finish2-start2)/(finish1-start1);
   printf("speedup for Wallies=%lf\n",spd);
   
   sem_destroy(&sem);
   free(threads);
   return 0;
}
