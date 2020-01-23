file(GLOB HEADERS_LIB "*.h")
file(GLOB SOURCES_LIB "*.cpp")

# file(GLOB HEADERS_LIB_SYSDEB "sysdep/*.h")
# file(GLOB SOURCES_LIB_SYSDEB "sysdep/*.cpp")

# file(GLOB HEADERS_LIB_PCH "pch/*.h")

add_library( oad_lib 
                ${SOURCES_LIB}
                ${HEADERS_LIB}
)