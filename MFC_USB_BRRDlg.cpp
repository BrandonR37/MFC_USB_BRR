
// MFC_USB_BRRDlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "MFC_USB_BRR.h"
#include "MFC_USB_BRRDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
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


// Cuadro de diálogo de CMFCUSBBRRDlg



CMFCUSBBRRDlg::CMFCUSBBRRDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_MFC_USB_BRR_DIALOG, pParent)
	, m_pasos(0)
	, m_lectura(FALSE)
	, m_volt(0)
	, m_voltaje(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCUSBBRRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASOS, m_pasos);
	DDX_Check(pDX, IDC_CHECK_LECTURA, m_lectura);
	DDX_Text(pDX, IDC_STATIC_VOLT, m_volt);
	DDX_Text(pDX, IDC_STATIC_VOLTAJE, m_voltaje);
}

BEGIN_MESSAGE_MAP(CMFCUSBBRRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ON, &CMFCUSBBRRDlg::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CMFCUSBBRRDlg::OnBnClickedButtonOff)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCUSBBRRDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCUSBBRRDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK_LECTURA, &CMFCUSBBRRDlg::OnBnClickedCheckLectura)
END_MESSAGE_MAP()


// Controladores de mensajes de CMFCUSBBRRDlg

BOOL CMFCUSBBRRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
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

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CMFCUSBBRRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CMFCUSBBRRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMFCUSBBRRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCUSBBRRDlg::OnBnClickedButtonOn()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	BYTE dato[1];
	dato[0] = 1;
	USB_BRAN.SendPacket(dato, 1);

}


void CMFCUSBBRRDlg::OnBnClickedButtonOff()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	BYTE dato[1];
	dato[0] = 0;
	USB_BRAN.SendPacket(dato, 1);
}


void CMFCUSBBRRDlg::OnBnClickedButton2()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	BYTE dato_1[3];
	dato_1[0] = 0x01;
	dato_1[1] = 0x02;
	dato_1[2] = 0x04;
	for (int i = 0; i <= m_pasos; i++) {
		USB_BRAN.SendPacket(dato_1, 3);
		Sleep(1000);
	}
}


void CMFCUSBBRRDlg::OnBnClickedButton3()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	BYTE dato_1[3];
	dato_1[0] = 0x04;
	dato_1[1] = 0x02;
	dato_1[2] = 0x01;
	for (int i = 0; i <= m_pasos; i++) {
		USB_BRAN.SendPacket(dato_1, 3);
		Sleep(1000);
	}
}


void CMFCUSBBRRDlg::OnBnClickedCheckLectura()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(true);
	if (m_lectura) {
		m_volt = 0; //Aqui va el valor leido y enviado por el PIC
	}
	UpdateData(false);
}
