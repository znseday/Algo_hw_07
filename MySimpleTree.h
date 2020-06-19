/*
*     Кроссплатформенное ядро обычного бинарного дерева
*/

//---------------------------------------------------------------------------
#ifndef MySimpleTreeH
#define MySimpleTreeH
//---------------------------------------------------------------------------

#include <string>


template<typename T>
struct SimpleItemType
{
	T Data;
	SimpleItemType<T> *pLeft = nullptr;
	SimpleItemType<T> *pRight = nullptr;

	SimpleItemType() = delete;
	SimpleItemType(const T &_data) : Data(_data) {}

	virtual ~SimpleItemType(); // делаем структуры полиморфными
};

template<typename T>
SimpleItemType<T>::~SimpleItemType()
{
 //	ShowMessage(L"SimpleItemType удаляют: " + String(Data)); // Для отладки
}
//---------------------------------------------------------------------------

template<typename T>
class BSTree
{
protected:
	SimpleItemType<T> *pRoot = nullptr;

	void ClearAll_inside(SimpleItemType<T> *pCur);

	void PrintKPL_inside(std::string &str, SimpleItemType<T> *pCur);
	void PrintLKP_inside(std::string &str, SimpleItemType<T> *pCur);

	[[nodiscard]] virtual SimpleItemType<T> * CreateNode(const T &_data)
	{
//		ShowMessage(L"Создаем SimpleItemType<T>");
		return new SimpleItemType<T>(_data);
	}

//	[[nodiscard]] virtual SimpleItemType<T> * Insert_inside(SimpleItemType<T> *t, const T &_data)
//	{
//		ShowMessage(L"Insert_inside для SimpleItemType<T>");
//		//return new SimpleItemType<T>(_data);
//
//		if (!t)
//			return CreateNode(_data);
//
//		if (t->Data == _data)
//			throw std::invalid_argument("_data == t->Data"); // пока так, чтобы сразу вылезти из рекурсии
//	}


public:
	BSTree() = default;
	BSTree(const BSTree &) = delete;
	BSTree(BSTree &&) = delete;
	BSTree & operator=(const BSTree &) = delete;
	BSTree & operator=(BSTree &&) = delete;

	~BSTree() {ClearAll();}

	void PrintKPL(std::string &str) { PrintKPL_inside(str, pRoot); }
	void PrintLKP(std::string &str) { PrintLKP_inside(str, pRoot); }

//	[[nodiscard]] std::pair<SimpleItemType<T>*, SimpleItemType<T>**> Add(const T &_data);
	[[nodiscard]] SimpleItemType<T>* Add(const T &_data);

	[[nodiscard]] SimpleItemType<T> * Find(const T &_data) const; // Возвращать указатель на узел целиком или только на Data?

	[[nodiscard]] bool Remove(const T &_data);
	[[nodiscard]] bool Remove_v2(const T &_data);

	void ClearAll();

};
//---------------------------------------------------------------------------

template<typename T>
[[nodiscard]] SimpleItemType<T> * BSTree<T>::Find(const T &_data) const
{
	SimpleItemType<T> *pCur = pRoot;

	if (!pRoot)
        return nullptr;

	do
	{
		if (_data < pCur->Data)
		{
			if (!pCur->pLeft)
				return nullptr;

			pCur = pCur->pLeft;
		}
		else if (_data > pCur->Data)
		{
			if (!pCur->pRight)
				return nullptr;

			pCur = pCur->pRight;
		}
		else
		{
			//return &pCur->Data;
			return pCur;
		}

	} while(pCur != nullptr);

//	return &pCur->Data;
	return pCur;
}
//---------------------------------------------------------------------------

template<typename T>
[[nodiscard]] SimpleItemType<T>* BSTree<T>::Add(const T &_data)
//[[nodiscard]] std::pair<SimpleItemType<T>*, SimpleItemType<T>**> BSTree<T>::Add(const T &_data)
{
	SimpleItemType<T> *pCur = pRoot;
	//SimpleItemType<T> *parent = nullptr;

	SimpleItemType<T> *pNew = nullptr; // CreateNode(_data);

	if (pRoot == nullptr)   //если это первый элемент
	{
		pNew = CreateNode(_data);
		pCur = pRoot = pNew;
	}
	else                   //не первый элемент
	{
		do
		{
			if (_data < pCur->Data)
			{
				if (!pCur->pLeft)
				{
					pNew = CreateNode(_data);
					pCur->pLeft = pNew;
					break;
				}

				pCur = pCur->pLeft;
			}
			else if (_data > pCur->Data)
			{
				if (!pCur->pRight)
				{
                    pNew = CreateNode(_data);
					pCur->pRight = pNew;
					break;
				}
				pCur = pCur->pRight;
			}
			else
			{
				//return {nullptr, &(*parent)};
				return nullptr;
			}

		} while(pCur != nullptr);
	}

//	return {pNew, parent};
    return pNew;
}
//---------------------------------------------------------------------------

template<typename T>
void BSTree<T>::ClearAll()
{
	ClearAll_inside(pRoot);
}
//---------------------------------------------------------------------------

template<typename T>
void BSTree<T>::PrintKPL_inside(std::string &str, SimpleItemType<T> *pCur)
{
	if (pCur)
	{
		str += std::to_string(pCur->Data) + " ";

		PrintKPL_inside(str, pCur->pRight);
		PrintKPL_inside(str, pCur->pLeft);
	}

}
//---------------------------------------------------------------------------

template<typename T>
void BSTree<T>::PrintLKP_inside(std::string &str, SimpleItemType<T> *pCur)
{
	if (pCur)
	{
		PrintLKP_inside(str, pCur->pLeft);

		str += std::to_string(pCur->Data) + " ";

		PrintLKP_inside(str, pCur->pRight);
	}
}
//---------------------------------------------------------------------------

template<typename T>
void BSTree<T>::ClearAll_inside(SimpleItemType<T> *pCur)
{
//	SimpleItemType<T> *pCur = pRoot;
	if (pCur != nullptr)
	{
		ClearAll_inside(pCur->pLeft);

		ClearAll_inside(pCur->pRight);

		delete pCur;
	}

	pRoot = nullptr;
}
//---------------------------------------------------------------------------

template<typename T>
bool BSTree<T>::Remove(const T &_data)  // По мотивам лекции
{
	SimpleItemType<T> *previous = nullptr,
					  *present = pRoot,
					  *s = nullptr;

	bool r = false;

	bool found = false;
	while (present && !found)
	{
		if (present->Data == _data)
			found = true;
		else
		{
			previous = present;
			if (_data < present->Data)
			{
				present = present->pLeft;   r = false;
			}
			else
			{
				present = present->pRight;  r = true;
			}
		}
	}

	if (found)
	{
		if (!previous) // удаляем корень
		{
			if (!present->pLeft && !present->pRight) // единственный элемент - корень
			{
				pRoot = nullptr;
			}
			else if ( !present->pLeft )
			{
				pRoot = present->pRight;
			}
			else if ( !present->pRight )
			{
				pRoot = present->pLeft;
			}
			else // есть обе ветки
			{
				s = present->pLeft;
				while (s->pRight)
				{
					s = s->pRight; // находим самый правый узел/лист
				}

				pRoot = present->pLeft;
				s->pRight = present->pRight;
			}

			delete present; return true;
		}
		else // Удаляем не корень
		{
			s = present->pLeft;
			while (s && s->pRight)
			{
				s = s->pRight; // находим самый правый узел/лист
			}

			if (!present->pLeft && !present->pRight) // нет дочерних элементов
			{
				delete present;
				if (r)
					previous->pRight = nullptr;
				else
					previous->pLeft = nullptr;
				return true;
			}
			else if (!present->pLeft /* && present->pRight*/)
			{
				if (r)
					previous->pRight = present->pRight;
				else
					previous->pLeft = present->pRight;
			}
			else if (/*present->pLeft && */ !present->pRight)
			{
				if (r)
					previous->pRight = present->pLeft;
				else
					previous->pLeft = present->pLeft;
			}
            else // Общий случай - есть обе ветки
			{
				if (r)
					previous->pRight = present->pLeft;
				else
					previous->pLeft = present->pLeft;


				if (s)
					s->pRight = present->pRight;

			}

			delete present; return true;
		}
	}

	return found;
}
//---------------------------------------------------------------------------

template<typename T>
bool BSTree<T>::Remove_v2(const T &_data)   // По мотивам книги Р. Уинера "Турбо СИ"
{                                   // Данная версия не приводит к сильной расбалансировке
	SimpleItemType<T> *previous = nullptr,
					  *present = pRoot,
					  *replace = nullptr,
					  *s = nullptr,
					  *parent;

	bool found = false;
	while (present && !found)
	{
		if (present->Data == _data)
			found = true;
		else
		{
			previous = present;
			if (_data < present->Data)
				present = present->pLeft;
			else
				present = present->pRight;
		}
	}

	if (found)
	{
		if (!present->pLeft)
			replace = present->pRight;
		else
			if (!present->pRight)
				replace = present->pLeft;
			else
			{
				parent = present;
				replace = present->pRight;
				// идем вправо и находим самый левый из правого поддерева
				// для замены на удаляемый
				s = replace->pLeft;
				while (s)
				{
					parent = replace;
					replace = s;
					s = replace->pLeft;
				}
				if (parent != present)
				{
					parent->pLeft = replace->pRight;
					replace->pRight = present->pRight;
				}
				replace->pLeft = present->pLeft;
			}

			if (!previous)
				pRoot = replace;
			else
				if (present == previous->pLeft)
					previous->pLeft = replace;
				else
					previous->pRight = replace;

			delete present;
	}
	return found;
}


//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
