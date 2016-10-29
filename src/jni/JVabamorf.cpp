
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"
#include "ArrayList.cpp"
#include "Sentence.h"

static void jvabamorf_handle_results(CFSArray<CMorphInfos> &results, Sentence &sentence) {
	for(ssize_t i = 0; i < results.GetSize(); i++) {
		wprintf(L"Handling result %ld [%ls]: ", i, results[i].m_szWord.GetString());
		for (ssize_t j = 0; j < results[i].m_MorphInfo.GetSize(); j++) {
			wprintf(L"%ld: %ls ", j, results[i].m_MorphInfo[j].m_szRoot.GetString());
		}
		printf("\n");

		String string(sentence.getEnv(), results[i].m_szWord.GetString());
		Word word(sentence.getEnv(), string);
		sentence.addWord(word);
	}
}

static void jvabamorf_analyze_sentence(CLinguistic &linguistic, Sentence &sentence) {
	CPTWordArray words;
	PTWSplitBuffer(sentence.toCFSWString(), words);
	CFSArray<CMorphInfos> results = linguistic.AnalyzeSentence(words);
	jvabamorf_handle_results(results, sentence);
}

JNIEXPORT void JNICALL Java_ee_risk_vabamorf_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring lingFile, jobject corpus) {
	CLinguistic linguistic;
	ArrayList<Sentence> arrayList(env, corpus);
	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);

	try {
		linguistic.Open(nLingFile);
		for (ssize_t i = 0; i < arrayList.getSize(); i++) {
			Sentence sentence = arrayList.get(i);
			jvabamorf_analyze_sentence(linguistic, sentence);
		}

		goto cleanup;
	}
	catch (CLinguisticException &ex) {
		if (ex.m_lMajor == CLinguisticException::MAINDICT && ex.m_lMinor == CLinguisticException::UNDEFINED) {
			JNIException::LinguisticException(env, "File %s not found", nLingFile);
			goto release;
		}

		JNIException::LinguisticException(env, "Unknown error: file=%s, major=%ld, minor=%ld", nLingFile, ex.m_lMajor, ex.m_lMinor);
		goto cleanup;
	}

	cleanup:
	linguistic.Close();

	release:
	env->ReleaseStringUTFChars(lingFile, nLingFile);

}

JNIEXPORT jstring JNICALL Java_ee_risk_vabamorf_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
