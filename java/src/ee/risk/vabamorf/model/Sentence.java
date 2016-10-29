package ee.risk.vabamorf.model;

import java.util.ArrayList;

/**
 * Initially created by ranger on 14.05.16 for jVabamorf project.
 */
public class Sentence {

	private String data;

	public Sentence(String sentence) {
		data = sentence;
	}

	private ArrayList<Word> words = new ArrayList<>();

	public ArrayList<Word> getWords() {
		return words;
	}

	public void setWords(ArrayList<Word> words) {
		this.words = words;
	}

	public void addWord(Word word) {
		words.add(word);
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}
}
