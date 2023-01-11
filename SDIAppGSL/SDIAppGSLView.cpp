
// SDIAppGSLView.cpp : implementation of the CSDIAppGSLView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SDIAppGSL.h"
#endif

#include "SDIAppGSLDoc.h"
#include "SDIAppGSLView.h"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIAppGSLView

IMPLEMENT_DYNCREATE(CSDIAppGSLView, CView)

BEGIN_MESSAGE_MAP(CSDIAppGSLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSDIAppGSLView construction/destruction

CSDIAppGSLView::CSDIAppGSLView() noexcept
{
	// TODO: add construction code here

}

CSDIAppGSLView::~CSDIAppGSLView()
{
}

void CSDIAppGSLView::PiecewiseLinearInterpolation()
{

}
void CSDIAppGSLView::LagrangePolynomial()
{

}
void CSDIAppGSLView::InterpolationByCubicSpline()
{

}

BOOL CSDIAppGSLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSDIAppGSLView drawing

void CSDIAppGSLView::OnDraw(CDC* pDC)
{
	CSDIAppGSLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(&rect);

	pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(rect.Width(), rect.Height() / 2);

	/*for (int i = 0; i < 10; i++)
	{
		CPen pen(PS_SOLID, 3, rgbBlack);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(pDoc->X[i] * rect.Width() / 10 + 2, (rect.Height() / 2) - (pDoc->Y[i] * rect.Height() / 10));
		pDC->AngleArc(pDoc->X[i] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[i] * rect.Height() / 10), 2, 0, 360);
	}*/

	pDC->MoveTo(pDoc->X[0] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[0] * rect.Height() / 10));

	if (pDoc->m_bMethod1)
	{
		/*CPen pen(PS_SOLID, 1, rgbRed);
		CPen* pOldPen = pDC->SelectObject(&pen);*/

		for (int i = 0; i < 10; i++)
		{
			pDC->LineTo(pDoc->X[i] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[i] * rect.Height() / 10));
		    //pDC->MoveTo(pDoc->X[i] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[i] * rect.Height() / 10));
		}

		pDC->MoveTo(pDoc->X[0] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[0] * rect.Height() / 10));
	}

	if (pDoc->m_bMethod2)
	{

		/*CPen pen(PS_SOLID, 1, rgbGreen);
		CPen* pOldPen = pDC->SelectObject(&pen);*/

		for (Xi = pDoc->X[0]; Xi < pDoc->X[9]; Xi += 0.01)
		{
			double res = 0;
			for (int i = 0; i < 10; ++i)
			{
				double l = 1;
				for (int j = 0; j < 10; ++j)
				{
					if (j != i)
					{
						l *= (Xi - pDoc->X[j]) / (pDoc->X[i] - pDoc->X[j]);
					}
				}
				res += pDoc->Y[i] * l;
			}
			pDC->LineTo(Xi * rect.Width() / 10, (rect.Height() / 2) - (res * rect.Height() / 10));
		}

		pDC->MoveTo(pDoc->X[0] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[0] * rect.Height() / 10));
	}

	if (pDoc->m_bMethod3)
	{
		/*CPen pen(PS_SOLID, 1, rgbBlue);
		CPen* pOldPen = pDC->SelectObject(&pen);*/

		gsl_interp_accel* acc = gsl_interp_accel_alloc();
		gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, 10);
		gsl_spline_init(spline, pDoc->X, pDoc->Y, 10);
		for (Xi = pDoc->X[0]; Xi < pDoc->X[9]; Xi += 0.01)
		{
			Yi = gsl_spline_eval(spline, Xi, acc);
			pDC->LineTo(Xi * rect.Width() / 10, (rect.Height() / 2) - (Yi * rect.Height() / 10));
			//pDC->MoveTo(Xi * rect.Width() / 10, (rect.Height() / 2) - (Yi * rect.Height() / 10));
		}
		gsl_spline_free(spline);
		gsl_interp_accel_free(acc);

		pDC->MoveTo(pDoc->X[0] * rect.Width() / 10, (rect.Height() / 2) - (pDoc->Y[0] * rect.Height() / 10));
	}
}


// CSDIAppGSLView printing

BOOL CSDIAppGSLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDIAppGSLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDIAppGSLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSDIAppGSLView diagnostics

#ifdef _DEBUG
void CSDIAppGSLView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIAppGSLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIAppGSLDoc* CSDIAppGSLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIAppGSLDoc)));
	return (CSDIAppGSLDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIAppGSLView message handlers
