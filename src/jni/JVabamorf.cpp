#include <JVabamorf.h>
#include "../proof/proof.h"
#include "JNIException.h"
#include "Sentence.h"

static void jvabamorf_handle_results(JNIEnv *env, CFSArray<CMorphInfos> &results, Sentence &sentence) {

	for (ssize_t i = 0; i < results.GetSize(); i++) {
		String string(env, results[i].m_szWord.GetString());
		Word word(env, string);

		for (ssize_t j = 0; j < results[i].m_MorphInfo.GetSize(); j++) {
			CMorphInfo info = results[i].m_MorphInfo[j];
			MorphInfo morphInfo(env);

			morphInfo.setRoot(String(env, info.m_szRoot.GetString()));
			morphInfo.setEnding(String(env, info.m_szEnding.GetString()));
			morphInfo.setClitic(String(env, info.m_szClitic.GetString()));
			morphInfo.setForm(String(env, info.m_szForm.GetString()));
			morphInfo.setPos(String(env, info.m_cPOS));
			word.morphInfos.add(morphInfo);
		}

		sentence.words.add(word);
	}
}

static void jvabamorf_analyze_sentence(JNIEnv *env, CLinguistic &linguistic, CDisambiguator &disambiguator, Sentence &sentence) {
	CPTWordArray words;
	PTWSplitBuffer(sentence.toCFSWString(), words);
	CFSArray<CMorphInfos> linguisticResults = linguistic.AnalyzeSentence(words);
	CFSArray<CMorphInfos> disambiguatedResults = disambiguator.Disambiguate(linguisticResults);
	jvabamorf_handle_results(env, disambiguatedResults, sentence);
}

JNIEXPORT void JNICALL Java_ee_risk_vabamorf_JVabamorf_analyze(JNIEnv *env, jobject obj, jstring linguisticDict, jstring disambiguatorDict, jobject sentence) {
	CLinguistic linguistic;
	CDisambiguator disambiguator;

	const char *nLinguisticDict = env->GetStringUTFChars(linguisticDict, NULL);
	const char *nDisambiguatorDict = env->GetStringUTFChars(disambiguatorDict, NULL);
	Sentence nSentence(env, sentence);

	try {
		linguistic.Open(nLinguisticDict);
		disambiguator.Open(nDisambiguatorDict);
		jvabamorf_analyze_sentence(env, linguistic, disambiguator, nSentence);
		goto cleanup;
	}
	catch (CLinguisticException &ex) {
		if (ex.m_lMajor == CLinguisticException::MAINDICT && ex.m_lMinor == CLinguisticException::UNDEFINED) {
			JNIException::LinguisticException(env, "File %s not found", nLinguisticDict);
			goto release;
		}

		JNIException::LinguisticException(env, "Unknown error: file=%s, major=%ld, minor=%ld", nLinguisticDict, ex.m_lMajor, ex.m_lMinor);
		goto cleanup;
	}
	catch (CDisambiguatorException &ex) {
		if (ex.m_lMajor == CDisambiguatorException::MAINDICT && ex.m_lMinor == CDisambiguatorException::UNDEFINED) {
			JNIException::DisambiguatorException(env, "File %s not found", nDisambiguatorDict);
			goto release;
		}

		JNIException::DisambiguatorException(env, "Unknown error: file=%s, major=%ld, minor=%ld", nDisambiguatorDict, ex.m_lMajor, ex.m_lMinor);
		goto cleanup;
	}

	cleanup:
	linguistic.Close();
	disambiguator.Close();

	release:
	env->ReleaseStringUTFChars(linguisticDict, nLinguisticDict);
	env->ReleaseStringUTFChars(disambiguatorDict, nDisambiguatorDict);
}

JNIEXPORT jstring JNICALL Java_ee_risk_vabamorf_JVabamorf_getModuleName(JNIEnv *env, jobject obj) {
	return (*env).NewStringUTF("Vabamorf JNI bridge");
}
