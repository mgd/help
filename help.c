//CSE 1001, Lab 29 Task 1

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
FILE * MASTER_FILE;
int LETTER_ARR[26];

void init_hangman_player(char*);
void fill_arrays();

int
main(int argc, char *argv[1]){
  init_hangman_player(argv[1]);  
  printf("check\n");
  return 0;
}

void 
init_hangman_player(char* word_file){
int i, j;
  MASTER_FILE = fopen(word_file, "r");
  //INITIALIZE 
  for(i=0;i<MWL;i++){
    PMS[i].word_count = 0;
    PMS[i].string_array = NULL;
    //INITIALIZE LETTER FREQUENCY
    for(j=0;j<26;j++){
      PMS[i].letter_freq[j]=0;
    }
  }


  fill_arrays();
  return ;
}

void 
fill_arrays(){
  int i = 0;
  int true_max_len = 0;   // to find the "actual" longest word
  int mem_hog=0;
  int cur_len=0;
  char current_word[MWL]; //current word scaned in, not the other word you pervert


 //////////////////////////////// INITAL SCAN /////////////////////////////////
          ////////////// TOTALS FOR EACH WORD AR FOUND ///////////////////
  while (fscanf(MASTER_FILE, "%s", current_word) == 1) {
    cur_len = strlen(current_word)-1;
    if (cur_len > true_max_len) {
      true_max_len = cur_len;
      printf("char size %d true len %d\n", sizeof(char), true_max_len);
    }
    PMS[cur_len].word_count++;
    printf("word count%d\n",PMS[cur_len].word_count);
  }
    printf("char size %d true len %d\n", sizeof(char), true_max_len);

    true_max_len++;

  /////////////////////////////// MALLOC STRING ARRAY SIZES ///////////////////////////////
  for (i = 0; i < true_max_len; i++) {

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! why doesnt this work ??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
    PMS[i].string_array = (char *) malloc((PMS[i].word_count * (i+2)) * sizeof(char));
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! size word count should = correct size??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
    printf("word count%d, size word count_array%d\n",PMS[i].word_count, sizeof(PMS[i].string_array));
    printf("Correct size%d \n",(PMS[i].word_count * (i+2)) * sizeof(char));
    if(PMS[i].word_count > mem_hog){
      mem_hog = PMS[i].word_count;
    }
  }
}