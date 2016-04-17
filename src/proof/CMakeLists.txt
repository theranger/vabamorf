set(MODULE_NAME ${PROJECT_NAME}-proof)

set(SOURCE_FILES
	disambiguator.cpp
	disambiguator.h
	linguistic.cpp
	linguistic.h
	morphinfo.h
	proof.h
	pttype.h
	ptword.cpp
	ptword.h
	suggestor.cpp
	suggestor.h
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/java/lib")
add_library(${MODULE_NAME} STATIC ${SOURCE_FILES})
add_library(${MODULE_NAME}-shared SHARED ${SOURCE_FILES})
set_target_properties(${MODULE_NAME}-shared PROPERTIES OUTPUT_NAME ${MODULE_NAME})
