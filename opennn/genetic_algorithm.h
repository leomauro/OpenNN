/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   G E N E T I C   A L G O R I T H M   C L A S S   H E A D E R                                                */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __GENETICALGORITHM_H__
#define __GENETICALGORITHM_H__

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "training_strategy.h"

#include "inputs_selection_algorithm.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

///
/// This concrete class represents a genetic algorithm for the inputs selection of a neural network.
///
class GeneticAlgorithm : public InputsSelectionAlgorithm
{
public:
    // DEFAULT CONSTRUCTOR
    explicit GeneticAlgorithm();

    // TRAINING STRATEGY CONSTRUCTOR
    explicit GeneticAlgorithm(TrainingStrategy *);

    // XML CONSTRUCTOR
    explicit GeneticAlgorithm(const tinyxml2::XMLDocument &);

    // FILE CONSTRUCTOR
    explicit GeneticAlgorithm(const std::string &);

    // DESTRUCTOR
    virtual ~GeneticAlgorithm();

    /// Enumeration of available methods for the initialization of the population.
    enum InitializationMethod {
        Random, Weigthed
    };

    /// Enumeration of available methods for the crossover of the population.
    enum CrossoverMethod {
        OnePoint, TwoPoint, Uniform
    };

    /// Enumeration of available methods for the fitness assignement of the population.
    enum FitnessAssignment {
        ObjectiveBased, RankBased
    };

    ///
    /// This structure contains the training results for the genetic algorithm method.
    ///
    struct GeneticAlgorithmResults : public InputsSelectionAlgorithm::InputsSelectionResults {
        /// Default constructor.
        explicit GeneticAlgorithmResults() : InputsSelectionAlgorithm::InputsSelectionResults()
        {
        }

        /// Destructor.
        virtual ~GeneticAlgorithmResults()
        {
        }

        std::string to_string() const;

        /// Values of the minimum performance in each generation.
        Vector<double> generation_optimum_performance_history;

        /// Values of the minimum selection performance in each generation.
        Vector<double> generation_minimum_selection_history;

        /// Mean of the selection performance in each generation.
        Vector<double> generation_mean_history;

        /// Standard deviation of the selection performance in each generation.
        Vector<double> generation_standard_deviation_history;
    };

    // Get methods
    const Vector<Vector<bool>> &get_population() const;

    const Matrix<double> &get_performance() const;

    const Vector<double> &get_fitness() const;

    const InitializationMethod &get_initialization_method() const;

    const CrossoverMethod &get_crossover_method() const;

    const FitnessAssignment &get_fitness_assignment_method() const;

    const size_t &get_population_size() const;

    const double &get_mutation_rate() const;

    const size_t &get_elitism_size() const;

    const size_t &get_crossover_first_point() const;

    const size_t &get_crossover_second_point() const;

    const double &get_selective_pressure() const;

    const double &get_incest_prevention_distance() const;

    const bool &get_reserve_generation_mean() const;

    const bool &get_reserve_generation_standard_deviation() const;

    const bool &get_reserve_generation_minimum_selection() const;

    const bool &get_reserve_generation_optimum_performance() const;

    std::string write_initialization_method() const;

    std::string write_crossover_method() const;

    std::string write_fitness_assignment_method() const;

    // Set methods
    void set_default();

    void set_population(const Vector<Vector<bool>> &);

    void set_performance(const Matrix<double> &);

    void set_fitness(const Vector<double> &);

    void set_inicialization_method(const InitializationMethod &);

    void set_fitness_assignment_method(const FitnessAssignment &);

    void set_crossover_method(const CrossoverMethod &);

    void set_inicialization_method(const std::string &);

    void set_fitness_assignment_method(const std::string &);

    void set_crossover_method(const std::string &);

    void set_population_size(const size_t &);

    void set_mutation_rate(const double &);

    void set_elitism_size(const size_t &);

    void set_crossover_first_point(const size_t &);

    void set_crossover_second_point(const size_t &);

    void set_selective_pressure(const double &);

    void set_incest_prevention_distance(const double &);

    void set_reserve_generation_mean(const bool &);

    void set_reserve_generation_standard_deviation(const bool &);

    void set_reserve_generation_minimum_selection(const bool &);

    void set_reserve_generation_optimum_performance(const bool &);

    // Population methods
    void initialize_population();

    void initialize_random_population();

    void initialize_weighted_population();

    void evaluate_population();

    void calculate_fitness();

    void calculate_objetive_fitness();

    void calculate_rank_fitness();

    void evolve_population();

    // Selection methods
    void perform_selection();

    // Crossover methods
    void perform_crossover();

    void perform_1point_crossover();

    void perform_2point_crossover();

    void perform_uniform_crossover();

    // Mutation methods
    void perform_mutation();

    // Order selection methods
    size_t get_optimal_individual_index() const;

    GeneticAlgorithmResults *perform_inputs_selection();

    // Serialization methods
    Matrix<std::string> to_string_matrix() const;

    tinyxml2::XMLDocument *to_XML() const;

    void from_XML(const tinyxml2::XMLDocument &);

    void save(const std::string &) const;

    void load(const std::string &);

private:
    /// Population matrix.
    Vector<Vector<bool>> population;

    /// Performance of population.
    Matrix<double> performance;

    /// Fitness of population.
    Vector<double> fitness;

    /// Initialization method used in the algorithm.
    InitializationMethod initialization_method;

    /// Crossover method used in the algorithm.
    CrossoverMethod crossover_method;

    /// Fitness assignment method used in the algorithm.
    FitnessAssignment fitness_assignment_method;

    /// Initial uses of the variables in the data set.
    Vector<Variables::Use> original_uses;

    /// Size of the population.
    size_t population_size;

    /// Incest prevention distance
    /// Distance between two individuals to prevent the crossover.
    double incest_prevention_distance;

    /// Mutation rate.
    /// The mutation rate value must be between 0 and 1.
    /// This is a parameter of the mutation operator.
    double mutation_rate;

    /// Elitism size.
    /// It represents the number of individuals which will always be selected for recombination.
    /// This is a parameter of the selection operator.
    size_t elitism_size;

    /// First point used in the OnePoint and TwoPoint crossover method.
    /// If it is 0 the algorithm selects a random point for each pair of offsprings.
    size_t crossover_first_point;

    /// Second point used in the TwoPoint crossover method.
    /// If it is 0 the algorithm selects a random point for each pair of offsprings.
    size_t crossover_second_point;

    /// Linear ranking allows values for the selective pressure greater than 0.
    /// This is a parameter of the fitness assignment operator.
    double selective_pressure;

    /// True if the mean of selection performance are to be reserved in each generation.
    bool reserve_generation_mean;

    /// True if the standard deviation of selection performance are to be reserved in each generation.
    bool reserve_generation_standard_deviation;

    /// True if the minimum of selection performance are to be reserved in each generation.
    bool reserve_generation_minimum_selection;

    /// True if the optimum of performance are to be reserved in each generation.
    bool reserve_generation_optimum_performance;
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
