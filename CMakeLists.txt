cmake_minimum_required(VERSION 3.30)
project(GoldMiner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(YAML_CPP_DIR "yaml-cpp")

include_directories(./EasyX/include ${YAML_CPP_DIR}/include)
link_directories(./EasyX/lib64 ${YAML_CPP_DIR}/lib)
link_libraries(libeasyx.a libyaml-cpp.dll.a)



file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/audios DESTINATION ${CMAKE_BINARY_DIR})


# 添加 Unicode 支持
#add_compile_definitions(UNICODE _UNICODE)

add_executable(GoldMiner
        # 基础配置文件
        windowCfg.cpp

        # 帧信息应该最先初始化
        FrameInfo.cpp

        # 图像配置
        imgCfg.cpp
        ImageProcessing.cpp

        # 计时器工具
        Timer.cpp

        # 基本对象类
        Object.cpp

        # 派生对象类
        ImageObject.cpp
        TextObject.cpp
        TriangleObject.cpp
        LineObject.cpp

        # 动画对象应在levelCfg前初始化
        AnimationObject.cpp

        Mineral.cpp
        MineralManager.cpp
        MineralCfg.cpp

        # 关卡配置（依赖于前面所有的初始化）
        levelCfg.cpp

        # 具体关卡实现
        StartMenu.cpp
        HighScore.cpp
        ShowTarget.cpp
        Level_A.cpp

        # 控制台功能
        commands.cpp
        Console.cpp

        # 主程序应该最后
        main.cpp
)
target_link_libraries(GoldMiner PRIVATE yaml-cpp user32 gdi32 kernel32 shell32 ole32 oleaut32 uuid comdlg32 advapi32)