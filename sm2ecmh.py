# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。



import sm2.py
def hashmul(hash): 
    for i in hash:
        x = int(sm3.sm3_hash((i)), 16)
        temp = sm2mod(x ** 2 + a * x + b, p)
        y = remain(temp, p)
        value = pointpls(value, x, y, a, p)
    return value


p = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF    
a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
Gx = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7 
Gy = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
G = [Gx, Gy]
[sk, pk] = key_gen(a, p, n, G)
hash=input("hashset")
print(hashmul(hash))




# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
