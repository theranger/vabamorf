//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_WORD_H
#define VABAMORF_WORD_H

#include <string>
#include <jni.h>

class Word {

public:
	Word(JNIEnv *env, jobject word);
	std::string getData();

private:
	JNIEnv *env;
	jobject word;
	jmethodID midGetData;

	std::string data;
};


#endif //VABAMORF_WORD_H
