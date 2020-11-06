#pragma once

#include "number.h"

namespace AlgoLib::Math{

    class Real final: public Number{
        private:
        double m_number;

        public:
        Real(): m_number(0){}
        Real(double num): m_number(num){}
        Real(const Real& other) = default;
        Real(Real&& other) = default;

        ~Real(){}

        void _neg(){
            m_number = -m_number;
        }

        Real neg(){
            Real res(*this);
            res._neg();
            return res;
        }

        friend Real operator + (const Real& x, const Real& y);
        friend Real operator - (const Real& x, const Real& y);
        friend Real operator * (const Real& x, const Real& y);
        friend Real operator / (const Real& x, const Real& y);

        friend bool operator > (const Real& x, const Real& y);
        friend bool operator < (const Real& x, const Real& y);
        friend bool operator == (const Real& x, const Real& y);
        friend bool operator != (const Real& x, const Real& y);
        friend bool operator >= (const Real& x, const Real& y);
        friend bool operator <= (const Real& x, const Real& y);

        operator Complex() const;
        
    };

}
