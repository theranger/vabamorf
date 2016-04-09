
#If JAVA_HOME is not set, JNI module will not be properly initialized
set(ENV{JAVA_HOME} "/usr/lib/jvm/jdk-8-oracle-x64")

find_package(JNI)
if(NOT JNI_FOUND)
	message(WARNING "JNI not found, not building Java components")
	return()
endif(NOT JNI_FOUND)

include(UseJava)

set(MODULE_NAME JVabamorf)

set(SOURCE_FILES
		JVabamorf.java
		)

add_jar(${MODULE_NAME} ${SOURCE_FILES})
get_target_property(TARGET_CLASS_DIR ${MODULE_NAME} CLASSDIR)

add_custom_command(
		TARGET ${MODULE_NAME}
		COMMAND ${Java_JAVAH_EXECUTABLE} -verbose
		-classpath ${TARGET_CLASS_DIR}
		-d ${PROJECT_BINARY_DIR}
		-jni ${MODULE_NAME}
)
