# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import random
import sm3

def Rho_Attack(n):
    a=random.randint(0,0xffff)
    res=[]
    for i in range(0xffff):
        res.append(sm3(str(a))[:int(n/4)])
        a=(2*a+1)
        if(sm3(str(a))[:int(n/4)]in res):
            print('Succeed')
            return;
    print('Failed')


if __name__ == '__main__':
    time_start = time.time()
    n=8
    Rho_Attack(n)
    time_end = time.time()
    time_c = time_end - time_start
    print("n=",n)
    print('time cost', time_c, 's')
    
    
    
    

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
