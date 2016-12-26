//
// Created by The Ranger on 29.10.16.
//

#include "String.h"

String::String(JNIEnv *env, jstring string) {
	this->env = env;
	this->string = string;
}

String::String(JNIEnv *env, const std::string &string) {
	this->env = env;
	this->string = env->NewStringUTF(string.c_str());
}

String::String(JNIEnv *env, const std::wstring &string) {
	std::string str(string.begin(), string.end());
	this->env = env;
	this->string = env->NewStringUTF(str.c_str());
}

String::String(JNIEnv *env, wchar_t character) : String(env, std::wstring(1, character)) {
}

String::~String() {
	this->env->DeleteLocalRef(string);
}

std::string String::toString() {
	const char *data = env->GetStringUTFChars(string, NULL);
	std::string ret(data);
	env->ReleaseStringUTFChars(string, data);
	return ret;
}


jstring String::toJString() const {
	return string;
}
