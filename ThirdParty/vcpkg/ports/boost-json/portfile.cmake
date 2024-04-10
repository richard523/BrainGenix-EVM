# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/json
    REF boost-1.83.0
    SHA512 0640a922507c416d171eff1b60c291e9644dba97770a3277c85233982d8c1022e64cbab88e9cdff7ce0f371965c214dc6da36f9cd7b134d1f5e8dc8deabb31f9
    HEAD_REF master
    PATCHES
        0001-Fix-use-of-intrinsics-on-windows-ARM-platforms.patch
        0002-Replace-_M_ARM64-with-_M_ARM-for-32-bit-path.patch
)

vcpkg_replace_string("${SOURCE_PATH}/build/Jamfile"
    "import ../../config/checks/config"
    "import ../config/checks/config"
)
file(COPY "${CURRENT_INSTALLED_DIR}/share/boost-config/checks" DESTINATION "${SOURCE_PATH}/config")
include(${CURRENT_HOST_INSTALLED_DIR}/share/boost-build/boost-modular-build.cmake)
boost_modular_build(
    SOURCE_PATH ${SOURCE_PATH}
    BOOST_CMAKE_FRAGMENT "${CMAKE_CURRENT_LIST_DIR}/b2-options.cmake"
)
include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})