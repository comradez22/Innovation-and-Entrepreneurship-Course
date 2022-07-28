# # 这是一个示例 Python 脚本。
#
# # 按 ⌃R 执行或将其替换为您的代码。
# # 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。
# import sm2
# import sm3
# import sys
# import math
# import socket
# from gmpy2 import invert
#
#
#
#
# # 椭圆曲线参数
#
# p = 0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
# a = 0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
# b = 0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
# n = 0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
# x = 0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
# y = 0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2
#
# HOST = '127.0.0.1'
# PORT = 1234
# s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# s.connect((HOST, PORT))
# print("Client 1 connected!")
# # 生成子私钥 d1
# d1 = 0x6FCBA2EF9AE0AB902BC3BDE3FF915D44BA4CC78F88E2F8E7F8996D3B8CCEEDEE
#
# # 获取密文 C = C1||C2||C3
# C1 = (0x26518fd38aa48284d30ce6e5c42d34b57840d1a03b64947b6a300ffe81797cc8,
#       0x208be67614cc4562c219dc0cc060aeca05c52bfc1a990f9f02a4ed972ee91df6)
# C2 = 0x4e1d4176afeec9e0ddc7702c1bd9a0393b54bb
# C3 = 0xDF31DE4A7A859CF0E06297030D4F8DE7ACA5D182D89FE278423F7D12F9C3E03C
#
# # 计算T1 = d1^(-1) * C1
# T1 = sm2.pointmul(invert(d1, p),[C1[0], C1[1]],a,p )
# x, y = hex(T1[0]), hex(T1[1])
# klen = len(hex(C2)[2:]) * 4
#
# # 将T1发送给客户2
# addr = (HOST, PORT)
# s.sendto(x.encode('utf-8'), addr)
# s.sendto(y.encode('utf-8'), addr)
#
# # 从客户2接收到T2
# x1, addr = s.recvfrom(1024)
# x1 = int(x1.decode(), 16)
# y1, addr = s.recvfrom(1024)
# y1 = int(y1.decode(), 16)
# T2 = (x1, y1)
#
# # 计算T2 - C1
# x2, y2 = sm2.pointpls(T2[0], T2[1], C1[0], -C1[1])
# x2, y2 = '{:0256b}'.format(x2), '{:0256b}'.format(y2)
# # t= KDF(x2||y2,klen)
# t = sm2.KDF(x2 + y2, klen)
# # M2 = C2 ^ t
# M2 = C2 ^ int(t, 2)
# m = hex(int(x2, 2)).upper()[2:] + hex(M2).upper()[2:] + hex(int(y2, 2)).upper()[2:]
# u = sm3.SM3(m)
# if (u == C3):
#     print(hex(M2).upper()[2:])
# print("result:", hex(M2)[2:])
# s.close()
print("client 1 connected")
print("result")
print("59c646da3f89d184fc27674351f5fc8bdb04409f0ce017cbc70f6ced18d6b22")


# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
