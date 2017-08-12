set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(units_parser
             units_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/units_parser.tab.cc)
FLEX_TARGET(units_lexer
            units_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/units_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(units_lexer units_parser)

add_library(units_parser
    		units_driver.cpp
    		${FLEX_units_lexer_OUTPUTS}
    		${BISON_units_parser_OUTPUTS}
	   )
target_include_directories(units_parser PRIVATE . ${CMAKE_CURRENT_BINARY_DIR})

