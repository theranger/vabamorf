
#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"
#include "ArrayList.cpp"
#include "Sentence.h"

static void jvabamorf_handle_results(CFSArray<CMorphInfos> &results, Sentence &sentence) {
	for(ssize_t i = 0; i < results.GetSize(); i++) {
		wprintf(L"----------- Result %ld [%ls] ------------\n", i, results[i].m_szWord.GetString());
		for (ssize_t j = 0; j < results[i].m_MorphInfo.GetSize(); j++) {
			CMorphInfo info = results[i].m_MorphInfo[j];
			wprintf(L"%ld: root: %ls, ending: %ls, clitic: %ls, form: %ls, partofspeech: %lc\n", j,
					info.m_szRoot.GetString(),
					info.m_szEnding.GetString(),
					info.m_szClitic.GetString(),
					info.m_szForm.GetString(),
					info.m_cPOS);
		}

		String string(sentence.getEnv(), results[i].m_szWord.GetString());
		Word word(sentence.getEnv(), string);
		sentence.addWord(word);
	}
}

static void jvabamorf_analyze_sentence(CLinguistic &linguistic, CDisambiguator &disambiguator, Sentence &sentence) {
	CPTWordArray words;
	PTWSplitBuffer(sentence.toCFSWString(), words);
	CFSArray<CMorphInfos> results = linguistic.AnalyzeSentence(words);
	printf("\n\nPreliminary results:\n");
	printf("====================\n\n");
	jvabamorf_handle_results(results, sentence);

	CFSArray<CMorphInfos> disresults = disambiguator.Disambiguate(results);
	printf("\n\nDisambiguated results:\n");
	printf("======================\n\n");
	jvabamorf_handle_results(disresults, sentence);
}

JNIEXPORT void JNICALL Java_ee_risk_vabamorf_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring lingFile, jstring disambFile, jobject corpus) {
	CLinguistic linguistic;
	CDisambiguator disambiguator;

	ArrayList<Sentence> arrayList(env, corpus);
	const char *nLingFile = env->GetStringUTFChars(lingFile, NULL);
	const char *nDisambFile = env->GetStringUTFChars(disambFile, NULL);

	try {
		linguistic.Open(nLingFile);
		disambiguator.Open(nDisambFile);

		for (ssize_t i = 0; i < arrayList.getSize(); i++) {
			Sentence sentence = arrayList.get(i);
			jvabamorf_analyze_sentence(linguistic, disambiguator, sentence);
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
	disambiguator.Close();

	release:
	env->ReleaseStringUTFChars(lingFile, nLingFile);
	env->ReleaseStringUTFChars(disambFile, nDisambFile);

}

JNIEXPORT jstring JNICALL Java_ee_risk_vabamorf_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
