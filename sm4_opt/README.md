# 			SM4软件优化——查表+SIMD

平台：Windows 

语言：C++ 

运行环境：VS2022，SIMD指令集

运行指南：在VS2022 Debug模式下直接运行即可

Author:张浩旸

日期：2022/7/29

成功运行截图：

首先分析一下，SM4算法中有哪些部分是性能瓶颈

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps1.jpg) 

以上是SM4加密算法中各个关键部分的耗时，其中l 置换和s盒置换进行1000万次，耗时单位是纳秒，32轮加密进行10000次 轮密钥生成10000次，耗时单位是微秒

可以发现，两种变换上面，s盒变换比l置换花费更长的时间，轮密钥的生成时间远远低于32轮加密的时间。

32round Tfunction是指32轮加密中T函数所花费的总时间

32轮加密时间是只有32轮遍历的部分

根据这样的结果，我们可以确立SM4优化方案：

1.优化S盒非线性变换，因为S盒变换花费时间比l置换更高，所以优化s盒比优化l置换可以得到更好的性能提升

2.优化T函数，32轮变换总花费127微秒，而其中T函数占用了105微秒，占据变换时间的百分之82，优化T函数可以得到相当的性能提升。

 

根据以上的分析，我着手对T函数和S盒进行优化

\1. T函数优化：

根据https://www.cnblogs.com/kentle/p/15510582.html的指导，我们发现了SM4加密算法的合二为一查表优化，旨在缩短T函数时间

其原理如下：

T函数变换：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps2.jpg) 

其中X0-X3是低位到高位字节

可以将S盒和移位变换合并：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps3.jpg) 

预先计算好4个8bit输入的查找表：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps4.jpg) 

从而将T函数流程从先S盒，后循环移位变换等价转化为了：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps5.jpg) 

通过查表即可完成T函数

 

通过查表优化的SM4与普通SM4的对比：

。。。。。。。。。

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps6.jpg) 

可以看到有约1.7倍的性能提升（单位微秒）

 

\2. SIMD优化

接下来考虑并行的加速，SM4中轮密钥生成具有依赖性，所以不能很好的并行生成轮密钥：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps7.jpg) 

32轮变换加密部分同样具有依赖性，所以内部很难进行并行优化，考虑在外部进行并行

使用SIMD指令集进行并行：考虑到内部的变换中都是以32bit位为单位进行变换，所以可以考虑用SIMD对多组数据同时处理。

 

参考https://www.cnblogs.com/kentle/p/15562530.html

   http://html.rhhz.net/ZGKXYDXXB/20180205.htm#close

 

 

将数据以如下的形式组织起来：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps8.jpg) 

同步的对不同明文字的同一位置的字进行处理，从而达成并行的效果。

要做到这一点，使用AVX指令中的_mm256_unpacklo_epi8/16/32/64

可以做到，参考：

https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/intrinsics/intrinsics-for-avx2/intrinsics-for-pack-unpack-operations/mm256-unpacklo-epi8-16-32-64.html

 

https://qiita.com/fukushima1981/items/407dc2c635597ec26fd1#_mm256_unpacklohi_epi8163264-avx2

像这样：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps9.jpg) 

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps10.jpg) 

考虑8组数据，8x128bit数据的同时处理，使用以上的指令可以取出8组数据同一位置的32bit字：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps11.jpg) 

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps12.jpg) 

 

如图，LOLOLO 用于解包所有8个明文的第3个

HILOLO 用于解包所有8个明文的第2个

LOHIHI 用于解包所有8个明文的第1个

HIHIHI 用于解包所有8个明文的第0个

 

首先，从16*8个字节中装填数据：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps13.jpg) 

接着，取出8组数据的第0，1，2，3个double double word（也就是4字节）

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps14.jpg) 

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps15.jpg) 

接下来要进行shuffle即混洗操作，预先定义indicie向量

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps16.jpg) 

参考：

https://docs.microsoft.com/zh-tw/dotnet/api/system.runtime.intrinsics.x86.avx2.shiftrightlogical?view=netcore-3.1

一开始结果并不正确，参考以上文章后发现，装载数据时有顺序问题，电脑以小端法装载数据，所以要按照我们的想法处理SM4的话，需要将其倒转至大端表示。

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps17.jpg) 

接着是查表和移位操作

_mm256_i32gather_epi32是AVX2中的并行查表指令，它会将第2个操作数的8个32位作为索引，从第一个操作数作为基地址，并行查询。这一段直接参考了：

https://www.cnblogs.com/kentle/p/15562530.html

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps18.jpg) 

最后再调整端序，回传数据

性能表现：

![img](file:///C:\Users\ASUS\AppData\Local\Temp\ksohtml8884\wps19.jpg) 

10000次加密，平均1微秒进行一次，一次并行加密8组明文

吞吐量在240MB/s左右 相比朴素实现有了数十倍的提升