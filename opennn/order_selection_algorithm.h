/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   O R D E R   S E L E C T I O N   A L G O R I T H M   C L A S S   H E A D E R                                */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __ORDERSELECTIONALGORITHM_H__
#define __ORDERSELECTIONALGORITHM_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "training_strategy.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This abstract class represents the concept of order selection algorithm for a neural network.
/// Any derived class must implement the perform_order_selection() method.
class OrderSelectionAlgorithm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit OrderSelectionAlgorithm();

    // TRAINING STRATEGY CONSTRUCTOR
    explicit OrderSelectionAlgorithm(TrainingStrategy *);

    // FILE CONSTRUCTOR
    explicit OrderSelectionAlgorithm(const std::string &);

    // XML CONSTRUCTOR
    explicit OrderSelectionAlgorithm(const tinyxml2::XMLDocument &);

    // DESTRUCTOR
    virtual ~OrderSelectionAlgorithm();

    /// Enumeration of available methods for the calculus of the performances.
    enum PerformanceCalculationMethod {
        Minimum, Maximum, Mean
    };

    /// Enumeration of all possibles condition of stop for the algorithms.
    enum StoppingCondition {
        MaximumTime,
        SelectionPerformanceGoal,
        MaximumIterations,
        MaximumSelectionFailures,
        MinimumTemperature,
        AlgorithmFinished
    };

    ///
    /// This structure contains the results from the order selection.
    ///
    struct OrderSelectionResults {
        explicit OrderSelectionResults()
        {
        }

        virtual ~OrderSelectionResults()
        {
        }

        std::string write_stopping_condition() const;

        std::string to_string() const;

        /// Order of the diferent neural networks.
        Vector<size_t> order_data;

        /// Parameters of the different neural networks.
        Vector<Vector<double>> parameters_data;

        /// Performance of the different neural networks.
        Vector<double> performance_data;

        /// Selection performance of the different neural networks.
        Vector<double> selection_performance_data;

        /// Vector of parameters for the neural network with minimum selection performance.
        Vector<double> minimal_parameters;

        /// Value of minimum selection performance.
        double final_selection_performance;

        /// Value of performance for the neural network with minimum selection performance.
        double final_performance;

        /// Order of the neural network with minimum selection performance.
        size_t optimal_order;

        /// Number of iterations to perform the order selection.
        size_t iterations_number;

        /// Stopping condition of the algorithm.
        StoppingCondition stopping_condition;

        /// Elapsed time during the performance of the algortihm.
        double elapsed_time;
    };

    // Get methods
    TrainingStrategy *get_training_strategy_pointer() const;

    bool has_training_strategy() const;

    const size_t &get_maximum_order() const;

    const size_t &get_minimum_order() const;

    const size_t &get_trials_number() const;

    const bool &get_reserve_parameters_data() const;

    const bool &get_reserve_performance_data() const;

    const bool &get_reserve_selection_performance_data() const;

    const bool &get_reserve_minimal_parameters() const;

    const PerformanceCalculationMethod &get_performance_calculation_method() const;

    const bool &get_display() const;

    const double &get_selection_performance_goal() const;

    const size_t &get_maximum_iterations_number() const;

    const double &get_maximum_time() const;

    const double &get_tolerance() const;

    std::string write_performance_calculation_method() const;

    // Set methods
    void set_training_strategy_pointer(TrainingStrategy *);

    void set_default();

    void set_maximum_order(const size_t &);

    void set_minimum_order(const size_t &);

    void set_trials_number(const size_t &);

    void set_reserve_parameters_data(const bool &);

    void set_reserve_performance_data(const bool &);

    void set_reserve_selection_performance_data(const bool &);

    void set_reserve_minimal_parameters(const bool &);

    void set_performance_calculation_method(const PerformanceCalculationMethod &);

    void set_performance_calculation_method(const std::string &);

    void set_display(const bool &);

    void set_selection_performance_goal(const double &);

    void set_maximum_iterations_number(const size_t &);

    void set_maximum_time(const double &);

    void set_tolerance(const double &);

    // Performances calculation methods
    Vector<double> perform_minimum_model_evaluation(const size_t &);

    Vector<double> perform_maximum_model_evaluation(const size_t &);

    Vector<double> perform_mean_model_evaluation(const size_t &);

    Vector<double> get_final_performances(const TrainingStrategy::Results &) const;

    Vector<double> perform_model_evaluation(const size_t &);

    Vector<double> get_parameters_order(const size_t &) const;

    // order order selection methods
    void delete_selection_history();

    void delete_performance_history();

    void delete_parameters_history();

    void check() const;

    /// Performs the order selection for a neural network.
    virtual OrderSelectionResults *perform_order_selection() = 0;

protected:
    /// Pointer to a training strategy object.
    TrainingStrategy *training_strategy_pointer;

    /// Order of all the neural networks trained.
    Vector<size_t> order_history;

    /// Selection performance of all the neural networks trained.
    Vector<double> selection_performance_history;

    /// Performance of all the neural networks trained.
    Vector<double> performance_history;

    /// Parameters of all the neural network trained.
    Vector<Vector<double>> parameters_history;

    /// Number of minimum hidden perceptrons.
    size_t minimum_order;

    /// Number of maximum hidden perceptrons.
    size_t maximum_order;

    /// Number of trials for each neural network.
    size_t trials_number;

    /// Method used for the calculation of the performance and the generalizaton performance.
    PerformanceCalculationMethod performance_calculation_method;

    // Order selection results
    /// True if the parameters of all neural networks are to be reserved.
    bool reserve_parameters_data;

    /// True if the performance of all neural networks are to be reserved.
    bool reserve_performance_data;

    /// True if the selection performance of all neural networks are to be reserved.
    bool reserve_selection_performance_data;

    /// True if the vector parameters of the neural network presenting minimum selection performance is to be reserved.
    bool reserve_minimal_parameters;

    /// Display messages to screen.
    bool display;

    // STOPPING CRITERIA
    /// Goal value for the selection performance. It is used as a stopping criterion.
    double selection_performance_goal;

    /// Maximum number of iterations to perform_order_selection. It is used as a stopping criterion.
    size_t maximum_iterations_number;

    /// Maximum selection algorithm time. It is used as a stopping criterion.
    double maximum_time;

    /// Tolerance for the error in the trainings of the algorithm.
    double tolerance;
};


}

#endif // ORDERSELECTIONALGORITHM_H


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
