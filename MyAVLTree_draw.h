/*
*  AVL-дерево с рисованием на объекте TImage в VCL (C++Builder)
*/


//---------------------------------------------------------------------------
#ifndef MyAVLTree_drawH
#define MyAVLTree_drawH
//---------------------------------------------------------------------------

#include "MyAVLTree.h"

#include <vcl.h>

#include <vector>
#include <utility>
#include <cmath>



template <typename T>
class AVLTreeDraw : public AVLTree<T>
{
protected:

	size_t Count = 0;

	std::vector<std::pair<TPoint, TPoint>> Lines;

	void Draw_inside(TCanvas *pCanvas, int w, int h, int _level, bool _isR,
				 TPoint LastPoint, int x, int y, AVLItemType<T> *pCur);

public:
	AVLTreeDraw() = default;
	AVLTreeDraw(const AVLTreeDraw &) = delete;
	AVLTreeDraw(AVLTreeDraw &&) = delete;
	AVLTreeDraw & operator=(const AVLTreeDraw &) = delete;
	AVLTreeDraw & operator=(AVLTreeDraw &&) = delete;

	void Draw(TImage *pImg, int w, int h, int _level, int x, int y);

    size_t GetCount() {return Count;}
};
//---------------------------------------------------------------------------

template<typename T>
void AVLTreeDraw<T>::Draw(TImage *pImg, int w, int h, int _level, int x, int y)
{
	pImg->Picture->Bitmap->Width = w;
	pImg->Picture->Bitmap->Height = h;

	TCanvas *pCanvas = pImg->Canvas;

	pCanvas->Brush->Style = bsSolid;
	pCanvas->Brush->Color = clWhite;
	pCanvas->Rectangle(0,0, w, h);
	pCanvas->Pen->Color = clRed;
	pCanvas->Pen->Width = 2;
	pCanvas->Font->Size = 12;

	Count = 0;

	Lines.clear();

	Draw_inside(pCanvas, w, h, _level, true, TPoint(0, 0), x, y+10,
						 static_cast<AVLItemType<T>*>(BSTree<T>::pRoot) );

//	Draw_inside(pCanvas, w, h, _level, true, TPoint(0, 0), x, y, pRoot);

	pCanvas->Pen->Color   = clBlack;
	//pCanvas->Pen->Width   = 2;
	for (auto &line : Lines)
	{
		pCanvas->MoveTo(line.first.x, line.first.y);
		pCanvas->LineTo(line.second.x, line.second.y);
	}

	pCanvas->TextOutW( 20, 20, String("Count = ") + String(Count) );

}
//---------------------------------------------------------------------------

template<typename T>
void AVLTreeDraw<T>::Draw_inside(TCanvas *pCanvas, int w, int h, int _level, bool _isR,
								TPoint LastPoint, int x, int y, AVLItemType<T> *pCur)
{
	constexpr int R = 18;
	constexpr int arrow = 70;
	const double kw = w / 290.0;
	const double sq2 = sqrt(2);

	constexpr double kk = 1.95;

	if (pCur != nullptr)
	{
		if (LastPoint != TPoint(0,0) )
			Lines.emplace_back(LastPoint, TPoint(_isR ? x-R/sq2 : x+R/sq2, y-R/sq2));

		LastPoint = TPoint(x,y);

		String text = String(pCur->Data);
		TSize size = pCanvas->TextExtent(text);

        Count++;

        pCanvas->Font->Style = TFontStyles();
		pCanvas->Font->Color = clBlack;
		pCanvas->Font->Size = 12;
		pCanvas->Ellipse(x - R, y  - R, x  + R, y + R);
		pCanvas->TextOutW( x - size.cx/2, y - size.cy/2, String(pCur->Data) );

		pCanvas->Font->Size = 10;
		pCanvas->Font->Style = TFontStyles() << fsBold;
		pCanvas->Font->Color = clGreen;
		pCanvas->TextOutW( x - size.cx/2 + 26, y - size.cy/2 - 5,
												"h= " + String(pCur->h) );
		pCanvas->Font->Color = clNavy;
		pCanvas->TextOutW( x - size.cx/2 + 26, y - size.cy/2 - 24,
								"b= " + String(AVLTree<T>::GetBalance(pCur)) );
		//pCanvas->Pen->Color = clBlack;

		if (pCur->pLeft)
		{

			Draw_inside(pCanvas, w, h, _level+1, false, TPoint(x-R/sq2, y+R/sq2),
						 x - kw*arrow/(pow(kk, _level)),
						 y + arrow, static_cast<AVLItemType<T>*>(pCur->pLeft));
		}

		if (pCur->pRight)
		{

			Draw_inside(pCanvas, w, h, _level+1, true, TPoint(x+R/sq2, y+R/sq2),
						x + kw*arrow/(pow(kk, _level)),
						y + arrow, static_cast<AVLItemType<T>*>(pCur->pRight));
		}

	}

}
//---------------------------------------------------------------------------





#endif
