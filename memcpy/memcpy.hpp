#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstddef>
#include <immintrin.h>

inline void mm256Memcpy(char* dst, const char* src, const size_t len);
//inline void mm512Memcpy(char* dst, const char* src, const size_t len);
inline void longMemcpy(char* dst, const char* src, const size_t len);
inline void naiveMemcpy(char* dst, const char* src, const size_t len);

//just demo, NULL/overlap conercase not support

inline void Memcpy(char* dst, const char* src, const size_t len) {
#ifdef LONG_MEMCPY
    longMemcpy(dst, src, len);
    return;
#endif
#ifdef NAIVE_MEMCPY
    naiveMemcpy(dst, src, len);
    return;
#endif 
#ifdef AVX_MEMCPY
    mm256Memcpy(dst, src, len);
    return;
#endif
#ifdef STD_MEMCPY
    memcpy(dst,src,len);
    return;
#endif
}

inline void naiveMemcpy(char* dst, const char* src, const size_t len) {
    for(int i=0;i<len;i++) {
        *dst = *src;
        ++src;
        ++dst;
    }  
    return;
}

inline void longMemcpy(char* dst, const char* src, const size_t len) {
    size_t step = sizeof(long);
    size_t task_num = len / step;
    size_t remain_num = len - task_num * step;
    for(int i=0;i<task_num;i++) {
        *((long*)dst) = *((long*)src);
        src += step;
        dst += step;
    }  
    naiveMemcpy(dst, src, remain_num);
    return;
}

inline void mm256Memcpy(char* dst, const char* src, const size_t len) {
    size_t step = 256/8; 
    size_t task_num = len / step;
    size_t remain_num = len - task_num * step;
	for(int i=0;i<task_num;i++) {
        register const __m256i tmp = _mm256_loadu_si256((const __m256i *)src);
        _mm256_storeu_si256((__m256i *)dst, tmp);
        src += step;
        dst += step;
    }
    longMemcpy(dst, src, remain_num);
    return;
}