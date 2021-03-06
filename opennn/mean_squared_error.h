/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   M E A N   S Q U A R E D   E R R O R    C L A S S   H E A D E R                                             */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MEANSQUAREDERROR_H__
#define __MEANSQUAREDERROR_H__

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>

// OpenNN includes

#include "performance_term.h"
#include "data_set.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the mean squared error performance term.
/// The mean squared error measures the difference between the outputs from a neural network and the targets in a data set.
/// This functional is used in data modeling problems, such as function regression,
/// pattern recognition and time series prediction.
class MeanSquaredError : public PerformanceTerm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit MeanSquaredError();

    // NEURAL NETWORK CONSTRUCTOR
    explicit MeanSquaredError(NeuralNetwork *);

    // DATA SET CONSTRUCTOR
    explicit MeanSquaredError(DataSet *);

    // GENERAL CONSTRUCTOR
    explicit MeanSquaredError(NeuralNetwork *, DataSet *);

    // XML CONSTRUCTOR
    explicit MeanSquaredError(const tinyxml2::XMLDocument &);

    // COPY CONSTRUCTOR
    MeanSquaredError(const MeanSquaredError &);

    // DESTRUCTOR
    virtual ~MeanSquaredError();

    // Checking methods
    void check() const;

    // Objective methods
    double calculate_performance() const;

    double calculate_performance(const Vector<double> &) const;

    double calculate_selection_performance() const;

    Vector<double> calculate_output_gradient(const Vector<double> &, const Vector<double> &) const;

    Vector<double> calculate_gradient() const;

    Matrix<double> calculate_output_Hessian(const Vector<double> &, const Vector<double> &) const;

    Matrix<double> calculate_Hessian() const;

    FirstOrderPerformance calculate_first_order_performance() const;

    SecondOrderPerformance calculate_second_order_performance() const;

    // Objective terms methods
    Vector<double> calculate_terms() const;

    Vector<double> calculate_terms(const Vector<double> &) const;

    Matrix<double> calculate_terms_Jacobian() const;

    FirstOrderTerms calculate_first_order_terms() const;

    std::string write_performance_term_type() const;

    // Serialization methods
    tinyxml2::XMLDocument *to_XML() const;
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
