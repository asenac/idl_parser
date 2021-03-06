// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * idlmm/AttributeDef.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IDLMM_ATTRIBUTEDEF_HPP
#define IDLMM_ATTRIBUTEDEF_HPP

#include <idlmm_forward.hpp>

#include <idlmm/Contained.hpp>
#include <idlmm/Typed.hpp>

/*PROTECTED REGION ID(AttributeDef_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace idlmm
{

    class AttributeDef: public virtual ::idlmm::Contained,
            public virtual ::idlmm::Typed
    {
    public:
        AttributeDef();

        virtual ~AttributeDef();

        // Operations
        // Attributes
        bool isIsReadonly() const;
        void setIsReadonly(bool _isReadonly);

        // References
        typedef boost::ptr_vector< ::idlmm::ExceptionDef > GetRaises_t;
        GetRaises_t& getGetRaises();

        typedef boost::ptr_vector< ::idlmm::ExceptionDef > SetRaises_t;
        SetRaises_t& getSetRaises();

        /*PROTECTED REGION ID(AttributeDef) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        /*PROTECTED REGION ID(AttributeDefImpl) ENABLED START*/

        virtual void accept(IdlmmVisitor& visitor);

        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        bool m_isReadonly;

        // References

        boost::ptr_vector<
                ::idlmm::ExceptionDef > m_getRaises;

        boost::ptr_vector<
                ::idlmm::ExceptionDef > m_setRaises;

    };

} // idlmm

#endif // IDLMM_ATTRIBUTEDEF_HPP
