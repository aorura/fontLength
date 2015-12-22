
// GPFontWidthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GPFontWidth.h"
#include "GPFontWidthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGPFontWidthDlg dialog




CGPFontWidthDlg::CGPFontWidthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPFontWidthDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPFontWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_cbModel);
	DDX_Control(pDX, IDC_COMBO4, m_cbFontType);
	DDX_Control(pDX, IDC_EDIT1, m_edInputString);
	DDX_Control(pDX, IDC_FONTWIDTH, m_stFontWidth);
	DDX_Control(pDX, IDC_CHECK1, m_bCrlf);
}

BEGIN_MESSAGE_MAP(CGPFontWidthDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO3, &CGPFontWidthDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_ANALYSIS, &CGPFontWidthDlg::OnBnClickedAnalysis)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CGPFontWidthDlg::OnCbnSelchangeCombo4)
	ON_EN_CHANGE(IDC_EDIT1, &CGPFontWidthDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CHECK1, &CGPFontWidthDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CGPFontWidthDlg message handlers

BOOL CGPFontWidthDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_bSK = m_pSK.Init("./font.bin");

	if ( m_bSK == lgTRUE  )
	{
		m_cbModel.AddString(L"SK");
		m_cbModel.SetCurSel(0);
		OnCbnSelchangeCombo3();
	}
	else
	{
		m_cbModel.AddString(L"Font Reader Fail!");
	}

	m_bCRLF = lgTRUE;
	m_bCrlf.SetCheck(m_bCRLF);
	// TODO: Add extra initialization here


	wchar_t strLen[128] = {0x00, };
	wsprintf(strLen, L"Font Width : %d pixel", 0);
	m_stFontWidth.SetWindowTextW(strLen);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGPFontWidthDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGPFontWidthDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGPFontWidthDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGPFontWidthDlg::OnCbnSelchangeCombo3()
{
	if ( m_bSK == lgFALSE )
	{
		MessageBox(L"Font Loaded Fail !");
		return;
	}

	int nIndex = m_cbModel.GetCurSel();

	m_cbFontType.Clear();

	if ( nIndex == 0 )
	{
		for(int i=1; i<= CLGFontFreeType::getFontCount(); i++)
		{
			wchar_t key[20] = {0x00, };
			wsprintf(key, L"Type %d", i);
			m_cbFontType.AddString(key);
		}
	}

	m_nModel = nIndex;
}

wchar_t *replaceAll(wchar_t *s, const wchar_t *olds, const wchar_t *news) 
{
	wchar_t *result, *sr;
	size_t i, count = 0;
	size_t oldlen = wcslen(olds); if (oldlen < 1) return s;
	size_t newlen = wcslen(news);

	if (newlen != oldlen) 
	{
		for (i = 0; s[i] != '\0';) 
		{
			if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
			else i++;
		}
	} else i = wcslen(s);


	result = (wchar_t *) malloc(i + 1 + count * (newlen - oldlen));
	if (result == NULL) return NULL;


	sr = result;
	while (*s) 
	{
		if (memcmp(s, olds, oldlen) == 0) 
		{
			wmemcpy(sr, news, newlen);
			sr += newlen;
			s  += oldlen;
		} else *sr++ = *s++;
	}
	*sr = '\0';

	return result;
}

void CGPFontWidthDlg::OnBnClickedAnalysis()
{
	if ( m_bSK == lgFALSE )
	{
		MessageBox(L"Font Loaded Fail !");
		return;
	}

	uint32_t len = 0;

	lgString txt = m_strString;

	if ( m_bCRLF == lgTRUE )
	{
		wchar_t strText[4096];
		wsprintf(strText, L"%s", m_strString.c_str());
		txt = replaceAll(strText, L"\n", L"");

		wsprintf(strText, L"%s", txt.c_str());
		txt = replaceAll(strText, L"\r", L"");
	}

	if ( m_nModel == 0 )
	{
		m_pSK.setFontSizeLanguage(m_nType+1);
		len = m_pSK.getWidth(txt.c_str(), 0);
	}

	wchar_t strLen[128] = {0x00, };
	wsprintf(strLen, L"Font Width : %d pixel", len);

	m_stFontWidth.SetWindowTextW(strLen);

}

void CGPFontWidthDlg::OnCbnSelchangeCombo4()
{
	if ( m_bSK == lgFALSE )
	{
		MessageBox(L"Font Loaded Fail !");
		return;
	}

	m_nType = m_cbFontType.GetCurSel();
}

void CGPFontWidthDlg::OnEnChangeEdit1()
{
	if ( m_bSK == lgFALSE )
	{
		MessageBox(L"Font Loaded Fail !");
		return;
	}

	wchar_t	txt[4096] = {0x00, };
	m_edInputString.GetWindowTextW(txt, 4096);

	m_strString = txt;
}

void CGPFontWidthDlg::OnBnClickedCheck1()
{
	m_bCRLF = m_bCrlf.GetCheck();
}

BOOL CGPFontWidthDlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* pwndCtrl = GetFocus();
	CWnd* pwndCtrlNext = pwndCtrl;

	if ( pwndCtrlNext != NULL )
	{
		int ctrl_ID = pwndCtrl->GetDlgCtrlID();

		if ( ctrl_ID != IDOK ) return CDialog::PreTranslateMessage(pMsg);
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			{
				return TRUE;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
