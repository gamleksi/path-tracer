# Path-Tracer for C++ programming project

The path tracer supports physical geometries, precisely spheres, rectangles (xy, xz and yz planes) and boxes. Each object can be built with different material models like dielectrics (e.g. glass, water), solid textures (e.g. RGB colors and textures like checker) as well as metal (albedo). In addition, each object can be assigned as diffuse material meaning that it emits light to the scene. Also, a normal map is available. Images are constructed with minimal noise by anti-aliasing meaning that rays are sent multiple times through pixels and the result is averaged. The amount of anti-aliasing can be controlled by the user. The camera can be moved to all directions as well as rotated. In addition, focus distance, field of view, aspect and aperture can be modified.

Performance-wise rendering is accelerated by a bounding volume hierarchy. The software is also parallelized to enable computing with all cores of the CPU.

