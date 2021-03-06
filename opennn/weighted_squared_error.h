/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   W E I G H T E D   S Q U A R E D   E R R O R    C L A S S   H E A D E R                                     */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __WEIGHTEDSQUAREDERROR_H__
#define __WEIGHTEDSQUAREDERROR_H__

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
class WeightedSquaredError : public PerformanceTerm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit WeightedSquaredError();

    // NEURAL NETWORK CONSTRUCTOR
    explicit WeightedSquaredError(NeuralNetwork *);

    // DATA SET CONSTRUCTOR
    explicit WeightedSquaredError(DataSet *);

    // GENERAL CONSTRUCTOR
    explicit WeightedSquaredError(NeuralNetwork *, DataSet *);

    // XML CONSTRUCTOR
    explicit WeightedSquaredError(const tinyxml2::XMLDocument &);

    // COPY CONSTRUCTOR
    WeightedSquaredError(const WeightedSquaredError &);

    // DESTRUCTOR
    virtual ~WeightedSquaredError();

    // Get methods
    double get_positives_weight() const;

    double get_negatives_weight() const;

    // Checking methods
    void check() const;

    // Objective methods
    void set_default();

    void set_positives_weight(const double &);

    void set_negatives_weight(const double &);

    void set_weights(const double &, const double &);

    void set_weights();

    double calculate_positives_performance() const;

    double calculate_negatives_performance() const;

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

    void from_XML(const tinyxml2::XMLDocument &);

    std::string write_information() const;

    std::string to_string() const;

private:
    double positives_weight;
    double negatives_weight;
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
