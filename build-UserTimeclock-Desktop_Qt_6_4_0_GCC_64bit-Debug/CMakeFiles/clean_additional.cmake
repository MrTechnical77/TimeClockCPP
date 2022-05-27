# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/UserTimeclock_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/UserTimeclock_autogen.dir/ParseCache.txt"
  "UserTimeclock_autogen"
  )
endif()
