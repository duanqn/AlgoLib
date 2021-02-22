#pragma once

#include "number.h"
#include "real.hpp"

namespace AlgoLib::Math{

    class Complex final: public Number{
        private:
        Real m_realpart;
        Real m_imagpart;

        public:
        Complex(): m_realpart(0), m_imagpart(0){}
        Complex(double real, double imag): m_realpart(real), m_imagpart(imag){}
        Complex(Real&& real): m_realpart(real), m_imagpart(0){}
        Complex(Real&& real, Real&& imag): m_realpart(real), m_imagpart(imag){}
        Complex(const Complex& other) = default;
        Complex(Complex&& other) = default;

        ~Complex(){}

        Complex _conjugate(){
            m_imagpart._neg();
        }

        Complex conjugate(){
            Complex res(*this);
            res.m_imagpart._neg();
            return res;
        }

    };

}