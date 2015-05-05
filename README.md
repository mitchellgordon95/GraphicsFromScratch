# GraphicsFromScratch

This is a graphics-oriented command line interface that has some of the basic features of industry standard computer graphics applications, like Renderman or Photoshop. It was created originally as a semester-long project for CS 258, Introduction to Computer Graphics, as an exercise in understanding. It's built on top of OpenGL for cross platform window support, but as the name suggests, it attempts to implement most features using basic C++ functionality.

## Features

- A TIFF file reader and writer (for certain parts of the scheme, including 24-bit RGB and 8-bit Grayscale)
- Image resizing with convolution filters (Gaussian, Lanczos, etc.) to prevent image degradation.
- Line drawing in 3D coordinate space using a transformation pipeline
- A basic raytracer, which implements diffuse and specular objects, ambient light sources, and light sources at an infinite distance.
