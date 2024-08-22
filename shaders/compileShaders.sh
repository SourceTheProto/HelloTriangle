#!/bin/bash

# Compiling GLSL Shaders to SPIR-V bytecode
glslc -O -fshader-stage=vert ../shaders/triangleVert.glsl -o ../shaders/compiled/triangleVert.spv
glslc -O -fshader-stage=frag ../shaders/triangleFrag.glsl -o ../shaders/compiled/triangleFrag.spv
