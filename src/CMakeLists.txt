set(TARGET ns3dp)

find_package (PythonLibs)
if(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${PYTHON_LIBRARIES})
endif(PYTHONLIBS_FOUND)

find_package (Cat)
if (CAT_FOUND)
  include_directories(${CAT_INCLUDE_DIR})
  set(LIBS ${LIBS} ${CAT_LIBRARIES})
endif (CAT_FOUND)

find_package (FFTW)
if (FFTW_FOUND)
  include_directories(${FFTW_INCLUDE_DIR})
  set(LIBS ${LIBS} ${FFTW_LIBRARIES})
endif (FFTW_FOUND)

find_package (Goops)
if (GOOPS_FOUND)
  include_directories(${GOOPS_INCLUDE_DIR})
  set(LIBS ${LIBS} ${GOOPS_LIBRARIES})
endif (GOOPS_FOUND)

find_package (Godess)
if (GODESS_FOUND)
  include_directories(${GODESS_INCLUDE_DIR})
  set(LIBS ${LIBS} ${GODESS_LIBRARIES})
endif (GODESS_FOUND)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SRC_DIR})

set(HEADERS

"${SRC_DIR}/globals.h"
"${SRC_DIR}/init_cond.h"
"${SRC_DIR}/input.h"
"${SRC_DIR}/ns3dp.h"
"${SRC_DIR}/ns3dp_rhs.h"

)

set(SOURCES

"${SRC_DIR}/init_cond.C"
"${SRC_DIR}/input.C"
"${SRC_DIR}/ns3dp.C"
"${SRC_DIR}/ns3dp_rhs.C"

)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${LIBS})

install (TARGETS ${TARGET} DESTINATION bin)

