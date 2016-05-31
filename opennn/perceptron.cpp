/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P E R C E P T R O N   C L A S S                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "perceptron.h"


namespace OpenNN {

/// Default constructor.
/// It creates a perceptron object with zero inputs.
/// The neuron's bias is initialized to zero.
/// This constructor also initializes the rest of class members to their default values.
Perceptron::Perceptron()
{
    set();
}

/// Inputs number constructor.
/// It creates a perceptron object with a given number of inputs.
/// The neuron's free paramameters (bias and synaptic weights) are initialized at random with a normal
/// distribution of mean 0 and standard deviation 1.
/// This constructor also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of inputs in the neuron.
Perceptron::Perceptron(const size_t &new_inputs_number)
{
    set(new_inputs_number);
}

/// Inputs number and initialization constructor.
/// This creates a perceptron with a given number of inputs.
/// It also initializes the bias and synaptic weights with a given value.
/// @param new_inputs_number Number of inputs in the neuron.
/// @param new_parameters_value Bias and synaptic weights initialization value.
Perceptron::Perceptron(const size_t &new_inputs_number, const double &new_parameters_value)
{
    set(new_inputs_number, new_parameters_value);
}

/// Copy constructor.
/// It creates a percdeptron object by copying its members with those for other perceptron object.
/// @param other_perceptron Perceptron object to be copied.
Perceptron::Perceptron(const Perceptron &other_perceptron)
{
    set(other_perceptron);
}

/// Destructor.
/// This destructor does not delete any pointer.
Perceptron::~Perceptron()
{
}

/// Assignment operator.
/// It assigns to the current perceptron the members of an existing perceptron.
/// @param other_perceptron Assigning perceptron object .
Perceptron &Perceptron::operator=(const Perceptron &other_perceptron)
{
    if (this != &other_perceptron) {
        bias = other_perceptron.bias;
        synaptic_weights = other_perceptron.synaptic_weights;
        activation_function = other_perceptron.activation_function;
        display = other_perceptron.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_perceptron Perceptron to be compared with.
bool Perceptron::operator==(const Perceptron &other_perceptron) const
{
    return bias == other_perceptron.bias &&
           synaptic_weights == other_perceptron.synaptic_weights &&
           activation_function == other_perceptron.activation_function &&
           display == other_perceptron.display;
}

/// Returns the activation function of the neuron.
const Perceptron::ActivationFunction &Perceptron::get_activation_function() const
{
    return activation_function;
}

/// Returns a string with the name of the activation function of the neuron.
std::string Perceptron::write_activation_function() const
{
    switch (activation_function) {
    case Perceptron::Logistic:
        return "logistic";

    case Perceptron::HyperbolicTangent:
        return "tanh";

    case Perceptron::Threshold:
        return "threshold";

    case Perceptron::SymmetricThreshold:
        return "symmetric_threshold";

    case Perceptron::Linear:
        return "";

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "std::string get_activation_function() const method.\n"
                   << "Unknown activation function.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns the number of inputs to the neuron.
size_t Perceptron::get_inputs_number() const
{
    return synaptic_weights.size();
}

/// Returns the bias value of the neuron.
const double &Perceptron::get_bias() const
{
    return bias;
}

/// Returns the synaptic weight values of the neuron.
const Vector<double> &Perceptron::arrange_synaptic_weights() const
{
    return synaptic_weights;
}

/// Returns the synaptic weight value with index i of the neuron.
/// @param synaptic_weight_index Synaptic weight index.
const double &Perceptron::get_synaptic_weight(const size_t &synaptic_weight_index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();

    if (synaptic_weight_index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double get_synaptic_weight(const size_t&) const method.\n"
               << "Index of synaptic weight must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return synaptic_weights[synaptic_weight_index];
}

/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.
const bool &Perceptron::get_display() const
{
    return display;
}

/// Sets the number of inputs to zero and the rest of members to their default values.
void Perceptron::set()
{
    initialize_bias_normal(0.0, 0.2);
    synaptic_weights.set();
    activation_function = HyperbolicTangent;
    display = true;
}

/// Sets a new number of inputs.
/// It also sets the other members of this object to their defaul values.
/// @param new_inputs_number Number of inputs in the neuron.
void Perceptron::set(const size_t &new_inputs_number)
{
    activation_function = HyperbolicTangent;
    initialize_bias_normal(0.0, 0.2);
    synaptic_weights.set(new_inputs_number);
    initialize_synaptic_weights_normal(0.0, 0.2);
    display = true;
}

/// Sets the number of inputs to a given value and initializes the bias and the synaptic weights with a given value.
/// @param new_inputs_number Number of inputs in the neuron.
/// @param new_parameters_value Parameters initialization value.
void Perceptron::set(const size_t &new_inputs_number, const double &new_parameters_value)
{
    bias = new_parameters_value;
    synaptic_weights.set(new_inputs_number, new_parameters_value);
    activation_function = HyperbolicTangent;
    display = true;
}

/// Sets the members of this perceptron object with those from other perceptron object.
/// @param other_perceptron Setting perceptron object.
void Perceptron::set(const Perceptron &other_perceptron)
{
    bias = other_perceptron.bias;
    synaptic_weights = other_perceptron.synaptic_weights;
    activation_function = other_perceptron.activation_function;
    display = other_perceptron.display;
}

/// Sets a new activation function in the neuron.
/// @param new_activation_function Activation function.
void Perceptron::set_activation_function(const Perceptron::ActivationFunction &new_activation_function)
{
    activation_function = new_activation_function;
}

/// Sets a new activation function in the perceptron with a string containing
/// the name of the activation function.
/// @param new_activation_function_name String with name of activation function.
void Perceptron::set_activation_function(const std::string &new_activation_function_name)
{
    if (new_activation_function_name == "Logistic")
        activation_function = Logistic;
    else if (new_activation_function_name == "HyperbolicTangent")
        activation_function = HyperbolicTangent;
    else if (new_activation_function_name == "Threshold")
        activation_function = Threshold;
    else if (new_activation_function_name == "SymmetricThreshold")
        activation_function = SymmetricThreshold;
    else if (new_activation_function_name == "Linear")
        activation_function = Linear;
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "void set_activation_function(const std::string&) method.\n"
               << "Unknown activation function: " << new_activation_function_name << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new bias value for the perceptron.
/// @param new_bias Bias value.
void Perceptron::set_bias(const double &new_bias)
{
    bias = new_bias;
}

/// This method a new set of synaptic weights for the perceptron.
/// @param new_synaptic_weights Synaptic weight values.
void Perceptron::set_synaptic_weights(const Vector<double> &new_synaptic_weights)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();

    if (new_synaptic_weights.size() != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "void set_synaptic_weights(const Vector<double>&) method.\n"
               << "Size of synaptic weights vector must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    synaptic_weights = new_synaptic_weights;
}

/// Sets the synaptic weight value with index i for the neuron.
/// @param synaptic_weight_index Synaptic weight index.
/// @param new_synaptic_weight Synaptic weight value.
void Perceptron::set_synaptic_weight(const size_t &synaptic_weight_index, const double &new_synaptic_weight)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();

    if (synaptic_weight_index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "void set_synaptic_weight(const size_t&, const double&) method.\n"
               << "Index of synaptic weight must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    synaptic_weights[synaptic_weight_index] = new_synaptic_weight;
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void Perceptron::set_display(const bool &new_display)
{
    display = new_display;
}

/// Sets a new number of inputs in the neuron.
/// The new synaptic weights are initialized at random with a normal distribution of
/// mean 0 and standard deviation 1.
/// @param new_inputs_number Number of inputs in the neuton.
void Perceptron::set_inputs_number(const size_t &new_inputs_number)
{
    initialize_bias_normal(0.0, 1.0);
    synaptic_weights.set(new_inputs_number);
    initialize_synaptic_weights_normal(0.0, 1.0);
}

/// Returns the number of parameters (bias and synaptic weights) in the perceptron.
size_t Perceptron::count_parameters_number() const
{
    const size_t inputs_number = get_inputs_number();
    return 1 + inputs_number;
}

/// Returns the parameters (bias and synaptic weights) of the perceptron.
Vector<double> Perceptron::arrange_parameters() const
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters[0] = bias;
    const size_t inputs_number = get_inputs_number();
    for (size_t i = 0; i < inputs_number; i++) {
        parameters[(size_t) 1 + i] = synaptic_weights[i];
    }
    return parameters;
}

/// This method set a new set of parameters (bias and synaptic weights) to the perceptron.
/// @param new_parameters New set of parameters
void Perceptron::set_parameters(const Vector<double> &new_parameters)
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_parameters.size();

    if (size != 1 + inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "void set_parameters(const Vector<double>&) method.\n"
               << "Size must be equal to one plus number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    bias = new_parameters[0];
    for (size_t i = 0; i < inputs_number; i++) {
        synaptic_weights[i] = new_parameters[i + 1];
    }
}

/// Initializes the bias with a given value.
/// @param value Initialization value.
void Perceptron::initialize_bias(const double &value)
{
    bias = value;
}

/// Initializes the neuron's bias with a random value chosen from a uniform distribution.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.
void Perceptron::initialize_bias_uniform(const double &minimum, const double &maximum)
{

#ifdef __OPENNN_DEBUG__
    if (minimum > maximum) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "initialize_bias_uniform(const double&, const double&) method.\n"
               << "Minimum value must be less than maximum value.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    bias = calculate_random_uniform(minimum, maximum);
}

/// Initializes all the synaptic weights of the neuron with a given value.
/// @param value Initialization value.
void Perceptron::initialize_synaptic_weights(const double &value)
{
    synaptic_weights.initialize(value);
}

/// Initializes the neuron's synaptic weights with random values chosen from an uniform distribution.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.
void Perceptron::initialize_synaptic_weights_uniform(const double &minimum, const double &maximum)
{
    synaptic_weights.randomize_uniform(minimum, maximum);
}

/// Initializes the neuron's bias with random values chosen from a normal distribution.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.
void Perceptron::initialize_bias_normal(const double &mean, const double &standard_deviation)
{

#ifdef __OPENNN_DEBUG__
    if (standard_deviation < 0.0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "initialize_bias_normal(const double&, const double&) method.\n"
               << "Standard deviation must be equal or greater than zero.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    bias = calculate_random_normal(mean, standard_deviation);
}

/// Initializes the neuron's synaptic weights with random values chosen from a normal distribution.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.
void Perceptron::initialize_synaptic_weights_normal(const double &mean, const double &standard_deviation)
{
    synaptic_weights.randomize_normal(mean, standard_deviation);
}

/// Initializes the bias and the synaptic weights with a given value.
/// @param value Parameters initialization value.
void Perceptron::initialize_parameters(const double &value)
{
    bias = value;
    synaptic_weights.initialize(value);
}

/// Returns the combination to the neuron for a set of inputs signals, using the dot product
/// combination function.
/// @param inputs Set of inputs signals to the neuron.
double Perceptron::calculate_combination(const Vector<double> &inputs) const
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    if (inputs_number == 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "calculate_combination(const Vector<double>&) method.\n"
               << "Number of inputs must be greater than zero.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t inputs_size = inputs.size();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_combination(const Vector<double>&) method.\n"
               << "Size of inputs (" << inputs_size << ") must be equal to number of inputs (" << inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    double combination = bias;
    for (size_t i = 0; i < inputs_number; i++) {
        combination += synaptic_weights[i] * inputs[i];
    }
    return combination;
}

/// Returns which would be the combination for some inputs and for a potential set of parameters.
/// @param inputs Vector of inputs to the perceptron.
/// @param parameters Potential bias and synaptic weights in the perceptron.
double Perceptron::calculate_combination(const Vector<double> &inputs, const Vector<double> &parameters) const
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();

    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_combination(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t parameters_size = parameters.size();
    const size_t parameters_number = count_parameters_number();

    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_combination(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of potential parameters (" << parameters_size << ") must be equal to number of parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    double combination = parameters[0];
    for (size_t i = 0; i < inputs_number; i++) {
        combination += parameters[i + 1] * inputs[i];
    }
    return combination;
}

/// Returns the activation from the neuron for a combination.
/// The outputs depends on the activation function used.
/// @param combination Combination of the neuron.
double Perceptron::calculate_activation(const double &combination) const
{
    switch (activation_function) {
    case Perceptron::Logistic:
        return 1.0 / (1.0 + exp(-combination));

    case Perceptron::HyperbolicTangent:
        return 1.0 - 2.0 / (exp(2.0 * combination) + 1.0);

    case Perceptron::Threshold:
        return combination < 0? 0.0: 1.0;

    case Perceptron::SymmetricThreshold:
        return combination < 0? -1.0: 1.0;

    case Perceptron::Linear:
        return combination;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation(const double&) const  method.\n"
                   << "Unknown activation function.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns the activation derivative of the neuron for a combination.
/// The activation derivative depends on the activation function used.
/// @param combination Combination of the neuron.
double Perceptron::calculate_activation_derivative(const double &combination) const
{
    switch (activation_function) {
    case Perceptron::Logistic:
        {
            const double logistic_function = 1.0 / (1.0 + exp(-combination));
            return logistic_function * (1.0 - logistic_function);
        }

    case Perceptron::HyperbolicTangent:
        {
            const double tanh_combination = tanh(combination);
            return 1.0 - tanh_combination * tanh_combination;
        }

    case Perceptron::Threshold:
        if (combination == 0.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_derivative(const double&) const  method.\n"
                   << "Threshold activation function is not derivable.\n";

            throw std::logic_error(buffer.str());
        }
        return 0.0;

    case Perceptron::SymmetricThreshold:
        if (combination == 0.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_derivative(const double&) const  method.\n"
                   << "Symmetric threshold activation function is not derivable.\n";

            throw std::logic_error(buffer.str());
        }
        return 0.0;

    case Perceptron::Linear:
        return 1.0;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_derivative(const double&) const  method.\n"
                   << "Unknown activation function.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns the activation second derivative of the neuron for a combination.
/// The second derivative of the outputs depends on the activation function used.
/// @param combination Combination of the neuron.
double Perceptron::calculate_activation_second_derivative(const double &combination) const
{
    switch (activation_function) {
    case Perceptron::Logistic:
        {
            const double logistic_function = 1.0 / (1.0 + exp(-combination));
            return logistic_function * (1.0 - logistic_function) * (1.0 - 2 * logistic_function);
        }

    case Perceptron::HyperbolicTangent:
        {
            const double tanh_combination = tanh(combination);
            return -2.0 * tanh_combination * (1.0 - pow(tanh_combination, 2));
        }

    case Perceptron::Threshold:
        if (combination == 0.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_second_derivative(const double&) const  method.\n"
                   << "Threshold activation function is not derivable.\n";

            throw std::logic_error(buffer.str());
        }
        return 0.0;

    case Perceptron::SymmetricThreshold:
        if (combination == 0.0) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_second_derivative(const double&) const  method.\n"
                   << "Symmetric threshold activation function is not derivable.\n";

            throw std::logic_error(buffer.str());
        }
        return 0.0;

    case Perceptron::Linear:
        return 0.0;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Perceptron class.\n"
                   << "double calculate_activation_second_derivative(const double&) const  method.\n"
                   << "Unknown activation function.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns the output from the neuron for a set of inputs signals.
/// The output depends on the activation function used.
/// @param inputs Set of input signals to the neuron.
double Perceptron::calculate_output(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t size = inputs.size();
    const size_t inputs_number = get_inputs_number();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_output(const Vector<double>&) const method.\n"
               << "Size must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_activation(calculate_combination(inputs));
}

/// Returns the output from the neuron for a set of inputs.
/// The output depends on the activation function used.
/// @param inputs Set of inputs signals to the neuron.
/// @param parameters Set of potential bias and synaptic weights in the perceptron.
double Perceptron::calculate_output(const Vector<double> &inputs, const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();

    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_output(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t parameters_size = parameters.size();
    const size_t parameters_number = count_parameters_number();

    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_output(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of potential parameters (" << parameters_size << ") must be equal to number of parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_activation(calculate_combination(inputs, parameters));
}

/// Returns the partial derivatives of the outputs with respect to the inputs.
/// @param inputs Vector of inputs to the perceptron.
Vector<double> Perceptron::calculate_gradient(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t size = inputs.size();
    const size_t inputs_number = get_inputs_number();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "Vector<double> calculate_gradient(const Vector<double>&) const method.\n"
               << "Size must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return synaptic_weights * calculate_activation_derivative(calculate_combination(inputs));
}

/// Returns the partial derivatives of the outputs with respect to a given set of  parameters
/// and at a given inputs point.
/// @param inputs Vector of inputs to the perceptron.
/// @param parameters Vector of potential parameters for the perceptron.
Vector<double> Perceptron::calculate_gradient(const Vector<double> &inputs, const Vector<double> &parameters) const
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = inputs.size();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_gradient(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const double activation_derivative = calculate_activation_derivative(calculate_combination(inputs, parameters));
    Vector<double> gradient(1 + inputs_number);

    // Bias
    gradient[0] = activation_derivative;

    // Synaptic weights
    for (size_t i = 1; i < 1 + inputs_number; i++) {
        gradient[i] = inputs[i - 1] * activation_derivative;
    }
    return gradient;
}

/// Returns the partial derivatives of the combination with respect to the inputs.
Vector<double> Perceptron::calculate_combination_gradient(const Vector<double> &) const
{
    return synaptic_weights;
}

/// Returns the partial derivatives of the combination with respect to the parameters at some inputs point.
/// @param inputs Vector of inputs to the perceptron.
Vector<double> Perceptron::calculate_combination_gradient(const Vector<double> &inputs,
                                                          const Vector<double> &) const
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = inputs.size();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "double calculate_combination_gradient(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<double> combination_gradient(1 + inputs_number);

    // Bias
    combination_gradient[0] = 1.0;

    // Synaptic weights
    for (size_t i = 1; i < 1 + inputs_number; i++) {
        combination_gradient[i] = inputs[i - 1];
    }
    return combination_gradient;
}

/// Returns the second partial derivatives of the outputs with respect to the inputs.
/// @param inputs Vector of inputs to the perceptron.
Matrix<double> Perceptron::calculate_Hessian(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    const size_t inputs_size = inputs.size();

    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "Matrix<double> calculate_Hessian(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return synaptic_weights.direct(synaptic_weights) *
           calculate_activation_second_derivative(calculate_combination(inputs));
}

/// This method retuns the second derivatives of the outputs with respect to a given set of parameters,
/// at some inputs point.
/// This is called the Hessian of the outputs parameters function.
/// @param inputs Input vector.
/// @param parameters Potential parameters vector.
Matrix<double> Perceptron::calculate_Hessian(const Vector<double> &inputs, const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();

    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "Matrix<double> calculate_Hessian(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const double activation_second_derivative =
            calculate_activation_second_derivative(calculate_combination(inputs, parameters));
    const size_t parameters_number = count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number);

    // Bias - bias derivative
    Hessian(0, 0) = activation_second_derivative;

    // Bias - synaptic weight derivative
    for (size_t i = 1; i < parameters_number; i++) {
        Hessian(0, i) = activation_second_derivative * inputs[i - 1];
    }

    // Synaptic weight - synaptic weight derivative
    for (size_t i = 1; i < parameters_number; i++) {
        for (size_t j = 1; j < parameters_number; j++) {
            Hessian(i, j) = activation_second_derivative * inputs[i - 1] * inputs[j - 1];
        }
    }

    // Hessian symmetry
    for (size_t i = 0; i < parameters_number; i++) {
        for (size_t j = 0; j < i; j++) {
            Hessian(i, j) = Hessian(j, i);
        }
    }

    return Hessian;
}

/// This method retuns the second derivatives of the combination with respect to the inputs.
//@todo
Matrix<double> Perceptron::calculate_combination_Hessian(const Vector<double> &) const
{
    const size_t inputs_number = get_inputs_number();
    const Matrix<double> combination_Hessian(inputs_number, inputs_number, 0.0);
    return combination_Hessian;
}

/// Returns the second derivatives of the combination with respect to the parameters.
/// The Hessian matrix of the combination parameters function is always
/// a squared matrix of size the number of parameters and zero values.
//@todo
Matrix<double> Perceptron::calculate_combination_Hessian(const Vector<double> &, const Vector<double> &) const
{
    const size_t parameters_number = count_parameters_number();
    const Matrix<double> Hessian(parameters_number, parameters_number, 0.0);
    return Hessian;
}

/// Makes the perceptron to have one more input.
/// The corresponding synaptic weight is initialized to zero.
void Perceptron::grow_input()
{
    synaptic_weights.push_back(0.0);
}

/// This method removes a given input from the neuron.
/// @param index Index of input to be removed.
void Perceptron::prune_input(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();

    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Perceptron class.\n"
               << "void prune_input(const size_t&) method.\n"
               << "Index of input is equal or greater than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    synaptic_weights.erase(synaptic_weights.begin() + index);
}

/// Returns a string with the mathematical expression represented by the perceptron.
/// @param inputs_name Name of input variables to the neuron.
/// @param output_name Name of output variable from the neuron.
std::string Perceptron::write_expression(const Vector<std::string> &inputs_name,
                                         const std::string &output_name) const
{
    std::ostringstream buffer;
    buffer << output_name << "=" << write_activation_function() << "("
           << bias << "\n";

    const size_t inputs_number = get_inputs_number();
    for (size_t i = 0; i < inputs_number; i++) {
        if (synaptic_weights[i] >= 0)
            buffer << "+";
        buffer << synaptic_weights[i] << "*" << inputs_name[i];
        if (i != 0 && i % 4 == 0 && i != inputs_number - 1)
            buffer << "\n";
    }
    buffer << ");\n";
    return buffer.str();
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
