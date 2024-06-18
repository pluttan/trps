#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double gettmms(){
    clock_t ticks = clock();
    return (ticks * 1000.0) / CLOCKS_PER_SEC; 
}
int main()
{
    double t0 = gettmms();
    for (int i = 0; i < 1000000; i++){
    double s,a,m,eps,x;
    double *ms, *mss;
    int N = 1000, i,o; 
    ms = (double*)malloc(N * sizeof(int));
    mss = (double*)malloc(N * sizeof(int));
    eps = 0.00001;
    ms[1] = 1.0/4;
    o = 1;
    s = 1.0/4;
    mss[1] = s;
    double t1 = gettmms();
    do {
        o++;
        ms[o] = ms[o-1] * (-1/(o<<2));
        s = s+ms[o];
        mss[o] = ms[o] + mss[o-1];
    } while (abs(ms[o-1]-ms[o])>=eps);
    free(ms);
    free(mss);
    }
    double t2 = gettmms();
    printf("t0 = %f\nt2 = %f\nTime = %f\n",t0,t2,t2-t0);
    return 0;
}
