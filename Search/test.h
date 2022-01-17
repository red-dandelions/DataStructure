
/**
 * 
 * 顺序表的查找：
```
#pragma once
#ifndef SEQSEARCH_H_
#define SEQSEARCH_H_
int search(int a[], int n, int key)
{
	a[0] = key;
	int i = n;
	for (; a[i] != key; i--);
	return i;
}
template <class T>
int SeqSearch(LinkList<T>&A, T key) // Node<T>* (返回类型)
{
	Node<T> *p = A.first->next;
	int j = 0;
	while (p != NULL && p->data != key)
	{
		p = p->next;   j++;
	}
	return j; // rturn p;
}

#endif // !SEQSEARCH_H_
```
二分查找：
```
#pragma once
#ifndef BINSEARCH_H_
#define BINSEARCH_H_
int Search_Bin(int a[], int n, int key)
{
	int low = 1;
	int high = n;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (key == a[mid]) 	return mid;
		else if (key < a[mid]) 	high = mid - 1;
		else 	low = mid + 1;
	}
	return 0;
}
#endif // !1
```
二叉排序树（BST）：
```
#ifndef BST_H_
#define BST_H_
#include<iostream>
template<class T> class BiNode
{
public:
	T data;
	BiNode<T>  *lch;
	BiNode<T>  *rch;
	BiNode():lch(NULL), rch(NULL) { };
};
template<class T> 
class BST
{
public:
	BST(T r[], int n);
	~BST();
	BiNode<T>  *search(BiNode<T> *R, T key);
	void InsertBST(BiNode<T> *&R, BiNode<T> *s);
	void Delete(BiNode<T> *&R);
	bool DeleteBST(BiNode<T> *&R, T key);
private:
	BiNode<T> *Root;
};
template<class T>
BiNode<T>* BST<T>::search(BiNode<T>* R, T key)
{
	if(R==NULL)
		return NULL;
	if (R->data == key)
		return R;
	else if (key < R->data)
		return search(R->lch, key);
	else
		return search(R->rch, key);
}
template<class T>
void BST<T>::InsertBST(BiNode<T> *&R, BiNode<T> *s)
{
	if (R == NULL)
	{
		R = s;
	}
	else if (s->data < R->data)
	{
		InsertBST(R->lch, s);
	}
	else
	{
		InsertBST(R->rch, s);
	}
}
template<class T>
void BST<T>::Delete(BiNode<T>*& R)
{
	BiNode<T> *q, *s;
	if (R->lch == NULL) //右子树节点和叶子
	{
		q = R;
		R = R->rch; 
		delete q;
	}
	else if (R->rch == NULL) //左子树节点
	{
		q = R;
		R = R->lch; 
		delete q;
	}
	else { //左右子树都有的节点。s是R的前驱， q是s的双亲
		q = R; 
		s = R->lch;
		while (s->rch != NULL) 
		{ 
			q = s; 
			s = s->rch; 
		}
		R->data = s->data;
		if (q != R)  
			q->rch = s->lch;
		else       
			R->lch = s->lch;  // q==R: 表示s为R的孩子
		delete s;
	}
}
template<class T>
bool BST<T>::DeleteBST(BiNode<T>*& R, T key)
{
	if(R==NULL)
		return false;
	else
	{
		if (key == R->data)
			Delete(R);
		else if (key < R->data)
			DeleteBST(R->lch, key);
		else
			DeleteBST(R->rch, key);
		return true;
	}
}
template<class T>
BST<T>::BST(T r[], int n)
{
	Root = NULL;
	for (int i = 0; i < n; i++)
	{
		BiNode<T>* s = new BiNode <T>;
		s->data = r[i];
		s->lch = s->rch = NULL;
		InsertBST(Root, s);
	}
}
template<class T>
BST<T>::~BST()
{
	while (Root != NULL)
		Delete(Root);
	delete Root;
}
#endif // !BST_H_
#pragma once
```
平衡二叉树（AVL）：
```


```
*/

