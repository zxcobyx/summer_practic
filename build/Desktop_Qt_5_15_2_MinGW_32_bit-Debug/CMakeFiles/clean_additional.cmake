# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\summer_practic_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\summer_practic_autogen.dir\\ParseCache.txt"
  "summer_practic_autogen"
  )
endif()
