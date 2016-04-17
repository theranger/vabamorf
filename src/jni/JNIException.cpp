//
// Created by ranger on 17.04.16.
//

#include "JNIException.h"

#define LINGUSTIC_EX_CLASS "LinguisticException"

void JNIException::LinguisticException(JNIEnv *env, const char *msg) {
	jclass c = env->FindClass(LINGUSTIC_EX_CLASS);
	if(c == NULL) return;
	env->ThrowNew(c, msg);
}
