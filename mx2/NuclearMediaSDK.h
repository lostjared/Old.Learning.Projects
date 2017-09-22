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

NuclearMedia 2.0

This will connect all the engines for you. If you want to use any of these funtions they must
be loaded and run threw this class!!!
*/
//only include header once
#pragma once

//all the headers and libs for NuclearMedia
#include <windows.h> //for windows api calls and sound
#include <mmsystem.h> //for sound
#include <stdio.h> //to put string together
#include <stdlib.H>
#include <FSTREAM.h> //for file opening
#include <time.h> //for randomization
#include "NuclearMedia.h" //multimedia engine
#include "NuclearM3U.h" //M3U engine

#pragma comment(lib,"winmm") //auto links winmm.lib

class NuclearMediaSDK
{
private:
	
	int played;

	int SizeOf(char* item)
	{
		int Num = 0;
		while(item[Num] != NULL)
		{
			Num++;
		}
		return Num - 1;
	}

	int CmpExtention(char* item1, char* item2)
	{
		int a, b;
		int d = 2;
		int Size = SizeOf(item2);
		int Stop = Size - 3;
		for(int c = Size; c != Stop; c--)
		{
			a = (char)item1[d];
			b = (char)item2[c];
			if(a != b)
			{
				return 0;
			}
			d--;
		}
		return 1;
	}

public:

	NuclearM3U M3U; //M3U engine
	NuclearMedia Media; //MultiMedia engine
	NuclearCDAudio CDAudio; //CDAudio engine

	NuclearMediaSDK()
	{
		played = 0;
	}

	~NuclearMediaSDK()
	{
	}

	/*If returns 1 opened Media file
	  If returns 2 opened CDAudio file
	  If returns more then 2 opened M3U file
	  If returns -1 failed to open Media file
	  If returns -2 failed to open CDAudio file
	  If returns -3 failed to open M3U file
	 */
	int Open(char* File)
	{
		if(CmpExtention("m3u", File) == 1)
		{
			int m3u = M3U.Load(File, true);
			if(m3u > 0)
			{
				return m3u;
			}else{
				return -3;
			}
		}

		if(Media.Open(File) == 0)
		{
			return 1;
		}else{
			return -1;
		}
	}

	//opens/plays a file from a play list
	int OpenList(int Number, bool Play)
	{
		int a;
		int type;

		if(CmpExtention("cda", M3U.Path(Number)) == 1)
		{
			a = CDAudio.Open();
			CDAudio.SeekTrack(atoi(M3U.Path(Number)));
			type = 0;
		}else{
			a = Media.Open(M3U.Path(Number));
			type = 1;
		}

		if(Play == true)
		{
			played++;
			M3U.EditPlayed(Number, true);
			if(type == 0)
			{
				a = CDAudio.Play();
			}else{
				a = Media.Play();
			}
		}

		if(type == 0)
		{
			if(strcmp(M3U.Time(Number), CDAudio.TrackLength()) != 0)
			{
				M3U.EditTime(Number, CDAudio.TrackLength());
			}
		}else{
			if(strcmp(M3U.Time(Number), Media.Length()) != 0)
			{
				M3U.EditTime(Number, Media.Length());
			}
		}
		return a;
	}

	/*
	  This will find the time of all the files in a playlist
	  but it takes awhile and uses lotz memory
	*/
	void GetAllTime()
	{	
		for(int a=START; a!=M3U.num; a++)
		{
			GetTime(a);
		}
	}

	void GetTime(int Number)
	{
		char Alias[MAX];
		strcpy(Alias, Media.ReturnAlias());
		Media.Alias("Time");
		OpenList(Number, false);
		M3U.EditTime(Number, Media.Length());
		Media.Close();
		Media.Alias(Alias);
	}

	/*
	if Repeat = false then it will not repeat a file that has been played
	if Repeat = true then it will repeat files that have been played
	play a random playlist file
	returns number that it played
	if it returns -1 then you played all the files on the list or there is nothing in list
	*/
	int PlayRand(bool Repeat)
	{
		if(M3U.num == START)
		{
			return -1;
		}

		srand(time(START));
		int num = rand()%M3U.num;

		if(Repeat == false)
		{
			if(played == M3U.num)
			{
				return -1;
			}

			int loop = START;
			while(M3U.Played(num) == true)
			{
				loop++;
				num = rand()%M3U.num;
				if(loop == (M3U.num + 1))
				{
					return -1;
				}
			}
		}
		
		OpenList(num, true);

		return num;
	}

	//adds all the cd trcks to a M3U list
	void CDtoM3U()
	{
		char Title[MAX];
		char Path[MAX];
		CDAudio.Open();
		for(int a=1;a != CDAudio.TotalTracks(); a++)
		{
			sprintf(Title, "Track %i", a);
			sprintf(Path, "%i.cda\n\n", a);
			M3U.Add(Title, Path, CDAudio.FindTrackLength(a));
		}
	}
};