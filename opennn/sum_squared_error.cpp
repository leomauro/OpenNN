/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   S U M   S Q U A R E D   E R R O R   C L A S S                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "sum_squared_error.h"


namespace OpenNN {

/// Default constructor.
/// It creates a sum squared error performance term not associated to any neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.
SumSquaredError::SumSquaredError() : PerformanceTerm()
{
}

/// Neural network constructor.
/// It creates a sum squared error performance term associated to a neural network but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
SumSquaredError::SumSquaredError(NeuralNetwork *new_neural_network_pointer)
        : PerformanceTerm(new_neural_network_pointer)
{
}

/// Data set constructor.
/// It creates a sum squared error not associated to any neural network but to be measured on a data set object.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.
SumSquaredError::SumSquaredError(DataSet *new_data_set_pointer)
        : PerformanceTerm(new_data_set_pointer)
{
}

/// Neural network and data set constructor.
/// It creates a sum squared error associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.
SumSquaredError::SumSquaredError(NeuralNetwork *new_neural_network_pointer, DataSet *new_data_set_pointer)
        : PerformanceTerm(new_neural_network_pointer, new_data_set_pointer)
{
}

/// XML constructor.
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from a TinyXML document.
/// @param sum_squared_error_document XML document with the class members.
SumSquaredError::SumSquaredError(const tinyxml2::XMLDocument &sum_squared_error_document)
        : PerformanceTerm(sum_squared_error_document)
{
}

/// Copy constructor.
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from another sum squared error object.
/// @param new_sum_squared_error Object to be copied.
SumSquaredError::SumSquaredError(const SumSquaredError &new_sum_squared_error)
        : PerformanceTerm(new_sum_squared_error)
{
}

/// Destructor.
SumSquaredError::~SumSquaredError()
{
}

/// Checks that there are a neural network and a data set associated to the sum squared error,
/// and that the numbers of inputs and outputs in the neural network are equal to the numbers of inputs and targets in the data set.
/// If some of the above conditions is not hold, the method throws an exception.
void SumSquaredError::check() const
{
    if (!neural_network_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void check() const method.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

    if (!mlp) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void check() const method.\n"
               << "Pointer to multilayer perceptron is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();

    if (!data_set_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void check() const method.\n"
               << "Pointer to data set is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Sum squared error stuff

    const Variables &variables = data_set_pointer->get_variables();
    const size_t data_set_inputs_number = variables.count_inputs_number();
    const size_t targets_number = variables.count_targets_number();

    if (data_set_inputs_number != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void check() const method.\n"
               << "Number of inputs in neural network (" << inputs_number << ") must be equal to number of inputs in data set (" << data_set_inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if (outputs_number != targets_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void check() const method.\n"
               << "Number of outputs in neural network must be equal to number of targets in data set.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns the performance value of a neural network according to the sum squared error on a data set.
double SumSquaredError::calculate_performance() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();

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
    double sum_squared_error = 0.0;

#pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : sum_squared_error)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);

        // Output vector
        outputs = mlp->calculate_outputs(inputs);

        // Sum squared error
        sum_squared_error += outputs.calculate_sum_squared_error(targets);
    }

    return sum_squared_error;
}

/// Returns which would be the sum squard error performance of a neural network for an hypothetical vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of potential parameters for the neural network associated to the performance term.
double SumSquaredError::calculate_performance(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check();

    const size_t size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class." << std::endl
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
    double sum_squared_error = 0.0;

#pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : sum_squared_error)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Output vector
        outputs = multilayer_perceptron_pointer->calculate_outputs(inputs, parameters);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);

        // Sum squared error
        sum_squared_error += outputs.calculate_sum_squared_error(targets);
    }

    return sum_squared_error;
}


// Test combination

double SumSquaredError::calculate_performance_combination(const size_t &index,
                                                          const Vector<double> &combinations) const
{
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();
    const Vector<double> targets = data_set_pointer->get_instance(0, targets_indices);
    const Vector<double> activations = neural_network_pointer->get_multilayer_perceptron_pointer()
                                                             ->get_layer(index)
                                                             .calculate_activations(combinations);

    return activations.calculate_sum_squared_error(targets);
}

double SumSquaredError::calculate_performance_combinations(const size_t &index_1,
                                                           const Vector<double> &combinations_1,
                                                           const size_t &index_2,
                                                           const Vector<double> &combinations_2) const
{
    std::cout << index_1 << combinations_1 << std::endl;

    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();
    const Variables &variables = data_set_pointer->get_variables();
    const size_t layers_number = neural_network_pointer->get_multilayer_perceptron_pointer()->get_layers_number();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();
    const Vector<double> targets = data_set_pointer->get_instance(0, targets_indices);

    Vector<double> outputs;
    for (size_t i = index_2; i < layers_number; i++) {
        outputs = multilayer_perceptron_pointer->get_layer(index_2).calculate_activations(combinations_2);
    }

    return outputs.calculate_sum_squared_error(targets);
}

/// Returns the sum squared error of the neural network measured on the selection instances of the data set.
double SumSquaredError::calculate_selection_performance() const
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
    const size_t selection_instances_number = instances.count_selection_instances_number();
    const Vector<size_t> selection_indices = instances.arrange_selection_indices();
    size_t selection_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    // Sum squared error stuff
    Vector<double> inputs(inputs_number);
    Vector<double> outputs(outputs_number);
    Vector<double> targets(outputs_number);

    double selection_performance = 0.0;
    int i = 0;

#pragma omp parallel for private(i, selection_index, inputs, outputs, targets) reduction(+ : selection_performance)

    for (i = 0; i < (int) selection_instances_number; i++) {
        selection_index = selection_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(selection_index, inputs_indices);

        // Output vector
        outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

        // Target vector
        targets = data_set_pointer->get_instance(selection_index, targets_indices);

        // Sum of squares error
        selection_performance += outputs.calculate_sum_squared_error(targets);
    }

    return selection_performance;
}

Vector<double> SumSquaredError::calculate_output_gradient(const Vector<double> &output,
                                                          const Vector<double> &target) const
{
    const Vector<double> output_gradient = (output - target) * 2.0;

    return output_gradient;
}

/// Calculates the performance term gradient by means of the back-propagation algorithm,
/// and returns it in a single vector of size the number of neural network parameters.
Vector<double> SumSquaredError::calculate_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

    // Neural network stuff
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

Matrix<double> SumSquaredError::calculate_output_Hessian(const Vector<double> &, const Vector<double> &) const
{
    const size_t outputs_number = neural_network_pointer->get_multilayer_perceptron_pointer()->get_outputs_number();
    Matrix<double> output_Hessian(outputs_number, outputs_number);
    output_Hessian.initialize_diagonal(2.0);

    return output_Hessian;
}

/// Calculates the Hessian by means of the back-propagation algorithm,
/// and returns it in a single symmetric matrix of size the number of neural network parameters.
/// Only implemented for one hidden layer
Matrix<double> SumSquaredError::calculate_Hessian() const
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

    if (layers_number != 2) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "Matrix<double> calculate_Hessian() method.\n"
               << "This method is under development for more than one hidden layer.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t parameters_number = mlp->count_parameters_number();
    const Vector<size_t> layers_perceptrons_number = mlp->arrange_layers_perceptrons_numbers();
    Vector<Vector<Vector<double>>> second_order_forward_propagation(3);
    Vector<Vector<Vector<double>>> perceptrons_combination_parameters_gradient(layers_number);
    Matrix<Matrix<double>> interlayers_combination_combination_Jacobian;

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
    Vector<Vector<double>> layers_delta(layers_number);
    Matrix<double> output_interlayers_Delta;
    Vector<double> output_gradient(outputs_number);
    Matrix<double> output_Hessian(outputs_number, outputs_number);
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    for (size_t i = 0; i < training_instances_number; i++) {
        training_index = training_indices[i];
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);
        targets = data_set_pointer->get_instance(training_index, targets_indices);
        second_order_forward_propagation = mlp->calculate_second_order_forward_propagation(inputs);
        const Vector<Vector<double>> &layers_activation = second_order_forward_propagation[0];
        const Vector<Vector<double>> &layers_activation_derivative = second_order_forward_propagation[1];
        const Vector<Vector<double>> &layers_activation_second_derivative = second_order_forward_propagation[2];
        Vector<Vector<double>> layers_inputs(layers_number);
        layers_inputs[0] = inputs;

        for (size_t j = 1; j < layers_number; j++) {
            layers_inputs[j] = layers_activation[j - 1];
        }

        perceptrons_combination_parameters_gradient = mlp->calculate_perceptrons_combination_parameters_gradient(layers_inputs);
        interlayers_combination_combination_Jacobian = mlp->calculate_interlayers_combination_combination_Jacobian(inputs);
        if (!has_conditions_layer) {
            output_gradient = calculate_output_gradient(layers_activation[layers_number - 1], targets);
            output_Hessian = calculate_output_Hessian(layers_activation[layers_number - 1], targets);
            layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
            output_interlayers_Delta = calculate_output_interlayers_Delta(layers_activation_derivative[layers_number - 1],
                                                                          layers_activation_second_derivative[layers_number - 1],
                                                                          output_gradient,
                                                                          output_Hessian);
        } else {
            particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
            homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);
            output_gradient = (particular_solution + homogeneous_solution * layers_activation[layers_number - 1] - targets) * 2.0;
            layers_delta = calculate_layers_delta(layers_activation_derivative,
                                                  homogeneous_solution,
                                                  output_gradient);
        }

        Hessian += calculate_single_hidden_layer_point_Hessian(layers_activation_derivative,
                                                               layers_activation_second_derivative,
                                                               perceptrons_combination_parameters_gradient,
                                                               layers_delta,
                                                               output_interlayers_Delta);
    }

    return Hessian;
}

/// Calculates the Hessian matrix for a neural network with one hidden layer and an arbitrary number of
/// inputs, perceptrons in the hidden layer and outputs.
Matrix<double> SumSquaredError::calculate_single_hidden_layer_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();
    const size_t layers_number = 2;
    const size_t parameters_number = mlp->count_parameters_number();
    Vector<Vector<Vector<double>>> second_order_forward_propagation(3);
    Vector<Vector<Vector<double>>> perceptrons_combination_parameters_gradient(layers_number);
    Matrix<Matrix<double>> interlayers_combination_combination_Jacobian;

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    Vector<double> inputs(inputs_number);
    Vector<double> targets(outputs_number);

    // Sum squared error stuff
    Vector<Vector<double>> layers_delta(layers_number);
    Vector<double> output_gradient(outputs_number);
    Matrix<double> output_Hessian(outputs_number, outputs_number);
    Matrix<double> single_hidden_layer_Hessian(parameters_number, parameters_number, 0.0);
    const size_t i = 0;
    training_index = training_indices[i];
    inputs = data_set_pointer->get_instance(training_index, inputs_indices);
    targets = data_set_pointer->get_instance(training_index, targets_indices);
    second_order_forward_propagation = mlp->calculate_second_order_forward_propagation(inputs);

    const Vector<Vector<double>> &layers_activation = second_order_forward_propagation[0];
    const Vector<Vector<double>> &layers_activation_derivative = second_order_forward_propagation[1];
    const Vector<Vector<double>> &layers_activation_second_derivative = second_order_forward_propagation[2];

    Vector<Vector<double>> layers_inputs(layers_number);
    layers_inputs[0] = inputs;
    for (size_t j = 1; j < layers_number; j++) {
        layers_inputs[j] = layers_activation[j - 1];
    }

    perceptrons_combination_parameters_gradient = mlp->calculate_perceptrons_combination_parameters_gradient(layers_inputs);
    interlayers_combination_combination_Jacobian = mlp->calculate_interlayers_combination_combination_Jacobian(inputs);
    output_gradient = calculate_output_gradient(layers_activation[layers_number - 1], targets);
    output_Hessian = calculate_output_Hessian(layers_activation[layers_number - 1], targets);
    layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
    const size_t first_layer_parameters_number = mlp->get_layer(0).arrange_parameters().size();
    const size_t second_layer_parameters_number = mlp->get_layer(1).arrange_parameters().size();
    Vector<size_t> parameter_indices(3);

    size_t layer_index_i;
    size_t neuron_index_i;
    size_t parameter_index_i;
    size_t layer_index_j;
    size_t neuron_index_j;
    size_t parameter_index_j;
    const Matrix<double> output_interlayers_Delta =
            output_Hessian *
            layers_activation_derivative[layers_number - 1] *
            layers_activation_derivative[layers_number - 1] +
            output_gradient * layers_activation_second_derivative[layers_number - 1];

    // Both weights in the second layer
    for (size_t i = first_layer_parameters_number; i < second_layer_parameters_number + first_layer_parameters_number; i++) {
        parameter_indices = mlp->arrange_parameter_indices(i);
        layer_index_i = parameter_indices[0];
        neuron_index_i = parameter_indices[1];
        parameter_index_i = parameter_indices[2];
        for (size_t j = first_layer_parameters_number; j < second_layer_parameters_number + first_layer_parameters_number; j++) {
            parameter_indices = mlp->arrange_parameter_indices(j);
            layer_index_j = parameter_indices[0];
            neuron_index_j = parameter_indices[1];
            parameter_index_j = parameter_indices[2];

            single_hidden_layer_Hessian(i, j) =
                    perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                    perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                    calculate_Kronecker_delta(neuron_index_i, neuron_index_j) *
                    output_interlayers_Delta(neuron_index_j, neuron_index_i);
        }
    }

    // One weight in each layer
    Matrix<double> second_layer_weights = mlp->get_layer(1).arrange_synaptic_weights();
    for (size_t i = 0; i < first_layer_parameters_number; i++) {
        parameter_indices = mlp->arrange_parameter_indices(i);
        layer_index_i = parameter_indices[0];
        neuron_index_i = parameter_indices[1];
        parameter_index_i = parameter_indices[2];

        for (size_t j = first_layer_parameters_number; j < first_layer_parameters_number + second_layer_parameters_number; j++) {
            parameter_indices = mlp->arrange_parameter_indices(j);
            layer_index_j = parameter_indices[0];
            neuron_index_j = parameter_indices[1];
            parameter_index_j = parameter_indices[2];

            single_hidden_layer_Hessian(i, j) =
                    perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                    perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                    layers_activation_derivative[layer_index_i][neuron_index_i] *
                    second_layer_weights(neuron_index_j, neuron_index_i) *
                    output_interlayers_Delta(neuron_index_j, neuron_index_j) +
                    perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                    layers_activation_derivative[layer_index_i][neuron_index_i] *
                    layers_delta[layer_index_j][neuron_index_j] *
                    calculate_Kronecker_delta(parameter_index_j, neuron_index_i + 1);
        }
    }

    // Both weights in the first layer
    for (size_t i = 0; i < first_layer_parameters_number; i++) {
        parameter_indices = mlp->arrange_parameter_indices(i);
        layer_index_i = parameter_indices[0];
        neuron_index_i = parameter_indices[1];
        parameter_index_i = parameter_indices[2];

        for (size_t j = 0; j < first_layer_parameters_number; j++) {
            parameter_indices = mlp->arrange_parameter_indices(j);
            layer_index_j = parameter_indices[0];
            neuron_index_j = parameter_indices[1];
            parameter_index_j = parameter_indices[2];

            double sum = 0.0;
            for (size_t k = 0; k < outputs_number; k++) {
                sum += second_layer_weights(k, neuron_index_i) *
                       second_layer_weights(k, neuron_index_j) *
                       output_interlayers_Delta(k, k);
            }

            single_hidden_layer_Hessian(i, j) =
                    perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                    perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                    (layers_activation_derivative[layer_index_i][neuron_index_i] *
                     layers_activation_derivative[layer_index_j][neuron_index_j] *
                     sum +
                     layers_activation_second_derivative[layer_index_j][neuron_index_j] *
                     calculate_Kronecker_delta(neuron_index_j, neuron_index_i) *
                     second_layer_weights.arrange_column(neuron_index_j).dot(layers_delta[1]));
        }
    }

    // Hessian
    for (size_t i = 0; i < parameters_number; i++) {
        for (size_t j = 0; j < parameters_number; j++) {
            single_hidden_layer_Hessian(j, i) = single_hidden_layer_Hessian(i, j);
        }
    }

    return single_hidden_layer_Hessian;
}

/// Calculates the squared error terms for each instance, and returns it in a vector of size the number training instances.
Vector<double> SumSquaredError::calculate_terms() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    // Performance functional stuff
    Vector<double> performance_terms(training_instances_number);
    Vector<double> inputs(inputs_number);
    Vector<double> outputs(outputs_number);
    Vector<double> targets(outputs_number);

    int i = 0;

#pragma omp parallel for private(i, training_index, inputs, outputs, targets)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Output vector
        outputs = mlp->calculate_outputs(inputs);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);

        // Error
        performance_terms[i] = outputs.calculate_distance(targets);
    }

    return performance_terms;
}

/// Returns the performance terms vector for a hypotetical vector of parameters.
/// @param parameters Neural network parameters for which the performance terms vector is to be computed.
Vector<double> SumSquaredError::calculate_terms(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check();

    const size_t size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class." << std::endl
               << "double calculate_terms(const Vector<double>&) const method." << std::endl
               << "Size (" << size << ") must be equal to number of neural network parameters (" << parameters_number << ")." << std::endl;

        throw std::logic_error(buffer.str());
    }
#endif

    NeuralNetwork neural_network_copy(*neural_network_pointer);
    neural_network_copy.set_parameters(parameters);
    SumSquaredError sum_squared_error_copy(*this);
    sum_squared_error_copy.set_neural_network_pointer(&neural_network_copy);

    return sum_squared_error_copy.calculate_terms();
}

/// Returns the terms_Jacobian matrix of the sum squared error function, whose elements are given by the
/// derivatives of the squared errors data set with respect to the multilayer perceptron parameters.
/// The terms_Jacobian matrix here is computed using a back-propagation algorithm.
Matrix<double> SumSquaredError::calculate_terms_Jacobian() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();
    const size_t layers_number = mlp->get_layers_number();
    const size_t neural_parameters_number = mlp->count_parameters_number();

    Vector<Vector<Vector<double>>> first_order_forward_propagation(2);
    Vector<Vector<double>> layers_inputs(layers_number);
    Vector<Matrix<double>> layers_combination_parameters_Jacobian(layers_number);

    Vector<double> particular_solution;
    Vector<double> homogeneous_solution;

    const bool has_conditions_layer = neural_network_pointer->has_conditions_layer();
    const ConditionsLayer *conditions_layer_pointer = has_conditions_layer?
                                                      neural_network_pointer->get_conditions_layer_pointer():
                                                      NULL;

    // Data set
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();
    const MissingValues missing_values = data_set_pointer->get_missing_values();

    Vector<double> inputs(inputs_number);
    Vector<double> targets(outputs_number);

    // Performance functional
    Vector<double> term(outputs_number);
    double term_norm;
    Vector<double> output_gradient(outputs_number);
    Vector<Vector<double>> layers_delta(layers_number);
    Vector<double> point_gradient(neural_parameters_number);
    Matrix<double> terms_Jacobian(training_instances_number, neural_parameters_number);

    // Main loop
    int i = 0;

#pragma omp parallel for private(i, training_index, inputs, targets, first_order_forward_propagation, layers_inputs, \
    layers_combination_parameters_Jacobian, term, term_norm, output_gradient, layers_delta, particular_solution, homogeneous_solution, point_gradient)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);
        targets = data_set_pointer->get_instance(training_index, targets_indices);
        first_order_forward_propagation = mlp->calculate_first_order_forward_propagation(inputs);
        layers_inputs = mlp->arrange_layers_input(inputs, first_order_forward_propagation);
        layers_combination_parameters_Jacobian = mlp->calculate_layers_combination_parameters_Jacobian(layers_inputs);

        if (!has_conditions_layer) {
            term = first_order_forward_propagation[0][layers_number - 1] - targets;
            term_norm = term.calculate_norm();
            if (term_norm == 0.0)
                output_gradient.set(outputs_number, 0.0);
            else
                output_gradient = term / term_norm;
            layers_delta = calculate_layers_delta(first_order_forward_propagation[1], output_gradient);
        } else {
            particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
            homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);
            term = (particular_solution + homogeneous_solution * first_order_forward_propagation[0][layers_number - 1] - targets);
            term_norm = term.calculate_norm();
            if (term_norm == 0.0)
                output_gradient.set(outputs_number, 0.0);
            else
                output_gradient = term / term_norm;

            layers_delta = calculate_layers_delta(first_order_forward_propagation[1],
                                                  homogeneous_solution,
                                                  output_gradient);
        }

        point_gradient = calculate_point_gradient(layers_combination_parameters_Jacobian, layers_delta);
        terms_Jacobian.set_row(i, point_gradient);
    }

    return terms_Jacobian;
}

/// Returns the first order performance of the terms performance function.
/// This is a structure containing the performance terms vector and the performance terms Jacobian.
PerformanceTerm::FirstOrderTerms SumSquaredError::calculate_first_order_terms() const
{
    FirstOrderTerms first_order_terms;
    first_order_terms.terms = calculate_terms();
    first_order_terms.Jacobian = calculate_terms_Jacobian();

    return first_order_terms;
}

/// Returns the squared errors of the training instances.
Vector<double> SumSquaredError::calculate_squared_errors() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    // Neural network stuff
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t inputs_number = mlp->get_inputs_number();
    const size_t outputs_number = mlp->get_outputs_number();

    // Data set stuff
    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    const Vector<size_t> training_indices = instances.arrange_training_indices();
    size_t training_index;
    const Variables &variables = data_set_pointer->get_variables();
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();
    const MissingValues missing_values = data_set_pointer->get_missing_values();

    // Performance functional
    Vector<double> squared_errors(training_instances_number);
    Vector<double> inputs(inputs_number);
    Vector<double> outputs(outputs_number);
    Vector<double> targets(outputs_number);

    int i = 0;

#pragma omp parallel for private(i, training_index, inputs, outputs, targets)

    for (i = 0; i < (int) training_instances_number; i++) {
        training_index = training_indices[i];

        // Input vector
        inputs = data_set_pointer->get_instance(training_index, inputs_indices);

        // Output vector
        outputs = mlp->calculate_outputs(inputs);

        // Target vector
        targets = data_set_pointer->get_instance(training_index, targets_indices);

        // Error
        squared_errors[i] = outputs.calculate_sum_squared_error(targets);
    }

    return squared_errors;
}

// @todo
Vector<double> SumSquaredError::calculate_gradient(const Vector<double> &) const
{
    Vector<double> gradient;
    return gradient;
}

// @todo
Matrix<double> SumSquaredError::calculate_Hessian(const Vector<double> &) const
{
    Matrix<double> Hessian;
    return Hessian;
}

/// Returns a string with the name of the sum squared error performance type, "SUM_SQUARED_ERROR".
std::string SumSquaredError::write_performance_term_type() const
{
    return "SUM_SQUARED_ERROR";
}

/// Returns a representation of the sum squared error object, in XML format.
tinyxml2::XMLDocument *SumSquaredError::to_XML() const
{
    std::ostringstream buffer;
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;

    // Sum squared error
    tinyxml2::XMLElement *root_element = document->NewElement("SumSquaredError");
    document->InsertFirstChild(root_element);

    return document;
}

/// Loads a sum squared error object from a XML document.
/// @param document TinyXML document containing the members of the object.
void SumSquaredError::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *root_element = document.FirstChildElement("SumSquaredError");
    if (!root_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Sum squared error element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Display
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("Display");
        if (element) {
            const std::string new_display_string = element->GetText();
            try {
                set_display(new_display_string != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
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
