set(MODULE_NAME ${PROJECT_NAME}-etyhh)

set(SOURCE_FILES
	dctmetainf.h
	et3myh.cpp
	etmrfyhh.h
	t3common.h
	t3lex.h
)

add_library(${MODULE_NAME} ${SOURCE_FILES})
add_library(${MODULE_NAME}-shared SHARED ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME}-shared ${PROJECT_NAME}-fsc-shared)
