# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import math
import random

def isprime(a, b):
    while a != 0:
        a, b = b % a, a
    return b

def gcd(a, m):
    if isprime(a, m) != 1 and isprime(a, m) != -1:
        return None
    u1, u2, u3 = 1, 0, a
    v1, v2, v3 = 0, 1, m
    while v3 != 0:
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    if u1 > 0:
        return u1 % m
    else:
        return (u1 + m) % m

def Add(m, n):
    if (m == 0):
        return n
    if (n == 0):
        return m
    he = []
    if (m != n):
        if (isprime(m[0] - n[0], p) != 1 and isprime(m[0] - n[0], p) != -1):
            return 0
        else:
            k = ((m[1] - n[1]) * gcd(m[0] - n[0], p)) % p
    else:
        k = ((3 * (m[0] ** 2) + a) * gcd(2 * m[1], p)) % p
    x = (k ** 2 - m[0] - n[0]) % p
    y = (k * (m[0] - x) - m[1]) % p
    he.append(x)
    he.append(y)
    return he


def Multiply(n, l):
    if n == 0:
        return 0
    if n == 1:
        return l
    t = l
    while (n >= 2):
        t = Add(t, l)
        n = n - 1
    return t

#签名
def ecdsasignal(m, n, G, d,k):
    e = hash(m)
    R = Multiply(k, G)
    r = R[0] % n
    s = (gcd(k, n) * (e + d * r)) % n
    return r, s

#验证
def verify(m, n, G, r, s, P):
    e = hash(m)
    w = gcd(s, n)
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



a = 2
b = 18
p = 17
m = 'hello'
G = [5,1]
n = 19
k = 2
d = 5
P = Multiply(d, G)
r,s=ecdsasignal(m,n,G,d,k)
print("签名为:",r,s)
print("验证结果：")
verify(m,n,G,r,s,P)






# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助


