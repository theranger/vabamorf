//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_ARRAYLIST_H
#define VABAMORF_ARRAYLIST_H

#include <jni.h>

#define JNI_ARRAY_LIST_CLASS "java/util/ArrayList"
template <typename T>
class ArrayList {

public:
	#define JNI_ARRAY_LIST_SG "L" JNI_ARRAY_LIST_CLASS ";"
	ArrayList<T>(JNIEnv *env, jobject arrayList);
	ssize_t getSize();
	T get(ssize_t id);

private:
	JNIEnv *env;
	jobject arrayList;
	jmethodID midSize;
	jmethodID midGet;
};

#endif //VABAMORF_ARRAYLIST_H
