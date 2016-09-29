file(GLOB SRC_FILES [^.]*.c)
file(GLOB HDR_FILES [^.]*.h)
add_executable(dash ${SRC_FILES} ${HDR_FILES})