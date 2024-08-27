#!/bin/bash

# Compiling GLSL Shaders to SPIR-V bytecode
glslc -O -fshader-stage=vert ./triangleVert.glsl -o ../build/shaders/triangleVert.spv
glslc -O -fshader-stage=frag ./triangleFrag.glsl -o ../build/shaders/triangleFrag.spv
