file(GLOB_RECURSE SOURCES_C *.c)

idf_component_register(SRCS ${SOURCES_C} INCLUDE_DIRS ".")
