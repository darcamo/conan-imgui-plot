from conans import ConanFile, CMake, tools
from conans.tools import os_info, SystemPackageTool
import shutil
import os


class ImguiplotConan(ConanFile):
    name = "imgui-plot"
    version = "0.1.0"
    license = "MIT"
    author = "Darlan Cavalcante Moreira (darcamo@gmail.com)"
    url = "https://github.com/darcamo/conan-imgui-plot"
    description = "An improved plot widget for Dear ImGui, aimed at displaying audio data"
    topics = ("plot", "imgui", "audio")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "CMakeLists.txt"
    requires = "imgui-sfml/2.1@bincrafters/stable"

    def source(self):
        tools.get(
            f"https://github.com/soulthreads/imgui-plot/archive/v{self.version}.zip"
        )

        # Remove CMakeLists provided by imgui-plot
        os.remove("imgui-plot-0.1.0/CMakeLists.txt")

        # Copy our CMakeLists
        shutil.move("CMakeLists.txt", f"imgui-plot-{self.version}/")

    def build(self):
        cmake = CMake(self)
        os.mkdir("build")
        shutil.move("conanbuildinfo.cmake", "build/")
        cmake.configure(source_folder=f"imgui-plot-{self.version}/",
                        build_folder="build")
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["imgui-plot"]
