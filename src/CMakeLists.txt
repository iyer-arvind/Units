include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(parser)

add_library(units SHARED unit_defs.cpp units.cpp)
target_link_libraries(units units_parser)

add_executable(test_units test_units.cpp)
target_link_libraries(test_units units)

