# 这是一个示例 Python 脚本。

# 按 ⌃R 执行或将其替换为您的代码。
# 按 双击 ⇧ 在所有地方搜索类、文件、工具窗口、操作和设置。
import requests
import os

url="https://api.blockcypher.com/v1/btc/test3/txs/44b0e7aef67bd56f35e34ef62275883b19378d448b9050b91b35603f3a3040dc?limit=50&includeHex=true" \

response=requests.get(url)
response.encoding="utf-8"
html=response.text
f=open("tx.txt","wb")
f.write(html.encode("utf-8"))
f.close()


# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
