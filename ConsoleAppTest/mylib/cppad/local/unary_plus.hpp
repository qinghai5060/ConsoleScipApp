/* $Id: unary_plus.hpp 2506 2012-10-24 19:36:49Z bradbell $ */
# ifndef CPPAD_UNARY_PLUS_INCLUDED
# define CPPAD_UNARY_PLUS_INCLUDED

/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-12 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the 
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

/*
$begin UnaryPlus$$
$spell
	Vec
	const
	inline
$$

$index unary, AD plus operator$$
$index AD, unary plus operator$$
$index plus, AD unary operator$$
$index +, AD unary operator$$

$section AD Unary Plus Operator$$

$head Syntax$$

$icode%y% = + %x%$$


$head Purpose$$
Performs the unary plus operation
(the result $icode y$$ is equal to the operand $icode x$$).


$head x$$
The operand $icode x$$ has one of the following prototypes
$codei%
	const AD<%Base%>               &%x%
	const VecAD<%Base%>::reference &%x%
%$$

$head y$$
The result $icode y$$ has type
$codei%
	AD<%Base%> %y%
%$$
It is equal to the operand $icode x$$.

$head Operation Sequence$$
This is an AD of $icode Base$$
$cref/atomic operation/glossary/Operation/Atomic/$$
and hence is part of the current
AD of $icode Base$$
$cref/operation sequence/glossary/Operation/Sequence/$$.

$head Derivative$$
If $latex f$$ is a 
$cref/Base function/glossary/Base Function/$$,
$latex \[
	\D{[ + f(x) ]}{x} = \D{f(x)}{x}
\] $$



$head Example$$
$children%
	example/unary_plus.cpp
%$$
The file
$cref unary_plus.cpp$$
contains an example and test of this operation.

$end
-------------------------------------------------------------------------------
*/

//  BEGIN CppAD namespace
namespace CppAD {

template <class Base>
inline AD<Base> AD<Base>::operator + (void) const 
{	AD<Base> result(*this);

	return result;
}


template <class Base>
inline AD<Base> operator + (const VecAD_reference<Base> &right) 
{	return right.ADBase(); }

}
//  END CppAD namespace


# endif
