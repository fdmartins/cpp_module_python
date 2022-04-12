from distutils.core import setup, Extension

def main():
    setup(name="cppModuleTest",
          version="1.0.0",
          description="Modulo C teste 2",
          author="<your name>",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("cppModuleTest", ["src/module.cpp"])])

if __name__ == "__main__":
    main()