#include "number.h"
#include "real.hpp"
#include "complex.hpp"

namespace AlgoLib::Math{
    Real operator + (const Real& x, const Real& y){
        Real res(x);
        res.m_number += y.m_number;
        return res;
    }
    
    Real operator - (const Real& x, const Real& y){
        Real res(x);
        res.m_number -= y.m_number;
        return res;
    }

    Real operator * (const Real& x, const Real& y){
        Real res(x);
        res.m_number *= y.m_number;
        return res;
    }

    Real operator / (const Real& x, const Real& y){
        Real res(x);
        res.m_number /= y.m_number;
        return res;
    }

    bool operator > (const Real& x, const Real& y){
        return x.m_number > y.m_number;
    }
    
    bool operator < (const Real& x, const Real& y){
        return x.m_number < y.m_number;
    }

    bool operator == (const Real& x, const Real& y){
        return x.m_number == y.m_number;
    }

    bool operator != (const Real& x, const Real& y){
        return x.m_number != y.m_number;
    }

    bool operator >= (const Real& x, const Real& y){
        return x.m_number >= y.m_number;
    }

    bool operator <= (const Real& x, const Real& y){
        return x.m_number <= y.m_number;
    }
    
    Real::operator Complex() const {
        return Complex(m_number, 0);
    }
} // namespace AlgoLib::Math
