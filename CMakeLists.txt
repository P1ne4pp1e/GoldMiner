cmake_minimum_required(VERSION 3.30)
project(GoldMiner)

set(CMAKE_CXX_STANDARD 20)

include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)



file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/audios DESTINATION ${CMAKE_BINARY_DIR})


# 添加 Unicode 支持
#add_compile_definitions(UNICODE _UNICODE)

add_executable(GoldMiner main.cpp Console.cpp commands.cpp)

target_link_libraries(GoldMiner PRIVATE user32 gdi32 kernel32 shell32 ole32 oleaut32 uuid comdlg32 advapi32)
