sm2的缺陷，一些攻击

1.leaking k
sk=(s+r)^(-1)*(k-s) mod n

<img width="527" alt="截屏2022-07-29 21 59 57" src="https://user-images.githubusercontent.com/108727329/181776658-01c400f6-1b2f-4d12-b263-897885fc4657.png">

2. reusing k
sk=(s2-s1)/(s1-s2+r1-r2)

<img width="495" alt="截屏2022-07-29 22 02 16" src="https://user-images.githubusercontent.com/108727329/181776880-385697d7-98d9-4ec4-a79a-6097e3e10c11.png">

3. reusing k by different users
sk2=(k-s2)/s2+r2
sk1=(k-s1)/(s1+r1)

<img width="554" alt="截屏2022-07-29 22 03 16" src="https://user-images.githubusercontent.com/108727329/181777032-c3170a21-3b6e-44ae-aab7-cbf931f6db62.png">


4.same dk with ecdsa
 d=(s1s2-e)/(r1-s1s2-s1r2) mod n
 
 <img width="404" alt="截屏2022-07-29 22 04 03" src="https://user-images.githubusercontent.com/108727329/181777192-54da3c4b-9a1f-47de-8d3e-c61ab78a48ea.png">


实现结果

<img width="435" alt="截屏2022-07-29 21 54 57" src="https://user-images.githubusercontent.com/108727329/181777230-a8839e3b-3b4a-4cce-a569-03c5b7bd4599.png">
