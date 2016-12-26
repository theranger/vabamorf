//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_SENTENCE_H
#define VABAMORF_SENTENCE_H

#include "../fsc/fsc.h"

#include "Word.h"
#include "ArrayList.h"
#include "String.h"

#define JNI_SENTENCE_CLASS "ee/risk/vabamorf/model/Sentence"
#define JNI_SENTENCE_SG "L" JNI_SENTENCE_CLASS ";"
class Sentence {

public:
	Sentence(JNIEnv *env, jobject sentence);

	Sentence(const Sentence &other);
	Sentence& operator=(const Sentence &other);
	virtual ~Sentence();

	#define JNI_SENTENCE_WORDS_FN "getWords"
	#define JNI_SENTENCE_WORDS_SG "()" JNI_ARRAY_LIST_SG
	ArrayList<Word> words;

	#define JNI_SENTENCE_ADD_WORD_FN "addWord"
	#define JNI_SENTENCE_ADD_WORD_SG "(" JNI_WORD_SG ")V"
	void addWord(const Word &word);

	#define JNI_SENTENCE_DATA_FN "getData"
	#define JNI_SENTENCE_DATA_SG "()" JNI_STRING_SG
	String getData();

	CFSWString toCFSWString();
	JNIEnv * getEnv();

private:
	JNIEnv *env;
	jobject sentence;
	jmethodID midGetData;
	jmethodID midAddWord;
};

#endif //VABAMORF_SENTENCE_H
