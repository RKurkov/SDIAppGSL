// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDIAppGSL.h"
#include "MyTreeView.h"

#include "SDIAppGSLDoc.h"
#include "SDIAppGSLView.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hMethods = tree.InsertItem(L"Методы", -1, -1, NULL, TVI_FIRST);

	m_hMethod1 = tree.InsertItem(L"Кусочно-линейный", -1, -1, m_hMethods, TVI_FIRST);
	m_hMethod2 = tree.InsertItem(L"Многочлен Лагранжа", -1, -1, m_hMethods, TVI_FIRST);
	m_hMethod3 = tree.InsertItem(L"Кубический сплайн", -1, -1, m_hMethods, TVI_FIRST);

	tree.Expand(m_hMethods, TVE_EXPAND);
}


BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS
		                  | TVS_LINESATROOT | TVS_SHOWSELALWAYS
		                  | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeCtrl& tree = GetTreeCtrl();
	CTreeView::OnLButtonDown(nFlags, point);

	CRect rc;
	tree.GetItemRect(m_hMethods, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hMethods);

	tree.GetItemRect(m_hMethod1, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hMethod1);

	tree.GetItemRect(m_hMethod2, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hMethod2);

	tree.GetItemRect(m_hMethod3, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hMethod3);

	if (tree.GetSelectedItem() == m_hMethods)
	{
		bool check = tree.GetCheck(m_hMethods);
		tree.SetCheck(m_hMethod1, check);
		tree.SetCheck(m_hMethod2, check);
		tree.SetCheck(m_hMethod3, check);

	}
	else
		tree.SetCheck(m_hMethods, false);

	m_pDoc->m_bMethod1 = tree.GetCheck(m_hMethod1);
	m_pDoc->m_bMethod2 = tree.GetCheck(m_hMethod2);
	m_pDoc->m_bMethod3 = tree.GetCheck(m_hMethod3);

	m_pDoc->m_pView->Invalidate();

}
