set(MODULE_NAME_ETANA etana)
set(MODULE_NAME_ETDISAMB etdisamb)
set(MODULE_NAME_ETSYN etsyn)
set(MODULE_NAME_SPELLER speller)

add_executable(${MODULE_NAME_ETANA} etana.cpp)
target_link_libraries(${MODULE_NAME_ETANA} ${PROJECT_NAME}-json ${PROJECT_NAME}-proof ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana ${PROJECT_NAME}-etyhh)

add_executable(${MODULE_NAME_ETDISAMB} etdisamb.cpp)
target_link_libraries(${MODULE_NAME_ETDISAMB} ${PROJECT_NAME}-json ${PROJECT_NAME}-proof ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana ${PROJECT_NAME}-etyhh)

add_executable(${MODULE_NAME_ETSYN} etsyn.cpp)
target_link_libraries(${MODULE_NAME_ETSYN} ${PROJECT_NAME}-json ${PROJECT_NAME}-proof ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana ${PROJECT_NAME}-etyhh)

add_executable(${MODULE_NAME_SPELLER} speller.cpp speller.h stlspeller.cpp)
target_link_libraries(${MODULE_NAME_SPELLER} ${PROJECT_NAME}-proof ${PROJECT_NAME}-fsc ${PROJECT_NAME}-etana ${PROJECT_NAME}-etyhh)
