# 					RFC6962 Merkle树

平台：Windows 

语言：C++ 

运行环境：VS2022，无额外依赖 

运行指南：在VS2022 Debug模式下直接运行即可

Author:张浩旸

日期：2022/7/29

成功运行截图：

Merkle一致性证明：

![image-20220729215012348](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20220729215012348.png)

Merkle审计路径：

![image-20220729215042991](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20220729215042991.png)

我参考了这篇文章：https://blog.csdn.net/Ciellee/article/details/108073025

我的代码中，句子动态分割，树结构的打印显示两个功能来自此文章作者

树节点结构体：

~~~c++
typedef struct Merkle_Tree_Node
{
	struct Merkle_Tree_Node* left_child;//左孩子
	struct Merkle_Tree_Node* right_child;//右孩子
	struct Merkle_Tree_Node* father_node;//父节点
	unsigned int level;//本节点深度
	unsigned int hash_value;//hash值
	char* str;//如果是叶子节点，则没有str赋值为相应字符串
}Merkle_Tree;
~~~

在C++上安装openssl比较麻烦，所以使用暂时的hash函数代替sha256

~~~c++
unsigned int sha256_string(char* str1, char* str2)//暂时代替sha256哈希函数
{
	unsigned int magic_number = 12345, hash = 0;
	if (str1 != NULL)
	{
		while (*str1 != '\0' && *str1 != 0)
		{
			hash = hash * magic_number + *str1;
			str1++;
		}
	}
	if (str2 != NULL)
	{
		while (*str2 != '\0' && *str2 != 0)
		{
			hash = hash * magic_number + *str2;
			str2++;
		}
	}
	return hash & 0xFFFFFFFF;
}
~~~

树的构建用递归方法，从左下角开始构建，使用递归构建，构建的思路是：

首先每次都新建一个叶子节点，保存当前递归中的词语，叶子会保存string而中间节点保存hash

首先判断root是否是空，如果空了，说明当前无树，新建树

如果不是空，当前有树，然后找到最后一个叶子节点，再从这个叶子节点向上判断哪一个头节点需要插入

找到需要插入的节点后，判断该节点的子节点的子节点是否是叶子，如果是就插入右孩子，不是的话说明是中间节点，要新建子节点，然后更新同样深度的左树

如果需要插入的节点没找到，说明当前已经是满二叉树了，新增头节点，建立同样深度的子树，返回叶子节点的父节点，给叶子结点的父节点赋值

添加完节点后，自下而上更新hash值即可完成构建





