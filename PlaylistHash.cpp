#include "UserClass.h"

PlaylistKvp* initializePlaylistKvp(string playlistName, Playlist* playlist) {
    PlaylistKvp* kvp = new PlaylistKvp;
    if (isMemoryError(kvp))
    {
        exit(EXIT_FAILURE);
    }

    kvp->playlistName = playlistName;
    kvp->playlist = playlist;

    return kvp;
}

PlaylistStorage* InitializePlaylistTable(void) {
    PlaylistStorage* hashTable = new PlaylistStorage;
    if (isMemoryError(hashTable))
    {
        exit(EXIT_FAILURE);
	}

    for (int i = 0; i < 50; i++)
    {
        hashTable->table[i] = NULL;
	}

	return hashTable;
}

bool isValidPlaylistName(string playlistName) {
    if (playlistName.length() >= 1 && playlistName.length() <= 20) {
		return true;
	}
    return false;
}

void insertPlaylist(UserClass* user, string playlistName, Playlist* playlist) {
    if (!isValidPlaylistName(playlistName)) {
		PrintError(INVALID_PLAYLIST_NAME);
		return;
	}
    int index = GenerateHash(playlistName);
	PlaylistKvp* kvp = initializePlaylistKvp(playlistName, playlist);
    PlaylistKvp* bucket = user->playlists->table[index];
    if (bucket == NULL) {
        user->playlists->table[index] = kvp;
		return;
	}
    free(kvp);
    PrintError(PLAYLIST_NAME_TAKEN);
    }

void deletePlaylist(UserClass* user, string playlistName) {
    int index = GenerateHash(playlistName);
    PlaylistKvp* bucket = user->playlists->table[index];
    if (bucket == NULL) {
        PrintError(PLAYLIST_DOES_NOT_EXIST);
        return;
    }
    delete bucket->playlist;
    delete bucket;
    user->playlists->table[index] = NULL;
}


Playlist* searchForPlaylist(UserClass* user, string playlistName) 
{
    if (playlistName == "")
    {
        return NULL;
    }
    int index = GenerateHash(playlistName);
    PlaylistKvp* bucket = user->playlists->table[index];
    if (bucket == NULL) 
    {
		PrintError(PLAYLIST_DOES_NOT_EXIST);
		return NULL;
	}
    if (bucket->playlistName == playlistName) 
    {
        return bucket->playlist;
	}
	PrintError(INVALID_PLAYLIST_NAME);
	return NULL;

}		

