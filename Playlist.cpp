#include "UserClass.h"

void addPlaylistToQueue(UserClass* user, Playlist* playlist)
{
	if (isMemoryError(user->queue)) 
	{
		exit(EXIT_FAILURE);
	}
	Playlist* currentPlaylist = playlist;
	while (currentPlaylist != NULL) 
	{
		EnQueue(user, currentPlaylist->songName);
		currentPlaylist = currentPlaylist->next;
	}
}


void freePlaylists(UserClass* user)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (user->playlists->table[i] != NULL)
        {
            Playlist* currentSong = user->playlists->table[i]->playlist;
            while (currentSong != NULL)
            {
                Playlist* temp = currentSong;
                currentSong = currentSong->next;
                delete temp;
            }
            delete user->playlists->table[i];
        }
    }
	delete user->playlists;
}



void printPlaylist(UserClass* user, string playlistName)
{
	system("cls");
	if (isValidPlaylist(user, playlistName) == false)
	{
		PrintError(PLAYLIST_DOES_NOT_EXIST);
		return;
	}
	PlaylistKvp* playlistToPrint = user->playlists->table[GenerateHash(playlistName)];
	Playlist* currentSong = playlistToPrint->playlist;
	printf("\n--- Displaying Playlist %s ---\n", playlistName.c_str());
	if (currentSong == NULL || currentSong->songName == "")
	{
		PrintError(EMPTY_PLAYLIST);
		return;
	}
	else if (currentSong == nullptr)
	{
		PrintError(EMPTY_PLAYLIST);
		return;
	}


	while (currentSong != nullptr || currentSong != NULL)
	{
		DisplaySongAttributes(user, currentSong->songName);
		currentSong = currentSong->next;
	}
	system("pause");
}


void DeleteSongFromPlaylist(UserClass* user, string songName, string playlistName)
{
	if (isValidPlaylist(user, playlistName) == false)
	{
		PrintError(PLAYLIST_DOES_NOT_EXIST);
		return;
	}
	PlaylistKvp* playlist = user->playlists->table[GenerateHash(playlistName)];
	Playlist* currentSong = playlist->playlist;
	Playlist* previousSong = NULL;
	while (currentSong != NULL)
	{
		if (currentSong->songName == songName)
		{
			if (previousSong == NULL)
			{
				playlist->playlist = currentSong->next;
				free(currentSong);
				return;
			}
			previousSong->next = currentSong->next;
			free(currentSong);
			return;
		}
		previousSong = currentSong;
		currentSong = currentSong->next;
	}
	PrintError(SONG_NOT_IN_PLAYLIST);

}

string GetPlaylistName(UserClass* user) {
	string playlistName;
	getline(cin, playlistName);

		size_t extensionPos = playlistName.find(".mp3");
		if (extensionPos != string::npos) {
			playlistName = playlistName.substr(0, extensionPos);
			printf("\nERROR: Playlist name cannot contain .mp3 extension\n");
			printf("\nRemoving .mp3 from name and setting playlist...\n");

			return playlistName;
		}
		return playlistName;
}

bool isValidPlaylist(UserClass* user, string playlistName) {
    PlaylistKvp* playlist = user->playlists->table[GenerateHash(playlistName)];
    if (playlist != nullptr && playlist->playlistName == playlistName) {
        return true;
    }
    return false;
}

void PlaylistOperator(int operation, UserClass* user) {

	Playlist* playlist = NULL;
	string playlistName;
	string playlistSelection;
	string songName;
	Playlist* bucket = NULL;
	printf("\n");
	switch (operation) {
	case CREATE_PLAYLIST:
		cout << "Enter the name of the playlist you want to create > ";
		playlistName = GetPlaylistName(user);
		insertPlaylist(user, playlistName, createPlaylist(user));
		break;

	case ADD_TO_PLAYLIST:
		cout << "Enter the name of the playlist you want to add a song to > ";
		playlistName = GetPlaylistName(user);
		if (isValidPlaylist(user, playlistName) == false) {
			PrintError(PLAYLIST_DOES_NOT_EXIST);
			return;
		}

		printf("Enter the name of the song you want to add > ");

		bucket = searchForPlaylist(user, playlistName);
		AddSongNodeToPlaylist(user, &bucket, user->GetSongname());
		break;


	case REMOVE_FROM_PLAYLIST:
		cout << "Enter the name of the playlist you want to remove a song from > ";
		playlistName = GetPlaylistName(user);
		if (isValidPlaylist(user, playlistName) == false) {
			PrintError(PLAYLIST_DOES_NOT_EXIST);
			return;
		}
		printf("Enter the name of the song you want to remove > ");
		DeleteSongFromPlaylist(user, user->GetSongname(), playlistName);
		break;
	case DISPLAY_PLAYLIST:
		printf("Enter the name of the playlist to display > ");
		playlistName = GetPlaylistName(user);
		if (!isValidPlaylist(user, playlistName))
		{
			PrintError(PLAYLIST_DOES_NOT_EXIST);
		}
		else
		{ 
			printPlaylist(user, playlistName);
		}
		break;

	case DISPLAY_ALL_PLAYLISTS:
		printAllPlayLists(user);
		break;

	case DELETE_PLAYLIST:
		cout << "Enter the name of the playlist you want to delete > ";
		playlistName = GetPlaylistName(user);
		if (isValidPlaylist(user, playlistName) == false) {
			PrintError(PLAYLIST_DOES_NOT_EXIST);
			return;
		}

		deletePlaylist(user, playlistName);
		break;


	case ADD_PLAYLIST_TO_QUEUE:
		cout << "Enter the name of the playlist you want to add to the queue > ";
		playlistName = GetPlaylistName(user);
		bucket = searchForPlaylist(user, playlistName);
		if (isValidPlaylist(user, playlistName) == false) {
			return;
		}
		addPlaylistToQueue(user, bucket);
		break;


	case ADD_SONG_TO_QUEUE:
		cout << "Enter the name of the song you want to add to the queue > ";
		EnQueue(user, user->GetSongname());
		break;
	}
}


void printAllPlayLists(UserClass* user)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (user->playlists->table[i] != NULL)
		{
			printPlaylist(user, user->playlists->table[i]->playlistName);
		}
	}
}


Playlist* createPlaylist(UserClass* user) {
	if (isMemoryError(user->playlists)) {
		exit(EXIT_FAILURE);
	}

	Playlist* newPlaylist = new Playlist;
	if (isMemoryError(newPlaylist)) {
		exit(EXIT_FAILURE);
	}

	newPlaylist->next = NULL;
}

void AddSongNodeToPlaylist(UserClass* user, Playlist** head, string songName) {
	if ((*head)->songName == "") {
		(*head)->songName = songName;
		return;
	}
	Playlist* newPlaylist = new Playlist;
	if (isMemoryError(newPlaylist)) {
		exit(EXIT_FAILURE);
	}
	if (SearchForSong(user, songName) == NULL) {
		return;
	}
	newPlaylist->songName = songName;
	newPlaylist->next = NULL;

	if (*head == NULL) {
		*head = newPlaylist;
		return;
	}
	Playlist* current = *head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newPlaylist;
}

void checkAndLoadPlaylists(UserClass* user)
{
	string playListName;
	if (FileExists(user, "playlists.txt"))
	{
		string filePath = user->GetDirectory() + "playlists.txt";
		ifstream file(filePath);
		if (!file)
		{
			cerr << "Error: Unable to open file." << endl;
			return;
		}

		string songName;

		while (getline(file, songName))
		{
			if (songName == "")
			{
				continue;
			}

			if (strcmp(songName.c_str() + songName.length() - 4, ".mp3") != 0)
			{
				playListName = songName;
				insertPlaylist(user, playListName, createPlaylist(user));
			}
			else 
			{
				AddSongNodeToPlaylist(user, &user->playlists->table[GenerateHash(playListName)]->playlist, songName);
			}
		}
		file.close();
		return;
	}
}

void storePlayListsInTextFile(UserClass* user) 
{
	ofstream file(user->GetDirectory() + "playlists.txt");
	if (!file) 
	{
		return;
	}

	int index = 0;
	PlaylistKvp* bucket;
	Playlist* currentSong;

	for (index = 0; index < SIZE; index++)
	{
		bucket = user->playlists->table[index];
		if (bucket != NULL)
		{
			file << bucket->playlistName;
			file << '\n';

			currentSong = bucket->playlist;
			while (currentSong != NULL)
			{
				file << currentSong->songName;
				file << '\n';
				currentSong = currentSong->next;
			}
		}
	}
	file.close();

	if (file.fail()) {
		PrintError(MEM_ERROR);
	}
}