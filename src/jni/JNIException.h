//
// Created by ranger on 17.04.16.
//

#ifndef VABAMORF_JNIEXCEPTION_H
#define VABAMORF_JNIEXCEPTION_H

#include <jni.h>
#include <string>

class JNIException {

public:
	static void LinguisticException(JNIEnv *env, const char *msg);

	template<typename ...T>
	static void LinguisticException(JNIEnv *env, const std::string &message, T... args) {
		ssize_t len = snprintf(NULL, 0, message.c_str(), args...);
		char buf[len + 1];	// Include space for terminating NULL
		snprintf(buf, sizeof(buf), message.c_str(), args...);
		LinguisticException(env, buf);
	}
};


#endif //VABAMORF_JNIEXCEPTION_H
