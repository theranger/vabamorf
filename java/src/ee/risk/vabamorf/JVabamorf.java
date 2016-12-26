package ee.risk.vabamorf;

import ee.risk.vabamorf.model.Sentence;
import ee.risk.vabamorf.model.Word;

/**
 * Initially created by ranger on 3.04.16 for jVabamorf project.
 */
public class JVabamorf {

	public native void analyze(String linguisticDict, String disambiguatorDict, Sentence sentence);
	public native String getModuleName();

	static {
		System.loadLibrary("vabamorf-jni");
	}

	public static void main(String[] args) throws LinguisticException, DisambiguatorException {
		if (args.length !=3) {
			System.err.println("Usage: JVabamorf <et.dct> <et3.dct> <corpus_string>");
			return;
		}

		JVabamorf jVabamorf = new JVabamorf();
		Sentence sentence = new Sentence("Vihmase ilmaga me õue ei lähe");

		System.out.println(jVabamorf.getModuleName());
		jVabamorf.analyze(args[0], args[1], sentence);

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
