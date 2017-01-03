//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_WORD_H
#define VABAMORF_WORD_H

#include <string>
#include <jni.h>
#include "String.h"
#include "MorphInfo.h"
#include "ArrayList.h"

#define JNI_WORD_CLASS "ee/risk/vabamorf/model/Word"
#define JNI_WORD_SG "L" JNI_WORD_CLASS ";"
class Word {

	friend class Sentence;

public:
	#define JNI_WORD_INIT_FN "<init>"
	#define JNI_WORD_INIT_SG "(" JNI_STRING_SG ")V"
	Word(JNIEnv *env, String data);
	Word(JNIEnv *env, jobject word);

	Word(const Word &other);
	Word& operator=(const Word &other);
	virtual ~Word();

	#define JNI_WORD_DATA_FN "getData"
	#define JNI_WORD_DATA_SG "()" JNI_STRING_SG
	String getData();

	#define JNI_WORD_SET_MORPHINFO_FN "setMorphInfo"
	#define JNI_WORD_SET_MORPHINFO_SG "(" JNI_ARRAY_LIST_SG ")V"
	ArrayList<MorphInfo> morphInfos;

	jobject getObject();

private:
	JNIEnv *env;
	jobject word;
	jmethodID midGetData;
};


#endif //VABAMORF_WORD_H
