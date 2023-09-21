cmake_minimum_required (VERSION 3.10)

project (pci-atca-adc)

set( CMAKE_CXX_FLAGS "-fPIC" )

include_directories( ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

#add_library( atca-mimo32-v2-api SHARED atca-mimo32-v2-device.h atca-mimo32-v2-device.cpp)
add_executable( pci-atca-adc pci-atca-adc-test.cpp )

#target_link_libraries( atca-mimo32-v2-api pthread rt)
#target_link_libraries( atca-mimo32-v2 atca-mimo32-v2-api )

SET(CPACK_GENERATOR "TGZ;DEB")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ATCA MIMO ISOL V1 User API")
SET(CPACK_PACKAGE_VENDOR "IPFN-IST ")
SET(CPACK_PACKAGE_CONTACT "Bernardo Carvalho <bernardo.carvalho@tecnico.ulisboa.pt>")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)

#install( TARGETS atca-mimo32-v2-api atca-mimo32-v2 RUNTIME DESTINATION bin ARCHIVE DESTINATION lib )
#install( FILES atca-mimo32-v2-device.h DESTINATION include )


