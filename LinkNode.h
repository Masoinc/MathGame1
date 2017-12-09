// LinkNode.h
//定义了基本的链表结构

#ifndef MATHGAME_LINKNODE_H
#define MATHGAME_LINKNODE_H

#endif //MATHGAME_LINKNODE_H

#include <string>
using namespace std;

struct Info
{
    string scheme;
};

//链表定义
struct Node
{
    Info val;
    Node *next;
    Node(Info x):val(x),next(NULL) {}
};

class LinkList
{
public:
    //构造函数
    LinkList();
    //在链表头部插入结点
    void InsertHead(Info val);
    //插入结点
    void Insert(Info val,int pos);
    //删除结点
    void Remove(Info val);
    //得到链表长度
    int Length();
    //查找节点位置
    int Find(Info val);
    //链表反序
    void Reverse();
    //打印链表
    string getval();
    //析构函数
    ~LinkList();
private:
    Node *head;
    int length;
};