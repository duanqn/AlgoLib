#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include "scaleArray.hpp"

namespace AlgoLib::String{
    namespace Internal{
        template<typename C, typename Container>
        Container _split(std::basic_string<C> s, C splitChar){
            using CString = std::basic_string<C>;
            int segStart = 0, index = 0;
            Container ret;

            for(; index < s.length(); ++index){
                if(s[index] == splitChar){
                    if(index > segStart){
                        CString segment(s, segStart, index - segStart);
                        ret.push_back(std::move(segment));
                    }
                    segStart = index + 1;
                }
            }

            if(index > segStart){
                CString segment(s, segStart, index - segStart);
                ret.push_back(std::move(segment));
            }

            return ret;
        }
    }   // Internal

    template<typename C, bool UseSTL = true>
    std::enable_if_t<UseSTL, std::vector<std::basic_string<C>>> split(std::basic_string<C> s, C splitChar){
        using CString = std::basic_string<C>;
        using Container = std::vector<CString>;
        
        return Internal::_split<C, Container>(s, splitChar);
    }

    template<typename C, bool UseSTL = true>
    std::enable_if_t<!UseSTL, AlgoLib::DataStructure::ScaleArray<std::basic_string<C>>> split(std::basic_string<C> s, C splitChar){
        using CString = std::basic_string<C>;
        using Container = AlgoLib::DataStructure::ScaleArray<CString>;
        
        return Internal::_split<C, Container>(s, splitChar);
    }
}   // AlgoLib::String
