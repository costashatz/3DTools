###Simple Templated Mathematics Library for 3D Graphics

####How to compile:

```
cd path/to/3DTools
mkdir build && cd build
cmake ..
make
```

* Optional CMake options:
	1. BUILD_TEST (ON/OFF) - Determine to either build tests or not. Defaults to OFF.
	2. BUILD_EXAMPLES (ON/OFF) - Specify whether you want to build tests or not. Defaults to OFF.

####How to use:

* You can just edit the CMakeLists.txt and include the headers to your project (after all it is just a header library).
* Via ExternalProject to always get latest edition:
	```cmake
	include(ExternalProject)
	ExternalProject_Add(3DToolsProj
	    GIT_REPOSITORY "https://github.com/costashatz/3DTools"
	    CMAKE_ARGS -DBUILD_TEST=OFF -DBUILD_EXAMPLES=OFF
	    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
	    INSTALL_COMMAND ""
	)
	# Specify include dir
	ExternalProject_Get_Property(3DToolsProj source_dir)
	set(3DTOOLS_INCLUDE_DIRS ${source_dir}/include)

	# Specify MainTest's link libraries
	ExternalProject_Get_Property(3DToolsProj binary_dir)
	set(3DTOOLS_LIBS_DIR ${binary_dir})

	link_directories(${3DTOOLS_LIBS_DIR})
	include_directories(${PROJECT_SOURCE_DIR}/include ${3DTOOLS_INCLUDE_DIRS})
	....
	target_link_libraries(mytarget 3DTools)
	```

####So far I have implemented:

1. Vector3D
    * Simple Class for handling Vectors and Points (maybe needs fourth component and new class for Points)
2. Matrix3D
    * Simple Class for 4x4 Matrices needed (now is column major representation and multiplying with a vector by either side has the same effect)
3. Simple Unit Tests with gtest

####Planning to implement:

1. LinearShapes
	* Simple Classes for Linear Shapes (Line, Ray, Segment)
2. PlanarShapes
	* Planes, e.t.c.
3. Polymeshes, Polyhedra, Polytopes

4. Quadratic Surfaces
	* Three nonzero eigenvalues, two nonzero eigenvalues, ...
5. Polynomial Curves
    * Bezier
    * B-Spline
    * NURBS
6. Intersections3D
    * Find intersections (intersection area, points, true/false) between all the 3D primitives/shapes above
7. Distances3D
	* Find distances between shapes/primitives
8. BSP Trees in 3D
9. Miscellaneous Topics in 3D
    * Convex Hulls
    * Triangulation
    * Area/Volume Measurement

####So far I have tested and are working properly:

1. Vector3D
2. Matrix3D


####WORK IN PROGRESS - WILL BE UPDATED FREQUENTLY

I am currently working on this little library and will be pushing more updated stuff. Any suggestions of course are more than welcomed.