#This file is for other projects to use, so that they can locate KGLT
#using cmake

FIND_PATH( KGLT_INCLUDE_DIRS kglt/window.h /usr/include /usr/local/include $ENV{INCLUDE} )
FIND_LIBRARY( KGLT_LIBRARIES NAMES kglt PATHS /usr/lib /usr/local/lib )

IF(KGLT_INCLUDE_DIRS)
	MESSAGE(STATUS "Found KGLT include dir: ${KGLT_INCLUDE_DIRS}")
ELSE(KGLT_INCLUDE_DIRS)
	MESSAGE(STATUS "Could NOT find KGLT headers.")
ENDIF(KGLT_INCLUDE_DIRS)

IF(KGLT_LIBRARIES)
	MESSAGE(STATUS "Found KGLT library: ${KGLT_LIBRARIES}")
ELSE(KGLT_LIBRARIES)
	MESSAGE(STATUS "Could NOT find KGLT library.")
ENDIF(KGLT_LIBRARIES)

IF(KGLT_INCLUDE_DIRS AND KGLT_LIBRARIES)
	SET(KGLT_FOUND "YES")
ELSE(KGLT_INCLUDE_DIRS AND KGLT_LIBRARIES)
	SET(KGLT_FOUND "NO")
	IF(KGLT_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find KGLT. Please install KGLT (http://github.com/kazade/kglt)")
	ENDIF(KGLT_FIND_REQUIRED)
ENDIF(KGLT_INCLUDE_DIRS AND KGLT_LIBRARIES)
