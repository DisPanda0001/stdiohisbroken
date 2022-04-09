//
// APS105 Lab 9
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: Gu Anda
// Student Number: 1008321638
//

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
  char *songName;
  char *artist;
  char *genre;
  struct node *next;
} Node;
// A node in the linked list
typedef struct linkedlist{
  Node* head;
} LinkedList;


// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//
// Function to create new node with input information
Node* createNode(char* SongName, char* Artist, char* Genre){
  Node* NewNode;
  NewNode=(Node*)malloc(sizeof(Node));
  if(NewNode!=NULL){
    NewNode->artist=Artist;
    NewNode->songName=SongName;
    NewNode->genre=Genre; 
    NewNode->next=NULL;
    return NewNode;
  }
  return NULL;
}
// Function to insert at front
bool insertAtFront(LinkedList* list, char* SongName, char* Artist, char* Genre){
  Node* temporary=(Node*)createNode(SongName,Artist,Genre);
  if(temporary==NULL){
    return false;
  }
  temporary->next=list->head;
  list->head=temporary;
  return true;
}
// Function to check if the linked list is empty
bool isEmpty(LinkedList* list){
  return list->head==NULL;
}
// Function to find first match
bool findFirstMatch(LinkedList* list, char* SongName){
  if(isEmpty(list)){
    return false;
  }
  Node* current=list->head;
  if(strcmp(current->songName,SongName)==0){
    return true;
  }
  while(current->next!=NULL&&strcmp(current->next->songName,SongName)!=0){
    current=current->next;
  }
  if(current->next!=NULL){
    return true;
  }
  return false;
}
// Function to insert node
bool insertNode(char* SongName, char* Artist, char* Genre, LinkedList* list){
  Node* current=list->head;
  if(isEmpty(list)){
    list->head=createNode(SongName, Artist, Genre);
    return true;
  }
  else{
    if(strcmp(current->songName,SongName)<0){
      while(current->next!=NULL&&strcmp(current->songName,SongName)<0){
        current=current->next;
      }
      if(current->next!=NULL){
        Node* temp=current->next;
        current->next=createNode(SongName, Artist, Genre);
        current->next->next=temp;
        return true;
      }
      else{
        current->next=createNode(SongName, Artist, Genre);
        return true;
      }
    }
    else{
      insertAtFront(list, SongName, Artist, Genre);
    }
  }
  return false;
}
// Function to delete node
bool deleteNode(char* deleteName, LinkedList* list){
  Node* current=list->head;
  if(strcmp(current->songName,deleteName)!=0){
    while(current->next!=NULL&&strcmp(current->next->songName,deleteName)!=0){
      current=current->next;
    }
    if(current->next!=NULL){
      return false;
    }
    else{
      Node* temp=current->next->next;
      free(current->next);
      current->next=temp;
      return true;
    }
  }
  else{
    Node* NewHead=current->next;
    free(current);
    list->head=NewHead;
    return true;
  }
  return false;
}
// Function to print the music library, if library is not empty
void printMusicLibrary(LinkedList* list){
  if(isEmpty(list)){
    return;
  }
  Node* current=list->head;
  printf("%s\n%s\n%s\n", current->songName, current->artist, current->genre);
  while(current->next!=NULL){
    current=current->next;
    printf("%s\n%s\n%s\n", current->songName, current->artist, current->genre);
  }
  return;
}
// Function to deleteNode from the front
bool deleteFromFront(LinkedList* list){
  Node* current=list->head;
  if(isEmpty(list)){
    return true;
  }
  if(current->next!=NULL){
    Node* newHead=current->next;
    free(current);
    list->head=newHead;
    return true;
  }
  else{
    free(current);
    return true;
  }
  return false;
}
// Declarations of support functions

// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

const int MAX_LENGTH = 1024;

int main(void) {
  // Declare the head of the linked list.
  //   ADD YOUR STATEMENT(S) HERE
  LinkedList* list=(LinkedList*)malloc(sizeof(LinkedList));
  list->head=NULL;
  // Announce the start of the program
  printf("Personal Music Library.\n\n");
  printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
               "P (print), Q (quit).\n");

  char response;
  char input[MAX_LENGTH + 1];
  do {
    inputStringFromUser("\nCommand", input, MAX_LENGTH);

    // Response is the first character entered by user.
    // Convert to uppercase to simplify later comparisons.
    response = toupper(input[0]);

    if (response == 'I') {
      // Insert a song into the linked list.
      // Maintain the list in alphabetical order by song name.
      //   ADD STATEMENT(S) HERE
      char newSong[MAX_LENGTH];
      char newArtist[MAX_LENGTH];
      char newGenre[MAX_LENGTH];
      // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
      char *promptName = "Song name" ;
      char *promptArtist =  "Artist" ;
      char *promptGenre = "Genre" ;
      inputStringFromUser(promptName, newSong, MAX_LENGTH);
      inputStringFromUser(promptArtist, newArtist, MAX_LENGTH);
      inputStringFromUser(promptGenre,newGenre, MAX_LENGTH);
      if(!isEmpty(list)){
        if(!findFirstMatch(list,newSong)){
          insertNode(newSong,newArtist,newGenre,list);
        }
        else{
          songNameDuplicate(newSong);
        }
      }
      else{
        list->head=createNode(newSong,newArtist,newGenre);
      }
    } else if (response == 'D') {
      // Delete a song from the list.
    
      char *prompt = "\nEnter the name of the song to be deleted";

      //   ADD STATEMENT(S) HERE
      char deleteName[MAX_LENGTH];
      inputStringFromUser(prompt, deleteName, MAX_LENGTH);
      
      if(!findFirstMatch(list,deleteName)){
        songNameNotFound(deleteName);
      }
      else{
        if(deleteNode(deleteName,list)){
          songNameDeleted(deleteName);
        }
      }
    
    } else if (response == 'S') {
      // Search for a song by its name.

      char *prompt = "\nEnter the name of the song to search for";

      //   ADD STATEMENT(S) HERE
      char searchSong[MAX_LENGTH];
      inputStringFromUser(prompt, searchSong, MAX_LENGTH);
      if(findFirstMatch(list,searchSong)){
        songNameFound(searchSong);
      }
      else{
        songNameNotFound(searchSong);
      }
    } else if (response == 'P') {
      // Print the music library.
      
      //   ADD STATEMENT(S) HERE
      if(isEmpty(list)){
        printMusicLibraryEmpty();
      }
      else{
        printMusicLibraryTitle();
        printMusicLibrary(list);
      }
    } else if (response == 'Q') {
      ; // do nothing, we'll catch this below
    } else {
      // do this if no command matched ...
      printf("\nInvalid command.\n");
    }
  } while (response != 'Q');

  // Delete the entire linked list.
  //   ADD STATEMENT(S) HERE
  while(!isEmpty(list)){
    deleteFromFront(list);
  }
  // Print the linked list to confirm deletion.
  //   ADD STATEMENT(S) HERE
  printMusicLibrary(list);

  return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
  int i = 0;
  char c;

  printf("%s --> ", prompt);
  while (i < maxStrLength && (c = getchar()) != '\n')
    s[i++] = c;
  s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName) {
  printf("\nA song with the name '%s' is already in the music library.\n"
         "No new song entered.\n",
         songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
  printf("\nThe song name '%s' was found in the music library.\n", songName);
}

// Function to call when a song name was not found in the personal music
// library.
void songNameNotFound(char *songName) {
  printf("\nThe song name '%s' was not found in the music library.\n",
         songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName) {
  printf("\nDeleting a song with name '%s' from the music library.\n",
         songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) { 
  printf("\nThe music library is empty.\n"); 
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) { 
  printf("\nMy Personal Music Library: \n"); 
}

// Add your functions below this line.
//   ADD STATEMENT(S) HERE