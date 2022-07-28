# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


from Crypto.Cipher import AES
from gmssl import sm2
import random
from gmssl import sm3, func
from gmssl.sm2 import CryptSM2

import SM2



def hashmul(s):
    digest_value = [float("inf"), float("inf")]
    for i in s:
        x = int(sm3.sm3_hash(func.bytes_to_list(i)), 16)
        temp = SM2.sm2mod(x ** 2 + a * x + b, p)
        y = SM2.Tonelli_Shanks(temp, p)
        value = SM2.pointpls(value, [x, y], a, p)
    return value



def encode(mes, k):
    mode = AES.MODE_OFB
    iv = b'0000000000000000'
    cryptor = AES.new(k.encode('utf-8'), mode, iv)
    length = 16
    count = len(mes)
    if count % length != 0:
        add = length - (count % length)
    else:
        add = 0
    mes = mes + ('\0' * add)
    text1 = cryptor.encrypt(mes.encode('utf-8'))
    text = k.encode('utf-8')
    text2 = sm2_crypt.encrypt(text)
    print("会话密钥加密：", text1)
    print("会话密钥加密：", text2)
    return text1, text2


def decode(mes1, mes2):
    mode = AES.MODE_OFB
    iv = b'0000000000000000'
    get_key = sm2_crypt.decrypt(mes2)
    print("会话密钥：", get_key.decode('utf-8'))
    cryptor = AES.new(get_key, mode, iv)
    text = cryptor.decrypt(mes1)
    print("原消息值", text.decode('utf-8'))


if __name__ == '__main__':
    p = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
    a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
    b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
    n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
    Gx = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7
    Gy = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
    G = [Gx, Gy]
    [sk, pk] = SM2.key_gen(a, p, n, G)
    sk_bytes = hex(sk)[2:]
    pk_bytes = hex(pk[0])[2:] + hex(pk[1])[2:]

    sm2_crypt =sm2.CryptSM2(public_key=pk_bytes, private_key=sk_bytes)
    msg = "ABCDEFG1234567890"
    print("消息：", msg)
    k = hex(random.randint(2 ** 127, 2 ** 128))[2:]
    print("会话密钥：", k)
    result1, result2 = encode(msg, k)
    decode(result1, result2)

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助


