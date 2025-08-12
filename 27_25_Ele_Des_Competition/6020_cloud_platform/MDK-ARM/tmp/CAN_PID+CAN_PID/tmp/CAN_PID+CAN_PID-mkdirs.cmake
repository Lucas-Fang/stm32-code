# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID")
  file(MAKE_DIRECTORY "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID")
endif()
file(MAKE_DIRECTORY
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/1"
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID"
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/tmp"
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/src/CAN_PID+CAN_PID-stamp"
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/src"
  "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/src/CAN_PID+CAN_PID-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/src/CAN_PID+CAN_PID-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/25_Ele_Des_Competition/6020_cloud_platform/MDK-ARM/tmp/CAN_PID+CAN_PID/src/CAN_PID+CAN_PID-stamp${cfgdir}") # cfgdir has leading slash
endif()
