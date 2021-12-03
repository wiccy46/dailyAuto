from conans import ConanFile, CMake

class CppStarterConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = ["gtest/1.11.0", "boost/1.77.0"]
   generators = "cmake", "gcc"
   default_options = {}

   def imports(self):
      self.copy("*.dll", "bin", "bin")
      self.copy("*.dylib", "bin", "lib")

   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()
      cmake.test()
