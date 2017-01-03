//
// Created by The Ranger on 26.12.16.
//

#include "MorphInfo.h"

MorphInfo::MorphInfo(JNIEnv *env) :
	env(env)
{
	jclass morphInfoClass = env->FindClass(JNI_MORPHINFO_CLASS);
	jmethodID constructor = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_INIT_FN, JNI_MORPHINFO_INIT_SG);
	morphInfo = env->NewLocalRef(env->NewObject(morphInfoClass, constructor));
	midSetRoot = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_ROOT_FN, JNI_MORPHINFO_SET_ROOT_SG);
	midSetEnding = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_ENDING_FN, JNI_MORPHINFO_SET_ENDING_SG);
	midSetClitic = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_CLITIC_FN, JNI_MORPHINFO_SET_CLITIC_SG);
	midSetForm = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_FORM_FN, JNI_MORPHINFO_SET_FORM_SG);
	midSetPos = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_POS_FN, JNI_MORPHINFO_SET_POS_SG);
}

MorphInfo::MorphInfo(JNIEnv *env, jobject morphInfo) :
	env(env)
{
	this->morphInfo = env->NewLocalRef(morphInfo);
	jclass morphInfoClass = env->GetObjectClass(morphInfo);
	midSetRoot = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_ROOT_FN, JNI_MORPHINFO_SET_ROOT_SG);
	midSetEnding = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_ENDING_FN, JNI_MORPHINFO_SET_ENDING_SG);
	midSetClitic = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_CLITIC_FN, JNI_MORPHINFO_SET_CLITIC_SG);
	midSetForm = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_FORM_FN, JNI_MORPHINFO_SET_FORM_SG);
	midSetPos = env->GetMethodID(morphInfoClass, JNI_MORPHINFO_SET_POS_FN, JNI_MORPHINFO_SET_POS_SG);
}

MorphInfo::MorphInfo(const MorphInfo &other):
	env(other.env),
	midSetRoot(other.midSetRoot),
	midSetEnding(other.midSetEnding),
	midSetClitic(other.midSetClitic),
	midSetForm(other.midSetForm),
	midSetPos(other.midSetPos)
{
	morphInfo = env->NewLocalRef(other.morphInfo);
}

MorphInfo &MorphInfo::operator=(const MorphInfo &other) {
	this->env = other.env;
	this->morphInfo = env->NewLocalRef(other.morphInfo);
	this->midSetRoot = other.midSetRoot;
	this->midSetEnding = other.midSetEnding;
	this->midSetClitic = other.midSetClitic;
	this->midSetForm = other.midSetForm;
	this->midSetPos = other.midSetPos;

	return *this;
}

MorphInfo::~MorphInfo() {
	env->DeleteLocalRef(morphInfo);
}

void MorphInfo::setRoot(const String &root) {
	env->CallObjectMethod(morphInfo, midSetRoot, root.toJString());
}

void MorphInfo::setEnding(const String &ending) {
	env->CallObjectMethod(morphInfo, midSetEnding, ending.toJString());
}

void MorphInfo::setClitic(const String &clitic) {
	env->CallObjectMethod(morphInfo, midSetClitic, clitic.toJString());
}

void MorphInfo::setForm(const String &form) {
	env->CallObjectMethod(morphInfo, midSetForm, form.toJString());
}

void MorphInfo::setPos(const String &pos) {
	env->CallObjectMethod(morphInfo, midSetPos, pos.toJString());
}

jobject MorphInfo::getObject() {
	return morphInfo;
}
