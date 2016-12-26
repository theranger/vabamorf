//
// Created by Ivari Horm on 21.05.16.
//

#include "Word.h"

Word::Word(JNIEnv *env, String data) {
	this->env = env;

	jclass wordClass = env->FindClass(JNI_WORD_CLASS);
	jmethodID constructor = env->GetMethodID(wordClass, JNI_WORD_INIT_FN, JNI_WORD_INIT_SG);
	word = env->NewObject(wordClass, constructor, data.toJString());
	midAddMorphInfo = env->GetMethodID(wordClass, JNI_WORD_ADD_MORPHINFO_FN, JNI_WORD_ADD_MORPHINFO_SG);
}

Word::Word(JNIEnv *env, jobject word) {
	this->env = env;
	this->word = word;

	jclass wordClass = env->GetObjectClass(word);
	midGetData = env->GetMethodID(wordClass, JNI_WORD_DATA_FN, JNI_WORD_DATA_SG);
	midAddMorphInfo = env->GetMethodID(wordClass, JNI_WORD_ADD_MORPHINFO_FN, JNI_WORD_ADD_MORPHINFO_SG);
}

Word::Word(const Word &other) :
	env(other.env),
	word(other.word),
	midGetData(other.midGetData),
	midAddMorphInfo(other.midAddMorphInfo)
{
	env->NewLocalRef(word);
}

Word &Word::operator=(const Word &other) {
	this->env = other.env;
	this->word = other.word;
	this->midGetData = other.midGetData;
	this->midAddMorphInfo = other.midAddMorphInfo;
	env->NewLocalRef(word);

	return *this;
}

Word::~Word() {
	env->DeleteLocalRef(word);
}

String Word::getData() {
	String string(env, static_cast<jstring>(env->CallObjectMethod(word, midGetData)));
	return string;
}

void Word::addMorphInfo(const MorphInfo &morphInfo) {
	env->CallObjectMethod(word, midAddMorphInfo, morphInfo.morphInfo);
}
