/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   S C A L I N G   L A Y E R   C L A S S                                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "scaling_layer.h"


namespace OpenNN {

/// Default constructor.
/// It creates a scaling layer object with no scaling neurons.
ScalingLayer::ScalingLayer()
{
    set();
}

/// Scaling neurons number constructor.
/// This constructor creates a scaling layer with a given size.
/// The members of this object are initialized with the default values.
/// @param new_scaling_neurons_number Number of scaling neurons in the layer.
ScalingLayer::ScalingLayer(const size_t &new_scaling_neurons_number)
{
    set(new_scaling_neurons_number);
}

/// Statistics constructor.
/// This constructor creates a scaling layer with given minimums, maximums, means and standard deviations.
/// The rest of members of this object are initialized with the default values.
/// @param new_statistics Vector of vectors with the variables statistics.
ScalingLayer::ScalingLayer(const Vector<Statistics<double>> &new_statistics)
{
    set(new_statistics);
}

/// Copy constructor.
ScalingLayer::ScalingLayer(const ScalingLayer &new_scaling_layer)
{
    set(new_scaling_layer);
}

/// Destructor.
ScalingLayer::~ScalingLayer()
{
}

/// Assignment operator.
/// @param other_scaling_layer Object to be copied.
ScalingLayer &ScalingLayer::operator=(const ScalingLayer &other_scaling_layer)
{
    if (this != &other_scaling_layer) {
        statistics = other_scaling_layer.statistics;
        scaling_method = other_scaling_layer.scaling_method;
        display = other_scaling_layer.display;
    }
    return *this;
}

/// Equal to operator.
/// If compares this object with another object of the same class, and returns true if they are equal, and false otherwise.
/// @param other_scaling_layer Object to be compared with.
bool ScalingLayer::operator==(const ScalingLayer &other_scaling_layer) const
{
    return /*statistics == other_scaling_layer.statistics &&*/
            scaling_method == other_scaling_layer.scaling_method &&
            display == other_scaling_layer.display;
}

/// Returns the number of unscaling neurons in this layer.
size_t ScalingLayer::get_scaling_neurons_number() const
{
    return statistics.size();
}

/// Returns all the scaling layer statistics.
/// The format is a vector of statistics structures of size the number of scaling neurons.
Vector<Statistics<double>> ScalingLayer::get_statistics() const
{
    return statistics;
}

/// Returns the statistics structure of a single scaling neuron.
/// @param index Neuron index.
Statistics<double> ScalingLayer::get_statistics(const size_t &index) const
{
    return statistics[index];
}

/// Returns a single matrix with the statistics of all scaling neurons.
/// The number of rows is the number of scaling neurons.
/// The number of columns is four (minimum, maximum, mean and standard deviation).
Matrix<double> ScalingLayer::arrange_statistics() const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Matrix<double> statistics_matrix(scaling_neurons_number, 4);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        statistics_matrix.set_row(i, statistics[i].to_vector());
    }
    return statistics_matrix;
}

/// Returns a single matrix with the means of all scaling neurons.
Vector<double> ScalingLayer::arrange_means() const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> means(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        means[i] = statistics[i].mean;
    }
    return means;
}

/// Returns a single matrix with the standard deviations of all scaling neurons.
Vector<double> ScalingLayer::arrange_standard_deviations() const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> standard_deviations(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        standard_deviations[i] = statistics[i].standard_deviation;
    }
    return standard_deviations;
}

/// Returns the method used for scaling.
const ScalingLayer::ScalingMethod &ScalingLayer::get_scaling_method() const
{
    return scaling_method;
}

/// Returns a string with the name of the method used for scaling.
std::string ScalingLayer::write_scaling_method() const
{
    if (scaling_method == MeanStandardDeviation)
        return "MeanStandardDeviation";
    else if (scaling_method == MinimumMaximum)
        return "MinimumMaximum";
    else if (scaling_method == NoScaling)
        return "NoScaling";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "std::string write_scaling_method() const method.\n"
               << "Unknown scaling method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string with the name of the method used for scaling,
/// as paragaph text.
std::string ScalingLayer::write_scaling_method_text() const
{
    if (scaling_method == NoScaling)
        return "no scaling";
    else if (scaling_method == MeanStandardDeviation)
        return "mean and standard deviation";
    else if (scaling_method == MinimumMaximum)
        return "minimum and maximum";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "std::string write_scaling_method_text() const method.\n"
               << "Unknown scaling method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.
const bool &ScalingLayer::get_display() const
{
    return display;
}

/// Sets the scaling layer to be empty.
void ScalingLayer::set()
{
    statistics.set();

    set_default();
}

/// Sets a new size in the scaling layer.
/// It also sets the members to their default values.
void ScalingLayer::set(const size_t &new_inputs_number)
{
    statistics.set(new_inputs_number);

    set_default();
}

/// Sets the size of the scaling layer and the statistics values.
/// @param new_statistics Vector of vectors containing the minimums, maximums, means and standard deviations for the scaling layer.
/// The size of this vector must be 4.
/// The size of each subvector will be the size of the scaling layer.
void ScalingLayer::set(const Vector<Statistics<double>> &new_statistics)
{
    statistics = new_statistics;

    set_default();
}

/// Sets the scaling layer members from a XML document.
/// @param new_scaling_layer_document Pointer to a TinyXML document containing the member data.
void ScalingLayer::set(const tinyxml2::XMLDocument &new_scaling_layer_document)
{
    set_default();

    from_XML(new_scaling_layer_document);
}

/// Sets the members of this object to be the members of another object of the same class.
/// @param new_scaling_layer Object to be copied.
void ScalingLayer::set(const ScalingLayer &new_scaling_layer)
{
    statistics = new_scaling_layer.statistics;
    scaling_method = new_scaling_layer.scaling_method;
    display = new_scaling_layer.display;
}

/// Sets the members to their default value:
/// <ul>
/// <li> Minimus: -1 for all unscaling neurons.
/// <li> Maximums: 1 for al unscaling neurons.
/// <li> Means: 0 for all unscaling neurons.
/// <li> Standard deviations 1 for all unscaling neurons.
/// <li> Scaling method: Minimum and maximum.
/// <li> Display: True.
/// </ul>
void ScalingLayer::set_default()
{
    // minimums.initialize(-1.0);
    // maximums.initialize(1.0);
    // means.initialize(0.0);
    // standard_deviations.initialize(1.0);
    set_scaling_method(MinimumMaximum);
    set_display(true);
}

/// Sets all the scaling layer statistics from a vector statistics structures.
/// The size of the vector must be equal to the number of scaling neurons in the layer.
/// @param new_statistics Scaling layer statistics.
void ScalingLayer::set_statistics(const Vector<Statistics<double>> &new_statistics)
{

#ifdef __OPENNN_DEBUG__
    const size_t new_statistics_size = new_statistics.size();
    const size_t scaling_neurons_number = get_scaling_neurons_number();

    if (new_statistics_size != scaling_neurons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void set_statistics(const Vector< Statistics<double> >&) method.\n"
               << "Size of statistics is not equal to number of scaling neurons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    statistics = new_statistics;
}

/// Sets the statistics of a single scaling neuron.
/// @param i Index of neuron.
/// @param item_statistics Statistics structure for that neuron.
void ScalingLayer::set_item_statistics(const size_t &i, const Statistics<double> &item_statistics)
{
    statistics[i] = item_statistics;
}

/// Sets the minimum value of a given scaling neuron.
/// @param i Index of scaling neuron.
/// @param new_minimum Minimum value.
void ScalingLayer::set_minimum(const size_t &i, const double &new_minimum)
{
    statistics[i].set_minimum(new_minimum);
}

/// Sets the maximum value of a given scaling neuron.
/// @param i Index of scaling neuron.
/// @param new_maximum Maximum value.
void ScalingLayer::set_maximum(const size_t &i, const double &new_maximum)
{
    statistics[i].set_maximum(new_maximum);
}

/// Sets the mean value of a given scaling neuron.
/// @param i Index of scaling neuron.
/// @param new_mean Mean value.
void ScalingLayer::set_mean(const size_t &i, const double &new_mean)
{
    statistics[i].set_mean(new_mean);
}

/// Sets the standard deviation value of a given scaling neuron.
/// @param i Index of scaling neuron.
/// @param new_standard_deviation Standard deviation value.
void ScalingLayer::set_standard_deviation(const size_t &i, const double &new_standard_deviation)
{
    statistics[i].set_standard_deviation(new_standard_deviation);
}

/// Sets the method to be used for scaling the variables.
/// @param new_scaling_method New scaling method for the variables.
void ScalingLayer::set_scaling_method(const ScalingLayer::ScalingMethod &new_scaling_method)
{
    scaling_method = new_scaling_method;
}

/// Sets the method to be used for scaling the variables.
/// The argument is a string containing the name of the method ("NoScaling", "MeanStandardDeviation" or "MinimumMaximum").
/// @param new_scaling_method New scaling method in the layer.
void ScalingLayer::set_scaling_method(const std::string &new_scaling_method)
{
    if (new_scaling_method == "NoScaling")
        set_scaling_method(NoScaling);
    else if (new_scaling_method == "MeanStandardDeviation")
        set_scaling_method(MeanStandardDeviation);
    else if (new_scaling_method == "MinimumMaximum")
        set_scaling_method(MinimumMaximum);
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void set_scaling_method(const std::string&) method.\n"
               << "Unknown scaling method: " << new_scaling_method << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void ScalingLayer::set_display(const bool &new_display)
{
    display = new_display;
}

/// Add a scaling neuron from the scaling layer and asociate new statistics.
/// @param new_statistics Value of the statistics of the new neuron added. The default value is an empty vector.
void ScalingLayer::grow_scaling_neuron(const Statistics<double> &new_statistics)
{
    statistics.push_back(new_statistics);
}

/// Removes a given scaling neuron from the scaling layer.
/// @param index Index of neuron to be removed.
void ScalingLayer::prune_scaling_neuron(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t scaling_neurons_number = get_scaling_neurons_number();

    if (index >= scaling_neurons_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void prune_scaling_neuron(const size_t&) method.\n"
               << "Index of scaling neuron is equal or greater than number of scaling neurons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    statistics.erase(statistics.begin() + index);
}

/// Returns true if the number of scaling neurons is zero, and false otherwise.
bool ScalingLayer::is_empty() const
{
    return get_scaling_neurons_number() == 0;
}

/// This method chechs whether the inputs to the scaling layer have the right size.
/// If not, it displays an error message and exits the program.
/// It also checks whether the input values are inside the range defined by the minimums and maximum values, and
/// displays a warning message if they are outside.
/// @param inputs Set of inputs to the scaling layer.
void ScalingLayer::check_range(const Vector<double> &inputs) const
{
    const size_t inputs_number = get_scaling_neurons_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = inputs.size();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void check_range(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    // Check inputs
    if (display) {
        for (size_t i = 0; i < inputs_number; i++) {
            if (inputs[i] < statistics[i].minimum) {
                std::cout << "OpenNN Warning: ScalingLayer class.\n"
                          << "void check_range(const Vector<double>&) const method.\n"
                          << "Input value " << i << " is less than corresponding minimum.\n";
            }

            if (inputs[i] > statistics[i].maximum) {
                std::cout << "OpenNN Warning: ScalingLayer class.\n"
                          << "void check_range(const Vector<double>&) const method.\n"
                          << "Input value " << i << " is greater than corresponding maximum.\n";
            }
        }
    }
}

/// Initializes at random the statistics of all neurons in the layer
/// and the unscaling method.
void ScalingLayer::initialize_random()
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();

    // Statistics
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        statistics[i].initialize_random();
    }

    // Unscaling method
    switch (rand() % 2) {
    case 0:
        scaling_method = MinimumMaximum;
        break;

    case 1:
        scaling_method = MeanStandardDeviation;
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void initialize_random() method.\n"
                   << "Unknown scaling method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Scales some values to produce some scaled values.
/// @param inputs Set of inputs to the scaling layer.
Vector<double> ScalingLayer::calculate_outputs(const Vector<double> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_scaling_neurons_number();
    const size_t size = inputs.size();

    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "Vector<double> calculate_outputs(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to number of scaling neurons.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    switch (scaling_method) {
    case MinimumMaximum:
        return calculate_minimum_maximum_outputs(inputs);

    case MeanStandardDeviation:
        return calculate_mean_standard_deviation_outputs(inputs);

    case NoScaling:
        return inputs;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class\n"
                   << "Vector<double> calculate_outputs(const Vector<double>&) const method.\n"
                   << "Unknown scaling and unscaling method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// This method retuns the derivatives of the scaled inputs with respect to the raw inputs.
/// That derivatives depend on the inputs scaling method to be used.
Vector<double> ScalingLayer::calculate_derivatives(const Vector<double> &dummy) const
{
    switch (scaling_method) {
    case MinimumMaximum:
        return calculate_minimum_maximum_derivatives(dummy);

    case MeanStandardDeviation:
        return calculate_mean_standard_deviation_derivatives(dummy);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "Vector<double> calculate_derivatives(const Vector<double>&) const method.\n"
                   << "Unknown scaling and unscaling method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// This method retuns the second derivatives of the scaled inputs with respect to the raw inputs.
/// That second derivatives depend on the inputs scaling method to be used.
Vector<double> ScalingLayer::calculate_second_derivatives(const Vector<double> &dummy) const
{
    switch (scaling_method) {
    case MinimumMaximum:
        return calculate_minimum_maximum_second_derivatives(dummy);

    case MeanStandardDeviation:
        return calculate_mean_standard_deviation_second_derivatives(dummy);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "Vector<double> calculate_second_derivatives(const Vector<double>&) const method.\n"
                   << "Unknown scaling and unscaling method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Calculates the outputs from the scaling layer with the minimum and maximum method for a set of inputs.
/// @param inputs Vector of input values to the scaling layer. The size must be equal to the number of scaling neurons.
Vector<double> ScalingLayer::calculate_minimum_maximum_outputs(const Vector<double> &inputs) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> outputs(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        if (statistics[i].maximum - statistics[i].minimum < 1e-99) {
            if (display) {
                std::cout << "OpenNN Warning: ScalingLayer class\n"
                          << "Vector<double> calculate_minimum_maximum_outputs(Vector<double>&) const method.\n"
                          << "Minimum and maximum values of variable " << i << " are equal.\n"
                          << "Those inputs won't be scaled.\n";
            }
            outputs[i] = inputs[i];
        } else
            outputs[i] = 2.0 * (inputs[i] - statistics[i].minimum) / (statistics[i].maximum - statistics[i].minimum) - 1.0;
    }
    return outputs;
}

/// Calculates the derivatives of the outputs from the scaling layer with the minimum and maximum method.
/// As the minimum and maximum method is a linear method, the derivatives will not depend on the inputs.
Vector<double> ScalingLayer::calculate_minimum_maximum_derivatives(const Vector<double> &) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> scaled_derivative(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        if (statistics[i].maximum - statistics[i].minimum < 1e-99) {
            if (display) {
                std::cout << "OpenNN Warning: ScalingLayer class.\n"
                          << "Vector<double> calculate_minimum_maximum_derivatives(const Vector<double>&) const method.\n"
                          << "Minimum and maximum values of variable " << i << " are equal.\n"
                          << "That inputs is not scaled.\n";
            }
            scaled_derivative[i] = 1.0;
        } else
            scaled_derivative[i] = 2.0 / (statistics[i].maximum - statistics[i].minimum);
    }
    return scaled_derivative;
}

/// Calculates the second derivatives of the outputs from the scaling layer with the minimum and maximum method.
/// As the minimum and maximum method is a linear method, the second derivatives will be always zero.
Vector<double> ScalingLayer::calculate_minimum_maximum_second_derivatives(const Vector<double> &) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    const Vector<double> scaled_second_derivative(scaling_neurons_number, 0.0);
    return scaled_second_derivative;
}

/// Calculates the outputs from the scaling layer with the mean and standard deviation method for a set of inputs.
/// @param inputs Vector of input values to the scaling layer. The size must be equal to the number of scaling neurons.
Vector<double> ScalingLayer::calculate_mean_standard_deviation_outputs(const Vector<double> &inputs) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> outputs(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        if (statistics[i].standard_deviation < 1e-99) {
            if (display) {
                std::cout << "OpenNN Warning: ScalingLayer class.\n"
                          << "Vector<double> calculate_mean_standard_deviation_outputs(const Vector<double>&) const method.\n"
                          << "Standard deviation of variable " << i << " is zero.\n"
                          << "Those variables won't be scaled.\n";
            }
            outputs[i] = inputs[i];
        } else
            outputs[i] = (inputs[i] - statistics[i].mean) / statistics[i].standard_deviation;
    }
    return outputs;
}

/// Calculates the derivatives of the outputs from the scaling layer with the mean and standard deviation method.
/// As the minimum and maximum method is a linear method, the derivatives will not depend on the inputs.
Vector<double> ScalingLayer::calculate_mean_standard_deviation_derivatives(const Vector<double> &) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<double> derivative(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        if (statistics[i].standard_deviation < 1e-99) {
            if (display) {
                std::cout << "OpenNN Warning: ScalingLayer class.\n"
                          << "Vector<double> calculate_mean_standard_deviation_derivatives(const Vector<double>&) const method.\n"
                          << "Standard deviation of input variable " << i << " is zero.\n"
                          << "That inputs is not be scaled.\n";
            }
            derivative[i] = 1.0;
        } else
            derivative[i] = 1.0 / statistics[i].standard_deviation;
    }
    return derivative;
}

/// Calculates the second derivatives of the outputs from the scaling layer with the mean and standard deviation method.
/// As the minimum and maximum method is a linear method, the second derivatives will be always zero.
Vector<double> ScalingLayer::calculate_mean_standard_deviation_second_derivatives(const Vector<double> &) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    const Vector<double> second_derivative(scaling_neurons_number, 0.0);
    return second_derivative;
}

/// Arranges a "Jacobian" matrix from the vector of derivatives.
Matrix<double> ScalingLayer::arrange_Jacobian(const Vector<double> &derivatives) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Matrix<double> Jacobian(scaling_neurons_number, scaling_neurons_number, 0.0);
    Jacobian.set_diagonal(derivatives);
    return Jacobian;
}

/// Arranges a "Hessian form" vector of matrices from the vector of second derivatives.
Vector<Matrix<double>> ScalingLayer::arrange_Hessian_form(const Vector<double> &second_derivative) const
{
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    Vector<Matrix<double>> Hessian_form(scaling_neurons_number);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        Hessian_form[i].set(scaling_neurons_number, scaling_neurons_number, 0.0);
        Hessian_form[i](i, i) = second_derivative[i];
    }
    return Hessian_form;
}

/// Returns a string with the expression of the scaling process when the none method is used.
/// @param inputs_name Name of inputs to the scaling layer. The size of this vector must be equal to the number of scaling neurons.
/// @param outputs_name Name of outputs from the scaling layer. The size of this vector must be equal to the number of scaling neurons.
std::string ScalingLayer::write_no_scaling_expression(const Vector<std::string> &inputs_name,
                                                      const Vector<std::string> &outputs_name) const
{
    const size_t inputs_number = get_scaling_neurons_number();
    std::ostringstream buffer;
    for (size_t i = 0; i < inputs_number; i++) {
        buffer << outputs_name[i] << "=" << inputs_name[i] << ";\n";
    }
    return buffer.str();
}

/// Returns a string with the expression of the scaling process with the minimum and maximum method.
/// @param inputs_name Name of inputs to the scaling layer. The size of this vector must be equal to the number of scaling neurons.
/// @param outputs_name Name of outputs from the scaling layer. The size of this vector must be equal to the number of scaling neurons.
std::string ScalingLayer::write_minimum_maximum_expression(const Vector<std::string> &inputs_name,
                                                           const Vector<std::string> &outputs_name) const
{
    const size_t inputs_number = get_scaling_neurons_number();
    std::ostringstream buffer;
    for (size_t i = 0; i < inputs_number; i++) {
        buffer << outputs_name[i] << "=2*(" << inputs_name[i] << "-" << statistics[i].minimum << ")/(" << statistics[i].maximum << "-" << statistics[i].minimum << ")-1;\n";
    }
    return buffer.str();
}

/// Returns a string with the expression of the scaling process with the mean and standard deviation method.
/// @param inputs_name Name of inputs to the scaling layer. The size of this vector must be equal to the number of scaling neurons.
/// @param outputs_name Name of outputs from the scaling layer. The size of this vector must be equal to the number of scaling neurons.
std::string ScalingLayer::write_mean_standard_deviation_expression(const Vector<std::string> &inputs_name,
                                                                   const Vector<std::string> &outputs_name) const
{
    const size_t inputs_number = get_scaling_neurons_number();
    std::ostringstream buffer;
    for (size_t i = 0; i < inputs_number; i++) {
        buffer << outputs_name[i] << "=(" << inputs_name[i] << "-" << statistics[i].mean << ")/" << statistics[i].standard_deviation << ";\n";
    }
    return buffer.str();
}

/// Returns a string with the expression of the inputs scaling process.
std::string ScalingLayer::write_expression(const Vector<std::string> &inputs_name,
                                           const Vector<std::string> &outputs_name) const
{
    switch (scaling_method) {
    case NoScaling:
        return write_no_scaling_expression(inputs_name, outputs_name);

    case MinimumMaximum:
        return write_minimum_maximum_expression(inputs_name, outputs_name);

    case MeanStandardDeviation:
        return write_mean_standard_deviation_expression(inputs_name, outputs_name);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "std::string write_expression() const method.\n"
                   << "Unknown inputs scaling method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns a string representation of the current scaling layer object.
std::string ScalingLayer::to_string() const
{
    std::ostringstream buffer;
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    buffer << "Scaling layer\n";
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        buffer << "Statistics " << i + 1 << "\n"
               << "Minimum: " << statistics[i].minimum << "\n"
               << "Maximum: " << statistics[i].maximum << "\n"
               << "Mean: " << statistics[i].mean << "\n"
               << "Standard deviation: " << statistics[i].standard_deviation << "\n";
    }
    buffer << "Scaling method: " << write_scaling_method() << "\n";
    return buffer.str();
}

/// Serializes the scaling layer object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this element.
tinyxml2::XMLDocument *ScalingLayer::to_XML() const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    std::ostringstream buffer;
    tinyxml2::XMLElement *scaling_layer_element = document->NewElement("ScalingLayer");
    document->InsertFirstChild(scaling_layer_element);

    // Scaling neurons number
    tinyxml2::XMLElement *size_element = document->NewElement("ScalingNeuronsNumber");
    scaling_layer_element->LinkEndChild(size_element);
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    buffer.str("");
    buffer << scaling_neurons_number;
    tinyxml2::XMLText *size_text = document->NewText(buffer.str().c_str());
    size_element->LinkEndChild(size_text);

    for (size_t i = 0; i < scaling_neurons_number; i++) {
        tinyxml2::XMLElement *statistics_element = document->NewElement("Statistics");
        statistics_element->SetAttribute("Index", (unsigned) i + 1);
        scaling_layer_element->LinkEndChild(statistics_element);

        // Minimum
        tinyxml2::XMLElement *minimum_element = document->NewElement("Minimum");
        statistics_element->LinkEndChild(minimum_element);
        buffer.str("");
        buffer << statistics[i].minimum;
        tinyxml2::XMLText *minimum_text = document->NewText(buffer.str().c_str());
        minimum_element->LinkEndChild(minimum_text);

        // Maximum
        tinyxml2::XMLElement *maximum_element = document->NewElement("Maximum");
        statistics_element->LinkEndChild(maximum_element);
        buffer.str("");
        buffer << statistics[i].maximum;
        tinyxml2::XMLText *maximum_text = document->NewText(buffer.str().c_str());
        maximum_element->LinkEndChild(maximum_text);

        // Mean
        tinyxml2::XMLElement *mean_element = document->NewElement("Mean");
        statistics_element->LinkEndChild(mean_element);
        buffer.str("");
        buffer << statistics[i].mean;
        tinyxml2::XMLText *mean_text = document->NewText(buffer.str().c_str());
        mean_element->LinkEndChild(mean_text);

        // Standard deviation
        tinyxml2::XMLElement *standard_deviation_element = document->NewElement("StandardDeviation");
        statistics_element->LinkEndChild(standard_deviation_element);
        buffer.str("");
        buffer << statistics[i].standard_deviation;
        tinyxml2::XMLText *standard_deviation_text = document->NewText(buffer.str().c_str());
        standard_deviation_element->LinkEndChild(standard_deviation_text);
    }

    // Scaling method
    tinyxml2::XMLElement *method_element = document->NewElement("ScalingMethod");
    scaling_layer_element->LinkEndChild(method_element);
    tinyxml2::XMLText *method_text = document->NewText(write_scaling_method().c_str());
    method_element->LinkEndChild(method_text);

    return document;
}

/// Deserializes a TinyXML document into this scaling layer object.
/// @param document XML document containing the member data.
void ScalingLayer::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *scaling_layer_element = document.FirstChildElement("ScalingLayer");
    if (!scaling_layer_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Scaling layer element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Scaling neurons number
    const tinyxml2::XMLElement *scaling_neurons_number_element = scaling_layer_element->FirstChildElement(
            "ScalingNeuronsNumber");
    if (!scaling_neurons_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ScalingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Scaling neurons number element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t scaling_neurons_number = atoi(scaling_neurons_number_element->GetText());
    set(scaling_neurons_number);
    unsigned index = 0; // size_t does not work
    const tinyxml2::XMLElement *start_element = scaling_neurons_number_element;
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        const tinyxml2::XMLElement *statistics_element = start_element->NextSiblingElement("Statistics");
        start_element = statistics_element;
        if (!statistics_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Statistics of scaling neuron " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        statistics_element->QueryUnsignedAttribute("Index", &index);
        if (index != i + 1) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw std::logic_error(buffer.str());
        }

        // Minimum
        const tinyxml2::XMLElement *minimum_element = statistics_element->FirstChildElement("Minimum");
        if (!minimum_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Minimum element " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (minimum_element->GetText())
            statistics[i].minimum = atof(minimum_element->GetText());

        // Maximum
        const tinyxml2::XMLElement *maximum_element = statistics_element->FirstChildElement("Maximum");
        if (!maximum_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Maximum element " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (maximum_element->GetText())
            statistics[i].maximum = atof(maximum_element->GetText());

        // Mean
        const tinyxml2::XMLElement *mean_element = statistics_element->FirstChildElement("Mean");
        if (!mean_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Mean element " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (mean_element->GetText())
            statistics[i].mean = atof(mean_element->GetText());

        // Standard deviation
        const tinyxml2::XMLElement *standard_deviation_element = statistics_element->FirstChildElement("StandardDeviation");
        if (!standard_deviation_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                   << "Standard deviation element " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (standard_deviation_element->GetText())
            statistics[i].standard_deviation = atof(standard_deviation_element->GetText());
    }

    // Scaling method
    {
        const tinyxml2::XMLElement *scaling_method_element = scaling_layer_element->FirstChildElement("ScalingMethod");
        if (scaling_method_element) {
            std::string new_method = scaling_method_element->GetText();
            try {
                set_scaling_method(new_method);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Display
    {
        const tinyxml2::XMLElement *display_element = scaling_layer_element->FirstChildElement("Display");
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
}

void ScalingLayer::to_PMML(tinyxml2::XMLElement *element, const Vector<std::string> &inputs_names)
{
    tinyxml2::XMLDocument *pmml_document = element->GetDocument();
    const size_t scaling_neurons_number = get_scaling_neurons_number();
    std::stringstream double_precision_stream;

    // Error checking
    if (scaling_neurons_number != inputs_names.size())
        return;
    if (scaling_method == NoScaling)
        return;

    const Vector<double> inputs_to_scale_range_begin(scaling_neurons_number, 0.0f);
    const Vector<double> inputs_to_scale_range_end(scaling_neurons_number, 1.0f);
    const Vector<double> scaled_outputs_range_begin = calculate_outputs(inputs_to_scale_range_begin);
    const Vector<double> scaled_outputs_range_end = calculate_outputs(inputs_to_scale_range_end);
    for (size_t i = 0; i < scaling_neurons_number; i++) {
        const std::string current_input_display_name(inputs_names[i]);
        const std::string current_input_name(current_input_display_name + "*");
        tinyxml2::XMLElement *derived_field = pmml_document->NewElement("DerivedField");
        element->LinkEndChild(derived_field);
        derived_field->SetAttribute("displayName", current_input_display_name.c_str());
        derived_field->SetAttribute("name", current_input_name.c_str());
        derived_field->SetAttribute("dataType", "double");
        derived_field->SetAttribute("optype", "continuous");

        tinyxml2::XMLElement *norm_continuous = pmml_document->NewElement("NormContinuous");
        derived_field->LinkEndChild(norm_continuous);
        norm_continuous->SetAttribute("field", current_input_display_name.c_str());

        tinyxml2::XMLElement *linear_norm_begin = pmml_document->NewElement("LinearNorm");
        norm_continuous->LinkEndChild(linear_norm_begin);
        linear_norm_begin->SetAttribute("orig", "0.0");
        double_precision_stream.str(std::string());
        double_precision_stream << std::setprecision(15) << scaled_outputs_range_begin[i];
        linear_norm_begin->SetAttribute("norm", double_precision_stream.str().c_str());

        tinyxml2::XMLElement *linear_norm_end = pmml_document->NewElement("LinearNorm");
        norm_continuous->LinkEndChild(linear_norm_end);
        linear_norm_end->SetAttribute("orig", "1.0");
        double_precision_stream.str(std::string());
        double_precision_stream << std::setprecision(15) << scaled_outputs_range_end[i];
        linear_norm_end->SetAttribute("norm", double_precision_stream.str().c_str());
    }
}

void ScalingLayer::from_PMML(const tinyxml2::XMLElement *element, const Vector<std::string> &inputs_names)
{
    const tinyxml2::XMLElement *derived_field = element->FirstChildElement("DerivedField");
    ScalingMethod new_scaling_method = NoScaling;
    int i = 0;
    while (derived_field) {
        std::string derived_field_name;
        const tinyxml2::XMLAttribute *attribute_display_name = derived_field->FindAttribute("displayName");
        if (!attribute_display_name) {
            const tinyxml2::XMLAttribute *attribute_name = derived_field->FindAttribute("name");
            if (!attribute_name) {
                std::stringstream buffer;

                buffer << "OpenNN Exception: ScalingLayer class.\n"
                       << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                       << "Attribute \"name\" in DerivedField element is NULL.\n";

                throw std::logic_error(buffer.str());
            }
            derived_field_name = std::string(attribute_name->Value());
        } else
            derived_field_name = std::string(attribute_display_name->Value());

        if (!derived_field->FindAttribute("optype")) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "Attribute \"optype\" in DerivedField element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        // not supported
        if (std::string(derived_field->FindAttribute("optype")->Value()) != "continuous")
            break;

        const tinyxml2::XMLElement *norm_continuous = derived_field->FirstChildElement("NormContinuous");
        if (!norm_continuous)
            break;

        const tinyxml2::XMLAttribute *norm_continuous_field = norm_continuous->FindAttribute("field");
        if (!norm_continuous_field) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "Attribute \"field\" in NormContinuous_field element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (!inputs_names.contains(std::string(norm_continuous_field->Value()))) {
            derived_field = derived_field->NextSiblingElement("DerivedField");
            continue;
        }

        const tinyxml2::XMLElement *linear_norm_begin = norm_continuous->FirstChildElement("LinearNorm");
        const tinyxml2::XMLElement *linear_norm_end = norm_continuous->LastChildElement("LinearNorm");
        if (!linear_norm_begin || !linear_norm_end) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "LinearNorm in NormContinuous element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        const tinyxml2::XMLAttribute *attribute_orig_begin = linear_norm_begin->FindAttribute("orig");
        const tinyxml2::XMLAttribute *attribute_orig_end = linear_norm_end->FindAttribute("orig");
        if (!attribute_orig_begin || !attribute_orig_end) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "Attribute \"orig\" in LinearNorm element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        const tinyxml2::XMLAttribute *attribute_norm_begin = linear_norm_begin->FindAttribute("norm");
        const tinyxml2::XMLAttribute *attribute_norm_end = linear_norm_end->FindAttribute("norm");
        if (!attribute_norm_begin || !attribute_norm_end) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "Attribute \"norm\" in LinearNorm element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        const std::string string_orig_begin(attribute_orig_begin->Value());
        const std::string string_orig_end(attribute_orig_end->Value());
        const std::string string_normalization_range_begin(attribute_norm_begin->Value());
        const std::string string_normalization_range_end(attribute_norm_end->Value());
        if (string_orig_begin == "" ||
            string_orig_end == "" ||
            string_normalization_range_begin == "" ||
            string_normalization_range_end == "")
            break;

        double orig_begin = std::stod(string_orig_begin);
        double orig_end = std::stod(string_orig_end);
        double normalization_range_begin = std::stod(string_normalization_range_begin);
        double normalization_range_end = std::stod(string_normalization_range_end);
        if (orig_begin > orig_end) {
            double swap = orig_begin;
            orig_begin = orig_end;
            orig_end = swap;
            swap = normalization_range_begin;
            normalization_range_begin = normalization_range_end;
            normalization_range_end = swap;
        }

        if (orig_begin == orig_end) {
            std::stringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class.\n"
                   << "void from_PMML(const tinyxml2::XMLElement*, const Vector<std::string>&) method.\n"
                   << "Attributes \"orig\" in LinearNorm elements are equals.\n";

            throw std::logic_error(buffer.str());
        }

        if (normalization_range_begin != normalization_range_end) {
            // Set data mean and standard deviation
            const double new_data_standard_deviation = (orig_begin - orig_end) / (normalization_range_begin - normalization_range_end);
            const double new_data_mean = orig_begin - normalization_range_begin * new_data_standard_deviation;
            set_mean(i, new_data_mean);
            set_standard_deviation(i, new_data_standard_deviation);
            const double new_min = ((2 * normalization_range_end * orig_begin) + (2 * orig_begin) - (2 * normalization_range_begin * orig_end) - (2 * orig_end)) / (2 * (normalization_range_end - normalization_range_begin));
            double new_max;
            if ((normalization_range_begin + 1) != 0)
                new_max = ((2 * (orig_begin - new_min)) / (normalization_range_begin + 1)) + new_min;
            else
                new_max = ((2 * (orig_end - new_min)) / (normalization_range_end + 1)) + new_min;

            if (fabs(new_min - get_statistics().at(i).minimum) < 1e-5 &&
                fabs(new_max - get_statistics().at(i).maximum) < 1e-5) {
                if (new_scaling_method == NoScaling)
                    new_scaling_method = MinimumMaximum;
            } else {
                new_scaling_method = MeanStandardDeviation;
            }
        }

        derived_field = derived_field->NextSiblingElement("DerivedField");
        i++;
    }
    set_scaling_method(new_scaling_method);
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
