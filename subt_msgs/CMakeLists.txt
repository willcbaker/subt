cmake_minimum_required(VERSION 2.8.3)
project(subt_msgs)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_generation
)

add_service_files(
  FILES
    ObjectOfInterest.srv
)

generate_messages(
  DEPENDENCIES
    geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    message_runtime
)
