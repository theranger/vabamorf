set(MODULE_NAME ${PROJECT_NAME}-t3mesta)

set(SOURCE_FILES
	main-krida.cpp
	main-krida.h
	t3lexpre.cpp
	t3main.cpp
	t3main.h
	t3mitmesus.cpp
	t3tabelpre.cpp
	t3tagspre.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana)
