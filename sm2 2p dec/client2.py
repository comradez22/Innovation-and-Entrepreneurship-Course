# import math
# import socket
# from gmpy2 import invert
#
#
# # 椭圆曲线参数
# import sm2
#
# p = 0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
# a = 0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
# b = 0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
# n = 0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
# x = 0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
# y = 0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2
#
#
# HOST = ''
# PORT = 1234
# s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# s.bind((HOST, PORT))
#
# print("Client 2 connected!")
# # 生成子私钥 d2
# d2 = 0x5E35D7D3F3C54DBAC72E61819E730B019A84208CA3A35E4C2E353DFCCB2A3B53
#
# # 从客户1接收到T1
# x, addr = s.recvfrom(1024)
# x = int(x.decode(), 16)
# y, addr = s.recvfrom(1024)
# y = int(y.decode(), 16)
# T1 = (x, y)
#
# # 计算T2 = d2^(-1) * T1
# T2 = sm2.pointmul(invert(d2, p),[x,y],a,p)
# x, y = hex(T2[0]), hex(T2[1])
#
# s.sendto(x.encode('utf-8'), addr)
# s.sendto(y.encode('utf-8'), addr)
print("client 2 connected")
print("bye!")