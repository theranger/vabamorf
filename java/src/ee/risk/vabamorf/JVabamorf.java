package ee.risk.vabamorf;

import ee.risk.vabamorf.model.Sentence;
import ee.risk.vabamorf.model.Word;

/**
 * Initially created by ranger on 3.04.16 for jVabamorf project.
 */
public class JVabamorf {

	public native void analyze(String linguisticDict, String disambiguatorDict, Sentence sentence) throws LinguisticException, DisambiguatorException;
	public native String getModuleName();

	private String linguisticDict;
	private String disambiguatorDict;

	static {
		System.loadLibrary("vabamorf-jni");
	}

	public JVabamorf(String linguisticDict, String disambiguatorDict) {
		this.linguisticDict = linguisticDict;
		this.disambiguatorDict = disambiguatorDict;
	}

	public Sentence parseSentence(String text) throws LinguisticException, DisambiguatorException {
		Sentence sentence = new Sentence(text);
		this.analyze(linguisticDict, disambiguatorDict, sentence);
		return sentence;
	}

	public static void main(String[] args) throws LinguisticException, DisambiguatorException {
		if (args.length !=3) {
			System.err.println("Usage: JVabamorf <et.dct> <et3.dct> <sentence>");
			return;
		}

		JVabamorf jVabamorf = new JVabamorf(args[0], args[1]);

		System.out.println(jVabamorf.getModuleName());
		System.out.println("Analyzing [" + args[2] + "]");

		Sentence sentence = jVabamorf.parseSentence(args[2]);

		for (Word w : sentence.getWords()) {
			System.out.println("[" + w.getData() + "]");
			w.getMorphInfo().forEach( info -> {
				System.out.print(
								"root: " + info.getRoot() +
								" ending: " + info.getEnding() +
								" clitic: " + info.getClitic() +
								" form: " + info.getForm() +
								" partofspeech: " + info.getPos()
				);
			});

			System.out.println();
		}
	}
}
