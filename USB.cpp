// USB.cpp: implementation of the USB class.
//
//////////////////////////////////////////////////////////////////////
//#include "StdAfx.h"
#include "pch.h"
#include "USB.h"
#include "usb2550.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//***********************************************************************************************

//#pragma argsused

// Global Vars
PCHAR vid_pid = "vid_04d8&pid_0011";
PCHAR out_pipe= "\\MCHP_EP1";
PCHAR in_pipe= "\\MCHP_EP1";
HANDLE myOutPipe;
HANDLE myInPipe;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USB::USB()
{

}

USB::~USB()
{

}

void USB::OpenPipes()
{
DWORD selection = 0;
	
	myOutPipe = MPUSBOpen(selection,vid_pid,out_pipe,0,0);
	myInPipe = MPUSBOpen(selection,vid_pid,in_pipe,1,0);
}

void USB::Initialice()
{
	myOutPipe = myInPipe = NULL;
}

void USB::ClosePipes()
{
	MPUSBClose(myOutPipe);
	MPUSBClose(myInPipe);
}

/*void USB::SendPacket(PVOID SendData, DWORD SendLength)ORIGINAL
{
	DWORD SendDelay = 1000;
	//DWORD SendDelay = 10;
	PDWORD SentDataLength = 0;

	USB::OpenPipes();
	MPUSBWrite(myOutPipe,SendData,SendLength,SentDataLength,SendDelay);
	USB::ClosePipes();
}*/

void USB::SendPacket(BYTE *SendData, DWORD SendLength)
{
	DWORD SendDelay = 1000;
	//DWORD SendDelay = 10;
	DWORD SentDataLength;

	USB::OpenPipes();
	MPUSBWrite(myOutPipe,(void*)SendData,SendLength,&SentDataLength,SendDelay);
	USB::ClosePipes();
}

/*******************************************************************************************
Esta función recibe del PIC los datos "RecieveData" y la longitud de la cadena "RecieveLenght"
Los otros datos de MPUSBRead los imponemos nosotros, dichos datos del PIC se reciben con la función
usb_put_packet(endpoint,*ptr,len,toggle)
********************************************************************************************/

void USB::ReceivePacket(BYTE *ReceiveData, PDWORD ReceiveLength)
{
	DWORD ReceiveDelay = 1000;
	DWORD ExpectedReceiveLength = *ReceiveLength;

	USB::OpenPipes();
	MPUSBRead(myInPipe, (void*)ReceiveData, ExpectedReceiveLength, ReceiveLength, ReceiveDelay);
	
	USB::ClosePipes();
}

/********************************************************************************************

Función ampliada que usa SendPacket(PVOID, DWORD) la cual es lo mismo, sólo que en vez de
decirle manualmente lo que queremos enviar, se lo pasamos por la posición del joystick.

*********************************************************************************************/
void USB::SendPacket2(int Position1)
{
	BYTE send_buf[1];
	int AbsPosition1 = abs(Position1);


/********************************************************************************************
							CONTROL DEL SERVO POR VELOCIDAD
										By JVidal
********************************************************************************************/
/*	//Giramos hacia la izquierda
	if(Position1<0)
	{
		send_buf[0] = 0x00;
		for (i=0;i<AbsPosition1;i++)
		{
			SendPacket(send_buf,1);	
		}		
	}

	//Giramos hacia la derecha
	if(Position1>0)
	{
		send_buf[0] = 0x01;
		for (i=0;i<AbsPosition1;i++)
		{
			SendPacket(send_buf,1);	
		}		
	}

	USB::ClosePipes();
*/

/********************************************************************************************
							CONTROL DEL SERVO POR POSICIÓN
										By JVidal
********************************************************************************************/
	
	send_buf[0] = Position1;	//Servo
	SendPacket(send_buf,1);


	USB::ClosePipes();
	
}

void USB::SendPacket2(int Position1, int PosMotor)
{
	BYTE send_buf[2];


/********************************************************************************************
							CONTROL DEL SERVO POR VELOCIDAD
										By JVidal
********************************************************************************************/
/*	//Giramos hacia la izquierda
	if(Position1<0)
	{
		send_buf[0] = 0x00;
		for (i=0;i<AbsPosition1;i++)
		{
			SendPacket(send_buf,1);	
		}		
	}

	//Giramos hacia la derecha
	if(Position1>0)
	{
		send_buf[0] = 0x01;
		for (i=0;i<AbsPosition1;i++)
		{
			SendPacket(send_buf,1);	
		}		
	}

	USB::ClosePipes();
*/

/********************************************************************************************
							CONTROL DEL SERVO POR POSICIÓN
										By JVidal
********************************************************************************************/
	
	send_buf[0] = Position1;	//Servo
	send_buf[1] = PosMotor;		//entre 0 y 1023
	SendPacket(send_buf,2);


	USB::ClosePipes();
	
}

void USB::SumaPIC(UINT sumando1, UINT sumando2)
        {
            BYTE* send_buf = (BYTE*)malloc (3);
            
            send_buf[0] = 0x00;             // Código de Entrada a Modo_Suma
            send_buf[1] = (byte)sumando1;
            send_buf[2] = (byte)sumando2;
            SendPacket(send_buf, 3);
        }

UINT USB::ResultadoPIC()
        {
            UINT result = 0;
            byte* receive_buf = (BYTE*)malloc(1);

            DWORD RecvLength = 1;

            ReceivePacket(receive_buf, &RecvLength);
            result = receive_buf[0];

            return result;
        }

void USB::XORPIC(UINT sumando1, UINT sumando2)
        {
            BYTE* send_buf = (BYTE*)malloc (3);
            
            send_buf[0] = 2;             // Código de Entrada a Modo_Suma
            send_buf[1] = (byte)sumando1;
            send_buf[2] = (byte)sumando2;
            SendPacket(send_buf, 3);
        }


void USB::NOTPIC(UINT sumando1, UINT sumando2)
        {
            BYTE* send_buf = (BYTE*)malloc (3);
            
            send_buf[0] = 3;             // Código de Entrada a Modo_Suma
            send_buf[1] = (byte)sumando1;
            send_buf[2] = (byte)sumando2;
            SendPacket(send_buf, 3);
        }

void USB::ORPIC(UINT sumando1, UINT sumando2)
        {
            BYTE* send_buf = (BYTE*)malloc (3);
            
            send_buf[0] = 4;             // Código de Entrada a Modo_Suma
            send_buf[1] = (byte)sumando1;
            send_buf[2] = (byte)sumando2;
            SendPacket(send_buf, 3);
        }

void USB::ANDPIC(UINT sumando1, UINT sumando2)
        {
            BYTE* send_buf = (BYTE*)malloc (3);
            
            send_buf[0] = 5;             // Código de Entrada a Modo_Suma
            send_buf[1] = (byte)sumando1;
            send_buf[2] = (byte)sumando2;
            SendPacket(send_buf, 3);
        }


