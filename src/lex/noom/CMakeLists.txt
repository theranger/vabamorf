set(MODULE_NAME ${PROJECT_NAME}-noom)

set(SOURCE_FILES
	lihtlisa.cpp
	nomerand.cpp
	nomnul.cpp
	noomen.cpp
	par1-10.cpp
	par11-20.cpp
	par21-26.cpp
	parpar.cpp
	tee_para.cpp
	ykssilp.cpp
)

add_executable(${MODULE_NAME} ${SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${PROJECT_NAME}-fsc ${PROJECT_NAME}-nomvrb ${PROJECT_NAME}-etana)
