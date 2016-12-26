//
// Created by ranger on 17.04.16.
//

#include "JNIException.h"

#define LINGUISTIC_EX_CLASS "LinguisticException"
#define DISAMBIGUATOR_EX_CLASS "DisambiguatorException"

void JNIException::LinguisticException(JNIEnv *env, const char *msg) {
	jclass c = env->FindClass(LINGUISTIC_EX_CLASS);
	if (c == NULL) return;
	env->ThrowNew(c, msg);
}

void JNIException::DisambiguatorException(JNIEnv *env, const char *msg) {
	jclass c = env->FindClass(DISAMBIGUATOR_EX_CLASS);
	if (c == NULL) return;
	env->ThrowNew(c, msg);
}
