# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。


from random import randint
import math

#mod
def modinv(a,m):
    x1,x2,x3=1,0,a
    y1,y2,y3=0,1,m
    while y3!=0:
        q=x3//y3
        t1,t2,t3=x1-q*y1,x2-q*y2,x3-q*y3
        x1,x2,x3=y1,y2,y3
        y1,y2,y3=t1,t2,t3
    return x1%m



def t(j):
    if j<16:
        return 0x79cc4519
    return 0x7a879d8a

#shift_left
def csl(x,k):
    x='{:032b}'.format(x)
    k=k%32
    x=x[k:]+x[:k]
    return int(x,2)

#bool function
def ff(x,y,z,j):
    if j<16:
        return x^y^z
    return (x&y)|(y&z)|(z&x)

def gg(x,y,z,j):
    if j<16:
        return x^y^z
    return (x&y)|(~x&z)

#displace function
def p0(x):
    return x^csl(x, 9)^csl(x, 17)
def p1(x):
    return x^csl(x, 15)^csl(x, 23)

#plaintext:m(length<2^64bit)
def fill(m):
    l=len(m)*4
    m=m+'8'
    k=112-(len(m)%128)
    m=m+'0'*k+'{:016x}'.format(l)
    return m

def grouping(m):
    n=len(m)//128
    b=[]
    for i in range(n):
        b.append(m[i*128:(i+1)*128])
    return b

def extend(bi):
    w=[]
    for i in range(16):
        w.append(int(bi[i*8:(i+1)*8],16))
    for j in range(16,68):
        w.append(p1(w[j-16]^w[j-9]^csl(w[j-3], 15))^csl(w[j-13], 7)^w[j-6])
    for j in range(68,132):
        w.append(w[j-68]^w[j-64])
    return w

def cf(vi,bi):
    w=extend(bi)
    a,b,c,d,e,f,g,h=int(vi[0:8],16),int(vi[8:16],16),int(vi[16:24],16),int(vi[24:32],16),int(vi[32:40],16),int(vi[40:48],16),int(vi[48:56],16),int(vi[56:64],16)
    for j in range(64):
        ss1=csl((csl(a,12)+e+csl(t(j),j))%pow(2,32),7)
        ss2=ss1^csl(a,12)
        tt1=(ff(a,b,c,j)+d+ss2+w[j+68])%pow(2,32)
        tt2=(gg(e,f,g,j)+h+ss1+w[j])%pow(2,32)
        d=c
        c=csl(b,9)
        b=a
        a=tt1
        h=g
        g=csl(f,19)
        f=e
        e=p0(tt2)
    abcdefgh=int('{:08x}'.format(a)+'{:08x}'.format(b)+'{:08x}'.format(c)+'{:08x}'.format(d)+'{:08x}'.format(e)+'{:08x}'.format(f)+'{:08x}'.format(g)+'{:08x}'.format(h),16)
    return '{:064x}'.format(abcdefgh^int(vi,16))

def iteration(b):
    n=len(b)
    v=iv
    for i in range(n):
        v=cf(v,b[i])
    return v


#m为16进制串
def sm3hash(m):
    m=fill(m)
    b=grouping(m)
    return iteration(b)


#群上的点相加
def addition(x1,y1,x2,y2,a,p):
    if x1==x2 and y1==p-y2:
        return False
    if x1!=x2:
        lamda=((y2-y1)*modinv(x2-x1, p))%p
    else:
        lamda=(((3*x1*x1+a)%p)*modinv(2*y1, p))%p
    x3=(lamda*lamda-x1-x2)%p
    y3=(lamda*(x1-x3)-y1)%p
    return x3,y3

def mutipoint(x,y,k,a,p):
    k=bin(k)[2:]
    qx,qy=x,y
    for i in range(1,len(k)):
        qx,qy=addition(qx, qy, qx, qy, a, p)
        if k[i]=='1':
            qx,qy=addition(qx, qy, x, y, a, p)
    return qx,qy

def kdf(z,klen):
    ct=1
    k=''
    for _ in range(math.ceil(klen/256)):
        k=k+sm3hash(hex(int(z+'{:032b}'.format(ct),2))[2:])
        ct=ct+1
    k='0'*((256-(len(bin(int(k,16))[2:])%256))%256)+bin(int(k,16))[2:]
    return k[:klen]

#官方推荐参数

iv='7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e'
p=0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
a=0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b=0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
gx=0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
gy=0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2
n=0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7

'''
dB=0x1649AB77A00637BD5E2EFE283FBF353534AA7F7CB89463F208DDBC2920BB0DA0
xB=0x435B39CCA8F3B508C1488AFC67BE491A0F7BA07E581A0E4849A5CF70628A7E0A
yB=0x75DDBA78F15FEECB4C7895E2C1CDF5FE01DEBB2CDBADF45399CCF77BBA076A42
'''
dB=randint(1,n-1)
xB,yB=mutipoint(gx,gy,dB,a,p)


def encrypt(m:str):
    plen=len(hex(p)[2:])
    m='0'*((4-(len(bin(int(m.encode().hex(),16))[2:])%4))%4)+bin(int(m.encode().hex(),16))[2:]
    klen=len(m)
    while True:
        k=randint(1, n)
        while k==dB:
            k=randint(1, n)
        x2,y2=mutipoint(xB, yB, k, a, p)
        x2,y2='{:0256b}'.format(x2),'{:0256b}'.format(y2)
        t=kdf(x2+y2, klen)
        if int(t,2)!=0:
            break
    x1,y1=mutipoint(gx, gy, k, a, p)
    x1,y1=(plen-len(hex(x1)[2:]))*'0'+hex(x1)[2:],(plen-len(hex(y1)[2:]))*'0'+hex(y1)[2:]
    c1='04'+x1+y1
    c2=((klen//4)-len(hex(int(m,2)^int(t,2))[2:]))*'0'+hex(int(m,2)^int(t,2))[2:]
    c3=sm3hash(hex(int(x2+m+y2,2))[2:])
    return c1,c2,c3

def decrypt(c1,c2,c3,a,b,p):
    c1=c1[2:]
    x1,y1=int(c1[:len(c1)//2],16),int(c1[len(c1)//2:],16)
    if pow(y1,2,p)!=(pow(x1,3,p)+a*x1+b)%p:
        return False
    x2,y2=mutipoint(x1, y1, dB, a, p)
    x2,y2='{:0256b}'.format(x2),'{:0256b}'.format(y2)
    klen=len(c2)*4
    t=kdf(x2+y2, klen)
    if int(t,2)==0:
        return False
    m='0'*(klen-len(bin(int(c2,16)^int(t,2))[2:]))+bin(int(c2,16)^int(t,2))[2:]
    u=sm3hash(hex(int(x2+m+y2,2))[2:])
    if u!=c3:
        return False
    return hex(int(m,2))[2:]


def verify():
    M="1234567890ABCDEF0987654321ABCDEF123456"
    c1,c2,c3=encrypt(M)
    c=(c1+c2+c3).upper()
    print('ciphertext:',c)
    print('plaintext:')
    m1=decrypt(c1, c2, c3, a, b, p)
    if m1:
        m1=str(bytes.fromhex(m1))
        m1='\n'.join(m1[2:-1].split('\\n'))
        print(m1)
        print(M==m1)
    else:
        print(False)


# SM2签名
def SM2_signature(message,n,G,d,ZA,k,a,p):
    M = ZA + message
    e = sm3hash(M)
    Z = mutipoint(G[0],G[1],k,a,p)
    r = (Z[0] + int(e,16)) % n
    e = hash(message)
    s = (modinv(1 + d, n) * (k - d * r)) % n
    return r,s

verify()

