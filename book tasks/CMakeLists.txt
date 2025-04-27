file(GLOB Sources "*.cpp")
add_executable(MyProgram ${Sources})
target_compile_options(MyProgram PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(MyProgram doctest)