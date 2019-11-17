#pragma once
#include <iostream>
#include <string>

void Assert(bool expression, std::string errmsg){
    if (!expression)
        std::cerr<<errmsg;
}