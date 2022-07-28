# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。

import math
import random
from gmssl import sm3, func



def pointpls(P, Q, a, p):  # 椭圆曲线上的加法
    if (math.isinf(P[0]) or math.isinf(P[1])) and (~math.isinf(Q[0]) and ~math.isinf(Q[1])):  # OP = P
        R = Q
    elif (~math.isinf(P[0]) and ~math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):  # PO = P
        R = P
    elif (math.isinf(P[0]) or math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):  # OO = O
        R = [float('inf'), float('inf')]
    else:
        if P != Q:
            l = modinv(Q[1] - P[1], Q[0] - P[0], p)
        else:
            l = modinv(3 * P[0] ** 2 + a, 2 * P[1], p)
        x = sm2mod(l ** 2 - P[0] - Q[0], p)
        y = sm2mod(l * (P[0] - x) - P[1], p)
        R = [x, y]
    return R

def pointmul(k, P, a, p):
    k_b = bin(k).replace('0b', '')
    i = len(k_b) - 1
    R = P
    if i > 0:
        k = k - 2 ** i
        while i > 0:
            R = pointpls(R, R, a, p)
            i -= 1
        if k > 0:
            R = pointpls(R, pointmul(k, P, a, p), a, p)
    return R





def sm2mod(a, b):
    if math.isinf(a):
        return float('inf')
    else:
        return a % b


def modinv(n, d, b):
    if d == 0:
        x = float('inf')
    elif n == 0:
        x = 0
    else:
        a = bin(b - 2).replace('0b', '')
        y = 1
        i = 0
        while i < len(a):
            y = (y ** 2) % b
            if a[i] == '1':
                y = (y * d) % b
            i += 1
        x = (y * n) % b
    return x


def key_gen(a, p, n, G):  # SM2密钥对的生成

    sk = random.randint(1, n - 2)
    pk = pointmul(sk, G, a, p)
    return sk, pk


def Legendre(n, p):
    return pow(n, (p - 1) // 2, p)


def Tonelli_Shanks(n, p):
    assert Legendre(n, p) == 1
    if p % 4 == 3:
        return pow(n, (p + 1) // 4, p)
    q = p - 1
    s = 0
    while q % 2 == 0:
        q = q // 2
        s += 1
    for z in range(2, p):
        if Legendre(z, p) == p - 1:
            c = pow(z, q, p)
            break
    r = pow(n, (q + 1) // 2, p)
    t = pow(n, q, p)
    m = s
    if t % p == 1:
        return r
    else:
        i = 0
        while t % p != 1:
            temp = pow(t, 2 ** (i + 1), p)
            i += 1
            if temp % p == 1:
                b = pow(c, 2 ** (m - i - 1), p)
                r = r * b % p
                c = b * b % p
                t = t * c % p
                m = i
                i = 0
        return r


def hashmul(sett):  # 定义集合的哈希 sett: bytes型集合
    digest_value = [float("inf"), float("inf")]
    for i in sett:
        x = int(sm3.sm3_hash(func.bytes_to_list(i)), 16)
        temp = sm2mod(x ** 2 + a * x + b, p)
        y = Tonelli_Shanks(temp, p)
        digest_value = pointpls(digest_value, [x, y], a, p)
    return digest_value


if __name__ == '__main__':
    p = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
    a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
    b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
    n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
    Gx = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7
    Gy = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
    G = [Gx, Gy]
    [sk, pk] = key_gen(a, p, n, G)
    hash1=b"1234"
    hash2=b"1234"
    hash=(hash1,hash2)
    print(hashmul(hash))




# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
