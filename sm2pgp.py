# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


import random
import sm2.py
import sm2ecmh.py
def encode(mes,key):
    cipher1 = encrypt(mes.encode('utf-8'),key)
    bintext = key.encode('utf-8')
    cipher2 = encrypt(bintext)
    print("会话密钥加密：", cipher1)
    print("公钥加密：", cipher2)
    return cipher1, cipher2


def decode(txt1, txt2):
    getkey = decrypt(txt2)
    print("私钥得到会话密钥：", getkey.decode('utf-8'))
    cpt= AES.new(get_key,mode = AES.MODE_OFB, b'0000000000000000')
    plain = cpt.decrypt(txt1)
    print("原消息值", plain.decode('utf-8'))



p = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
Gx = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7
Gy = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
G = [Gx, Gy]
[sk, pk] = key_gen(a, p, n, G)
sk_bytes = hex(sk)[2:]
pk_bytes = hex(pk[0])[2:] + hex(pk[1])[2:]

sm2_crypt = sm2.CryptSM2(public_key=pk_bytes, private_key=sk_bytes)
msg = "abcdefg123456"
print("msg", msg)
k = hex(random.randint(2 ** 127, 2 ** 128))[2:]
print("随机会话密钥：", k)
result1, result2 = encode(msg, k)
decode(result1, result2)






# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
