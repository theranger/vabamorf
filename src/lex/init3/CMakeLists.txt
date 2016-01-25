set(MODULE_NAME ${PROJECT_NAME}-init3)

set(SOURCE_FILES
	cxxget2.cpp
	cxxinit3.cpp
	estmorf.h
	global.cpp
	init3.cpp
	init_eel.cpp
	init_end.cpp
	init_gr.cpp
	init.h
	init_prf.cpp
	init_suf.cpp
	result.cpp
	test.cpp
	wfi.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana)
