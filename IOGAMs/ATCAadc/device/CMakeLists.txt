cmake_minimum_required (VERSION 3.8)

project (atcamimo32)
###################### find ATCA_MIMO32 dependencies ########################
find_path( ATCA_MIMO32_INCLUDE_PATH pci-atca-adc-ioctl.h ${PROJECT_SOURCE_DIR}/../driver )
if ( ATCA_MIMO32_INCLUDE_PATH )
  message( STATUS "Found pci-atca-adc-ioctl.h in " ${ATCA_MIMO32_INCLUDE_PATH} )
else ( ATCA_MIMO32_INCLUDE_PATH )
  message( FATAL_ERROR "pci-atca-adc-ioctl.h not found" )
endif ( ATCA_MIMO32_INCLUDE_PATH )

include_directories( ${PROJECT_BINARY_DIR} ${ATCA_MIMO32_INCLUDE_PATH} )

set( CMAKE_CXX_FLAGS -fPIC )

add_library(atca-mimo32-api ATCAMIMO32Device.h ATCAMIMO32Device.cpp )
#target_link_libraries( atca-mimo32-api)
target_link_libraries(atca-mimo32-api pthread rt )

add_executable( pci-atca-adc pci-atca-adc-test.cpp )
target_link_libraries(pci-atca-adc atca-mimo32-api )

# add_executable( atcamimo32 atcamimo32.cpp )
#install( TARGETS atcamimo32-api atcamimo32 RUNTIME DESTINATION bin ARCHIVE DESTINATION lib )

#install( FILES ATCAMIMO32Device.h DESTINATION include/atca )

SET(CPACK_GENERATOR "TGZ;DEB")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ATCA MIMO ISOL V1 User API")
SET(CPACK_PACKAGE_VENDOR "IPFN-IST ")
SET(CPACK_PACKAGE_CONTACT "Bernardo Carvalho <bernardo.carvalho@tecnico.ulisboa.pt>")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)
