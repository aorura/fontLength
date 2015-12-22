
// GPFontWidthDlg.h : header file
//
#include "LGFontManager.h"
#include "LGFontFreeType.h"

#pragma once
#include "afxwin.h"


// CGPFontWidthDlg dialog
class CGPFontWidthDlg : public CDialog
{
// Construction
public:
	CGPFontWidthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GPFONTWIDTH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CLGFontManager		m_pSK;
	lgBOOL				m_bSK;

	lgBOOL				m_bCRLF;
	lgINT				m_nModel;
	lgINT				m_nType;
	lgString			m_strString;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox m_cbModel;
	CComboBox m_cbFontType;
	CEdit m_edInputString;
	CStatic m_stFontWidth;
	afx_msg void OnBnClickedAnalysis();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnEnChangeEdit1();
	CButton m_bCrlf;
	afx_msg void OnBnClickedCheck1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
