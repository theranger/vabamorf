package ee.risk.vabamorf.model;

import java.util.ArrayList;

/**
 * Initially created by ranger on 14.05.16 for jVabamorf project.
 */
public class Word {
	private String data;
	private ArrayList<MorphInfo> morphInfo;

	public Word(String data) {
		this.data = data;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public ArrayList<MorphInfo> getMorphInfo() {
		return morphInfo;
	}

	public void setMorphInfo(ArrayList<MorphInfo> morphInfo) {
		this.morphInfo = morphInfo;
	}
}
