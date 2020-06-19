//---------------------------------------------------------------------------
#include <chrono>

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

using ClockType = std::chrono::steady_clock;


//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	MyBSTree  = new BSTreeDraw<int>;
	MyAVLTree = new AVLTreeDraw<int>;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAddClick(TObject *Sender)
{
	int NewItem = EditNewItem->Text.ToIntDef(-1);

	if (rbBSTree->Checked)
	{
		if (! MyBSTree->Add(NewItem) )
		{
			ShowMessage(L"Такой элемент уже есть в дереве");
			return;
		}
		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}
	else if (rbAVLTree->Checked)
	{
		if ( !MyAVLTree->Add(NewItem) )
		{
			ShowMessage(L"Такой элемент уже есть в дереве");
			return;
		}
		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnPrintKPLClick(TObject *Sender)
{
	std::string tStr = "";

	if (rbBSTree->Checked)
		MyBSTree->PrintKPL(tStr);
	else if (rbAVLTree->Checked)
		MyAVLTree->PrintKPL(tStr);

	EditTree->Text = String(tStr.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnPrintLKPClick(TObject *Sender)
{
	std::string tStr = "";

	if (rbBSTree->Checked)
		MyBSTree->PrintLKP(tStr);
	else if (rbAVLTree->Checked)
    	MyAVLTree->PrintLKP(tStr);

	EditTree->Text = String(tStr.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnStandartTestClick(TObject *Sender)
{
	if (rbBSTree->Checked)
	{
		MyBSTree->Add(10);
		MyBSTree->Add(21);
		MyBSTree->Add(15);
		MyBSTree->Add(7);
		MyBSTree->Add(9);
		MyBSTree->Add(17);
		MyBSTree->Add(4);
		MyBSTree->Add(2);
		MyBSTree->Add(12);
		MyBSTree->Add(14);
		MyBSTree->Add(25);
		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);

	}
	else if (rbAVLTree->Checked)
	{
		MyAVLTree->Add(10);
		MyAVLTree->Add(21);
		MyAVLTree->Add(15);
		MyAVLTree->Add(7);
		MyAVLTree->Add(9);
		MyAVLTree->Add(17);
		MyAVLTree->Add(4);
		MyAVLTree->Add(2);
		MyAVLTree->Add(12);
		MyAVLTree->Add(14);
		MyAVLTree->Add(25);
		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnClearAllClick(TObject *Sender)
{
	if (rbBSTree->Checked)
	{
		MyBSTree->ClearAll();
		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}
	else if (rbAVLTree->Checked)
	{
		MyAVLTree->ClearAll();
		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete MyBSTree;
    delete MyAVLTree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemoveClick(TObject *Sender)
{
	int DelItem = EditNewItem->Text.ToIntDef(-1);

	if (rbBSTree->Checked)
	{
		std::size_t CurCount = MyBSTree->GetCount();

		if ( !MyBSTree->Remove(DelItem) )
		{
			ShowMessage(L"Элемент не найден");
			return;
		}

		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);

		if (CurCount != MyBSTree->GetCount()+1)
			ShowMessage(L"Некорректное удаление!");

	}
	else if (rbAVLTree->Checked)
	{
		std::size_t CurCount = MyAVLTree->GetCount();

		if ( !MyAVLTree->Remove(DelItem) )
		{
			ShowMessage(L"Элемент не найден");
			return;
		}

		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);

		if (CurCount != MyAVLTree->GetCount()+1)
			ShowMessage(L"Некорректное удаление!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnFindClick(TObject *Sender)
{
	int NewItem = EditNewItem->Text.ToIntDef(-1);

	decltype(MyBSTree->Find(NewItem)) p;

	if (rbBSTree->Checked)
	{
		p = MyBSTree->Find(NewItem);
	}
	else if (rbAVLTree->Checked)
	{
		p = MyAVLTree->Find(NewItem);
	}
	if (!p)
	{
		ShowMessage(L"Элемент не найден");
		return;
	}
	ShowMessage(L"Найден элемент: " + String(p->Data));

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove_v2Click(TObject *Sender)
{
	int DelItem = EditNewItem->Text.ToIntDef(-1);

	if (rbBSTree->Checked)
	{
		std::size_t CurCount = MyBSTree->GetCount();

		if ( !MyBSTree->Remove_v2(DelItem) )
		{
			ShowMessage(L"Элемент не найден");
			return;
		}

		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);

		if (CurCount != MyBSTree->GetCount()+1)
			ShowMessage(L"Некорректное удаление!");
	}
	else if (rbAVLTree->Checked)
	{
		ShowMessage(L"Для АВЛ-дерева есть только одна версия удаления элемента");
		return;

//		std::size_t CurCount = MyAVLTree->GetCount();
//
//		if ( !MyAVLTree->Remove_v2(DelItem) )
//		{
//			ShowMessage(L"Элемент не найден");
//			return;
//		}
//
//		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
//
//		if (CurCount != MyAVLTree->GetCount()+1)
//			ShowMessage(L"Некорректное удаление!");
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSmallRandomClick(TObject *Sender)
{
	const size_t N = 45;
	MyUniqueRandom Gen(N, 5);

	if (rbBSTree->Checked)
	{
		for (size_t i = 0; i < N; i++)
		{
			int v = Gen.GetNext();
			Memo->Lines->Add("v = " + String(v)); // Для отладки

			if ( !MyBSTree->Add(v) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		MyBSTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}
	else if (rbAVLTree->Checked)
	{
		for (size_t i = 0; i < N; i++)
		{
			int v = Gen.GetNext();
			Memo->Lines->Add("v = " + String(v)); // Для отладки

			if ( !MyAVLTree->Add(v) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		MyAVLTree->Draw(imgDraw, imgDraw->ClientWidth, imgDraw->ClientHeight, 0, imgDraw->ClientWidth/2, 20);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnTestClick(TObject *Sender)
{
// Создать два дерева (максимальный размер дерева выберите такой,
//                                  чтобы программа работала не дольше 1 минуты)
// Добавить N чисел в случайном (первое) и возрастающем (второе) порядке.
// Искать N/10 случайных чисел в каждом дереве.
// Удалить N/10 случайных элементов в каждом дереве.
//
// Заполнить таблицу производительности и сделать вывод. +1 байт.

	const size_t N = EditN->Text.ToIntDef(0);

	Memo->Clear();
	Memo->Lines->Add("N = " + String(N));

	MyUniqueRandom Gen_ToAdd(N, 1);
	MyUniqueRandom Gen_ToFind(N, 1);
	MyUniqueRandom Gen_ToDel(N, 1);

	std::chrono::time_point<ClockType> TimeStart, TimeEnd;
    double Time;

	if (rbBSTree->Checked)
	{
//		BSTree<int> *BSTreeRandom = new BSTree<int>;
//		BSTree<int> *BSTreeSeq = new BSTree<int>;
		BSTree<int> BSTreeRandom, BSTreeSeq;

		TimeStart = ClockType::now();
		for (size_t i = 0; i < N; i++)
		{
			int v = Gen_ToAdd.GetNext();

			if ( !BSTreeRandom.Add(v) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTree: Add random, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N; i++)
		{
			if ( !BSTreeSeq.Add(i) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTreeSeq: Add sequentially, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !BSTreeRandom.Find( Gen_ToFind.GetNext() ) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTreeRandom: Find N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));



		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !BSTreeSeq.Find( Gen_ToFind.GetNext() ) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTreeSeq: Find N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !BSTreeRandom.Remove(Gen_ToDel.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTreeRandom: Remove N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));



		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !BSTreeSeq.Remove(Gen_ToDel.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("BSTreeSeq: Remove N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));


//		delete BSTreeRandom;
//		delete BSTreeSeq;
	}
	else if (rbAVLTree->Checked)
	{
//		AVLTree<int> *AVLTreeRandom = new AVLTree<int>;
//		AVLTree<int> *AVLTreeSeq = new AVLTree<int>;
		AVLTree<int> AVLTreeRandom, AVLTreeSeq;


		TimeStart = ClockType::now();

		for (size_t i = 0; i < N; i++)
		{
			int v = Gen_ToAdd.GetNext();

			if ( !AVLTreeRandom.Add(v) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTree: Add random, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N; i++)
		{
			if ( !AVLTreeSeq.Add(i) )
			{
				ShowMessage(L"Такой элемент уже есть в дереве");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTreeSeq: Add sequentially, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !AVLTreeRandom.Find( Gen_ToFind.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTreeRandom: Find N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));



		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !AVLTreeSeq.Find( Gen_ToFind.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTreeSeq: Find N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));


		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !AVLTreeRandom.Remove(Gen_ToDel.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTreeRandom: Remove N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));



		TimeStart = ClockType::now();
		for (size_t i = 0; i < N/10; i++)
		{
			if ( !AVLTreeSeq.Remove(Gen_ToDel.GetNext()) )
			{
				ShowMessage(L"Такой элемент не найден");
				return;
			}
		}
		TimeEnd = ClockType::now();
		Time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count()) / 1.0e9;
		Memo->Lines->Add("AVLTreeSeq: Remove N/10 items, s = " + FloatToStrF(Time, ffFixed, 20, 6));



//		delete AVLTreeRandom;
//		delete AVLTreeSeq;
	}

}
//---------------------------------------------------------------------------

