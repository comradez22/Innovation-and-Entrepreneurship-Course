# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。

# 伪造签名
import random
import ecdsa



def attack(e, r, s):
    global pk, n, g
    t = ecdsa.xgcd(s, n)  # t = s^(-1) mod n
    Z = ecdsa.Add(ecdsa.Multiply((e * t) % n, g), ecdsa.Multiply((r * t) % n, pk))
    if (Z != 0):
        if (Z[0] % n == r):
            return True
        else:
            return False
    return False


def satoshi(r, s):
    global n, g, pk
    a = random.randint(1, n - 1)
    b = random.randint(1, n - 1)
    Z = ecdsa.Add(ecdsa.Multiply(a, g), ecdsa.Multiply(b, pk))
    r1 = Z[0] % n
    e1 = (r1 * a * ecdsa.gcd(b, n)) % n
    s1 = (r1 * ecdsa.xgcd(b, n)) % n
    print('fakemsg:', e1)
    print('fakesig:', r1, s1)
    if (attack(e1, r1, s1)):
        print('sucess!')
    else:
        print('failure!')


# 椭圆曲线参数
a = 2
b = 2
p = 17
x = 5
y = 1
g = [x, y]
n = 19

m = 'Satoshi'
e = hash(m)
d = 7
pk = ecdsa.Multiply(d, g)
k = random.randint(1,n-1)
r, s = ecdsa.ecdsasignal(m,n,g,d,k)

print("sig", r, s)
if (ecdsa.verify(m,n,g,r,s,pk)):
    print('success')
else:
    print('failure')

satoshi(r, s)

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
