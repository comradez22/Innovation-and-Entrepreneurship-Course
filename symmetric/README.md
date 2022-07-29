# 					密码分析---构造对称HASH

平台：Windows 

语言：C++ 

运行环境：VS2022，无额外依赖 

运行指南：在VS2022 Debug模式下直接运行即可

Author:张浩旸

日期：2022/7/29

成功运行截图：![image-20220730001416192](C:\Users\ASUS\Desktop\网安创新实践\symmetric\image-20220730001416192.png)

思路和构造逆hash一致，因为meowhash的所有部件都具有可逆性，给定一个对称hash输出，给定一个输入，就一定能构造出合适的key值

64字节的消息输入，最终会得到四个消息快：`Hashinput1,Hashinput2,Hashinput3,LenghBlock4`

其中前两个是原本的输入，第三个是全零的填充，第四个是消息长度填充

他们被吸收入压缩函数的顺序是：`Hashinput3,LengthBlock4,Hashinput1,Hashinput2`

根据这个特性就可以构造出相应的Initkey，如图，最后输出的Hash值对称