from conans import ConanFile, CMake
from conan.tools.cmake import CMakeDeps, CMakeToolchain

class JsonRPC(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "nlohmann_json/3.9.1", "boost/1.75.0", "fmt/7.1.3", "gtest/1.10.0"
    
    def generate(self):
        cmakedeps = CMakeDeps(self)
        cmaketoolchain = CMakeToolchain(self)
        cmakedeps.generate()
        cmaketoolchain.generate()
