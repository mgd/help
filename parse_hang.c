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
INDEX TEMP;
FILE * MASTER_FILE;
int *IX_A;
int LETTER_ARR[26];
int IX_FLAG=0;          // INSERTS VALUE OF IX TABLE
int GTL = 0;            // GLOBAL TRUE LENGTH OF CURRENT WORD, USED TO INCREMENT IN ARRAY
char IBG[MWL];          // INITIAL BEST GUESS
char LG = ' ';          // LAST GUESS MADE


void init_hangman_player(char*);
void fill_arrays();
//rewrite_letter_freq(char *);

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
    TEMP.letter_freq[i]=0; // can do later
    //INITIALIZE LETTER FREQUENCY
    for(j=0;j<26;j++){
      PMS[i].letter_freq[j]=0;
    }
  }

  TEMP.word_count = 0; // can do later

  fill_arrays();
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
        printf("string_Arry %s\n", PMS[i].string_array);

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
      printf("i[%d]=%c| ", i, IBG[i]);
  }
  printf("\n");
}


char 
guess_hangman_player(char* current_word, bool is_new_word){
  //Initialize variables
  char best_guess = ' ';
  int i;
  int length = strlen(current_word) - 1; 

  if(is_new_word == true){
  ///////////// RESET GLOBAL POSITION INDEX /////////////
    for(i=0; PMS[length].word_count;i++){
      IX_A[i]=0;
    }
    IX_FLAG= 1;        // 1 IS USED TO MARK LOCATIONS IN THE IX INDEX FOR CORECT VALUES
    GTL = length + 1;    // ACTUAL LENGTH OF WORD USED TO "JUMP"         
    TEMP.word_count = PMS[length].word_count; 
    best_guess=IBG[length];
  }else{
    //best_guess = rewrite_letter_freq(current_word);
  }
  LG = best_guess;
  return best_guess;
}

/*
void 
feedback_hangman_player(bool is_correct_guess, char* current_word){
int key_position = LG-97;
int counter = 0;
int key_value = 0;
int length = strlen(current_word) - 1;
char copy[MWL];
int i=0, k=0;
int repeting = 0;
int offset = 0;
char *sting_head = PMS[length].string_array;


  if(is_correct_guess == true){
    // FIND & MARK GOOD GUESS

    printf("Correct GUESS: %c, posion %d\n", LG, key_position);
    TEMP.letter_freq[key_position] = - 2;

    // CHECK FOR REPETING LETTERS
    for(i=0;i<GTL;i++){
      if(LG = current_word[i])
        repeting++;
    }

    //// WOULD NEED A GLOBAL FLAG HERE AS WOULD ONLY WORK FOR FIRST GUESS
    // CHECK FOR THE LETTER IN THE CORRECT POSITION
    for(i=0;i<TEMP.word_count;i++){
      //!!!!!!!!!!!!!!!!!!NOT SURE HOW TO PROPERLY INDEX THIS HERE!!!!!!!!!!!!!!!!!!!
      if(PMS[length].string_array->(string_array[i]+key_position) == current_word[key_position]){
        
        if(repeting > 1){  
          for(j=0; j<GTL; j++){
            PMS[length].string_array->(string_array[i])
            
          }
        }else{
          // HERE WE ARE SAVING THE "OFFSET" VALUE OF THE STRING LOCATION FROM .string_array
          IX_A[counter] = offset;
          counter++;
        }
      }
      offset = GTL+1;
    }
    
      TEMP.array_loc[counter] = -1;
      // FLAG THE VALUE AS NO LONGER CURRENT GUESS OR AVAILABLE GUESS

      TEMP.letter_freq[key_position] = -2;
    //printf("key posn%d should be -2: %d\n", key_position,  TEMP.letter_freq[key_position]);
    }else{
    // MARK OUT WORD INCORRECT WORD O(1) OP 
    TEMP.letter_freq[best_guess-97] = - 3;

      // 1ST LOOP: USED TO INDEX CORRECT VALUES
      for(i=0;i<TEMP.word_count;i++){    

        // 2nd LOOP: CHECK ALL THE LETTERS FOR THE BAD LETTER
        for(int k=0; k<GTL; k++){
          bad_word = 0;
            // WE CAN SPEED THIS UP TO BREAK WHEN IF IS MET BUT FLAG IS SAFER FOR NOW
            if(key_letter == copy[k]){
              bad_word = 1;
            }
        }
        // CHECK FLAG
        if(bad_word != 1){
            TEMP.array_loc[counter] = TEMP.array_loc[i];
            counter++;
        }
      }
    }
    IX_A[]


    // FOR LOOP SEARCH COMPLETE, SET NEW WORD COUNT TO A NEWLY "SORTED" LENGTH
    TEMP.array_loc[counter]=-1;

    TEMP.word_count = counter;

//////////////////////// IF CORRECT GUESS  ///////////////////////////////////
  return;
}
*/



  


