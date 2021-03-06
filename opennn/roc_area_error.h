/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   R O C   A R E A   E R R O R   C L A S S   H E A D E R                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __ROCAREAERROR_H__
#define __ROCAREAERROR_H__

// System includes

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>

// OpenNN includes

#include "performance_term.h"
#include "data_set.h"
#include "numerical_integration.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the sum squared peformance term functional.
/// This is used as the performance term in data modeling problems, such as function regression,
/// pattern recognition or time series prediction.
class RocAreaError : public PerformanceTerm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit RocAreaError();

    // NEURAL NETWORK CONSTRUCTOR
    explicit RocAreaError(NeuralNetwork *);

    // DATA SET CONSTRUCTOR
    explicit RocAreaError(DataSet *);

    // GENERAL CONSTRUCTOR
    explicit RocAreaError(NeuralNetwork *, DataSet *);

    // XML CONSTRUCTOR
    explicit RocAreaError(const tinyxml2::XMLDocument &);

    // COPY CONSTRUCTOR
    RocAreaError(const RocAreaError &);

    // DESTRUCTOR
    virtual ~RocAreaError();

    // Checking methods
    void check() const;

    // performance methods
    double calculate_performance() const;

    Vector<double> calculate_output_gradient(const Vector<double> &, const Vector<double> &) const;

    Vector<double> calculate_gradient() const;

    double calculate_performance(const Vector<double> &) const;

private:
    NumericalIntegration numerical_integration;
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
