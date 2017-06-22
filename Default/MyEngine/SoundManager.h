///////////////////////////////////////////////////////////////////////////////
// Filename: SoundManager.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <list>
#include"stdafx.h"

///////////////////////////////////////////////////////////////////////////////
// Class name: SoundManager
///////////////////////////////////////////////////////////////////////////////

#define SOUND_DOUBLEJUMP 1000
#define SOUND_LAND 1001
#define SOUND_FIRE 1002
#define SOUND_SAVE 1003
#define SOUND_BOSHYTIME 1004
#define SOUND_BOSSHIT 1007


#define SOUND_INTROBGM 0
#define SOUND_INTROTD 1
#define SOUND_INTROJUMP 2
#define SOUND_INTROGODDAMN 3

#define SOUND_WORLDBGM 0
#define SOUND_BOSSBGM 1
#define SOUND_BOSSSHOOT 2

class SoundManager
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	
	SoundManager(const SoundManager&);
	~SoundManager();

	static SoundManager * GetInstance();
	
	bool Initialize(HWND);
	void Shutdown();
	void UpdateStageList(int i);

	bool PlayWaveFile(int i);
	bool PlayWaveFileLoop(int i);

	bool PlayWaveFilePos(int i, int pos);

	bool StopWaveFile(int i);

	bool StopWaveFile();

private:
	static SoundManager* instance;
	SoundManager();
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(const char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);



private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

	std::list<LPDIRECTSOUNDBUFFER8*> GeneralList;
	std::list<LPDIRECTSOUNDBUFFER8*> StageList;
};

#define GET_SNDMANAGER() SoundManager::GetInstance()



#endif