# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import random
import math
import binascii
import time
import socket
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

HOST = '127.0.0.1'
PORT = 1234
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    client.connect((HOST, PORT))
    print("Client 1 connected!")
except Exception:
    print('Connection failed!')
    sys.exit()
else:
    # 生成子私钥 d1
    d1 = randint(1, n - 1)

    # 计算P1 = d1^(-1) * G
    P1 = SM2.pointmul(invert(d1, p),[X,Y],a,p)
    x, y = hex(P1[0]), hex(P1[1])

    向客户2发送P1
    addr = (HOST, PORT)
    client.sendto(x.encode('utf-8'), addr)
    client.sendto(y.encode('utf-8'), addr)

    # 计算ZA
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

    # 向客户2发送Q1,e
    client.sendto(x.encode('utf-8'), addr)
    client.sendto(y.encode('utf-8'), addr)
    client.sendto(e.encode('utf-8'), addr)

    # 从客户2接收r,s2,s3
    r, addr = client.recvfrom(1024)
    r = int(r.decode(), 16)
    s2, addr = client.recvfrom(1024)
    s2 = int(s2.decode(), 16)
    s3, addr = client.recvfrom(1024)
    s3 = int(s3.decode(), 16)

    # 计算s
    s = ((d1 * k1) * s2 + d1 * s3 - r) % n
    if s != 0 or s != n - r:
        print("Signal:")
        print((hex(r), hex(s)))
    client.close()
# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
