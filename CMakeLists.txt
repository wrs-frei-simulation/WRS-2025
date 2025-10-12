if(NOT ENABLE_GUI)
  return()
endif()

if(NOT BUILD_SCENE_EFFECTS_PLUGIN OR NOT BUILD_WRS2018 OR NOT BUILD_HAIRO_WORLD_PLUGIN)
  return()
endif()

option(BUILD_WRS2025 "Building the WRS2025 files" ON)
if(NOT BUILD_WRS2025)
  return()
endif()

if(UNIX)
  add_custom_target(
    symlink_to_WRS2025 ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_SOURCE_DIR} ${CHOREONOID_BINARY_SHARE_DIR}/WRS2025)
endif()

install(DIRECTORY
  model
  project
  share
  DESTINATION ${CHOREONOID_SHARE_SUBDIR}/WRS2025)

add_subdirectory(controller)
add_subdirectory(src)
