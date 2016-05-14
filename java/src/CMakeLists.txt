
#If JAVA_HOME is not set, JNI module will not be properly initialized
if(APPLE)
	set(ENV{JAVA_HOME} "/Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home")
else(APPLE)
	set(ENV{JAVA_HOME} "/usr/lib/jvm/jdk-8-oracle-x64")
endif(APPLE)

find_package(JNI)
if(NOT JNI_FOUND)
	message(WARNING "JNI not found, not building Java components")
	return()
endif(NOT JNI_FOUND)

include(UseJava)

set(MODULE_NAME JVabamorf)

set(SOURCE_FILES
		ee/risk/vabamorf/JVabamorf.java
		ee/risk/vabamorf/LinguisticException.java
		ee/risk/vabamorf/model/Sentence.java
		ee/risk/vabamorf/model/MorphInfo.java
		ee/risk/vabamorf/model/Word.java
		)

set(CLASS_NAMES
		ee.risk.vabamorf.JVabamorf
		)

add_jar(${MODULE_NAME} ${SOURCE_FILES})
get_target_property(TARGET_CLASS_DIR ${MODULE_NAME} CLASSDIR)
Create_Javah(TARGET ${MODULE_NAME}-headers CLASSES ${CLASS_NAMES} CLASSPATH ${MODULE_NAME} OUTPUT_NAME ${PROJECT_BINARY_DIR}/${MODULE_NAME}.h)
