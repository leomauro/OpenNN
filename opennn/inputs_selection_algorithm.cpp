/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   I N P U T S   S E L E C T I O N   A L G O R I T H M   C L A S S                                            */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/


// OpenNN includes

#include "inputs_selection_algorithm.h"

namespace OpenNN {

/// Default constructor.
InputsSelectionAlgorithm::InputsSelectionAlgorithm()
        : training_strategy_pointer(NULL)
{
    set_default();
}

/// Training strategy constructor.
/// @param new_training_strategy_pointer Pointer to a trainig strategy object.
InputsSelectionAlgorithm::InputsSelectionAlgorithm(TrainingStrategy *new_training_strategy_pointer)
        : training_strategy_pointer(new_training_strategy_pointer)
{
    set_default();
}

/// File constructor.
/// @param file_name Name of XML inputs selection file.
InputsSelectionAlgorithm::InputsSelectionAlgorithm(const std::string &)
        : training_strategy_pointer(NULL)
{
}

/// XML constructor.
/// @param inputs_selection_document Pointer to a TinyXML document containing the inputs selection algorithm data.
InputsSelectionAlgorithm::InputsSelectionAlgorithm(const tinyxml2::XMLDocument &)
        : training_strategy_pointer(NULL)
{
}

/// Destructor.
InputsSelectionAlgorithm::~InputsSelectionAlgorithm()
{
}

/// Returns whether the problem is of function regression type.
const bool &InputsSelectionAlgorithm::get_function_regression() const
{
    return function_regression;
}

/// Returns a pointer to the training strategy object.
TrainingStrategy *InputsSelectionAlgorithm::get_training_strategy_pointer() const
{
#ifdef __OPENNN_DEBUG__
    if (!training_strategy_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "DataSet* get_training_strategy_pointer() const method.\n"
               << "Training strategy pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return training_strategy_pointer;
}

/// Returns true if this inputs selection algorithm has a training strategy associated, and false otherwise.
bool InputsSelectionAlgorithm::has_training_strategy() const
{
    return training_strategy_pointer;
}

/// Returns the number of trials for each network architecture.
const size_t &InputsSelectionAlgorithm::get_trials_number() const
{
    return trials_number;
}

/// Returns true if the neural network parameters are to be reserved, and false otherwise.
const bool &InputsSelectionAlgorithm::get_reserve_parameters_data() const
{
    return reserve_parameters_data;
}

/// Returns true if the performance functional performances are to be reserved, and false otherwise.
const bool &InputsSelectionAlgorithm::get_reserve_performance_data() const
{
    return reserve_performance_data;
}

/// Returns true if the selection performances are to be reserved, and false otherwise.
const bool &InputsSelectionAlgorithm::get_reserve_selection_performance_data() const
{
    return reserve_selection_performance_data;
}

/// Returns true if the parameters vector of the neural network with minimum selection performance is to be reserved, and false otherwise.
const bool &InputsSelectionAlgorithm::get_reserve_minimal_parameters() const
{
    return reserve_minimal_parameters;
}

/// Returns the method for the calculation of the performance and the selection performance.
const InputsSelectionAlgorithm::PerformanceCalculationMethod &InputsSelectionAlgorithm::get_performance_calculation_method() const
{
    return performance_calculation_method;
}

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.
const bool &InputsSelectionAlgorithm::get_display() const
{
    return display;
}

/// Returns the goal for the selection performance in the inputs selection algorithm.
const double &InputsSelectionAlgorithm::get_selection_performance_goal() const
{
    return selection_performance_goal;
}

/// Returns the maximum number of iterations in the inputs selection algorithm.
const size_t &InputsSelectionAlgorithm::get_maximum_iterations_number() const
{
    return maximum_iterations_number;
}

/// Returns the maximum time in the inputs selection algorithm.
const double &InputsSelectionAlgorithm::get_maximum_time() const
{
    return maximum_time;
}

/// Return the maximum correlation for the algorithm.
const double &InputsSelectionAlgorithm::get_maximum_correlation() const
{
    return maximum_correlation;
}

/// Return the minimum correlation for the algorithm.
const double &InputsSelectionAlgorithm::get_minimum_correlation() const
{
    return minimum_correlation;
}

/// Return the tolerance of error for the algorithm.
const double &InputsSelectionAlgorithm::get_tolerance() const
{
    return tolerance;
}

/// Return a string with the performance calculation method of this inputs selection algorithm.
std::string InputsSelectionAlgorithm::write_performance_calculation_method() const
{
    switch (performance_calculation_method) {
    case Maximum:
        return "Maximum";

    case Minimum:
        return "Minimum";

    case Mean:
        return "Mean";

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
                   << "std::string write_performance_calculation_method() const method.\n"
                   << "Unknown performance calculation method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Sets a new regression value.
/// If it is set to true the problem will be taken as a function regression;
/// if it is set to false the problem will be taken as a pattern recognition.
/// @param new_regression Regression value.
void InputsSelectionAlgorithm::set_function_regression(const bool &new_function_regression)
{
    function_regression = new_function_regression;
}

/// Sets a new training strategy pointer.
/// @param new_training_strategy_pointer Pointer to a training strategy object.
void InputsSelectionAlgorithm::set_training_strategy_pointer(TrainingStrategy *new_training_strategy_pointer)
{
    training_strategy_pointer = new_training_strategy_pointer;
}

/// Sets the members of the inputs selection object to their default values.
void InputsSelectionAlgorithm::set_default()
{
    // MEMBERS
    trials_number = 1;

    // inputs selection results
    reserve_parameters_data = true;
    reserve_performance_data = true;
    reserve_selection_performance_data = true;
    reserve_minimal_parameters = true;

    performance_calculation_method = Minimum;

    display = true;

    // STOPPING CRITERIA
    selection_performance_goal = 0.0;
    maximum_iterations_number = 1000;
    maximum_correlation = 1e20;
    minimum_correlation = 0;
    maximum_time = 10000.0;
    tolerance = 1.0e-3;
}

/// Sets the number of times that each different neural network is to be trained.
/// @param new_trials_number Number of trials for each set of parameters.
void InputsSelectionAlgorithm::set_trials_number(const size_t &new_trials_number)
{

#ifdef __OPENNN_DEBUG__
    if (new_trials_number <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_trials_number(const size_t&) method.\n"
               << "Number of assays must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    trials_number = new_trials_number;
}

/// Sets the reserve flag for the parameters data.
/// @param new_reserve_parameters_data Flag value.
void InputsSelectionAlgorithm::set_reserve_parameters_data(const bool &new_reserve_parameters_data)
{
    reserve_parameters_data = new_reserve_parameters_data;
}

/// Sets the reserve flag for the performance data.
/// @param new_reserve_performance_data Flag value.
void InputsSelectionAlgorithm::set_reserve_performance_data(const bool &new_reserve_performance_data)
{
    reserve_performance_data = new_reserve_performance_data;
}

/// Sets the reserve flag for the selection performance data.
/// @param new_reserve_selection_performance_data Flag value.
void InputsSelectionAlgorithm::set_reserve_selection_performance_data(const bool &new_reserve_selection_performance_data)
{
    reserve_selection_performance_data = new_reserve_selection_performance_data;
}

/// Sets the reserve flag for the minimal parameters.
/// @param new_reserve_minimal_parameters Flag value.
void InputsSelectionAlgorithm::set_reserve_minimal_parameters(const bool &new_reserve_minimal_parameters)
{
    reserve_minimal_parameters = new_reserve_minimal_parameters;
}

/// Sets a new method to calculate the performance and the selection performance.
/// @param new_performance_calculation_method Method to calculate the performance (Minimum, Maximum or Mean).
void InputsSelectionAlgorithm::set_performance_calculation_method(const InputsSelectionAlgorithm::PerformanceCalculationMethod &new_performance_calculation_method)
{
    performance_calculation_method = new_performance_calculation_method;
}

/// Sets a new performance calculation method from a string.
/// @param new_performance_calculation_method String with the performance calculation method.
void InputsSelectionAlgorithm::set_performance_calculation_method(const std::string &new_performance_calculation_method)
{
    if (new_performance_calculation_method == "Maximum")
        performance_calculation_method = Maximum;
    else if (new_performance_calculation_method == "Minimum")
        performance_calculation_method = Minimum;
    else if (new_performance_calculation_method == "Mean")
        performance_calculation_method = Mean;
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_performance_calculation_method(const std::string&) method.\n"
               << "Unknown performance calculation method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void InputsSelectionAlgorithm::set_display(const bool &new_display)
{
    display = new_display;
}

/// Sets the Selection performance goal for the inputs selection algorithm.
/// @param new_selection_performance_goal Goal of the selection performance.
void InputsSelectionAlgorithm::set_selection_performance_goal(const double &new_selection_performance_goal)
{

#ifdef __OPENNN_DEBUG__
    if (new_selection_performance_goal < 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_selection_performance_goal(const double&) method.\n"
               << "Selection performance goal must be greater or equal than 0.\n";

        throw std::logic_error(buffer.str());
    }

#endif

    selection_performance_goal = new_selection_performance_goal;
}

/// Sets the maximum iterations number for the inputs selection algorithm.
/// @param new_maximum_iterations_number Maximum number of iterations.
void InputsSelectionAlgorithm::set_maximum_iterations_number(const size_t &new_maximum_iterations_number)
{
    maximum_iterations_number = new_maximum_iterations_number;
}

/// Sets the maximum time for the inputs selection algorithm.
/// @param new_maximum_time Maximum time for the algorithm.
void InputsSelectionAlgorithm::set_maximum_time(const double &new_maximum_time)
{

#ifdef __OPENNN_DEBUG__
    if (new_maximum_time < 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_maximum_time(const double&) method.\n"
               << "Maximum time must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    maximum_time = new_maximum_time;
}

/// Sets the maximum value for the correlations in the inputs selection algorithm.
/// @param new_maximum_correlation Maximum value of the correlations.
void InputsSelectionAlgorithm::set_maximum_correlation(const double &new_maximum_correlation)
{

#ifdef __OPENNN_DEBUG__
    if (new_maximum_correlation < 0 || new_maximum_correlation > 1) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_maximum_correlation(const double&) method.\n"
               << "Maximum correlation must be comprised between 0 and 1.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    maximum_correlation = new_maximum_correlation;
}

/// Sets the minimum value for the correlations in the inputs selection algorithm.
/// @param new_minimum_correlation Minimum value of the correlations.
void InputsSelectionAlgorithm::set_minimum_correlation(const double &new_minimum_correlation)
{

#ifdef __OPENNN_DEBUG__
    if (new_minimum_correlation < 0 || new_minimum_correlation > 1) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_minimum_correlation(const double&) method.\n"
               << "Minimum correaltion must be comprised between 0 and 1.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    minimum_correlation = new_minimum_correlation;
}

/// Set the tolerance for the errors in the trainings of the algorithm.
/// @param new_tolerance Value of the tolerance.
void InputsSelectionAlgorithm::set_tolerance(const double &new_tolerance)
{

#ifdef __OPENNN_DEBUG__
    if (new_tolerance < 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void set_tolerance(const double&) method.\n"
               << "Tolerance must be equal or greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    tolerance = new_tolerance;
}

/// Returns a matrix with the logistic correlations between all inputs and target variables.
/// The number of rows is the number of inputs variables.
/// The number of columns is the number of target variables.
Matrix<double> InputsSelectionAlgorithm::calculate_logistic_correlations() const
{

#ifdef __OPENNN_DEBUG__
    if (!training_strategy_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to training strategy is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    if (!training_strategy_pointer->has_performance_functional()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to performance functional is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    if (!training_strategy_pointer->get_performance_functional_pointer()->has_data_set()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to data set is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const PerformanceFunctional *performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();
    const DataSet *data_set_pointer = performance_functional_pointer->get_data_set_pointer();
    const Variables &variables = data_set_pointer->get_variables();
    const Instances &instances = data_set_pointer->get_instances();

    const size_t instances_number = instances.get_instances_number();
    const size_t inputs_number = variables.count_inputs_number();
    const size_t targets_number = variables.count_targets_number();

    const Vector<size_t> input_indices = variables.arrange_inputs_indices();
    const Vector<size_t> target_indices = variables.arrange_targets_indices();

    Matrix<double> correlations(inputs_number, targets_number, 0.0);

    srand(0);

    for (size_t i = 0; i < inputs_number; i++) {
        const Vector<double> inputs = data_set_pointer->get_variable(input_indices[i]);
        for (size_t j = 0; j < targets_number; j++) {
            const Vector<double> targets = data_set_pointer->get_variable(target_indices[j]);
            Matrix<double> data(instances_number, 2);
            data.set_column(0, inputs);
            data.set_column(1, targets);
            DataSet data_set(data);

            const Vector<Statistics<double>> inputs_statistics = data_set.scale_inputs_minimum_maximum();
            Instances *instances_pointer = data_set.get_instances_pointer();
            instances_pointer->set_training();

            NeuralNetwork neural_network(1, 1);
            neural_network.construct_scaling_layer();

            ScalingLayer *scaling_layer_pointer = neural_network.get_scaling_layer_pointer();
            scaling_layer_pointer->set_statistics(inputs_statistics);
            scaling_layer_pointer->set_scaling_method(ScalingLayer::NoScaling);

            MultilayerPerceptron *multilayer_perceptron_pointer = neural_network.get_multilayer_perceptron_pointer();
            multilayer_perceptron_pointer->set_layer_activation_function(0, Perceptron::Logistic);

            PerformanceFunctional performance_functional(&neural_network, &data_set);
            performance_functional.set_objective_type(PerformanceFunctional::WEIGHTED_SQUARED_ERROR_OBJECTIVE);

            TrainingStrategy training_strategy(&performance_functional);
            training_strategy.set_main_type(TrainingStrategy::LEVENBERG_MARQUARDT_ALGORITHM);

            LevenbergMarquardtAlgorithm *levenberg_marquardt_algorithm = training_strategy.get_Levenberg_Marquardt_algorithm_pointer();
            levenberg_marquardt_algorithm->set_minimum_parameters_increment_norm(1.0e-3);
            levenberg_marquardt_algorithm->set_gradient_norm_goal(1.0e-4);
            levenberg_marquardt_algorithm->set_minimum_performance_increase(1.0e-12);
            levenberg_marquardt_algorithm->set_maximum_iterations_number(100);

            training_strategy.set_display(false);
            training_strategy.perform_training();
            scaling_layer_pointer->set_scaling_method(ScalingLayer::MinimumMaximum);
            const Vector<double> outputs = neural_network.calculate_output_data(inputs.to_column_matrix())
                                                         .to_vector();
            correlations(i, j) = targets.calculate_linear_correlation(outputs);
            if (display) {
                std::cout << "Calculating correlation: Input " << i + 1 << "; Target " << j + 1 << std::endl;
                std::cout << "Correlation value = " << std::abs(correlations(i, j)) << std::endl;
            }
        }
    }

    srand((unsigned) time(NULL));

    return correlations;
}

/// Calculate the correlation depending on whether the problem is a linear regression or a pattern recognition.
/// Return the absolute value of the correlation.
/// If there are many targets in the data set it returns the sum of the absolute values.
Vector<double> InputsSelectionAlgorithm::calculate_final_correlations() const
{
    Vector<double> final_correlations;
    Matrix<double> correlations;

    DataSet *data_set = training_strategy_pointer->get_performance_functional_pointer()->get_data_set_pointer();
    if (function_regression)
        correlations = data_set->calculate_linear_correlations();
    else
        correlations = calculate_logistic_correlations();
    correlations = correlations.calculate_absolute_value();
    final_correlations.resize(correlations.get_rows_number());
    for (size_t i = 0; i < final_correlations.size(); i++) {
        for (size_t j = 0; j < correlations.get_columns_number(); j++) {
            final_correlations[i] += correlations(i, j);
        }
    }

    return final_correlations;
}

/// Sets the neural network with the number of inputs encoded in the vector.
/// This method used the grow and prune inputs methods.
/// @param inputs Vector with the inputs to be set.
void InputsSelectionAlgorithm::set_neural_inputs(const Vector<bool> &inputs)
{
    const PerformanceFunctional *performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();
    NeuralNetwork *neural_network_pointer = performance_functional_pointer->get_neural_network_pointer();

    const size_t current_inputs_number = inputs.count_occurrences(true);
    const size_t neural_network_inputs_number = neural_network_pointer->get_inputs_number();

    if (current_inputs_number < neural_network_inputs_number) {
        for (size_t j = current_inputs_number; j < neural_network_inputs_number; j++) {
            neural_network_pointer->prune_input(0);
        }
    } else {
        for (size_t j = neural_network_inputs_number; j < current_inputs_number; j++) {
            neural_network_pointer->grow_input();
        }
    }

    neural_network_pointer->perturbate_parameters(200);
}

/// Returns the minimum of the performance and selection performance in trials_number trainings.
/// @param inputs Vector of the inputs to be trained with.
Vector<double> InputsSelectionAlgorithm::perform_minimum_model_evaluation(const Vector<bool> &inputs)
{

#ifdef __OPENNN_DEBUG__
    if (inputs.count_occurrences(true) <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of inputs must be greater or equal than 1.\n";

        throw std::logic_error(buffer.str());
    }

    if (trials_number <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of parameters assay must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    NeuralNetwork *neural_network = training_strategy_pointer->get_performance_functional_pointer()
                                                             ->get_neural_network_pointer();
    TrainingStrategy::Results training_strategy_results;

    Vector<double> final(2);
    final[0] = 10;
    final[1] = 10;

    Vector<double> current_performance(2);
    Vector<double> final_parameters;
    bool flag_performance = false;
    bool flag_selection = false;
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            final[0] = performance_history[i];
            flag_performance = true;
        }
    }
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            final[1] = selection_performance_history[i];
            flag_selection = true;
        }
    }
    if (flag_performance && flag_selection)
        return final;

    neural_network->perturbate_parameters(0.5);
    training_strategy_results = training_strategy_pointer->perform_training();
    current_performance = get_final_performances(training_strategy_results);
    final[0] = current_performance[0];
    final[1] = current_performance[1];
    final_parameters.set(neural_network->arrange_parameters());
    for (size_t i = 1; i < trials_number; i++) {
        if (display) {
            std::cout << "Trial number: " << i << std::endl;
            std::cout << "Training performance: " << final[0] << std::endl;
            std::cout << "Selection performance: " << final[1] << std::endl;
        }

        neural_network->randomize_parameters_normal();
        training_strategy_results = training_strategy_pointer->perform_training();
        current_performance = get_final_performances(training_strategy_results);
        if (!flag_performance && final[0] > current_performance[0]) {
            final[0] = current_performance[0];
            final_parameters.set(neural_network->arrange_parameters());
        }
        if (!flag_selection && final[1] > current_performance[1]) {
            final[1] = current_performance[1];
            final_parameters.set(neural_network->arrange_parameters());
        }
        if (i == trials_number - 1 && display) {
            std::cout << "Trial number: " << trials_number << std::endl;
            std::cout << "Training performance: " << final[0] << std::endl;
            std::cout << "Selection performance: " << final[1] << std::endl;
        }
    }

    inputs_history.push_back(inputs);
    performance_history.push_back(final[0]);
    selection_performance_history.push_back(final[1]);
    parameters_history.push_back(final_parameters);

    return final;
}

/// Returns the maximum of the performance and selection performance in trials_number trainings.
/// @param inputs Vector of the inputs to be trained with.
Vector<double> InputsSelectionAlgorithm::perform_maximum_model_evaluation(const Vector<bool> &inputs)
{

#ifdef __OPENNN_DEBUG__
    if (inputs.count_occurrences(true) <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of inputs must be greater or equal than 1.\n";

        throw std::logic_error(buffer.str());
    }

    if (trials_number <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of parameters assay must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    NeuralNetwork *neural_network = training_strategy_pointer->get_performance_functional_pointer()
                                                             ->get_neural_network_pointer();

    TrainingStrategy::Results training_strategy_results;
    Vector<double> final(2);
    final[0] = 0;
    final[1] = 0;

    Vector<double> current_performance(2);
    Vector<double> final_parameters;
    bool flag_performance = false;
    bool flag_selection = false;
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            final[0] = performance_history[i];
            flag_performance = true;
        }
    }
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            final[1] = selection_performance_history[i];
            flag_selection = true;
        }
    }
    if (flag_performance && flag_selection)
        return final;

    neural_network->perturbate_parameters(0.5);
    training_strategy_results = training_strategy_pointer->perform_training();
    current_performance = get_final_performances(training_strategy_results);
    final[0] = current_performance[0];
    final[1] = current_performance[1];
    final_parameters.set(neural_network->arrange_parameters());
    for (size_t i = 1; i < trials_number; i++) {
        if (display) {
            std::cout << "Trial number: " << i << std::endl;
            std::cout << "Training performance: " << final[0] << std::endl;
            std::cout << "Selection performance: " << final[1] << std::endl;
        }
        neural_network->randomize_parameters_normal();
        training_strategy_results = training_strategy_pointer->perform_training();
        current_performance = get_final_performances(training_strategy_results);
        if (!flag_performance && final[0] < current_performance[0]) {
            final[0] = current_performance[0];
            final_parameters.set(neural_network->arrange_parameters());
        }
        if (!flag_selection && final[1] < current_performance[1]) {
            final[1] = current_performance[1];
            final_parameters.set(neural_network->arrange_parameters());
        }
        if (i == trials_number - 1 && display) {
            std::cout << "Trial number: " << trials_number << std::endl;
            std::cout << "Training performance: " << final[0] << std::endl;
            std::cout << "Selection performance: " << final[1] << std::endl;
        }
    }

    inputs_history.push_back(inputs);
    performance_history.push_back(final[0]);
    selection_performance_history.push_back(final[1]);
    parameters_history.push_back(final_parameters);

    return final;
}

/// Returns the mean of the performance and selection performance in trials_number trainings.
/// @param inputs Vector of the inputs to be trained with.
Vector<double> InputsSelectionAlgorithm::perform_mean_model_evaluation(const Vector<bool> &inputs)
{

#ifdef __OPENNN_DEBUG__
    if (inputs.count_occurrences(true) <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of inputs must be greater or equal than 1.\n";

        throw std::logic_error(buffer.str());
    }

    if (trials_number <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> perform_minimum_model_evaluation(size_t) method.\n"
               << "Number of parameters assay must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    NeuralNetwork *neural_network = training_strategy_pointer->get_performance_functional_pointer()
                                                             ->get_neural_network_pointer();
    TrainingStrategy::Results training_strategy_results;
    Vector<double> mean_final(2);
    mean_final[0] = 0;
    mean_final[1] = 0;

    Vector<double> current_performance(2);
    Vector<double> final_parameters;
    bool flag_performance = false;
    bool flag_selection = false;
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            mean_final[0] = performance_history[i];
            flag_performance = true;
        }
    }
    for (size_t i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            mean_final[1] = selection_performance_history[i];
            flag_selection = true;
        }
    }
    if (flag_performance && flag_selection)
        return mean_final;

    neural_network->perturbate_parameters(0.5);
    training_strategy_results = training_strategy_pointer->perform_training();
    current_performance = get_final_performances(training_strategy_results);
    mean_final[0] = current_performance[0];
    mean_final[1] = current_performance[1];
    final_parameters.set(neural_network->arrange_parameters());
    for (size_t i = 1; i < trials_number; i++) {
        if (display) {
            std::cout << "Trial number: " << i << std::endl;
            std::cout << "Training performance: " << mean_final[0] << std::endl;
            std::cout << "Selection performance: " << mean_final[1] << std::endl;
        }

        neural_network->randomize_parameters_normal();
        training_strategy_results = training_strategy_pointer->perform_training();
        current_performance = get_final_performances(training_strategy_results);
        if (!flag_performance)
            mean_final[0] += current_performance[0] / trials_number;
        if (!flag_selection)
            mean_final[1] += current_performance[1] / trials_number;
        if (i == trials_number - 1 && display) {
            std::cout << "Trial number: " << trials_number << std::endl;
            std::cout << "Training performance: " << mean_final[0] << std::endl;
            std::cout << "Selection performance: " << mean_final[1] << std::endl;
        }
    }

    inputs_history.push_back(inputs);
    performance_history.push_back(mean_final[0]);
    selection_performance_history.push_back(mean_final[1]);
    parameters_history.push_back(final_parameters);

    return mean_final;
}

/// Return final training performance and final selection performance depending on the training method.
/// @param results Results of the perform_training method.
Vector<double> InputsSelectionAlgorithm::get_final_performances(const TrainingStrategy::Results &results) const
{
    Vector<double> performances(2);
    switch (training_strategy_pointer->get_main_type()) {
    case TrainingStrategy::NO_MAIN:
        performances[0] = 0;
        performances[1] = 0;
        break;

    case TrainingStrategy::GRADIENT_DESCENT:
        performances[0] = results.gradient_descent_results_pointer->final_performance;
        performances[1] = results.gradient_descent_results_pointer->final_selection_performance;
        break;

    case TrainingStrategy::CONJUGATE_GRADIENT:
        performances[0] = results.conjugate_gradient_results_pointer->final_performance;
        performances[1] = results.conjugate_gradient_results_pointer->final_selection_performance;
        break;

    case TrainingStrategy::QUASI_NEWTON_METHOD:
        performances[0] = results.quasi_Newton_method_results_pointer->final_performance;
        performances[1] = results.quasi_Newton_method_results_pointer->final_selection_performance;
        break;

    case TrainingStrategy::LEVENBERG_MARQUARDT_ALGORITHM:
        performances[0] = results.Levenberg_Marquardt_algorithm_results_pointer->final_performance;
        performances[1] = results.Levenberg_Marquardt_algorithm_results_pointer->final_selection_performance;
        break;

    case TrainingStrategy::USER_MAIN:
        performances[0] = 0;
        performances[1] = 0;
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
                   << "Vector<double> get_final_performances(const TrainingStrategy::Results) method.\n"
                   << "Unknown main type method.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return performances;
}

/// Return performance and selection depending on the performance calculation method.
/// @param inputs Vector of inputs to be trained with.
Vector<double> InputsSelectionAlgorithm::perform_model_evaluation(const Vector<bool> &inputs)
{
    set_neural_inputs(inputs);
    switch (performance_calculation_method) {
    case Maximum:
        return perform_maximum_model_evaluation(inputs);

    case Minimum:
        return perform_minimum_model_evaluation(inputs);

    case Mean:
        return perform_mean_model_evaluation(inputs);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
                   << "Vector<double> perform_model_evaluation(const size_t) method.\n"
                   << "Unknown performance calculation method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}


/// Returns the parameters of the neural network if the inputs is in the history.
/// @param inputs Vector of inputs to be trained with.
Vector<double> InputsSelectionAlgorithm::get_parameters_inputs(const Vector<bool> &inputs) const
{

#ifdef __OPENNN_DEBUG__
    if (inputs.count_occurrences(true) <= 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "Vector<double> get_parameters_inputs(const Vector<bool>&) method.\n"
               << "Inputs must be greater than 1.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    size_t i;
    Vector<double> parameters;
    for (i = 0; i < inputs_history.size(); i++) {
        if (inputs_history[i] == inputs) {
            parameters = parameters_history[i];
            break;
        }
    }
    return parameters;

}

/// Delete the history of the selection performance values.
void InputsSelectionAlgorithm::delete_selection_history()
{
    selection_performance_history.set();
}

/// Delete the history of the performance values.
void InputsSelectionAlgorithm::delete_performance_history()
{
    performance_history.set();
}

/// Delete the history of the parameters of the trained neural networks.
void InputsSelectionAlgorithm::delete_parameters_history()
{
    parameters_history.set();
}

/// Checks that the different pointers needed for performing the inputs selection are not NULL.
void InputsSelectionAlgorithm::check() const
{
    if (!training_strategy_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to training strategy is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    if (!training_strategy_pointer->has_performance_functional()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to performance functional is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const PerformanceFunctional *performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

    if (!performance_functional_pointer->has_neural_network()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const NeuralNetwork *neural_network_pointer = performance_functional_pointer->get_neural_network_pointer();

    if (!neural_network_pointer->has_multilayer_perceptron()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to multilayer perceptron is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const MultilayerPerceptron *multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

    if (multilayer_perceptron_pointer->is_empty()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Multilayer Perceptron is empty.\n";

        throw std::logic_error(buffer.str());
    }

    if (!performance_functional_pointer->has_data_set()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to data set is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const DataSet *data_set_pointer = performance_functional_pointer->get_data_set_pointer();
    const Instances &instances = data_set_pointer->get_instances();
    const size_t selection_instances_number = instances.count_selection_instances_number();

    if (selection_instances_number == 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "void check() const method.\n"
               << "Number of selection instances is zero.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Return a string with the stopping condition of the InputsSelectionResults
std::string InputsSelectionAlgorithm::InputsSelectionResults::write_stopping_condition() const
{
    switch (stopping_condition) {
    case MaximumTime:
        return "MaximumTime";

    case SelectionPerformanceGoal:
        return "SelectionPerformanceGoal";

    case MaximumInputs:
        return "MaximumInputs";

    case MinimumInputs:
        return "MinimumInputs";

    case MaximumIterations:
        return "MaximumIterations";

    case MaximumSelectionFailures:
        return "MaximumSelectionFailures";

    case CorrelationGoal:
        return "CorrelationGoal";

    case AlgorithmFinished:
        return "AlgorithmFinished";

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: InputsSelectionResults struct.\n"
            << "std::string write_stopping_condition() const method.\n"
            << "Unknown stopping condition type.\n";

            throw std::logic_error(buffer.str());

            break;
        }
    }

}

/// Returns a string representation of the current inputs selection results structure.
std::string InputsSelectionAlgorithm::InputsSelectionResults::to_string() const
{
    std::ostringstream buffer;

    // Inputs history
    if (!inputs_data.empty()) {
        buffer << "% Inputs history:\n"
               << inputs_data.to_row_matrix() << "\n";
    }

    // Parameters history
    if (!parameters_data.empty()) {
        buffer << "% Parameters history:\n"
               << parameters_data.to_row_matrix() << "\n";
    }

    // Performance history
    if (!performance_data.empty()) {
        buffer << "% Performance history:\n"
               << performance_data.to_row_matrix() << "\n";
    }

    // Selection performance history
    if (!selection_performance_data.empty()) {
        buffer << "% Selection performance history:\n"
               << selection_performance_data.to_row_matrix() << "\n";
    }

    // Minimal parameters
    if (!minimal_parameters.empty()) {
        buffer << "% Minimal parameters:\n"
               << minimal_parameters << "\n";
    }

    // Stopping condition
    buffer << "% Stopping condition\n"
           << write_stopping_condition() << "\n";

    // Optimum selection performance
    if (final_selection_performance != 0) {
        buffer << "% Optimum selection performance:\n"
               << final_selection_performance << "\n";
    }

    // Final performance
    if (final_performance != 0) {
        buffer << "% Final performance:\n"
               << final_performance << "\n";
    }

    // Optimal input
    if (!optimal_inputs.empty()) {
        buffer << "% Optimal input:\n"
               << optimal_inputs << "\n";
    }

    // Iterations number
    buffer << "% Number of iterations:\n"
           << iterations_number << "\n";

    // Elapsed time
    buffer << "% Elapsed time:\n"
           << elapsed_time << "\n";

    return buffer.str();
}

/// Return the index of uses where is the (input_number)-th input.
/// @param uses vector of the uses of the variables.
/// @param input_number index of the input to find.
size_t InputsSelectionAlgorithm::get_input_index(const Vector<Variables::Use> uses, const size_t input_number)
{

#ifdef __OPENNN_DEBUG__
    if (uses.size() < input_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: InputsSelectionAlgorithm class.\n"
               << "const size_t get_input_index(const Vector<Variables::Use>, const size_t) method.\n"
               << "Size of uses vector must be greater than " <<  input_number << ".\n";

        throw std::logic_error(buffer.str());
    }
#endif

    size_t i = 0;
    size_t j = 0;
    while (i < uses.size()) {
        if (uses[i] == Variables::Input && input_number == j)
            break;
        if (uses[i] == Variables::Input) {
            i++;
            j++;
        } else {
            i++;
        }
    }
    return i;
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
