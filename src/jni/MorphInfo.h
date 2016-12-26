//
// Created by Ivari Horm on 26.12.16.
//

#ifndef VABAMORF_MORPHINFO_H
#define VABAMORF_MORPHINFO_H

#include <jni.h>
#include "String.h"

#define JNI_MORPHINFO_CLASS "ee/risk/vabamorf/model/MorphInfo"
#define JNI_MORPHINFO_SG "L" JNI_MORPHINFO_CLASS ";"

class MorphInfo {

	friend class Word;

public:
	#define JNI_MORPHINFO_INIT_FN "<init>"
	#define JNI_MORPHINFO_INIT_SG "()V"
	MorphInfo(JNIEnv *env);

	virtual ~MorphInfo();


	#define JNI_MORPHINFO_SET_ROOT_FN "setRoot"
	#define JNI_MORPHINFO_SET_ROOT_SG "(" JNI_STRING_SG ")V"
	void setRoot(const String &root);

	#define JNI_MORPHINFO_SET_ENDING_FN "setEnding"
	#define JNI_MORPHINFO_SET_ENDING_SG "(" JNI_STRING_SG ")V"
	void setEnding(const String &ending);

	#define JNI_MORPHINFO_SET_CLITIC_FN "setClitic"
	#define JNI_MORPHINFO_SET_CLITIC_SG "(" JNI_STRING_SG ")V"
	void setClitic(const String &clitic);

	#define JNI_MORPHINFO_SET_FORM_FN "setForm"
	#define JNI_MORPHINFO_SET_FORM_SG "(" JNI_STRING_SG ")V"
	void setForm(const String &form);

	#define JNI_MORPHINFO_SET_POS_FN "setPos"
	#define JNI_MORPHINFO_SET_POS_SG "(" JNI_STRING_SG ")V"
	void setPos(const String &pos);


private:
	JNIEnv *env;
	jobject morphInfo;
	jmethodID midSetRoot;
	jmethodID midSetEnding;
	jmethodID midSetClitic;
	jmethodID midSetForm;
	jmethodID midSetPos;
};


#endif //VABAMORF_MORPHINFO_H
