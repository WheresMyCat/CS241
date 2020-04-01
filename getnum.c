#include "getnum.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// global var
bool at_eof = false; 
bool valid_num = true; 
bool is_negative = false;


static bool in_range(int base, bool negative, long result, int next){
  negative = is_negative;
  if (!negative){ 
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
  else { 
    if (result >= (LONG_MIN + next) / base){
      valid_num = true;
      return true;
    } 
    else {
      valid_num = false;
      return false;
    }
  }
}

bool isnegative(char ch){
  if (ch == '-'){
    is_negative = true;
    return true;
  } 
  else {
    is_negative = false;
    return false;
  }
}


long getnum(void){
  long value = 0;
  int base = 0;
  char ch;
  if ((ch = getchar()) != EOF){
    while (isspace(ch)){
      ch = getchar();
    } 
    isnegative(ch);
    if (is_negative){
      ch = getchar();
    }
    if (isdigit(ch)){ 
      if (ch == '0'){ 
        ch = getchar();
        if (isspace(ch) || ch == EOF){ 
          valid_num = true;
          if (ch == EOF){
            at_eof = true;
          }
          return 0;
        }

        if ((ch == 'b') || (ch == 'B')){
          base = 2;
        }
        else if ((ch == 'x') || (ch == 'X')){ 
           base = 16;
        }
        else if (isdigit(ch)){ 
          base = 8;
          ch = ungetc(ch, stdin);
        }
        else { 
          valid_num = false;
          return 0; 
        }

        if (base != 8){
        ch = getchar();
        if (isspace(ch) || ch == EOF){

          valid_num = false;
          if (ch == EOF){
            at_eof = true;
          }
          return 0;
        }
        ch = ungetc(ch, stdin);
        } 
      }
      else { 
        base = 10;
        ch = ungetc(ch, stdin);
      }
    } 
    else { 
      while(!isspace(ch) && (ch != EOF)){
        ch = getchar();
      }
      if (ch == EOF){
        at_eof = true;
      }
      valid_num = false;
      return 0;
    }
  } 

  else {
    at_eof = true;
    valid_num = true;
    return 0;
  }

  while ((ch = getchar()) != EOF){
    int next = 0;
    if (!isspace(ch)){
      if (isdigit(ch)){ 
        next = ch - '0';

      } 
      else{ 
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
            at_eof = true;
          }
          valid_num = false;
          return 0;
        }
      }
      if (in_range(base, is_negative, value, next) && next > -1 && next < base){
        value = base * value + next;
      }
      else {
        while (!isspace(ch) && (ch != EOF)){
          ch = getchar();
        }
        if (ch == EOF){
          at_eof = true;
        }
        valid_num = false;
        return 0;
      }
    }
    else { 
      return value;
    }
  }
  at_eof = true;
  valid_num = true;
  return 0;
}
