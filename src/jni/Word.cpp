//
// Created by Ivari Horm on 21.05.16.
//

#include "Word.h"

Word::Word(JNIEnv *env, jobject word) {
	this->env = env;
	this->word = word;

	jclass wordClass = env->GetObjectClass(word);
	midGetData = env->GetMethodID(wordClass, "getData", "()Ljava/lang/String;");
}

std::string Word::getData() {
	jstring string = static_cast<jstring>(env->CallObjectMethod(word, midGetData));

	const char *data = env->GetStringUTFChars(string, NULL);
	std::string ret = (data);
	env->ReleaseStringUTFChars(string, data);
	return ret;
}

