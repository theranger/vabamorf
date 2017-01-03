//
// Created by Ivari Horm on 21.05.16.
//

#include "Word.h"
#include "ArrayList.cpp"

Word::Word(JNIEnv *env, String data) :
	env(env),
	morphInfos(env)
{
	jclass wordClass = env->FindClass(JNI_WORD_CLASS);
	jmethodID constructor = env->GetMethodID(wordClass, JNI_WORD_INIT_FN, JNI_WORD_INIT_SG);
	word = env->NewObject(wordClass, constructor, data.toJString());

	jmethodID midSetMorphInfo = env->GetMethodID(wordClass, JNI_WORD_SET_MORPHINFO_FN, JNI_WORD_SET_MORPHINFO_SG);
	env->CallObjectMethod(wordClass, midSetMorphInfo, morphInfos.arrayList);
}

Word::Word(JNIEnv *env, jobject word) :
	env(env),
	morphInfos(env)
{
	this->word = env->NewLocalRef(word);
	jclass wordClass = env->GetObjectClass(word);
	midGetData = env->GetMethodID(wordClass, JNI_WORD_DATA_FN, JNI_WORD_DATA_SG);

	jmethodID midSetMorphInfo = env->GetMethodID(wordClass, JNI_WORD_SET_MORPHINFO_FN, JNI_WORD_SET_MORPHINFO_SG);
	env->CallObjectMethod(wordClass, midSetMorphInfo, morphInfos.arrayList);
}

Word::Word(const Word &other) :
	env(other.env),
	morphInfos(other.morphInfos),
	midGetData(other.midGetData)
{
	word = env->NewLocalRef(other.word);
}

Word &Word::operator=(const Word &other) {
	this->env = other.env;
	this->word = env->NewLocalRef(other.word);
	this->morphInfos = other.morphInfos;
	this->midGetData = other.midGetData;

	return *this;
}

Word::~Word() {
	env->DeleteLocalRef(word);
}

String Word::getData() {
	String string(env, static_cast<jstring>(env->CallObjectMethod(word, midGetData)));
	return string;
}

jobject Word::getObject() {
	return word;
}
