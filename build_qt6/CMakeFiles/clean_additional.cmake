# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  [[CMakeFiles\codebrowser_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\codebrowser_autogen.dir\ParseCache.txt]]
  [[CMakeFiles\test_adblock_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\test_adblock_autogen.dir\ParseCache.txt]]
  [[CMakeFiles\test_database_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\test_database_autogen.dir\ParseCache.txt]]
  "codebrowser_autogen"
  "test_adblock_autogen"
  "test_database_autogen"
  )
endif()
