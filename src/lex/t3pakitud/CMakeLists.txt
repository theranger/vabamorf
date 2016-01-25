set(MODULE_NAME ${PROJECT_NAME}-t3pakitud)

set(SOURCE_FILES
	t3pakikokku.cpp
	t3_pakitud.h
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc)
