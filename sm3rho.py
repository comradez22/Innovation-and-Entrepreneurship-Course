# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import random
import sm3
def rho():
    list_r_value = []
    for i in range(pow(2,32)):
        list_r = random.randint(0, pow(2,64))
        m = TC(str(list_r))
        M = Group(m)
        Vn=SM3(M)
        aa=""
        for x in Vn:
            aa += hex(x)[2:]
        bb=aa[:1]
        if(bb in list_r_value):
            print("success")
            break
        else:
            list_r_value.append(bb)


rho()



# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
