#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef unsigned int uint;
typedef struct Merkle_Tree_Node
{
	struct Merkle_Tree_Node* left_child;//左孩子
	struct Merkle_Tree_Node* right_child;//右孩子
	struct Merkle_Tree_Node* father_node;//父节点
	unsigned int level;//本节点深度
	unsigned int hash_value;//hash值
	char* str;//如果是叶子节点，则没有str赋值为相应字符串
}Merkle_Tree;
Merkle_Tree* correct_leaf;
int neibor_counter = 0;
#define Init_new_node(root, tree_level) {	\
	root = (Merkle_Tree *)malloc(sizeof(Merkle_Tree)); \
	root->left_child = NULL; \
	root->right_child = NULL; \
	root->father_node = NULL; \
	root->level = (unsigned int)tree_level; \
	root->hash_value = 0;	\
	root->str = NULL; \
	}
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
unsigned int sha256_int(unsigned int num1, unsigned int num2)//暂时代替sha256哈希函数
{
	unsigned int magic_num = 12345, hash = 0;
	hash = num1 + num2;
	hash = hash * magic_num;
	return hash ^ 0xFFFFFFFF;
}

Merkle_Tree* get_leaf_node(Merkle_Tree* root)//取得最后一个叶子节点
{
	Merkle_Tree* ptr = root;
	Merkle_Tree* temp;
	if (ptr->left_child == NULL && ptr->right_child == NULL)//左右孩子都空，是叶子节点，返回之
	{
		return ptr;
	}
	else if (ptr->right_child == NULL && ptr->left_child != NULL)//右空左不空，遍历左边直到叶子节点
	{
		return get_leaf_node(ptr->left_child);
	}
	else if (ptr->right_child != NULL)//右不空，便利右边直到叶子节点
	{
		return get_leaf_node(ptr->right_child);
	}
}
Merkle_Tree* get_correct_insert_node(Merkle_Tree* leaf_node)//输入叶子节点，输出一个待插入的头节点
{
	Merkle_Tree* ptr = leaf_node->father_node;//叶子节点不需要插入，先找到其父节点
	while (ptr->left_child != NULL && ptr->right_child != NULL && ptr->father_node != NULL)
	{
		ptr = ptr->father_node;//如果父节点左右孩子都满了，说明不需要插入节点，向上查询直到遇到需要的为止
	}
	if (ptr->father_node == NULL && ptr->left_child != NULL && ptr->right_child != NULL)
	{
		return NULL;//没有父节点但是左右孩子都有了，说明目前是满二叉树，不需要插入，返回空值
	}
	else
	{
		return ptr;//否则，当前节点就需要插入
	}
}

Merkle_Tree* Build_Merkle_Tree(Merkle_Tree* root, char** input_list, int length)//输入根节点，输入列表（字符数组列表），列表长度
{
	Merkle_Tree* new_node, * temp, * ptr;
	int count;
	if (length == 0)
	{
		cout << "Build Complete!" << endl;
		return root;
	}
	else
	{
		Init_new_node(new_node, 0);//新建叶子节点
		new_node->str = (char*)malloc(strlen(*input_list) + 1);//叶子节点字符串分配空间，+1是因为结束符
		
		for (int i = 0; i < strlen(*input_list); i++)
		{
			new_node->str[i] = (*input_list)[i];//字符串赋值
		}
		new_node->str[strlen(*input_list)] = '\0';//赋值结束符
		if (root == NULL)//root空说明当前没有树，需要新建头节点
		{
			Init_new_node(root, 1);
			root->left_child = new_node;
			new_node->father_node = root;
			root->hash_value = sha256_string(root->left_child->str, root->right_child == NULL ? NULL : root->right_child->str);
			root = Build_Merkle_Tree(root, input_list + 1, length - 1);//递归插入新节点，input_list+1即下一个字符串，length-1即待插入个数少一个
		}
		else//root不为空，当前有树
		{
			//ptr现在是叶子节点
			ptr = get_correct_insert_node(get_leaf_node(root));//ptr是待插入节点的节点

			if (ptr != NULL)//ptr不为空，表示已经找到需要插入节点的节点
			{
				if (ptr->left_child->left_child == NULL && ptr->right_child == NULL)//ptr的子节点的子节点是空，说明ptr的子节点是叶子节点，直接插入右孩子即可
				{
					ptr->right_child = new_node;
					new_node->father_node = ptr;
					ptr->hash_value = sha256_string(ptr->left_child->str, ptr->right_child == NULL ? NULL : ptr->right_child->str);
				}
				else//说明不是叶子节点的父节点，是树中的中间节点,则应该给中间节点新建子节点
				{
					count = ptr->level - 1;//记下当前深度
					Init_new_node(temp, count);
					ptr->right_child = temp;
					temp->father_node = ptr;
					ptr = ptr->right_child;
					count = ptr->level - 1;//更新为当前深度-1
					while (count > 0)//根据当前深度新建左树
					{
						Init_new_node(temp, count);
						ptr->left_child = temp;
						temp->father_node = ptr;
						ptr = ptr->left_child;
						count = count - 1;
					}
					ptr->left_child = new_node;//现在count=1，即是叶子节点的父节点这一层，将叶子节点插入
					new_node->father_node = ptr;
					ptr->hash_value = sha256_string(ptr->left_child->str, ptr->right_child == NULL ? NULL : ptr->right_child->str);
				}
			}
			else//当前返回空值，说明该子树已经满了，要增加头节点，深度也要增加
			{

				temp = root;
				Init_new_node(root, temp->level + 1);//创建新头节点
				root->left_child = temp;
				temp->father_node = root;

				Init_new_node(temp, root->level - 1);//创建新头节点下的右孩子
				root->right_child = temp;
				temp->father_node = root;
				ptr = root->right_child;
				count = ptr->level - 1;

				while (count > 0)//存储现有树的深度，建立同样深度的左子树
				{
					Init_new_node(temp, count);
					ptr->left_child = temp;
					temp->father_node = ptr;
					ptr = ptr->left_child;
					count = count - 1;
				}
				ptr->left_child = new_node;//回到了叶子节点的父节点,给叶子节点赋值
				new_node->father_node = ptr;
				ptr->hash_value = sha256_string(ptr->left_child->str, ptr->right_child == NULL ? NULL : ptr->right_child->str);

			}
			//现在叶子节点已经成功添加，但是p指向当前新插入的叶子节点的父节点，故p从下而上更新hash值
			if (ptr != root)
			{
				ptr = ptr->father_node;
				while (ptr != root)
				{
					ptr->hash_value = sha256_int(ptr->left_child->hash_value, ptr->right_child == NULL ? 0 : ptr->right_child->hash_value);
					ptr = ptr->father_node;
				}
				ptr->hash_value = sha256_int(ptr->left_child->hash_value, ptr->right_child == NULL ? 0 : ptr->right_child->hash_value);
			}
			root = Build_Merkle_Tree(root, input_list + 1, length - 1);
		}
	}
}

bool compare_str(char* s1, char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (len1 != len2)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < len1; i++)
		{
			if (*(s1 + i) != *(s2 + i))
			{
				return 0;
			}
		}
		return 1;
	}
}
void Merkle_Proof(Merkle_Tree* mt1, Merkle_Tree* mt2, bool result)//Merkle一致性证明，输入两个merkle树根，
{
	if (mt1 != NULL && mt2 != NULL)
	{
		if (mt1->hash_value != mt2->hash_value)
		{
			if (mt1->left_child != NULL && mt2->left_child != NULL && mt1->left_child->hash_value != mt2->left_child->hash_value)
			{
				Merkle_Proof(mt1->left_child, mt2->left_child, result);
			}
			else if (mt1->right_child != NULL && mt2->right_child != NULL && mt1->right_child->hash_value != mt2->right_child->hash_value)
			{
				Merkle_Proof(mt1->right_child, mt2->right_child, result);
			}
			else if (mt1->left_child->left_child == NULL && mt1->left_child->right_child == NULL && mt1->right_child->left_child == NULL && mt1->right_child->right_child == NULL && mt2->left_child->left_child == NULL && mt2->left_child->right_child == NULL && mt2->right_child->left_child == NULL && mt2->right_child->right_child == NULL)
			{
				if (!compare_str(mt1->left_child->str, mt2->left_child->str))
				{
					printf("verify fail,the word that differs are: %s              %s\n\n\n", mt1->left_child->str, mt2->left_child->str);
				}
				else if (!compare_str(mt1->right_child->str, mt2->right_child->str))
				{
					printf("verify fail,the word that differs are:%s              %s\n\n\n", mt1->right_child->str, mt2->right_child->str);
				}
			}
		}
		else
		{
			printf("verify pass!");
			result = 1;
			return;
		}
	}
}
void Print_Merkle_Tree(Merkle_Tree* mt, int high)
{
	Merkle_Tree* p = mt;
	int i;

	if (p == NULL)
		return;

	if (p->left_child == NULL && p->right_child == NULL) {
		for (i = 0; i < high - p->level; i++)
			printf("           ");

		printf("------>%s\n", p->str);
	}
	else {
		Print_Merkle_Tree(mt->left_child, high);
		printf("\n");
		for (i = 0; i < high - p->level; i++)
			printf("           ");

		printf("------>%-6d\n", p->hash_value);

		Print_Merkle_Tree(mt->right_child, high);
	}
}
void Get_Node(Merkle_Tree* root, char* input)//取得对应str是input的叶子节点
{
	if (root != NULL)
	{
		if (root->str != NULL)
		{
			if (compare_str(input, root->str))
			{
				correct_leaf = root;
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			Get_Node(root->left_child, input);
			Get_Node(root->right_child, input);
		}

	}
	return;
}
bool is_root(Merkle_Tree* node)//判断是否是根节点
{
	if (node->father_node == NULL && node->left_child != NULL && node->right_child != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Merkle_Tree* Get_Neibor_Node(Merkle_Tree* node)//取得本节点的相邻节点，若该节点是根节点则返回空指针
{
	if (is_root(node))
	{
		return NULL;
	}
	else
	{
		Merkle_Tree* temp_node = node;
		node = node->father_node;
		if (node->left_child == temp_node)
			return node->right_child;
		else
			return node->left_child;
	}
}
void Merkle_audit_path(Merkle_Tree*root,Merkle_Tree* leaf_node)
{
	if (leaf_node == NULL)
		return;
	else
	{
		leaf_node = Get_Neibor_Node(leaf_node);
		if (leaf_node == NULL)
		{
			printf("%d  ", root->hash_value);
			return;
		}
		if (leaf_node->str == NULL)
			printf("%d  ------>  ", leaf_node->hash_value);
		else if(leaf_node->str!=NULL)
			printf("%s  ------>  ", leaf_node->str);
		leaf_node = leaf_node->father_node;
		Merkle_audit_path(root, leaf_node);
	}
}
int main()
{
	char* str_arr[8] = { (char*)"Hi",(char*)",",(char*)"I",(char*)"am",(char*)"Twilight",(char*)"!",(char*)"happy",(char*)"Hi" };
	char* str_arr1[8] = {(char*)"Hi",(char*)",",(char*)"I",(char*)"am",(char*)"Rarity",(char*)"!",(char*)"happy",(char*)"Hi"};
	int num;
	int num1;
	Merkle_Tree* mt = NULL;
	Merkle_Tree* mt11 = NULL;
	Merkle_Tree* mt2 = NULL;
	Merkle_Tree* leaf = NULL;
	bool result = 0;
	mt = Build_Merkle_Tree(mt, str_arr, 8);
	char* test_input = (char*)"Twilight";
	mt11 = Build_Merkle_Tree(mt11, str_arr1, 8);
	Merkle_Proof(mt, mt11, result);
	Print_Merkle_Tree(mt, mt->level);
	cout << endl << endl << endl << endl << endl << endl << endl;
	Print_Merkle_Tree(mt11, mt11->level);
	Print_Merkle_Tree(mt, mt->level);
	Get_Node(mt, test_input);
	printf("Merkle审计路径是：");
	Merkle_audit_path(mt,correct_leaf);
}