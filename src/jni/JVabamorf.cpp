
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"
#include "ArrayList.cpp"
#include "Sentence.h"

JNIEXPORT void JNICALL Java_ee_risk_vabamorf_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring lingFile, jobject corpus) {
	CLinguistic linguistic;
	ArrayList<Sentence> arrayList(env, corpus);
	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);
	CFSVar cfsCorpus;

	printf("Sentence count: %ld\n", arrayList.getSize());
	for (ssize_t i = 0; i < arrayList.getSize(); i++) {
		Sentence sentence = arrayList.get(i);
		ArrayList<Word> words = sentence.words;
		printf("Word count: %ld\n", words.getSize());

		for (ssize_t j = 0; j < words.getSize(); j++) {
			Word word = words.get(j);
			printf("Word data: %s", word.getData().c_str());
		}
	}


	try {
		linguistic.Open(nLingFile);
		CFSArray<CMorphInfo> results = linguistic.Analyze(cfsCorpus.GetWString());
		linguistic.Close();

		env->ReleaseStringUTFChars(lingFile, nLingFile);

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

JNIEXPORT jstring JNICALL Java_ee_risk_vabamorf_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
