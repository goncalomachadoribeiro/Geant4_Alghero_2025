cmake_minimum_required(VERSION 3.16...3.27)
project(task)

option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# We presume the existence of three directories
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB_RECURSE macros RELATIVE ${PROJECT_SOURCE_DIR} macros/*.mac)

# Enable macros for out-of-source build
foreach(_file ${macros})
  configure_file(
    ${_file}
    ${PROJECT_BINARY_DIR}/${_file}
    COPYONLY
    )
endforeach()
#Copy scripts
configure_file( 
    ${PROJECT_SOURCE_DIR}/root_histogram.C
    ${PROJECT_BINARY_DIR}/root_histogram.C 
    COPYONLY
    )
configure_file( 
    ${PROJECT_SOURCE_DIR}/csv_histogram.py 
    ${PROJECT_BINARY_DIR}/csv_histogram.py
    COPYONLY
    )

add_executable(task main.cc ${sources} ${headers})
target_link_libraries(task ${Geant4_LIBRARIES})

install(TARGETS task DESTINATION bin)
