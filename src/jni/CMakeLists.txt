
find_package(Java)
if(NOT Java_FOUND)
	message(WARNING "Java not found, not building Java components")
	return()
endif(NOT Java_FOUND)

# PROJECT_BINARY_DIR contains JNI header file
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_BINARY_DIR} -I${JAVA_INCLUDE_PATH} -I${JAVA_INCLUDE_PATH2}")

# Force building shared JNI library along Java sources so Java project can find it
# This is required for development only
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/java/lib")

set(MODULE_NAME ${PROJECT_NAME}-jni)

set(SOURCE_FILES
		JVabamorf.cpp
		JNIException.cpp JNIException.h)

add_library(${MODULE_NAME} SHARED ${SOURCE_FILES})

# Ensure that Java is built and JNI header is generated before trying to build this module
add_dependencies(${MODULE_NAME} JVabamorf)
target_link_libraries(${MODULE_NAME} vabamorf-fsc-shared vabamorf-proof-shared vabamorf-etana-shared)
