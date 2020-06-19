/*
*     Кроссплатформенное ядро AVL дерева
*/

//---------------------------------------------------------------------------
#ifndef MyAVLTreeH
#define MyAVLTreeH
//---------------------------------------------------------------------------

#include "MySimpleTree.h"
#include <algorithm>

template<typename T>
struct AVLItemType : public SimpleItemType<T>
{
	int h = 1;

	AVLItemType() = delete;
	AVLItemType(const T &_data) : SimpleItemType<T>(_data) {}

	virtual ~AVLItemType();
};

template<typename T>
AVLItemType<T>::~AVLItemType()
{
//	ShowMessage(L"AVLItemType удаляют: " + String(SimpleItemType<T>::Data)); // Для отладки
}


template <typename T>
class AVLTree : public BSTree<T>
{
protected:

	AVLItemType<T> *ItemToDel = nullptr;

	[[nodiscard]] int GetH(AVLItemType<T> *t)
	{
		return t ? t->h : 0;
	}


	[[nodiscard]] int GetBalance(AVLItemType<T> *t)
	{
//		return GetH(dynamic_cast<AVLItemType<T>*>(t->pLeft)) - GetH(dynamic_cast<AVLItemType<T>*>(t->pRight));
		return GetH(dynamic_cast<AVLItemType<T>*>(t->pRight)) - GetH(dynamic_cast<AVLItemType<T>*>(t->pLeft));
	}

	void ReCalcH(AVLItemType<T> *t)
	{
		t->h = std::max(GetH(dynamic_cast<AVLItemType<T>*>(t->pLeft)),
						GetH(dynamic_cast<AVLItemType<T>*>(t->pRight))) + 1;
	}


	[[nodiscard]] virtual AVLItemType<T> * CreateNode(const T &_data)
	{
		//ShowMessage(L"Создаем AVLItemType<T>");
		return new AVLItemType<T>(_data);
	}

	[[nodiscard]] AVLItemType<T> * Rebalance(AVLItemType<T> *t);

	[[nodiscard]] AVLItemType<T> * SmallLeftRotation (AVLItemType<T> *a);
	[[nodiscard]] AVLItemType<T> * SmallRightRotation(AVLItemType<T> *a);

//	void BigLeftRotation (AVLItemType<T> *a, AVLItemType<T> * *parent);
//	void bigRightRotation(AVLItemType<T> *a, AVLItemType<T> * *parent);

	[[nodiscard]] AVLItemType<T> * Add_inside(AVLItemType<T> *t, const T &_data);

	[[nodiscard]] AVLItemType<T> * FindMin(AVLItemType<T> *t);
	[[nodiscard]] AVLItemType<T> * RemoveMin(AVLItemType<T> *t);
	[[nodiscard]] AVLItemType<T> * Remove_inside(AVLItemType<T> *t, const T &_data);

public:

	// Сделать overload или override?

	[[nodiscard]] AVLItemType<T> * Add(const T &_data); // Простой overload
	[[nodiscard]] bool Remove(const T &_data);  // Простой overload

};
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::Add_inside(AVLItemType<T> *t, const T &_data)
{
	if ( !t )
	{
		AVLItemType<T> *NewNode = CreateNode(_data);
		if (!BSTree<T>::pRoot)
		{
			BSTree<T>::pRoot = NewNode;
			return dynamic_cast<AVLItemType<T>*>(BSTree<T>::pRoot);
		}
		else
			return NewNode;
	}

	if ( _data < t->Data)
		t->pLeft = Add_inside(dynamic_cast<AVLItemType<T>*>(t->pLeft), _data);
	else if ( _data > t->Data)
		t->pRight = Add_inside(dynamic_cast<AVLItemType<T>*>(t->pRight), _data);
	else
		throw std::invalid_argument("_data == t->Data"); // пока так, чтобы сразу вылезти из рекурсии

	return Rebalance(t);

}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::Add(const T &_data)
{
	try
	{
		return Add_inside(dynamic_cast<AVLItemType<T>*>(BSTree<T>::pRoot), _data);
	}
	catch(...) // ловим "выпрыгивание" из рекурсии; криво - но пока так
	{
		return nullptr;
	}

}
//----------------------------------------------------------------------------

//template <typename T>
//[[nodiscard]] bool AVLTree<T>::Remove_v2(const T &_data)
//{
//	bool b = BSTree<T>::Remove_v2(_data); // Попытка расширить базовыу версию пока не увенчалась успехом
//
//	return b;
//}


template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::SmallRightRotation(AVLItemType<T> *a)
{
	//bool RootCorrection = false;
	//if (a == BSTree<T>::pRoot)
	//	RootCorrection = true;

	AVLItemType<T> *b = dynamic_cast<AVLItemType<T>*>(a->pLeft);
	AVLItemType<T> *c = dynamic_cast<AVLItemType<T>*>(b->pRight);

	a->pLeft = c;
	b->pRight = a;

	ReCalcH(a);
	ReCalcH(b);

	//if (RootCorrection)
    if (a == BSTree<T>::pRoot)
		BSTree<T>::pRoot = b;

	return b;
}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::SmallLeftRotation(AVLItemType<T> *a)
{
	//bool RootCorrection = false;
	//if (a == BSTree<T>::pRoot)
	//	RootCorrection = true;

	AVLItemType<T> *b = dynamic_cast<AVLItemType<T>*>(a->pRight);
	AVLItemType<T> *c = dynamic_cast<AVLItemType<T>*>(b->pLeft);

	a->pRight = c;
	b->pLeft = a;

	ReCalcH(a);
	ReCalcH(b);

	//if (RootCorrection)
	if (a == BSTree<T>::pRoot)
		BSTree<T>::pRoot = b;

	return b;
}
//----------------------------------------------------------------------------

//template <typename T>
//void AVLTree<T>::BigLeftRotation(AVLItemType<T> *a) // нет необходимости - лаконично получилось в Rebalance
//{
//}
//
//template <typename T>
//void AVLTree<T>::bigRightRotation(AVLItemType<T> *a)
//{
//}

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::Rebalance(AVLItemType<T> *t)
{
	ReCalcH(t);

	if( GetBalance(t) == 2 ) // >=
	{
		if( GetBalance(dynamic_cast<AVLItemType<T>*>(t->pRight)) < 0 )
			t->pRight = SmallRightRotation(dynamic_cast<AVLItemType<T>*>(t->pRight));
		return SmallLeftRotation(t);
	}
	if( GetBalance(t) == -2 ) // <=
	{
		if( GetBalance(dynamic_cast<AVLItemType<T>*>(t->pLeft)) > 0  )
			t->pLeft = SmallLeftRotation(dynamic_cast<AVLItemType<T>*>(t->pLeft));
		return SmallRightRotation(t);
	}
	return t;
}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::FindMin(AVLItemType<T> *t)
{
	return t->pLeft ? FindMin(dynamic_cast<AVLItemType<T>*>(t->pLeft)) : t;
}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::RemoveMin(AVLItemType<T> *t)
{
	if ( !t->pLeft )
	{
		return dynamic_cast<AVLItemType<T>*>(t->pRight);
	}

	t->pLeft = RemoveMin(dynamic_cast<AVLItemType<T>*>(t->pLeft));

	return Rebalance(t);
}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] AVLItemType<T> * AVLTree<T>::Remove_inside(AVLItemType<T> *t, const T &_data)
{
	if (!t)
		return nullptr;

	if (_data < t->Data)
		t->pLeft = Remove_inside(dynamic_cast<AVLItemType<T>*>(t->pLeft), _data);
	else if (_data > t->Data)
		t->pRight = Remove_inside(dynamic_cast<AVLItemType<T>*>(t->pRight), _data);
	else
	{

		AVLItemType<T> *Left = dynamic_cast<AVLItemType<T>*>(t->pLeft);
		AVLItemType<T> *Right = dynamic_cast<AVLItemType<T>*>(t->pRight);

		ItemToDel = t;

		if (!Right)
			return Left;

		AVLItemType<T> *Min = FindMin(Right);
		Min->pRight = RemoveMin(Right);
		Min->pLeft = Left;

        return Rebalance(Min);
	}

    return Rebalance(t);
}
//----------------------------------------------------------------------------

template <typename T>
[[nodiscard]] bool AVLTree<T>::Remove(const T &_data)
{
	ItemToDel = nullptr;

	AVLItemType<T>* NewRoot = Remove_inside(dynamic_cast<AVLItemType<T>*>(BSTree<T>::pRoot), _data);

	if (ItemToDel)
	{
		if (ItemToDel == BSTree<T>::pRoot)
		{
			BSTree<T>::pRoot = NewRoot;
		}

		delete ItemToDel;
		return true;
	}
	else
		return false;

//	return Remove_inside(dynamic_cast<AVLItemType<T>*>(BSTree<T>::pRoot), _data) ? true : false;
}
//----------------------------------------------------------------------------



#endif

