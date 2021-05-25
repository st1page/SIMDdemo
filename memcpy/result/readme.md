### machine info
Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
DDR4 2933 MT/s 3 channel

### data
                2^28 Byte  2^29 Byte  2^30 Byte  cache-miss
charMemcpy      0.121793s  0.243573s  0.486880s  1,015,781,624
longMemcpy      0.096855s  0.096855s  0.194039s  1,016,268,276
mm256Memcpy     0.045024s  0.090282s  0.182033s  1,008,370,202
glibcMemcpy     0.057884s  0.111685s  0.226364s  527,624,034

几个cache-miss基本相同，不能确定是不是到内存带宽了。
glibc里面的memcpy应该是做的prefetch等访存优化，cache-miss明显少很多