#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//struct to store one line
struct outStoryLine_tag {
  char * outStoryLine;  //one line of story
  int outStoryLen;      //length of that line
};
typedef struct outStoryLine_tag outStoryLine_t;

//struct to store the whole story
struct outStory_tag {
  outStoryLine_t * outStory;  //every line of story
  int outStoryLineNum;        //line number
};
typedef struct outStory_tag outStory_t;

//struct to store two "_" position
struct categoryPosition_tag {
  int begin;
  int end;
};
typedef struct categoryPosition_tag categoryPosition_t;

//initialize the file with 2 arguments
FILE * initialFile(int argc, char ** argv);

//initialize the struct of outStory_t which
//describes the story and its line numbers.
outStory_t initializeOutStory();

//initialize cateTrack to record words been used
category_t * initialTrack();

//initialize catarray_t
catarray_t initializeCategory();

//update the struct of outStory_t to store next line.
outStory_t addLine(outStory_t ans);

//Put characters to story, if there is '\n',
//print current story line.
int updateNotInterestedWords(outStory_t * story, char * line, int index);

//get position of two neighboring '_'
categoryPosition_t get_Position(char * line, int index);

//paste the input string to an outStory_t typed input
outStory_t replaceChar(char string, outStory_t input);

//Using position of '_' to get the string between '_'
char * getcateNamefromPosition(char * line, categoryPosition_t position);

//update category_t type with a word which length is len
void updateCateWithLen(category_t * cate, size_t len);

/*
According to catgory name, lookup through wordsList to find a word to
replace.if the wordList == NULL,
    chooseWord will choose cat.else : Convert the catgory to int : if it large than 0 and
        samller than number of words used : backref else
    : lookup through wordsList to find a word to replace,
    and resize wordlist to avoid reusing.
*/
void replaceCategory(char * category,
                     outStory_t * input,
                     catarray_t * word,
                     category_t * track,
                     int reuse);

//delete used word in wordList
void deleteUsedWord(catarray_t * cateWordList, const char * Word, int index);

//check if the catgoryName in wordList
int ifCatgoryInWord(char * catgory, catarray_t * word);

//Pair name and words in input file to make a wordList
catarray_t getCatarray(FILE * f);

//paste categoryName to the wordList
int produceArrName(char * string, catarray_t * categoryList, int n);

//paste categoryWord to the wordList
void produceArrWord(char * string, int isAppearedName, catarray_t * categoryList, int n);

//free outStory_t
void freeAns(outStory_t outStory);

//free catarray_t
void freeCategoryList(catarray_t categoryList);

//free category_t
void freeCateTrack(category_t * category);

#endif
