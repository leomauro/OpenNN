/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   R O C   A R E A   E R R O R   C L A S S                                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "roc_area_error.h"


namespace OpenNN {

/// Default constructor.
/// It creates a sum squared error performance term not associated to any neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.
RocAreaError::RocAreaError() : PerformanceTerm()
{
}

/// Neural network constructor.
/// It creates a sum squared error performance term associated to a neural network but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
RocAreaError::RocAreaError(NeuralNetwork *new_neural_network_pointer)
        : PerformanceTerm(new_neural_network_pointer)
{
}

/// Data set constructor.
/// It creates a sum squared error not associated to any neural network but to be measured on a data set object.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.
RocAreaError::RocAreaError(DataSet *new_data_set_pointer)
        : PerformanceTerm(new_data_set_pointer)
{
}

/// Neural network and data set constructor.
/// It creates a sum squared error associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.
RocAreaError::RocAreaError(NeuralNetwork *new_neural_network_pointer, DataSet *new_data_set_pointer)
        : PerformanceTerm(new_neural_network_pointer, new_data_set_pointer)
{
}

/// XML constructor.
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from a TinyXML document.
/// @param sum_squared_error_document XML document with the class members.
RocAreaError::RocAreaError(const tinyxml2::XMLDocument &roc_area_error_document)
        : PerformanceTerm(roc_area_error_document)
{
}

/// Copy constructor.
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from another sum squared error object.
/// @param new_sum_squared_error Object to be copied.
RocAreaError::RocAreaError(const RocAreaError &new_roc_area_error)
        : PerformanceTerm(new_roc_area_error)
{
}

/// Destructor.
RocAreaError::~RocAreaError()
{
}

/// Checks that there are a neural network and a data set associated to the sum squared error,
/// and that the numbers of inputs and outputs in the neural network are equal to the numbers of inputs and targets in the data set.
/// If some of the above conditions is not hold, the method throws an exception.
void RocAreaError::check() const
{
    if (!neural_network_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class.\n"
               << "void check() const method.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

    if (!multilayer_perceptron_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class.\n"
               << "void check() const method.\n"
               << "Pointer to multilayer perceptron is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
    const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

    if (!data_set_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class.\n"
               << "void check() const method.\n"
               << "Pointer to data set is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const Variables &variables = data_set_pointer->get_variables();
    const size_t data_set_inputs_number = variables.count_inputs_number();
    const size_t targets_number = variables.count_targets_number();

    if (data_set_inputs_number != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class.\n"
               << "void check() const method.\n"
               << "Number of inputs in neural network (" << inputs_number << ") must be equal to number of inputs in data set (" << data_set_inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if (outputs_number != targets_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class.\n"
               << "void check() const method.\n"
               << "Number of outputs in neural network must be equal to number of targets in data set.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns the performance value of a neural network according to the sum squared error on a data set.
double RocAreaError::calculate_performance() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
    const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    // Sum squared error stuff
    Vector<double> inputs(inputs_number);
    Vector<double> outputs(outputs_number);
    Vector<double> targets(outputs_number);

    int i = 0;

//   #pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : sum_squared_error)

    double decision_threshold = 0.0;
    double true_positives = 0.0;
    double true_negatives = 0.0;
    double false_positives = 0.0;
    double false_negatives = 0.0;
    const size_t points_number = 101;

    Vector<double> target_data(training_instances_number);
    Vector<double> output_data(training_instances_number);
    Vector<double> true_positive_rate(points_number, 0.0);
    Vector<double> false_positive_rate(points_number, 0.0);

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);
        target_data[i] = targets[0];

        // Output vector
        outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);
        output_data[i] = outputs[0];
    }

    // Calculate binary classification tests
    for (size_t i = 1; i < points_number - 1; i++) {
        decision_threshold = i * 0.01;
        true_positives = 0.0;
        true_negatives = 0.0;
        false_positives = 0.0;
        false_negatives = 0.0;
        for (size_t j = 0; j < training_instances_number; j++) {
            if (target_data[j] == 1.0) {
                if (output_data[j] >= decision_threshold)
                    true_positives += output_data[j];
                else
                    false_negatives += (1.0 - output_data[j]);
            } else if (target_data[j] == 0.0) {
                if (output_data[j] >= decision_threshold)
                    false_positives += output_data[j];
                else
                    true_negatives += (1.0 - output_data[j]);
            } else {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: RocAreaError class.\n"
                       << "double calculate_performance() const method.\n"
                       << "Target is not binary.\n";

                throw std::logic_error(buffer.str());
            }
        }

        if (true_negatives + false_positives < 1.0e-12) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "Cannot compute false_positive_rate.\n";

            throw std::logic_error(buffer.str());
        }

        false_positive_rate[i] = false_negatives / (true_positives + false_negatives);
        if (false_positive_rate[i] < 0.0 || false_positive_rate[i] > 1.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "false_positve_rate must be between 0 and 1.\n";

            throw std::logic_error(buffer.str());
        }

        if (true_positives + false_negatives < 1.0e-12) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "Cannot compute true_positive_rate.\n";

            throw std::logic_error(buffer.str());
        }

        true_positive_rate[i] = true_positives / (true_negatives + false_positives);
        if (true_positive_rate[i] < 0.0 || true_positive_rate[i] > 1.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "true_positve_rate must be between 0 and 1.\n";

            throw std::logic_error(buffer.str());
        }
    }

    false_positive_rate[points_number - 1] = 1.0;
    true_positive_rate[points_number - 1] = 1.0;
    const double roc_area = numerical_integration.calculate_trapezoid_integral(false_positive_rate, true_positive_rate);
    const double roc_area_error = (1.0 - roc_area) * (1.0 - roc_area);

    return roc_area_error;
}

/// Returns which would be the sum squard error performance of a neural network for an hypothetical vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of potential parameters for the neural network associated to the performance term.
double RocAreaError::calculate_performance(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check();

    const size_t size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: RocAreaError class." << std::endl
               << "double calculate_performance(const Vector<double>&) const method." << std::endl
               << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ")." << std::endl;

        throw std::logic_error(buffer.str());
    }
#endif

    // Neural network stuff
    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
    const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    // Sum squared error stuff

    Vector<double> inputs(inputs_number);
    Vector<double> outputs(outputs_number);
    Vector<double> targets(outputs_number);

    int i = 0;

    double decision_threshold = 0.0;
    double true_positives = 0.0;
    double true_negatives = 0.0;
    double false_positives = 0.0;
    double false_negatives = 0.0;

    const size_t points_number = 101;
    Vector<double> true_positive_rate(points_number, 0.0);
    Vector<double> false_positive_rate(points_number, 0.0);
    Vector<double> target_data(training_instances_number);
    Vector<double> output_data(training_instances_number);

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);
        target_data[i] = targets[0];

        // Output vector
        outputs = multilayer_perceptron_pointer->calculate_outputs(inputs, parameters);
        output_data[i] = outputs[0];
    }

    // Calculate binary classification tests
    for (size_t i = 1; i < points_number - 1; i++) {
        decision_threshold = i * 0.01;
        true_positives = 0.0;
        true_negatives = 0.0;
        false_positives = 0.0;
        false_negatives = 0.0;
        for (size_t j = 0; j < training_instances_number; j++) {
            if (target_data[j] == 1.0) {
                if (output_data[j] >= decision_threshold)
                    true_positives += output_data[j];
                else
                    false_negatives += (1.0 - output_data[j]);
            } else if (target_data[j] == 0.0) {
                if (output_data[j] >= decision_threshold)
                    false_positives += output_data[j];
                else
                    true_negatives += (1.0 - output_data[j]);
            } else {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: RocAreaError class.\n"
                       << "double calculate_performance() const method.\n"
                       << "Target is not binary.\n";

                throw std::logic_error(buffer.str());
            }
        }

        if (true_negatives + false_positives < 1.0e-12) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "Cannot compute false_positive_rate.\n";

            throw std::logic_error(buffer.str());
        }

        false_positive_rate[i] = false_negatives / (true_positives + false_negatives);
        if (false_positive_rate[i] < 0.0 || false_positive_rate[i] > 1.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "false_positve_rate must be between 0 and 1.\n";

            throw std::logic_error(buffer.str());
        }

        if (true_positives + false_negatives < 1.0e-12) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "Cannot compute true_positive_rate.\n";

            throw std::logic_error(buffer.str());
        }

        true_positive_rate[i] = true_positives / (true_negatives + false_positives);
        if (true_positive_rate[i] < 0.0 || true_positive_rate[i] > 1.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: RocAreaError class.\n"
                   << "double calculate_performance() const method.\n"
                   << "true_positve_rate must be between 0 and 1.\n";

            throw std::logic_error(buffer.str());
        }
    }

    false_positive_rate[points_number - 1] = 1.0;
    true_positive_rate[points_number - 1] = 1.0;
    NumericalIntegration numerical_integration;
    const double roc_area = numerical_integration.calculate_trapezoid_integral(false_positive_rate,
                                                                               true_positive_rate);
    const double roc_area_error = (1.0 - roc_area) * (1.0 - roc_area);

    return roc_area_error;
}

Vector<double> RocAreaError::calculate_output_gradient(const Vector<double> &output,
                                                       const Vector<double> &target) const
{
    const Vector<double> output_gradient = (output - target) * 2.0;
    return output_gradient;
}

/// Calculates the performance term gradient by means of the back-propagation algorithm,
/// and returns it in a single vector of size the number of neural network parameters.
Vector<double> RocAreaError::calculate_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const bool has_conditions_layer = neural_network_pointer->has_conditions_layer();
    const ConditionsLayer *conditions_layer_pointer = has_conditions_layer?
                                                      neural_network_pointer->get_conditions_layer_pointer():
                                                      NULL;
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();
    const size_t layers_number = mlp->get_layers_number();
    const size_t neural_parameters_number = mlp->count_parameters_number();

    Vector<Vector<Vector<double>>> first_order_forward_propagation(2);
    Vector<double> particular_solution;
    Vector<double> homogeneous_solution;

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    Vector<double> inputs(inputs_number);
    Vector<double> targets(outputs_number);

    // Sum squared error stuff
    Vector<double> output_gradient(outputs_number);
    Vector<Matrix<double>> layers_combination_parameters_Jacobian;
    Vector<Vector<double>> layers_inputs(layers_number);
    Vector<Vector<double>> layers_delta;
    Vector<double> point_gradient(neural_parameters_number, 0.0);
    Vector<double> gradient(neural_parameters_number, 0.0);

    int i;

#pragma omp parallel for private(i, training_index, inputs, targets, first_order_forward_propagation, layers_inputs, layers_combination_parameters_Jacobian,\
    output_gradient, layers_delta, particular_solution, homogeneous_solution, point_gradient)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);
        targets = data_set_pointer->get_instance(training_index, targets_indices);
        first_order_forward_propagation = mlp->calculate_first_order_forward_propagation(inputs);
        const Vector<Vector<double>> &layers_activation = first_order_forward_propagation[0];
        const Vector<Vector<double>> &layers_activation_derivative = first_order_forward_propagation[1];
        layers_inputs = mlp->arrange_layers_input(inputs, layers_activation);
        layers_combination_parameters_Jacobian = mlp->calculate_layers_combination_parameters_Jacobian(layers_inputs);
        if (!has_conditions_layer) {
            output_gradient = calculate_output_gradient(layers_activation[layers_number - 1], targets);
            layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
        } else {
            particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
            homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);
            output_gradient = (particular_solution + homogeneous_solution * layers_activation[layers_number - 1] - targets) * 2.0;
            layers_delta = calculate_layers_delta(layers_activation_derivative,
                                                  homogeneous_solution,
                                                  output_gradient);
        }
        point_gradient = calculate_point_gradient(layers_combination_parameters_Jacobian, layers_delta);

#pragma omp critical
        gradient += point_gradient;
    }

    return gradient;
}


}


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
