//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_ARRAYLIST_H
#define VABAMORF_ARRAYLIST_H

#include <jni.h>

template <typename T>
class ArrayList {

public:
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
