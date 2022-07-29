# 				SM3优化----SIMD方法

平台：Windows 

语言：C++ 

运行环境：VS2022，使用SIMD指令集(主要是支持256bit向量的那些)

运行指南：在VS2022 Debug模式下直接运行即可

Author:张浩旸

日期：2022/7/29

成功运行截图：

![image-20220729210726889](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20220729210726889.png)

因为消息填充部分挺快的，我觉得不用进行优化了，所以重点对CF函数及message extension消息拓展进行SIMD优化，成功部署了8组同时进行，运行效率如图，运行10000次，耗时8000微秒左右，吞吐量是305MB/s左右（只进行一次CF函数即512的消息分组的压缩）相比没有优化的SM3（3微秒一轮，而且一轮只完成一次）有约30倍的性能提升！