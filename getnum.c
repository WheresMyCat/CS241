#include "getnum.h"

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// global var
bool at_eof = false; //true if EOF encountered before digits
bool valid_num = true; //true if valid then return value
bool is_negative = false;

// return true if adding next in range of long type
static bool in_range(int base, bool negative, long result, int next){
  negative = is_negative;
  if (!negative){ // for  non-negative
    if (result <= (LONG_MAX - next) / base){
      valid_num = true;
      return true;
    }
    else {
     // printf("a ");
      valid_num = false;
      return false;
    }
  } 
  else { // for  negative
    if (result >= (LONG_MIN + next) / base){
      valid_num = true;
      return true;
    } 
    else {
      //printf("b ");
      valid_num = false;
      return false;
    }
  }
}

// check if negative
static bool isnegative(char ch){
  if (ch == '-'){
    is_negative = true;
    return true;
  } 
  else {
    is_negative = false;
    return false;
  }
}

//get a value of number
long getnum(void){
  long value = 0;
  int base = 0;
  char ch;
  if ((ch = getchar()) != EOF){
    while (isspace(ch)){ // read until not whitespace
      ch = getchar();
    } // FIRST CHAR READ
    isnegative(ch);
    if (is_negative){
      ch = getchar();
    }
    if (isdigit(ch)){ // first char is digit
      if (ch == '0'){ // binary / hex / octal / '0'
        // SECOND CHAR READ
        ch = getchar();
        if (isspace(ch) || ch == EOF){ // decimal '0'
          valid_num = true;
          if (ch == EOF){
            //printf("1 ");
            at_eof = true;
          }
          return 0;
        }

        if ((ch == 'b') || (ch == 'B')){ // binary 
          base = 2;
        }
        else if ((ch == 'x') || (ch == 'X')){ // hex
           base = 16;
        }
        else if (isdigit(ch)){ // octal
          base = 8;
          ch = ungetc(ch, stdin);
        }
        else { // invalid
          //printf("c ");
          valid_num = false;
          return 0; 
        }
        // check if THIRD CHAR exits
        if (base != 8){
        ch = getchar();
        if (isspace(ch) || ch == EOF){
          //printf("d ");
          valid_num = false;
          if (ch == EOF){
            //printf("2 ");
            at_eof = true;
          }
          return 0;
        }
        ch = ungetc(ch, stdin);
        } //unread
      }
      else { // decimal
        //printf("decimal ");
        base = 10;
        ch = ungetc(ch, stdin);
      }
    } 
    else { // first char not digit invalid
      while(!isspace(ch) && (ch != EOF)){
        ch = getchar();
      }
      if (ch == EOF){
        //printf("3 ");
        at_eof = true;
      }
      //printf("e ");
      valid_num = false;
      return 0;
    }
  } // second char read

  else {
    //printf("4 ");
    at_eof = true;
    valid_num = true;
    return 0;
  }

  while ((ch = getchar()) != EOF){
    //printf("%c", ch);
    int next = 0;
    if (!isspace(ch)){
      if (isdigit(ch)){ // building value of binary / octal / decimal
        next = ch - '0';
       // printf("%d ", next);
      } 
      else{ // building value of hex
        if (ch >= 'A' && ch <= 'F'){
          next = ch - 'A' + 10;
        }
        else if (ch >= 'a' && ch <= 'f'){
          next = ch - 'a' + 10;
        }
        else {
          while (!isspace(ch) && (ch != EOF)){
            ch = getchar();
          }
          if (ch == EOF){
            //printf("5 ");
            at_eof = true;
          }
          //printf("f ");
          valid_num = false;
          return 0;
        }
      }
      // get next and check in_range
      if (in_range(base, is_negative, value, next) && next > -1 && next < base){
       // printf("next: %d ", next);
        value = base * value + next;
      }
      else {
        while (!isspace(ch) && (ch != EOF)){
          ch = getchar();
        }
        if (ch == EOF){
          //printf("6 ");
          at_eof = true;
        }
        //printf("h ");
        valid_num = false;
        return 0;
      }
    }
    else { // whitespace
      //printf("value: %ld base: %d eof: %d  result: ", value, base, at_eof);
      return value;
    }
  }
  //printf ("7 ");
  at_eof = true;
  valid_num = true;
  return 0;
}
