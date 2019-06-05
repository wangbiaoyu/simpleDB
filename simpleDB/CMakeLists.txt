set(SRCS
    main.cpp
    Util.cpp
    Lex_ana.cpp
    Table.cpp
    Insert.cpp
    Select.cpp
    State_code.cpp
    HashIndex.cpp
    File.cpp
    UndoLog.cpp
    RedoLog.cpp
)


add_executable(simpleDB ${SRCS})

target_link_libraries(simpleDB pthread rt)

target_link_libraries(simpleDB -lboost_serialization)

add_subdirectory(test)
