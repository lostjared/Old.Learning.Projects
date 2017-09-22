// message que
// written by jared bruni
// www.lostsidedead.com
// example of message que structure
// FIFO 
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#define QUE_SIZE 100


struct MyMessage
{
	char name[100];
	// input other variable types for message
};


class MsgQue
{
	MyMessage que[QUE_SIZE];
	int que_count;
public:

	inline MsgQue()
	{
		que_count = 0;
		Clear();
	}
	
	inline void AddMessage(char* data)
	{
		strcpy(que[que_count].name,data);
		que_count++;
	}

	inline int GetLength()
	{
		return que_count;
	}

	inline void Clear()
	{
		for(int i = 0; i < GetLength(); i++)
		{
			strcpy(que[que_count].name,"");
		}
		que_count = 0;
	}

	// GetNextMessage from que
	inline bool GetNextMessage(char* buff)
	{
		if(que_count == 0)
		{
			return false;
		}

		MyMessage nque[QUE_SIZE];

		for(int i = 0; i < que_count; i++)
		{
			strcpy(nque[i].name,que[i].name);
		}

		strcpy(buff,que[0].name);

		int cx = 0;

		for(i = 1; i < que_count; i++)
		{
			strcpy(que[cx].name,nque[i].name);
			cx++;
		}

		que_count = cx;


		return true;

	}

};