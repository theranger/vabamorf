//
// Created by Ivari Horm on 21.05.16.
//

#include "Sentence.h"
#include "ArrayList.cpp"

Sentence::Sentence(JNIEnv *env, jobject sentence) :
	env(env),
	words(env)
{
	this->sentence = env->NewLocalRef(sentence);
	jclass sentenceClass = env->GetObjectClass(sentence);
	midGetData = env->GetMethodID(sentenceClass, JNI_SENTENCE_DATA_FN, JNI_SENTENCE_DATA_SG);

	jmethodID midSetWords = env->GetMethodID(sentenceClass, JNI_SENTENCE_WORDS_FN, JNI_SENTENCE_WORDS_SG);
	env->CallObjectMethod(sentence, midSetWords, words.arrayList);
}

Sentence::Sentence(const Sentence &other) :
	env(other.env),
	words(other.words),
	midGetData(other.midGetData)
{
	sentence = env->NewLocalRef(other.sentence);
}

Sentence &Sentence::operator=(const Sentence &other) {
	this->env = other.env;
	this->sentence = env->NewLocalRef(other.sentence);
	this->words = other.words;
	this->midGetData = other.midGetData;

	return *this;
}

Sentence::~Sentence() {
	env->DeleteLocalRef(sentence);
}

String Sentence::getData() {
	String string(env, static_cast<jstring>(env->CallObjectMethod(sentence, midGetData)));
	return string;
}

CFSWString Sentence::toCFSWString() {
	jstring string = static_cast<jstring>(env->CallObjectMethod(sentence, midGetData));

	const char *data = env->GetStringUTFChars(string, NULL);
	return CFSVar(data).GetWString();
}

JNIEnv *Sentence::getEnv() {
	return env;
}


