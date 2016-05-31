/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P E R F O R M A N C E   T E R M   C L A S S                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "performance_term.h"


namespace OpenNN {

/// Default constructor.
/// It creates a default performance term object, with all pointers initialized to NULL.
/// It also initializes all the rest of class members to their default values.
PerformanceTerm::PerformanceTerm()
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Neural network constructor.
/// It creates a performance term object associated to a neural network object.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
PerformanceTerm::PerformanceTerm(NeuralNetwork *new_neural_network_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Data set constructor.
/// It creates a performance term object associated to a given data set object.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.
PerformanceTerm::PerformanceTerm(DataSet *new_data_set_pointer)
        : neural_network_pointer(NULL),
          data_set_pointer(new_data_set_pointer),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Mathematical model constructor.
/// It creates a performance term object associated to a given mathematical model object.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
PerformanceTerm::PerformanceTerm(MathematicalModel *new_mathematical_model_pointer)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(new_mathematical_model_pointer),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Neural network and data set constructor.
/// It creates a performance term object associated to a neural network and to be measured on a data set.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.
PerformanceTerm::PerformanceTerm(NeuralNetwork *new_neural_network_pointer, DataSet *new_data_set_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(new_data_set_pointer),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Neural network and mathematical model constructor.
/// It creates a performance term object associated to a neural network and to be measured on a mathematical model.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
PerformanceTerm::PerformanceTerm(NeuralNetwork *new_neural_network_pointer,
                                 MathematicalModel *new_mathematical_model_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(NULL),
          mathematical_model_pointer(new_mathematical_model_pointer),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// Neural network, mathematical model and data set constructor.
/// It creates a performance term object associated to a neural network and to be measured on both a mathematical model and a data set.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
/// @param new_data_set_pointer Pointer to a data set object.
PerformanceTerm::PerformanceTerm(NeuralNetwork *new_neural_network_pointer,
                                 MathematicalModel *new_mathematical_model_pointer,
                                 DataSet *new_data_set_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(new_data_set_pointer),
          mathematical_model_pointer(new_mathematical_model_pointer),
          numerical_differentiation_pointer(NULL)
{
    set_default();
}

/// XML constructor.
/// It creates a default performance term object, with all pointers initialized to NULL.
/// It also loads all the rest of class members from a XML document.
/// @param performance_term_document Pointer to a TinyXML document with the object data.
PerformanceTerm::PerformanceTerm(const tinyxml2::XMLDocument &performance_term_document)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    set_default();

    from_XML(performance_term_document);
}

/// Copy constructor.
/// It creates a copy of an existing performance term object.
/// @param other_performance_term Performance term object to be copied.
PerformanceTerm::PerformanceTerm(const PerformanceTerm &other_performance_term)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          numerical_differentiation_pointer(NULL)
{
    neural_network_pointer = other_performance_term.neural_network_pointer;
    data_set_pointer = other_performance_term.data_set_pointer;
    mathematical_model_pointer = other_performance_term.mathematical_model_pointer;
    if (other_performance_term.numerical_differentiation_pointer)
        numerical_differentiation_pointer = new NumericalDifferentiation(*other_performance_term.numerical_differentiation_pointer);
    display = other_performance_term.display;
}

/// Destructor.
/// It deletes the numerical differentiation object composing this performance term object.
PerformanceTerm::~PerformanceTerm()
{
    delete numerical_differentiation_pointer;
}

/// Assignment operator.
/// It assigns to this performance term object the members from another performance term object.
/// @param other_performance_term Performance term object to be copied.
PerformanceTerm &PerformanceTerm::operator=(const PerformanceTerm &other_performance_term)
{
    if (this != &other_performance_term) {
        neural_network_pointer = other_performance_term.neural_network_pointer;
        data_set_pointer = other_performance_term.data_set_pointer;
        mathematical_model_pointer = other_performance_term.mathematical_model_pointer;
        if (other_performance_term.numerical_differentiation_pointer == NULL) {
            delete numerical_differentiation_pointer;
            numerical_differentiation_pointer = NULL;
        } else
            numerical_differentiation_pointer = new NumericalDifferentiation(*other_performance_term.numerical_differentiation_pointer);
        display = other_performance_term.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object to another object.
/// The return is true if both objects have the same member data, and false otherwise.
bool PerformanceTerm::operator==(const PerformanceTerm &other_performance_term) const
{
    if (neural_network_pointer != other_performance_term.neural_network_pointer ||
        data_set_pointer != other_performance_term.data_set_pointer ||
        mathematical_model_pointer != other_performance_term.mathematical_model_pointer)
        return false;
    if (display != other_performance_term.display)
        return false;
    return true;
}

/// Returns true if messages from this class can be displayed on the screen, or false if messages
/// from this class can't be displayed on the screen.
const bool &PerformanceTerm::get_display() const
{
    return display;
}

/// Returns true if this performance term has a neural network associated,
/// and false otherwise.
bool PerformanceTerm::has_neural_network() const
{
    return neural_network_pointer;
}

/// Returns true if this performance term has a mathematical model associated,
/// and false otherwise.
bool PerformanceTerm::has_mathematical_model() const
{
    return mathematical_model_pointer;
}

/// Returns true if this performance term has a data set associated,
/// and false otherwise.
bool PerformanceTerm::has_data_set() const
{
    return data_set_pointer;
}

/// Returns true if this performance term object contains a numerical differentiation object,
/// and false otherwise.
bool PerformanceTerm::has_numerical_differentiation() const
{
    return numerical_differentiation_pointer;
}

/// Sets all the member pointers to NULL (neural network, data set, mathematical model and numerical differentiation).
/// It also initializes all the rest of class members to their default values.
void PerformanceTerm::set()
{
    neural_network_pointer = NULL;
    data_set_pointer = NULL;
    mathematical_model_pointer = NULL;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets all the member pointers to NULL, but the neural network, which set to a given pointer.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
void PerformanceTerm::set(NeuralNetwork *new_neural_network_pointer)
{
    neural_network_pointer = new_neural_network_pointer;
    data_set_pointer = NULL;
    mathematical_model_pointer = NULL;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets all the member pointers to NULL, but the data set, which set to a given pointer.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.
void PerformanceTerm::set(DataSet *new_data_set_pointer)
{
    neural_network_pointer = NULL;
    data_set_pointer = new_data_set_pointer;
    mathematical_model_pointer = NULL;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets all the member pointers to NULL, but the mathematical model, which set to a given pointer.
/// It also initializes all the rest of class members to their default values.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
void PerformanceTerm::set(MathematicalModel *new_mathematical_model_pointer)
{
    neural_network_pointer = NULL;
    data_set_pointer = NULL;
    mathematical_model_pointer = new_mathematical_model_pointer;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets new neural network and data set pointers.
/// It also sets the mathematical model and numerical differentiation pointers to NULL.
/// Finally, it initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.
void PerformanceTerm::set(NeuralNetwork *new_neural_network_pointer, DataSet *new_data_set_pointer)
{
    neural_network_pointer = new_neural_network_pointer;
    data_set_pointer = new_data_set_pointer;
    mathematical_model_pointer = NULL;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets new neural network and mathematical model pointers.
/// It also sets the data set and numerical differentiation pointers to NULL.
/// Finally, it initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a data set object.
void PerformanceTerm::set(NeuralNetwork *new_neural_network_pointer,
                          MathematicalModel *new_mathematical_model_pointer)
{
    neural_network_pointer = new_neural_network_pointer;
    data_set_pointer = NULL;
    mathematical_model_pointer = new_mathematical_model_pointer;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets new neural network, mathematical model and data set pointers.
/// The numerical differentiation pointer is set to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to mathematical model object.
/// @param new_data_set_pointer Pointer to a data set object.
void PerformanceTerm::set(NeuralNetwork *new_neural_network_pointer,
                          MathematicalModel *new_mathematical_model_pointer,
                          DataSet *new_data_set_pointer)
{
    neural_network_pointer = new_neural_network_pointer;
    data_set_pointer = new_data_set_pointer;
    mathematical_model_pointer = new_mathematical_model_pointer;
    numerical_differentiation_pointer = NULL;

    set_default();
}

/// Sets to this performance term object the members of another performance term object.
/// @param other_performance_term Performance term to be copied.
void PerformanceTerm::set(const PerformanceTerm &other_performance_term)
{
    neural_network_pointer = other_performance_term.neural_network_pointer;
    data_set_pointer = other_performance_term.data_set_pointer;
    mathematical_model_pointer = other_performance_term.mathematical_model_pointer;
    if (other_performance_term.numerical_differentiation_pointer)
        numerical_differentiation_pointer = new NumericalDifferentiation(*other_performance_term.numerical_differentiation_pointer);
    display = other_performance_term.display;
}

/// Sets a pointer to a neural network object which is to be associated to the performance term.
/// @param new_neural_network_pointer Pointer to a neural network object to be associated to the performance term.
void PerformanceTerm::set_neural_network_pointer(NeuralNetwork *new_neural_network_pointer)
{
    neural_network_pointer = new_neural_network_pointer;
}

/// Sets a new mathematical model on which the performance term is to be measured.
void PerformanceTerm::set_mathematical_model_pointer(MathematicalModel *new_mathematical_model_pointer)
{
    mathematical_model_pointer = new_mathematical_model_pointer;
}

/// Sets a new data set on which the performance term is to be measured.
void PerformanceTerm::set_data_set_pointer(DataSet *new_data_set_pointer)
{
    data_set_pointer = new_data_set_pointer;
}

/// Sets a new numerical differentiation pointer in this performance term object.
/// @param new_numerical_differentiation_pointer Pointer to a numerical differentiation object.
void PerformanceTerm::set_numerical_differentiation_pointer(NumericalDifferentiation *new_numerical_differentiation_pointer)
{
    numerical_differentiation_pointer = new_numerical_differentiation_pointer;
}

/// Sets the members of the performance term to their default values:
/// <ul>
/// <li> Display: true.
/// </ul>
void PerformanceTerm::set_default()
{
    display = true;
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void PerformanceTerm::set_display(const bool &new_display)
{
    display = new_display;
}

/// This method constructs the numerical differentiation object which composes the performance term class.
void PerformanceTerm::construct_numerical_differentiation()
{
    if (numerical_differentiation_pointer == NULL)
        numerical_differentiation_pointer = new NumericalDifferentiation();
}

/// This method deletes the numerical differentiation object which composes the performance term class.
void PerformanceTerm::delete_numerical_differentiation_pointer()
{
    delete numerical_differentiation_pointer;
    numerical_differentiation_pointer = NULL;
}

/// Checks that there is a neural network associated to the performance term.
/// If some of the above conditions is not hold, the method throws an exception.
void PerformanceTerm::check() const
{
    if (!neural_network_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "void check() const.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns the delta vector for all the layers in the multilayer perceptron
/// The format of this quantity is a vector of vectors.
/// @param layers_activation_derivative Forward propagation activation derivative.
/// @param output_gradient Gradient of the outputs objective function.
Vector<Vector<double>> PerformanceTerm::calculate_layers_delta(const Vector<Vector<double>> &layers_activation_derivative,
                                                               const Vector<double> &output_gradient) const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

#ifdef __OPENNN_DEBUG__
    if (!multilayer_perceptron_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_delta(const Vector< Vector<double> >&, const Vector<double>&) const method.\n"
               << "Pointer to multilayer perceptron in neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();
    const Vector<size_t> layers_perceptrons_number = multilayer_perceptron_pointer->arrange_layers_perceptrons_numbers();

#ifdef __OPENNN_DEBUG__
    const size_t layers_activation_derivative_size = layers_activation_derivative.size();

    if (layers_activation_derivative_size != layers_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_delta(const Vector< Vector<double> >&, const Vector<double>&) method.\n"
               << "Size of forward propagation activation derivative vector must be equal to number of layers.\n";

        throw std::logic_error(buffer.str());
    }

    if (layers_number > 0) {
        const size_t output_gradient_size = output_gradient.size();

        if (output_gradient_size != layers_perceptrons_number[layers_number - 1]) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceTerm class.\n"
                   << "Vector<double> calculate_layers_delta(const Vector< Vector<double> >&, const Vector<double>&) method.\n"
                   << "Size of outputs objective gradient (" << output_gradient_size << ") must be equal to "
                   << "number of outputs (" << layers_perceptrons_number[layers_number - 1] << ").\n";

            throw std::logic_error(buffer.str());
        }
    }
#endif

    // Neural network stuff
    Matrix<double> layer_synaptic_weights;

    // Performance functional stuff
    Vector<Vector<double>> layers_delta(layers_number);

    // Output layer
    if (layers_number > 0) {
        layers_delta[layers_number - 1] = layers_activation_derivative[layers_number - 1] * output_gradient;

        // Rest of hidden layers
        for (int i = (int) layers_number - 2; i >= 0; i--) {
            layer_synaptic_weights = neural_network_pointer->get_multilayer_perceptron_pointer()
                                                           ->get_layer(i + 1)
                                                           .arrange_synaptic_weights();
            layers_delta[i] = layers_activation_derivative[i] * (layers_delta[i + 1].dot(layer_synaptic_weights));
        }
    }

    return layers_delta;
}

/// Returns the delta vector for all the layers in the multilayer perceptron, when boundary conditions are imposed.
/// The format of this quantity is a vector of vectors.
/// @param layers_activation_derivative Forward propagation activation derivative.
/// @param homogeneous_solution Homogeneous solution for calculating the conditioned outputs.
/// @param output_gradient Gradient of the outputs objective function.
Vector<Vector<double>> PerformanceTerm::calculate_layers_delta(const Vector<Vector<double>> &layers_activation_derivative,
                                                               const Vector<double> &homogeneous_solution,
                                                               const Vector<double> &output_gradient) const
{
    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();
    const Vector<size_t> layers_perceptrons_number = multilayer_perceptron_pointer->arrange_layers_perceptrons_numbers();

#ifdef __OPENNN_DEBUG__
    const size_t layers_activation_derivative_size = layers_activation_derivative.size();

    if (layers_activation_derivative_size != layers_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_delta(const Vector< Vector<double> >&, const Vector<double>&) const method.\n"
               << "Size of forward propagation activation derivative vector must be equal to number of layers.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t objective_function_output_gradient_size = output_gradient.size();

    if (objective_function_output_gradient_size != layers_perceptrons_number[layers_number - 1]) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<double> calculate_layers_delta(const Vector< Vector<double> >&, const Vector<double>&) const method.\n"
               << "Size of objective function outputs derivative (" << objective_function_output_gradient_size << ")must be equal to "
               << "number of outputs (" << layers_perceptrons_number[layers_number - 1] << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<PerceptronLayer> &layers = multilayer_perceptron_pointer->get_layers();
    Matrix<double> synaptic_weights;

    // Set layers delta vector of vectors
    Vector<Vector<double>> layers_delta(layers_number);
    for (size_t i = 0; i < layers_number; i++) {
        layers_delta[i].set(layers_perceptrons_number[i]);
    }

    // Output layer
    layers_delta[layers_number - 1] = layers_activation_derivative[layers_number - 1] * homogeneous_solution * output_gradient;

    // Rest of hidden layers
    for (int h = (int) layers_number - 2; h >= 0; h--) {
        for (size_t i = 0; i < layers_perceptrons_number[h]; i++) {
            double sum = 0.0;
            for (size_t j = 0; j < layers_perceptrons_number[h + 1]; j++) {
                synaptic_weights = layers[h + 1].arrange_synaptic_weights();
                sum += synaptic_weights(i, j) * layers_delta[h + 1][j];
            }
            layers_delta[h][i] = layers_activation_derivative[h][i] * sum;
        }
    }

    return layers_delta;
}

/// Returns the gradient of the performance term function at some input point.
/// @param inputs Input vector.
/// @param layers_activation Activations of all layers in the multilayer perceptron
/// @param layers_delta Vector of vectors containing the partial derivatives of the outputs objective function with respect to all the combinations of all layers.
Vector<double> PerformanceTerm::calculate_point_gradient(const Vector<double> &inputs,
                                                         const Vector<Vector<double>> &layers_activation,
                                                         const Vector<Vector<double>> &layers_delta) const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

#ifdef __OPENNN_DEBUG__
    if (!mlp) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<double> calculate_point_gradient(const Vector<double>&, const Vector< Vector<double> >&, const Vector<double>&) const method.\n"
               << "Pointer to multilayer perceptron is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t inputs_number = mlp->get_inputs_number();
    const size_t layers_number = mlp->get_layers_number();
    const Vector<size_t> layers_perceptrons_number = mlp->arrange_layers_perceptrons_numbers();

#ifdef __OPENNN_DEBUG__
    const size_t inputs_size = inputs.size();

    if (inputs_size != inputs_number) {
        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_objective_gradient(const Vector< Vector<double> >&, const Vector<double>&, const Vector<double>&) method.\n"
               << "Size of inputs (" << inputs_size << ") must be equal to inputs number (" << inputs_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t layers_activation_size = layers_activation.size();

    if (layers_activation_size != layers_number) {
        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_objective_gradient(const Vector< Vector<double> >&, const Vector<double>&, const Vector<double>&) method.\n"
               << "Size of forward propagation activation (" << layers_activation_size << ") must be equal to number of layers (" << layers_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t layers_delta_size = layers_delta.size();

    if (layers_delta_size != layers_number) {
        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector< Vector<double> > calculate_layers_objective_gradient(const Vector< Vector<double> >&, const Vector<double>&) method.\n"
               << "Size of layers delta (" << layers_delta_size << ") must be equal to number of layers (" << layers_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<double> point_gradient(neural_network_pointer->count_parameters_number());
    size_t index = 0;
    const Vector<Vector<double>> layers_inputs = mlp->arrange_layers_input(inputs, layers_activation);
    const Vector<Matrix<double>> layers_combination_parameters_Jacobian = mlp->calculate_layers_combination_parameters_Jacobian(layers_inputs);

    for (size_t i = 0; i < layers_number; i++) {
        point_gradient.tuck_in(index, layers_delta[i].dot(layers_combination_parameters_Jacobian[i]));
        index += mlp->get_layer(i).count_parameters_number();
    }

    if (layers_number != 0) {
        Vector<double> synaptic_weights;
        size_t index = 0;

        // First layer
        for (size_t i = 0; i < layers_perceptrons_number[0]; i++) {
            // Bias
            point_gradient[index] = layers_delta[0][i];
            index++;

            // Synaptic weights
            synaptic_weights = mlp->get_layer(0).get_perceptron(i).arrange_synaptic_weights();
            for (size_t j = 0; j < inputs_number; j++) {
                point_gradient[index] = layers_delta[0][i] * inputs[j];
                index++;
            }
        }

        // Rest of layers
        for (size_t h = 1; h < layers_number; h++) {
            for (size_t i = 0; i < layers_perceptrons_number[h]; i++) {
                // Bias
                point_gradient[index] = layers_delta[h][i];
                index++;

                // Synaptic weights
                synaptic_weights = mlp->get_layer(h).get_perceptron(i).arrange_synaptic_weights();
                for (size_t j = 0; j < layers_perceptrons_number[h - 1]; j++) {
                    point_gradient[index] = layers_delta[h][i] * layers_activation[h - 1][j];
                    index++;
                }
            }
        }
    }

    return point_gradient;
}

/// Returns the gradient of the performance term function at some input point.
/// @param layers_combination_parameters_Jacobian
/// @param layers_delta
/// @todo
Vector<double> PerformanceTerm::calculate_point_gradient(const Vector<Matrix<double>> &layers_combination_parameters_Jacobian,
                                                         const Vector<Vector<double>> &layers_delta) const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

#ifdef __OPENNN_DEBUG__
    if (!mlp) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<double> calculate_point_gradient(const Vector<double>&, const Vector< Vector<double> >&, const Vector<double>&) const method.\n"
               << "Pointer to network is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t layers_number = mlp->get_layers_number();

#ifdef __OPENNN_DEBUG__
    const size_t layers_combination_parameters_Jacobian_size = layers_combination_parameters_Jacobian.size();

    if (layers_combination_parameters_Jacobian_size != layers_number) {
        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<Vector<double>> calculate_layers_objective_gradient(const Vector<Vector<double>>&, const Vector<double>&, const Vector<double>&) method.\n"
               << "Size of forward propagation activation (" << layers_combination_parameters_Jacobian_size << ") must be equal to number of layers (" << layers_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t layers_delta_size = layers_delta.size();

    if (layers_delta_size != layers_number) {
        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<Vector<double>> calculate_layers_objective_gradient(const Vector<Vector<double>>&, const Vector<double>&) method.\n"
               << "Size of layers delta (" << layers_delta_size << ") must be equal to number of layers (" << layers_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t parameters_number = mlp->count_parameters_number();
    Vector<double> point_gradient(parameters_number);
    size_t index = 0;

    for (size_t i = 0; i < layers_number; i++) {
        point_gradient.tuck_in(index, layers_delta[i].dot(layers_combination_parameters_Jacobian[i]));
        index += mlp->get_layer(i).count_parameters_number();
    }

    return point_gradient;
}

double PerformanceTerm::calculate_performance_output_combinations(const Vector<double> &combinations) const
{
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    Vector<double> targets(mlp->get_outputs_number(), 1.0);
    Vector<double> activations = mlp->get_layer(0).calculate_activations(combinations);

    return activations.calculate_sum_squared_error(targets);
}

Matrix<double> PerformanceTerm::calculate_output_interlayers_Delta(const Vector<double> &output_layer_activation_derivative,
                                                                   const Vector<double> &output_layer_activation_second_derivative,
                                                                   const Vector<double> &output_gradient,
                                                                   const Matrix<double> &output_Hessian) const
{
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t layers_number = mlp->get_layers_number();
    const Matrix<double> output_interlayers_Delta =
            output_Hessian *
            output_layer_activation_derivative[layers_number - 1] *
            output_layer_activation_derivative[layers_number - 1] +
            output_gradient *
            output_layer_activation_second_derivative[layers_number - 1];

    return output_interlayers_Delta;
}

Matrix<double> PerformanceTerm::calculate_interlayers_Delta(const size_t &index_1,
                                                            const size_t &index_2,
                                                            const Vector<double> &layer_1_activation_derivative,
                                                            const Vector<double> &layer_2_activation_derivative,
                                                            const Vector<double> &layer_1_activation_second_derivative,
                                                            const Vector<double> &layer_2_activation_second_derivative,
                                                            const Vector<Vector<double>> &layers_activation_derivative,
                                                            const Vector<double> &layers_delta,
                                                            const Matrix<double> &interlayers_combination_combination_Jacobian,
                                                            const Matrix<double> &previous_interlayers_Delta,
                                                            const Vector<Vector<double>> &complete_layers_delta) const
{
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t outputs_number = mlp->get_outputs_number();
    const size_t layers_number = mlp->get_layers_number();
    Matrix<double> layer_1_weights = mlp->get_layer(index_1).arrange_synaptic_weights();
    Matrix<double> layer_2_weights = mlp->get_layer(index_2).arrange_synaptic_weights();
    Matrix<double> output_layer_weights = mlp->get_layer(layers_number - 1).arrange_synaptic_weights();

    if (index_1 == 0 && index_2 == 0)
        layer_2_weights = mlp->get_layer(index_2 + 1).arrange_synaptic_weights();

    const size_t layer_1_perceptrons_number = mlp->get_layer(index_1).get_perceptrons_number();
    const size_t layer_2_perceptrons_number = mlp->get_layer(index_2).get_perceptrons_number();
    Matrix<double> interlayers_Delta(layer_1_perceptrons_number, layer_2_perceptrons_number, 0.0);

    for (size_t i = 0; i < layer_1_perceptrons_number; i++) {
        for (size_t j = 0; j < layer_2_perceptrons_number; j++) {
            if (index_2 == mlp->get_layers_number() - 1) {
                if (index_1 == 0 && index_2 == 2) {
                    interlayers_Delta(i, j) +=
                            previous_interlayers_Delta(0, 0) *
                            layers_activation_derivative[1][j] *
                            mlp->get_layer(index_2).arrange_synaptic_weights()(0, 0) *
                            mlp->get_layer(index_1 + 1).arrange_synaptic_weights()(0, 0) *
                            layer_1_activation_derivative[i] +
                            layer_1_activation_second_derivative[i] *
                            interlayers_combination_combination_Jacobian(0, 0) *
                            mlp->get_layer(index_1).arrange_synaptic_weights().arrange_column(j).dot(layers_delta);
                } else {
                    interlayers_Delta(i, j) =
                            layer_2_weights(j, i) *
                            layer_1_activation_derivative[i] *
                            previous_interlayers_Delta(j, j);
                }
            } else {
                if (index_1 == 0 && index_2 == 0) {
                    interlayers_Delta(i, j) +=
                            layer_2_weights(0, 0) *
                            layer_2_weights(0, 0) *
                            previous_interlayers_Delta(0, 0) +
                            layer_2_activation_second_derivative[j] *
                            calculate_Kronecker_delta(i, j) *
                            output_layer_weights.arrange_column(j).dot(layers_delta);
                } else if (index_1 == 0 && index_2 == 1) {
                    double interlayers_Delta02 =
                            previous_interlayers_Delta(0, 0) *
                            layers_activation_derivative[1][j] *
                            mlp->get_layer(2).arrange_synaptic_weights()(0, 0) *
                            mlp->get_layer(1).arrange_synaptic_weights()(0, 0) *
                            layers_activation_derivative[0][j] +
                            layer_1_activation_second_derivative[i] *
                            interlayers_combination_combination_Jacobian(0, 0) *
                            mlp->get_layer(0).arrange_synaptic_weights().arrange_column(j).dot(layers_delta);

                    // Previous interlayers Delta:   interlayers_Delta02
                    interlayers_Delta(i, j) +=
                            layers_activation_derivative[0][j] *
                            output_layer_weights(0, 0) *
                            interlayers_Delta02 +
                            layer_1_activation_second_derivative[i] *
                            interlayers_combination_combination_Jacobian(0, 0) *
                            mlp->get_layer(0).arrange_synaptic_weights().arrange_column(j).dot(complete_layers_delta[0]);
                } else {
                    if (index_1 == 1 && index_2 == 1) {
                        for (size_t k = 0; k < outputs_number; k++) {
                            interlayers_Delta(i, j) +=
                                    output_layer_weights(k, i) *
                                    output_layer_weights(k, j) *
                                    previous_interlayers_Delta(k, k);
                        }

                        interlayers_Delta(i, j) =
                                interlayers_Delta(i, j) *
                                layer_1_activation_derivative[i] *
                                layer_2_activation_derivative[j] +
                                layer_2_activation_second_derivative[j] *
                                calculate_Kronecker_delta(i, j) *
                                output_layer_weights.arrange_column(j).dot(layers_delta);
                    } else {
                        for (size_t k = 0; k < outputs_number; k++) {
                            interlayers_Delta(i, j) +=
                                    output_layer_weights(k, i) *
                                    output_layer_weights(k, j) *
                                    previous_interlayers_Delta(k, k);
                        }

                        interlayers_Delta(i, j) =
                                interlayers_Delta(i, j) *
                                layer_1_activation_derivative[i] *
                                layer_2_activation_derivative[j] +
                                layer_2_activation_second_derivative[j] *
                                calculate_Kronecker_delta(i, j) *
                                output_layer_weights.arrange_column(j).dot(layers_delta);
                    }
                }
            }
        }
    }

    return interlayers_Delta;
}

/// Returns the second partial derivatives of the outputs objective function with respect to the combinations of two layers.
/// That quantity is called interlayers Delta, and it is represented as a matrix of matrices.
/// @param layers_activation_derivative Activation derivatives of all layers in the multilayer perceptron
/// @param layers_activation_second_derivative Activation second derivatives of all layers in the multilayer perceptron
/// @param interlayers_combination_combination_Jacobian_form Matrix of matrices containing the partial derivatives of all layers combinations with respect to all layers combinations.
/// @param output_gradient Gradient vector of the outputs objective function.
/// @param output_Hessian Hessian matrix of the outputs objective function.
/// @param layers_delta Vector of vectors containing the partial derivatives of the outputs objective function with respect to the combinations of all layers.
/// @todo
Matrix<Matrix<double>> PerformanceTerm::calculate_interlayers_Delta(const Vector<Vector<double>> &layers_activation_derivative,
                                                                    const Vector<Vector<double>> &layers_activation_second_derivative,
                                                                    const Matrix<Matrix<double>> &interlayers_combination_combination_Jacobian_form,
                                                                    const Vector<double> &output_gradient,
                                                                    const Matrix<double> &output_Hessian,
                                                                    const Vector<Vector<double>> &layers_delta) const
{
#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

#ifdef __OPENNN_DEBUG__
    if (!mlp) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Matrix< Matrix<double> > calculate_interlayers_Delta() method.\n"
               << "Multilayer perceptron pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t layers_number = mlp->get_layers_number();
    const Vector<size_t> layers_size = mlp->arrange_layers_perceptrons_numbers();

#ifdef __OPENNN_DEBUG__
    if (layers_number != 0) {
        const size_t output_gradient_size = output_gradient.size();

        if (output_gradient_size != layers_size[layers_number - 1]) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceTerm class.\n"
                   << "Vector<double> calculate_interlayers_Delta() method.\n"
                   << "Size of layer " << layers_number - 1 << " must be equal to size of output objective gradient (" << output_gradient_size << ")."
                   << std::endl;

            throw std::logic_error(buffer.str());
        }

        const size_t output_Hessian_rows_number = output_Hessian.get_rows_number();
        const size_t output_Hessian_columns_number = output_Hessian.get_columns_number();

        if (output_Hessian_rows_number != layers_size[layers_number - 1]) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceTerm class.\n"
                   << "Vector<double> calculate_interlayers_Delta() method.\n"
                   << "Size of layer " << layers_number - 1 << " must be equal to number of rows in output objective Hessian (" << output_Hessian_rows_number << ")."
                   << std::endl;

            throw std::logic_error(buffer.str());
        }

        if (output_Hessian_columns_number != layers_size[layers_number - 1]) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceTerm class.\n"
                   << "Vector<double> calculate_interlayers_Delta() method.\n"
                   << "Size of layer " << layers_number - 1 << ") must be equal to number of columns in output objective Hessian (" << output_Hessian_columns_number << ")."
                   << std::endl;

            throw std::logic_error(buffer.str());
        }
    }
#endif

    const Vector<Matrix<double>> layers_synaptic_weights = mlp->arrange_layers_synaptic_weights();

    // Objective functional stuff
    Matrix<Matrix<double>> interlayers_Delta(layers_number, layers_number);
    Matrix<double> previous_interlayers_Delta;

    for (size_t i = 0; i < layers_number; i++) {
        for (size_t j = 0; j < layers_number; j++) {
            interlayers_Delta(i, j).set(layers_size[i], layers_size[j], 0.0);
        }
    }

    if (layers_number == 0)
        return interlayers_Delta;

    Matrix<double> output_interlayers_Delta = calculate_output_interlayers_Delta(layers_activation_derivative[layers_number - 1],
                                                                                 layers_activation_second_derivative[layers_number - 1],
                                                                                 output_gradient,
                                                                                 output_Hessian);
    interlayers_Delta(layers_number - 1, layers_number - 1) = output_interlayers_Delta;

    for (int i = (int) layers_number - 1; i >= 0; i--) {
        for (int j = (int) layers_number - 1; j >= i; j--) {
            if (i == (int) layers_number - 1 && j == (int) layers_number - 1) { // Output-outputs layer
                interlayers_Delta(i, j) =
                        calculate_output_interlayers_Delta(layers_activation_derivative[layers_number - 1],
                                                           layers_activation_second_derivative[layers_number - 1],
                                                           output_gradient,
                                                           output_Hessian);
                previous_interlayers_Delta = interlayers_Delta(i, j);
            } else {
                interlayers_Delta(i, j) =
                        calculate_interlayers_Delta(i, j,
                                                    layers_activation_derivative[i],
                                                    layers_activation_derivative[j],
                                                    layers_activation_second_derivative[i],
                                                    layers_activation_second_derivative[j],
                                                    layers_activation_derivative,
                                                    layers_delta[i + 1],
                                                    interlayers_combination_combination_Jacobian_form(i, j),
                                                    interlayers_Delta(2, 2),
                                                    layers_delta);
            }
        }
    }

    return interlayers_Delta;
}

/// Returns the Hessian of the performance term at some input.
/// @param layers_activation_derivative
/// @param perceptrons_combination_parameters_gradient
/// @param interlayers_combination_combination_Jacobian
/// @param layers_delta
/// @param interlayers_Delta
/// @todo
Matrix<double> PerformanceTerm::calculate_point_Hessian(const Vector<Vector<double>> &layers_activation_derivative,
                                                        const Vector<Vector<Vector<double>>> &perceptrons_combination_parameters_gradient,
                                                        const Matrix<Matrix<double>> &interlayers_combination_combination_Jacobian,
                                                        const Vector<Vector<double>> &layers_delta,
                                                        const Matrix<Matrix<double>> &interlayers_Delta) const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

#ifdef __OPENNN_DEBUG__
    if (!mlp) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Matrix<double> calculate_point_Hessian(const Vector<double>&, const Matrix< Matrix<double> >&, const Vector< Vector<double> >&, const Matrix< Matrix<double> >&) const method.\n"
               << "Multilayer perceptron pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t layers_number = mlp->get_layers_number();
    const size_t parameters_number = mlp->count_parameters_number();

#ifdef __OPENNN_DEBUG__
    const size_t layers_activation_derivative_size = layers_activation_derivative.size();

    if (layers_activation_derivative_size != layers_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Matrix<double> calculate_point_Hessian(const Vector<double>&, const Matrix< Matrix<double> >&, const Vector< Vector<double> >&, const Matrix< Matrix<double> >&) const method.\n"
               << "Size of layers activation derivative must be equal to number of layers in multilayer perceptron.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    // Objective functional
    Matrix<double> point_Hessian(parameters_number, parameters_number, 0.0);
    Vector<size_t> parameter_indices(3);
    size_t layer_index_i;
    size_t neuron_index_i;
    size_t parameter_index_i;
    size_t layer_index_j;
    size_t neuron_index_j;
    size_t parameter_index_j;
    const size_t last_layer_parameters_number = mlp->get_layer(layers_number - 1).count_parameters_number();

    // @todo
    std::cout << "Interlayers Delta: \n" << interlayers_Delta << std::endl;
    std::cout << "Layers delta: \n" << layers_delta << std::endl;

    if (layers_number > 0) {
        // Last layer
        std::cout << "---Last layer---" << std::endl;
        for (size_t i = parameters_number - last_layer_parameters_number; i < parameters_number; i++) {
            parameter_indices = mlp->arrange_parameter_indices(i);
            layer_index_i = parameter_indices[0];
            neuron_index_i = parameter_indices[1];
            parameter_index_i = parameter_indices[2];

            for (size_t j = parameters_number - last_layer_parameters_number; j < parameters_number; j++) {
                parameter_indices = mlp->arrange_parameter_indices(j);
                layer_index_j = parameter_indices[0];
                neuron_index_j = parameter_indices[1];
                parameter_index_j = parameter_indices[2];
                point_Hessian(i, j) =
                        perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                        perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                        calculate_Kronecker_delta(neuron_index_i, neuron_index_j) *
                        interlayers_Delta(layer_index_i, layer_index_j)(neuron_index_j, neuron_index_i);
            }
        }

        // First layer
        std::cout << "---First layer---" << std::endl;
        for (size_t i = 0; i < parameters_number - last_layer_parameters_number; i++) {
            parameter_indices = mlp->arrange_parameter_indices(i);
            layer_index_i = parameter_indices[0];
            neuron_index_i = parameter_indices[1];
            parameter_index_i = parameter_indices[2];

            for (size_t j = 0; j < parameters_number - last_layer_parameters_number; j++) {
                parameter_indices = mlp->arrange_parameter_indices(j);
                layer_index_j = parameter_indices[0];
                neuron_index_j = parameter_indices[1];
                parameter_index_j = parameter_indices[2];
                point_Hessian(i, j) =
                        perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                        perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                        interlayers_Delta(layer_index_i, layer_index_j)(neuron_index_i, neuron_index_j) +
                        perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                        layers_activation_derivative[layer_index_i][neuron_index_i] *
                        layers_delta[layer_index_j][neuron_index_j] *
                        calculate_Kronecker_delta(parameter_index_j, neuron_index_i + 1);
            }
        }

        // Rest of the layers
        std::cout << "---Rest of the layers---" << std::endl;
        for (size_t i = 0; i < parameters_number - last_layer_parameters_number; i++) {
            parameter_indices = mlp->arrange_parameter_indices(i);
            layer_index_i = parameter_indices[0];
            neuron_index_i = parameter_indices[1];
            parameter_index_i = parameter_indices[2];

            for (size_t j = parameters_number - last_layer_parameters_number; j < parameters_number; j++) {
                parameter_indices = mlp->arrange_parameter_indices(j);
                layer_index_j = parameter_indices[0];
                neuron_index_j = parameter_indices[1];
                parameter_index_j = parameter_indices[2];

                point_Hessian(i, j) =
                        perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                        perceptrons_combination_parameters_gradient[layer_index_j][neuron_index_j][parameter_index_j] *
                        interlayers_Delta(layer_index_i, layer_index_j)(neuron_index_i, neuron_index_j) +
                        perceptrons_combination_parameters_gradient[layer_index_i][neuron_index_i][parameter_index_i] *
                        layers_activation_derivative[layer_index_i][neuron_index_i] *
                        layers_delta[layer_index_j][neuron_index_j] *
                        calculate_Kronecker_delta(parameter_index_j, neuron_index_i + 1) *
                        interlayers_combination_combination_Jacobian(layer_index_j - 1, layer_index_i)(neuron_index_j, neuron_index_i);
            }
        }
    }

    for (size_t i = 0; i < parameters_number; i++) {
        for (size_t j = 0; j < i; j++) {
            point_Hessian(i, j) = point_Hessian(j, i);
        }
    }

    return point_Hessian;
}

/// Returns the Hessian of the performance term at some input for only one hidden layer.
/// @param layers_activation_derivative
/// @param perceptrons_combination_parameters_gradient
/// @param interlayers_combination_combination_Jacobian
/// @param layers_delta
/// @param interlayers_Delta
/// @todo
Matrix<double> PerformanceTerm::calculate_single_hidden_layer_point_Hessian(const Vector<Vector<double>> &layers_activation_derivative,
                                                                            const Vector<Vector<double>> &layers_activation_second_derivative,
                                                                            const Vector<Vector<Vector<double>>> &perceptrons_combination_parameters_gradient,
                                                                            const Vector<Vector<double>> &layers_delta,
                                                                            const Matrix<double> &output_interlayers_Delta) const
{
    const MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();
    const size_t outputs_number = mlp->get_outputs_number();
    const size_t parameters_number = mlp->count_parameters_number();
    const size_t first_layer_parameters_number = mlp->get_layer(0).arrange_parameters().size();
    const size_t second_layer_parameters_number = mlp->get_layer(1).arrange_parameters().size();
    Matrix<double> single_hidden_layer_point_Hessian(parameters_number, parameters_number, 0.0);
    Vector<size_t> parameter_indices(3);

    size_t layer_index_i;
    size_t neuron_index_i;
    size_t parameter_index_i;
    size_t layer_index_j;
    size_t neuron_index_j;
    size_t parameter_index_j;

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
            single_hidden_layer_point_Hessian(i, j) =
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
            single_hidden_layer_point_Hessian(i, j) =
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

            single_hidden_layer_point_Hessian(i, j) =
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
            single_hidden_layer_point_Hessian(j, i) = single_hidden_layer_point_Hessian(i, j);
        }
    }

    return single_hidden_layer_point_Hessian;
}

/// Returns the default gradient vector of the performance term.
/// It uses numerical differentiation.
Vector<double> PerformanceTerm::calculate_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check();

    if (!numerical_differentiation_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<double> calculate_gradient() const method.\n"
               << "Numerical differentiation pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<double> parameters = neural_network_pointer->arrange_parameters();
    return numerical_differentiation_pointer->calculate_gradient(*this,
                                                                 &PerformanceTerm::calculate_performance,
                                                                 parameters);
}

/// Returns the default gradient vector of the performance term.
/// It uses numerical differentiation.
Vector<double> PerformanceTerm::calculate_gradient(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check();

    if (!numerical_differentiation_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceTerm class.\n"
               << "Vector<double> calculate_gradient(const Vector<double>&) const method.\n"
               << "Numerical differentiation pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return numerical_differentiation_pointer->calculate_gradient(*this,
                                                                 &PerformanceTerm::calculate_performance,
                                                                 parameters);
}

/// @todo
Matrix<double> PerformanceTerm::calculate_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    const Vector<double> parameters = neural_network_pointer->arrange_parameters();
    return numerical_differentiation_pointer->calculate_Hessian(*this,
                                                                &PerformanceTerm::calculate_performance,
                                                                parameters);
}

/// @todo
Matrix<double> PerformanceTerm::calculate_Hessian(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check();
#endif

    return numerical_differentiation_pointer->calculate_Hessian(*this,
                                                                &PerformanceTerm::calculate_performance,
                                                                parameters);
}

/// Returns the performance of all the subterms composing the performance term.
Vector<double> PerformanceTerm::calculate_terms() const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: PerformanceTerm class.\n"
           << "Vector<double> calculate_terms() const method.\n"
           << "The terms function is not defined for this performance term.\n";

    throw std::logic_error(buffer.str());
}

/// Returns the performance of all the subterms composing the performance term.
Vector<double> PerformanceTerm::calculate_terms(const Vector<double> &) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: PerformanceTerm class.\n"
           << "Vector<double> calculate_terms(const Vector<double>&) const method.\n"
           << "The terms function is not defined for this performance term.\n";

    throw std::logic_error(buffer.str());
}

/// Returns the Jacobian matrix of the subterms composing the performance term.
Matrix<double> PerformanceTerm::calculate_terms_Jacobian() const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: PerformanceTerm class.\n"
           << "Matrix<double> calculate_terms_Jacobian() const method.\n"
           << "The terms function is not defined for this performance term.\n";

    throw std::logic_error(buffer.str());
}

/// Returns the performance of all the subterms composing the performance term.
PerformanceTerm::FirstOrderTerms PerformanceTerm::calculate_first_order_terms() const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: PerformanceTerm class.\n"
           << "Vector<double> calculate_terms() const method.\n"
           << "The terms function is not defined for this performance term.\n";

    throw std::logic_error(buffer.str());
}

/// Returns a string with the default type of performance term, "USER_PERFORMANCE_TERM".
std::string PerformanceTerm::write_performance_term_type() const
{
    return "USER_PERFORMANCE_TERM";
}

/// Returns a string with the default information of the performance term.
/// It will be used by the training strategy to monitor the training process.
/// By default this information is empty.
std::string PerformanceTerm::write_information() const
{
    return "";
}

/// Returns the default string representation of a performance term.
std::string PerformanceTerm::to_string() const
{
    std::ostringstream buffer;
    buffer << "Performance term\n";
    return buffer.str();
}

/// Serializes a default performance term object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
tinyxml2::XMLDocument *PerformanceTerm::to_XML() const
{
    std::ostringstream buffer;
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;

    // Performance term
    tinyxml2::XMLElement *root_element = document->NewElement("PerformanceTerm");
    document->InsertFirstChild(root_element);

    return document;
}

/// Loads a default performance term from a XML document.
/// @param document TinyXML document containing the performance term members.
void PerformanceTerm::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *display_element = document.FirstChildElement("Display");
    if (display_element) {
        std::string new_display_string = display_element->GetText();
        try {
            set_display(new_display_string != "0");
        }
        catch (const std::logic_error &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

/// Returns the Knronecker delta of two integers a and b, which equals 1 if they are equal and 0 otherwise.
/// @param a First integer.
/// @param b Second integer.
size_t PerformanceTerm::calculate_Kronecker_delta(const size_t &a, const size_t &b) const
{
    return a == b? 1: 0;
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
