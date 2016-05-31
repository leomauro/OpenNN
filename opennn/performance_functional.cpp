/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P E R F O R M A N C E   F U N C T I O N A L   C L A S S                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "performance_functional.h"


namespace OpenNN {

/// Default constructor.
/// It creates a performance functional object with all pointers initialized to NULL.
/// It also initializes all the rest of class members to their default values.
PerformanceFunctional::PerformanceFunctional()
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();
}

/// Neural network constructor.
/// It creates a performance functional object associated to a neural network object.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
PerformanceFunctional::PerformanceFunctional(NeuralNetwork *new_neural_network_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();
}

/// Neural network and data set constructor.
/// It creates a performance functional object associated to a neural network and a data set objects.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.
PerformanceFunctional::PerformanceFunctional(NeuralNetwork *new_neural_network_pointer,
                                             DataSet *new_data_set_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(new_data_set_pointer),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();

}

/// Neural network and mathematical model constructor.
/// It creates a performance functional object associated to a neural network and a mathematical model objects.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.

PerformanceFunctional::PerformanceFunctional(NeuralNetwork *new_neural_network_pointer,
                                             MathematicalModel *new_mathematical_model_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(NULL),
          mathematical_model_pointer(new_mathematical_model_pointer),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();
}

/// Neural network, mathematical model and data set constructor.
/// It creates a performance functional object associated to a neural network, a mathematical model and a data set objects.
/// The rest of pointers are initialized to NULL.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
/// @param new_data_set_pointer Pointer to a data set object.
PerformanceFunctional::PerformanceFunctional(NeuralNetwork *new_neural_network_pointer,
                                             MathematicalModel *new_mathematical_model_pointer,
                                             DataSet *new_data_set_pointer)
        : neural_network_pointer(new_neural_network_pointer),
          data_set_pointer(new_data_set_pointer),
          mathematical_model_pointer(new_mathematical_model_pointer),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();
}

/// Objective term constructor.
/// It creates a performance functional object with a given objective functional.
/// The rest of pointers are initialized to NULL.
/// The other members are set to their default values, but the objective term type, which is set to USER_PERFORMANCE_TERM.
PerformanceFunctional::PerformanceFunctional(PerformanceTerm *new_user_objective_pointer)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(new_user_objective_pointer),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    objective_type = USER_OBJECTIVE;
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();
}

/// File constructor.
/// It creates a performance functional object by loading its members from an XML-type file.
/// Please be careful with the format of that file, which is specified in the OpenNN manual.
/// @param file_name Name of performance functional file.
PerformanceFunctional::PerformanceFunctional(const std::string &file_name)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();

    load(file_name);
}

/// XML constructor.
/// It creates a performance functional object by loading its members from an XML document->
/// @param performance_functional_document Pointer to a TinyXML document containing the performance functional data.
PerformanceFunctional::PerformanceFunctional(const tinyxml2::XMLDocument &performance_functional_document)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL), mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    set_regularization_type(NO_REGULARIZATION);
    set_constraints_type(NO_CONSTRAINTS);

    set_default();

    from_XML(performance_functional_document);
}

/// Copy constructor.
/// It creates a copy of an existing performance functional object.
/// @param other_performance_functional Performance functional object to be copied.
/// @todo
PerformanceFunctional::PerformanceFunctional(const PerformanceFunctional &other_performance_functional)
        : neural_network_pointer(NULL),
          data_set_pointer(NULL),
          mathematical_model_pointer(NULL),
          sum_squared_error_objective_pointer(NULL),
          mean_squared_error_objective_pointer(NULL),
          root_mean_squared_error_objective_pointer(NULL),
          normalized_squared_error_objective_pointer(NULL),
          Minkowski_error_objective_pointer(NULL),
          cross_entropy_error_objective_pointer(NULL),
          weighted_squared_error_objective_pointer(NULL),
          roc_area_error_objective_pointer(NULL),
          outputs_integrals_objective_pointer(NULL),
          solutions_error_objective_pointer(NULL),
          final_solutions_error_objective_pointer(NULL),
          independent_parameters_error_objective_pointer(NULL),
          inverse_sum_squared_error_objective_pointer(NULL),
          user_objective_pointer(NULL),
          neural_parameters_norm_regularization_pointer(NULL),
          outputs_integrals_regularization_pointer(NULL),
          user_regularization_pointer(NULL),
          outputs_integrals_constraints_pointer(NULL),
          solutions_error_constraints_pointer(NULL),
          final_solutions_error_constraints_pointer(NULL),
          independent_parameters_error_constraints_pointer(NULL),
          user_constraints_pointer(NULL)
{
    neural_network_pointer = other_performance_functional.neural_network_pointer;
    data_set_pointer = other_performance_functional.data_set_pointer;
    mathematical_model_pointer = other_performance_functional.mathematical_model_pointer;

    objective_type = other_performance_functional.objective_type;
    regularization_type = other_performance_functional.regularization_type;
    constraints_type = other_performance_functional.constraints_type;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        sum_squared_error_objective_pointer = new SumSquaredError(*other_performance_functional.sum_squared_error_objective_pointer);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        mean_squared_error_objective_pointer = new MeanSquaredError(*other_performance_functional.mean_squared_error_objective_pointer);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        root_mean_squared_error_objective_pointer = new RootMeanSquaredError(*other_performance_functional.root_mean_squared_error_objective_pointer);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        normalized_squared_error_objective_pointer = new NormalizedSquaredError(*other_performance_functional.normalized_squared_error_objective_pointer);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        weighted_squared_error_objective_pointer = new WeightedSquaredError(*other_performance_functional.weighted_squared_error_objective_pointer);
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        roc_area_error_objective_pointer = new RocAreaError(*other_performance_functional.roc_area_error_objective_pointer);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Minkowski_error_objective_pointer = new MinkowskiError(*other_performance_functional.Minkowski_error_objective_pointer);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        cross_entropy_error_objective_pointer = new CrossEntropyError(*other_performance_functional.cross_entropy_error_objective_pointer);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        outputs_integrals_objective_pointer = new OutputsIntegrals(*other_performance_functional.outputs_integrals_objective_pointer);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        solutions_error_objective_pointer = new SolutionsError(*other_performance_functional.solutions_error_objective_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        final_solutions_error_objective_pointer = new FinalSolutionsError(*other_performance_functional.final_solutions_error_objective_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        independent_parameters_error_objective_pointer = new IndependentParametersError(*other_performance_functional.independent_parameters_error_objective_pointer);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        inverse_sum_squared_error_objective_pointer = new InverseSumSquaredError(*other_performance_functional.inverse_sum_squared_error_objective_pointer);
        break;

    case USER_OBJECTIVE:
        //user_objective_pointer = new PerformanceTerm(*other_performance_functional.user_objective_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Copy constructor.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        neural_parameters_norm_regularization_pointer = new NeuralParametersNorm(*other_performance_functional.neural_parameters_norm_regularization_pointer);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        outputs_integrals_regularization_pointer = new OutputsIntegrals(*other_performance_functional.outputs_integrals_regularization_pointer);
        break;

    case USER_REGULARIZATION:
        //user_regularization_pointer = new PerformanceTerm(*other_performance_functional.user_regularization_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Copy constructor.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        outputs_integrals_constraints_pointer = new OutputsIntegrals(*other_performance_functional.outputs_integrals_constraints_pointer);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        solutions_error_constraints_pointer = new SolutionsError(*other_performance_functional.solutions_error_constraints_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        final_solutions_error_constraints_pointer = new FinalSolutionsError(*other_performance_functional.final_solutions_error_constraints_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        independent_parameters_error_constraints_pointer = new IndependentParametersError(*other_performance_functional.independent_parameters_error_constraints_pointer);
        break;

    case USER_CONSTRAINTS:
        //user_constraints_pointer = new PerformanceTerm(*other_performance_functional.user_constraints_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Copy constructor.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    display = other_performance_functional.display;
}

/// Destructor.
/// It deletes the objective, regularization and constraints terms.
PerformanceFunctional::~PerformanceFunctional()
{
    // Delete objective terms
    delete sum_squared_error_objective_pointer;
    delete mean_squared_error_objective_pointer;
    delete root_mean_squared_error_objective_pointer;
    delete normalized_squared_error_objective_pointer;
    delete Minkowski_error_objective_pointer;
    delete cross_entropy_error_objective_pointer;
    delete weighted_squared_error_objective_pointer;
    delete outputs_integrals_objective_pointer;
    delete solutions_error_objective_pointer;
    delete final_solutions_error_objective_pointer;
    delete independent_parameters_error_objective_pointer;
    delete inverse_sum_squared_error_objective_pointer;
    delete user_objective_pointer;

    // Delete regularization terms
    delete neural_parameters_norm_regularization_pointer;
    delete outputs_integrals_regularization_pointer;
    delete user_regularization_pointer;

    // Delete constraints terms
    delete outputs_integrals_constraints_pointer;
    delete solutions_error_constraints_pointer;
    delete final_solutions_error_constraints_pointer;
    delete independent_parameters_error_constraints_pointer;
    delete user_constraints_pointer;
}

/// Returns true if this performance functional has a neural network associated,
/// and false otherwise.
bool PerformanceFunctional::has_neural_network() const
{
    return (bool) neural_network_pointer;
}

/// Returns true if this performance functional has a mathematical model associated,
/// and false otherwise.
bool PerformanceFunctional::has_mathematical_model() const
{
    return (bool) mathematical_model_pointer;
}

/// Returns true if this performance functional has a data set associated,
/// and false otherwise.
bool PerformanceFunctional::has_data_set() const
{
    return (bool) data_set_pointer;
}

/// Returns true if this performance functional has a selection method defined,
/// and false otherwise.
bool PerformanceFunctional::has_selection() const
{
    return data_set_pointer && data_set_pointer->get_instances().count_selection_instances_number() != 0;
}

/// Returns true if the performance functional can be expressed as the sum of squared terms.
/// Only those performance functionals are suitable for the Levenberg-Marquardt training algorithm.
bool PerformanceFunctional::is_sum_squared_terms() const
{
    if (objective_type == ROOT_MEAN_SQUARED_ERROR_OBJECTIVE ||
        objective_type == MINKOWSKI_ERROR_OBJECTIVE ||
        objective_type == CROSS_ENTROPY_ERROR_OBJECTIVE ||
        objective_type == OUTPUTS_INTEGRALS_OBJECTIVE ||
        objective_type == SOLUTIONS_ERROR_OBJECTIVE ||
        objective_type == FINAL_SOLUTIONS_ERROR_OBJECTIVE ||
        objective_type == INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE ||
        objective_type == INVERSE_SUM_SQUARED_ERROR_OBJECTIVE)
        return false;

    if (regularization_type == NEURAL_PARAMETERS_NORM_REGULARIZATION ||
        regularization_type == OUTPUTS_INTEGRALS_REGULARIZATION)
        return false;

    if (constraints_type == OUTPUTS_INTEGRALS_CONSTRAINTS ||
        constraints_type == SOLUTIONS_ERROR_CONSTRAINTS ||
        constraints_type == FINAL_SOLUTIONS_ERROR_CONSTRAINTS ||
        constraints_type == INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS)
        return false;

    return true;
}

/// Throws an exception if no neural network is associated to the performance functional.
void PerformanceFunctional::check_neural_network() const
{
    if (!neural_network_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void check_neural_network() const.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Throws an exception if the performance functional has not got any
/// objective, regularization or constraints terms.
void PerformanceFunctional::check_performance_terms() const
{
    if (objective_type == NO_OBJECTIVE &&
        regularization_type == NO_REGULARIZATION &&
        constraints_type == NO_CONSTRAINTS) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void check_performance_terms() const method.\n"
               << "None objective, regularization or constraints terms are used.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a pointer to the sum squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
SumSquaredError *PerformanceFunctional::get_sum_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!sum_squared_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "SumSquaredError* get_sum_squared_error_objective_pointer() const method.\n"
               << "Pointer to sum squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return sum_squared_error_objective_pointer;
}

/// Returns a pointer to the mean squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
MeanSquaredError *PerformanceFunctional::get_mean_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!mean_squared_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "MeanSquaredError* get_mean_squared_error_objective_pointer() const method.\n"
               << "Pointer to mean squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return mean_squared_error_objective_pointer;
}

/// Returns a pointer to the root mean squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
RootMeanSquaredError *PerformanceFunctional::get_root_mean_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!root_mean_squared_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "RootMeanSquaredError* get_root_mean_squared_error_objective_pointer() const method.\n"
               << "Pointer to root mean squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return root_mean_squared_error_objective_pointer;
}

/// Returns a pointer to the normalized squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
NormalizedSquaredError *PerformanceFunctional::get_normalized_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!normalized_squared_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "NormalizedSquaredError* get_normalized_squared_error_objective_pointer() const method.\n"
               << "Pointer to normalized squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return normalized_squared_error_objective_pointer;
}

/// Returns a pointer to the Minkowski error which is used as objective.
/// If that object does not exists, an exception is thrown.
MinkowskiError *PerformanceFunctional::get_Minkowski_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!Minkowski_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "MinkowskiError* get_Minkowski_error_objective_pointer() const method.\n"
               << "Pointer to Minkowski error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return Minkowski_error_objective_pointer;
}

/// Returns a pointer to the cross entropy error which is used as objective.
/// If that object does not exists, an exception is thrown.
CrossEntropyError *PerformanceFunctional::get_cross_entropy_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!cross_entropy_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "CrossEntropyError* get_cross_entropy_error_objective_pointer() const method.\n"
               << "Pointer to cross entropy error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return cross_entropy_error_objective_pointer;
}

/// Returns a pointer to the weighted squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
WeightedSquaredError *PerformanceFunctional::get_weighted_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!cross_entropy_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "WeightedSquaredError* get_weighted_squared_error_objective_pointer() const method.\n"
               << "Pointer to weighted squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return weighted_squared_error_objective_pointer;
}

/// Returns a pointer to the ROC area error which is used as objective.
/// If that object does not exists, an exception is thrown.
RocAreaError *PerformanceFunctional::get_roc_area_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!roc_area_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "RocAreaError* get_roc_area_error_objective_pointer() const method.\n"
               << "Pointer to ROC area error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return roc_area_error_objective_pointer;
}

/// Returns a pointer to the outputs integrals which is used as objective.
/// If that object does not exists, an exception is thrown.
OutputsIntegrals *PerformanceFunctional::get_outputs_integrals_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!outputs_integrals_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "OutputsIntegrals* get_outputs_integrals_objective_pointer() const method.\n"
               << "Pointer to outputs integrals objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return outputs_integrals_objective_pointer;
}

/// Returns a pointer to the solutions error which is used as objective.
/// If that object does not exists, an exception is thrown.
SolutionsError *PerformanceFunctional::get_solutions_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!solutions_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "SolutionsError* get_solutions_error_objective_pointer() const method.\n"
               << "Pointer to solutions error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return (solutions_error_objective_pointer);
}

/// Returns a pointer to the final solutions error which is used as objective.
/// If that object does not exists, an exception is thrown.
FinalSolutionsError *PerformanceFunctional::get_final_solutions_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!final_solutions_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "FinalSolutionsError* get_final_solutions_error_objective_pointer() const method.\n"
               << "Pointer to final solutions error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return final_solutions_error_objective_pointer;
}

/// Returns a pointer to the independent parameters error which is used as objective.
/// If that object does not exists, an exception is thrown.
IndependentParametersError *PerformanceFunctional::get_independent_parameters_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!independent_parameters_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "IndependentParametersError* get_independent_parameters_error_objective_pointer() const method.\n"
               << "Pointer to independent parameters error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return independent_parameters_error_objective_pointer;
}

/// Returns a pointer to the inverse sum squared error which is used as objective.
/// If that object does not exists, an exception is thrown.
InverseSumSquaredError *PerformanceFunctional::get_inverse_sum_squared_error_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!solutions_error_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "InverseSumSquaredError* get_inverse_sum_squared_error_objective_pointer() const method.\n"
               << "Pointer to inverse sum squared error objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return inverse_sum_squared_error_objective_pointer;
}

/// Returns a pointer to the user performance term which is used as objective.
/// If that object does not exists, an exception is thrown.
PerformanceTerm *PerformanceFunctional::get_user_objective_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!user_objective_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "PerformanceTerm* get_user_objective_pointer() const method.\n"
               << "Pointer to user objective is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return user_objective_pointer;
}

/// Returns a pointer to the neural parameters norm functional which is used as regularization.
/// If that object does not exists, an exception is thrown.
NeuralParametersNorm *PerformanceFunctional::get_neural_parameters_norm_regularization_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!neural_parameters_norm_regularization_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "NeuralParametersNorm* get_neural_parameters_norm_regularization_pointer() const method.\n"
               << "Pointer to neural parameters norm regularization is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return neural_parameters_norm_regularization_pointer;
}

/// Returns a pointer to the outputs integrals functional which is used as regularization.
/// If that object does not exists, an exception is thrown.
OutputsIntegrals *PerformanceFunctional::get_outputs_integrals_regularization_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!outputs_integrals_regularization_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "NeuralParametersNorm* get_outputs_integrals_regularization_pointer() const method.\n"
               << "Pointer to outputs integrals regularization is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return outputs_integrals_regularization_pointer;
}

/// Returns a pointer to the user regularization functional.
/// If that object does not exists, an exception is thrown.
PerformanceTerm *PerformanceFunctional::get_user_regularization_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!user_regularization_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "PerformanceTerm* get_user_regularization_pointer() const method.\n"
               << "Pointer to user regularization is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return user_regularization_pointer;
}

/// Returns a pointer to the outputs integrals which is used as constraints.
/// If that object does not exists, an exception is thrown.
OutputsIntegrals *PerformanceFunctional::get_outputs_integrals_constraints_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!outputs_integrals_constraints_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "OutputsIntegrals* get_outputs_integrals_constraints_pointer() const method.\n"
               << "Pointer to outputs integrals constraints is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return outputs_integrals_constraints_pointer;
}

/// Returns a pointer to the solutions error which is used as constraints.
/// If that object does not exists, an exception is thrown.
SolutionsError *PerformanceFunctional::get_solutions_error_constraints_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!solutions_error_constraints_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "SolutionsError* get_outputs_integrals_constraints_pointer() const method.\n"
               << "Pointer to solutions error constraints is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return solutions_error_constraints_pointer;
}

/// Returns a pointer to the final solutions error which is used as constraints.
/// If that object does not exists, an exception is thrown.
FinalSolutionsError *PerformanceFunctional::get_final_solutions_error_constraints_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!final_solutions_error_constraints_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "FinalSolutionsError* get_final_solutions_error_constraints_pointer() const method.\n"
               << "Pointer to final solutions error constraints is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return final_solutions_error_constraints_pointer;
}

/// Returns a pointer to the independent parameters error which is used as constraints.
/// If that object does not exists, an exception is thrown.
IndependentParametersError *PerformanceFunctional::get_independent_parameters_error_constraints_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!independent_parameters_error_constraints_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "IndependentParametersError* get_independent_parameters_error_constraints_pointer() const method.\n"
               << "Pointer to solutions error constraints is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return independent_parameters_error_constraints_pointer;
}

/// Returns a pointer to the user constraints functional.
/// If that object does not exists, an exception is thrown.
PerformanceTerm *PerformanceFunctional::get_user_constraints_pointer() const
{

#ifdef __OPENNN_DEBUG__
    if (!user_constraints_pointer) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "PerformanceTerm* get_user_constraints_pointer() const method.\n"
               << "Pointer to user constraints is NULL.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return user_constraints_pointer;
}

/// Returns the type of objective term used in the performance functional expression.
const PerformanceFunctional::ObjectiveType &PerformanceFunctional::get_objective_type() const
{
    return objective_type;
}

/// Returns the type of regularization term used in the performance functional expression.
const PerformanceFunctional::RegularizationType &PerformanceFunctional::get_regularization_type() const
{
    return regularization_type;
}

/// Returns the type of constraints term used in the performance functional expression.
const PerformanceFunctional::ConstraintsType &PerformanceFunctional::get_constraints_type() const
{
    return constraints_type;
}

/// Returns a string with the type of objective term used in the performance functional expression.
std::string PerformanceFunctional::write_objective_type() const
{
    if (objective_type == NO_OBJECTIVE)
        return "NO_OBJECTIVE";
    else if (objective_type == SUM_SQUARED_ERROR_OBJECTIVE)
        return "SUM_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == MEAN_SQUARED_ERROR_OBJECTIVE)
        return "MEAN_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == ROOT_MEAN_SQUARED_ERROR_OBJECTIVE)
        return "ROOT_MEAN_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == NORMALIZED_SQUARED_ERROR_OBJECTIVE)
        return "NORMALIZED_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == WEIGHTED_SQUARED_ERROR_OBJECTIVE)
        return "WEIGHTED_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == MINKOWSKI_ERROR_OBJECTIVE)
        return "MINKOWSKI_ERROR_OBJECTIVE";
    else if (objective_type == CROSS_ENTROPY_ERROR_OBJECTIVE)
        return "CROSS_ENTROPY_ERROR_OBJECTIVE";
    else if (objective_type == OUTPUTS_INTEGRALS_OBJECTIVE)
        return "OUTPUTS_INTEGRALS_OBJECTIVE";
    else if (objective_type == SOLUTIONS_ERROR_OBJECTIVE)
        return "SOLUTIONS_ERROR_OBJECTIVE";
    else if (objective_type == FINAL_SOLUTIONS_ERROR_OBJECTIVE)
        return "FINAL_SOLUTIONS_ERROR_OBJECTIVE";
    else if (objective_type == INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE)
        return "INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE";
    else if (objective_type == INVERSE_SUM_SQUARED_ERROR_OBJECTIVE)
        return "INVERSE_SUM_SQUARED_ERROR_OBJECTIVE";
    else if (objective_type == USER_OBJECTIVE)
        return "USER_OBJECTIVE";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_objective_type() const method.\n"
               << "Unknown objective type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string with the type of regularization term used in the performance functional expression.
std::string PerformanceFunctional::write_regularization_type() const
{
    if (regularization_type == NO_REGULARIZATION)
        return "NO_REGULARIZATION";
    else if (regularization_type == NEURAL_PARAMETERS_NORM_REGULARIZATION)
        return "NEURAL_PARAMETERS_NORM_REGULARIZATION";
    else if (regularization_type == OUTPUTS_INTEGRALS_REGULARIZATION)
        return "OUTPUTS_INTEGRALS_REGULARIZATION";
    else if (regularization_type == USER_REGULARIZATION)
        return "USER_REGULARIZATION_REGULARIZATION";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_regularization_type() const method.\n"
               << "Unknown regularization type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string with the type of constraints term used in the performance functional expression.
std::string PerformanceFunctional::write_constraints_type() const
{
    if (constraints_type == NO_CONSTRAINTS)
        return "NO_CONSTRAINTS";
    else if (constraints_type == OUTPUTS_INTEGRALS_CONSTRAINTS)
        return "OUTPUTS_INTEGRALS_CONSTRAINTS";
    else if (constraints_type == SOLUTIONS_ERROR_CONSTRAINTS)
        return "SOLUTIONS_ERROR_CONSTRAINTS";
    else if (constraints_type == FINAL_SOLUTIONS_ERROR_CONSTRAINTS)
        return "FINAL_SOLUTIONS_ERROR_CONSTRAINTS";
    else if (constraints_type == INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS)
        return "INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS";
    else if (constraints_type == USER_CONSTRAINTS)
        return "USER_CONSTRAINTS";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_constraints_type() const method.\n"
               << "Unknown constraints type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string in text format with the type of objective term used in the performance functional expression.
std::string PerformanceFunctional::write_objective_type_text() const
{
    if (objective_type == NO_OBJECTIVE)
        return "no objective";
    else if (objective_type == SUM_SQUARED_ERROR_OBJECTIVE)
        return "sum squared error";
    else if (objective_type == MEAN_SQUARED_ERROR_OBJECTIVE)
        return "mean squared error";
    else if (objective_type == ROOT_MEAN_SQUARED_ERROR_OBJECTIVE)
        return "root mean squared error";
    else if (objective_type == NORMALIZED_SQUARED_ERROR_OBJECTIVE)
        return "normalized squared error";
    else if (objective_type == WEIGHTED_SQUARED_ERROR_OBJECTIVE)
        return "weighted squared error";
    else if (objective_type == MINKOWSKI_ERROR_OBJECTIVE)
        return "Minkowski error";
    else if (objective_type == CROSS_ENTROPY_ERROR_OBJECTIVE)
        return "cross entropy error";
    else if (objective_type == OUTPUTS_INTEGRALS_OBJECTIVE)
        return "outputs integrals";
    else if (objective_type == SOLUTIONS_ERROR_OBJECTIVE)
        return "solutions error";
    else if (objective_type == FINAL_SOLUTIONS_ERROR_OBJECTIVE)
        return "final solutions error";
    else if (objective_type == INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE)
        return "independent parameters error";
    else if (objective_type == INVERSE_SUM_SQUARED_ERROR_OBJECTIVE)
        return "inverse sum squared error";
    else if (objective_type == USER_OBJECTIVE)
        return "user objective";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_objective_type_text() const method.\n"
               << "Unknown objective type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string in text format with the type of regularization term used in the performance functional expression.
std::string PerformanceFunctional::write_regularization_type_text() const
{
    if (regularization_type == NO_REGULARIZATION)
        return "no regularization";
    else if (regularization_type == NEURAL_PARAMETERS_NORM_REGULARIZATION)
        return "neural parameters norm";
    else if (regularization_type == OUTPUTS_INTEGRALS_REGULARIZATION)
        return "outputs integrals";
    else if (regularization_type == USER_REGULARIZATION)
        return "user regularization";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_regularization_type_text() const method.\n"
               << "Unknown regularization type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string in text format with the type of constraints term used in the performance functional expression.
std::string PerformanceFunctional::write_constraints_type_text() const
{
    if (constraints_type == NO_CONSTRAINTS)
        return "no constraints";
    else if (constraints_type == OUTPUTS_INTEGRALS_CONSTRAINTS)
        return "outputs integrals";
    else if (constraints_type == SOLUTIONS_ERROR_CONSTRAINTS)
        return "solutions error";
    else if (constraints_type == FINAL_SOLUTIONS_ERROR_CONSTRAINTS)
        return "fina solutions error";
    else if (constraints_type == INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS)
        return "independent parameters error";
    else if (constraints_type == USER_CONSTRAINTS)
        return "user constraints";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "std::string write_constraints_type_text() const method.\n"
               << "Unknown constraints type.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns true if messages from this class can be displayed on the screen, or false if messages
/// from this class can't be displayed on the screen.
const bool &PerformanceFunctional::get_display() const
{
    return display;
}

/// Sets a pointer to a multilayer perceptron object which is to be associated to the performance functional.
/// @param new_neural_network_pointer Pointer to a neural network object to be associated to the performance functional.
void PerformanceFunctional::set_neural_network_pointer(NeuralNetwork *new_neural_network_pointer)
{
    neural_network_pointer = new_neural_network_pointer;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        sum_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        mean_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        root_mean_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        normalized_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        weighted_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Minkowski_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        cross_entropy_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        outputs_integrals_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        solutions_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        final_solutions_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        independent_parameters_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        inverse_sum_squared_error_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case USER_OBJECTIVE:
        user_objective_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_neural_network_pointer(NeuralNetwork*) method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        neural_parameters_norm_regularization_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        outputs_integrals_regularization_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case USER_REGULARIZATION:
        user_regularization_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_neural_network_pointer(NeuralNetwork*) method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        outputs_integrals_constraints_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        solutions_error_constraints_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        final_solutions_error_constraints_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        independent_parameters_error_constraints_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    case USER_CONSTRAINTS:
        user_constraints_pointer->set_neural_network_pointer(new_neural_network_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_neural_network_pointer(NeuralNetwork*) method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Sets a new mathematical model on which it will be measured the performance functional.
/// @param new_mathematical_model_pointer Pointer to an external mathematical model object.
void PerformanceFunctional::set_mathematical_model_pointer(MathematicalModel *new_mathematical_model_pointer)
{
    mathematical_model_pointer = new_mathematical_model_pointer;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        sum_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        mean_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        root_mean_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        normalized_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        weighted_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Minkowski_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        cross_entropy_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        outputs_integrals_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        solutions_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        final_solutions_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        independent_parameters_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        inverse_sum_squared_error_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case USER_OBJECTIVE:
        user_objective_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_mathematical_model_pointer(MathematicalModel*) method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        neural_parameters_norm_regularization_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        outputs_integrals_regularization_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case USER_REGULARIZATION:
        user_regularization_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_mathematical_model_pointer(NeuralNetwork*) method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        outputs_integrals_constraints_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        solutions_error_constraints_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        final_solutions_error_constraints_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        independent_parameters_error_constraints_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    case USER_CONSTRAINTS:
        user_constraints_pointer->set_mathematical_model_pointer(new_mathematical_model_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_mathematical_model_pointer(NeuralNetwork*) method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Sets a new data set on which it will be measured the performance functional.
/// @param new_data_set_pointer Pointer to an external data set object.
void PerformanceFunctional::set_data_set_pointer(DataSet *new_data_set_pointer)
{
    data_set_pointer = new_data_set_pointer;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        sum_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        mean_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        root_mean_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        normalized_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        weighted_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        if (new_data_set_pointer == NULL)
            set_default();
        else if (new_data_set_pointer->empty())
            set_default();
        else
            weighted_squared_error_objective_pointer->set_weights();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Minkowski_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        cross_entropy_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        outputs_integrals_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        solutions_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        final_solutions_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        independent_parameters_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        inverse_sum_squared_error_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case USER_OBJECTIVE:
        user_objective_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_data_set_pointer(DataSet*) method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        neural_parameters_norm_regularization_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        outputs_integrals_regularization_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case USER_REGULARIZATION:
        user_regularization_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_data_set_pointer(DataSet*) method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        outputs_integrals_constraints_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        solutions_error_constraints_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        final_solutions_error_constraints_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        independent_parameters_error_constraints_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    case USER_CONSTRAINTS:
        user_constraints_pointer->set_data_set_pointer(new_data_set_pointer);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_data_set_pointer(DataSet*) method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Sets the objective term to be a specialized one provided by the user.
/// @param new_user_objective_pointer Pointer to a performance term object.

void PerformanceFunctional::set_user_objective_pointer(PerformanceTerm *new_user_objective_pointer)
{
    destruct_objective();
    objective_type = USER_OBJECTIVE;
    user_objective_pointer = new_user_objective_pointer;
}

/// Sets the regularization term to be a specialized one provided by the user.
/// @param new_user_regularization_pointer Pointer to a performance term object.
void PerformanceFunctional::set_user_regularization_pointer(PerformanceTerm *new_user_regularization_pointer)
{
    destruct_regularization();
    regularization_type = USER_REGULARIZATION;
    user_regularization_pointer = new_user_regularization_pointer;
}

/// Sets the constraints term to be a specialized one provided by the user.
/// @param new_user_constraints_pointer Pointer to a performance term object.
void PerformanceFunctional::set_user_constraints_pointer(PerformanceTerm *new_user_constraints_pointer)
{
    destruct_constraints();
    constraints_type = USER_CONSTRAINTS;
    user_constraints_pointer = new_user_constraints_pointer;
}

/// Sets the members of the performance functional object to their default values.
void PerformanceFunctional::set_default()
{
    display = true;
}

/// Sets a new type for the objective term from a string.
/// @param new_objective_type String with the type of objective term.
void PerformanceFunctional::set_objective_type(const std::string &new_objective_type)
{
    if (new_objective_type == "NO_OBJECTIVE")
        set_objective_type(NO_OBJECTIVE);
    else if (new_objective_type == "SUM_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(SUM_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "MEAN_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(MEAN_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "ROOT_MEAN_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(ROOT_MEAN_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "NORMALIZED_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(NORMALIZED_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "WEIGHTED_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(WEIGHTED_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "ROC_AREA_ERROR_OBJECTIVE")
        set_objective_type(ROC_AREA_ERROR_OBJECTIVE);
    else if (new_objective_type == "MINKOWSKI_ERROR_OBJECTIVE")
        set_objective_type(MINKOWSKI_ERROR_OBJECTIVE);
    else if (new_objective_type == "CROSS_ENTROPY_ERROR_OBJECTIVE")
        set_objective_type(CROSS_ENTROPY_ERROR_OBJECTIVE);
    else if (new_objective_type == "OUTPUTS_INTEGRALS_OBJECTIVE")
        set_objective_type(OUTPUTS_INTEGRALS_OBJECTIVE);
    else if (new_objective_type == "SOLUTIONS_ERROR_OBJECTIVE")
        set_objective_type(SOLUTIONS_ERROR_OBJECTIVE);
    else if (new_objective_type == "FINAL_SOLUTIONS_ERROR_OBJECTIVE")
        set_objective_type(FINAL_SOLUTIONS_ERROR_OBJECTIVE);
    else if (new_objective_type == "INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE")
        set_objective_type(INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE);
    else if (new_objective_type == "INVERSE_SUM_SQUARED_ERROR_OBJECTIVE")
        set_objective_type(INVERSE_SUM_SQUARED_ERROR_OBJECTIVE);
    else if (new_objective_type == "USER_OBJECTIVE")
        set_objective_type(USER_OBJECTIVE);
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void set_objective_type(const std::string&) method.\n"
               << "Unknown objective type: " << new_objective_type << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new type for the regularization term from a string.
/// @param new_regularization_type String with the type of regularization term.
void PerformanceFunctional::set_regularization_type(const std::string &new_regularization_type)
{
    if (new_regularization_type == "NO_REGULARIZATION")
        set_regularization_type(NO_REGULARIZATION);
    else if (new_regularization_type == "NEURAL_PARAMETERS_NORM_REGULARIZATION")
        set_regularization_type(NEURAL_PARAMETERS_NORM_REGULARIZATION);
    else if (new_regularization_type == "OUTPUTS_INTEGRALS_REGULARIZATION")
        set_regularization_type(OUTPUTS_INTEGRALS_REGULARIZATION);
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void set_regularization_type(const std::string&) method.\n"
               << "Unknown regularization type: " << new_regularization_type << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new type for the constraints term from a string.
/// @param new_constraints_type String with the type of constraints term.

void PerformanceFunctional::set_constraints_type(const std::string &new_constraints_type)
{
    if (new_constraints_type == "NO_CONSTRAINTS")
        set_constraints_type(NO_CONSTRAINTS);
    else if (new_constraints_type == "OUTPUTS_INTEGRALS_CONSTRAINTS")
        set_constraints_type(OUTPUTS_INTEGRALS_CONSTRAINTS);
    else if (new_constraints_type == "SOLUTIONS_ERROR_CONSTRAINTS")
        set_constraints_type(SOLUTIONS_ERROR_CONSTRAINTS);
    else if (new_constraints_type == "FINAL_SOLUTIONS_ERROR_CONSTRAINTS")
        set_constraints_type(FINAL_SOLUTIONS_ERROR_CONSTRAINTS);
    else if (new_constraints_type == "INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS")
        set_constraints_type(INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS);
    else if (new_constraints_type == "USER_CONSTRAINTS")
        set_constraints_type(USER_CONSTRAINTS);
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void set_constraints_type(const std::string&) method.\n"
               << "Unknown constraints term type: " << new_constraints_type << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void PerformanceFunctional::set_display(const bool &new_display)
{
    display = new_display;
}

/// Creates a new objective term inside the performance functional of a given performance term type.
/// @param new_objective_type Type of objective term to be created.
void PerformanceFunctional::set_objective_type(const ObjectiveType &new_objective_type)
{
    destruct_objective();
    objective_type = new_objective_type;

    switch (new_objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        sum_squared_error_objective_pointer = new SumSquaredError(neural_network_pointer, data_set_pointer);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        mean_squared_error_objective_pointer = new MeanSquaredError(neural_network_pointer, data_set_pointer);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        root_mean_squared_error_objective_pointer = new RootMeanSquaredError(neural_network_pointer, data_set_pointer);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        normalized_squared_error_objective_pointer = new NormalizedSquaredError(neural_network_pointer, data_set_pointer);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        weighted_squared_error_objective_pointer = new WeightedSquaredError(neural_network_pointer, data_set_pointer);
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        roc_area_error_objective_pointer = new RocAreaError(neural_network_pointer, data_set_pointer);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Minkowski_error_objective_pointer = new MinkowskiError(neural_network_pointer, data_set_pointer);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        cross_entropy_error_objective_pointer = new CrossEntropyError(neural_network_pointer, data_set_pointer);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        outputs_integrals_objective_pointer = new OutputsIntegrals(neural_network_pointer);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        solutions_error_objective_pointer = new SolutionsError(neural_network_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        final_solutions_error_objective_pointer = new FinalSolutionsError(neural_network_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        independent_parameters_error_objective_pointer = new IndependentParametersError(neural_network_pointer);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        inverse_sum_squared_error_objective_pointer = new InverseSumSquaredError(neural_network_pointer);
        break;

    case USER_OBJECTIVE:
        //user_objective_pointer = NULL;
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_objective_type(const ObjectiveType&) method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Creates a new regularization term inside the performance functional of a given performance term type.
/// @param new_regularization_type Type of regularization term to be created.
void PerformanceFunctional::set_regularization_type(const RegularizationType &new_regularization_type)
{
    destruct_regularization();
    regularization_type = new_regularization_type;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        neural_parameters_norm_regularization_pointer = new NeuralParametersNorm(neural_network_pointer);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        outputs_integrals_regularization_pointer = new OutputsIntegrals(neural_network_pointer);
        break;

    case USER_REGULARIZATION:
        //   regularization_pointer = NULL;
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_regularization_type(const RegularizationType&) method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Creates a new constraints term inside the performance functional of a given performance term type.
/// @param new_constraints_type Type of constraints term to be created.
void PerformanceFunctional::set_constraints_type(const ConstraintsType &new_constraints_type)
{
    destruct_constraints();
    constraints_type = new_constraints_type;

    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        outputs_integrals_constraints_pointer = new OutputsIntegrals(neural_network_pointer);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        solutions_error_constraints_pointer = new SolutionsError(neural_network_pointer);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        final_solutions_error_constraints_pointer = new FinalSolutionsError(neural_network_pointer);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        independent_parameters_error_constraints_pointer = new IndependentParametersError(neural_network_pointer);
        break;

    case USER_CONSTRAINTS:
        user_constraints_pointer = NULL;
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "void set_constraints_type(const ConstraintsType&) method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// This method deletes the objective term object.
/// It also sets the objective term type to NONE and the corresponding flag to false.

void PerformanceFunctional::destruct_objective()
{
    delete sum_squared_error_objective_pointer;
    delete mean_squared_error_objective_pointer;
    delete root_mean_squared_error_objective_pointer;
    delete normalized_squared_error_objective_pointer;
    delete Minkowski_error_objective_pointer;
    delete cross_entropy_error_objective_pointer;
    delete outputs_integrals_objective_pointer;
    delete solutions_error_objective_pointer;
    delete final_solutions_error_objective_pointer;
    delete independent_parameters_error_objective_pointer;
    delete inverse_sum_squared_error_objective_pointer;
    delete user_objective_pointer;

    sum_squared_error_objective_pointer = NULL;
    mean_squared_error_objective_pointer = NULL;
    root_mean_squared_error_objective_pointer = NULL;
    normalized_squared_error_objective_pointer = NULL;
    Minkowski_error_objective_pointer = NULL;
    cross_entropy_error_objective_pointer = NULL;
    outputs_integrals_objective_pointer = NULL;
    solutions_error_objective_pointer = NULL;
    final_solutions_error_objective_pointer = NULL;
    independent_parameters_error_objective_pointer = NULL;
    inverse_sum_squared_error_objective_pointer = NULL;
    user_objective_pointer = NULL;

    objective_type = NO_OBJECTIVE;
}

/// This method deletes the regularization term object.
/// It also sets the regularization term type to NONE and the corresponding flag to false.
void PerformanceFunctional::destruct_regularization()
{
    delete neural_parameters_norm_regularization_pointer;
    delete outputs_integrals_regularization_pointer;
    delete user_regularization_pointer;

    neural_parameters_norm_regularization_pointer = NULL;
    outputs_integrals_regularization_pointer = NULL;
    user_regularization_pointer = NULL;

    regularization_type = NO_REGULARIZATION;
}

/// This method deletes the constraints term object.
/// It also sets the constraints term type to NONE and the corresponding flag to false.
void PerformanceFunctional::destruct_constraints()
{
    delete outputs_integrals_constraints_pointer;
    delete solutions_error_constraints_pointer;
    delete final_solutions_error_constraints_pointer;
    delete independent_parameters_error_constraints_pointer;
    delete user_constraints_pointer;

    outputs_integrals_constraints_pointer = NULL;
    solutions_error_constraints_pointer = NULL;
    final_solutions_error_constraints_pointer = NULL;
    independent_parameters_error_constraints_pointer = NULL;
    user_constraints_pointer = NULL;

    constraints_type = NO_CONSTRAINTS;
}

/// This method destructs the objective, regularization and constraints terms.
void PerformanceFunctional::destruct_all_terms()
{
    destruct_objective();
    destruct_regularization();
    destruct_constraints();
}

/// Returns the objective evaluation,
/// according to the respective objective type used in the performance functional expression.
double PerformanceFunctional::calculate_objective() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double objective = 0.0;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        objective = sum_squared_error_objective_pointer->calculate_performance();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        objective = mean_squared_error_objective_pointer->calculate_performance();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        objective = root_mean_squared_error_objective_pointer->calculate_performance();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        objective = normalized_squared_error_objective_pointer->calculate_performance();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        objective = weighted_squared_error_objective_pointer->calculate_performance();
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        objective = roc_area_error_objective_pointer->calculate_performance();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        objective = Minkowski_error_objective_pointer->calculate_performance();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        objective = cross_entropy_error_objective_pointer->calculate_performance();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        objective = outputs_integrals_objective_pointer->calculate_performance();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        objective = solutions_error_objective_pointer->calculate_performance();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        objective = final_solutions_error_objective_pointer->calculate_performance();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        objective = independent_parameters_error_objective_pointer->calculate_performance();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        objective = inverse_sum_squared_error_objective_pointer->calculate_performance();
        break;

    case USER_OBJECTIVE:
        objective = user_objective_pointer->calculate_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_objective() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return objective;
}

/// Returns the objective evaluation,
/// according to the respective objective type used in the performance functional expression.
double PerformanceFunctional::calculate_objective(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double objective = 0.0;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        objective = sum_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        objective = mean_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        objective = root_mean_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        objective = normalized_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        objective = weighted_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        objective = roc_area_error_objective_pointer->calculate_performance(parameters);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        objective = Minkowski_error_objective_pointer->calculate_performance(parameters);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        objective = cross_entropy_error_objective_pointer->calculate_performance(parameters);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        objective = outputs_integrals_objective_pointer->calculate_performance(parameters);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        objective = solutions_error_objective_pointer->calculate_performance(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        //objective = final_solutions_error_objective_pointer->calculate_performance(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        objective = independent_parameters_error_objective_pointer->calculate_performance(parameters);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        objective = inverse_sum_squared_error_objective_pointer->calculate_performance(parameters);
        break;

    case USER_OBJECTIVE:
        objective = user_objective_pointer->calculate_performance(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_objective(const Vector<double>&) const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return objective;
}

/// Returns the regularization evaluation,
/// according to the respective regularization type used in the performance functional expression.
double PerformanceFunctional::calculate_regularization() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double regularization = 0.0;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        regularization = neural_parameters_norm_regularization_pointer->calculate_performance();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        regularization = outputs_integrals_regularization_pointer->calculate_performance();
        break;

    case USER_REGULARIZATION:
        regularization = user_regularization_pointer->calculate_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_regularization() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return regularization;
}

/// Returns the regularization evaluation,
/// according to the respective regularization type used in the performance functional expression.
double PerformanceFunctional::calculate_regularization(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double regularization = 0.0;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        regularization = neural_parameters_norm_regularization_pointer->calculate_performance(parameters);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        regularization = outputs_integrals_regularization_pointer->calculate_performance(parameters);
        break;

    case USER_REGULARIZATION:
        regularization = user_regularization_pointer->calculate_performance(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_regularization(const Vector<double>&) const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return regularization;
}

/// Returns the constraints evaluation,
/// according to the respective constraints type used in the performance functional expression.
double PerformanceFunctional::calculate_constraints() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double constraints = 0.0;

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        constraints = outputs_integrals_constraints_pointer->calculate_performance();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        constraints = solutions_error_constraints_pointer->calculate_performance();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        constraints = final_solutions_error_constraints_pointer->calculate_performance();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        constraints = independent_parameters_error_constraints_pointer->calculate_performance();
        break;

    case USER_CONSTRAINTS:
        constraints = user_constraints_pointer->calculate_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_constraints() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return constraints;
}

/// Returns the constraints evaluation,
/// according to the respective constraints type used in the performance functional expression.
double PerformanceFunctional::calculate_constraints(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    double constraints = 0.0;

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        constraints = outputs_integrals_constraints_pointer->calculate_performance(parameters);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        constraints = solutions_error_constraints_pointer->calculate_performance(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        //constraints = final_solutions_error_constraints_pointer->calculate_performance(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        constraints = independent_parameters_error_constraints_pointer->calculate_performance(parameters);
        break;

    case USER_CONSTRAINTS:
        constraints = user_constraints_pointer->calculate_performance(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_constraints(const Vector<double>&) const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return constraints;
}

/// Returns the evaluation of all the objective terms,
/// according to the respective objective type used in the performance functional expression.
/// Note that this function is only defined when the objective can be expressed as a sum of squared terms.
Vector<double> PerformanceFunctional::calculate_objective_terms() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const Instances &instances = data_set_pointer->get_instances();
    const size_t training_instances_number = instances.count_training_instances_number();
    Vector<double> objective_terms(training_instances_number, 0.0);

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        objective_terms = sum_squared_error_objective_pointer->calculate_terms();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        objective_terms = mean_squared_error_objective_pointer->calculate_terms();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for root mean squared error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        objective_terms = normalized_squared_error_objective_pointer->calculate_terms();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        objective_terms = weighted_squared_error_objective_pointer->calculate_terms();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for Minkowski error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for cross-entropy error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals objective.\n";

            throw std::logic_error(buffer.str());
        }

    case SOLUTIONS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for solutions error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for final solutions error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for independent parameters error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Cannot calculate performance terms for inverse sum squared error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case USER_OBJECTIVE:
        objective_terms = user_objective_pointer->calculate_terms();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_terms() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return objective_terms;
}

// @todo
Vector<double> PerformanceFunctional::calculate_regularization_terms() const
{
    Vector<double> regularization_terms;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_regularization_terms() const method.\n"
                   << "Cannot calculate performance terms for neural parameters norm.\n";

            throw std::logic_error(buffer.str());
        }

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_regularization_terms() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals.\n";

            throw std::logic_error(buffer.str());
        }

    case USER_REGULARIZATION:
        regularization_terms = user_regularization_pointer->calculate_terms();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_regularization_terms() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return regularization_terms;
}

// @todo
Vector<double> PerformanceFunctional::calculate_constraints_terms() const
{
    Vector<double> constraints_terms;

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_terms() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals.\n";

            throw std::logic_error(buffer.str());
        }

    case SOLUTIONS_ERROR_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_terms() const method.\n"
                   << "Cannot calculate performance terms for solutions error.\n";

            throw std::logic_error(buffer.str());
        }

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_terms() const method.\n"
                   << "Cannot calculate performance terms for final solutions error.\n";

            throw std::logic_error(buffer.str());
        }

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS: {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
        << "Vector<double> calculate_constraints_terms() const method.\n"
        << "Cannot calculate performance terms for independent parameters error.\n";

        throw std::logic_error(buffer.str());
    }
        break;

    case USER_CONSTRAINTS:
        constraints_terms = user_constraints_pointer->calculate_terms();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_terms() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return constraints_terms;
}

/// Returns the Jacobian of the objective terms function,
/// according to the objective type used in the performance functional expression.
/// Note that this function is only defined when the objective can be expressed as a sum of squared terms.
/// The Jacobian elements are the partial derivatives of a single term with respect to a single parameter.
/// The number of rows in the Jacobian matrix are the number of parameters,
/// and the number of columns the number of terms composing the objective.

Matrix<double> PerformanceFunctional::calculate_objective_terms_Jacobian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    Matrix<double> objective_terms_Jacobian;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        objective_terms_Jacobian = sum_squared_error_objective_pointer->calculate_terms_Jacobian();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        objective_terms_Jacobian = mean_squared_error_objective_pointer->calculate_terms_Jacobian();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for root mean squared error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        objective_terms_Jacobian = normalized_squared_error_objective_pointer->calculate_terms_Jacobian();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        objective_terms_Jacobian = weighted_squared_error_objective_pointer->calculate_terms_Jacobian();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for Minkowski error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for cross-entropy error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals objective.\n";

            throw std::logic_error(buffer.str());
        }

    case SOLUTIONS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for solutions error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for final solutions error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for independent parameters error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for inverse sum squared error objective.\n";

            throw std::logic_error(buffer.str());
        }

    case USER_OBJECTIVE:
        objective_terms_Jacobian = user_objective_pointer->calculate_terms_Jacobian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_terms_Jacobian() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return objective_terms_Jacobian;
}

/// Returns the Jacobian of the regularization terms function,
/// according to the regularization type used in the performance functional expression.
/// Note that this function is only defined when the objective can be expressed as a sum of squared terms.
/// The Jacobian elements are the partial derivatives of a single term with respect to a single parameter.
/// The number of rows in the Jacobian matrix are the number of parameters,
/// and the number of columns the number of terms composing the regularization.
Matrix<double> PerformanceFunctional::calculate_regularization_terms_Jacobian() const
{
    Matrix<double> regularization_terms_Jacobian;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_regularization_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for neural parameters norm.\n";

            throw std::logic_error(buffer.str());
        }

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_regularization_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals.\n";

            throw std::logic_error(buffer.str());
        }

    case USER_REGULARIZATION:
        regularization_terms_Jacobian = user_regularization_pointer->calculate_terms_Jacobian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_regularization_terms_Jacobian() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return regularization_terms_Jacobian;
}

/// Returns the Jacobian of the constraints terms function,
/// according to the constraints type used in the performance functional expression.
/// Note that this function is only defined when the objective can be expressed as a sum of squared terms.
/// The Jacobian elements are the partial derivatives of a single term with respect to a single parameter.
/// The number of rows in the Jacobian matrix are the number of parameters,
/// and the number of columns the number of terms composing the constraints.
Matrix<double> PerformanceFunctional::calculate_constraints_terms_Jacobian() const
{
    Matrix<double> constraints_terms_Jacobian;

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for outputs integrals.\n";

            throw std::logic_error(buffer.str());
        }

    case SOLUTIONS_ERROR_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for solutions error.\n";

            throw std::logic_error(buffer.str());
        }

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for final solutions error.\n";

            throw std::logic_error(buffer.str());
        }

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_terms_Jacobian() const method.\n"
                   << "Cannot calculate performance terms for independent parameters error.\n";

            throw std::logic_error(buffer.str());
        }

    case USER_CONSTRAINTS:
        constraints_terms_Jacobian = user_constraints_pointer->calculate_terms_Jacobian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_terms_Jacobian() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return constraints_terms_Jacobian;
}

/// Returns the gradient of the objective, according to the objective type.
/// That gradient is the vector of partial derivatives of the objective with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_objective_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        gradient = sum_squared_error_objective_pointer->calculate_gradient();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        gradient = mean_squared_error_objective_pointer->calculate_gradient();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        gradient = root_mean_squared_error_objective_pointer->calculate_gradient();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        gradient = normalized_squared_error_objective_pointer->calculate_gradient();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        gradient = weighted_squared_error_objective_pointer->calculate_gradient();
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        gradient = roc_area_error_objective_pointer->calculate_gradient();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        gradient = Minkowski_error_objective_pointer->calculate_gradient();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        gradient = cross_entropy_error_objective_pointer->calculate_gradient();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        gradient = outputs_integrals_objective_pointer->calculate_gradient();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        gradient = solutions_error_objective_pointer->calculate_gradient();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        gradient = final_solutions_error_objective_pointer->calculate_gradient();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        gradient = independent_parameters_error_objective_pointer->calculate_gradient();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        gradient = inverse_sum_squared_error_objective_pointer->calculate_gradient();
        break;

    case USER_OBJECTIVE:
        gradient = user_objective_pointer->calculate_gradient();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_gradient() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return gradient;
}

/// Returns the gradient of the objective, according to the objective type.
/// That gradient is the vector of partial derivatives of the objective with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_objective_gradient(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        //gradient = sum_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        //gradient = mean_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        //gradient = root_mean_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        //gradient = normalized_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        //gradient = weighted_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        //gradient = Minkowski_error_objective_pointer->calculate_gradient(parameters);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        //gradient = cross_entropy_error_objective_pointer->calculate_gradient(parameters);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        //gradient = outputs_integrals_objective_pointer->calculate_gradient(parameters);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        gradient = solutions_error_objective_pointer->calculate_gradient(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        gradient = final_solutions_error_objective_pointer->calculate_gradient(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        //gradient = independent_parameters_error_objective_pointer->calculate_gradient(parameters);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        gradient = inverse_sum_squared_error_objective_pointer->calculate_gradient(parameters);
        break;

    case USER_OBJECTIVE:
        gradient = user_objective_pointer->calculate_gradient(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_objective_gradient(const Vector<double>&) const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return gradient;
}

/// Returns the gradient of the regularization, according to the regularization type.
/// That gradient is the vector of partial derivatives of the regularization with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_regularization_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        gradient = neural_parameters_norm_regularization_pointer->calculate_gradient();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        gradient = outputs_integrals_regularization_pointer->calculate_gradient();
        break;

    case USER_REGULARIZATION:
        gradient = user_regularization_pointer->calculate_gradient();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_regularization_gradient() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return gradient;
}

/// Returns the gradient of the regularization, according to the regularization type.
/// That gradient is the vector of partial derivatives of the regularization with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_regularization_gradient(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        //gradient = neural_parameters_norm_regularization_pointer->calculate_gradient(parameters);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        //gradient = outputs_integrals_regularization_pointer->calculate_gradient(parameters);
        break;

    case USER_REGULARIZATION:
        gradient = user_regularization_pointer->calculate_gradient(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_regularization_gradient(const Vector<double>&) const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return gradient;
}

/// Returns the gradient of the constraints, according to the objective type.
/// That gradient is the vector of partial derivatives of the constraints with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_constraints_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        gradient = outputs_integrals_constraints_pointer->calculate_gradient();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        gradient = solutions_error_constraints_pointer->calculate_gradient();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        gradient = final_solutions_error_constraints_pointer->calculate_gradient();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        gradient = independent_parameters_error_constraints_pointer->calculate_gradient();
        break;

    case USER_CONSTRAINTS:
        gradient = user_constraints_pointer->calculate_gradient();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_gradient() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return gradient;
}

/// Returns the gradient of the constraints, according to the objective type.
/// That gradient is the vector of partial derivatives of the constraints with respect to the parameters.
/// The size is thus the number of parameters.
Vector<double> PerformanceFunctional::calculate_constraints_gradient(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Vector<double> gradient(parameters_number, 0.0);

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        //gradient = outputs_integrals_constraints_pointer->calculate_gradient(parameters);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        gradient = solutions_error_constraints_pointer->calculate_gradient(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        gradient = final_solutions_error_constraints_pointer->calculate_gradient(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        //gradient = independent_parameters_error_constraints_pointer->calculate_gradient(parameters);
        break;

    case USER_CONSTRAINTS:
        gradient = user_constraints_pointer->calculate_gradient(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Vector<double> calculate_constraints_gradient(const Vector<double>&) const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
        break;
    }

    return gradient;
}

/// Returns the Hessian of the objective, according to the objective type.
/// That Hessian is the matrix of second partial derivatives of the objective with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
Matrix<double> PerformanceFunctional::calculate_objective_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Objectiv
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        Hessian = sum_squared_error_objective_pointer->calculate_Hessian();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        Hessian = mean_squared_error_objective_pointer->calculate_Hessian();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        Hessian = root_mean_squared_error_objective_pointer->calculate_Hessian();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        Hessian = normalized_squared_error_objective_pointer->calculate_Hessian();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        Hessian = weighted_squared_error_objective_pointer->calculate_Hessian();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        Hessian = Minkowski_error_objective_pointer->calculate_Hessian();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        Hessian = cross_entropy_error_objective_pointer->calculate_Hessian();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        Hessian = outputs_integrals_objective_pointer->calculate_Hessian();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        Hessian = solutions_error_objective_pointer->calculate_Hessian();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        Hessian = final_solutions_error_objective_pointer->calculate_Hessian();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        Hessian = independent_parameters_error_objective_pointer->calculate_Hessian();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        Hessian = inverse_sum_squared_error_objective_pointer->calculate_Hessian();
        break;

    case USER_OBJECTIVE:
        Hessian = user_objective_pointer->calculate_Hessian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "Matrix<double> Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_Hessian() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Returns the Hessian of the objective, according to the objective type.
/// That Hessian is the matrix of second partial derivatives of the objective with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
/// @todo
Matrix<double> PerformanceFunctional::calculate_objective_Hessian(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        Hessian = sum_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        //Hessian = mean_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        //Hessian = root_mean_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        //Hessian = normalized_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        //Hessian = weighted_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        //Hessian = Minkowski_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        //Hessian = cross_entropy_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        //Hessian = outputs_integrals_objective_pointer->calculate_Hessian(parameters);
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        //Hessian = solutions_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        //Hessian = final_solutions_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        //Hessian = independent_parameters_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        //Hessian = inverse_sum_squared_error_objective_pointer->calculate_Hessian(parameters);
        break;

    case USER_OBJECTIVE:
        //Hessian = user_objective_pointer->calculate_Hessian(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "Matrix<double> Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_objective_Hessian(const Vector<double>&) const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Returns the Hessian of the regularization, according to the regularization type.
/// That Hessian is the matrix of second partial derivatives of the regularization with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
Matrix<double> PerformanceFunctional::calculate_regularization_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        Hessian = neural_parameters_norm_regularization_pointer->calculate_Hessian();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        Hessian = outputs_integrals_regularization_pointer->calculate_Hessian();
        break;

    case USER_REGULARIZATION:
        Hessian = user_regularization_pointer->calculate_Hessian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_regularization_Hessian() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Returns the Hessian of the regularization, according to the regularization type.
/// That Hessian is the matrix of second partial derivatives of the regularization with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
/// @todo
Matrix<double> PerformanceFunctional::calculate_regularization_Hessian(const Vector<double> &) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        //Hessian = neural_parameters_norm_regularization_pointer->calculate_Hessian(parameters);
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        //Hessian = outputs_integrals_regularization_pointer->calculate_Hessian(parameters);
        break;

    case USER_REGULARIZATION:
        //Hessian = user_regularization_pointer->calculate_Hessian(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_regularization_Hessian(const Vector<double>&) const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Returns the Hessian of the constraints, according to the constraints type.
/// That Hessian is the matrix of second partial derivatives of the constraints with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
Matrix<double> PerformanceFunctional::calculate_constraints_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        Hessian = outputs_integrals_constraints_pointer->calculate_Hessian();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        Hessian = solutions_error_constraints_pointer->calculate_Hessian();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        Hessian = final_solutions_error_constraints_pointer->calculate_Hessian();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        Hessian = independent_parameters_error_constraints_pointer->calculate_Hessian();
        break;

    case USER_CONSTRAINTS:
        Hessian = user_constraints_pointer->calculate_Hessian();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_Hessian() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Returns the Hessian of the constraints, according to the constraints type.
/// That Hessian is the matrix of second partial derivatives of the constraints with respect to the parameters.
/// That matrix is symmetric, with size the number of parameters.
/// @todo
Matrix<double> PerformanceFunctional::calculate_constraints_Hessian(const Vector<double> &) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
#endif

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        //Hessian = outputs_integrals_constraints_pointer->calculate_Hessian(parameters);
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        //Hessian = solutions_error_constraints_pointer->calculate_Hessian(parameters);
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        //Hessian = final_solutions_error_constraints_pointer->calculate_Hessian(parameters);
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        //Hessian = independent_parameters_error_constraints_pointer->calculate_Hessian(parameters);
        break;

    case USER_CONSTRAINTS:
        //Hessian = user_constraints_pointer->calculate_Hessian(parameters);
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "Matrix<double> calculate_constraints_Hessian(const Vector<double>&) const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return Hessian;
}

/// Calculates the evaluation value of the performance functional,
/// as the sum of the objective, regularization and constraints functionals.
double PerformanceFunctional::calculate_performance() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    return calculate_objective() + calculate_regularization() + calculate_constraints();
}

/// Returns the performance of a neural network for a given vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of parameters for the neural network associated to the performance functional.
double PerformanceFunctional::calculate_performance(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();

    const size_t size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "double calculate_performance(const Vector<double>&) method.\n"
               << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_objective(parameters) + calculate_regularization(parameters) + calculate_constraints(parameters);
}

/// Returns the evaluation of the objective term on the selection instances of the associated data set.
double PerformanceFunctional::calculate_selection_objective() const
{
    double selection_objective = 0.0;

    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        selection_objective = sum_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        selection_objective = mean_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        selection_objective = root_mean_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        selection_objective = normalized_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        selection_objective = weighted_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        selection_objective = roc_area_error_objective_pointer->calculate_selection_performance();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        selection_objective = Minkowski_error_objective_pointer->calculate_selection_performance();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        selection_objective = cross_entropy_error_objective_pointer->calculate_selection_performance();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        selection_objective = outputs_integrals_objective_pointer->calculate_selection_performance();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        selection_objective = solutions_error_objective_pointer->calculate_selection_performance();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        selection_objective = final_solutions_error_objective_pointer->calculate_selection_performance();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        selection_objective = independent_parameters_error_objective_pointer->calculate_selection_performance();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        selection_objective = inverse_sum_squared_error_objective_pointer->calculate_selection_performance();
        break;

    case USER_OBJECTIVE:
        selection_objective = user_objective_pointer->calculate_selection_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_selection_objective() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return selection_objective;
}

/// Returns the evaluation of the regularization term on the selection instances of the associated data set.
double PerformanceFunctional::calculate_selection_regularization() const
{
    double selection_regularization = 0.0;

    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        selection_regularization = neural_parameters_norm_regularization_pointer->calculate_selection_performance();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        selection_regularization = outputs_integrals_regularization_pointer->calculate_selection_performance();
        break;

    case USER_REGULARIZATION:
        selection_regularization = user_regularization_pointer->calculate_selection_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_selection_regularization() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return selection_regularization;
}

/// Returns the evaluation of the constraints term on the selection instances of the associated data set.
double PerformanceFunctional::calculate_selection_constraints() const
{
    double selection_constraints = 0.0;

    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        selection_constraints = outputs_integrals_constraints_pointer->calculate_selection_performance();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        selection_constraints = solutions_error_constraints_pointer->calculate_selection_performance();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        selection_constraints = final_solutions_error_constraints_pointer->calculate_selection_performance();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        selection_constraints = independent_parameters_error_constraints_pointer->calculate_selection_performance();
        break;

    case USER_CONSTRAINTS:
        selection_constraints = user_constraints_pointer->calculate_selection_performance();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "double calculate_selection_constraints() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return selection_constraints;
}

/// Calculates the selection performance,
/// as the sum of the objective and the regularization terms.
double PerformanceFunctional::calculate_selection_performance() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    return calculate_selection_objective() /*+
           calculate_selection_regularization() +
           calculate_selection_constraints() */;
}

/// Returns the performance function gradient, as the sum of the objective and the regularization gradient vectors.
Vector<double> PerformanceFunctional::calculate_gradient() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();

    check_performance_terms();
#endif

    return calculate_objective_gradient() +
           calculate_regularization_gradient() +
           calculate_constraints_gradient();
}

/// Returns the performance gradient for a given vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of parameters for the neural network associated to the performance functional.
Vector<double> PerformanceFunctional::calculate_gradient(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();

    const size_t parameters_number = neural_network_pointer->count_parameters_number();
    const size_t size = parameters.size();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "Vector<double> calculate_gradient(const Vector<double>&) const method.\n"
               << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_objective_gradient(parameters) +
           calculate_regularization_gradient(parameters) +
           calculate_constraints_gradient(parameters);
}

/// Returns the default objective function Hessian matrix,
/// which is computed as the sum of the objective, regularization and constraints Hessians.
Matrix<double> PerformanceFunctional::calculate_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    return calculate_objective_Hessian() +
           calculate_regularization_Hessian() +
           calculate_constraints_Hessian();
}

/// Returns which would be the objective function Hessian of a neural network for an
/// hypothetical vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of potential parameters for the neural network associated
/// to this performance functional.
Matrix<double> PerformanceFunctional::calculate_Hessian(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();

    const size_t size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "double calculate_Hessian(const Vector<double>&) method.\n"
               << "Size must be equal to number of parameters.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return calculate_objective_Hessian(parameters) +
           calculate_regularization_Hessian(parameters) +
           calculate_constraints_Hessian(parameters);
}

/// Evaluates the objective, regularization and constraints terms functions,
/// and returns the total performance terms as the assembly of that three vectors.
Vector<double> PerformanceFunctional::calculate_terms() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();

    check_performance_terms();
#endif

    const Vector<double> objective_terms = calculate_objective_terms();
    const Vector<double> regularization_terms = calculate_regularization_terms();
    const Vector<double> constraints_terms = calculate_constraints_terms();

    return objective_terms.assemble(regularization_terms).assemble(constraints_terms);
}

// @todo
Matrix<double> PerformanceFunctional::calculate_terms_Jacobian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    const Matrix<double> objective_terms_Jacobian = calculate_objective_terms_Jacobian();

//    const Matrix<double> regularization_terms_Jacobian = calculate_regularization_terms_Jacobian();
//    const Matrix<double> constraints_terms_Jacobian = calculate_constraints_terms_Jacobian();
//    Matrix<double> terms_Jacobian;
//    if (!objective_terms_Jacobian.empty())
//        terms_Jacobian = objective_terms_Jacobian;

    return objective_terms_Jacobian;
}

/// Returns inverse matrix of the Hessian.
/// It first computes the Hessian matrix and then computes its inverse.
// @todo
Matrix<double> PerformanceFunctional::calculate_inverse_Hessian() const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    const Matrix<double> Hessian = calculate_Hessian();
    return Hessian.calculate_LU_inverse();
}

/// Returns the default product of some vector with the objective function Hessian matrix, which is
/// computed using numerical differentiation.
/// @param vector Vector in the dot product.
// @todo
Vector<double> PerformanceFunctional::calculate_vector_dot_Hessian(const Vector<double> &vector) const
{

#ifdef __OPENNN_DEBUG__
    check_neural_network();
    check_performance_terms();
#endif

    const size_t size = vector.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "Vector<double> calculate_vector_dot_Hessian(Vector<double>) method.\n"
               << "Size of vector must be equal to number of parameters.\n";

        throw std::logic_error(buffer.str());
    }

    // Calculate vector Hessian product
    Vector<double> vector_Hessian_product(parameters_number);
    return vector_Hessian_product;
}

/// Returns a zero order performance structure, which just contains the performance value of the performance function.
PerformanceFunctional::ZeroOrderperformance PerformanceFunctional::calculate_zero_order_performance() const
{
    ZeroOrderperformance zero_order_performance;
    zero_order_performance.performance = calculate_performance();
    return zero_order_performance;
}

/// Returns a first order performance structure, which contains the value and the gradient of the performance function.
PerformanceFunctional::FirstOrderperformance PerformanceFunctional::calculate_first_order_performance() const
{
    FirstOrderperformance first_order_performance;
    first_order_performance.performance = calculate_performance();
    first_order_performance.gradient = calculate_gradient();
    return first_order_performance;
}

/// Returns a second order performance structure, which contains the value, the gradient and the Hessian of the performance function.
PerformanceFunctional::SecondOrderperformance PerformanceFunctional::calculate_second_order_performance() const
{
    SecondOrderperformance second_order_performance;
    second_order_performance.performance = calculate_performance();
    second_order_performance.gradient = calculate_gradient();
    second_order_performance.Hessian = calculate_Hessian();
    return second_order_performance;
}

/// Returns the Taylor approximation of the performance function at some point near the parameters.
/// The order of the approximation here is zero, i.e., only the performance value is used.
double PerformanceFunctional::calculate_zero_order_Taylor_approximation(const Vector<double> &) const
{
    return calculate_performance();
}

/// Returns the Taylor approximation of the performance function at some point near the parameters.
/// The order of the approximation here is one, i.e., both the performance value and the performance gradient are used.
/// @param parameters Approximation point.
double PerformanceFunctional::calculate_first_order_Taylor_approximation(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t parameters_size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "double calculate_first_order_Taylor_approximation(const Vector<double>&) const method.\n"
               << "Size of potential parameters must be equal to number of parameters.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<double> original_parameters = neural_network_pointer->arrange_parameters();
    const double performance = calculate_performance();
    const Vector<double> gradient = calculate_gradient();
    const double first_order_Taylor_approximation = performance + gradient.dot(parameters - parameters);

    return first_order_Taylor_approximation;
}

/// Returns the Taylor approximation of the performance function at some point near the parameters.
/// The order of the approximation here is two, i.e., the performance value, the performance gradient and the performance Hessian are used.
/// @param parameters Approximation point.
double PerformanceFunctional::calculate_second_order_Taylor_approximation(const Vector<double> &parameters) const
{

#ifdef __OPENNN_DEBUG__
    const size_t parameters_size = parameters.size();
    const size_t parameters_number = neural_network_pointer->count_parameters_number();

    if (parameters_size != parameters_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "double calculate_second_order_Taylor_approximation(const Vector<double>&) const method.\n"
               << "Size of potential parameters must be equal to number of parameters.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const Vector<double> original_parameters = neural_network_pointer->arrange_parameters();
    const Vector<double> parameters_difference = parameters - parameters;

    // Performance functioNal stuff
    const double performance = calculate_performance();
    const Vector<double> gradient = calculate_gradient();
    const Matrix<double> Hessian = calculate_Hessian();

    return performance +
           gradient.dot(parameters_difference) +
           parameters_difference.dot(Hessian).dot(parameters_difference) / 2.0;
}

/// Returns the value of the performance function at some step along some direction.
/// @param direction Direction vector.
/// @param rate Step value.
double PerformanceFunctional::calculate_performance(const Vector<double> &direction, const double &rate) const
{
    return calculate_performance(neural_network_pointer->arrange_parameters() + direction * rate);
}

/// Returns the derivative of the performance function at some step along some direction.
/// @param direction Direction vector.
/// @param rate Step value.
double PerformanceFunctional::calculate_performance_derivative(const Vector<double> &direction,
                                                               const double &rate) const
{
    if (direction == 0.0)
        return 0.0;

    const Vector<double> parameters = neural_network_pointer->arrange_parameters();
    const Vector<double> potential_parameters = parameters + direction * rate;
    const Vector<double> gradient = calculate_gradient(potential_parameters);
    const Vector<double> normalized_direction = direction / direction.calculate_norm();

    return gradient.dot(normalized_direction);
}


/// Returns the second derivative of the performance function at some step along some direction.
/// @param direction Direction vector.
/// @param rate Step value.
double PerformanceFunctional::calculate_performance_second_derivative(const Vector<double> &direction,
                                                                      const double &rate) const
{
    if (direction == 0.0)
        return 0.0;

    const Vector<double> parameters = neural_network_pointer->arrange_parameters();
    const Vector<double> potential_parameters = parameters + direction * rate;
    const Matrix<double> Hessian = calculate_Hessian(potential_parameters);
    const Vector<double> normalized_direction = direction / direction.calculate_norm();

    return normalized_direction.dot(Hessian).dot(normalized_direction);
}

/// Serializes a default performance functional object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this element.
tinyxml2::XMLDocument *PerformanceFunctional::to_XML() const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;

    // Performance functional
    tinyxml2::XMLElement *performance_functional_element = document->NewElement("PerformanceFunctional");
    document->InsertFirstChild(performance_functional_element);

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "NO_OBJECTIVE");
        }
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "SUM_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *sum_squared_error_document = sum_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *sum_squared_error_element = sum_squared_error_document->FirstChildElement("SumSquaredError");
            DeepClone(objective_element, sum_squared_error_element, document, NULL);
            delete sum_squared_error_document;
        }
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "MEAN_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *mean_squared_error_document = mean_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *mean_squared_error_element = mean_squared_error_document->FirstChildElement("MeanSquaredError");
            DeepClone(objective_element, mean_squared_error_element, document, NULL);
            delete mean_squared_error_document;
        }
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "ROOT_MEAN_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *root_mean_squared_error_document = root_mean_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *root_mean_squared_error_element = root_mean_squared_error_document->FirstChildElement("RootMeanSquaredError");
            DeepClone(objective_element, root_mean_squared_error_element, document, NULL);
            delete root_mean_squared_error_document;
        }
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "NORMALIZED_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *normalized_squared_error_document = normalized_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *normalized_squared_error_element = normalized_squared_error_document->FirstChildElement("NormalizedSquaredError");
            DeepClone(objective_element, normalized_squared_error_element, document, NULL);
            delete normalized_squared_error_document;
        }
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "WEIGHTED_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *weighted_squared_error_document = weighted_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *weighted_squared_error_element = weighted_squared_error_document->FirstChildElement("WeightedSquaredError");
            DeepClone(objective_element, weighted_squared_error_element, document, NULL);
            delete weighted_squared_error_document;
        }
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "MINKOWSKI_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *Minkowski_error_document = Minkowski_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *Minkowski_error_element = Minkowski_error_document->FirstChildElement("MinkowskiError");
            DeepClone(objective_element, Minkowski_error_element, document, NULL);
            delete Minkowski_error_document;
        }
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "CROSS_ENTROPY_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *cross_entropy_error_document = cross_entropy_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *cross_entropy_error_element = cross_entropy_error_document->FirstChildElement("CrossEntropyError");
            DeepClone(objective_element, cross_entropy_error_element, document, NULL);
            delete cross_entropy_error_document;
        }
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "OUTPUTS_INTEGRALS_OBJECTIVE");
            const tinyxml2::XMLDocument *outputs_integrals_document = outputs_integrals_objective_pointer->to_XML();
            const tinyxml2::XMLElement *outputs_integrals_element = outputs_integrals_document->FirstChildElement("OutputsIntegrals");
            DeepClone(objective_element, outputs_integrals_element, document, NULL);
            delete outputs_integrals_document;
        }
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "SOLUTIONS_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *solutions_error_document = solutions_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *solutions_error_element = solutions_error_document->FirstChildElement("SolutionsError");
            DeepClone(objective_element, solutions_error_element, document, NULL);
            delete solutions_error_document;
        }
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "FINAL_SOLUTIONS_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *final_solutions_error_document = final_solutions_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *final_solutions_error_element = final_solutions_error_document->FirstChildElement("FinalSolutionsError");
            DeepClone(objective_element, final_solutions_error_element, document, NULL);
            delete final_solutions_error_document;
        }
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *independent_parameters_error_document = independent_parameters_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *independent_parameters_error_element = independent_parameters_error_document->FirstChildElement("IndependentParametersError");
            DeepClone(objective_element, independent_parameters_error_element, document, NULL);
            delete independent_parameters_error_document;
        }
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        {
            tinyxml2::XMLElement *objective_element = document->NewElement("Objective");
            performance_functional_element->LinkEndChild(objective_element);
            objective_element->SetAttribute("Type", "INVERSE_SUM_SQUARED_ERROR_OBJECTIVE");
            const tinyxml2::XMLDocument *inverse_sum_squared_error_document = inverse_sum_squared_error_objective_pointer->to_XML();
            const tinyxml2::XMLElement *inverse_sum_squared_error_element = inverse_sum_squared_error_document->FirstChildElement("InverseSumSquaredError");
            DeepClone(objective_element, inverse_sum_squared_error_element, document, NULL);
            delete inverse_sum_squared_error_document;
        }
        break;

    case USER_OBJECTIVE:
        // Do nothing
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "tinyxml2::XMLDocument* to_XML() const method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        {
            tinyxml2::XMLElement *regularization_element = document->NewElement("Regularization");
            performance_functional_element->LinkEndChild(regularization_element);
            regularization_element->SetAttribute("Type", "NO_REGULARIZATION");
        }
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        {
            tinyxml2::XMLElement *regularization_element = document->NewElement("Regularization");
            performance_functional_element->LinkEndChild(regularization_element);
            regularization_element->SetAttribute("Type", "NEURAL_PARAMETERS_NORM_REGULARIZATION");
            const tinyxml2::XMLDocument *neural_parameters_norm_document = neural_parameters_norm_regularization_pointer->to_XML();
            const tinyxml2::XMLElement *neural_parameters_norm_element = neural_parameters_norm_document->FirstChildElement("NeuralParametersNorm");
            DeepClone(regularization_element, neural_parameters_norm_element, document, NULL);
            delete neural_parameters_norm_document;
        }
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        {
            tinyxml2::XMLElement *regularization_element = document->NewElement("OUTPUTS_INTEGRALS_REGULARIZATION");
            performance_functional_element->LinkEndChild(regularization_element);
            regularization_element->SetAttribute("Type", "NEURAL_PARAMETERS_NORM_REGULARIZATION");
            const tinyxml2::XMLDocument *outputs_integrals_document = outputs_integrals_regularization_pointer->to_XML();
            const tinyxml2::XMLElement *outputs_integrals_element = outputs_integrals_document->FirstChildElement("OutputsIntegrals");
            DeepClone(regularization_element, outputs_integrals_element, document, NULL);
            delete outputs_integrals_document;
        }
        break;

    case USER_REGULARIZATION:
        // Do nothing
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "tinyxml2::XMLDocument* to_XML() const method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        {
            tinyxml2::XMLElement *constraints_element = document->NewElement("Constraints");
            performance_functional_element->LinkEndChild(constraints_element);
            constraints_element->SetAttribute("Type", "OUTPUTS_INTEGRALS_CONSTRAINTS");
            const tinyxml2::XMLDocument *outputs_integrals_document = outputs_integrals_constraints_pointer->to_XML();
            const tinyxml2::XMLElement *outputs_integrals_element = outputs_integrals_document->FirstChildElement("OutputsIntegrals");
            DeepClone(constraints_element, outputs_integrals_element, document, NULL);
            delete outputs_integrals_document;
        }
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        {
            tinyxml2::XMLElement *constraints_element = document->NewElement("Constraints");
            performance_functional_element->LinkEndChild(constraints_element);
            constraints_element->SetAttribute("Type", "SOLUTIONS_ERROR_CONSTRAINTS");
            const tinyxml2::XMLDocument *solutions_error_document = solutions_error_constraints_pointer->to_XML();
            const tinyxml2::XMLElement *solutions_error_element = solutions_error_document->FirstChildElement("SolutionsError");
            DeepClone(constraints_element, solutions_error_element, document, NULL);
            delete solutions_error_document;
        }
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        {
            tinyxml2::XMLElement *constraints_element = document->NewElement("Constraints");
            performance_functional_element->LinkEndChild(constraints_element);
            constraints_element->SetAttribute("Type", "FINAL_SOLUTIONS_ERROR_CONSTRAINTS");
            const tinyxml2::XMLDocument *final_solutions_error_document = final_solutions_error_constraints_pointer->to_XML();
            const tinyxml2::XMLElement *final_solutions_error_element = final_solutions_error_document->FirstChildElement("FinalSolutionsError");
            DeepClone(constraints_element, final_solutions_error_element, document, NULL);
            delete final_solutions_error_document;
        }
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        {
            tinyxml2::XMLElement *constraints_element = document->NewElement("Constraints");
            performance_functional_element->LinkEndChild(constraints_element);
            constraints_element->SetAttribute("Type", "INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS");
            const tinyxml2::XMLDocument *independent_parameters_error_document = independent_parameters_error_constraints_pointer->to_XML();
            const tinyxml2::XMLElement *independent_parameters_error_element = independent_parameters_error_document->FirstChildElement("FinalSolutionsError");
            DeepClone(constraints_element, independent_parameters_error_element, document, NULL);
            delete independent_parameters_error_document;
        }
        break;

    case USER_CONSTRAINTS:
        // Do nothing
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "tinyxml2::XMLDocument* to_XML() const method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return document;
}

/// Sets the performance functional member data from an XML document.
/// @param document Pointer to a TinyXML document with the performance functional data.
void PerformanceFunctional::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *performance_functional_element = document.FirstChildElement("PerformanceFunctional");
    if (!performance_functional_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Performance functional element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Objective type
    const tinyxml2::XMLElement *objective_element = performance_functional_element->FirstChildElement("Objective");
    if (objective_element) {
        const std::string new_objective_type = objective_element->Attribute("Type");
        set_objective_type(new_objective_type);
        switch (objective_type) {
        case NO_OBJECTIVE:
            // Do nothing
            break;

        case SUM_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("SumSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                sum_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case MEAN_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("MeanSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                mean_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("RootMeanSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                root_mean_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("NormalizedSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                normalized_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("WeightedSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                weighted_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case MINKOWSKI_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("MinkowskiError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                Minkowski_error_objective_pointer->from_XML(new_document);
            }
            break;

        case CROSS_ENTROPY_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("CrossEntropyError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                cross_entropy_error_objective_pointer->from_XML(new_document);
            }
            break;

        case OUTPUTS_INTEGRALS_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("OutputsIntegralsError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                outputs_integrals_objective_pointer->from_XML(new_document);
            }
            break;

        case SOLUTIONS_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("SolutionsError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                solutions_error_objective_pointer->from_XML(new_document);
            }
            break;

        case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("FinalSolutionsError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                final_solutions_error_objective_pointer->from_XML(new_document);
            }
            break;

        case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("IndependentParametersError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                independent_parameters_error_objective_pointer->from_XML(new_document);
            }
            break;

        case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("InverseSumSquaredError");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, objective_element, &new_document, NULL);
                inverse_sum_squared_error_objective_pointer->from_XML(new_document);
            }
            break;

        case USER_OBJECTIVE:
            //user_objective_pointer = NULL;
            break;

        default:
            {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                       << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                       << "Unknown objective type.\n";

                throw std::logic_error(buffer.str());
            }
        }
    }

    // Regularization type
    const tinyxml2::XMLElement *regularization_element = performance_functional_element->FirstChildElement("Regularization");
    if (regularization_element) {
        const std::string new_regularization_type = regularization_element->Attribute("Type");
        set_regularization_type(new_regularization_type);
        switch (regularization_type) {
        case NO_REGULARIZATION:
            // Do nothing
            break;

        case NEURAL_PARAMETERS_NORM_REGULARIZATION:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("NeuralParametersNorm");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, regularization_element, &new_document, NULL);
                neural_parameters_norm_regularization_pointer->from_XML(new_document);
            }
            break;

        case OUTPUTS_INTEGRALS_REGULARIZATION:
            {
                tinyxml2::XMLDocument new_document;
                tinyxml2::XMLElement *element_clone = new_document.NewElement("OutputsIntegrals");
                new_document.InsertFirstChild(element_clone);
                DeepClone(element_clone, regularization_element, &new_document, NULL);
                outputs_integrals_regularization_pointer->from_XML(new_document);
            }
            break;

        case USER_REGULARIZATION:
            // Do nothing
            break;

        default:
            {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                       << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                       << "Unknown regularization type.\n";

                throw std::logic_error(buffer.str());
            }
        }

        // Constraints term type
        const tinyxml2::XMLElement *constraints_element = performance_functional_element->FirstChildElement("Constraints");
        if (constraints_element) {
            const std::string new_constraints_type = constraints_element->Attribute("Type");
            set_constraints_type(new_constraints_type);
            switch (constraints_type) {
            case NO_CONSTRAINTS:
                // Do nothing
                break;

            case OUTPUTS_INTEGRALS_CONSTRAINTS:
                {
                    tinyxml2::XMLDocument new_document;
                    tinyxml2::XMLElement *element_clone = new_document.NewElement("OutputsIntegrals");
                    new_document.InsertFirstChild(element_clone);
                    DeepClone(element_clone, constraints_element, &new_document, NULL);
                    outputs_integrals_constraints_pointer->from_XML(new_document);
                }
                break;

            case SOLUTIONS_ERROR_CONSTRAINTS:
                {
                    tinyxml2::XMLDocument new_document;
                    tinyxml2::XMLElement *element_clone = new_document.NewElement("SolutionsError");
                    new_document.InsertFirstChild(element_clone);
                    DeepClone(element_clone, constraints_element, &new_document, NULL);
                    solutions_error_constraints_pointer->from_XML(new_document);
                }
                break;

            case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
                {
                    tinyxml2::XMLDocument new_document;
                    tinyxml2::XMLElement *element_clone = new_document.NewElement("FinalSolutionsError");
                    new_document.InsertFirstChild(element_clone);
                    DeepClone(element_clone, constraints_element, &new_document, NULL);
                    final_solutions_error_constraints_pointer->from_XML(new_document);
                }
                break;

            case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
                {
                    tinyxml2::XMLDocument new_document;
                    tinyxml2::XMLElement *element_clone = new_document.NewElement("IndependentParametersError");
                    new_document.InsertFirstChild(element_clone);
                    DeepClone(element_clone, constraints_element, &new_document, NULL);
                    independent_parameters_error_constraints_pointer->from_XML(new_document);
                }
                break;

            case USER_CONSTRAINTS:
                // Do nothing
                break;

            default:
                {
                    std::ostringstream buffer;

                    buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                           << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                           << "Unknown constraints type.\n";

                    throw std::logic_error(buffer.str());
                }
            }
        }
    }

    const tinyxml2::XMLElement *display_element = performance_functional_element->FirstChildElement("Display");
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

/// Writes to a string the members of the performance functional object in text format.
std::string PerformanceFunctional::to_string() const
{
    std::ostringstream buffer;
    buffer << "Performance functional\n"
           << "Objective type: " << write_objective_type() << "\n";

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        buffer << sum_squared_error_objective_pointer->to_string();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        buffer << mean_squared_error_objective_pointer->to_string();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        buffer << root_mean_squared_error_objective_pointer->to_string();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        buffer << normalized_squared_error_objective_pointer->to_string();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        buffer << weighted_squared_error_objective_pointer->to_string();
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        buffer << roc_area_error_objective_pointer->to_string();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        buffer << Minkowski_error_objective_pointer->to_string();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        buffer << cross_entropy_error_objective_pointer->to_string();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        buffer << outputs_integrals_objective_pointer->to_string();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        buffer << solutions_error_objective_pointer->to_string();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        buffer << final_solutions_error_objective_pointer->to_string();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        buffer << independent_parameters_error_objective_pointer->to_string();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        buffer << inverse_sum_squared_error_objective_pointer->to_string();
        break;

    case USER_OBJECTIVE:
        buffer << user_objective_pointer->to_string();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string to_string() method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    buffer << "Regularization type: " << write_regularization_type() << "\n";
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        buffer << neural_parameters_norm_regularization_pointer->to_string();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        buffer << outputs_integrals_regularization_pointer->to_string();
        break;

    case USER_REGULARIZATION:
        buffer << user_regularization_pointer->to_string();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string to_string() method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    buffer << "Constraints type: " << write_constraints_type() << "\n";
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        buffer << outputs_integrals_constraints_pointer->to_string();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        buffer << solutions_error_constraints_pointer->to_string();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        buffer << final_solutions_error_constraints_pointer->to_string();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        buffer << independent_parameters_error_constraints_pointer->to_string();
        break;

    case USER_CONSTRAINTS:
        buffer << user_constraints_pointer->to_string();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string to_string() method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return buffer.str();
}

/// Saves to a XML-type file a string representation of the performance functional object.
/// @param file_name Name of XML-type performance functional file.
void PerformanceFunctional::save(const std::string &file_name) const
{
    tinyxml2::XMLDocument *document = to_XML();
    document->SaveFile(file_name.c_str());
    delete document;
}

/// Loads a default performance functional XML-type file.
/// @param file_name Name of default XML-type performance functional file.
void PerformanceFunctional::load(const std::string &file_name)
{
    tinyxml2::XMLDocument document;
    if (document.LoadFile(file_name.c_str())) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PerformanceFunctional class.\n"
               << "void load(const std::string&) method.\n"
               << "Cannot load XML file " << file_name << ".\n";

        throw std::logic_error(buffer.str());
    }
    from_XML(document);
}

/// Returns any useful information about the objective function during training.
/// By default it is an empty string.
std::string PerformanceFunctional::write_information()
{
    std::ostringstream buffer;

    // Objective
    switch (objective_type) {
    case NO_OBJECTIVE:
        // Do nothing
        break;

    case SUM_SQUARED_ERROR_OBJECTIVE:
        buffer << sum_squared_error_objective_pointer->write_information();
        break;

    case MEAN_SQUARED_ERROR_OBJECTIVE:
        buffer << mean_squared_error_objective_pointer->write_information();
        break;

    case ROOT_MEAN_SQUARED_ERROR_OBJECTIVE:
        buffer << root_mean_squared_error_objective_pointer->write_information();
        break;

    case NORMALIZED_SQUARED_ERROR_OBJECTIVE:
        buffer << normalized_squared_error_objective_pointer->write_information();
        break;

    case WEIGHTED_SQUARED_ERROR_OBJECTIVE:
        buffer << weighted_squared_error_objective_pointer->write_information();
        break;

    case ROC_AREA_ERROR_OBJECTIVE:
        buffer << roc_area_error_objective_pointer->write_information();
        break;

    case MINKOWSKI_ERROR_OBJECTIVE:
        buffer << Minkowski_error_objective_pointer->write_information();
        break;

    case CROSS_ENTROPY_ERROR_OBJECTIVE:
        buffer << cross_entropy_error_objective_pointer->write_information();
        break;

    case OUTPUTS_INTEGRALS_OBJECTIVE:
        buffer << outputs_integrals_objective_pointer->write_information();
        break;

    case SOLUTIONS_ERROR_OBJECTIVE:
        buffer << solutions_error_objective_pointer->write_information();
        break;

    case FINAL_SOLUTIONS_ERROR_OBJECTIVE:
        buffer << final_solutions_error_objective_pointer->write_information();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE:
        buffer << independent_parameters_error_objective_pointer->write_information();
        break;

    case INVERSE_SUM_SQUARED_ERROR_OBJECTIVE:
        buffer << inverse_sum_squared_error_objective_pointer->write_information();
        break;

    case USER_OBJECTIVE:
        buffer << user_objective_pointer->write_information();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string write_information() method.\n"
                   << "Unknown objective type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Regularization
    switch (regularization_type) {
    case NO_REGULARIZATION:
        // Do nothing
        break;

    case NEURAL_PARAMETERS_NORM_REGULARIZATION:
        buffer << neural_parameters_norm_regularization_pointer->write_information();
        break;

    case OUTPUTS_INTEGRALS_REGULARIZATION:
        buffer << outputs_integrals_regularization_pointer->write_information();
        break;

    case USER_REGULARIZATION:
        buffer << user_regularization_pointer->write_information();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string write_information() method.\n"
                   << "Unknown regularization type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    // Constraints
    switch (constraints_type) {
    case NO_CONSTRAINTS:
        // Do nothing
        break;

    case OUTPUTS_INTEGRALS_CONSTRAINTS:
        buffer << outputs_integrals_constraints_pointer->write_information();
        break;

    case SOLUTIONS_ERROR_CONSTRAINTS:
        buffer << solutions_error_constraints_pointer->write_information();
        break;

    case FINAL_SOLUTIONS_ERROR_CONSTRAINTS:
        buffer << final_solutions_error_constraints_pointer->write_information();
        break;

    case INDEPENDENT_PARAMETERS_ERROR_CONSTRAINTS:
        buffer << independent_parameters_error_constraints_pointer->write_information();
        break;

    case USER_CONSTRAINTS:
        buffer << user_constraints_pointer->write_information();
        break;

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: PerformanceFunctional class.\n"
                   << "std::string write_information() method.\n"
                   << "Unknown constraints type.\n";

            throw std::logic_error(buffer.str());
        }
    }

    return buffer.str();
}

/// Print the members of this object to the standard output.
void PerformanceFunctional::print() const
{
    std::cout << to_string();
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
