#pragma once

namespace flm
{

class Entity;

class System
{
public:
    virtual ~System();

    virtual void Update(const float dt) = 0;
};


} // namepsace flm