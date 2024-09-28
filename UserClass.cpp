#include "UserClass.h"


UserClass::UserClass(string newDirectoryPath)
{

	songLibrary = InitializeHashTable();
	playlists = InitializePlaylistTable();
	queue = InititalizeQueue();

	SetDirectory(newDirectoryPath);
	if (checkAndLoadSongLibrary(this) == false) {
		findSongInDirectory(this);
	}
	
	if (GetLoginInfoFromFile() == false) {
		NewUsername();
		NewPassword();
		StoreUsernameToFile(username);
		StorePasswordToFile(password);
		isLoggedIn = true;
	}
	else {
		checkAndLoadPlaylists(this);
		isLoggedIn = false;
	}
}


UserClass::~UserClass()
{
	storePlayListsInTextFile(this);
	printf("\n Powering off MP3-Player-2000... \n");
	freePlaylists(this);
	freeQueue(this);
	freeList(this);
}


bool UserClass::GetLoginInfoFromFile(void)
{
	ifstream file(directoryPath + "UserAccounts.txt");
	string line;
	while (getline(file, line))
	{
		SetUsername(line);
		getline(file, line);
		SetPassword(line);
		return true;
	}
	return false;
}


// ACCESSORS


string UserClass::GetDirectory(void)
{
	return directoryPath;
}


string UserClass::GetUsername(void)
{
	return username;
}


string UserClass::GetPassword(void)
{
	return password;
}


// MUTATORS


bool UserClass::SetUsername(string newUsername)
{
	bool status = true;
	if (newUsername == "X")
	{
		return false;
	}
	if (newUsername.length() >= MAX_LOGGIN_LENGTH)
	{
		PrintErrorUI(OVER_FLOW, newUsername);
		status = false;
	}
	else if (newUsername.length() <= MIN_LOGGIN_LENGTH)
	{
		PrintErrorUI(UNDER_FLOW, newUsername);
		status = false;
	}
	if (newUsername.find(' ') != string::npos)
	{
		PrintErrorUI(INVALID_USERNAME, newUsername);
		status = false;
	}
	if (status == true)
	{
		username = newUsername;
	}
	else
	{
		return false;
	}
}


bool UserClass::SetPassword(string newPassword)
{
	bool status = true;
	if (newPassword.length() >= MAX_LOGGIN_LENGTH)
	{
		PrintErrorUI(OVER_FLOW, newPassword);
		status = false;
	}
	else if (newPassword.length() <= MIN_LOGGIN_LENGTH)
	{
		PrintErrorUI(UNDER_FLOW, newPassword);
		status = false;
	}
	if (newPassword.find(' ') != string::npos)
	{
		PrintErrorUI(INVALID_USERNAME, newPassword);
		status = false;
	}
	if (status == true)
	{
		password = newPassword;
	}
	else
	{
		return false;
	}
}


bool UserClass::SetDirectory(string directory)
{
	struct stat sb;
	if (stat(directory.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR))
	{
		directoryPath = directory;
		return true;
	}
	else
	{
		perror("Directory does not exist");
		return false;
	}
}


void UserClass::StoreUsernameToFile(string username)
{
	if (isUserAccountFileInDatabase(username))
	{
		cout << "Username already exists in database" << endl;
		return;
	}
	ofstream file(directoryPath + "UserAccounts.txt", ios::app);
	if (file.is_open())
	{
		file << username << endl;
		file.close();
	}
	else
	{
		PrintError(CANNOT_OPEN_FILE);
	}
}


void UserClass::StorePasswordToFile(string password)
{
	ofstream file(directoryPath + "UserAccounts.txt", ios::app);
	if (file.is_open())
	{
		file << password << endl;
		file.close();
	}
	else
	{
		PrintError(CANNOT_OPEN_FILE);
	}
}


bool UserClass::NewUsername(void)
{
	string newUsername;

	while (newUsername != "X") {
		printf("\n--- Creating New Account ---\n");
		printf("Input X to Quit\n");
		printf("Input new Username: ");
		getline(cin, newUsername);
		if (newUsername == "X")
		{
			exit(EXIT_SUCCESS);
		}
		if (SetUsername(newUsername))
		{

			system("CLS");
			return true;
		}
		system("CLS");
		printf("Username must be between 6 and 21 characters and cannot contain spaces\n");
	}
	return false;
}


bool UserClass::NewPassword(void)
{
	string newPassword;
	while (newPassword != "X") {
		printf("\n--- Creating New Account ---\n");
		printf("Input X to Quit\n");
		printf("Input new Password: ");
		getline(cin, newPassword);
		if (newPassword == "X")
		{
			exit(EXIT_SUCCESS);
		}
		if (SetPassword(newPassword))
		{
			return true;
		}
		system("CLS");
		printf("Password must be between 6 and 21 characters and cannot contain spaces\n");
	}
	return false;
}


void UserClass::PrintErrorUI(int ErrorType, string toPrinfIfInvalid)
{
	if (ErrorType == OVER_FLOW)
	{
		printf("\nERROR: %s is too long!! Must be under 21 characters\n", toPrinfIfInvalid.c_str());
	}
	else if (ErrorType == UNDER_FLOW)
	{
		printf("\nERROR: %s is too short!! Must be above 7 characters\n", toPrinfIfInvalid.c_str());
	}
	else if (ErrorType == INVALID_USERNAME)
	{
		printf("\nERROR: %s cannot contain spaces!!\n", toPrinfIfInvalid.c_str());
	}
	else if (ErrorType == CANNOT_OPEN_FILE)
	{
		printf("\nERROR: Cannot open file\n");
	}
	else if (ErrorType == INVALID_CHOICE)
	{
		printf("\nERROR: Invalid choice > %c\n", atoi(toPrinfIfInvalid.c_str()));
	}
	printf("\n");
	system("pause");
}


bool UserClass::isUserAccountFileInDatabase(string username)
{
	ifstream file(directoryPath + "UserAccounts.txt");
	string line;
	while (getline(file, line))
	{
		if (line == username)
		{
			return true;
		}
	}
	return false;
}


void UserClass::KeystrokeHandling(void)
{
	char choice = 0;
	while (true)
	{
		system("cls");
		printf("|MP3 - Player - 2000|\n");
		DisplayCurrentMenu();
		if (ProcessChoice(getch()) == EXIT_PROGRAM)
		{
			return;
		}

	}
}


int UserClass::LoginToAccount(void)
{
	string attemptUsername;
	string attemptPassword;
	string passwordBeingBuilt = "";
	char currentChar = 0;


	while (attemptUsername != "X" && attemptPassword != "X")
	{
		system("CLS");
		printf("\n--- Logging In ---\n");
		printf("Input X to exit\n");
		printf("Input your Username: ");
		getline(cin, attemptUsername);
		if (attemptUsername == "X")
		{
			return false;
		}
		if (attemptUsername != username)
		{
			system("CLS");
			printf("\n  ***ERROR: Cannot find account***\n\n");
			system("pause");
			break;
		}
		system("CLS");
		bool status = false;
		while (status == false)
		{
			currentChar = 0;
			while (attemptPassword != password)
			{
				printf("\n--- Logging In ---\n");
				printf("\nInput X to exit\n");
				printf("Input your Password: %s", passwordBeingBuilt.c_str());
				currentChar = getch();
				system("cls");
				if (currentChar == 'X')
				{
					return false;
				}
				if (currentChar != '\r' && currentChar != '\b')
				{
					passwordBeingBuilt += '*';
					attemptPassword += currentChar;
				}
				if (currentChar == '\b' && passwordBeingBuilt != "")
				{
					passwordBeingBuilt.pop_back();
					attemptPassword.pop_back();
				}
				if (currentChar == '\r' && attemptPassword != password)
				{
					system("cls");
					printf("\n***ERROR: Incorrect Password***\n");
					attemptPassword.clear();
					passwordBeingBuilt.clear();
				}
			}
			if (attemptPassword == password)
			{
				status = true;
			}
		}
		system("CLS");
		printf("*** Succesfully Logged In *** \n");
		return true;
	}
	return false;
}


void UserClass::DisplayCurrentMenu()
{

	switch (currentMenu)
	{

	case MUSIC_PLAYER_MENU:
		DisplayMusicPlayer();
		break;
	case MUSIC_MANAGER_MENU:
		DisplayMusicManager();
		break;
	case PLAYLIST_MANAGER:
		DiplayPlaylistManager();
		break;
	default:
		if (isLoggedIn)
		{
			DisplayMainMenuLoggedIn();
		}
		else if (!isLoggedIn)
		{
			DisplayMainMenuLoggedOut();
		}

	}

}


bool UserClass::SetCurrentMenu(int userChoice)
{
	// check if valid choice
	currentMenu = userChoice;
	return true;
}


int  UserClass::GetCurrentMenu(void)
{
	return currentMenu;
}


void UserClass::DisplayMainMenuLoggedIn(void)
{
	printf("\n--- Logged-In as %s ---\n", username.c_str());
	printf("1. Music Player\n");
	printf("2. Music Manager\n");
	printf("3. Playlist Manager\n");
	printf("4. Logout\n");
}


void UserClass::DisplayMainMenuLoggedOut(void)
{
	printf("\n--- Main Menu ---\n");
	printf("1. Login\n");
	printf("2. Exit\n");
}


void UserClass::DisplayMusicPlayer(void)
{
	printf("\n--- Music Player ---\n");
	printf("1. Play Song\n");
	printf("2. Play Queue\n");
	printf("3. Play Playlist\n");
	printf("4. Display Library\n");
	printf("5. Return to Main Menu\n");
}


void UserClass::DisplayMusicManager(void)
{
	printf("\n--- Music Manager ---\n");
	printf("1. Add Song to Queue\n");
	printf("2. Add Playlist to Queue\n");
	printf("3. Display Queue\n");
	printf("4. Display Library\n");
	printf("5. Delete Song from Library \n");
	printf("6. Return to Main Menu\n");
}


void UserClass::DiplayPlaylistManager(void)
{
	printf("\n--- Playlist Manager ---\n");
	printf("1. Create Playlist\n");
	printf("2. Add Song to Playlist\n");
	printf("3. Delete Song from Playlist\n");
	printf("4. Delete Playlist\n");
	printf("5. Display Playlist\n");
	printf("6. Display All Playlists\n");
	printf("7. Return to Main Menu\n");
}


int UserClass::ProcessChoice(int userChoice)
{
	string userInputString;
	bool found = false;


	if (currentMenu == MUSIC_PLAYER_MENU)
	{
		switch (userChoice)
		{

		case '1':
			printf("\nInput name of song > ");
			userInputString = GetSongname();
			if (SearchForSong(this, userInputString) != NULL)
			{
				playAudio(this, userInputString);
			}
			break;
		case '2':
			PlayQueue(this);
			break;

		case '3':
			printf("\nEnter the name of the playlist you want to play > ");
			userInputString = GetPlaylistName(this);
			PlayPlaylist(this, userInputString);
			break;
		case '4':

			DisplaySongList(this);
			system("pause");
			break;

		case '5':

			currentMenu = 0;
			break;

		default:

			PrintErrorUI(INVALID_CHOICE, to_string(userChoice));

		}
	}


	else if (currentMenu == MUSIC_MANAGER_MENU)
	{
		switch (userChoice)
		{
		case '1':
			PlaylistOperator(ADD_SONG_TO_QUEUE, this);
			break;
		case '2':
			PlaylistOperator(ADD_PLAYLIST_TO_QUEUE, this);
			break;
		case '3':
			DisplayQueue(this);
			break;
		case '4':
			DisplaySongList(this);
			system("pause");
			break;
		case '5':
			printf("\nInput song to delete > ");
			DeleteSongFromLibrary(this, GetSongname());
			break;
		case '6':
			currentMenu = 0;
			break;
		}

	}
	else if (currentMenu == PLAYLIST_MANAGER)
	{
		switch (userChoice)
		{
		case '1':

			PlaylistOperator(CREATE_PLAYLIST, this);
			break;

		case '2':

			PlaylistOperator(ADD_TO_PLAYLIST, this);
			break;

		case '3':

			PlaylistOperator(REMOVE_FROM_PLAYLIST, this);
			break;

		case '4':

			PlaylistOperator(DELETE_PLAYLIST, this);
			break;

		case '5':

			PlaylistOperator(DISPLAY_PLAYLIST, this);

			break;

		case '6':

			PlaylistOperator(DISPLAY_ALL_PLAYLISTS, this);

			break;

		case '7':

			currentMenu = 0;
			break;

		default:

			PrintErrorUI(INVALID_CHOICE, to_string(userChoice));

		}
	}


	else
	{
		if (isLoggedIn)
		{
			switch (userChoice)
			{
			case '1':

				currentMenu = MUSIC_PLAYER_MENU;
				break;

			case '2':

				currentMenu = MUSIC_MANAGER_MENU;
				break;

			case '3':

				currentMenu = PLAYLIST_MANAGER;
				break;

			case '4':

				isLoggedIn = false;
				break;

			default:

				PrintErrorUI(INVALID_CHOICE, to_string(userChoice));

			}
		}
		else if (!isLoggedIn)
		{
			switch (userChoice)
			{
			case '1':
				isLoggedIn = LoginToAccount();
				break;
			case '2':
				return EXIT_PROGRAM;
				break;

			default:

				PrintErrorUI(INVALID_CHOICE, to_string(userChoice));
			}

		}


		return userChoice;
	}
}



string UserClass::GetString()
{

	string stringToReturn;
	bool isValid = false;
	while (!isValid)
	{
		getline(cin, stringToReturn);
		isValid = ValidateRegularString(stringToReturn);
		if (!isValid)
		{
			printf("\nInvalid length\n");
		}
	}
	return stringToReturn;
}

string UserClass::GetSongname()
{
	string songToReturn;
	bool isValid = false;


		getline(cin, songToReturn);
		isValid = ValidateRegularString(songToReturn);
		if (!isValid)
		{
			return "";
		}

	return songToReturn + ".mp3";
}



