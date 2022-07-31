项目2:实施简化SM3的Rho方法

完成人：张施珵

运行方法：直接运行main.py即可

直接调用sm3hash然后随机选取一个起始值，选取fx=2x+1，和floyd判环法一样的思路，看前nbit相同即可

8bit
<img width="1022" alt="截屏2022-07-27 16 10 19" src="https://user-images.githubusercontent.com/108727329/181196634-568f7e20-1a9e-4874-9dbb-3d15f578fb72.png">

12bit
<img width="1006" alt="截屏2022-07-27 16 10 31" src="https://user-images.githubusercontent.com/108727329/181196661-8d75bcb7-e65e-418e-94dd-31e8a5631630.png">

16bit
<img width="942" alt="截屏2022-07-27 16 10 40" src="https://user-images.githubusercontent.com/108727329/181196669-336694e7-ed75-4f90-ac10-1b4cbd19ad43.png">
