项目12:方案的PoC实施，或通过谷歌进行实现分析

完成人：张施珵

运行方法：直接运行main.py即可

模拟google服务器端和client用户端

google服务器首先进行预计算将数据库中所有参数求解Hash 
之后将前缀匹配的Hash值全部进行幂运算处理，连同一同发送至客户端
客户端拿到数据之后，用自己的私钥进行幂逆运算，将求解的值与数组中的泄露值对比以确定是否泄露。

实现结果

<img width="325" alt="截屏2022-07-28 12 23 40" src="https://user-images.githubusercontent.com/108727329/181419919-91305856-d524-4cf1-8d3a-6a00cbef342e.png">

<img width="1113" alt="截屏2022-07-28 12 19 50" src="https://user-images.githubusercontent.com/108727329/181419944-3ac78c07-8519-4ab6-ad4d-d1f79bbb7d9a.png">
