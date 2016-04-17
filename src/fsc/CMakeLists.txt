set(MODULE_NAME ${PROJECT_NAME}-fsc)

set(SOURCE_FILES
	fsblockalloc.h
	fsc.h
	fscinit.cpp
	fscinit.h
	fsdata.cpp
	fsdata.h
	fsdll.cpp
	fsdll.h
	fsexception.cpp
	fsexception.h
	fsfile.cpp
	fsfile.h
	fsfixalloc.cpp
	fsfixalloc.h
	fshugeinteger.cpp
	fshugeinteger.h
	fsjni
	fslist.cpp
	fslist.h
	fsmemory.cpp
	fsmemory.h
	fsreg.cpp
	fsreg.h
	fssmartptr.h
	fsstream.h
	fsstring2.h
	fsstring.cpp
	fsstring.h
	fsthread.cpp
	fsthread.h
	fstime.cpp
	fstime.h
	fstrace.cpp
	fstrace.h
	fstype.h
	fsutil.h
	fsvar.cpp
	fsvar.h
	fswav.cpp
	fswav.h
	stdfsc.h
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/java/lib")
add_library(${MODULE_NAME} STATIC ${SOURCE_FILES})
add_library(${MODULE_NAME}-shared SHARED ${SOURCE_FILES})
set_target_properties(${MODULE_NAME}-shared PROPERTIES OUTPUT_NAME ${MODULE_NAME})
target_link_libraries(${MODULE_NAME} pthread)
