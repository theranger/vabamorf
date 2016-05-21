//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_SENTENCE_H
#define VABAMORF_SENTENCE_H


#include "Word.h"
#include "ArrayList.h"

class Sentence {

public:
	Sentence(JNIEnv *env, jobject sentence);

	#define JNI_SENTENCE_WORDS_FN "getWords"
	#define JNI_SENTENCE_WORDS_SG "()Ljava/util/ArrayList;"
	ArrayList<Word> words;
};

#endif //VABAMORF_SENTENCE_H
