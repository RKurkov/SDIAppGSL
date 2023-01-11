
// SDIAppGSLDoc.cpp : implementation of the CSDIAppGSLDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SDIAppGSL.h"
#endif

#include "SDIAppGSLDoc.h"

#include <propkey.h>

#define FNAME "D:\\source2\\repos2\\SDIAppGSL\\PointsXY.txt"
#include "SDIAppGSLView.h"
#include "MainFrm.h"
#include "MyTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDIAppGSLDoc

IMPLEMENT_DYNCREATE(CSDIAppGSLDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIAppGSLDoc, CDocument)
END_MESSAGE_MAP()


// CSDIAppGSLDoc construction/destruction

CSDIAppGSLDoc::CSDIAppGSLDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSDIAppGSLDoc::~CSDIAppGSLDoc()
{
}

void CSDIAppGSLDoc::ReadPoints()
{
	FILE* myfile;

	if (fopen_s(&myfile, FNAME, "rt"))
	{
		MessageBox(NULL, L"ERROR READ FILE", L"INFO", MB_OK);
		return;
	}
	
	int n = 0;
	float point[20];
	int k = 0;

	while (!feof(myfile))
	{
		fscanf_s(myfile, "%f", &point[n]);
		n++;
	}

	fclose(myfile);

	for (int i = 0; i < 10; i++)
	{
		X[i] = (double)point[k];
		k += 2;
	}

	k = 1;

	for (int i = 0; i < 10; i++)
	{
		Y[i] = (double)point[k];
		k += 2;
	}
}

BOOL CSDIAppGSLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	ReadPoints();

	CWnd* MainWnd = AfxGetMainWnd();

	if (MainWnd)
	{

		m_pTreeView = (CMyTreeView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 0);
		m_pView = (CSDIAppGSLView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 1);

		m_pTreeView->m_pDoc = this;

	}

	m_pTreeView->FillTree();

	m_bMethod1 = m_bMethod2 = m_bMethod3 = false;

	return TRUE;
}




// CSDIAppGSLDoc serialization

void CSDIAppGSLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSDIAppGSLDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSDIAppGSLDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSDIAppGSLDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSDIAppGSLDoc diagnostics

#ifdef _DEBUG
void CSDIAppGSLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIAppGSLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSDIAppGSLDoc commands
