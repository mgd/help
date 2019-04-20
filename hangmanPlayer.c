/*
  // Try JUST GUESSING E for fist letter, increased other ppls score a shit ton
  Authors (group members): Taylor Ertrachter (Leader), Noah Wilson, Matthew Dawson, James Spies
  // Email addresses of group members: wilsonn2018@my.fit.edu,
  Group name: ~Dream Team~

  Course: CSE 2010
  Section: 23

  Description of the overall algorithm: Lit af algorithm. Predicts the date of the end of the world
*/

#include "hangmanPlayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//////////////////////////////////////////////////////
typedef 
struct PRIMARY{
  int word_count;
  int letter_freq[26];
  char *string_array;
}PRIMARY;


typedef 
struct INDEX{
  int word_count;
  int letter_freq[26];
  int *word_int_loc;
}INDEX;

#define MWL 30             // MAX WORD LENGTH, CHANGED ONCE TRUE LENGHT IS FOUND
PRIMARY PMS[MWL];
INDEX TEMP;
FILE * MASTER_FILE;
int *IX_A;
int LETTER_ARR[26];
int IX_FLAG=0;          // INSERTS VALUE OF IX TABLE
int GTL = 0;            // GLOBAL TRUE LENGTH OF CURRENT WORD, USED TO INCREMENT IN ARRAY
char IBG[MWL];          // INITIAL BEST GUESS
char LG = ' ';          // LAST GUESS MADE

void T_FREQ(int);
void init_hangman_player(char*);
void fill_arrays();
//rewrite_letter_freq(char *);
//////////////////////////////////////////////////////

void 
init_hangman_player(char* word_file){
int i, j;

  MASTER_FILE = fopen(word_file, "r");

  //INITIALIZE 
  for(i=0;i<MWL;i++){
    PMS[i].word_count = 0;
    PMS[i].string_array = NULL;
    TEMP.letter_freq[i]=0; // can do later
    //INITIALIZE LETTER FREQUENCY
    for(j=0;j<26;j++){
      PMS[i].letter_freq[j]=0;
    }
  }

  TEMP.word_count = 0; // can do later

  fill_arrays();
  T_FREQ(3);
  return ;
}

void 
fill_arrays(){
  int i = 0;
  int j = 0;
  int k = 0;
  int m = 0;
  int n = 0;
  int flag = 0;
  int l_var = 0;
  int true_max_len = 0;   // to find the "actual" longest word
  int cur_len = 0;        // removed int long
  int pos;
  int mem_hog=0;
  char insert = ' ';
  char temp_l[2];
  char current_word[MWL]; //current word scaned in, not the other word you pervert
  char str[4];

 //////////////////////////////// INITAL SCAN /////////////////////////////////
          ////////////// TOTALS FOR EACH WORD AR FOUND ///////////////////
    while (fscanf(MASTER_FILE, "%s", current_word) == 1){
    cur_len = strlen(current_word)-1;
    if (cur_len > true_max_len) {
      true_max_len = cur_len;
      //printf("char size %d true len %d\n", sizeof(char), true_max_len);
    }
    PMS[cur_len].word_count++;
    //printf("word count%d\n",PMS[cur_len].word_count);
  }
    //printf("char size %d true len %d\n", sizeof(char), true_max_len);
    true_max_len++;

  for (i = 0; i < true_max_len; i++) {
      char *blank = (char *) malloc((PMS[i].word_count * (i+2)) * sizeof(char));
      int j=0;
      PMS[i].string_array = blank;
      blank = NULL;
      free(blank);
    if(PMS[i].word_count > mem_hog){
      mem_hog = PMS[i].word_count;
    }
  }

  /////////////////////////////// CREATE ARRAY TEMP STRUCTS INT ARRAY POINTS TO ///////////////////////////////////////
  IX_A = (int*) malloc(mem_hog*sizeof(int));
  ///////////////////////////// READ WORDS INTO ARRAYS /////////////////////////////
  for(i = 0; i < true_max_len; i++) {
    // Reset the file pointer to the begining position
    fseek(MASTER_FILE, 0, 0);

    flag = 0;
    fscanf(MASTER_FILE, "%s", current_word);
    
    while (flag != -1) {
      if(((cur_len = strlen(current_word)) == (i + 1))){
        //printf("%d\n", cur_len);
        current_word[0] = tolower(current_word[0]);

        strncat(PMS[i].string_array, current_word, i+1);
        //printf("string_Arry %s\n", PMS[i].string_array);

        // PUT FREQ OF LETTERS IN RESPECTIVE INT POSITION
        // COULD MAKE AS ARRAY OF CHARS SINCE VALUE RANGE 0-26
        for (j = 0; j <= i; j++) {
          l_var = current_word[j];
          l_var = l_var - 97;
          PMS[cur_len-1].letter_freq[l_var]++;
        }
      }
      if (fscanf(MASTER_FILE, "%s", current_word) != 1) {
        flag = -1;
      }
    }
  }

  /////////////CREATE *INITAL* BEST GUESS FREQUENCY TABLE//////////////////// 

  for(i=0;i<true_max_len;i++){
    k=0;
      for(j=0;j<26;j++){
          if(PMS[i].letter_freq[j] > k)
            k = j;
      }
      IBG[j] = k+97;
      //printf("i[%d]=%c| ", i, IBG[i]);
  }
  //printf("\n");
}

char guess_hangman_player(char* current_word, bool is_new_word){
}

void 
feedback_hangman_player(bool is_correct_guess, char* current_word){
}

void
T_FREQ(int length){
  int i ,j;

  //while (i < max_word_len){
    printf("Total Words: %d\n",PMS[length].word_count);
    for(j=0;j<26;j++) {
      printf("Struct[%d].letter_freq[%d] letter: %c letter_freq %d \n",i, j, 'a'+j, PMS[length].letter_freq[j]);
    }
    printf("\n");
    i++;
  //}
}
