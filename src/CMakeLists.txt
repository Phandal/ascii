add_executable(ascii main.c)
target_link_libraries(ascii bmp)
target_compile_options(ascii PRIVATE -Wall -Werror)
