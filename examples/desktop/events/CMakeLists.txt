cmake_minimum_required(VERSION 3.19)

project(sample_cmake_project)

find_package(atsdk REQUIRED CONFIG)

set(examples notify monitor resilient_monitor)

foreach(example ${examples})
  add_executable(${example} ${CMAKE_CURRENT_LIST_DIR}/${example}.c)
  target_link_libraries(${example} PRIVATE atsdk::atclient atsdk::cjson)
endforeach()
