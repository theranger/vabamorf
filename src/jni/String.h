//
// Created by The Ranger on 29.10.16.
//

#ifndef VABAMORF_STRING_H
#define VABAMORF_STRING_H

#include <jni.h>
#include <string>

#define JNI_STRING_CLASS "java/lang/String"
class String {

public:
	#define JNI_STRING_SG "L" JNI_STRING_CLASS ";"
	String(JNIEnv *env, jstring string);
	String(JNIEnv *env, const std::string &string);
	String(JNIEnv *env, const std::wstring &string);
	String(JNIEnv *env, wchar_t character);

	String(const String &other);
	String& operator=(const String &other);
	virtual ~String();

	std::string toString() const;
	jstring toJString() const;

private:
	JNIEnv *env;
	jstring string;

};


#endif //VABAMORF_STRING_H
