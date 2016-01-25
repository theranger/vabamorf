set(MODULE_NAME ${PROJECT_NAME}-verb)

set(SOURCE_FILES
	kogupara.cpp
	par27-38.cpp
	verb.cpp
	verbera.cpp
	vparpar.cpp
	vteepar.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-nomvrb ${PROJECT_NAME}-etana)
