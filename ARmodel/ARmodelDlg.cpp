
// ARmodelDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ARmodel.h"
#include "ARmodelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CARmodelDlg



CARmodelDlg::CARmodelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARMODEL_DIALOG, pParent)
	, f1(3)
	, f2(6)
	, f3(9)
	, fd(100)
	, N(1000)
	, N1(200)
	, N2(630)
	, futN1(0)
	, futN2(0)
	, E0(0.004)
	, L(30)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CARmodelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, f1);
	DDX_Text(pDX, IDC_EDIT2, f2);
	DDX_Text(pDX, IDC_EDIT4, f3);
	DDX_Text(pDX, IDC_EDIT3, fd);
	DDX_Text(pDX, IDC_EDIT5, N);
	DDX_Text(pDX, IDC_EDIT6, N1);
	DDX_Text(pDX, IDC_EDIT7, N2);
	DDX_Text(pDX, IDC_EDIT9, futN1);
	DDX_Text(pDX, IDC_EDIT8, futN2);
	DDX_Text(pDX, IDC_EDIT10, E0);
	//  DDX_Text(pDX, IDC_EDIT11, L);
	DDX_Text(pDX, IDC_EDIT11, L);
}

BEGIN_MESSAGE_MAP(CARmodelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CARmodelDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CARmodelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CARmodelDlg

BOOL CARmodelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	drvfunc.Create(GetDlgItem(IDC_FUNC)->GetSafeHwnd());
	drverror.Create(GetDlgItem(IDC_ERROR)->GetSafeHwnd());
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CARmodelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CARmodelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CARmodelDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CARmodelDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	signal s(f1, f2, f3, fd, N, N1, N2, L, E0);
	vector<double> y;
	s.CreateFunc(y);

	vector<double> errors;
	s.ErrorFuture(y, errors);

	drvfunc.DrawPoints(y, s, L"t", L"x", N / fd, 1 / fd);
	drverror.DrawPoints(errors, s, L"t", L"error", N / fd, 1 / fd);

	vector<double> sr;
	s.Sglagiv(L, errors, sr);
	drverror.DrawTwoSig(errors, sr, s, L"t", L"error", N / fd, 1 / fd);

	vector<int> new12;
	s.FindPorog(E0, sr, new12);

	futN1 = new12[0];
	futN2 = new12[1];
	UpdateData(false);
}
