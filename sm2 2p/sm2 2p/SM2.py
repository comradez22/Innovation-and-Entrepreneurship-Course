# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。

import math
import random
from gmssl import sm3, func



def pointpls(P, Q, a, p):
    if (math.isinf(P[0]) or math.isinf(P[1])) and (~math.isinf(Q[0]) and ~math.isinf(Q[1])):
        R = Q
    elif (~math.isinf(P[0]) and ~math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):
        R = P
    elif (math.isinf(P[0]) or math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):
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


def key_gen(a, p, n, G):

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