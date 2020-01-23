file(GLOB HEADERS_LIB "*.h")
file(GLOB SOURCES_LIB "*.cpp")
add_library( oad_lib ${SOURCES_LIB} ${HEADERS_LIB} )