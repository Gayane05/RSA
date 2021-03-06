
// RSADlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRSADlg dialog



CRSADlg::CRSADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSA_DIALOG, pParent)
	, p(0)
	, Q(0)
	, n(0)
	, fi(0)
	, e(0)
	, d(0)
	, sourceData(0)
	, encryptedData(0)
	, decryptedData(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, p);
	DDX_Text(pDX, IDC_EDIT3, Q);
	DDX_Text(pDX, IDC_EDIT4, n);
	DDX_Text(pDX, IDC_EDIT5, fi);
	DDX_Text(pDX, IDC_EDIT6, e);
	DDX_Text(pDX, IDC_EDIT7, d);
	DDX_Text(pDX, IDC_EDIT8, sourceData);
	DDX_Text(pDX, IDC_EDIT9, encryptedData);
	DDX_Text(pDX, IDC_EDIT10, decryptedData);
}

BEGIN_MESSAGE_MAP(CRSADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT5, &CRSADlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON1, &CRSADlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRSADlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRSADlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRSADlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CRSADlg message handlers

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRSADlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRSADlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//////////////////////////////////////////////////////////////////////


int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int countOpenExp(int FI) {
	// Count open exponent - e
	int i = 0, e;
	for (i = 2; i < FI; i++) {
		if (gcd(FI, i) == 1) break;
	}
	e = i;
	return e;
}

int countPrivate(int P, int Q, int E) {
	// Count and print private exponent
	bool check = true;
	int D = 0, clExp = 0, D_ = 0;
	int i = 1, k = 0, l;
	int fi = (P - 1)*(Q - 1);

		while (check) {
			k = fi * i; // 175-i bazmapatik
			l = (k + 1) % fi; // mshtakan 1 mnacord@
			if (l == 1) {
				D_ = (k + 1) % E;
				if (D_ == 0) {
					D = (k + 1) / E;
					check = false;
				}
			}
			i++;
		}
	clExp = D;
	return clExp;
}

void CRSADlg::OnBnClickedButton1()
{
	// TODO: Count n and fi
	UpdateData(true);

	n = (p * Q);
	fi = ((p - 1)*(Q - 1));

	UpdateData(false);
}

void CRSADlg::OnBnClickedButton2()
{
	// TODO: Count e and d
	UpdateData(true);

	int k = 0;

	e = countOpenExp(fi);
	d = countPrivate(p, Q, e);

	UpdateData(false);
}

void CRSADlg::OnBnClickedButton3()
{
	// TODO: Encrypt Source Data
	UpdateData(true);

	int k = sourceData;
		
	for (int i = 1; i < e; i++) {
		k = sourceData * k % n;
	}
	encryptedData = k;
	UpdateData(false);
}

void CRSADlg::OnBnClickedButton4()
{
	// TODO: Decrypt Source Data
	UpdateData(true);

	int k = encryptedData;

	for (int i = 1; i < d; i++) {
		k = encryptedData * k % n;
	}
	decryptedData = k;
	UpdateData(false);
}
