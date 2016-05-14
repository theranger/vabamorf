package ee.risk.vabamorf.model;

/**
 * Initially created by ranger on 14.05.16 for jVabamorf project.
 */
public class Word {
	private String data;
	private MorphInfo morphInfo;

	public Word(String data) {
		this.data = data;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public MorphInfo getMorphInfo() {
		return morphInfo;
	}

	public void setMorphInfo(MorphInfo morphInfo) {
		this.morphInfo = morphInfo;
	}
}
