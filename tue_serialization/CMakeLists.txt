cmake_minimum_required(VERSION 2.8.3)
project(tue_serialization)

find_package(catkin REQUIRED COMPONENTS message_generation)
# find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
  FILES
  Binary.msg
)

add_service_files(
  FILES
  BinaryService.srv
)

generate_messages(
  DEPENDENCIES
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES tue_serialization
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

include_directories(include)

set(HEADER_FILES
    include/tue/serialization/version.h
    include/tue/serialization/input_archive.h
    include/tue/serialization/archive.h
    include/tue/serialization/conversions.h
    include/tue/serialization/output_archive.h
    include/tue/serialization/filesystem.h
)

add_library(tue_serialization
    src/conversions.cpp
    src/filesystem.cpp
)

add_executable(test_serialization test/test_serialization.cpp ${HEADER_FILES})
target_link_libraries(test_serialization tue_serialization)

add_dependencies(tue_serialization ${PROJECT_NAME}_gencpp)
add_dependencies(test_serialization ${PROJECT_NAME}_gencpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(tue_serialization_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS tue_serialization tue_serialization_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_tue_serialization.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
