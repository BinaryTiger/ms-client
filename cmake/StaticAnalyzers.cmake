if(${PROJECT_NAME}_ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    #set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -p="${PROJECT_SOURCE_DIR}/build" --config="" --format-style=file -extra-arg=-Wno-unknown-warning-option)
    #message("Clang-Tidy finished setting up.")

    add_custom_target(
        clang-tidy
        COMMAND clang-tidy
         -p="${PROJECT_SOURCE_DIR}/build" 
         --fix
         --format-style=file 
         --checks=-*,modernize-pass-by-value,modernize-use-equals-default,modernize-use-override,readability-redundant-smartptr-get,modernize-concat-nested-namespaces,readability-container-size-empty,readability-else-after-return,google-readability-braces-around-statements,llvm-qualified-auto,performance-for-range-copy
         ${PROJECT_SOURCE_DIR}/*.h
         ${PROJECT_SOURCE_DIR}/*.cpp
         ${PROJECT_SOURCE_DIR}/Character/*.h
         ${PROJECT_SOURCE_DIR}/Character/*.cpp
         ${PROJECT_SOURCE_DIR}/Character/*/*.h
         ${PROJECT_SOURCE_DIR}/Character/*/*.cpp
         ${PROJECT_SOURCE_DIR}/Data/*.h
         ${PROJECT_SOURCE_DIR}/Data/*.cpp
         ${PROJECT_SOURCE_DIR}/Graphics/*.h
         ${PROJECT_SOURCE_DIR}/Graphics/*.cpp
         ${PROJECT_SOURCE_DIR}/IO/*.h
         ${PROJECT_SOURCE_DIR}/IO/*.cpp
         ${PROJECT_SOURCE_DIR}/IO/*/*.h
         ${PROJECT_SOURCE_DIR}/IO/*/*.cpp
         ${PROJECT_SOURCE_DIR}/Net/*.h
         ${PROJECT_SOURCE_DIR}/Net/*.cpp
         ${PROJECT_SOURCE_DIR}/Net/*/*.h
         ${PROJECT_SOURCE_DIR}/Net/*/*.cpp
         ${PROJECT_SOURCE_DIR}/Net/*/*/*.h
         ${PROJECT_SOURCE_DIR}/Net/*/*/*.cpp
         ${PROJECT_SOURCE_DIR}/Util/*.h
         ${PROJECT_SOURCE_DIR}/Util/*.cpp
         ${PROJECT_SOURCE_DIR}/Template/*.h
         ${PROJECT_SOURCE_DIR}/Gameplay/*.h
         ${PROJECT_SOURCE_DIR}/Gameplay/*.cpp
         ${PROJECT_SOURCE_DIR}/Gameplay/*/*.h
         ${PROJECT_SOURCE_DIR}/Gameplay/*/*.cpp
         ${PROJECT_SOURCE_DIR}/Audio/*.cpp 
         ${PROJECT_SOURCE_DIR}/Audio/*.h
    )
  else()
    message(SEND_ERROR "Clang-Tidy requested but executable not found.")
  endif()
endif()

add_custom_target(
        iwyu
        COMMAND iwyu_tool.py
        -p "${PROJECT_SOURCE_DIR}/build"
)

if(${PROJECT_NAME}_ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all
                           --inline-suppr --inconclusive -i ${CMAKE_SOURCE_DIR}/imgui/lib)
    message("Cppcheck finished setting up.")
  else()
    message(SEND_ERROR "Cppcheck requested but executable not found.")
  endif()
endif()
