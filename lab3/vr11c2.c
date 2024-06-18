#include <stdio.h>
#include <time.h>
#include <math.h>

double get_current_time_ms() {
    clock_t ticks = clock();
    return (ticks * 1000.0) / CLOCKS_PER_SEC; 
}

int main() {
    double start_time = get_current_time_ms();
    
    for (int i = 0; i < 1000000; i++){
        double epsilon, last, next, sum;
        epsilon = 0.00001;
        last = 1 << 2;
        next = last;
        do {
            last = next;
            next = next/4;
            sum += next;
        } while (fabs(last - next) >= epsilon);
    }
    double computation_end_time = get_current_time_ms();
    printf("start_time = %f\ncomputation_start_time = %f\ncomputation_end_time = %f\nComputation Time = %f\n", start_time,  computation_end_time, computation_end_time - start_time);
    return 0;
}
