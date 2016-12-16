#Terrain Painter

Program constructs and interactively manipulates a plane mesh model, by generating terrain. This was done as part of a programming assignment for CPS 511. Geometric transformations, shape modeling, and simple animation are supported in this project.

##Introduction

This program constructs a mesh-plane that can be modified using the Guassian metaballs "Blobs" using the following formula -> ƒ(x, y) = ∑ₖ bₖeᵃₖʳₖ². I create the mesh of quadrilaterals using `QuadMesh.cpp`. The Blobs, and their influence fields are computed using the formula.

Everytime the user deposits a blob via a left mouse click, the plane mesh updates accordingly in real time. The user can use their mouse to "paint" on terrain on to this plane mesh. The properties of the Blobs are parameterized by user input (*keys, refer to the HUD*).

There are two modes in this program. You can use the program in **Editor** mode, where the painting tools are available to you to be able to draw on Blobs. The other mode being the **Viewer** mode where you can hold the left mouse button to move your camera. Clicking F1 will alternate between these two modes. 

The camera movement is all based on the azimuth/zenith spherical coordinate system in addition to setting hemisphere limits. In turn, this creates a camera mode that allows the user to pan/zoom/elevate the camera. 

For explicit use details, please refer to the in-program manual overlay.

##Implementation Details

The program was built on Windows and has been tested fully within a Windows environment to work. Although built on Windows, special care was taken to write platform agnostic code, and the program should be able to run on *nix platforms.

Source files (*located in the root folder directory*):
> main.cpp
> main.h
> QuadMesh.cpp
> QuadMesh.h
> Blob.cpp
> Blob.h
> VECTOR3D.h
> CMakeList.txt

##Libaries & Compilers
OpenGL

FreeGLUT was used for the window creation system (*instead of the deprecated GLUT*).

MinGW was used as the GNU standard compiler (*latest version*).
 -> https://sourceforge.net/projects/mingw/files/latest/download?source=files (*download link*)
 -> https://sourceforge.net/projects/mingw/files/ (*general download page*)

CMake was used to link, compile, and make the binaries of the program (latest version).
 -> https://cmake.org/files/v3.7/cmake-3.7.0-rc1-win64-x64.msi (download link)
 -> https://cmake.org/download/ (general download page)

##Compile, Build, Run

Below are Windows instructions on how to compile, make, build, and run the program yourself.

1. Make sure MinGW and CMake are installed on your PC, as well as added to your `PATH`.

   `'C:\Program Files\CMake\bin'` -> CMake path example.
   
   `'C:\MinGW\bin'` -> MinGW path example.

2. Place the source files mentioned above in a directory where you want to build the program (*generally a new folder*).

3. Open cmd in that directory and run the following commands:

    `> cmake -G "MinGW Makefiles"`

    This command will now create the makefiles nessecary, and link libraries.

    `> mingw32-make.exe all`
    
    This command will now build the program.

4. To run the program double click on the 'A2.exe' file (*newly created in the root*).

##Screenshot

![](http://i.imgur.com/fDIFsHk.png)
