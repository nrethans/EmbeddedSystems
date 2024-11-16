/*
 *  Helpers.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



bool MatchSubString(const char *msg1, const char *msg2) {
    while (*msg1 != '\0' && *msg2 != '\0' && *msg1 != ' ' && *msg2 != ' ') {
        if (*msg1 != *msg2) {
            return false;
        }
        msg1++;
        msg2++;
    }
    return *msg2 == '\0';
}



/* NextSubString moves a pointer to the next substring in a string */
char* NextSubString(char *msg, bool Print){
    char *index;

    if(msg == NULL){
        return NULL;
    }
    index = strchr(msg, ' ');
    if(!index){
        return NULL;
    }
    if(!Print){
        while(*index == ' ' && *index != '0' && *index != '1'){
            index++;
        }
//        while(*index == ' '){
//            index++;
//        }
    } else {
        if(*index == ' '){
            index++;
        }
    }
    if(!*index){
        return NULL;
    }
    return index;
}
