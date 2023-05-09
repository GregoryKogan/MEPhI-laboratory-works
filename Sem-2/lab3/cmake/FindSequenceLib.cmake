set(FIND_SEQUENCE-LIB_PATHS
        ../../../libraries/sequence_lib)

find_path(SEQUENCE-LIB_INCLUDE_DIR sequence_lib.h
        PATH_SUFFIXES include
        PATHS ${FIND_SEQUENCE-LIB_PATHS})

find_library(SEQUENCE-LIB_LIBRARY
        NAMES sequence_lib
        PATH_SUFFIXES lib
        PATHS ${FIND_SEQUENCE-LIB_PATHS})
