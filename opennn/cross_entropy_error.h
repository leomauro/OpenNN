/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   C R O S S   E N T R O P Y   E R R O R   C L A S S   H E A D E R                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __CROSSENTROPYERROR_H__
#define __CROSSENTROPYERROR_H__

// System includes

#include <iostream>
#include <fstream>
#include <math.h>

// OpenNN includes

#include "performance_term.h"
#include "data_set.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the cross entropy performance term.
/// This functional is used in pattern recognition problems.
class CrossEntropyError : public PerformanceTerm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit CrossEntropyError();

    // NEURAL NETWORK CONSTRUCTOR
    explicit CrossEntropyError(NeuralNetwork *);

    // DATA SET CONSTRUCTOR
    explicit CrossEntropyError(DataSet *);

    // GENERAL CONSTRUCTOR
    explicit CrossEntropyError(NeuralNetwork *, DataSet *);

    // XML CONSTRUCTOR
    explicit CrossEntropyError(const tinyxml2::XMLDocument &);

    // COPY CONSTRUCTOR
    CrossEntropyError(const CrossEntropyError &);

    // DESTRUCTOR
    virtual ~CrossEntropyError();

    // ASSIGNMENT OPERATOR
    CrossEntropyError &operator=(const CrossEntropyError &);

    // EQUAL TO OPERATOR
    bool operator==(const CrossEntropyError &) const;

    // Checking methods
    void check() const;

    // performance methods
    double calculate_performance() const;

    double calculate_performance(const Vector<double> &) const;

    double calculate_minimum_performance() const;

    double calculate_selection_performance() const;

    double calculate_minimum_selection_performance() const;

    Vector<double> calculate_gradient() const;

    Matrix<double> calculate_Hessian() const;

    std::string write_performance_term_type() const;

    // Serialization methods
    tinyxml2::XMLDocument *to_XML() const;

    void from_XML(const tinyxml2::XMLDocument &);
};


}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright (c) 2005-2016 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
