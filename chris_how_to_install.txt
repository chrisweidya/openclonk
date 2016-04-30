Installation and run instructions for FYP openclonk PCG project. Tested on Win 7 64-bit.

1. Install VS 2015.

2. Install C++ compilers by creating new C++ project.

3. Clone repository from: https://github.com/chrisweidya/openclonk.git.

4. Extract dependencies zip to project folder.

5. Install cmake.

6. Run cmake.

7. Set source code and binary build directories to where the project folder is.

8. Click configure and set generator to Visual Studio 2015.

9. It's okay if there are some errors, click Generate. A VS sln file should be generated.

10. Run the solution file.

11. At the solution explorer, rightclick "openclonk" and set it as startup project.

12. Again, right click "openclonk and go to properties"

13. Go to Linker -> General. Under "Additional Library Directories", add the path to "<your project folder path>\deps\lib".

14. Go to Linker -> Input. Under "Additional Dependencies", append ";libcurl.lib".

///////// Note that steps 12 - 14 has to be repeated if you change environment from Debug to Release or vice versa. In general, if there are any errors related to curl, it should be due to incorrect linking.///////

15. Run the project. (Go to properties -> Linker -> System and change subsystem to console to see console)