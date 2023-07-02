
// MFC_USB_BRRDlg.h: archivo de encabezado
//

#pragma once
#include "USB.h"
#include "usb2550.h"




// Cuadro de diálogo de CMFCUSBBRRDlg
class CMFCUSBBRRDlg : public CDialogEx
{
// Construcción
public:
	CMFCUSBBRRDlg(CWnd* pParent = nullptr);	// Constructor estándar
	USB USB_BRAN;

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_USB_BRR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	int m_pasos;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	BOOL m_lectura;
	afx_msg void OnBnClickedCheckLectura();
	int m_volt;
	BYTE m_voltaje;
};
