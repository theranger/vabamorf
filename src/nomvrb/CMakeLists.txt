set(MODULE_NAME ${PROJECT_NAME}-nomvrb)

set(SOURCE_FILES
	era_ind.cpp
	era_tyvi.cpp
	lgr.cpp
	lyli.cpp
	muutujad.cpp
	noomen.h
	nullityv.cpp
)

add_library(${MODULE_NAME} ${SOURCE_FILES})
