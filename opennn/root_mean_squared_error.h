/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   R O O T   M E A N   S Q U A R E D   E R R O R   C L A S S   H E A D E R                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __ROOTMEANSQUAREDERROR_H__
#define __ROOTMEANSQUAREDERROR_H__

// System includes

#include <iostream>
#include <cmath>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>

// OpenNN includes

#include "performance_term.h"
#include "data_set.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the root mean squared error performance term.
/// The root mean squared error measures the difference between the outputs from a neural network and the targets in a data set.
/// This functional is used in data modeling problems.
class RootMeanSquaredError : public PerformanceTerm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit RootMeanSquaredError();

    // NEURAL NETWORK CONSTRUCTOR
    explicit RootMeanSquaredError(NeuralNetwork *);

    // DATA SET CONSTRUCTOR
    explicit RootMeanSquaredError(DataSet *);

    // GENERAL CONSTRUCTOR
    explicit RootMeanSquaredError(NeuralNetwork *, DataSet *);

    // XML CONSTRUCTOR
    explicit RootMeanSquaredError(const tinyxml2::XMLDocument &);

    // DESTRUCTOR
    virtual ~RootMeanSquaredError();

    // Checking methods
    void check() const;

    // Performance term performance methods
    double calculate_performance() const;

    double calculate_performance(const Vector<double> &) const;

    double calculate_selection_performance() const;

    Vector<double> calculate_output_gradient(const Vector<double> &, const Vector<double> &) const;

    Vector<double> calculate_gradient() const;

    Matrix<double> calculate_output_Hessian(const Vector<double> &, const Vector<double> &) const;

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
