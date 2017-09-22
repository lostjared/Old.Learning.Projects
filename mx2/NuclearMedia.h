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

NuclearMedia and NuclearCDAudio
part of the NuclearMedia SDK
by Lee Trager
E-Mail/MSN: L_Trager@hotmail.com
AIM: nukem996
www.LostSideDead.com

This has all the media stuff for Audio Video and CDAudio.
Most of this uses win api calls to work. You should be on win98 or above
and be compiling this on VC++. 

since most media players (windows media player, winamp) use
win api they can screw w/ each other. so if your playing an AudioCD in winamp and run this
then close it, it may stop the cd. other programs may do the same to this. try to think of
unique aliass. using 'cd' and 'mpeg' are VERY COMMON it will probly screw you over. the defalt
aliass are pretty unique (its the class names) so you should be good if dont need to play more
then one file at once.
*/

//only include header once
#pragma once

#include <windows.h> //for windows api calls and sound
#include <mmsystem.h> //for sound
#include <stdio.h> //to put string together
#include <stdlib.h>

#pragma comment(lib,"winmm") //auto links winmm.lib

#ifdef MAX
	#undef MAX
	#pragma message(" ")
	#pragma message("You cannt use MAX because Nuclear Media needs it. It will be undefined.")
	#pragma message(" ") 
#endif

#define MAX		150

#ifndef NULL
	#define NULL	0
#endif

//if the funtion returns 0 then it failed. if it worked then it will return 1 or greater

class NuclearMedia{

private:

	long a;
	char finname[MAX];
	char todo[MAX];
	char fin[MAX];
	char l[40];
	char p[40];
	char alias[MAX];
	char statuss[MAX];

	//error code
	void error(long what)
	{
		mciGetErrorString(what, err, 128);
	}

	//changes millisec to min:sec
	char* htime(char t[MAX])
	{
		long min = 0;
		long sec = 0;
		double ms = 0;
		double mm = 0;
		long sm = 0;
		ms = atoi(t);
		sm = atoi(t);
		//get decimal
		ms = ms / 1000;
		sm = sm / 1000;
		//get the diffrence between the decimal
		mm = ms - sm;
		//round
		if (mm < .4){
			ms = ms - mm;
		}
		if (mm > .5){
			mm = 1 - mm;
			ms = ms + mm;
		}
		if (ms > 59){
			min = (long) ms / 60;//converts float to int the /
			sec = (long) ms - (min * 60);
			if (sec < 10){
				sprintf(fin, "%i:0%i", min, sec);
				return fin;
			}
			if (sec > 9){
				sprintf(fin, "%i:%i", min, sec);
				return fin;
			}
		}
		if (ms < 60){
			sec = (long) ms;
			if (sec < 10){
				sprintf(fin, "0:0%i", sec);
				return fin;
			}
			if (sec > 9){
				sprintf(fin, "0:%i", sec);
				return fin;
			}
		}

		strcpy(fin, "0:00");
		return fin;
	}

	//changes millisec to sec
	int stime(char t[MAX]){
		long sec = 0;
		double ms = 0;
		double mm = 0;
		long sm = 0;
		ms = atoi(t);
		sm = atoi(t);
		//get decimal
		ms = ms / 1000;
		sm = sm / 1000;
		//get the diffrence between the decimal
		mm = ms - sm;
		//round
		if (mm < .4){
			ms = ms - mm;
		}
		if (mm > .5){
			mm = 1 - mm;
			ms = ms + mm;
		}

		sec = (long) ms;

		return sec;
	}

public:

	//this is where the error is stored
	char err[MAX];

	NuclearMedia()
	{
		strcpy(alias, "NuclearMedia");
	}
	
	~NuclearMedia()
	{
		Stop();
		Close();
	}

	//Sets the Alias
	void Alias(char* Alias)
	{
		strcpy(alias, Alias);
	}

	//returns the alias
	char* ReturnAlias()
	{
		return alias;
	}

	//opens files and dose not put them in a window
	int Open(char* file)
	{
		if(GetShortPathName(file, finname, 1000) != 0)
		{
			return fOpen(finname);
		}

		strcpy(err, "The File could not be found!");
		return 0;
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	opens files and dose not put them in a window
	this also could(still testing) for web files lik streaming video*/
	int fOpen(char* file)
	{
		Close();
		sprintf(todo, "open %s type mpegvideo Alias %s", file, alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 1;
		}else{
			return 0;
		}
    }

	//open files and puts them in a parent space
	int VidOpen(char* file, HWND parent)
	{
		if(GetShortPathName(file, finname, 1000) != 0){
			return fVidOpen(finname, parent);
		}

		strcpy(err, "The File could not be found!");
		return 0;
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	open files and puts them in a parent space
	this could also be used for streaming video(not tested)*/
	int fVidOpen(char* file, HWND parent)
	{
		Close();
		sprintf(todo, "open %s type mpegvideo Alias %s parent %s Style 1073741824", file, alias, parent);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 1;
		}else{
			return 0;
		}
	}

	//play file
	int Play()
	{
		sprintf(todo, "Play %s from 0", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
		
		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
    }

	//stop file
    int Stop()
	{
		sprintf(todo, "Stop %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
    }

	//pause file
	int Pause()
	{
		sprintf(todo, "Pause %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
    }

	//resume file
    int Resume()
	{
		sprintf(todo, "Resume %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
    }

	//close file
    int Close()
	{
		sprintf(todo, "Close %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//get the poistion of a file millisec time
	int MilliSecPosition()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0 ,0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString (todo, p, sizeof(p), 0);
		return ( unsigned long ) atol(p);
	}

	//get poistion sec time
	int SecPosition()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString(todo, p, sizeof(p), 0);
		return stime(p);
	}

	//get poistion min:sec time
	char* Position()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString(todo, p, sizeof(p), 0);
		return htime(p);
	}

	//gets the length of a file millisec time
	int MilliSecLength()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, sizeof(l), 0);
		return ( unsigned long ) atol (l);
	}

	//gets length in sec time
	int SecLength()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, sizeof(l), 0);
		return stime(l);
	}

	//get length min:sec time
	char* Length()
	{
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, sizeof(l), 0);
		return htime(l);
	}

	//gets time remaining in millisec time
	int MilliSecRemaining()
	{
		return MilliSecLength() - MilliSecPosition();
	}

	//gets time remaining in sec time
	int SecRemaining()
	{
		int time = MilliSecLength() - MilliSecPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return stime(ctime);
	}

	//gets time remaining in min:sec
	char* Remaining()
	{
		int time = MilliSecLength() - MilliSecPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return htime(ctime);
	}

	//changes volume sp = speaker vol = what the volume should be set at
	int Volume(char sp[6], long vol)
	{
		vol = vol * 10;

		if(strcmp(sp, "both") == 0)
		{
			sprintf(todo, "setaudio %s left Volume to %d", alias, vol);
			a = mciSendString (todo, 0, 0, 0);

			sprintf(todo, "setaudio %s right Volume to %d", alias, vol);
			a = mciSendString (todo, 0, 0, 0);
		
		}else{
		
			sprintf(todo, "setaudio %s %s Volume to %d", alias, sp, vol);
			a = mciSendString (todo, 0, 0, 0);
		}

		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//resize the video
	int ResizeVid(int left, int top, int width, int height)
	{
		sprintf(todo, "put %s window at %i %i %i %i", alias, left, top, width, height);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//seek somewhere with in the file
	int SeekTo(int where)
	{
		where = where * 1000;

		sprintf(todo, "set %s time format milliseconds", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
		sprintf(todo, "play %s from %i", alias, where);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//finds out the status of whats being played
	char* Status()
	{
		sprintf(todo, "status %s mode", alias);
		a = mciSendString(todo, statuss, 40, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return statuss;
		}
	}

	//find out if a file is playing or not.
	bool Playing()
	{
		if(strcmp(Status(), "playing") == 0)
		{
			return true;
		}else{
			return false;
		}
	}

	//set the speed of a file 1000 = normal below 1000 = slower above 1000 = faster
	//changes speed will make audio only come out the frount 2 speakers
	int Speed(int spe)
	{
		sprintf(todo, "set %s speed %i", alias, spe);
		a = mciSendString (todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}	
	}

	//auto repeat the file repeat [t] = true then repeat file false it wont or will stop
	int Repeat(bool re)
	{
		if (re == true)
		{
			sprintf(todo, "play %s notify repeat", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}else{
			sprintf(todo, "play %s", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//rewind to start
	int Rewind()
	{
		sprintf(todo, "seek %s to start wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//fast foward to end
	int FastFoward()
	{
		sprintf(todo, "seek %s to end wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}
		
};

/*
  this will play CDAudio. if another program is playing CDAudio this can screw w/ it.
  this is set up to werk w/ ur drive that is ur CDAudio drive. it might not werk w/ other drives
*/

class NuclearCDAudio
{

private:

	long a;
	char alias[MAX];
	char todo[MAX];
	char statuss[MAX];
	char fin[MAX];
	char len[MAX];
	char pos[MAX];


	//changes millisec to min:sec
	char* htime(char t[MAX])
	{
		long min = 0;
		long sec = 0;
		double ms = 0;
		double mm = 0;
		long sm = 0;
		ms = atoi(t);
		sm = atoi(t);
		//get decimal
		ms = ms / 1000;
		sm = sm / 1000;
		//get the diffrence between the decimal
		mm = ms - sm;
		//round
		if (mm < .4){
			ms = ms - mm;
		}
		if (mm > .5){
			mm = 1 - mm;
			ms = ms + mm;
		}
		if (ms > 59){
			min = (long) ms / 60;//converts float to int the /
			sec = (long) ms - (min * 60);
			if (sec < 10){
				sprintf(fin, "%i:0%i", min, sec);
				return fin;
			}
			if (sec > 9){
				sprintf(fin, "%i:%i", min, sec);
				return fin;
			}
		}
		if (ms < 60){
			sec = (long) ms;
			if (sec < 10){
				sprintf(fin, "0:0%i", sec);
				return fin;
			}
			if (sec > 9){
				sprintf(fin, "0:%i", sec);
				return fin;
			}
		}

		strcpy(fin, "0:00");
		return fin;
	}

	//changes millisec to sec
	int stime(char t[MAX]){
		long sec = 0;
		double ms = 0;
		double mm = 0;
		long sm = 0;
		ms = atoi(t);
		sm = atoi(t);
		//get decimal
		ms = ms / 1000;
		sm = sm / 1000;
		//get the diffrence between the decimal
		mm = ms - sm;
		//round
		if (mm < .4){
			ms = ms - mm;
		}
		if (mm > .5){
			mm = 1 - mm;
			ms = ms + mm;
		}

		sec = (long) ms;

		return sec;
	}

	void error(long what)
	{
		mciGetErrorString(what, err, 128);
	}

public:

	char err[MAX];

	NuclearCDAudio()
	{
		Alias("NuclearCDAudio");
	}

	~NuclearCDAudio()
	{
		Stop();
		Close();
	}

	//sets the alias
	void Alias(char* Alias)
	{
		strcpy(alias, Alias);
	}

	//returns alias
	char* ReturnAlias()
	{
		return alias;
	}

	//opens the cdrom door
	int OpenCDROM()
	{
		sprintf(todo, "set %s door open", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//closes the cdrom door
	int CloseCDROM()
	{
		sprintf(todo, "set %s door closed", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//open the cd
	int Open()
	{
		sprintf(todo, "open cdaudio alias %s wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//plays cdaudio
	int Play()
	{
		sprintf(todo, "play %s", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//seeks the file some where
	int Seek(int Where)
	{
		Stop();
		sprintf(todo, "play %s from %i", alias, Where);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//stop cd
	int Stop()
	{
		sprintf(todo, "stop %s", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//close cd
	int Close()
	{
		sprintf(todo, "close %s", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//pause cd
	int Pause()
	{
		sprintf(todo, "pause %s", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//resume cd
	int Resume()
	{
		sprintf(todo, "resume %s", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//the status of the cd
	char* Status()
	{
		sprintf(todo, "status %s mode", alias);
		a = mciSendString(todo, statuss, 40, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return statuss;
		}
	}

	//the total number of tracks
	int TotalTracks()
	{
		char tracks[MAX];
		sprintf(todo, "status %s number of tracks wait", alias);
		a = mciSendString(todo, tracks, 40, 0);
		error(a);

		if(a != 0)
		{
			return 0;
		}else{
			return atoi(tracks);
		}
	}

	//what track your on
	int Track()
	{
		char track[MAX];
		sprintf(todo, "status %s current track", alias);
		a = mciSendString(todo, track, 40, 0);

		if(a != 0)
		{
			return 0;
		}else{
			return atoi(track);
		}
	}

	//seek track to...
	void SeekTrack(int Track)
	{
		sprintf(todo, "set %s time format tmsf wait", alias);
		a = mciSendString(todo, 0, 0, 0);

		sprintf(todo, "seek %s to %i", alias, Track);
		a = mciSendString(todo, 0, 0, 0);
	}

	//goto the previous track
	void PrevTrack()
	{
		//if its on the 1st track then exit funtion
		if(Track() == 1)
		{
			return;
		}

		SeekTrack(Track() - 1);
	}

	//goto the next track
	void NextTrack()
	{
		//if its on the last track then exit funtion
		if(Track() == TotalTracks())
		{
			return;
		}

		SeekTrack(Track() + 1);
	}

	//finds the length of a track in milli sec time
	int MilliSecFindTrackLength(int Track)
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track);
		a = mciSendString(todo, len, sizeof(len), 0);
		return atol(len);
	}

	//finds the length of a track in sec time
	int SecFindTrackLength(int Track)
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track);
		a = mciSendString(todo, len, sizeof(len), 0);
		return stime(len);
	}

	//find the length of a track in min:sec time
	char* FindTrackLength(int Track)
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track);
		a = mciSendString(todo, len, sizeof(len), 0);
		return htime(len);
	}

	//finds the starting time(in the cd) of a track in milli sec time
	int MilliSecStartingTime(int Track)
	{
		sprintf(todo, "status %s position track %i", alias, Track);
		mciSendString(todo, pos, sizeof(pos), 0);
		return atol(pos);
	}

	//finds the starting time(in the cd) of a track in sec time
	int SecStartingTime(int Track)
	{
		sprintf(todo, "status %s position track %i", alias, Track);
		mciSendString(todo, pos, sizeof(pos), 0);
		return stime(pos);
	}

	//finds the starting time(in the cd) of a track in min:sec time
	char* StartingTime(int Track)
	{
		sprintf(todo, "status %s position track %i", alias, Track);
		mciSendString(todo, pos, sizeof(pos), 0);
		return htime(pos);
	}

	//find the track length in milli sec time
	int MilliSecTrackLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track());
		a = mciSendString(todo, len, sizeof(len), 0);
		return atol(len);
	}

	//find the track length in sec time
	int SecTrackLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track());
		a = mciSendString(todo, len, sizeof(len), 0);
		return stime(len);
	}

	//find the track length in min:sec time
	char* TrackLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length track %i", alias, Track());
		a = mciSendString(todo, len, sizeof(len), 0);
		return htime(len);
	}

	//find the cd length in milli sec time
	int MilliSecCDLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length wait", alias);
		a = mciSendString(todo, len, sizeof(len), 0);
		return atol(len);
	}

	//find the cd length in sec time
	int SecCDLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length wait", alias);
		a = mciSendString(todo, len, sizeof(len), 0);
		return stime(len);
	}

	//find the cd length in min:sec time
	char* CDLength()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s length wait", alias);
		a = mciSendString(todo, len, sizeof(len), 0);
		return htime(len);
	}

	//find the track position in milli sec time
	int MilliSecTrackPosition()
	{
		return MilliSecCDPosition() - MilliSecStartingTime(Track());
	}

	//find the track position in sec time
	int SecTrackPosition()
	{
		int time = MilliSecCDPosition() - MilliSecStartingTime(Track());
		char ctime[MAX];
		itoa(time, ctime, 10);
		return stime(ctime);
	}

	//find the track position in min:sec time
	char* TrackPosition()
	{
		int time = MilliSecCDPosition() - MilliSecStartingTime(Track());
		char ctime[MAX];
		itoa(time, ctime, 10);
		return htime(ctime);
	}

	//find the cd position in milli sec time
	int MilliSecCDPosition()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s position wait", alias);
		a = mciSendString(todo, pos, sizeof(pos), 0);
		return atol(pos);
	}

	//find the cd position in sec time
	int SecCDPosition()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s position wait", alias);
		a = mciSendString(todo, pos, sizeof(pos), 0);
		return stime(pos);
	}

	//find the cd position in min:sec time
	char* CDPosition()
	{
		sprintf(todo, "set %s time format milliseconds wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		sprintf(todo, "status %s position wait", alias);
		a = mciSendString(todo, pos, sizeof(pos), 0);
		return htime(pos);
	}

	//find the time remaining on the cd in milli sec time
	int MilliSecCDRemaining()
	{
		return MilliSecCDLength() - MilliSecCDPosition();
	}

	//find the time remaining on the cd in sec time
	int SecCDRemaining()
	{
		int time = MilliSecCDLength() - MilliSecCDPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return stime(ctime);
	}

	//find the time remaining on the cd in min:sec time
	char* CDRemaining()
	{
		int time = MilliSecCDLength() - MilliSecCDPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return htime(ctime);
	}

	//find the time remaining on the track in millisec time
	int MilliSecTrackRemaining()
	{
		return MilliSecTrackLength() - MilliSecTrackPosition();
	}

	//find the time remaining on the track in sec time
	int SecTrackRemaining()
	{
		int time = MilliSecTrackLength() - MilliSecTrackPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return stime(ctime);
	}

	//find the time remaining on the track in min:sec time
	char* TrackRemaining()
	{
		int time = MilliSecTrackLength() - MilliSecTrackPosition();
		char ctime[MAX];
		itoa(time, ctime, 10);
		return htime(ctime);
	}

	//rewind the cd to start
	int Rewind()
	{
		sprintf(todo, "seek %s to start wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//fast foward the cd to end
	int FastFoward()
	{
		sprintf(todo, "seek %s to end wait", alias);
		a = mciSendString(todo, 0, 0, 0);
		if(a != 0)
		{
			return 0;
		}else{
			return 1;
		}
	}

	//cheak if the cd is playing or not
	bool Playing()
	{
		if(strcmp(Status(), "playing") == 0)
		{
			return true;
		}else{
			return false;
		}
	}
};