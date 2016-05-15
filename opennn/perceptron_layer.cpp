/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P E R C E P T R O N   L A Y E R   C L A S S                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "perceptron_layer.h"

namespace OpenNN
{

/// Default constructor.
/// It creates a empty layer object, with no perceptrons.
/// This constructor also initializes the rest of class members to their default values.
PerceptronLayer::PerceptronLayer(void)
{
    set();
}

/// Layer architecture constructor.
/// It creates a layer object with given numbers of inputs and perceptrons.
/// The parameters are initialized at random.
/// This constructor also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of inputs in the layer.
/// @param new_perceptrons_number Number of perceptrons in the layer.
PerceptronLayer::PerceptronLayer(const size_t &new_inputs_number, const size_t &new_perceptrons_number)
{
    set(new_inputs_number, new_perceptrons_number);
}

/// Copy constructor.
/// It creates a copy of an existing perceptron layer object.
/// @param other_perceptron_layer Perceptron layer object to be copied.
PerceptronLayer::PerceptronLayer(const PerceptronLayer &other_perceptron_layer)
{
    set(other_perceptron_layer);
}

/// Destructor.
/// This destructor does not delete any pointer.
PerceptronLayer::~PerceptronLayer(void)
{
}

/// Assignment operator.
/// It assigns to this object the members of an existing perceptron layer object.
/// @param other_perceptron_layer Perceptron layer object to be assigned.
PerceptronLayer &PerceptronLayer::operator=(const PerceptronLayer &other_perceptron_layer)
{
    if (this != &other_perceptron_layer) {
        perceptrons = other_perceptron_layer.perceptrons;
        display = other_perceptron_layer.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_perceptron_layer Perceptron layer to be compared with.
bool PerceptronLayer::operator==(const PerceptronLayer &other_perceptron_layer) const
{
    return perceptrons == other_perceptron_layer.perceptrons &&
           display == other_perceptron_layer.display;
}

/// Returns true if the size of the layer is zero, and false otherwise.
bool PerceptronLayer::is_empty(void) const
{
    return perceptrons.empty();
}

/// Returns a constant reference to the vector of perceptrons defining the layer.
const Vector<Perceptron> &PerceptronLayer::get_perceptrons(void) const
{
    return perceptrons;
}

/// Returns the number of inputs to the layer.
size_t PerceptronLayer::get_inputs_number(void) const
{
    return is_empty()? 0: perceptrons[0].get_inputs_number();
}

/// Returns the size of the perceptrons vector.
size_t PerceptronLayer::get_perceptrons_number(void) const
{
    return perceptrons.size();
}

/// Returns a reference to a given element in the perceptrons vector.
/// @param index Index of perceptron element.
const Perceptron &PerceptronLayer::get_perceptron(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t perceptrons_number = get_perceptrons_number();
    if (index >= perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "const Perceptron& get_perceptron(const size_t&) const method.\n"
               << "Index of perceptron must be less than layer size.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return perceptrons[index];
}

/// Returns the number of parameters (biases and synaptic weights) of the layer.
size_t PerceptronLayer::count_parameters_number(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    size_t parameters_number = 0;
    for (size_t i = 0; i < perceptrons_number; i++) {
        parameters_number += perceptrons[i].count_parameters_number();
    }
    return parameters_number;
}

/// Returns a vector of size the number of neurons in the layer,
/// where each element is equal to the total number of parameters in the current and all the previous neurons.
Vector<size_t> PerceptronLayer::count_cumulative_parameters_number(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<size_t> cumulative_parameters_number(perceptrons_number);
    if (perceptrons_number > 0) {
        cumulative_parameters_number[0] = perceptrons[0].count_parameters_number();
        for (size_t i = 1; i < perceptrons_number; i++) {
            cumulative_parameters_number[i] = cumulative_parameters_number[i - 1] + perceptrons[i].count_parameters_number();
        }
    }
    return cumulative_parameters_number;
}

/// Returns the biases from all the perceptrons in the layer.
/// The format is a vector of real values.
/// The size of this vector is the number of neurons in the layer.
Vector<double> PerceptronLayer::arrange_biases(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<double> biases(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        biases[i] = perceptrons[i].get_bias();
    }
    return biases;
}

/// Returns the synaptic weights from the perceptrons.
/// The format is a matrix of real values.
/// The number of rows is the number of neurons in the layer.
/// The number of columns is the number of inputs to the layer.
Matrix<double> PerceptronLayer::arrange_synaptic_weights(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    const size_t inputs_number = get_inputs_number();
    Matrix<double> synaptic_weights(perceptrons_number, inputs_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        for (size_t j = 0; j < inputs_number; j++) {
            synaptic_weights(i, j) = perceptrons[i].get_synaptic_weight(j);
        }
    }
    return synaptic_weights;
}

/// Returns a single vector with all the layer parameters.
/// The format is a vector of real values.
/// The size is the number of parameters in the layer.
Vector<double> PerceptronLayer::arrange_parameters(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    if (perceptrons_number == 0) {
        Vector<double> parameters;
        return parameters;
    }

    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    const size_t perceptron_parameters_number = perceptrons[0].count_parameters_number();
    Vector<double> perceptron_parameters(perceptron_parameters_number);
    size_t position = 0;
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptron_parameters = perceptrons[i].arrange_parameters();
        parameters.tuck_in(position, perceptron_parameters);
        position += perceptron_parameters_number;
    }
    return parameters;
}

/// Returns the number of parameters of each perceptron in this layer.
/// This is equal to one plus the number of inputs.
size_t PerceptronLayer::count_perceptron_parameters_number(void) const
{
    const size_t inputs_number = get_inputs_number();
    return 1 + inputs_number;
}

/// Returns the parameters of every single perceptron in the layer.
/// The format is a vector of vectors.
/// The size is equal to the number of perceptrons in the layer.
/// Each element contains the parameters of a perceptron, with size one plus the number of inputs in this layer.
Vector<Vector<double>> PerceptronLayer::arrange_perceptrons_parameters(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<Vector<double>> perceptrons_parameters(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons_parameters[i] = perceptrons[i].arrange_parameters();
    }
    return perceptrons_parameters;
}

/// Returns the activation function of the layer.
/// The activation function of a layer is the activation function of all perceptrons in it.
const Perceptron::ActivationFunction &PerceptronLayer::get_activation_function(void) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    if (perceptrons_number == 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
        << "Perceptron::ActivationFunction& get_activation_function(void) method.\n"
        << "PerceptronLayer is empty.\n";

        throw std::logic_error(buffer.str());
    }

    return perceptrons[0].get_activation_function();
}

/// Returns a string with the name of the layer activation function.
/// This can be: Logistic, HyperbolicTangent, Threshold, SymmetricThreshold or Linear.
std::string PerceptronLayer::write_activation_function(void) const
{
    const Perceptron::ActivationFunction activation_function = get_activation_function();
    switch (activation_function) {
    case Perceptron::Logistic:
        return "Logistic";

    case Perceptron::HyperbolicTangent:
        return "HyperbolicTangent";

    case Perceptron::Threshold:
        return "Threshold";

    case Perceptron::SymmetricThreshold:
        return "SymmetricThreshold";

    case Perceptron::Linear:
        return "Linear";

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerceptronLayer class.\n"
                   << "std::string write_activation_function_name(void) const method.\n"
                   << "Unknown layer activation function.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns true if messages from this class are to be displayed on the screen,
/// or false if messages from this class are not to be displayed on the screen.
const bool &PerceptronLayer::get_display(void) const
{
    return display;
}

/// Sets an empty layer, wihtout any perceptron.
/// It also sets the rest of members to their default values.
void PerceptronLayer::set(void)
{
    perceptrons.set();
    set_default();
}

/// Sets a new layer from a given vector of perceptrons.
/// The rest of members of this class are given their defaul values.
void PerceptronLayer::set(const Vector<Perceptron> &new_perceptrons)
{
    perceptrons = new_perceptrons;
    set_default();
}

/// Sets new numbers of inputs and perceptrons in the layer.
/// It also sets the rest of members to their default values.
/// @param new_inputs_number Number of inputs.
/// @param new_perceptrons_number Number of perceptron neurons.
void PerceptronLayer::set(const size_t &new_inputs_number, const size_t &new_perceptrons_number)
{
    perceptrons.set(new_perceptrons_number);
    for (size_t i = 0; i < new_perceptrons_number; i++) {
        perceptrons[i].set_inputs_number(new_inputs_number);
    }
    set_default();
}

/// Sets the members of this perceptron layer object with those from other perceptron layer object.
/// @param other_perceptron_layer PerceptronLayer object to be copied.
void PerceptronLayer::set(const PerceptronLayer &other_perceptron_layer)
{
    perceptrons = other_perceptron_layer.perceptrons;
    display = other_perceptron_layer.display;
}

/// Sets a new vector of perceptrons in the layer.
/// @param new_perceptrons Perceptrons vector.
void PerceptronLayer::set_perceptrons(const Vector<Perceptron> &new_perceptrons)
{
    perceptrons = new_perceptrons;
}

/// Sets a single perceptron in the layer.
/// @param i Index of perceptron.
/// @param new_perceptron Perceptron neuron to be set.
void PerceptronLayer::set_perceptron(const size_t &i, const Perceptron &new_perceptron)
{
    perceptrons[i] = new_perceptron;
}

/// Sets those members not related to the vector of perceptrons to their default value.
/// <ul>
/// <li> Display: True.
/// </ul>
void PerceptronLayer::set_default(void)
{
    display = true;
}

/// Sets a new number of inputs in the layer.
/// The new synaptic weights are initialized at random.
/// @param new_inputs_number Number of layer inputs.
void PerceptronLayer::set_inputs_number(const size_t &new_inputs_number)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].set_inputs_number(new_inputs_number);
    }
}

/// Sets a new number perceptrons in the layer.
/// All the parameters are also initialized at random.
/// @param new_perceptrons_number New number of neurons in the layer.
void PerceptronLayer::set_perceptrons_number(const size_t &new_perceptrons_number)
{
    const size_t perceptrons_number = get_perceptrons_number();
    const size_t inputs_number = get_inputs_number();
    if (perceptrons_number > 0) {
        const Perceptron::ActivationFunction &activation_function = get_activation_function();
        perceptrons.set(new_perceptrons_number);
        set_activation_function(activation_function);
    } else
        perceptrons.set(new_perceptrons_number);
    set_inputs_number(inputs_number);
}

/// Sets the biases of all perceptrons in the layer from a single vector.
/// @param new_biases New set of biases in the layer.
void PerceptronLayer::set_biases(const Vector<double> &new_biases)
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t new_biases_size = new_biases.size();
    if (new_biases_size != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void set_biases(const Vector<double>&) method.\n"
               << "Size must be equal to number of perceptrons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].set_bias(new_biases[i]);
    }
}

/// Sets the synaptic weights of this perceptron layer from a single matrix.
/// The format is a matrix of real numbers.
/// The number of rows is the number of neurons in the corresponding layer.
/// The number of columns is the number of inputs to the corresponding layer.
/// @param new_synaptic_weights New set of synaptic weights in that layer.
void PerceptronLayer::set_synaptic_weights(const Matrix<double> &new_synaptic_weights)
{
    const size_t inputs_number = get_inputs_number();
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t rows_number = new_synaptic_weights.get_rows_number();
    const size_t columns_number = new_synaptic_weights.get_columns_number();
    if (rows_number != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void set_synaptic_weights(const Matrix<double>&) method.\n"
               << "Number of rows must be equal to size of layer.\n";

        throw std::logic_error(buffer.str());
    } else if (columns_number != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void set_synaptic_weights(const Matrix<double>&) method.\n"
               << "Number of columns must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < perceptrons_number; i++) {
        for (size_t j = 0; j < inputs_number; j++) {
            perceptrons[i].set_synaptic_weight(j, new_synaptic_weights(i, j));
        }
    }
}

/// Sets the parameters of this layer.
/// @param new_parameters Parameters vector for that layer.
void PerceptronLayer::set_parameters(const Vector<double> &new_parameters)
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t parameters_number = count_parameters_number();
    const size_t new_parameters_size = new_parameters.size();
    if (new_parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void set_parameters(const Vector<double>&) method.\n"
               << "Size of new parameters vector must be equal to number of parameters.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    if (perceptrons_number != 0) {
        const size_t perceptron_parameters_number = perceptrons[0].count_parameters_number();
        Vector<double> perceptron_parameters(perceptron_parameters_number);
        size_t position = 0;
        for (size_t i = 0; i < perceptrons_number; i++) {
            perceptron_parameters = new_parameters.take_out(position, perceptron_parameters_number);
            perceptrons[i].set_parameters(perceptron_parameters);
            position += perceptron_parameters_number;
        }
    }
}

/// This class sets a new activation (or transfer) function in a single layer.
/// @param new_activation_function Activation function for the layer.
void PerceptronLayer::set_activation_function(const Perceptron::ActivationFunction &new_activation_function)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].set_activation_function(new_activation_function);
    }
}

/// Sets a new activation (or transfer) function in a single layer.
/// The second argument is a string containing the name of the function ("Logistic", "HyperbolicTangent", "Threshold", etc).
/// @param new_activation_function Activation function for that layer.
void PerceptronLayer::set_activation_function(const std::string &new_activation_function)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].set_activation_function(new_activation_function);
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void PerceptronLayer::set_display(const bool &new_display)
{
    display = new_display;
}

/// Makes the perceptron layer to have one more input.
void PerceptronLayer::grow_input(void)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].grow_input();
    }
}

/// Makes the perceptron layer to have one more perceptron.
void PerceptronLayer::grow_perceptron(void)
{
    const size_t inputs_number = get_inputs_number();
    const Perceptron::ActivationFunction activation_function = get_activation_function();
    Perceptron perceptron(inputs_number);
    perceptron.initialize_parameters(0.0);
    perceptron.set_activation_function(activation_function);
    perceptrons.push_back(perceptron);
}

/// Makes the perceptron layer to have perceptrons_added more perceptrons.
/// @param perceptrons_added Number of perceptrons to be added.
void PerceptronLayer::grow_perceptrons(const size_t &perceptrons_added)
{
    for (size_t i = 0; i < perceptrons_added; i++)
        grow_perceptron();
}

/// This method removes a given input from the layer of perceptrons.
/// @param index Index of input to be pruned.
void PerceptronLayer::prune_input(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void prune_input(const size_t&) method.\n"
               << "Index of input is equal or greater than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].prune_input(index);
    }
}

/// This method removes a given perceptron from the layer.
/// @param index Index of perceptron to be pruned.
void PerceptronLayer::prune_perceptron(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t perceptrons_number = get_perceptrons_number();
    if (index >= perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "void prune_perceptron(const size_t&) method.\n"
               << "Index of perceptron is equal or greater than number of perceptrons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    perceptrons.erase(perceptrons.begin() + index);
}

/// Initializes the perceptron layer with a random number of inputs and a randon number of perceptrons.
/// That can be useful for testing purposes.
void PerceptronLayer::initialize_random(void)
{
    const size_t inputs_number = rand() % 10 + 1;
    const size_t perceptrons_number = rand() % 10 + 1;
    set(inputs_number, perceptrons_number);
    set_display(true);
}

/// Initializes the biases of all the perceptrons in the layer of perceptrons with a given value.
/// @param value Biases initialization value.
void PerceptronLayer::initialize_biases(const double &value)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].initialize_bias(value);
    }
}

/// Initializes the synaptic weights of all the perceptrons in the layer of perceptrons perceptron with a given value.
/// @param value Synaptic weights initialization value.
void PerceptronLayer::initialize_synaptic_weights(const double &value)
{
    const size_t perceptrons_number = get_perceptrons_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptrons[i].initialize_synaptic_weights(value);
    }
}

/// Initializes all the biases and synaptic weights in the neural newtork with a given value.
/// @param value Parameters initialization value.
void PerceptronLayer::initialize_parameters(const double &value)
{
    const size_t parameters_number = count_parameters_number();
    const Vector<double> parameters(parameters_number, value);
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the neural newtork at random with values comprised
/// between -1 and +1.
void PerceptronLayer::randomize_parameters_uniform(void)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_uniform();
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the layer of perceptrons at random with values
/// comprised between a minimum and a maximum values.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.
void PerceptronLayer::randomize_parameters_uniform(const double &minimum, const double &maximum)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_uniform(minimum, maximum);
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the layer of perceptrons at random, with values
/// comprised between different minimum and maximum numbers for each parameter.
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.
void PerceptronLayer::randomize_parameters_uniform(const Vector<double> &minimum, const Vector<double> &maximum)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_uniform(minimum, maximum);
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the layer of perceptrons at random, with values
/// comprised between a different minimum and maximum numbers for each parameter.
/// All minimum are maximum initialization values must be given from a vector of two real vectors.
/// The first element must contain the minimum inizizalization value for each parameter.
/// The second element must contain the maximum inizizalization value for each parameter.
/// @param minimum_maximum Vector of minimum and maximum initialization values.
void PerceptronLayer::randomize_parameters_uniform(const Vector<Vector<double>> &minimum_maximum)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_uniform(minimum_maximum[0], minimum_maximum[1]);
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the newtork with random values chosen from a
/// normal distribution with mean 0 and standard deviation 1.
void PerceptronLayer::randomize_parameters_normal(void)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_normal();
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the layer of perceptrons with random random values
/// chosen from a normal distribution with a given mean and a given standard deviation.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.
void PerceptronLayer::randomize_parameters_normal(const double &mean, const double &standard_deviation)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_normal(mean, standard_deviation);
    set_parameters(parameters);
}

/// Initializes all the biases an synaptic weights in the layer of perceptrons with random values chosen
/// from normal distributions with different mean and standard deviation for each parameter.
/// @param mean Vector of mean values.
/// @param standard_deviation Vector of standard deviation values.
void PerceptronLayer::randomize_parameters_normal(const Vector<double> &mean,
                                                  const Vector<double> &standard_deviation)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_normal(mean, standard_deviation);
    set_parameters(parameters);
}

/// Initializes all the biases and synaptic weights in the layer of perceptrons with random values chosen
/// from normal distributions with different mean and standard deviation for each parameter.
/// All mean and standard deviation values are given from a vector of two real vectors.
/// The first element must contain the mean value for each parameter.
/// The second element must contain the standard deviation value for each parameter.
/// @param mean_standard_deviation Vector of mean and standard deviation values.
void PerceptronLayer::randomize_parameters_normal(const Vector<Vector<double>> &mean_standard_deviation)
{
    const size_t parameters_number = count_parameters_number();
    Vector<double> parameters(parameters_number);
    parameters.randomize_normal(mean_standard_deviation[0], mean_standard_deviation[1]);
    set_parameters(parameters);
}

/// Calculates the norm of a layer parameters vector.
double PerceptronLayer::calculate_parameters_norm(void) const
{
    return arrange_parameters().calculate_norm();
}

/// Returns the combination to every perceptron in the layer as a function of the inputs to that layer.
/// @param inputs Inputs to the layer.
Vector<double> PerceptronLayer::calculate_combinations(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_combinations(const Vector<double>&) const method.\n"
               << "Size of inputs to layer must be equal to number of layer inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t perceptrons_number = get_perceptrons_number();
    Vector<double> combination(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        combination[i] = perceptrons[i].calculate_combination(inputs);
    }
    return combination;
}

/// Returns the partial derivatives of the combination of a layer with respect to the inputs.
/// All that partial derivatives are arranged in the so called Jacobian matrix of the layer combination function.
Matrix<double> PerceptronLayer::calculate_combinations_Jacobian(const Vector<double> &) const
{
    return arrange_synaptic_weights();
}

/// Returns the second partial derivatives of the combination of a layer with respect to the inputs of that layer.
/// All that partial derivatives are arranged in the so called Hessian form, represented as a vector of matrices,
/// of the layer combination function.
Vector<Matrix<double>> PerceptronLayer::calculate_combinations_Hessian_form(const Vector<double> &) const
{
    const size_t inputs_number = get_inputs_number();
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<Matrix<double>> combination_Hessian_form(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        combination_Hessian_form[i].set(inputs_number, inputs_number, 0.0);
    }
    return combination_Hessian_form;
}

/// Returns which would be the combination of a layer as a function of the inputs and for a set of parameters.
/// @param inputs Vector of inputs to that layer.
/// @param parameters Vector of parameters in the layer.
Vector<double> PerceptronLayer::calculate_combinations(const Vector<double> &inputs,
                                                       const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_combination_parameters(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of layer inputs (" << inputs_size << ") must be equal to number of layer inputs (" << inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t parameters_size = parameters.size();
    const size_t parameters_number = count_parameters_number();
    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_combination_parameters(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of layer parameters (" << parameters_size << ") must be equal to number of lasyer parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t perceptrons_number = get_perceptrons_number();
    const size_t perceptron_parameters_number = count_perceptron_parameters_number();
    Vector<double> combinations(perceptrons_number);
    Vector<double> perceptron_parameters(perceptron_parameters_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        perceptron_parameters = parameters.take_out(i * perceptron_parameters_number, perceptron_parameters_number);
        combinations[i] = perceptrons[i].calculate_combination(inputs, perceptron_parameters);
    }
    return combinations;
}

/// Returns the partial derivatives of the combination of a layer with respect to the parameters in that layer, for a given set of inputs.
/// All that partial derivatives are arranged in the so called Jacobian matrix of the layer combination function.
/// @param inputs Vector of inputs to that layer.
Matrix<double> PerceptronLayer::calculate_combinations_Jacobian(const Vector<double> &inputs,
                                                                const Vector<double> &) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    const size_t parameters_number = count_parameters_number();
    const size_t inputs_number = get_inputs_number();
    Matrix<double> combinations_Jacobian(perceptrons_number, parameters_number, 0.0);
    size_t column_index;
    for (size_t i = 0; i < perceptrons_number; i++) {
        // Bias derivative
        column_index = (1 + inputs_number) * i;
        combinations_Jacobian(i, column_index) = 1.0;

        // Synaptic weight derivatives
        for (size_t j = 0; j < inputs_number; j++) {
            column_index = 1 + (1 + inputs_number) * i + j;
            combinations_Jacobian(i, column_index) = inputs[j];
        }
    }
    return combinations_Jacobian;
}

/// Returns the second partial derivatives of the combination of a layer
/// with respect to the parameters in that layer, for a given set of inputs.
/// All that partial derivatives are arranged in the so called Hessian form,
/// represented as a vector of matrices, of the layer combination function.
Vector<Matrix<double>> PerceptronLayer::calculate_combinations_Hessian_form(const Vector<double> &,
                                                                            const Vector<double> &) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<Matrix<double>> combination_parameters_Hessian_form(perceptrons_number);
    const size_t parameters_number = count_parameters_number();
    for (size_t i = 0; i < perceptrons_number; i++) {
        combination_parameters_Hessian_form[i].set(parameters_number, parameters_number, 0.0);
    }
    return combination_parameters_Hessian_form;
}

/// Returns the activations from every perceptron in a layer as a function of their combination.
/// @param combinations Combination from every neuron in the layer.
Vector<double> PerceptronLayer::calculate_activations(const Vector<double> &combinations) const
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t combination_size = combinations.size();
    if (combination_size != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_activation(const Vector<double>&) const method.\n"
               << "Combination size must be equal to number of neurons.\n";

        throw std::logic_error(buffer.str());
    }

    if (combination_size == 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_activation(const Vector<double>&) const method.\n"
               << "Combination size cannot be empty.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<double> activations(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        activations[i] = perceptrons[i].calculate_activation(combinations[i]);
    }
    return activations;
}

/// Returns the activation derivative from every perceptron in the layer as a function of its combination.
/// @param combination Combination to every neuron in the layer.
Vector<double> PerceptronLayer::calculate_activations_derivatives(const Vector<double> &combination) const
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t combination_size = combination.size();
    if (combination_size != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_activations_derivatives(const Vector<double>&) const method.\n"
               << "Size of combination must be equal to number of neurons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<double> activation_derivatives(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        activation_derivatives[i] = perceptrons[i].calculate_activation_derivative(combination[i]);
    }
    return activation_derivatives;
}

/// Returns the activation second derivative from every perceptron as a function of their combination.
/// @param combination Combination to every perceptron in the layer.
Vector<double> PerceptronLayer::calculate_activations_second_derivatives(const Vector<double> &combination) const
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t combination_size = combination.size();
    if (combination_size != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_activations_second_derivatives(const Vector<double>&) const method.\n"
               << "Size of combinations must be equal to number of neurons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<double> activation_second_derivatives(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        activation_second_derivatives[i] = perceptrons[i].calculate_activation_second_derivative(combination[i]);
    }
    return activation_second_derivatives;
}

/// Arranges a "Jacobian" matrix from a vector of derivatives.
/// @param activation_derivative Vector of activation function derivatives.
Matrix<double> PerceptronLayer::arrange_activations_Jacobian(const Vector<double> &activation_derivative) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Matrix<double> activation_Jacobian(perceptrons_number, perceptrons_number, 0.0);
    activation_Jacobian.set_diagonal(activation_derivative);
    return activation_Jacobian;
}

/// Arranges a "Hessian form" vector of matrices from a vector of second derivatives.
/// @param activation_second_derivative Vector of activation function second derivatives.
Vector<Matrix<double>> PerceptronLayer::arrange_activations_Hessian_form(const Vector<double> &activation_second_derivative) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    Vector<Matrix<double>> activation_Hessian_form(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        activation_Hessian_form[i].set(perceptrons_number, perceptrons_number, 0.0);
        activation_Hessian_form[i](i, i) = activation_second_derivative[i];
    }
    return activation_Hessian_form;
}

/// Returns the outputs from every perceptron in a layer as a function of their inputs.
/// @param inputs Input vector to the layer.
Vector<double> PerceptronLayer::calculate_outputs(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_outputs(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs to layer.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_activations(calculate_combinations(inputs));
}

/// Returns the Jacobian matrix of a layer for a given inputs to that layer.
/// This is composed by the derivatives of the layer outputs with respect to their inputs.
/// The number of rows is the number of neurons in the layer.
/// The number of columns is the number of inputs to that layer.
/// @param inputs Input to layer.
Matrix<double> PerceptronLayer::calculate_Jacobian(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    const size_t inputs_size = inputs.size();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Matrix<double> calculate_Jacobian(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs to layer.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<double> combinations = calculate_combinations(inputs);
    const Vector<double> activations_derivatives = calculate_activations_derivatives(combinations);
    const Matrix<double> synaptic_weights = arrange_synaptic_weights();
    return activations_derivatives * synaptic_weights;
}

/// Returns the second partial derivatives of the outputs from a layer with respect to the inputs to that layer.
/// @param inputs Vector of inputs to that layer.
Vector<Matrix<double>> PerceptronLayer::calculate_Hessian_form(const Vector<double> &inputs) const
{
    const size_t perceptrons_number = get_perceptrons_number();
    const Matrix<double> synaptic_weights = arrange_synaptic_weights();
    const Vector<double> combination = calculate_combinations(inputs);
    const Vector<double> activations_second_derivatives = calculate_activations_second_derivatives(combination);
    Vector<Matrix<double>> activation_Hessian_form(perceptrons_number);
    Vector<Matrix<double>> Hessian_form(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        activation_Hessian_form[i].set(perceptrons_number, perceptrons_number, 0.0);
        activation_Hessian_form[i](i, i) = activations_second_derivatives[i];
        Hessian_form[i] = synaptic_weights.calculate_transpose()
                                          .dot(activation_Hessian_form[i])
                                          .dot(synaptic_weights);
    }
    return Hessian_form;
}

/// Returns which would be the outputs from a layer for a given inputs to that layer and a set of parameters in that layer.
/// @param inputs Vector of inputs to that layer.
/// @param parameters Vector of parameters in that layer.
Vector<double> PerceptronLayer::calculate_outputs(const Vector<double> &inputs,
                                                  const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();
    const size_t inputs_number = get_inputs_number();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_outputs(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of layer inputs (" << inputs_size << ") must be equal to number of layer inputs (" << inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t parameters_size = parameters.size();
    const size_t parameters_number = count_parameters_number();
    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector<double> calculate_outputs(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of parameters (" << parameters_size << ") must be equal to number of parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_activations(calculate_combinations(inputs, parameters));
}

/// Returns the parameters Jacobian for a given set of inputs.
/// This is composed by the derivatives of the layer outputs with respect to the layer parameters.
/// The number of rows is the number of neurons in the layer.
/// The number of columns is the number of parameters in that layer.
/// @param inputs Set of inputs to the layer.
/// @param parameters Set of layer parameters.
Matrix<double> PerceptronLayer::calculate_Jacobian(const Vector<double> &inputs,
                                                   const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    const size_t inputs_size = inputs.size();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Matrix<double> calculate_parameters_Jacobian(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<double> combinations = calculate_combinations(inputs, parameters);
    const Matrix<double> combinations_Jacobian = calculate_combinations_Jacobian(inputs, parameters);
    const Vector<double> activation_derivatives = calculate_activations_derivatives(combinations);
    const Matrix<double> activation_Jacobian = arrange_activations_Jacobian(activation_derivatives);
    return activation_Jacobian.dot(combinations_Jacobian);
}

/// Returns the second partial derivatives of the outputs from a layer with respect a given set of potential parameters for this layer,
/// and for a given set of inputs.
/// This quantity is the Hessian form of the layer outputs function, and it is represented as a vector of matrices.
/// @param inputs Set of layer inputs.
/// @param parameters Set of layer parameters.
Vector<Matrix<double>> PerceptronLayer::calculate_Hessian_form(const Vector<double> &inputs,
                                                               const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    const size_t inputs_size = inputs.size();
    if (inputs_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "Vector< Matrix<double> > calculate_Hessian_form(const Vector<double>&, const Vector<double>&) const method.\n"
               << "Size must be equal to number of inputs of layer.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t perceptrons_number = get_perceptrons_number();
    const Vector<double> combination = calculate_combinations(inputs);
    const Matrix<double> combination_parameters_Jacobian = calculate_combinations_Jacobian(inputs, parameters);
    const Vector<double> activation_second_derivatives = calculate_activations_second_derivatives(combination);
    const Vector<Matrix<double>> activation_Hessian_form = arrange_activations_Hessian_form(activation_second_derivatives);
    Vector<Matrix<double>> parameters_Hessian_form(perceptrons_number);
    for (size_t i = 0; i < perceptrons_number; i++) {
        parameters_Hessian_form[i] = combination_parameters_Jacobian.calculate_transpose()
                                                                    .dot(activation_Hessian_form[i])
                                                                    .dot(combination_parameters_Jacobian);
    }
    return parameters_Hessian_form;
}

/// Returns a string with the expression of the inputs-outputs relationship of the layer.
/// @param inputs_name Vector of strings with the name of the layer inputs.
/// @param outputs_name Vector of strings with the name of the layer outputs.
std::string PerceptronLayer::write_expression(const Vector<std::string> &inputs_name,
                                              const Vector<std::string> &outputs_name) const
{
    const size_t perceptrons_number = get_perceptrons_number();

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    const size_t inputs_name_size = inputs_name.size();
    if (inputs_name_size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "std::string write_expression(const Vector<std::string>&, const Vector<std::string>&) const method.\n"
               << "Size of inputs name must be equal to number of layer inputs.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t outputs_name_size = outputs_name.size();
    if (outputs_name_size != perceptrons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerceptronLayer class.\n"
               << "std::string write_expression(const Vector<std::string>&, const Vector<std::string>&) const method.\n"
               << "Size of outputs name must be equal to number of perceptrons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    std::ostringstream buffer;
    for (size_t i = 0; i < perceptrons_number; i++) {
        buffer << perceptrons[i].write_expression(inputs_name, outputs_name[i]);
    }
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
