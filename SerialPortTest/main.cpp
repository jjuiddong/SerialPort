
#include <stdio.h>
#include <Windows.h>
#include "Serial.h"


int main(char argc, char *argv[])
{
	int port = 3, baudRate = 9600, dispType = 0;
	if (argc >= 2)
		port = atoi(argv[2]);
	if (argc >= 3)
		baudRate = atoi(argv[3]);
	if (argc >= 4)
		dispType = atoi(argv[4]);

	CSerial serial;

	if (!serial.Open(port, baudRate))
		return 0;

	int curT=0, oldT=0;
	while (1)
	{
		curT = GetTickCount();

		if (curT - oldT > 10)
		{
			char buffer[256];
			int nBytesRead = serial.ReadData(buffer, sizeof(buffer));

			if (nBytesRead > 0)
			{
				for (int i = 0; i < nBytesRead; ++i)
				{
					switch (dispType)
					{ 
					case 0: printf("%c", buffer[i]); break;
					case 1: printf("%d", buffer[i]); break;
					case 2: printf("%x", buffer[i]); break;
					}
				}
				printf("\n");
			}

			oldT = curT;
		}
	}

	serial.Close();

	return 1;
}
