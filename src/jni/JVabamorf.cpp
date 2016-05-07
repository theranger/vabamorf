
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"

JNIEXPORT void JNICALL Java_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring corpus, jstring lingFile) {
	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);

	try {
		CLinguistic linguistic;
		linguistic.Open(nLingFile);

		printf("Analyzing input data\n");

		linguistic.Close();
		env->ReleaseStringUTFChars(lingFile, nLingFile);
	}
	catch (CLinguisticException &ex) {
		if (ex.m_lMajor == CLinguisticException::MAINDICT && ex.m_lMinor == CLinguisticException::UNDEFINED) {
			JNIException::LinguisticException(env, "File %s not found", nLingFile);
			return;
		}

		JNIException::LinguisticException(env, "Unknown error: file=%s, major=%ld, minor=%ld", nLingFile, ex.m_lMajor, ex.m_lMinor);
		return;
	}

}

JNIEXPORT jstring JNICALL Java_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
