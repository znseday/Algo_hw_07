/*
*     Кроссплатформенное ядро декартового дерева
*/

//---------------------------------------------------------------------------
#ifndef MySimpleTreeH
#define MySimpleTreeH
//---------------------------------------------------------------------------

// Расширить класс из 1 части и создать декартово дерево. +4 байта.
// Методы к реализации:
// Tree merge(Tree l, Tree r) - объединение двух деревьев
// void split(Tree t, int x, out Tree l, out Tree r) - разделение дерева на две части
// void insert(int x) - добавление элемента
// void remove(int x) - удаление элемента

#include <string>

#include "MySimpleTree.h"

template<typename T>
struct TreapItemType : public SimpleItemType<T>
{
	int Prior;
};


template<typename T>
class Treap
{
protected:




public:



};


#endif
