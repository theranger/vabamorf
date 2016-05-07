
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"

JNIEXPORT void JNICALL Java_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring corpus, jstring lingFile) {
	CLinguistic linguistic;
	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);
	const char *nCorpus = env->GetStringUTFChars(corpus, NULL);
	CFSVar cfsCorpus(nCorpus);

	try {
		linguistic.Open(nLingFile);
		CFSArray<CMorphInfo> results = linguistic.Analyze(cfsCorpus.GetWString());
		linguistic.Close();

		env->ReleaseStringUTFChars(lingFile, nLingFile);
		env->ReleaseStringUTFChars(corpus, nCorpus);

		for(ssize_t pos = 0; pos < results.GetSize(); pos++) {
			wprintf(L"root=%ls, pos=%lc, form=%ls, ending=%ls, clitic=%ls",
					results[pos].m_szRoot.GetString(),
					results[pos].m_cPOS,
					results[pos].m_szForm.GetString(),
					results[pos].m_szEnding.GetString(),
					results[pos].m_szClitic.GetString()
			);
		}
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
