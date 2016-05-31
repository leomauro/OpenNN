/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   T R A I N I N G   A L G O R I T H M   C L A S S   H E A D E R                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __TRAININGALGORITHM_H__
#define __TRAININGALGORITHM_H__

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "performance_functional.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This abstract class represents the concept of training algorithm for a neural network.
/// Any derived class must implement the perform_training() method.
class TrainingAlgorithm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit TrainingAlgorithm();

    // GENERAL CONSTRUCTOR
    explicit TrainingAlgorithm(PerformanceFunctional *);

    // XML CONSTRUCTOR
    explicit TrainingAlgorithm(const tinyxml2::XMLDocument &);

    // DESTRUCTOR
    virtual ~TrainingAlgorithm();

    // ASSIGNMENT OPERATOR
    virtual TrainingAlgorithm &operator=(const TrainingAlgorithm &);

    // EQUAL TO OPERATOR
    virtual bool operator==(const TrainingAlgorithm &) const;

    ///
    /// This structure contains the training algorithm results.
    ///
    struct TrainingAlgorithmResults {
        explicit TrainingAlgorithmResults()
        {
        }

        virtual ~TrainingAlgorithmResults()
        {
        }

        /// Returns a string representation of the results structure.
        virtual std::string to_string() const
        {
            std::string str;
            return str;
        }

        /// Returns a default (empty) string matrix with the final results from training.
        virtual Matrix<std::string> write_final_results(const size_t &) const
        {
            Matrix<std::string> final_results;
            return final_results;
        }
    };

    // Get methods
    PerformanceFunctional *get_performance_functional_pointer() const;

    bool has_performance_functional() const;

    // Utilities
    const bool &get_display() const;

    const size_t &get_display_period() const;

    const size_t &get_save_period() const;

    const std::string &get_neural_network_file_name() const;

    // Set methods
    void set();

    void set(PerformanceFunctional *);

    virtual void set_default();

    virtual void set_performance_functional_pointer(PerformanceFunctional *);

    void set_display(const bool &);

    void set_display_period(const size_t &);

    void set_save_period(const size_t &);

    void set_neural_network_file_name(const std::string &);

    // Training methods
    virtual void check() const;

    /// Trains a neural network which has a performance functional associated.
    virtual TrainingAlgorithmResults *perform_training() = 0;

    virtual std::string write_training_algorithm_type() const;

    // Serialization methods
    virtual std::string to_string() const;

    void print() const;

    virtual Matrix<std::string> to_string_matrix() const;

    virtual tinyxml2::XMLDocument *to_XML() const;

    virtual void from_XML(const tinyxml2::XMLDocument &);

    void save(const std::string &) const;

    void load(const std::string &);

    virtual void initialize_random();

protected:
    /// Pointer to a performance functional for a multilayer perceptron object.
    PerformanceFunctional *performance_functional_pointer;

    /// Number of iterations between the training showing progress.
    size_t display_period;

    /// Number of iterations between the training saving progress.
    size_t save_period;

    /// Path where the neural network is saved.
    std::string neural_network_file_name;

    /// Display messages to screen.
    bool display;
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
