#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
void Trap(double a, double b, int n, double* global_result_p);
double f(double x)
{
    return x*x;
}
int main()
{
    double global_result=00.0;
    double a,b;


    int n, thread_count=4;
    printf("Enter the value of a ,b and n \n");
    scanf("%lf %lf %d",&a,&b,&n);
    #pragma omp parallel num_threads(thread_count)
    Trap(a,b,n,&global_result);

    printf("With n = %d trapezoids our estimate \n",n);
    printf("of the integral from %.1f to %.1f =%.1f\n",a,b,global_result);
    return 0;
}
void Trap(double a, double b, int n, double* global_result_p)
{

    double h,x,my_result=0;
    double local_a, local_b;
    int i, local_n;
    int my_rank=omp_get_thread_num();
    int total_thread=omp_get_num_threads();
    h=(b-a)/n;
    local_n=n/total_thread;
    local_a=a+my_rank*local_n*h;
    local_b=local_a+local_n*h;

    my_result=(f(local_a)+f(local_b))/2.0;
    for(i=1;i<local_n;i++)
    {
        x=local_a+i*h;
        my_result+=f(x);

    }
    my_result=my_result*h;
    printf("rank = %d h= %.1f local_a=%.1f local_b=%.1f local_n=%d my_result=%.1f \n",my_rank,h,local_a,local_b,local_n,my_result);
    #pragma omp critical
    *global_result_p+=my_result;
}
