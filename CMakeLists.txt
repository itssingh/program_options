cmake_minimum_required(VERSION 3.10)

project(program_options
    LANGUAGES CXX
    VERSION 1.0.0)

find_package(Boost REQUIRED program_options)

add_executable(program_test main.cc)

add_executable(program_bittest mainbits.cc)

target_link_libraries(program_test PRIVATE ${Boost_LIBRARIES})

target_link_libraries(program_bittest PRIVATE ${Boost_LIBRARIES})
include(GNUInstallDirs)
message("${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
install(TARGETS program_bittest program_test)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "PrOp")
set(CPACK_DEBIAN_FILE_NAME "PrOp-${PROJECT_VERSION}.deb")
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sarita Singh")
include(CPack)