/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   C L A S S   H E A D E R                                                    */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MODELSELECTION_H__
#define __MODELSELECTION_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "training_strategy.h"

#include "incremental_order.h"
#include "golden_section_order.h"
#include "simulated_annealing_order.h"

#include "growing_inputs.h"
#include "pruning_inputs.h"
#include "genetic_algorithm.h"

#include "f1_score_optimization_threshold.h"
#include "matthew_correlation_optimization_threshold.h"
#include "youden_index_optimization_threshold.h"
#include "kappa_coefficient_optimization_threshold.h"
#include "roc_curve_optimization_threshold.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the concept of model selection algorithm.
/// It is used for finding a network architecture with maximum selection capabilities.
class ModelSelection
{
public:
    // DEFAULT CONSTRUCTOR
    explicit ModelSelection();

    // TRAINING STRATEGY CONSTRUCTOR
    explicit ModelSelection(TrainingStrategy *);

    // FILE CONSTRUCTOR
    explicit ModelSelection(const std::string &);

    // XML CONSTRUCTOR
    explicit ModelSelection(const tinyxml2::XMLDocument &);

    // DESTRUCTOR
    virtual ~ModelSelection();

    /// Enumeration of all the available types of inputs selection algorithms.
    enum InputsSelectionType {
        NO_INPUTS_SELECTION,
        GROWING_INPUTS,
        PRUNING_INPUTS,
        GENETIC_ALGORITHM
    };

    /// Enumeration of all the available types of order selection algorithms.
    enum OrderSelectionType {
        NO_ORDER_SELECTION,
        INCREMENTAL_ORDER,
        GOLDEN_SECTION,
        SIMULATED_ANNEALING
    };

    /// Enumeration of all the available types of threshold selection algorithms.
    enum ThresholdSelectionType {
        NO_THRESHOLD_SELECTION,
        F1_SCORE_OPTIMIZATION,
        MATTHEW_CORRELATION,
        YOUDEN_INDEX,
        KAPPA_COEFFICIENT,
        ROC_CURVE_DISTANCE
    };

    ///
    /// This structure contains the results from the model selection process.
    ///
    struct ModelSelectionResults {
        void save(const std::string &) const;

        // Order selection results
        /// Pointer to a structure with the results from the incremental order selection algorithm.
        IncrementalOrder::IncrementalOrderResults *incremental_order_results_pointer;

        /// Pointer to a structure with the results from the golden section order selection algorithm.
        GoldenSectionOrder::GoldenSectionOrderResults *golden_section_order_results_pointer;

        /// Pointer to a structure with the results from the simulated annealing order selection algorithm.
        SimulatedAnnealingOrder::SimulatedAnnealingOrderResults *simulated_annealing_order_results_pointer;

        /// Pointer to a structure with the results from the growing inputs selection algorithm.
        GrowingInputs::GrowingInputsResults *growing_inputs_results_pointer;

        /// Pointer to a structure with the results from the pruning inputs selection algorithm.
        PruningInputs::PruningInputsResults *pruning_inputs_results_pointer;

        /// Pointer to a structure with the results from the genetic inputs selection algorithm.
        GeneticAlgorithm::GeneticAlgorithmResults *genetic_algorithm_results_pointer;

        /// Pointer to a structure with the results from the f1 score optimization threshold selection algorithm.
        F1ScoreOptimizationThreshold::F1ScoreOptimizationThresholdResults *f1_score_opimization_results_pointer;

        /// Pointer to a structure with the results from the matthew correlation optimization threshold selection algorithm.
        MatthewCorrelationOptimizationThreshold::MatthewCorrelationOptimizationThresholdResults *matthew_correlation_optimization_results_pointer;

        /// Pointer to a structure with the results from the youden index optimization threshold selection algorithm.
        YoudenIndexOptimizationThreshold::YoudenIndexOptimizationThresholdResults *youden_index_optimization_results_pointer;

        /// Pointer to a structure with the results from the kappa coefficient optimization threshold selection algorithm.
        KappaCoefficientOptimizationThreshold::KappaCoefficientOptimizationThresholdResults *kappa_coefficient_optimization_results_pointer;

        /// Pointer to a structure with the results from the roc curve optimization threshold selection algorithm.
        ROCCurveOptimizationThreshold::ROCCurveOptimizationThresholdResults *roc_curve_optimization_results_pointer;
    };

    // Get methods
    TrainingStrategy *get_training_strategy_pointer() const;

    bool has_training_strategy() const;

    const OrderSelectionType &get_order_selection_type() const;

    const InputsSelectionType &get_inputs_selection_type() const;

    const ThresholdSelectionType &get_threshold_selection_type() const;

    IncrementalOrder *get_incremental_order_pointer() const;

    GoldenSectionOrder *get_golden_section_order_pointer() const;

    SimulatedAnnealingOrder *get_simulated_annealing_order_pointer() const;

    GrowingInputs *get_growing_inputs_pointer() const;

    PruningInputs *get_pruning_inputs_pointer() const;

    GeneticAlgorithm *get_genetic_algorithm_pointer() const;

    F1ScoreOptimizationThreshold *get_f1_score_optimization_threshold_pointer() const;

    MatthewCorrelationOptimizationThreshold *get_matthew_correlation_optimization_threshold() const;

    YoudenIndexOptimizationThreshold *get_youden_index_optimization_threshold() const;

    KappaCoefficientOptimizationThreshold *get_kappa_coefficient_optimization_threshold() const;

    ROCCurveOptimizationThreshold *get_roc_curve_optimization_threshold() const;

    // Set methods
    void set_default();

    void set_training_strategy_pointer(TrainingStrategy *);

    void set_order_selection_type(const OrderSelectionType &);

    void set_order_selection_type(const std::string &);

    void set_inputs_selection_type(const InputsSelectionType &);

    void set_inputs_selection_type(const std::string &);

    void set_threshold_selection_type(const ThresholdSelectionType &);

    void set_threshold_selection_type(const std::string &);

    void set_function_regression(const bool &);

    // Pointer methods
    void destruct_order_selection();

    void destruct_inputs_selection();

    void destruct_threshold_selection();

    // Model selection methods
    void check() const;

    ModelSelectionResults perform_order_selection() const;

    ModelSelectionResults perform_inputs_selection() const;

    ModelSelectionResults perform_threshold_selection() const;

    ModelSelectionResults perform_model_selection() const;

    // Serialization methods
    tinyxml2::XMLDocument *to_XML() const;

    void from_XML(const tinyxml2::XMLDocument &);

    void print() const;

    void save(const std::string &) const;

    void load(const std::string &);

private:
    /// Pointer to a training strategy object.
    TrainingStrategy *training_strategy_pointer;

    /// Pointer to a incremental order object to be used in the order selection.
    IncrementalOrder *incremental_order_pointer;

    /// Pointer to a golden section order object to be used in the order selection.
    GoldenSectionOrder *golden_section_order_pointer;

    /// Pointer to a simulated annealing order object to be used in the order selection.
    SimulatedAnnealingOrder *simulated_annelaing_order_pointer;

    /// Pointer to a growing inputs object to be used in the inputs selection.
    GrowingInputs *growing_inputs_pointer;

    /// Pointer to a pruning inputs object to be used in the inputs selection.
    PruningInputs *pruning_inputs_pointer;

    /// Pointer to a genetic algorithm object to be used in the inputs selection.
    GeneticAlgorithm *genetic_algorithm_pointer;

    /// Pointer to a f1 score optimization object to be used in the inputs selection.
    F1ScoreOptimizationThreshold *f1_score_optimization_threshold_pointer;

    /// Pointer to a matthew correlation optimization object to be used in the threshold selection.
    MatthewCorrelationOptimizationThreshold *matthew_correlation_optimization_threshold_pointer;

    /// Pointer to a youden index optimization object to be used in the threshold selection.
    YoudenIndexOptimizationThreshold *youden_index_optimization_threshold_pointer;

    /// Pointer to a kappa coefficient optimization object to be used in the threshold selection.
    KappaCoefficientOptimizationThreshold *kappa_coefficient_optimization_threshold_pointer;

    /// Pointer to a roc curve distance optimization object to be used in the threshold selection.
    ROCCurveOptimizationThreshold *roc_curve_optimization_threshold_pointer;

    /// Type of order selection algorithm.
    OrderSelectionType order_selection_type;

    /// Type of inputs selection algorithm.
    InputsSelectionType inputs_selection_type;

    /// Type of threshold selection algorithm.
    ThresholdSelectionType threshold_selection_type;
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
