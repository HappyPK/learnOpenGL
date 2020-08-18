import os
from conans import ConanFile, CMake, tools


class MdvConan(ConanFile):
    name = "learnOpenGL"
    #version = "1.0.0"
    url = "https://github.com/HappyPK/learnOpenGL"
    description = "learnOpenGL"
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake" # 指定生成器为cmake，将会生成conanbuildinfo.cmake

    # 指定若干依赖的程序包
    def requirements(self):
        self.requires("boost/1.73.0")
        self.requires("stb/20200203")

    # 生成项目文件并编译
    def build(self):
        cmake = CMake(self)
        cmake.definitions["CONAN_CXX_FLAGS"] = ""
        cmake.configure()
        cmake.build()


