#pragma once

#include "../BaseShape.hpp"
#include "../Cookable.hpp"

struct Quad :
    public Cookable,
    public BaseShape
{
    Quad();
    ~Quad() = default;

    void draw() override;
};