
// SDIAppGSLDoc.h : interface of the CSDIAppGSLDoc class
//


#pragma once

class CMyTreeView;
class CSDIAppGSLView;


class CSDIAppGSLDoc : public CDocument
{
protected: // create from serialization only
	CSDIAppGSLDoc() noexcept;
	DECLARE_DYNCREATE(CSDIAppGSLDoc)

// Attributes
public:
	double X[10], Y[10];

	CMyTreeView* m_pTreeView;
	CSDIAppGSLView* m_pView;

	bool m_bMethod1, m_bMethod2, m_bMethod3;

// Operations
public:
	void ReadPoints();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSDIAppGSLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
