file(GLOB_RECURSE SOURCES *.c)

idf_component_register(
    SRCS
    ${SOURCES}
    INCLUDE_DIRS
    .
    ./guider_customer_fonts
    ./guider_fonts
    REQUIRES
    lvgl)
