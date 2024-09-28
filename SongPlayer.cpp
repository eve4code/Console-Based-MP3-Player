#include "UserClass.h"
//This code containes the logic to play .mp3 files
bool playAudio(UserClass* user, string songName) 
{
	system("cls");
	sf::Music music;
	bool keepPlaying = true;
	if (!music.openFromFile(user->GetDirectory() + songName)) 
	{
		std::cerr << "Failed to load audio file" << std::endl;
		return false;
	}

	music.play();
	cout << "|--------------------<PLAYING>-------------------|" << endl;
	cout << "Press 'p' to pause/play, 'n' to skip, or 'q' to quit." << endl;
	DisplaySongAttributes(user, songName);
	while (music.getStatus() != sf::Music::Stopped) {
		char input = getch();
		switch (input) {
		case 'p':
			if (music.getStatus() == sf::Music::Playing) {
				music.pause();
				system("cls");
				cout << "|--------------------<PAUSED>--------------------|" << endl;
				DisplaySongAttributes(user, songName);
			} else if (music.getStatus() == sf::Music::Paused) {
				music.play();
				{
					system("cls");
					cout << "|--------------------<PLAYING>-------------------|" << endl;
					DisplaySongAttributes(user, songName);
				}
			}
			break;

		case 'n':
			system("cls");
			music.stop();
			return keepPlaying = true;
		case 'q':
			music.stop();
			cout << "Stopping." << endl;
			return keepPlaying = false;
		default:
			cout << "Invalid input. Press 'p' to pause/continue, 'n' to skip, or 'q' to quit." << endl;
			break;
		}
	}
	return true;
}

void PlayPlaylist(UserClass* user, string playlistName)
{
	bool keepPlaying = true;
	Playlist* current = searchForPlaylist(user, playlistName);
	if (current ==  NULL )
	{
		return;
	}
	if (current->songName == "")
	{
		PrintError(EMPTY_PLAYLIST);
		return;
	}

	while (current != NULL && keepPlaying == true)
	{
		keepPlaying = playAudio(user, current->songName);
		current = current->next;
	}
}


void PlayQueue(UserClass* user) {
	if (IsQueueEmpty(user)) {
		PrintError(QUEUE_IS_EMPTY);
		return;
	}
	bool keepPlaying = true;
	
	while (user->queue->Front != NULL && keepPlaying == true)
	{
		keepPlaying = playAudio(user, user->queue->Front->songName);
		DeQueue(user);
	}
}
