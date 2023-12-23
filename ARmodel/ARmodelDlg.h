
// ARmodelDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Analys.h"

// Диалоговое окно CARmodelDlg
class CARmodelDlg : public CDialogEx
{
// Создание
public:
	CARmodelDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARMODEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double f1;
	double f2;
	double f3;
	double fd;
	int N;
	int N1;
	int N2;
	int futN1;
	int futN2;
	Drawer drvfunc;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	Drawer drverror;
	double E0;
//	double L;
//	double stepwnd;
	int L;
};
