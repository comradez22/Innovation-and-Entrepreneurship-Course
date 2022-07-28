# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import math
import random
a = 2
b = 2
p = 17
x = 5
y = 1
g = [x, y]
n = 19

m = 'Satoshi'
e = hash(m)
d = 7

def isprime(a, b):
    while a != 0:
        a, b = b % a, a
    return b



def gcd(a,b):
    r=a%b
    while(r!=0):
        a=b
        b=r
        r=a%b
    return b

def xgcd(a, m):
    if gcd(a, m) != 1:
        return None
    u1, u2, u3 = 1, 0, a
    v1, v2, v3 = 0, 1, m
    while v3 != 0:
        q = u3 // v3
        v1 , v2, v3, u1 , u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1 , v2, v3
    return u1 % m


def Add(P,Q):
    if (P == 0):
        return Q
    if (Q == 0):
        return P
    if P == Q:
        t1 = (3 * (P[0]**2) + a)
        t2 = xgcd(2 * P[1], p)
        k = (t1 * t2) % p
    else:
        t1 = (P[1] - Q[1])
        t2 = (P[0] - Q[0])
        k = (t1 * xgcd(t2,p)) % p

    X = (k * k - P[0] - Q[0]) % p
    Y = (k * (P[0] - X) - P[1]) % p
    Z = [X,Y]
    return Z


def Multiply(k, g):
    if k == 0:
        return 0
    if k == 1:
        return g
    r = g
    while (k >= 2):
        r = Add(r, g)
        k = k - 1
    return r

#签名
def ecdsasignal(m, n, G, d,k):
    e = hash(m)
    R = Multiply(k, G)
    r = R[0] % n
    s = (xgcd(k, n) * (e + d * r)) % n
    return r, s

#验证
def verify(m, n, G, r, s, P):
    e = hash(m)
    w = xgcd(s, n)
    v1 = (e * w) % n
    v2 = (r * w) % n
    w = Add(Multiply(v1, G), Multiply(v2, P))
    if (w == 0):
        print('false')
    else:
        if (w[0] % n == r):
            print('true')
        else:
            print('false')






# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
