#          Copyright Marek Kurdej 2011 - 2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

################################################################################
set(BFT_PATH "${INCLUDE_PATH}/boost/bft")
set(CL_BFT_PATH "${SRC_PATH}/boost/bft/cl")

################################################################################
file(GLOB HDRS
    ${BFT_PATH}/*.hpp
    #${BFT_PATH}/cl/*.hpp
    ${BFT_PATH}/detail/*.hpp
)
foreach(HEADER ${HDRS})
    set(TEST_NAME test_${HEADER})
    string(REGEX REPLACE "[.:/\\]" "_" TEST_NAME ${TEST_NAME})
    add_definitions( -DBOOST_BFT_HEADER_NAME=${HEADER} )
    add_executable(${TEST_NAME}
        test.cpp
        ${HEADER}
    )
    remove_definitions( BOOST_BFT_HEADER_NAME )
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER "Tests/headers")
endforeach()

file(REMOVE "include_all1.cpp")
foreach(HEADER ${HDRS})
    file(APPEND "include_all1.cpp" "#include \"${HEADER}\"\n")
endforeach()
file(REMOVE "include_all2.cpp")
list(REVERSE HDRS)
foreach(HEADER ${HDRS})
    file(APPEND "include_all2.cpp" "#include \"${HEADER}\"\n")
endforeach()

add_executable(include_all
    main.cpp
    include_all1.cpp
    include_all2.cpp
    ${HDRS}
)
set_target_properties(include_all PROPERTIES FOLDER "Tests/headers")