set(MODULE_NAME ${PROJECT_NAME}-conv11)

set(SOURCE_FILES
	dctcnv11.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana)
