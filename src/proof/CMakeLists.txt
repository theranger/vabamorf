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

add_library(${MODULE_NAME} ${SOURCE_FILES})
