#set(TESTNS3DP_TARGET testns3dp)

#enable_testing()

set(TESTNS3DP_DIR "${CMAKE_SOURCE_DIR}/test")

#include_directories("${CMAKE_SOURCE_DIR}")

#set(TESTNS3DP_SOURCES 

#"${TESTNS3DP_DIR}/testns3dp.C"

#)

#set(TESTNS3DP_TARGET testgodess)
#add_executable(${TESTNS3DP_TARGET} ${TESTNS3DP_SOURCES})
#target_link_libraries(${TESTNS3DP_TARGET} ${LIBS} ns3dp)
#add_dependencies(${TESTNS3DP_TARGET} ns3dp)

#add_test(${TESTNS3DP_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TESTNS3DP_TARGET})


install (FILES ${TESTNS3DP_DIR}/default.cfg DESTINATION share/test)


