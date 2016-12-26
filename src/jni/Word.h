//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_WORD_H
#define VABAMORF_WORD_H

#include <string>
#include <jni.h>
#include "String.h"
#include "MorphInfo.h"

#define JNI_WORD_CLASS "ee/risk/vabamorf/model/Word"
#define JNI_WORD_SG "L" JNI_WORD_CLASS ";"
class Word {

	friend class Sentence;

public:
	#define JNI_WORD_INIT_FN "<init>"
	#define JNI_WORD_INIT_SG "(" JNI_STRING_SG ")V"
	Word(JNIEnv *env, String data);
	Word(JNIEnv *env, jobject word);

	virtual ~Word();

	#define JNI_WORD_DATA_FN "getData"
	#define JNI_WORD_DATA_SG "()" JNI_STRING_SG
	String getData();

	#define JNI_WORD_ADD_MORPHINFO_FN "addMorphInfo"
	#define JNI_WORD_ADD_MORPHINFO_SG "(" JNI_MORPHINFO_SG ")V"
	void addMorphInfo(const MorphInfo &morphInfo);

private:
	JNIEnv *env;
	jobject word;
	jmethodID midGetData;
	jmethodID midAddMorphInfo;
};


#endif //VABAMORF_WORD_H
