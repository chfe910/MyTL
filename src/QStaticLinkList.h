

#ifndef __QSTATICLINKLIST__
#define __QSTATICLINKLIST__

#include <iostream>
using namespace std;

template<class Type>
class QStaticLinkList
{

private:
	
	#define DEFAULT_MAX_SIZE 1000

	typedef struct 
	{
		Type val;
		int next;
	} QStaticListNode;

	QStaticListNode *list;
	int Capacity;
	int length;

	int  mallocNode();
	void freeNode(int idx);
	int  getIdx(int pos);

public:

	//构造函数
	QStaticLinkList();
	QStaticLinkList(int capacity);
	//拷贝构造函数...
	//赋值构造函数...

	bool empty() { return length == 0; };
	bool get(int pos, Type &value);
	int  find(Type value);

	bool insert(int pos, Type value);
	bool Delete(int pos);

	~QStaticLinkList() { delete [] list; cout << "here!";};
};

template <class Type>
QStaticLinkList<Type>::QStaticLinkList()
{
	Capacity = DEFAULT_MAX_SIZE;
	length = 0;

	list = new QStaticListNode [Capacity];
	for (int i = 0; i < Capacity - 1; i++)
	{
		list[i].next = i + 1;
	}
	list[Capacity - 1].next = 0; // 目前静态链表为空，最后一个元素的next为0
}

/*新建一个一维数组list，将该数组中各分量链成一条备用链表，list[0].next为头指针，“0”表示空指针*/
template <class Type>
QStaticLinkList<Type>::QStaticLinkList(int capacity = DEFAULT_MAX_SIZE)
{
	Capacity = capacity;
	length = 0;

	list = new QStaticListNode [Capacity];
	for (int i = 0; i < Capacity - 1; i++)
	{
		list[i].next = i + 1;
	}
	list[Capacity - 1].next = 0; // 目前静态链表为空，最后一个元素的next为0
}

/*若备用空间链表非空，则返回分配的结点下标，否则返回0*/
template <class Type>
int QStaticLinkList<Type>::mallocNode()
{
	int idx = list[0].next;//当前数组第一个元素的next存的值，就是要返回的第一个备用空闲的下标。

	if (idx)
	{
		list[0].next = list[idx].next;//由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用。
	}

	return idx;
}

/*将下标为idx的空闲结点回收到备用链表*/
template <class Type>
void QStaticLinkList<Type>::freeNode(int idx)
{
	list[idx].next = list[0].next;//把第一个元素next值赋给要删除的分量next
	list[ 0 ].next = idx;//把要删除的分量下标赋值给第一个元素的next
}

template <class Type>
int QStaticLinkList<Type>::getIdx(int pos)
{
	if (pos > length) return -1;

	int idx = Capacity - 1;
	for (int i = 0; i < pos; ++i)
	{
		idx = list[idx].next;
	}

	return idx;
}

template <class Type>
bool QStaticLinkList<Type>::get(int pos, Type &value)
{
	if (pos < 1 || pos > length) return false;

	int idx = Capacity - 1;
	for (int i = 0; i < pos; ++i)
	{
		idx = list[idx].next;
	}
	value = list[idx].val;

	return true;
}

template <class Type>
int QStaticLinkList<Type>::find(Type value)
{
	int idx = list[Capacity - 1].next;
	for (int i = 1; i <= length; ++i)
	{
		if (list[idx].val == value) return i;
		idx = list[idx].next;
	}

	return -1;
}

/*在链表中pos位置之前插入新的数据元素*/
template <class Type>
bool QStaticLinkList<Type>::insert(int pos, Type value)
{
	if (pos < 1 || pos > length + 1)
	{
		return false;
	}

	int newPos = mallocNode();
	if (!newPos)
	{
		return false;
	}

	list[newPos].val = value;
	int preIdx = getIdx(pos - 1);
	list[newPos].next = list[preIdx].next;
	list[preIdx].next = newPos;
	++length;

	return true;
}

/*删除链表中pos位置的数据元素*/
template <class Type>
bool QStaticLinkList<Type>::Delete(int pos)
{
	if (pos < 1 || pos > length)
	{
		return false;
	}
	
	int preIdx = getIdx(pos - 1);
	int delIdx = list[preIdx].next;
	list[preIdx].next = list[delIdx].next;
	freeNode(delIdx);
	--length;

	return true;
}

#endif
