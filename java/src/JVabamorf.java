/**
 * Initially created by ranger on 3.04.16 for jVabamorf project.
 */
public class JVabamorf {

	public native void analyze(String text, String lingFile);
	public native void getModuleName();

	static {
		System.loadLibrary("vabamorf-jni");
	}

	public static void main(String[] args) {
		new JVabamorf().getModuleName();
	}
}
