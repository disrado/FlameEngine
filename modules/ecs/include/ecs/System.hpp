#pragma once

namespace flm
{

class System
{
public:
    virtual ~System();

    virtual void Update(float dt) = 0;
};


} // namepsace flm