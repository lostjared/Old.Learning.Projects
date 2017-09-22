/*
Copyright Lee Trager

Here's the legal stuff...

License:

Removing this notice is a violation of the licence granted to you to use it.
You may freely distribute this code as long as it is not modified in any way
and as long as long as this licene agreement is not removed.
You may use this code with out payment of any kind to the author, however you
may not make any changes to the code.

The sample Templates, HTML, Macros, commands and/or code are furnished by 
the author as examples to provide an illustration.  These examples have not 
been thoroughly tested under all conditions.  The author, therefore, cannot 
guarantee reliability, serviceability or function of this program. 

All programs compiled or un-compiled contained herein are provided to you 
"AS IS". 

The sample Templates, HTML, Macros commands and/or code may include the 
names of individuals, companies, brands and products in order to illustrate 
them as completely as possible.  All of these are names are fictitious and 
any similarity to the names and addresses used by actual persons or 
business enterprises is entirely coincidental. 

All sample Templates, HTML, Macros commands and/or code contained herein 
are copyrighted and those copyrights are owned by Lee Trager. 

Licensed Materials - Property of Lee Trager  


NuclearM3U
part of the NuclearMedia SDK
by Lee Trager
E-Mail/MSN: L_Trager@hotmail.com
AIM: nukem996
www.LostSideDead.com

This is the M3U file reader class. this will read and write winamp M3U files.

this uses no api at all. any addons that need api are in the NuclearMediaSDK class.
since this uses no api M3U.h should be able to be run on any OS. but ive only tested it on 
windows. the file path finder is only set up for the windows directory structor im not sure if it
will work with other OSs it probly just needs a lil tweeking it should also be able to run on any
compiler but ive only tested it on VC++

if you put in an invalid number it will do nothing or return "Error!!!"

in memory each file is stored like this
|Number|Title|Path|Time|Played|

|0|KoRn|C:\My Music\KoRn\KoRn.mp3|10:49|false|
|1|Rammstein|C:\My Music\Rammstein.mp3|4:33|false|

M3U list code
to find the path you need to put the path of the m3u file and the path of the music file together

#EXTM3U //means this is a winamp M3U list file
#EXTINF:Time,Title  ]\Number according to where in the list it is
Path				]/

C:\My Music\Music.m3u
#EXTM3U
#EXTINF:601,KoRn
KoRn\Life is Peachy\KoRn.mp3
#EXTINF:273,Rammstein
Rammstein.mp3

Number - what is the number of the file in the list
*/

//only includes header once
#pragma once

#include <FSTREAM.h> //for file opening
#include <stdio.h> //to put string together
#include<stdlib.h>

#ifdef MAX
	#undef MAX
	#pragma message(" ")
	#pragma message("You cannt use MAX because NuclearMedia needs it. It will be undefined.")
	#pragma message(" ") 
#endif

#ifdef START
	#undef START 
	#pragma message(" ")
	#pragma message("You cannt use START because M3U.h needs it. It will be undefined.")
	#pragma message(" ")
#endif

#define MAX		150
#define START	0 //this is the number the list will start at

#ifndef NULL
	#define NULL	0
#endif

class NuclearM3U
{
private:

	struct M3UINFO
	{
		int Number;
		char Title[MAX];
		char Path[MAX];
		char Time[MAX];
		bool Played;
		M3UINFO* next;
	};

	bool loaded;
	FILE* file;
	M3UINFO* Head;
	char err[MAX];

	//findstr from MasterString coded by Jared
	//find a char in the 1st place its seen
	int findstr(char* body,char* search)
	{
		int len = strlen(body);
		int len2 = strlen(search); // search len

		for(int i = 0; i < len; i++)
		{
			if(body[i] == search[0])
			{
				bool ichk = true;

				for(int z = 0; z < len2; z++)
				{
					if(body[i+z] == search[z])
					{
					}
					else
					{
						ichk = false;
					}
				}

				if(ichk == true)
				{
					return i;
				}
			}
		}

		return -1; // failure
	}

	//FileLen from MasterString by Jared
	// return the length of this file
	int FileLen(const char *filename)
	{
		FILE* sfile;
		int count = 0;
		
		sfile = fopen(filename,"rb+");
		
		if( sfile == NULL )
		{
			return -1;
		}
		
		while (1)
		{
			char c;
			c = fgetc( sfile );
			if(c == EOF)
			{
				break;
			}
			else
			{
				count++;
			}
		}
		
		return count;
	}

	//bak 2 mi code :)

	/*If 1 then items are the same if returns 0 then there not*/
	int Cmp(char* item1, char* item2, int array)
	{
		int a, b;

		a = (char)item1[array];
		b = (char)item2[array];

		if(a == b)
		{
			return 1;
		}else{
			return 0;
		}
	}

	/*cmp 2 diffrent areas of 2 diffrent chars if 1 items r same 0 there not*/
	int Cmp2(char* item1, char* item2, int array1, int array2)
	{
		int a = (char)item1[array1];
		int b = (char)item2[array2];

		if(a == b)
		{
			return 1;
		}else{
			return 0;
		}
	}

	//1 means it found char in item 0 means it cannt find it
	int Find(char* item, char* find)
	{
		int fnd = 0;
		int a, b;
		while(item[fnd] != NULL)
		{
			a = (char)item[fnd];
			b = (char)find[0];
			if(a == b)
			{
				return 1;
			}
			fnd++;
		}
		return 0;
	}

	//finds the position(starting at end of char) of a char in a char and tells u were it is
	int FindLast(char* item, char* find)
	{
		int fnd = SizeOf(item);
		int a;
		int b = find[0];

		while(item[fnd] != NULL)
		{
			a = (char)item[fnd];
			if(a == b)
			{
				return fnd;
			}
			fnd--;
		}

		return -1;
	}

	int SizeOf(char* item)
	{
		int Num = 0;
		while(item[Num] != NULL)
		{
			Num++;
		}
		return Num - 1;
	}

	void FindLCpy(char* item, char find, char* Return)
	{
		int fnd = SizeOf(item);
		int a, b, fnd2;
		b = (char)find;
		while(item[fnd] != NULL)
		{
			a = (char)item[fnd];
			if(a == b)
			{
				fnd2 = fnd;
				CpyDown(item, fnd, Return);
				Return[fnd] = 0;
				return;
			}
			fnd--;
		}
	}

	void FindRCpy(char* item, char find, char* Return)
	{
		int fnd = SizeOf(item);
		int a, b, fnd2;
		b = (char)find;
		while(item[fnd] != NULL)
		{
			a = (char)item[fnd];
			if(a == b)
			{
				fnd2 = fnd;
				CpyUp(item, fnd, Return);
				return;
			}
			fnd--;
		}
	}

	void CpyDown(char* item, int From, char* Return)
	{
		Return[From] = 0;
		while(From != -1)
		{
			Return[From] = item[From];
			From--;
		}
	}

	void CpyUp(char* item, int From, char* Return)
	{
		int b = 0;
		for(int a=(From + 1); a!=(SizeOf(item) + 1);a++)
		{
			Return[b] = item[a];
			Return[b + 1] = 0;
			b++;
		}
	}

	void Clear(char* item)
	{
		for(int NUM=0;item[NUM]!=NULL;NUM++)
		{
			item[NUM] = 0;
		}
	}

	/*
	  Path1 - Part of a Path
	  Path2 - Path that you want to build Part1 w/
	  Return - The finished path
	*/
	void FindPath(char* Path1, char* Path2, char* Return)
	{
		//if the drive = same then the hole path is there in Path1
		int Drive = 0;

		for(int a = 0; a < 2; a++){
			
			if(Cmp(Path1, Path2, a) == 1)
			{
				Drive++;
			}
			if(Drive == 2)
			{
				strcpy(Return, Path1);
				return;
			}
		}

		char Root[MAX];
		char slash;
		slash = 92;

		FindLCpy(Path2, slash, Root);

		sprintf(Return, "%s\\%s", Root, Path1);
	}

	/*
	Path1 = File path from m3u list
	Path2 = File path of m3u file
	*/
	void SFindPath(char* Path1, char* Path2, char* Return)
	{
		int Place = 0;
		int Stop;
		
		if(SizeOf(Path1) > SizeOf(Path2))
		{
			Stop = SizeOf(Path1);
		}else{
			Stop = SizeOf(Path2);
		}

		while(Place != Stop)
		{
			if(Cmp(Path1, Path2, Place) == 1)
			{
				Place+=2;
				CpyUp(Path1, Place, Return);
				return;
			}

			Place++;
		}
	}

	/*Line - Enter string to search
	  sFind - What char to start cpying at if this is NULL it will cpy from beginning to eFind
	  eFind - What char to stop cpying at if this is NULL it will cpy from sFind to the end
	  Return - Where should the string be cpyed to*/
	void InbetweenChar(char* Line, char* sFind, char* eFind, char* Return)
	{
		int s;

		if(sFind != NULL)
		{
			s = findstr(Line, sFind);
		}else{
			s = -1;
		}

		if(eFind != NULL)
		{
			int e, charr, next = 0;
			e = findstr(Line, eFind);
			e--;

			while(s < e)
			{
				s++;
				charr = (char) Line[s];
				Return[next] = charr;
				next++;
			}
		}else{
			s+=1;
			strcpy(Return, &Line[s]);
			Return[SizeOf(Return) - 1] = 0;
		}
	}

	void KillNull(char* item)
	{
		int a = sizeof(item) - 2;
		item[a + 1] = 0;
	}

	//changes sec to min:sec
	void TTime(int SEC, char* Return)
	{
		long min = 0;
		long sec = 0;

		Clear(Return);

		if (SEC > 59){
			min = (long) SEC / 60;//converts float to int the /
			sec = (long) SEC - (min * 60);
			if (sec < 10){
				sprintf(Return, "%i:0%i", min, sec);
				return;
			}
			if (sec > 9){
				sprintf(Return, "%i:%i", min, sec);
				return;
			}
		}
		if (SEC < 60){
			sec = (long) SEC;
			if (sec < 10){
				sprintf(Return, "0:0%i", sec);
				return;
			}
			if (sec > 9){
				sprintf(Return, "0:%i", sec);
				return;
			}
		}
	}

	//changes min:sec to sec
	int STime(char* Time)
	{
		int fin = 0;

		if(Find(Time, ":") == 1)
		{
			int min = 0;
			int sec = 0;
			char Min[MAX];
			char Sec[MAX];
			char col;
			col = 58;
			FindLCpy(Time, col, Min);
			FindRCpy(Time, col, Sec);
			min = atoi(Min);
			sec = atoi(Sec);
			min = min * 60;
			fin = min + sec;
		}else{
			fin = atoi(Time);
		}

		return fin;
	}

	//Linked List Stuff

	inline void AddItem(M3UINFO** Head, char* Title, char* Path, char* Time)
	{

		M3UINFO* temp = *Head;

		if(temp == NULL)
		{
			num = START;
		}

		while (temp != NULL)
		{
			temp = temp->next;
		}

		if(*Head == NULL)
		{
			*Head = new M3UINFO;
			strcpy((*Head)->Title, Title);
			strcpy((*Head)->Path, Path);
			strcpy((*Head)->Time, Time);
			(*Head)->Number = num;
			(*Head)->Played = false;
			(*Head)->next = NULL;
		}
		else
		{
			M3UINFO* temp = new M3UINFO;
			strcpy(temp->Title, Title);
			strcpy(temp->Path, Path);
			strcpy(temp->Time, Time);
			temp->Number = num;
			temp->Played = false;
			temp->next = *Head;
			*Head = temp;
		}

		num++;
	}

	//if the return is a NULL then the list is empty
	inline char* PrintTitle(M3UINFO* Head, int Number)
	{
		if(Number < START)
		{
			return err;
		}

		if(Number >= num)
		{
			return err;
		}

		if(Head == NULL)
		{
			return NULL;
		}

		M3UINFO* temp = Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				return temp->Title;
			}
			temp = temp->next;
		}

		return NULL;
	}

	inline char* PrintTime(M3UINFO* Head, int Number)
	{
		if(Number < START)
		{
			return err;
		}

		if(Number >= num)
		{
			return err;
		}

		if(Head == NULL)
		{
			return NULL;
		}

		M3UINFO* temp = Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				return temp->Time;
			}
			temp = temp->next;
		}

		return NULL;
	}

	inline char *PrintPath(M3UINFO* Head, int Number)
	{
		if(Number < START)
		{
			return err;
		}

		if(Number >= num)
		{
			return err;
		}

		if(Head == NULL)
		{
			return NULL;
		}

		M3UINFO* temp = Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				char* Temp;
				Temp = new char[SizeOf(temp->Path)];
				strcpy(Temp, temp->Path);
				Temp[SizeOf(temp->Path) - 1] = 0;
				return Temp;
			}
			temp = temp->next;
		}

		return NULL;
	}

	inline bool PrintPlayed(M3UINFO* Head, int Number)
	{
		if(Number < START)
		{
			return false;
		}

		if(Number >= num)
		{
			return false;
		}

		if(Head == NULL)
		{
			return NULL;
		}

		M3UINFO* temp = Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				return temp->Played;
			}
			temp = temp->next;
		}
		return NULL;
	}

	inline void KillItem(M3UINFO** Head, int Number)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		if(*Head == NULL)	return;

		if ((*Head)->Number == Number)
		{
			M3UINFO* temp = *Head;
			*Head = (*Head)->next;
			delete temp;
			num--;
			return;
		}

		M3UINFO* temp1 = *Head;
		M3UINFO* temp2 = (*Head)->next;

		while(temp2 != NULL)
		{
			temp1->Number--;
			if(temp2->Number == Number)
			{
				temp1->next = temp2->next;
				delete temp2;
				num--;
				return;
			}
			temp2 = temp2->next;
			temp1 = temp1->next;
		}
	}

	inline void KillLst(M3UINFO** Head)
	{
		M3UINFO* temp = NULL;

		while(*Head != NULL)
		{
			temp = *Head;
			*Head = (*Head)->next;
			num = START;
			delete temp;
		}
	}

	inline void MoveUp(M3UINFO** Head, int Number)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		if(*Head == NULL) return;

		M3UINFO* temp = *Head;
		M3UINFO* temp2 = *Head;

		char bufferTitle[MAX];
		char bufferPath[MAX];
		char bufferTime[MAX];
		bool bufferPlayed;

		while (temp != NULL || temp2 != NULL)
		{
			if(temp->Number == (Number + 1))
			{
				strcpy(bufferTitle, temp->Title);
				strcpy(bufferPath, temp->Path);
				strcpy(bufferTime, temp->Time);
				bufferPlayed = temp->Played;

				temp2 = temp2->next;

				strcpy(temp->Title, temp2->Title);
				strcpy(temp->Path, temp2->Path);
				strcpy(temp->Time, temp2->Time);
				temp->Played = temp2->Played;

				strcpy(temp2->Title, bufferTitle);
				strcpy(temp2->Path, bufferPath);
				strcpy(temp2->Time, bufferTime);
				temp2->Played = bufferPlayed;
				return;
			}
			temp = temp->next;
			temp2 = temp2->next;
		}
	}

	inline void MoveDown(M3UINFO** Head, int Number)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		if(*Head == NULL) return;

		M3UINFO* temp = *Head;
		M3UINFO* temp2 = *Head;

		char bufferTitle[MAX];
		char bufferPath[MAX];
		char bufferTime[MAX];
		bool bufferPlayed;

		while (temp != NULL || temp2 != NULL)
		{
			if(temp->Number == Number)
			{
				strcpy(bufferTitle, temp->Title);
				strcpy(bufferPath, temp->Path);
				strcpy(bufferTime, temp->Time);
				bufferPlayed = temp->Played;

				temp2 = temp2->next;

				strcpy(temp->Title, temp2->Title);
				strcpy(temp->Path, temp2->Path);
				strcpy(temp->Time, temp2->Time);
				temp->Played = temp2->Played;

				strcpy(temp2->Title, bufferTitle);
				strcpy(temp2->Path, bufferPath);
				strcpy(temp2->Time, bufferTime);
				temp2->Played = bufferPlayed;
				return;
			}
			temp = temp->next;
			temp2 = temp2->next;
		}
	}

	inline void CTime(M3UINFO** Head, int Number, char* Change)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		M3UINFO* temp = *Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				strcpy(temp->Time, Change);
				return;
			}
			temp = temp->next;
		}
	}

	inline void CPath(M3UINFO** Head, int Number, char* Change)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		M3UINFO* temp = *Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				strcpy(temp->Path, Change);
				return;
			}
			temp = temp->next;
		}
	}

	inline void CTitle(M3UINFO** Head, int Number, char* Change)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		M3UINFO* temp = *Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				strcpy(temp->Title, Change);
				return;
			}
			temp = temp->next;
		}
	}

	inline void CPlayed(M3UINFO** Head, int Number, bool Played)
	{
		if(Number < START)
		{
			return;
		}

		if(Number >= num)
		{
			return;
		}

		M3UINFO* temp = *Head;

		while (temp != NULL)
		{
			if(temp->Number == Number)
			{
				temp->Played = Played;
				return;
			}
			temp = temp->next;
		}
	}

public:

	int num;

	NuclearM3U()
	{
		loaded = false;
		Head = NULL;
		num = START;
		strcpy(err, "Error!!!");
	} 

	~NuclearM3U()
	{
		KillLst(&Head);
	}

	/*
	  more then 0 = its all good
	  0 = file wasnt loaded
	 -1 = invalid m3u file
	*/
	int Load(char* FileName, bool ClearList)
	{
		bool go = false;
		bool foundd = false;
		int found = -1;
		long len = FileLen(FileName);
		char* buffer;
        buffer = new char[len + 1];
		char Time[MAX];
		char Title[MAX];
		char Path[MAX];
		int t = 0;

		if(ClearList == true)
		{
			KillLst(&Head);
		}

		file = fopen(FileName,"rb+");
		//if the file dosnt exist return 0
		if (!file)
		{
			delete buffer;
			fclose(file);
			return 0;
        }

		//file loaded
		loaded = true;

		while (fgets(buffer, len + 1, file) != NULL) //file buffer
		{
			if(go == false)
			{
				//look for #EXTM3U
				if(findstr(buffer, "#EXTM3U") == 0)
				{
					//found #EXTM3U
					go = true;
				}else{
					//didnt find #EXTM3U
					go = false;
					delete buffer;
					fclose(file);
					return -1;
				}
			}else{
				//look for #EXTINF
				if(findstr(buffer, "#EXTINF") == 0)
				{
					//found #EXTINF
					found++;
					
					//Find Time
					if(num != 0)
					{
						Clear(Time);
					}
					InbetweenChar(buffer, ":", ",", Time);
					KillNull(Time);
					t = atoi(Time);
					if(t > 0)
					{
						TTime(t, Time);
					}
					
					//Find Title
					InbetweenChar(buffer, ",", NULL, Title);
					
					foundd = true;
				}else{	
					if(foundd == false)
					{
						Clear(Title);
						Clear(Path);

						if(Find(buffer, "\\") == 1)
						{
							InbetweenChar(buffer, "\\", ".", Title);
						}else{
							InbetweenChar(buffer, NULL, ".", Title);
						}

						FindPath(buffer, FileName, Path);
						strcpy(Time, "0:00");
						found++;

						AddItem(&Head, Title, Path, Time);
					}else{

						//if the time is -1 then its net radio
						if(atol(Time) == -1)
						{
							strcpy(Path, buffer);
						}else{
							FindPath(buffer, FileName, Path);
						}

						foundd = false;

						AddItem(&Head, Title, Path, Time);
					}
					if(found == -1)
					{
						delete buffer;
						fclose(file);
						return -1;
					}
				}			
			}
		}

		delete buffer;
		fclose(file);
		return found;
	}

	/*
	  if Save returns 0 then Saving file failed probly because the file path is wrong
	  if Save returns 1 then its all good
	*/
	int Save(char* FileName)
	{
    	file = fopen(FileName,"w");
    	if (!file)
		{
			fclose(file);
        	return 0;
		}else{
			char buffer[MAX];
			char Path[MAX];

			fputs("#EXTM3U", file);
			fputs("\n", file);

			for(int a=START;a!=num;a++)
			{
				sprintf(buffer, "#EXTINF:%i,%s", STime(PrintTime(Head, a)), PrintTitle(Head, a));
				fputs(buffer, file);
				fputs("\n", file);

				if(STime(PrintTime(Head, a)) == -1)
				{
					strcpy(Path, PrintPath(Head, a));
				}else{
					SFindPath(PrintPath(Head, a), FileName, Path);
				}

				fputs(Path, file);
				fputs("\n", file);
			}
			fclose(file);
		}
		return 1;
	}

	//add a file to list
	void Add(char* Title, char* Path, char* Time)
	{
		AddItem(&Head, Title, Path, Time);
	}

	//delete a file off the list
	void KillFile(int Number)
	{
		KillItem(&Head, Number);
	}

	//delete the list from memory
	void KillList()
	{
		KillLst(&Head);
	}

	//get the path of a file
	char* Path(int Number)
	{
		return PrintPath(Head, Number);
	}

	//get the time of a file
	char* Time(int Number)
	{
		return PrintTime(Head, Number);
	}

	//get the title of a file
	char* Title(int Number)
	{
		return PrintTitle(Head, Number);
	}

	//cheak if the file has been played
	bool Played(int Number)
	{
		return PrintPlayed(Head, Number);
	}

	//move file up on the list
	void Up(int Number)
	{
		MoveUp(&Head, Number);
	}

	//move file down on the list
	void Down(int Number)
	{
		MoveDown(&Head, Number);
	}

	//chamge the time of a file
	void EditTime(int Number, char* Change)
	{
		CTime(&Head, Number, Change);
	}

	//change the title of a file
	void EditTitle(int Number, char* Change)
	{
		CTitle(&Head, Number, Change);
	}

	//change the path of a file
	void EditPath(int Number, char* Change)
	{
		CPath(&Head, Number, Change);
	}

	//change if the file was played
	void EditPlayed(int Number, bool Played)
	{
		CPlayed(&Head, Number, Played);
	}
};