/**
 * Initially created by ranger on 3.04.16 for jVabamorf project.
 */
public class JVabamorf {

	public native void analyze(String corpus, String lingFile);
	public native String getModuleName();

	static {
		System.loadLibrary("vabamorf-jni");
	}

	public static void main(String[] args) throws LinguisticException {
		JVabamorf jVabamorf = new JVabamorf();
		System.out.println(jVabamorf.getModuleName());
		jVabamorf.analyze("This is my corpus", "data.dat");
	}
}
