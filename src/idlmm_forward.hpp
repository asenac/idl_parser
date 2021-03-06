// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * idlmm_forward.hpp
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

#ifndef _IDLMM_FORWARD_HPP
#define _IDLMM_FORWARD_HPP

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

/*PROTECTED REGION ID(idlmm_forward) ENABLED START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here

namespace idlmm
{
    class IdlmmVisitor;
} // namespace idlmm
/*PROTECTED REGION END*/

// EPackage
namespace idlmm
{

    // EDataType
    /*PROTECTED REGION ID(idlmm_ParameterMode) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    enum ParameterMode
    {
        PARAM_IN,
        PARAM_OUT,
        PARAM_INOUT
    };
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(idlmm_PrimitiveKind) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    enum PrimitiveKind
    {
        PK_NULL,
        PK_VOID,
        PK_SHORT,
        PK_LONG,
        PK_USHORT,
        PK_ULONG,
        PK_FLOAT,
        PK_DOUBLE,
        PK_BOOLEAN,
        PK_CHAR,
        PK_OCTET,
        PK_ANY,
        PK_LONGDOUBLE,
        PK_WSTRING,
        PK_TYPECODE,
        PK_WCHAR,
        PK_PRINCIPAL,
        PK_STRING,
        PK_ULONGLONG,
        PK_OBJREF,
        PK_LONGLONG
    };
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(idlmm_EAny) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EAny;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(idlmm_ETypeCode) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int ETypeCode;
    /*PROTECTED REGION END*/

    // EClass

    // ModelElement
    class ModelElement;
    typedef ModelElement* ModelElement_ptr;

    // Container
    class Container;
    typedef Container* Container_ptr;

    // Contained
    class Contained;
    typedef Contained* Contained_ptr;

    // InterfaceDef
    class InterfaceDef;
    typedef InterfaceDef* InterfaceDef_ptr;

    // ModuleDef
    class ModuleDef;
    typedef ModuleDef* ModuleDef_ptr;

    // IDLType
    class IDLType;
    typedef IDLType* IDLType_ptr;

    // OperationDef
    class OperationDef;
    typedef OperationDef* OperationDef_ptr;

    // AttributeDef
    class AttributeDef;
    typedef AttributeDef* AttributeDef_ptr;

    // ConstantDef
    class ConstantDef;
    typedef ConstantDef* ConstantDef_ptr;

    // Typed
    class Typed;
    typedef Typed* Typed_ptr;

    // ParameterDef
    class ParameterDef;
    typedef ParameterDef* ParameterDef_ptr;

    // PrimitiveDef
    class PrimitiveDef;
    typedef PrimitiveDef* PrimitiveDef_ptr;

    // ExceptionDef
    class ExceptionDef;
    typedef ExceptionDef* ExceptionDef_ptr;

    // Field
    class Field;
    typedef Field* Field_ptr;

    // FixedDef
    class FixedDef;
    typedef FixedDef* FixedDef_ptr;

    // WstringDef
    class WstringDef;
    typedef WstringDef* WstringDef_ptr;

    // StringDef
    class StringDef;
    typedef StringDef* StringDef_ptr;

    // AliasDef
    class AliasDef;
    typedef AliasDef* AliasDef_ptr;

    // ArrayDef
    class ArrayDef;
    typedef ArrayDef* ArrayDef_ptr;

    // SequenceDef
    class SequenceDef;
    typedef SequenceDef* SequenceDef_ptr;

    // UnionField
    class UnionField;
    typedef UnionField* UnionField_ptr;

    // TypedefDef
    class TypedefDef;
    typedef TypedefDef* TypedefDef_ptr;

    // UnionDef
    class UnionDef;
    typedef UnionDef* UnionDef_ptr;

    // EnumDef
    class EnumDef;
    typedef EnumDef* EnumDef_ptr;

    // StructDef
    class StructDef;
    typedef StructDef* StructDef_ptr;

    // TranslationUnit
    class TranslationUnit;
    typedef TranslationUnit* TranslationUnit_ptr;

    // Include
    class Include;
    typedef Include* Include_ptr;

    // Expression
    class Expression;
    typedef Expression* Expression_ptr;

    // BinaryExpression
    class BinaryExpression;
    typedef BinaryExpression* BinaryExpression_ptr;

    // UnaryExpression
    class UnaryExpression;
    typedef UnaryExpression* UnaryExpression_ptr;

    // LiteralExpression
    class LiteralExpression;
    typedef LiteralExpression* LiteralExpression_ptr;

    // ConstantDefRef
    class ConstantDefRef;
    typedef ConstantDefRef* ConstantDefRef_ptr;

    // ValueExpression
    class ValueExpression;
    typedef ValueExpression* ValueExpression_ptr;

    // ForwardDef
    class ForwardDef;
    typedef ForwardDef* ForwardDef_ptr;

    // EnumMember
    class EnumMember;
    typedef EnumMember* EnumMember_ptr;

    // Constant
    class Constant;
    typedef Constant* Constant_ptr;

    // NamedElement
    class NamedElement;
    typedef NamedElement* NamedElement_ptr;

    // Package & Factory
    class IdlmmFactory;
    typedef IdlmmFactory * IdlmmFactory_ptr;
    class IdlmmPackage;
    typedef IdlmmPackage * IdlmmPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // idlmm
#endif // _IDLMM_FORWARD_HPP
