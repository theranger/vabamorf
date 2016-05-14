package ee.risk.vabamorf.model;

import java.util.ArrayList;

/**
 * Initially created by ranger on 14.05.16 for jVabamorf project.
 */
public class Sentence {

	private ArrayList<Word> words = new ArrayList<>();

	public ArrayList<Word> getWords() {
		return words;
	}

	public void setWords(ArrayList<Word> words) {
		this.words = words;
	}

	public void addWord(String word) {
		words.add(new Word(word));
	}
}
