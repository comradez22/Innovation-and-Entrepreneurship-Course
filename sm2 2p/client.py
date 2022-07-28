import math
import socket
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
HOST = ''
PORT = 1234
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.bind((HOST, PORT))

print("Client 2 connected!")

# 生成子私钥 d2
d2 = randint(1,n-1)

# 从客户1接收P1=(x,y)
x,addr = client.recvfrom(1024)
x = int(x.decode(),16)
y,addr = client.recvfrom(1024)
y = int(y.decode(),16)


P1 = (x,y)
P = SM2.pointmul(P1[0],P1[1],invert(d2,p))
P = SM2.pointpls(P[0],P[1],X,-Y)


x,addr = client.recvfrom(1024)
x = int(x.decode(),16)
y,addr = client.recvfrom(1024)
y = int(y.decode(),16)
Q1 = (x,y)
e,addr = client.recvfrom(1024)
e = int(e.decode(),16)

k2 = randint(1,n-1)
k3 = randint(1,n-1)

Q2 = SM2.pointmul(X,Y,k2)


x1,y1 = SM2.pointmul(Q1[0],Q1[1],k3)
x1,y1 = SM2.pointpls(x1,y1,Q2[0],Q2[1])
r =(x1 + e)%n
s2 = (d2 * k3)%n
s3 = (d2 * (r+k2))%n

# 向客户1发送r,s2,s3
client.sendto(hex(r).encode(),addr)
client.sendto(hex(s2).encode(),addr)
client.sendto(hex(s3).encode(),addr)

print("bye")
