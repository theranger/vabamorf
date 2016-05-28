//
// Created by Ivari Horm on 21.05.16.
//

#include "Sentence.h"
#include "ArrayList.cpp"
#include "../fsc/fsc.h"


Sentence::Sentence(JNIEnv *env, jobject sentence) :
		words(env, env->CallObjectMethod(
				sentence,
				env->GetMethodID(env->GetObjectClass(sentence), JNI_SENTENCE_WORDS_FN, JNI_SENTENCE_WORDS_SG)
		))
{
	this->env = env;
	this->sentence = sentence;

	jclass sentenceClass = env->GetObjectClass(sentence);
	midGetData = env->GetMethodID(sentenceClass, JNI_SENTENCE_DATA_FN, JNI_SENTENCE_DATA_SG);
}

std::string Sentence::getData() {
	jstring string = static_cast<jstring>(env->CallObjectMethod(sentence, midGetData));

	const char *data = env->GetStringUTFChars(string, NULL);
	std::string ret = (data);
	env->ReleaseStringUTFChars(string, data);
	return ret;
}

CFSWString Sentence::toCFSWString() {
	jstring string = static_cast<jstring>(env->CallObjectMethod(sentence, midGetData));

	const char *data = env->GetStringUTFChars(string, NULL);
	return CFSVar(data).GetWString();
}
