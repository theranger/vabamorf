set(MODULE_NAME ${PROJECT_NAME}-etsyn)

set(SOURCE_FILES
	etmrfsyn.h
	fake.cpp)

add_library(${MODULE_NAME} ${SOURCE_FILES})
