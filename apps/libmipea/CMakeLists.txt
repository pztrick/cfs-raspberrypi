include(ExternalProject)

if(NOT DEFINED TOOLCHAIN_PREFIX)
    message(FATAL_ERROR "You must export the environment variable \${TOOLCHAIN_PREFIX} = arm-linux-gnueabi, aarch64-linux-gnu.")
endif()

set(MIPEA_CC ${TOOLCHAIN_PREFIX}-gcc-7)
set(MIPEA_CXX ${TOOLCHAIN_PREFIX}-g++-7)

set(MIPEA_GIT ${CMAKE_CURRENT_SOURCE_DIR}/../../bundle/mipea)
set(MIPEA_DIR /tmp/mipea)
set(MIPEA_BIN ${CMAKE_CURRENT_BINARY_DIR}/libmipea)
set(MIPEA_STATIC_LIB ${MIPEA_BIN}/lib/libmipea.a)
set(MIPEA_INCLUDES ${MIPEA_BIN}/include)

file(MAKE_DIRECTORY ${MIPEA_INCLUDES})

ExternalProject_Add(
    libmipea
    PREFIX ${MIPEA_BIN}
    SOURCE_DIR ${MIPEA_DIR}
    DOWNLOAD_COMMAND rm -rf ${MIPEA_DIR} && cp -rf ${MIPEA_GIT} ${MIPEA_DIR} && cp ${CMAKE_CURRENT_SOURCE_DIR}/config.h ${MIPEA_DIR}/config.h && cd ${MIPEA_DIR} && autoreconf --install
    CONFIGURE_COMMAND ${MIPEA_DIR}/configure CC=${MIPEA_CC} CXX=${MIPEA_CXX} --target=${TOOLCHAIN_PREFIX} --host=${TOOLCHAIN_PREFIX} --prefix=${CMAKE_CURRENT_BINARY_DIR}/libmipea --srcdir=${MIPEA_DIR} --enable-static=yes --disable-shared
    BUILD_COMMAND make CPPFLAGS=-DBCM2836_7=1
    INSTALL_COMMAND make install
    BUILD_BYPRODUCTS ${MIPEA_STATIC_LIB}
)

add_library(mipea STATIC IMPORTED GLOBAL)

add_dependencies(mipea libmipea)

set_target_properties(mipea PROPERTIES IMPORTED_LOCATION ${MIPEA_STATIC_LIB})
set_target_properties(mipea PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${MIPEA_INCLUDES})

