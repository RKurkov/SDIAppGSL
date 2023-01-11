
// SDIAppGSLView.h : interface of the CSDIAppGSLView class
//

#pragma once

class CSDIAppGSLDoc;

class CSDIAppGSLView : public CView
{
protected: // create from serialization only
	CSDIAppGSLView() noexcept;
	DECLARE_DYNCREATE(CSDIAppGSLView)

// Attributes
public:
	CSDIAppGSLDoc* GetDocument() const;

	double Xi, Yi, X0, Y0;

	COLORREF rgbRed = 0x000000FF;
	COLORREF rgbGreen = 0x0000FF00;
	COLORREF rgbBlue = 0x00FF0000;
	COLORREF rgbBlack = 0x00000000;
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbColors;

// Operations
public:
	void PiecewiseLinearInterpolation();
	void LagrangePolynomial();
	void InterpolationByCubicSpline();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSDIAppGSLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SDIAppGSLView.cpp
inline CSDIAppGSLDoc* CSDIAppGSLView::GetDocument() const
   { return reinterpret_cast<CSDIAppGSLDoc*>(m_pDocument); }
#endif

