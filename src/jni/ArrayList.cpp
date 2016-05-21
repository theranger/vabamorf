//
// Created by Ivari Horm on 21.05.16.
//

#include "ArrayList.h"

template <typename T>
ArrayList<T>::ArrayList(JNIEnv *env, jobject arrayList) {
	this->env = env;
	this->arrayList = arrayList;

	jclass arrayClass = env->GetObjectClass(arrayList);
	midSize = env->GetMethodID(arrayClass, "size", "()I");
	midGet = env->GetMethodID(arrayClass, "get", "(I)Ljava/lang/Object;");
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
