import random
import time

IV = [0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600, 0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E]
T = [0x79cc4519, 0x7a879d8a]


def ROL(X, i):
    i = i % 32
    return ((X << i) & 0xFFFFFFFF) | ((X & 0xFFFFFFFF) >> (32 - i))


def FF(X, Y, Z, j):
    if j >= 0 and j <= 15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (X & Z) | (Y & Z))


def GG(X, Y, Z, j):
    if j >= 0 and j <= 15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (~X & Z))


def P0(X):
    return X ^ ROL(X, 9) ^ ROL(X, 17)


def P1(X):
    return X ^ ROL(X, 15) ^ ROL(X, 23)


def T_(j):
    if j >= 0 and j <= 15:
        return T[0]
    else:
        return T[1]


def Fill(message):
    m = bin(int(message, 16))[2:]
    if len(m) != len(message) * 4:
        m = '0' * (len(message) * 4 - len(m)) + m
    l = len(m)
    l_bin = '0' * (64 - len(bin(l)[2:])) + bin(l)[2:]
    m = m + '1'
    m = m + '0' * (448 - len(m) % 512) + l_bin
    m = hex(int(m, 2))[2:]
    return m


def coprime(a, b):
    while a != 0:
        a, b = b % a, a
    if b != 1 and b != -1:
        return 1
    return 0


def gcd(a, m):
    if coprime(a, m):
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


def Group(m):
    n = len(m) / 128
    M = []
    for i in range(int(n)):
        M.append(m[0 + 128 * i:128 + 128 * i])
    return M


def Expand(M, n):
    W = []
    W_ = []
    for j in range(16):
        W.append(int(M[n][0 + 8 * j:8 + 8 * j], 16))
    for j in range(16, 68):
        W.append(P1(W[j - 16] ^ W[j - 9] ^ ROL(W[j - 3], 15)) ^ ROL(W[j - 13], 7) ^ W[j - 6])
    for j in range(64):
        W_.append(W[j] ^ W[j + 4])
    Wstr = ''
    W_str = ''
    for x in W:
        Wstr += (hex(x)[2:] + ' ')
    for x in W_:
        W_str += (hex(x)[2:] + ' ')
    return W, W_


def CF(V, M, i):
    A, B, C, D, E, F, G, H = V[i]
    W, W_ = Expand(M, i)
    for j in range(64):
        SS1 = ROL((ROL(A, 12) + E + ROL(T_(j), j % 32)) % (2 ** 32), 7)
        SS2 = SS1 ^ ROL(A, 12)
        TT1 = (FF(A, B, C, j) + D + SS2 + W_[j]) % (2 ** 32)
        TT2 = (GG(E, F, G, j) + H + SS1 + W[j]) % (2 ** 32)
        D = C
        C = ROL(B, 9)
        B = A
        A = TT1
        H = G
        G = ROL(F, 19)
        F = E
        E = P0(TT2)
    a, b, c, d, e, f, g, h = V[i]
    V_ = [a ^ A, b ^ B, c ^ C, d ^ D, e ^ E, f ^ F, g ^ G, h ^ H]
    return V_


def Iterate(M):
    n = len(M)
    V = []
    V.append(IV)
    for i in range(n):
        V.append(CF(V, M, i))
    return V[n]


def sm3(message):
    m = Fill(message)  # 填充后消息
    M = Group(m)  # 数据分组
    Vn = Iterate(M)  # 迭代
    result = ''
    for x in Vn:
        result += hex(x)[2:]
    return result


