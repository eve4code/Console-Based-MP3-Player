#include "UserClass.h"

bool isMemoryError(void* pointer)
{

	if (pointer == NULL)
	{
		PrintError(MEM_ERROR);
		return true;
	}
	return false;

}



SongKeyValuePair* InitializeKeyValuePair(string songName, string artist, string album, int runtime)
{

	SongKeyValuePair* kvp = new SongKeyValuePair;
	if (isMemoryError(kvp))
	{
		exit(EXIT_FAILURE);
	}
	kvp->SongName = songName;
	kvp->SongInfo = InitializeSongInfo(songName, artist, album, runtime);

	return kvp;

}


string SecondsToMins(int seconds)
{
	int minutes = seconds / 60;
	int remainingSeconds = seconds % 60;
	string timeString = to_string(minutes) + " minutes " + to_string(remainingSeconds) + " seconds";
	return timeString;
}

SongInfo* InitializeSongInfo(string songName, string artist, string album, int runtime)
{

	SongInfo* newSong = new SongInfo;
	if (isMemoryError(newSong))
	{
		exit(EXIT_FAILURE);
	}


	newSong->SongName = songName;
	newSong->Artist = artist;
	newSong->Album = album;
	newSong->SongLength = runtime;

	newSong->SongName.erase(songName.length() - 4);

	return newSong;

}



SongStorage* InitializeHashTable(void)
{

	SongStorage* hashTable = (SongStorage*)calloc(SIZE, sizeof(SongStorage));
	if (isMemoryError(hashTable))
	{
		exit(EXIT_FAILURE);
	}

	return hashTable;

}


void PrintError(int ErrorType)
{

	if (ErrorType == MEM_ERROR) {
		printf("\nMemory Error!!\n");
	}
	else if (ErrorType == INVALID_KEY) {
		printf("\nERROR: That Profile does Not exist!!\n");
	}
	else if (ErrorType == DUP_KEY) {
		printf("\nERROR: Cannot Insert Username with the Same Hash Value!!\n");
	}
	else if (ErrorType == INVALID_ALBUM) {
		printf("\nERROR: Invalid Album Name!! (Must be between 0-40 characters)\n");
	}
	else if (ErrorType == INVALID_SONGNAME) {
		printf("\nERROR: Invalid Songname!! (Must be between 0-40 characters)\n");
	}
	else if (ErrorType == INVALID_ARTIST) {
		printf("\nERROR: Invalid ARTIST!! (Must be between 0-40 characters)\n");
	}
	else if (ErrorType == DOES_NOT_EXIST) {
		printf("\nERROR: Invalid SONG!! That Song does not exist in your Library!!\n");
	}
	else if (ErrorType == DUPLICATE) {
		printf("\nERROR: That Song is already in your Library!!\n");
	}
	else if (ErrorType == QUEUE_IS_EMPTY) {
		printf("\nERROR: Queue is Empty!!\n");
	}
	else if (ErrorType == INVALID_CHOICE) {
		printf("\nERROR: Invalid Choice!!\n");
	}
	else if (ErrorType == PLAYLIST_NAME_TAKEN) {
		printf("\nERROR: Playlist Name is already taken!!\n");
	}
	else if (ErrorType == PLAYLIST_DOES_NOT_EXIST) {
		printf("\nERROR: The Playlist you are looking for does not exist!!\n");
	}
	else if (ErrorType == INVALID_PLAYLIST_NAME) {
		printf("\nERROR: Invalid Playlist Name!! (Must be inbetween 1 & 20 characters)\n");
	}
	else if (ErrorType == EMPTY_PLAYLIST) {
		printf("\nERROR: Playlist is Empty!!\n");
	}
	else if (ErrorType == SONG_NOT_IN_PLAYLIST) {
		printf("\nERROR: That Song does not exist in your Playlist!!\n");
	}
	else {
		printf("\nERROR: Unknown Error!!\n");
	}
	printf("\n");
	system("pause");
}


SongInfo* SearchForSong(UserClass* user, string songName)
{

	int hash = GenerateHash(songName);
	SongKeyValuePair* bucket = user->songLibrary->Table[hash];

	if (bucket == NULL)
	{
		PrintError(DOES_NOT_EXIST);
		return NULL;
	}

	if (bucket->SongName == songName)
	{
		return bucket->SongInfo;
	}

	PrintError(INVALID_KEY);

	return NULL;

}


bool ValidateLength(int length)
{

	return length > 0;

}


bool ValidateRegularString(string string)
{

	return (string.length() > 0 && string.length() <= MAX_STRING_LENGTH);

}


bool ValidateMp3(string mp3)
{

	if (mp3.length() < 4)
	{
		return false;
	}
	if (strcmp(mp3.c_str() + mp3.length() - 4, ".mp3") != 0)
	{
		return false;
	}
	return true;
}




void DeleteSongFromLibrary(UserClass* user, string songToDelete)
{
	string file_path = user->GetDirectory() + "/" + songToDelete;

	int index = GenerateHash(songToDelete);

	delete (user->songLibrary->Table[index]);
	user->songLibrary->Table[index] = NULL;
}



bool AddSong(UserClass* user, string songName, string album, int length, string artist)
{

	bool status = true;
	if (ValidateRegularString(songName) == false || ValidateMp3(songName) == false)
	{
		PrintError(INVALID_SONGNAME);
		status = false;
	}
	if (ValidateRegularString(album) == false)
	{
		PrintError(INVALID_ALBUM);
		status = false;
	}
	if (ValidateRegularString(artist) == false)
	{
		PrintError(INVALID_ARTIST);
		status = false;
	}

	if (status == false)
	{
		return false;
	}
	SongKeyValuePair* kvp = InitializeKeyValuePair(songName, artist, album, length);
	int index = GenerateHash(songName);
	SongKeyValuePair* bucket = user->songLibrary->Table[index];

	if (bucket == NULL)
	{
		user->songLibrary->Table[index] = kvp;
		return true;
	}
	free(kvp);
	PrintError(DUP_KEY);
	return false;
}

void findSongInDirectory(UserClass* user)
{
	string filePath = user->GetDirectory();

	string command("dir /a-d /b ");
	command.append("\"" + filePath + "\*.mp3\"");
	const char* final_command = command.c_str();

	FILE* file = _popen(final_command, "r");

	if (!file) {
		cerr << "Error: Unable to execute command." << endl;
		return;
	}
	string input;
	char buffer[128];
	while (!feof(file)) {
		if (fgets(buffer, 128, file) != NULL) {
			string songName(buffer);
			songName.erase(songName.find_last_not_of("\n\r") + 1);
			string Artist;
			string Album;
			int Length;
			cout << "Collecting info for " << songName << endl;
			cout << "Enter Artist > ";
			getline(cin, input);
			if (ValidateRegularString(input)) {
				Artist = input;
			}
			cout << "Enter Album > ";
			getline(cin, input);
			if (ValidateRegularString(input)) {
				Album = input;
			}
			cout << "Enter Length in Seconds > ";
			cin >> Length;
			if (Length < 0 && Length < 1000) {
				printf("\nERROR: Invalid Length Setting Length to Minimum Length\n");
				Length = 1;
				return;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			AddSong(user, songName, Album, Length, Artist);
			storeSongInTextFile(user, songName);
		}
	}
	_pclose(file);
}


bool checkAndLoadSongLibrary(UserClass* user)
{
	if (FileExists(user, "songLibrary.txt"))
	{
		string filePath = user->GetDirectory() + "songLibrary.txt";
		ifstream file(filePath);
		if (!file)
		{
			cerr << "Error: Unable to open file." << endl;
			return false;
		}

		string songName;
		string album;
		int length;
		string artist;

		while (getline(file, songName))
		{
			getline(file, album);
			file >> length;
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(file, artist);

			AddSong(user, songName, album, length, artist);
		}

		file.close();
		return true;
	}
	else
	{
		return false;
	}
}



bool FileExists(UserClass* user, string myFile)
{
	ifstream file(user->GetDirectory() + myFile);
	return file.good();
}

void storeSongInTextFile(UserClass* user, string songName) {
	ofstream file(user->GetDirectory() + "songLibrary.txt", ios::app);
	if (!file) {
		PrintError(CANNOT_OPEN_FILE);
		return;
	}
	SongInfo* song = SearchForSong(user, songName);
	if (song == NULL) {
		PrintError(DOES_NOT_EXIST);
		return;
	}
	file << song->SongName+".mp3" << endl;
	file << song->Album << endl;
	file << song->SongLength << endl;
	file << song->Artist << endl;
	file.close();

	if (file.fail()) {
		PrintError(DOES_NOT_EXIST);
	}
}


bool DisplaySongAttributes(UserClass* user, string songName)
{

	SongInfo* songToPrint = SearchForSong(user, songName);
	if (songToPrint == NULL)
	{
		return false;
	}
	cout << "\n------------------------------------------------\n";
	cout << "* Songname                 : " << songToPrint->SongName << endl;
	cout << "* Artist                   : " << songToPrint->Artist << endl;
	cout << "* Album                    : " << songToPrint->Album << endl;
	cout << "* Length                   : " << SecondsToMins(songToPrint->SongLength) << endl;
	cout << "------------------------------------------------\n";

	return true;

}


int GenerateHash(string string)
{

	int hash = 0;
	for (int i = 0; i < string.length(); i++)
	{
		int asciiValue = string[i];
		hash = (hash + asciiValue * (asciiValue + i)) % SIZE;
	}
	return hash;
}

void freeList(UserClass* user)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (user->songLibrary->Table[i] != NULL)
        {
            delete user->songLibrary->Table[i]->SongInfo;
            delete user->songLibrary->Table[i];
        }
    }
    delete user->songLibrary;
}


void DisplaySongList(UserClass* user)
{
	int i = 0;
	system("cls");
	printf("\n--- Song Library ---\n");
	for (i = 0; i < SIZE; i++)
	{
		if (user->songLibrary->Table[i] != NULL)
		{
			DisplaySongAttributes(user, user->songLibrary->Table[i]->SongName);
		}
	}

}

