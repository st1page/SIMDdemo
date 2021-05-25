# SIMDdemo
## memcpy
在memcpy/memcpy.hpp 实现了逐字节复制、字长(long)、avx256、avx512的比较。
在memcpy/test.cpp 中做了正确性检测和简单的benchmark。未完成地址不对齐的测试，按照avx指令集文档mm_store和mm_load指令不需要对齐也会保证正确性，不过可能会慢。


测试结果见[memcpy/result/readme.md](memcpy/result/readme.md)