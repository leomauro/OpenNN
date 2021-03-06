/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   N E U R A L   N E T W O R K   C L A S S   H E A D E R                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __NEURALNETWORK_H__
#define __NEURALNETWORK_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "data_set.h"

#include "perceptron.h"
#include "perceptron_layer.h"
#include "multilayer_perceptron.h"
#include "scaling_layer.h"
#include "principal_components_layer.h"
#include "unscaling_layer.h"
#include "bounding_layer.h"
#include "probabilistic_layer.h"
#include "conditions_layer.h"
#include "independent_parameters.h"
#include "inputs.h"
#include "outputs.h"

// TinyXml includes

#include <tinyxml2.h>

namespace OpenNN
{

/// This class represents the concept of neural network in the OpenNN library.
/// A neural network here is defined as a multilayer perceptron extended with a scaling layer, an unscaling layer,
/// a bounding layer, a probabilistic layer, a conditions layer and a set of independent parameters.
/// This neural network is used to span a function space for the variational problem at hand.
class NeuralNetwork
{
public:
    // DEFAULT CONSTRUCTOR
    explicit NeuralNetwork();

    // MULTILAYER PERCEPTRON CONSTRUCTOR
    explicit NeuralNetwork(const MultilayerPerceptron &);

    // MULTILAYER PERCEPTRON ARCHITECTURE CONSTRUCTOR
    explicit NeuralNetwork(const Vector<size_t> &);

    // ONE PERCEPTRON LAYER CONSTRUCTOR
    explicit NeuralNetwork(const size_t &, const size_t &);

    // TWO PERCEPTRON LAYERS CONSTRUCTOR
    explicit NeuralNetwork(const size_t &, const size_t &, const size_t &);

    // INDEPENDENT PARAMETERS NUMBER CONSTRUCTOR
    explicit NeuralNetwork(const size_t &);

    // FILE CONSTRUCTOR
    explicit NeuralNetwork(const std::string &);

    // XML CONSTRUCTOR
    explicit NeuralNetwork(const tinyxml2::XMLDocument &);

    // COPY CONSTRUCTOR
    NeuralNetwork(const NeuralNetwork &);

    // DESTRUCTOR
    virtual ~NeuralNetwork();

    // ASSIGNMENT OPERATOR
    NeuralNetwork &operator=(const NeuralNetwork &);

    // EQUAL TO OPERATOR
    bool operator==(const NeuralNetwork &) const;

    // GET METHODS
    bool has_multilayer_perceptron() const;

    bool has_inputs() const;

    bool has_outputs() const;

    bool has_scaling_layer() const;

    bool has_principal_components_layer() const;

    bool has_unscaling_layer() const;

    bool has_bounding_layer() const;

    bool has_probabilistic_layer() const;

    bool has_conditions_layer() const;

    bool has_independent_parameters() const;

    MultilayerPerceptron *get_multilayer_perceptron_pointer() const;

    Inputs *get_inputs_pointer() const;

    Outputs *get_outputs_pointer() const;

    ScalingLayer *get_scaling_layer_pointer() const;

    PrincipalComponentsLayer *get_principal_components_layer_pointer() const;

    UnscalingLayer *get_unscaling_layer_pointer() const;

    BoundingLayer *get_bounding_layer_pointer() const;

    ProbabilisticLayer *get_probabilistic_layer_pointer() const;

    ConditionsLayer *get_conditions_layer_pointer() const;

    IndependentParameters *get_independent_parameters_pointer() const;

    const bool &get_display() const;

    // SET METHODS
    void set();

    void set(const MultilayerPerceptron &);

    void set(const Vector<size_t> &);

    void set(const size_t &, const size_t &);

    void set(const size_t &, const size_t &, const size_t &);

    void set(const size_t &);

    void set(const std::string &);

    void set(const NeuralNetwork &);

    virtual void set_default();

    void set_multilayer_perceptron_pointer(MultilayerPerceptron *);

    void set_scaling_layer_pointer(ScalingLayer *);

    void set_principal_components_layer_pointer(PrincipalComponentsLayer *);

    void set_unscaling_layer_pointer(UnscalingLayer *);

    void set_bounding_layer_pointer(BoundingLayer *);

    void set_probabilistic_layer_pointer(ProbabilisticLayer *);

    void set_conditions_layer_pointer(ConditionsLayer *);

    void set_inputs_pointer(Inputs *);

    void set_outputs_pointer(Outputs *);

    void set_independent_parameters_pointer(IndependentParameters *);

    void set_scaling_layer(ScalingLayer &);

    void set_display(const bool &);

    // Growing and pruning
    void grow_input(const Statistics<double> &new_statistics = Statistics<double>());

    void prune_input(const size_t &);

    void prune_output(const size_t &);

    void resize_inputs_number(const size_t &);

    void resize_outputs_number(const size_t &);

    // Pointer methods
    void construct_multilayer_perceptron();

    void construct_scaling_layer();

    void construct_principal_components_layer();

    void construct_unscaling_layer();

    void construct_bounding_layer();

    void construct_probabilistic_layer();

    void construct_conditions_layer();

    void construct_inputs();

    void construct_outputs();

    void construct_independent_parameters();

    void destruct_multilayer_perceptron();

    void destruct_scaling_layer();

    void destruct_unscaling_layer();

    void destruct_bounding_layer();

    void destruct_probabilistic_layer();

    void destruct_conditions_layer();

    void destruct_inputs();

    void destruct_outputs();

    void destruct_independent_parameters();

    void delete_pointers();

    // Initialization methods
    void initialize_random();

    // Layers
    size_t get_layers_number();

    // Architecture
    size_t get_inputs_number() const;

    size_t get_outputs_number() const;

    Vector<size_t> arrange_architecture() const;

    // Parameters
    size_t count_parameters_number() const;

    Vector<double> arrange_parameters() const;

    void set_parameters(const Vector<double> &);

    // Parameters initialization methods
    void initialize_parameters(const double &);

    void randomize_parameters_uniform();

    void randomize_parameters_uniform(const double &, const double &);

    void randomize_parameters_uniform(const Vector<double> &, const Vector<double> &);

    void randomize_parameters_uniform(const Vector<Vector<double>> &);

    void randomize_parameters_normal();

    void randomize_parameters_normal(const double &, const double &);

    void randomize_parameters_normal(const Vector<double> &, const Vector<double> &);

    void randomize_parameters_normal(const Vector<Vector<double>> &);

    // Parameters
    double calculate_parameters_norm() const;

    Statistics<double> calculate_parameters_statistics() const;

    Histogram<double> calculate_parameters_histogram(const size_t & = 10) const;

    void perturbate_parameters(const double &);

    // Output
    Vector<double> calculate_outputs(const Vector<double> &) const;

    Matrix<double> calculate_Jacobian(const Vector<double> &) const;

    Vector<Matrix<double>> calculate_Hessian_form(const Vector<double> &) const;

    Matrix<double> calculate_directional_input_data(const size_t &,
                                                    const Vector<double> &,
                                                    const double &,
                                                    const double &,
                                                    const size_t & = 101) const;

    Vector<double> calculate_outputs(const Vector<double> &, const Vector<double> &) const;

    Matrix<double> calculate_Jacobian(const Vector<double> &, const Vector<double> &) const;

    Vector<Matrix<double>> calculate_Hessian_form(const Vector<double> &, const Vector<double> &) const;

    Matrix<double> calculate_output_data(const Matrix<double> &) const;

    Matrix<double> calculate_output_data_missing_values(const Matrix<double> &/*, const double& missing_values_flag = -123.456*/) const;

    Vector<Matrix<double>> calculate_Jacobian_data(const Matrix<double> &) const;

    Vector<Histogram<double>> calculate_outputs_histograms(const size_t & = 1000, const size_t & = 10) const;

    Vector<Histogram<double>> calculate_outputs_histograms(const Matrix<double> &, const size_t & = 10) const;

    // Serialization methods
    std::string to_string() const;

    virtual tinyxml2::XMLDocument *to_XML() const;

    virtual void from_XML(const tinyxml2::XMLDocument &);

    void print() const;

    void save(const std::string &) const;

    void save_parameters(const std::string &) const;

    virtual void load(const std::string &);

    void load_parameters(const std::string &);

    void save_data(const std::string &) const;

    // Expression methods
    std::string write_expression() const;

    std::string write_expression_python() const;

    std::string write_expression_R() const;

    void save_expression(const std::string &);

    void save_expression_python(const std::string &);

    void save_expression_R(const std::string &);

    // PMML methods
    virtual tinyxml2::XMLDocument *to_PMML() const;

    virtual void from_PMML(const tinyxml2::XMLDocument &);

protected:
    /// Pointer to a multilayer perceptron object.
    MultilayerPerceptron *multilayer_perceptron_pointer;

    /// Pointer to a scaling layer object.
    ScalingLayer *scaling_layer_pointer;

    /// Pointer to a principal components layer object.
    PrincipalComponentsLayer *principal_components_layer_pointer;

    /// Pointer to an unscaling layer object.
    UnscalingLayer *unscaling_layer_pointer;

    /// Pointer to a bounding layer object.
    BoundingLayer *bounding_layer_pointer;

    /// Pointer to a probabilistic layer.
    ProbabilisticLayer *probabilistic_layer_pointer;

    /// Pointer to a conditions object.
    ConditionsLayer *conditions_layer_pointer;

    /// Pointer to an inputs object.
    Inputs *inputs_pointer;

    /// Pointer to an outputs object.
    Outputs *outputs_pointer;

    /// Pointer to an independent parameters object
    IndependentParameters *independent_parameters_pointer;

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
