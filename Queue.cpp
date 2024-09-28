#include "UserClass.h"




SongQueue* InititalizeQueue(void)
{
    SongQueue* queue = (SongQueue*)malloc(sizeof(SongQueue));
    if (isMemoryError(queue))
    {
        exit(EXIT_FAILURE);
    }

    queue->Front = NULL;
    queue->Back = NULL;
    return queue;
}

bool IsQueueEmpty(UserClass* user)
{
    return user->queue->Front == NULL;
}

string DeQueue(UserClass* user)
{
    if (IsQueueEmpty(user))
    {
        printf("Queue is Empty");
        return NULL;
    }

    Song* songToDeQueue = user->queue->Front;
    string songNameToDequeue = songToDeQueue->songName;
    user->queue->Front = songToDeQueue->NextSong; // Resetting Head
    free(songToDeQueue); // Free Up Existing Head
    return songNameToDequeue;
}

void DisplayQueue(UserClass* user)
{
    Song* temp = user->queue->Front;
    if (temp == NULL)
    {
        PrintError(QUEUE_IS_EMPTY);
        return;
    }
    system("CLS");
    printf("\n--- Song Queue ---\n");
    while (temp != NULL)
    {
        DisplaySongAttributes(user, temp->songName);
        temp = temp->NextSong;
    } 
    system("pause");
}


void EnQueue(UserClass* user, string songNameToInsert)
{
    if (user->queue == NULL)
    {
        return;
    }

    Song* toEnqueue = AddNewSong(user, songNameToInsert);
    if (toEnqueue == NULL)
    {
        return;
    }
    if (IsQueueEmpty(user))
    {
        user->queue->Front = toEnqueue;
        user->queue->Back = toEnqueue;
    }
    else
    {
        user->queue->Back->NextSong = toEnqueue;
        user->queue->Back = toEnqueue;
    }

}


Song* AddNewSong(UserClass* user, string newSongName)
{
    if ((SearchForSong(user, newSongName)) == NULL)
    {
        return NULL;
    }
    Song* newSong = new Song;
    if (isMemoryError(newSong))
    {
        exit(EXIT_FAILURE);
    }

    newSong->songName = newSongName;
    newSong->NextSong = NULL;
    return newSong;
}


void freeQueue(UserClass* user)
{
    Song* currentSong = user->queue->Front;
    while (currentSong != NULL)
    {
        Song* nextSong = currentSong->NextSong;
        delete currentSong;
        currentSong = nextSong;
    }
    delete user->queue;
}


