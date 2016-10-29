//
// Created by Ivari Horm on 21.05.16.
//

#include "Word.h"

Word::Word(JNIEnv *env, String data) {
	this->env = env;

	jclass wordClass = env->FindClass(JNI_WORD_CLASS);
	jmethodID constructor = env->GetMethodID(wordClass, JNI_WORD_INIT_FN, JNI_WORD_INIT_SG);
	word = env->NewObject(wordClass, constructor, data.toJString());
}

Word::Word(JNIEnv *env, jobject word) {
	this->env = env;
	this->word = word;

	jclass wordClass = env->GetObjectClass(word);
	midGetData = env->GetMethodID(wordClass, JNI_WORD_DATA_FN, JNI_WORD_DATA_SG);
}

Word::~Word() {
	env->DeleteLocalRef(word);
}

String Word::getData() {
	String string(env, static_cast<jstring>(env->CallObjectMethod(word, midGetData)));
	return string;
}
