# add source files
FILE(GLOB DEMO_SOURCES
    src/*.c
)

# register this app
add_cfe_app(demo ${DEMO_SOURCES})

# link mipea
target_link_libraries(demo mipea)
