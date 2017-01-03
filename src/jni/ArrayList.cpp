//
// Created by Ivari Horm on 21.05.16.
//

#include "ArrayList.h"
#include "Word.h"
#include "MorphInfo.h"

template <typename T>
ArrayList<T>::ArrayList(JNIEnv *env) {
	this->env = env;

	if (env == NULL) fprintf(stderr, "ENV is null!\n");

	fprintf(stderr, "Finding array list class...");
	jclass arrayClass = env->FindClass(JNI_ARRAY_LIST_CLASS);
	if (arrayClass) fprintf(stderr, " found!\n");

	jmethodID constructor = env->GetMethodID(arrayClass, JNI_ARRAY_LIST_INIT_FN, JNI_ARRAY_LIST_INIT_SG);
	arrayList = env->NewObject(arrayClass, constructor);
	midSize = env->GetMethodID(arrayClass, "size", "()I");
	midGet = env->GetMethodID(arrayClass, "get", "(I)Ljava/lang/Object;");
	midAdd = env->GetMethodID(arrayClass, "add", "(Ljava/lang/Object;)Z");
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &other) :
	env(other.env),
	elements(other.elements),
	midSize(other.midSize),
	midGet(other.midGet),
	midAdd(other.midAdd)
{
	this->arrayList = env->NewLocalRef(other.arrayList);
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other) {
	this->env = other.env;
	this->elements = other.elements;
	this->arrayList = env->NewLocalRef(other.arrayList);
	this->midSize = other.midSize;
	this->midGet = other.midGet;
	this->midAdd = other.midAdd;

	return *this;
}

template <typename T>
ArrayList<T>::~ArrayList() {
	env->DeleteLocalRef(arrayList);
}

template <typename T>
ssize_t ArrayList<T>::getSize() {
	return env->CallIntMethod(arrayList, midSize);
}

template <typename T>
T ArrayList<T>::get(ssize_t id) {
	jobject obj = env->CallObjectMethod(arrayList, midGet, id);
	return T(env, obj);
}

template <typename T>
void ArrayList<T>::add(T element) {
	elements.push_back(element);
	env->CallObjectMethod(arrayList, midAdd, element.getObject());
}

template class ArrayList<MorphInfo>;
template class ArrayList<Word>;
