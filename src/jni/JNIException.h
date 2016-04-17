//
// Created by ranger on 17.04.16.
//

#ifndef VABAMORF_JNIEXCEPTION_H
#define VABAMORF_JNIEXCEPTION_H

#include <jni.h>

class JNIException {

public:
	static void LinguisticException(JNIEnv *env, const char *msg);

};


#endif //VABAMORF_JNIEXCEPTION_H
