
#include <JVabamorf.h>
#include "../proof/proof.h"

JNIEXPORT void JNICALL Java_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring corpus, jstring lingFile) {
	CLinguistic linguistic;

	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);
	linguistic.Open(nLingFile);

	printf("Analyzing input data\n");

	linguistic.Close();
	env->ReleaseStringUTFChars(lingFile, nLingFile);
}

JNIEXPORT void JNICALL Java_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	printf("Vabamorf JNI bridge\n");
}