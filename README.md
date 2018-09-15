# storm-in-a-glass
#### Implementation of simple physical model that describes behaviour of balls thrown into the water 
---

This simple project provides opportunity to look how spherical bodies of different sizes and densities behave in case they are thrown into the water (or any other liquid).

Simply run `build.sh` to compile this project.

**Note**: you have to install GLEW and GLHW libraries for OpenGL to compile this app

In order to run this app provide configuration file as an argument to the `storm-in-a-glass` executable. This file should contain parameters of the environment (such as its width, height, liquid level and etc.) You can find an example of such configuration file in a root directory of a project.

**Note**: `config.json` describes structure of configuration file, all described fields are required

**Note**: it's important to use MKS system of units when creating your own configuration file
