#include <stdio.h>
#include <ctype.h>
#include <limits.h>
//
#define ARRAY_LENGTH 26

int main(void) {
  char ch = getchar();
  static int data[ARRAY_LENGTH];
  int total = 0;

  while (isspace(ch)){
    ch = getchar();
  }

  while (ch != EOF ){
    if (isalpha(ch)){
      char c = tolower (ch);
      int i = c - 'a';
      data[i] ++;
      total ++;
    }
    ch = getchar();
    while (isspace(ch)){
      ch = getchar();
    }
  }
  
  static int most[ARRAY_LENGTH];
  static int least[ARRAY_LENGTH];
  printf("%s    %s    %s", "Character", "Count", "Frequency (%)");
  
  for (int i = 0; i < ARRAY_LENGTH; i++){
    int k = i + 'a';
    char c = k;
    float freq;
    if (total != 0){
      freq = 100.0 * data[i] / total;
    } else {
      freq = 0.000;
    }
    printf("%c         %8d    %13.3f\n", c, data[i], freq);
  }

  int mostc = 0;
  int leastc = INT_MAX;
  for (int i = 0; i < ARRAY_LENGTH; i++){
    if (data[i] > mostc){
      mostc = data[i];
    }
    if (data[i] < leastc){
      leastc = data[i];
    }
  }

  for (int i = 0; i < ARRAY_LENGTH; i++){
    if (data[i] == mostc){  
      most[i] = 1;
    }
    if (data[i] == leastc){
      least[i] = 1;
    }
  }
  printf("Most frequent: ");
  for (int i = 0; i < ARRAY_LENGTH; i++){
    if (most[i] == 1){
      char ch = i + 'a';
      printf("%c ", ch); 
    } 
  }
  printf("\n"); 
  printf("Least frequent: ");
  for (int i = 0; i < ARRAY_LENGTH; i++){
    if (least[i] == 1){
      char ch = i + 'a';
      printf("%c ", ch);
    }
  }
}
