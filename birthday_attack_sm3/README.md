# 															SM3生日攻击

平台：Windows 

语言：C++ 

运行环境：VS2022，无额外依赖 

运行指南：在VS2022 Debug模式下直接运行即可

Author:张浩旸

日期：2022/7/29

成功运行截图：

![image-20220729205850033](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20220729205850033.png)

攻击核心部分：

~~~c++
bool birthday_attack(normal_node* root)
{
	unsigned int length;
	char* hash_input;
	for (int i = 0; i < 65535; i++)
	{
		length = rand() % 56;
		string temp = strRand(length);
		hash_input = (char*)temp.c_str();
		uint8_t* sm3_input = (uint8_t*)malloc(length * sizeof(uint8_t));
		for (int i = 0; i < length; i++)
		{
			sm3_input[i] = hash_input[i];
		}
		sm3(sm3_input, length * 8);
		free(sm3_input);
		uint32_t reduce_result = SM3_hash_result[0];
		bool result = search_tree(reduce_result, root);
		if (result == RESULT_FOUND)
		{
			return RESULT_FOUND;//找到碰撞
		}
		build_tree(root, reduce_result, temp);
	}
}
~~~

生日攻击函数，通过不断随机hash来得到碰撞，32bit的结果，在65535次碰撞后会有高概率得到碰撞

在本攻击中，因为要查询碰撞，而C++标准库中的hashmap跟不上hash的速度，所以我实现了一个二叉搜索树查询器，将32bit结果存储在二叉树中，可以在常数时间内查询出结果（二叉树深度最高32，所以是常数）：

~~~c++
bool search_tree(uint32_t hash_result,normal_node* root)//搜索树接口，输入哈希结果及根节点，返回该结果是否在树中
{
	int bit_status;
	normal_node* ptr = root;
	for (int i = 0; i < 32; i++)
	{
		bit_status = GetBitStatu(hash_result, i);
		if (bit_status == 1)
		{
			if (ptr->left_child == NULL)
				return RESULT_NOT_FOUND;
			else
				ptr = ptr->left_child;
		}
		else
		{
			if (ptr->right_child == NULL)
				return RESULT_NOT_FOUND;
			else
				ptr = ptr->right_child;
		}
	}
	return RESULT_FOUND;
}
~~~

