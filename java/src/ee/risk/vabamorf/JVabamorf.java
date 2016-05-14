package ee.risk.vabamorf;

import ee.risk.vabamorf.model.Sentence;

import java.util.ArrayList;

/**
 * Initially created by ranger on 3.04.16 for jVabamorf project.
 */
public class JVabamorf {

	public native void analyze(String dict, ArrayList<Sentence> sentences);
	public native String getModuleName();

	static {
		System.loadLibrary("vabamorf-jni");
	}

	public static void main(String[] args) throws LinguisticException {
		if (args.length !=2) {
			System.err.println("Usage: JVabamorf <et.dct> <corpus_string>");
			return;
		}

		Sentence sentence = new Sentence();
		sentence.addWord("Täna");
		sentence.addWord("on");
		sentence.addWord("vihmane");
		sentence.addWord("ilm");

		ArrayList<Sentence> sentences = new ArrayList<>();
		sentences.add(sentence);

		JVabamorf jVabamorf = new JVabamorf();
		System.out.println(jVabamorf.getModuleName());
		jVabamorf.analyze(args[0], sentences);
	}
}
