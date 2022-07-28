# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。

import random
import socket
import sm3


def google(k, v, b):
    l = []
    for i in range(10000, 10000 + pow(2, 8)):
        text = sm3.sm3(str(i) + str(i))
        l.append(text)
    vi = []
    for V in l:
        if V[:2] == k:
            vi.append((pow(int(V, 16), b)) % n)
    hab = (pow(v, b)) % n
    return hab, vi


def client(h, S, a):
    global user
    hb = (pow(h, sm3.gcd(a, n - 1))) % n
    a = 0
    for V in S:
        b = V
        if b == hb:
            a = 1
    if a == 0:
        print('测试账户', user, '安全')
    else:
        print('测试账户', user, '泄露')



def generate(u, p, a):
    h = sm3.sm3(str(user) + str(password))
    k = h[:2]
    v = (pow(int(h, 16), a)) % n
    return k, v

n = 31
d1 = 7
d2 = 11
user = 1234567890
password = 12345

k, v = generate(user, password, d1)
hab, vi = google(k, v, d2)
client(hab, vi, d1)

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
