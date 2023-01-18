#include "rand_story.h"
/*
Function: initialize the file with 2 arguments
Input: argc:number of arguments
       argc: arguments
Output: f: file named "argv[1]"
*/
FILE * initialFile(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Expected 2 arguments but got %d", argc);
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open the file: %s", argv[1]);
    exit(EXIT_FAILURE);
  }
  return f;
}

/*
Function: initialize the struct of outStory_t which 
describes the story and its line numbers.

Output: a well initialized struct of outStory_t
*/
outStory_t initializeOutStory() {
  outStory_t ans;
  ans.outStoryLineNum = 1;
  ans.outStory = malloc(sizeof(*ans.outStory));
  ans.outStory[0].outStoryLine = NULL;
  ans.outStory[ans.outStoryLineNum - 1].outStoryLen = 0;
  return ans;
}

/*
Function: initialize cateTrack to record words been used

Output: a category_t type list which record all the words
have been used before
 */
category_t * initialTrack() {
  category_t * cateTrack = malloc(sizeof(*cateTrack));
  cateTrack->words = malloc(sizeof(*cateTrack->words));
  cateTrack->n_words = 0;
  return cateTrack;
}

/*
Function: initialize catarray_t

Output: a catarray_t type
 */
catarray_t initializeCategory() {
  catarray_t categoryList;
  categoryList.n = 1;
  categoryList.arr = malloc(sizeof(*categoryList.arr));
  return categoryList;
}

/*
Function: update the struct of outStory_t to store next
Line.
 */
outStory_t addLine(outStory_t ans) {
  ans.outStoryLineNum++;
  ans.outStory = realloc(ans.outStory, (ans.outStoryLineNum) * sizeof(*ans.outStory));
  ans.outStory[ans.outStoryLineNum - 1].outStoryLine =
      malloc(sizeof(*ans.outStory[ans.outStoryLineNum - 1].outStoryLine));
  ans.outStory[ans.outStoryLineNum - 1].outStoryLen = 0;
  return ans;
}

/*
Function: Put characters to story, if there is '\n', 
          print current story line.
Input: story: outStory_t typed need to accept characters)
       line: Each line in input file;
       index: position of current element;
Output: if there is '\n', return index+1 to work on next story line.
 */
int updateNotInterestedWords(outStory_t * story, char * line, int index) {
  if (line[index] == '\n') {
    *story = replaceChar('\0', *story);  //finish this line and print it
    printf("%s\n", story->outStory[story->outStoryLineNum - 1].outStoryLine);
    index++;
  }
  else {  //update output of this line of story
    *story = replaceChar(line[index++], *story);
  }
  return index;
}

/*
Function: get position of two neighboring '_'
input: line: Each line in input file;
       index: position of current element;
output: The position of current "_" and "_" after it.
*/
categoryPosition_t get_Position(char * line, int index) {
  categoryPosition_t position;
  position.begin = index++;
  while (line[index] != '_') {
    if (line[index] == '\n' || line[index] == '\0') {
      fprintf(stderr, "Lack of _ on the same line");
      exit(EXIT_FAILURE);
    }
    index++;
  }
  position.end = index;
  return position;
}

/*
Function: paste the input string to an outStory_t typed input
Input: String: the string need to be pasted
       input: the outStory_t type should accept string
Output: OutStory_t type.
 */
outStory_t replaceChar(char string, outStory_t input) {
  input.outStory[input.outStoryLineNum - 1].outStoryLine =
      realloc(input.outStory[input.outStoryLineNum - 1].outStoryLine,
              (input.outStory[input.outStoryLineNum - 1].outStoryLen + 1) *
                  sizeof(*input.outStory[input.outStoryLineNum - 1].outStoryLine));
  input.outStory[input.outStoryLineNum - 1]
      .outStoryLine[input.outStory[input.outStoryLineNum - 1].outStoryLen++] = string;
  return input;
}

/*
Function: Using position of '_' to get the string between '_'
Input: line: Each line of input file
       position: position of two '_'
Output: catgory name which is char type
 */
char * getcateNamefromPosition(char * line, categoryPosition_t position) {
  int wordLength = position.end - position.begin - 1;
  int beginTmp = position.begin;
  char * catgory = NULL;
  for (int matchWordIndex = 0; matchWordIndex < wordLength - 1; matchWordIndex++) {
    catgory = realloc(catgory, (matchWordIndex + 1) * sizeof(catgory));
    catgory[matchWordIndex] = line[++beginTmp];
  }
  if (wordLength > 0) {
    catgory = realloc(catgory, (wordLength) * sizeof(catgory));
    catgory[wordLength - 1] = '\0';
  }
  return catgory;
}

/*
Function: update category_t type with a word which length is len
Input:cate: category_t type need to be update
      len: length of word
 */
void updateCateWithLen(category_t * cate, size_t len) {
  if (cate->n_words > 0) {
    cate->words = realloc(cate->words, (cate->n_words + 1) * sizeof(cate->words));
  }
  cate->words[cate->n_words] = malloc((len + 1) * sizeof(*cate->words[cate->n_words]));
  cate->n_words++;
}

/*
Function: According to catgory name, lookup through wordsList to find a word to
          replace.
          if the wordList == NULL, chooseWord will choose cat.
          else: 
	      Convert the catgory to int:
	         if it large than 0 and samller than number of words used:backref
		 else: lookup through wordsList to find a word to replace,
		       and resize wordlist to avoid reusing.
input: catgoary: catgoary name
       input: outStory_t type to accept words
       word: catarray_t wordList
       track: category_t used in backreference
       reuse: if 0, can be resued; else, cannot.
*/
void replaceCategory(char * catgory,
                     outStory_t * input,
                     catarray_t * word,
                     category_t * track,
                     int reuse) {
  if (word == NULL) {
    const char * Word = chooseWord(catgory, word);
    for (size_t i = 0; i < strlen(Word); i++) {
      *input = replaceChar(Word[i], *input);
    }
  }
  else {
    size_t backref = atoi(catgory);
    //for "_x_" if x is a number and range from 1 to track->n_words,
    //it is backreference
    if (backref > 0 && backref <= track->n_words) {
      const char * Word1 = track->words[track->n_words - backref];
      for (size_t i = 0; i < strlen(Word1); i++) {
        *input = replaceChar(Word1[i], *input);
      }
      updateCateWithLen(track, strlen(Word1));  //update trackList
      track->words[track->n_words - 1] = strcpy(track->words[track->n_words - 1], Word1);
    }
    else {
      int index = ifCatgoryInWord(catgory, word);  //check wordList has that catgory
      const char * Word2 = chooseWord(catgory, word);
      for (size_t i = 0; i < strlen(Word2); i++) {
        *input = replaceChar(Word2[i], *input);
      }
      updateCateWithLen(track, strlen(Word2));  //update trackList
      track->words[track->n_words - 1] = strcpy(track->words[track->n_words - 1], Word2);
      if (reuse == 1) {
        deleteUsedWord(word, Word2, --index);  //avoid reuse
      }
    }
  }
  free(catgory);
}

/*
Function: delete used word in wordList
Input: cateWordList:whole word list
       Word:the word need to be delete
       index: index of categoryName
 */
void deleteUsedWord(catarray_t * cateWordList, const char * Word, int index) {
  //find the word and cover it with words after it
  for (size_t i = 0; i < cateWordList->arr[index].n_words - 1; i++) {
    if (cateWordList->arr[index].words[i] == Word) {
      while (i < cateWordList->arr[index].n_words - 1) {
        *cateWordList->arr[index].words[i] = *cateWordList->arr[index].words[i + 1];
        i++;
      }
    }
  }
  //WordList has no word
  if (cateWordList->arr[index].n_words == 0) {
    fprintf(
        stderr, "There has no word being not used in %s", cateWordList->arr[index].name);
    exit(EXIT_FAILURE);
  }
  //Update wordlist
  cateWordList->arr[index].n_words--;
  free(cateWordList->arr[index].words[cateWordList->arr[index].n_words]);
}

/*
Function: check if the catgoryName in wordList
Input: catgory
       word: wordList
 */
int ifCatgoryInWord(char * catgory, catarray_t * word) {
  int j = 0;
  for (size_t i = 0; i < word->n; i++) {
    if (strcmp(catgory, word->arr[i].name) == 0) {
      j = 1 + i;
      i = word->n;
    }
  }
  if (j == 0) {
    fprintf(stderr, "The category is not in words file");
    exit(EXIT_FAILURE);
  }
  return j;
}

/*
Function: Pair name and words in input file to make a wordList
Input: File
Output: Categorylist
*/
catarray_t getCatarray(FILE * f) {
  size_t sz = 0;
  char * line = NULL;
  char * tmp = malloc(sizeof(*tmp));
  char * tmp2 = malloc(sizeof(*tmp2));
  catarray_t categoryList = initializeCategory();
  while (getline(&line, &sz, f) >= 0) {
    int i = 0;
    while (line[i] != ':') {
      if (line[i] == '\n') {
        fprintf(stderr, "Lack of catergory word\n");
        exit(EXIT_FAILURE);
      }
      i++;
    }
    //copy name to tmp
    tmp = realloc(tmp, (i + 1) * sizeof(*tmp));
    int tmplen = i++;
    for (int j = 0; j < i - 1; j++) {
      tmp[j] = line[j];
    }
    tmp[i - 1] = '\0';
    //paste categoryName to the wordList
    int isAppearedName = produceArrName(tmp, &categoryList, tmplen);
    while (line[i] != '\n') {
      i++;
    }
    //copy word to tmp2
    tmp2 = realloc(tmp2, (i - tmplen) * sizeof(*tmp2));
    for (int j = 0; j < i - tmplen - 1; j++) {
      tmp2[j] = line[tmplen + j + 1];
    }
    tmp2[i - tmplen - 1] = '\0';
    //paste categoryword to the wordList
    produceArrWord(tmp2, isAppearedName, &categoryList, i - tmplen - 1);
  }
  categoryList.n--;
  free(tmp);
  free(tmp2);
  free(line);
  assert(fclose(f) == 0);
  return categoryList;
}

/*
Function: paste categoryName to the wordList
Input: string: categoryname
       categorylist: the wordList
       n:length of categoryname (int)
Output: isAppearedname: the index of that categoryname in catarray_t 
 */
int produceArrName(char * string, catarray_t * categoryList, int n) {
  int isAppearedName = 0;
  for (size_t j = 0; j < categoryList->n - 1; j++) {
    if (strcmp(string, categoryList->arr[j].name) == 0) {
      isAppearedName = j + 1;  //find categoryname has appeared in categorylist
      //record that index
    }
  }
  if (isAppearedName == 0) {  //if categoryname is new, update catarray
    if (categoryList->n > 1) {
      categoryList->arr =
          realloc(categoryList->arr, categoryList->n * sizeof(*categoryList->arr));
    }
    categoryList->arr[categoryList->n - 1].name =
        malloc((n + 1) * sizeof(*categoryList->arr[categoryList->n - 1].name));
    categoryList->arr[categoryList->n - 1].n_words = 0;
    categoryList->arr[categoryList->n - 1].words =
        malloc(sizeof(*categoryList->arr[categoryList->n - 1].words));
    categoryList->arr[categoryList->n - 1].name =
        strcpy(categoryList->arr[categoryList->n - 1].name, string);
    isAppearedName = categoryList->n++;
  }
  return --isAppearedName;
}

/*
Function: paste categoryWord to the wordList
Input: string: categoryword
       isAppearedname: the name index of that word
       categorylist: the wordList 
        n:length of categoryword (int)
*/
void produceArrWord(char * string, int isAppearedName, catarray_t * categoryList, int n) {
  //resize categorylist
  categoryList->arr[isAppearedName].words =
      realloc(categoryList->arr[isAppearedName].words,
              (categoryList->arr[isAppearedName].n_words + 1) *
                  sizeof(*categoryList->arr[isAppearedName].words));
  categoryList->arr[isAppearedName].words[categoryList->arr[isAppearedName].n_words] =
      malloc((n + 1) * sizeof(*categoryList->arr[isAppearedName]
                                   .words[categoryList->arr[isAppearedName].n_words]));
  //paste the categoryword
  categoryList->arr[isAppearedName]
      .words[categoryList->arr[isAppearedName].n_words] = strcpy(
      categoryList->arr[isAppearedName].words[categoryList->arr[isAppearedName].n_words],
      string);

  ++categoryList->arr[isAppearedName].n_words;
}

//free outStory_t
void freeAns(outStory_t outStory) {
  for (int i = 0; i < outStory.outStoryLineNum; i++) {
    free(outStory.outStory[i].outStoryLine);
  }
  free(outStory.outStory);
}

//free catarray_t
void freeCategoryList(catarray_t categoryList) {
  for (size_t i = 0; i < categoryList.n; i++) {
    for (size_t j = 0; j < categoryList.arr[i].n_words; j++) {
      if (categoryList.arr[i].words[j] != NULL) {
        free(categoryList.arr[i].words[j]);
      }
    }
    if (categoryList.arr[i].words != NULL) {
      free(categoryList.arr[i].words);
    }
    free(categoryList.arr[i].name);
  }
  free(categoryList.arr);
}

//free category_t
void freeCateTrack(category_t * category) {
  for (size_t i = 0; i < category->n_words; i++) {
    free(category->words[i]);
  }
  free(category->words);
  free(category);
}
