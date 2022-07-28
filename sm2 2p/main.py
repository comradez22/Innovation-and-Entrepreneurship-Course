# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import random
import math
import binascii
import sys
from random import randint
from gmpy2 import invert
from random import randint


import SM2
import SM3


p = 0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
a = 0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b = 0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
n = 0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
X = 0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
Y = 0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2


# c1子私钥 d1
d1 = randint(1, n - 1)
# c2子私钥 d2
d2 = randint(1,n-1)
# P1
P1 = SM2.pointmul(invert(d1, p),[X,Y],a,p)
x, y = hex(P1[0]), hex(P1[1])
print("c1得到x,y")
print("x=",x)
print("y=",y)

#c1向c2发送P1
##
print("c1向c2发送P1")


#c2从c1接收P1=(x,y)
##
print("c2从c1接收P1=(x,y)")

# c2共享公钥P
P1 = (x, y)
P = SM2.pointmul(invert(d2, p),[int(P1[0],16), int(P1[1],16)],a,p)
P = SM2.pointpls([P[0],P[1]], [X, -Y],a,p)
print("c2计算共享公钥p")

# c1计算ZA
m = "hello"
m = hex(int(binascii.b2a_hex(m.encode()).decode(), 16)).upper()[2:]
h = "world"
h = hex(int(binascii.b2a_hex(h.encode()).decode(), 16)).upper()[2:]
s = '{:04X}'.format(len(h) * 4)
ma = s + h + '{:064X}'.format(a) + '{:064X}'.format(b) + '{:064X}'.format(X) + '{:064X}'.format(Y)
ZA = SM3.sm3(ma)
e = SM3.sm3(ZA + m)
# 生成随机数k1
k1 = randint(1, n - 1)
# 计算Q1 = k1 * G
Q1 = SM2.pointmul(k1,[X,Y],a,p)
x, y = hex(Q1[0]), hex(Q1[1])

# c1向c2发送Q1,e
#
print("向c2发送Q1,e")

# c2从c1接收Q1=(x,y)与e
print("c2从c1接收Q1=(x,y)与e")


# c2生成随机数k2,k3
k2 = randint(1, n - 1)
k3 = randint(1, n - 1)

# 计算Q2 = k2 * G
Q2 = SM2.pointmul( k2,[X, Y],a,p)

# 计算(x1,y1) = k3 * Q1 + Q2
x1, y1 = SM2.pointmul(k3,[Q1[0], Q1[1]],a,p)
x1, y1 = SM2.pointpls([x1, y1], [Q2[0], Q2[1]],a,p)
r = (x1 + int(e,16)) % n
s2 = (d2 * k3) % n
s3 = (d2 * (r + k2)) % n

# c2向c1发送r,s2,s3
print("c2向c1发送r,s2,s3")
# c1从c2接收r,s2,s3
print("c1从c2接收r,s2,s3")


# c1计算s
s = ((d1 * k1) * s2 + d1 * s3 - r) % n
if s != 0 or s != n - r:
    print("Signal:")
    print((hex(r), hex(s)))

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
