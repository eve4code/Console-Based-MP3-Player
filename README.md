# Console-Based MP3 Player

This project is a Console-Based MP3 Player built in **C++** with playlist management, song queuing, and music playback features. It leverages **SFML** to handle audio playback and various data structures to manage playlists and song queues efficiently. Created by Luke Alkema, Jacob Atienza, Dylan Shouldice.

## Features
- **Play MP3 Files**: Play songs from your local directory.
- **Playlist Management**: Create, add, remove songs from playlists.
- **Queue Support**: Add playlists and individual songs to a play queue.
- **Playback Controls**: Play, pause, skip, and stop songs.

## Data Structures
- **Song Queue**: A queue data structure to manage song playback order.
- **Playlist Hash Table**: A hash table to store and quickly retrieve playlists.
- **Playlist Linked List**: A linked list structure to manage the songs within each playlist.

## Installation Instructions
- **Requires Visual Studio 2022 with C/C++ Desktop Development environment installed:**
### Clone the Repository
Clone the repository to your local machine by running:

```bash
git clone <https://github.com/jacob-atienza/Console-Based-MP3-Player>
cd <repository-folder>
```
## Usage
### Playlist Management
- **Create a playlist, add songs, remove songs from playlists**: Add a new playlist, Add song to a playlist
### Queue Songs
- **Queue up songs for continuous playback**:
Add song to queue
Controls
Use the following controls during playback:
Press p to pause/play.
Press n to skip to the next song.
Press q to quit playback.

### Adding Songs
- **Downloading Songs:**
- If you would like to add your own music you need to delete the songlibrary.txt file in the Presentation
- This will prompt you to enter information about the songs you have in that folder.

### Playing Songs
- **Song Name**: The name of the mp3 file in your song directory

### Logging In
- **Creating An Account**: If the account file doesnt exist, you will be prompted to create an account.
- You need to remember your login information because you will have to login with it later
- **Logging In**: You have to use the username and password you created previously
