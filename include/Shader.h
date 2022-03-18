#pragma once

struct Shader
{
    unsigned int programId;

    void bind();
    void compile();
};