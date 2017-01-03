//
// Created by Ivari Horm on 21.05.16.
//

#ifndef VABAMORF_ARRAYLIST_H
#define VABAMORF_ARRAYLIST_H

#include <jni.h>
#include <list>

#define JNI_ARRAY_LIST_CLASS "java/util/ArrayList"
#define JNI_ARRAY_LIST_SG "L" JNI_ARRAY_LIST_CLASS ";"
template <typename T>
class ArrayList {

	friend class Sentence;
	friend class Word;

public:
	#define JNI_ARRAY_LIST_INIT_FN "<init>"
	#define JNI_ARRAY_LIST_INIT_SG "()V"
	ArrayList<T>(JNIEnv *env);
	ssize_t getSize();
	T get(ssize_t id);
	void add(T element);

	ArrayList(const ArrayList &other);
	ArrayList& operator=(const ArrayList &other);
	virtual ~ArrayList();

private:
	JNIEnv *env;
	jobject arrayList;
	jmethodID midSize;
	jmethodID midGet;
	jmethodID midAdd;

	std::list<T> elements;
};

#endif //VABAMORF_ARRAYLIST_H
