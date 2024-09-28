#pragma once

#pragma warning(disable:4996)



#define MAX_PLAYLIST_SIZE 20
#define MIN_PLAYLIST_SIZE 1
#define SIZE 50   //size of hash table
#define MAX_STRING_LENGTH 200
#define TRUE              0
#define FALSE            -1
#define MEM_ERROR        -1
#define INVALID_KEY      -2
#define DUP_KEY          -3
#define INVALID_SONGNAME -4
#define INVALID_ALBUM    -5
#define INVALID_ARTIST   -6
#define DOES_NOT_EXIST   -7
#define DUPLICATE        -8
#define QUEUE_IS_EMPTY   -9
#define INVALID_CHOICE   -10
#define PLAYLIST_NAME_TAKEN -11
#define PLAYLIST_DOES_NOT_EXIST -12
#define INVALID_PLAYLIST_NAME -13
#define MAX_LOGGIN_LENGTH 21
#define MIN_LOGGIN_LENGTH 6
#define OVER_FLOW -14
#define UNDER_FLOW -15
#define INVALID_USERNAME -16
#define CANNOT_OPEN_FILE -17
#define ADD_TO_PLAYLIST -18
#define REMOVE_FROM_PLAYLIST -19
#define PLAY_PLAYLIST -20
#define DISPLAY_PLAYLIST -21
#define DISPLAY_ALL_PLAYLISTS -26
#define DELETE_PLAYLIST -22
#define CREATE_PLAYLIST -23
#define ADD_PLAYLIST_TO_QUEUE -24
#define ADD_SONG_TO_QUEUE -25
#define EMPTY_PLAYLIST -32
#define SONG_NOT_IN_PLAYLIST -34

#define MUSIC_PLAYER_MENU  '1'
#define MUSIC_MANAGER_MENU '2'
#define PLAYLIST_MANAGER   '3'
#define EXIT_PROGRAM     2

#include <SFML/Audio.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <filesystem>
#include <cstdlib>
#include <cstdio>
#include <fstream>



using namespace std;


typedef struct Playlist
{
	string songName;
	struct Playlist* next;

} Playlist;

typedef struct PlaylistKvp {
	string playlistName;
	Playlist* playlist;
}PlaylistKvp;

typedef struct PlaylistStorage {
	PlaylistKvp* table[SIZE];

} PlaylistStorage;

typedef struct Song
{
	string songName;
	struct Song* NextSong;
} Song;

typedef struct SongQueue
{
	Song* Front;
	Song* Back;
} SongQueue;

typedef struct SongInfo
{
	string SongName;
	string Artist;
	int SongLength;
	string Album;
} SongInfo;


typedef struct SongKeyValuePair
{
	string    SongName;
	SongInfo* SongInfo;
} SongKeyValuePair;


typedef struct SongStorage
{
	SongKeyValuePair* Table[SIZE];
} SongStorage;




class UserClass
{

private:


	string      username;
	string	    password;
	string directoryPath;
	bool	isLoggedIn;
	int      currentMenu; 

public:

	SongStorage*   songLibrary;
	PlaylistStorage* playlists;
	SongQueue*           queue;

	UserClass(string directoryPath);
	~UserClass();

	//ACCESSORS
	string GetDirectory(void);
	string GetUsername(void);
	string GetPassword(void);

	//MUTATORS
	bool SetDirectory(string directory);
	bool SetUsername(string newUsername);
	bool SetPassword(string newPassword);


	//User Interface Methods
	void DisplayMusicManager(void);
	void DiplayPlaylistManager(void);
	bool GetLoginInfoFromFile(void);
	void StorePasswordToFile(string password);
	void StoreUsernameToFile(string username);
	void PrintErrorUI(int ErrorType, string toPrinfIfInvalid);
	bool isUserAccountFileInDatabase(string username);
	bool NewUsername(void);
	bool NewPassword(void);
	void DisplayMainMenuLoggedIn(void);
	void DisplayMainMenuLoggedOut(void);
	void DisplayMusicPlayer(void);
	void KeystrokeHandling(void);
	int LoginToAccount(void);
	string GetString();
	string GetSongname();
	void DisplayCurrentMenu();
	bool SetCurrentMenu(int userChoice);
	int  GetCurrentMenu(void);
	int ProcessChoice(int userChoice);
};


//song storage functions
bool FileExists(UserClass* user, string myFile);
bool checkAndLoadSongLibrary(UserClass* user);
SongKeyValuePair* InitializeKeyValuePair(string songName, string artist, string album, int runtime);
SongInfo* InitializeSongInfo(string songName, string artist, string album, int runtime);
SongStorage* InitializeHashTable(void);
bool DisplaySongAttributes(UserClass* user, string songName);
bool isMemoryError(void* pointer);
int GenerateHash(string word);
void PrintError(int ErrorType);
bool AddSong(UserClass* user, string songName, string album, int length, string artist);
SongInfo* SearchForSong(UserClass* user, string songName);
void freeList(UserClass* user);
void DisplaySongList(UserClass* user);
void findSongInDirectory(UserClass* user);
bool ValidateMp3(string mp3);
bool ValidateRegularString(string string);
bool ValidateLength(int length);
void storeSongInTextFile(UserClass* user, string songName);
void DeleteSongFromLibrary(UserClass* user, string songToDelete);
void freeQueue(UserClass* user);


//song player functions
bool playAudio(UserClass* user, string songName);
void PlayPlaylist(UserClass* user, string playlistName);
void PlayQueue(UserClass* user);

//queue functions
SongQueue* InititalizeQueue(void);
string DeQueue(UserClass* user);
bool IsQueueEmpty(UserClass* user);
void EnQueue(UserClass* user, string songNameToInsert);
Song* AddNewSong(UserClass* user, string newSongName);
void DisplayQueue(UserClass* user);

//playlisthash functions
PlaylistKvp* initializePlaylistKvp(string playlistName, Playlist* playlist);
PlaylistStorage* InitializePlaylistTable(void);
void insertPlaylist(UserClass* user, string playlistName, Playlist* playlist);
void deletePlaylist(UserClass* user, string playlistName);
bool isValidPlaylistName(string playlistName);
Playlist* searchForPlaylist(UserClass* user, string playlistName);
void PlaylistOperator(int operation, UserClass* user);
string GetPlaylistName(UserClass* user);
bool isValidPlaylist(UserClass* user, string playlistName);
//playlist functions
Playlist* createPlaylist(UserClass* user);
void AddSongNodeToPlaylist(UserClass* user, Playlist** head, string songName);
void DeleteSongFromPlaylist(UserClass* user, string songName, string playlistName);
void freePlaylists(UserClass* user);
void addPlaylistToQueue(UserClass* user, Playlist* playlist);
void checkAndLoadPlaylists(UserClass* user);
void storePlayListsInTextFile(UserClass* user);
void printPlaylist(UserClass* user, string playlistName);
void printAllPlayLists(UserClass* user);
