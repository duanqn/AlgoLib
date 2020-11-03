#pragma once

#include <string>
#include <vector>
#include <cstdio>

namespace AlgoLib::String{
    template<typename C>
    std::vector<std::basic_string<C>> split(std::basic_string<C> s, C splitChar){
        int segStart = 0, index = 0;
        std::vector<std::basic_string<C>> ret;

        for(; index < s.length(); ++index){
            if(s[index] == splitChar){
                if(index > segStart){
                    std::basic_string<C> segment(s, segStart, index - segStart);
                    ret.push_back(std::move(segment));
                }
                segStart = index + 1;
            }
        }

        if(index > segStart){
            std::basic_string<C> segment(s, segStart, index - segStart);
            ret.push_back(std::move(segment));
        }

        return ret;
    }
}
