#pragma once

#include "../BaseShape.hpp"
#include "../Cookable.hpp"

struct Quad :
    public BaseShape,
    public Cookable
{
    Quad();
    ~Quad() = default;

    void draw();
};