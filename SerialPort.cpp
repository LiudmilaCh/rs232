#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

//#using <System.dll>

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace std;

//Значения байтов????
#define BYTE1 0x00;
#define BYTE2 0x00;
#define BYTE3 0x00;


using namespace System;

int Readed=0;

int sim;

int 
	Read1,
	Read2,
	Read3,
	Read4,
	Read5 = 0;

int 
	RizByte1,
	RizByte2, 
	RizByte3,
	RizByte4, 
	RizByte5 = 0;

int main(array<System::String ^> ^args)
{
	SerialPort^ serialPort = gcnew SerialPort(L"COM1", 57600, Parity::Even, 8, StopBits::One); //МК работает с портом COM1

		serialPort->Open();

    Console::WriteLine(L"Проверка связи по RS232");
    Console::WriteLine(L"Для перезагрузки МК нажмите F2");

	while (	kbhit()) getch();

//===========================================================
//  Формирование массивов для управления микроконтроллером
//===========================================================
//-------------Массивы Выдача (СБ->ОУ)--------------------
	array <Byte>^_MKVersion = {0xA1, 0xFF, 0xA0}; //mk
	array <Byte>^_Reset     = {0x51, 0xFF, 0x50}; //reset
	array <Byte>^_Riz       = {0x41, 0x5F, 0xA0}; //mk

//-------------Массивы Прием (ОУ->СБ)--------------------
	array <Byte>^MKVersion = {0x00, 0x00, 0x00, 0x00, 0x00}; 
	array <Byte>^Reset     = {0x00, 0x00, 0x00, 0x00, 0x00}; 
	array <Byte>^Riz       = {0x00, 0x00, 0x00, 0x00, 0x00}; 


//===========================================================
//				Управление микроконтроллером
//===========================================================
//-------------Запись--------------------
	serialPort->Write(_MKVersion, 0, 3);	
	serialPort->Write(_Riz,       0, 3);

	Sleep(1000);//при измерении Rиз ст дается задержка на ответ

	sim = getch();
	switch(sim)
	{
		case 60:
			serialPort->Write(_Reset, 0, 3);
		break;
	}

	//serialPort->Write(MK, 0, 8);
	//serialPort->WriteLine("1");	//
	//cout<<"Written = ";
	//cout<<

//-------------Чтение информации из МК--------------------
	//serialPort->ReadByte(); //считывает один байт из буфера

	serialPort->Read(MKVersion, 0, 5);

	Read1= int(MKVersion[0]);
	Read2= int(MKVersion[1]);
	Read3= int(MKVersion[2]);
	Read4= int(MKVersion[3]); 
	Read5= int(MKVersion[4]);

	//serialPort->ReadByte();
	//serialPort->ReadByte();
	//Readed = int (serialPort->ReadByte());
	//cout<<"Read Byte1 = "<<Readed;
	//cout<<"Read Byte2 = "<<Readed;
	//cout<<"Read Byte3 = "<<Readed;

	cout<<"Версия прошивки МК:"<<"\n";
	cout<<"Byte1 = "
		<<Read1<<"\n"
		<<"Byte2 = "
		<<Read2<<"\n"
		<<"Byte3 = "
		<<Read3<<"\n"
		<<"Byte4 = "
		<<Read4<<"\n"
		<<"Byte5 = "
		<<Read5;

	RizByte1 = int(Riz[0]);
	RizByte2 = int(Riz[1]); 
	RizByte3 = int(Riz[2]);
	RizByte4 = int(Riz[3]); 
	RizByte5 = int(Riz[4]);
	
	cout<<"Измерение Rиз_ст = "<<"\n";
	cout<<"Byte1 = "
		<<RizByte1<<"\n"
		<<"Byte2 = "
		<<RizByte2<<"\n"
		<<"Byte3 = "
		<<RizByte3<<"\n"
		<<"Byte4 = "
		<<RizByte4<<"\n"
		<<"Byte5 = "
		<<RizByte5;

	serialPort->Close();

	getch();


    return 0;
}
