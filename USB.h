// USB.h: interface for the USB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USB_H__801FD7DD_554C_4197_A9AF_6A4FC934E5FA__INCLUDED_)
#define AFX_USB_H__801FD7DD_554C_4197_A9AF_6A4FC934E5FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class USB  
{
public:
	void ClosePipes();
	void Initialice();
	void OpenPipes();
	USB();
	virtual ~USB();
	//void ReceivePacket(short* ReceiveData,DWORD* ReceiveLength);
	void ReceivePacket(/*PVOID*/BYTE *ReceiveData,PDWORD ReceiveLength);//Este es el original
	//void SendPacket(short* SendData, DWORD SendLength);
	void SendPacket(BYTE *SendData, DWORD SendLength);
	//void SendPacket(PVOID SendData, DWORD SendLength);ORIGINAL
	void SendPacket2(int PosServo);
	void SendPacket2(int Position1, int PosMotor);
	void SumaPIC(UINT sumando1, UINT sumando2);
	UINT ResultadoPIC();
	void ORPIC(UINT sumando1, UINT sumando2);
	void NOTPIC(UINT sumando1, UINT sumando2);
	void XORPIC(UINT sumando1, UINT sumando2);
	void ANDPIC(UINT sumando1, UINT sumando2);
};

#endif // !defined(AFX_USB_H__801FD7DD_554C_4197_A9AF_6A4FC934E5FA__INCLUDED_)
