# register this app
add_cfe_app(demo src/*.c)

# link mipea
target_link_libraries(demo mipea)
