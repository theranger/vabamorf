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
		if (args.length !=2) {
			System.err.println("Usage: JVabamorf <et.dct> <corpus_string>");
			return;
		}

		JVabamorf jVabamorf = new JVabamorf();
		System.out.println(jVabamorf.getModuleName());
		jVabamorf.analyze(args[1], args[0]);
	}
}
