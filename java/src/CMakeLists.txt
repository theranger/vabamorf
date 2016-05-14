
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
		JVabamorf.java
		LinguisticException.java
		)

set(CLASS_NAMES
		JVabamorf
		)

add_jar(${MODULE_NAME} ${SOURCE_FILES})
get_target_property(TARGET_CLASS_DIR ${MODULE_NAME} CLASSDIR)
Create_Javah(TARGET ${MODULE_NAME}-headers CLASSES ${CLASS_NAMES} CLASSPATH ${MODULE_NAME} OUTPUT_DIR ${PROJECT_BINARY_DIR})
