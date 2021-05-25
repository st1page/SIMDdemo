#include "memcpy.hpp"
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <stdlib.h>
#include <sys/time.h>

const int k_align = 64; 

double get_sec(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


void test_alignAddr(int size){

	char *src = (char*)aligned_alloc(k_align, size+1);
    for (int i = 0; i < size; i++) src[i]=i*7+3;
	char *dst = (char*)aligned_alloc(k_align, size+1);
    char *stddst = (char*)aligned_alloc(k_align, size+1);

    memcpy(stddst, src, size);
    Memcpy(dst, src, size);
    if(memcmp(stddst, dst, size)!=0) {
        printf("[Error] align Addr test: size=%d\n", size);
        exit(-1);
    }
    free(src);
    free(dst);
    free(stddst);

}

const int bench_cnt = 16;
void bench(int size){
    char *src = (char*)aligned_alloc(k_align, size);
    for (int i = 0; i < size; i++) src[i]=i*7+3;
	char *dst = (char*)aligned_alloc(k_align, size);

    printf("running bench, size=%d, %d times\n", size ,bench_cnt);
    double tot_time = 0;
    for(int i = 0; i < bench_cnt; i++) {
        double t0 = get_sec();
        Memcpy(dst, src, size);
        tot_time += get_sec() - t0;
    }
    printf("  Time cost: %lf\n", tot_time/bench_cnt);
    
    free(src);
    free(dst);
}

int main(){
    for(int test_offset = 0; test_offset < k_align*4; test_offset++) {
        test_alignAddr(4096+test_offset); 
    }
    puts("[PASS] align Addr test pass");

    for(int i=20;i<=30;i++) {
        bench(1<<i);
    }

    return 0;
}



//TODO test correct and benchmark for unalign
/* 

const uint32_t k_max_offset = 32;
const uint32_t k_size = 512*10;
static char src[k_size + k_max_offset];
static char stddst[k_size + k_max_offset];
static char dst[k_size + k_max_offset];
int main(){
    for(int i = 0; i < k_size; i++) src[i] = (char)i;
    for(int soffset = 0; soffset < k_max_offset; soffset++)
        for(int doffset = 0; doffset < k_max_offset; doffset++) {
            memcpy(stddst + doffset, src+soffset, k_size);
            Memcpy(dst + doffset, src+soffset, k_size);
            if(memcmp(stddst + doffset, dst + doffset, k_size)!=0) {
                printf("Error! soffset=%d, doffset=%d\n", soffset, doffset);
                return -1;
            }
        }
    return 0;
}
*/