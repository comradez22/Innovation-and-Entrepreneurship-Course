//
//  fat16.h
//  fat16
//
//  Created by 张施珵 on 2022/5/27.
//

#ifndef fat16_h
#define fat16_h

#include<iostream>
#include<string>
using namespace std;
#define  DISK_MAXLEN  2560  //disk的大小
#define   TSIZE  40        //目录表的个数  也是fat的个数   簇长64


//块号
struct fcb
{
    int blockindex; //放的第一个块号
    int filesize;   //文件长度
};

//目录项 存文件相关信息
struct item
{
    char filename[8];
    int fatnum;  //fat 开始的索引号
    int fcbnum;  //当前文件在磁盘块中开始存储的盘块号
    int listnum;  //目录项列表开始的索引号
};

//目录项组成的列表
struct itemlist
{
    int itemnum;
    item dirs[TSIZE];
};

char Disk[DISK_MAXLEN];  //硬盘 不设置mbr dbr
int startindex;


int fat[TSIZE];
itemlist* list[10];
fcb* fcblist[TSIZE];
itemlist rootitemlist;    //根表
itemlist* currentlist; //当前表



int fnum = 0; //fcb序号
int tnum = 0; //tab序号

void init()
{
    rootitemlist.itemnum = 0;
    currentlist = &rootitemlist;
    startindex = 8 + TSIZE;  //留下dbr的8
}


//直接遍历整个当前的目录表来查看文件名，返回在目录表里的序号
int finditem(char filename[])
{
    int itemnum = currentlist->itemnum;
    int unitIndex = -1;
    for (int i = 0; i < itemnum; i++)
        if (strcmp(filename, currentlist->dirs[i].filename) == 0)
            unitIndex = i;
    return unitIndex;
}


//让后面的表项直接替代即可
void deleteitem(int index)
{
    int itemnum = currentlist->itemnum;
    for (int i = index; i < itemnum - 1; i++)
    {
        currentlist->dirs[i] = currentlist->dirs[i + 1];
    }
    currentlist->itemnum--;
}


//在fat表中把一整条路线找出来然后把它们清空
void freefat(char file[])
{
    int i = currentlist->dirs[finditem(file)].fatnum;//目录表里面找到文件的目录里面存的startfat
    if (i == -1)
    {
        fat[i] = 0;
        return;
    }  //只有一块
    while (i == -1)
    {
        int temp = i;
        i = fat[i];
        fat[temp] = 0;
    }
    if (i == -1)
    {
        fat[i] = 0;
        return;
    }//找到一条完整的路线，全赋0
}



//加一个项目到目录表里面
void additem(char filename[])
{
    int itemnum = currentlist->itemnum;
    //有同名的文件
    if (finditem(filename) != -1)
    {
        cout<<"file already exist"<<endl;
        return;
    }
    
    //新建一个放在现在的目录表的最后，存名字和类型
    item* newitem = &currentlist->dirs[itemnum];
    currentlist->itemnum++;
    int i = strlen(filename);
    while (i--)
        newitem->filename[i] = filename[i];
    return;
}

//找一个空的fat起点
int find()
{
    for (int i = 0; i < TSIZE; i++)
    {
        if (fat[i] == 0)
            return i;
    }
    return 0;
}

//把num个块大小的放到fat里面去
void intofat(int num, int unitindex)
{
    int index = currentlist->dirs[unitindex].fatnum;
    for (int i = 0; i < num - 1; i++)
    {
        int j = find();
        fat[index] = j;
        index = j;
    }
    fat[index] = -1;
}


void create(char filename[], int filesize)
{
    //分别创建项，分配fcb
    additem(filename);//, type);
    int index = finditem(filename);
    fcb* curfcb = (fcb*)new fcb();
    curfcb->blockindex = startindex++;
    curfcb->filesize = filesize;
    fcblist[fnum] = curfcb;
    currentlist->dirs[index].fcbnum = fnum;
    //分配fat
    int i = find();
    currentlist->dirs[index].fatnum = i;
    fat[i] = -1;
    cout<<"created"<<endl;
}



void del(char filename[])
{
    int index = finditem(filename);
    if (index == -1)
    {
        cout << "not found" << endl;
        return;
    }
    deleteitem(index);
    freefat(filename);
    cout<<"deleted"<<endl;
}


void read(char filename[], int length)
{
    int itemindex = finditem(filename);
    if (itemindex == -1)
    {
        cout << "not found" << endl;
        return;
    }
    // 找到file对应的fcb
    int index = currentlist->dirs[itemindex].fcbnum;
    fcb* myfcb = fcblist[index];
    int h=myfcb->blockindex;
    for (int i = 0; i < length; i++)
    {
        cout << Disk[i+h];
    }
    cout << endl;
}



void write(char filename[], char content[])
{
    int unitindex = finditem(filename);
    if (unitindex == -1)
    {
        cout << "not found" << endl;
        return;
    }
    int length = sizeof(content);
    //放到fat，size+
    int num = (length % 32 == 0) ? length / 32 : length / 32 + 1;
    intofat(num, unitindex);
    fcblist[currentlist->dirs[unitindex].fcbnum]->filesize = num;

    //找到startfab写入disk
    int index = currentlist->dirs[unitindex].fcbnum;
    fcb* myfcb = fcblist[index];
    for (int i = 0; i < length; i++)
    {
        Disk[i + myfcb->blockindex] = content[i];
    }
}



//打印所有
void ls()
{
    int uninum = currentlist->itemnum;
    for (int i = 0; i < uninum; i++)
    {
        item curunit = currentlist->dirs[i];
        cout << curunit.filename << " ";
    }
    cout << endl;
}


#endif /* fat16_h */
