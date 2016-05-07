
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"

JNIEXPORT void JNICALL Java_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring corpus, jstring lingFile) {
	try {
		CLinguistic linguistic;

		const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);
		linguistic.Open(nLingFile);

		printf("Analyzing input data\n");

		linguistic.Close();
		env->ReleaseStringUTFChars(lingFile, nLingFile);
	}
	catch (CLinguisticException &ex) {
		JNIException::LinguisticException(env, ex.GetText());
		return;
	}

}

JNIEXPORT jstring JNICALL Java_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
