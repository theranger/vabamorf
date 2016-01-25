set(MODULE_NAME ${PROJECT_NAME}-conv4)

set(SOURCE_FILES
	dctcnv4.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc)
