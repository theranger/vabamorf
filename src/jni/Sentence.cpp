//
// Created by Ivari Horm on 21.05.16.
//

#include "Sentence.h"
#include "ArrayList.cpp"


Sentence::Sentence(JNIEnv *env, jobject sentence) :
		words(env, env->CallObjectMethod(
				sentence,
				env->GetMethodID(env->GetObjectClass(sentence), JNI_SENTENCE_WORDS_FN, JNI_SENTENCE_WORDS_SG)
		))
{
}
