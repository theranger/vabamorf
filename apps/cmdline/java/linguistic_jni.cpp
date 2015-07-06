#include "../../../lib/proof/proof.h"
#include "../../../lib/fsc/fsjni/fsjni.h"
#include "utils.h"

FSDLL_ENTRYPOINT;

#define FUNCTION_HEADER \
	CLinguistic *linguistic = (CLinguistic *)FSJNIGetLongField(env, jobj, "objId"); \
	if (linguistic) { \
		linguistic->m_bAbbrevations = (FSJNIGetBooleanField(env, jobj, "abbrevations") != JNI_FALSE); \
		linguistic->m_bRomanNumerals = (FSJNIGetBooleanField(env, jobj, "romanNumerals") != JNI_FALSE); \
		linguistic->m_bGuess = (FSJNIGetBooleanField(env, jobj, "guess") != JNI_FALSE); \
		linguistic->m_bPhonetic = (FSJNIGetBooleanField(env, jobj, "phonetic") != JNI_FALSE); \
		linguistic->m_bProperName = (FSJNIGetBooleanField(env, jobj, "properName") != JNI_FALSE); \
	}

extern "C" {

JNIEXPORT jboolean JNICALL Java_ee_filosoft_vabamorf_Linguistic_open(JNIEnv *env, jobject jobj, jstring fileName)
{
	FUNCTION_HEADER;

	if (linguistic) {
		FSJNISetLongField(env, jobj, "objId", (jlong)0);
		IGNORE_FSEXCEPTION( delete linguistic; )
	}

	try {
#if defined (UNICODE)
		CFSFileName fileNameT=FSJNIStrtoW(env, fileName);
#else
		CFSFileName fileNameT=FSJNIStrtoA(env, fileName);
#endif
		linguistic = new CLinguistic();
		linguistic->Open(fileNameT);
		FSJNISetLongField(env, jobj, "objId", (jlong)linguistic);
		return JNI_TRUE;
	} catch(...) {
		return JNI_FALSE;
	}}

JNIEXPORT void JNICALL Java_ee_filosoft_vabamorf_Linguistic_close(JNIEnv *env, jobject jobj)
{
	FUNCTION_HEADER;

	if (linguistic) {
		FSJNISetLongField(env, jobj, "objId", (jlong)0);
		IGNORE_FSEXCEPTION( delete linguistic; )
	}
}

// Speller
JNIEXPORT jint JNICALL Java_ee_filosoft_vabamorf_Linguistic_spellWord(JNIEnv *env, jobject jobj, jstring word)
{
	FUNCTION_HEADER;
	if (!linguistic) return -1;

	try {
		return linguistic->SpellWord(FSJNIStrtoW(env, word));
	} catch (...) {
		return -1;
	}
}

JNIEXPORT jintArray JNICALL Java_ee_filosoft_vabamorf_Linguistic_spellWords(JNIEnv *env, jobject jobj, jobjectArray words)
{
	FUNCTION_HEADER;
	if (!linguistic) return NULL;

	try {
		CFSArray<CPTWord> ptwords;
		INTPTR ipSize = env->GetArrayLength(words);
		for (INTPTR ip=0; ip<ipSize; ip++) {
			ptwords.AddItem(FSJNIStrtoW(env, (jstring)env->GetObjectArrayElement(words, ip)));
		}

		CFSArray<SPLRESULT> splresults = linguistic->SpellWords(ptwords);

		jintArray result = env->NewIntArray(splresults.GetSize());
		for (INTPTR ip=0; ip<splresults.GetSize(); ip++) {
			jint result1 = splresults[ip];
			env->SetIntArrayRegion(result, ip, 1, &result1);
		}
		return result;
	} catch (...) {
		return NULL;
	}
}

JNIEXPORT jobjectArray JNICALL Java_ee_filosoft_vabamorf_Linguistic_suggest(JNIEnv *env, jobject jobj, jstring word, jboolean startSentence)
{
	FUNCTION_HEADER;
	if (!linguistic) return NULL;

	try {
		CFSWStringArray suggestions = linguistic->Suggest(FSJNIStrtoW(env, word), startSentence!=JNI_FALSE);

		jobjectArray suggs = (jobjectArray)env->NewObjectArray(suggestions.GetSize(), env->FindClass("java/lang/String"), 0);
		for (INTPTR ip=0; ip<suggestions.GetSize(); ip++) {
			env->SetObjectArrayElement(suggs, ip, FSJNIWtoStr(env, suggestions[ip]));
		}
		return suggs;
	} catch(...) {
		return 0;
	}
}

JNIEXPORT jobjectArray JNICALL Java_ee_filosoft_vabamorf_Linguistic_analyze(JNIEnv *env, jobject jobj, jstring word)
{
	FUNCTION_HEADER;
	if (!linguistic) return NULL;

	try {
		CFSArray<CMorphInfo> results = linguistic->Analyze(FSJNIStrtoW(env, word));

		jobjectArray analyzes=(jobjectArray)env->NewObjectArray(results.GetSize(), env->FindClass("java/lang/Object"), 0);
		for (INTPTR ip=0; ip<results.GetSize(); ip++) {
			env->SetObjectArrayElement(analyzes, ip, MorphInfoToJNI(env, results[ip]));
		}
		return analyzes;
	} catch(...) {
		return NULL;
	}
}

JNIEXPORT jobjectArray JNICALL Java_ee_filosoft_vabamorf_Linguistic_analyzeSentence(JNIEnv *env, jobject jobj, jobjectArray words)
{
	FUNCTION_HEADER;
	if (!linguistic) return NULL;

	try {
		CFSArray<CPTWord> ptwords;
		INTPTR ipSize = env->GetArrayLength(words);
		for (INTPTR ip=0; ip<ipSize; ip++) {
			ptwords.AddItem(FSJNIStrtoW(env, (jstring)env->GetObjectArrayElement(words, ip)));
		}

		CFSArray<CMorphInfos> results = linguistic->AnalyzeSentence(ptwords);

		jobjectArray analyzes = (jobjectArray)env->NewObjectArray(results.GetSize(), env->FindClass("java/lang/Object"), 0);
		for (INTPTR ip = 0; ip < results.GetSize(); ip++) {
			env->SetObjectArrayElement(analyzes, ip, MorphInfosToJNI(env, results[ip]));
		}
		return analyzes;
	} catch(...) {
		return NULL;
	}
}

JNIEXPORT jobjectArray JNICALL Java_ee_filosoft_vabamorf_Linguistic_synthesize(JNIEnv *env, jobject jobj, jobject info, jstring hint)
{
	FUNCTION_HEADER;
	if (!linguistic) return NULL;

	try {
		CMorphInfo MorphInfo = JNIToMorphInfo(env, info);
		MorphInfo.m_szEnding.Empty();

		CFSArray<CMorphInfo> results = linguistic->Synthesize(MorphInfo, FSJNIStrtoW(env, hint));

		jobjectArray synths=(jobjectArray)env->NewObjectArray(results.GetSize(), env->FindClass("java/lang/Object"), 0);
		for (INTPTR ip=0; ip<results.GetSize(); ip++) {
			env->SetObjectArrayElement(synths, ip, MorphInfoToJNI(env, results[ip]));
		}
		return synths;
	} catch(...) {
		return NULL;
	}
}

} // extern "C"
