//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_SENTENCE_H
#define VABAMORF_SENTENCE_H

#include "../fsc/fsc.h"

#include "Word.h"
#include "ArrayList.h"

class Sentence {

public:
	Sentence(JNIEnv *env, jobject sentence);

	#define JNI_SENTENCE_WORDS_FN "getWords"
	#define JNI_SENTENCE_WORDS_SG "()Ljava/util/ArrayList;"
	ArrayList<Word> words;

	std::string getData();
	CFSWString toCFSWString();

private:
	JNIEnv *env;
	jobject sentence;
	jmethodID midGetData;

	#define JNI_SENTENCE_DATA_FN "getData"
	#define JNI_SENTENCE_DATA_SG "()Ljava/lang/String;"
};

#endif //VABAMORF_SENTENCE_H
