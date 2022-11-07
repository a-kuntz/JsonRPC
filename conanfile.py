from conans import ConanFile, tools

class ConanPackage(ConanFile):
    name = "jsonrpc"
    # version = intentionally left undefined; must be explicitly set by user or CI pipeline
    license = "None"
    settings = "os", "compiler", "build_type", "arch"
    options = {"build_tests": [True, False], "build_example": [True, False]}
    default_options = {"build_tests": False, "build_example": False}
    generators = "CMakeDeps", "CMakeToolchain"
    requires = "boost/1.75.0", "fmt/7.1.3", "nlohmann_json/3.9.1"
    exports_sources = "example/*", "lib/*", "test/*", "CMakeLists.txt"

    def build_requirements(self):
        if self.options.build_tests:
            self.test_requires("gtest/1.11.0")

    def build(self):
        cmd = f"cmake -S {self.source_folder} -B {self.build_folder} -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE={self.settings.build_type}"
        cmd += " -DBUILD_TESTS=ON" if self.options.build_tests else " -DBUILD_TESTS=OFF"
        cmd += " -DBUILD_EXAMPLE=ON" if self.options.build_example else " -DBUILD_EXAMPLE=OFF"
        self.run(cmd)
        self.run(f"cmake --build {self.build_folder}")

    def package(self):
        strip_option = "--strip" if self.settings.build_type == "Release" else ""
        self.run(f"cmake --install {self.build_folder} --prefix {self.package_folder} {strip_option}")

    def package_id(self):
        del self.info.options.build_tests
        del self.info.options.build_example

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "config")
        self.cpp_info.set_property("cmake_file_name", "JsonRpc")
        self.cpp_info.set_property("cmake_target_name", "JsonRpc::JsonRpc")
        suffix = "d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.libs = [f"hotp{suffix}"]
