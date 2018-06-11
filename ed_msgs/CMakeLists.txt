cmake_minimum_required(VERSION 2.8.3)
project(ed_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  tue_serialization
  geometry_msgs
)

# Generate messages in the 'msg' folder
add_message_files(
  FILES
    EntityInfo.msg
)

# Generate services in the 'srv' folder
add_service_files(
  FILES
    GetGUICommand.srv
    GetMeasurements.srv
    RaiseEvent.srv
    SetClick.srv
    SetLabel.srv
    SimpleQuery.srv
    LoadPlugin.srv

    Query.srv
    UpdateSrv.srv
    Configure.srv
    Reset.srv

    # For builder plugin
    SetEntity.srv
)

# Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
    tue_serialization
    geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS tue_serialization geometry_msgs
)
