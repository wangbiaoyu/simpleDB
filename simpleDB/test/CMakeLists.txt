set(srcs
    fxxx.cpp
    ../HashIndex.cpp
    #../File.cpp
    )


add_executable(test ${srcs})

target_link_libraries(test -lboost_serialization)
