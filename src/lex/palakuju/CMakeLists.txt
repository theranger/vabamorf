set(MODULE_NAME ${PROJECT_NAME}-palakuju)

set(SOURCE_FILES
	dctcnvpala.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana)
