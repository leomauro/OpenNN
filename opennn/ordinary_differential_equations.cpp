/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   O R D I N A R Y   D I F F E R E N T I A L   E Q U A T I O N S   C L A S S                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "ordinary_differential_equations.h"


namespace OpenNN {

/// Default constructor.
/// It constructs a default ordinary differential equations object.
OrdinaryDifferentialEquations::OrdinaryDifferentialEquations()
        : MathematicalModel()
{
    set_default();
}

/// XML constructor.
/// It creates a ordinary differential equations mathematical modeel and loads its members from a TinyXML document.
/// @param ordinary_differential_equations_document XML document containing the member data.
OrdinaryDifferentialEquations::OrdinaryDifferentialEquations(const tinyxml2::XMLDocument &ordinary_differential_equations_document)
        : MathematicalModel(ordinary_differential_equations_document)
{
    set_default();
}

/// File constructor.
/// It creates an ordinary differential equations mathematical model and loads its members from a XML file.
/// @param file_name Name of XML file.
OrdinaryDifferentialEquations::OrdinaryDifferentialEquations(const std::string &file_name)
        : MathematicalModel(file_name)
{
    set_default();
}

/// Copy constructor.
/// It creates an ordinary differential equations mathematical model object and copies its members from another object.
/// @param other_ordinary_differential_equations Ordinary differential equations object to be copied.
OrdinaryDifferentialEquations::OrdinaryDifferentialEquations(const OrdinaryDifferentialEquations &other_ordinary_differential_equations)
        : MathematicalModel()
{
    set(other_ordinary_differential_equations);
}

/// Destructor.
/// It does not delete any object.
OrdinaryDifferentialEquations::~OrdinaryDifferentialEquations()
{
}

/// Assignment operator.
/// It assigns to this object the members of an existing ordinary differential equations object.
/// @param other_ordinary_differential_equations Ordinary differential equations object to be assigned.
OrdinaryDifferentialEquations &OrdinaryDifferentialEquations::operator=(const OrdinaryDifferentialEquations &other_ordinary_differential_equations)
{
    if (this != &other_ordinary_differential_equations) {
        initial_independent_variable = other_ordinary_differential_equations.initial_independent_variable;
        final_independent_variable = other_ordinary_differential_equations.final_independent_variable;
        initial_dependent_variables = other_ordinary_differential_equations.initial_dependent_variables;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @param other_ordinary_differential_equations Object to be compared with.
bool OrdinaryDifferentialEquations::operator==(const OrdinaryDifferentialEquations &other_ordinary_differential_equations) const
{
    return initial_independent_variable == other_ordinary_differential_equations.initial_independent_variable &&
           final_independent_variable == other_ordinary_differential_equations.final_independent_variable &&
           initial_dependent_variables == other_ordinary_differential_equations.initial_dependent_variables;
}

/// Returns the initial value of the independent variable.
const double &OrdinaryDifferentialEquations::get_initial_independent_variable() const
{
    return initial_independent_variable;
}

/// Returns the final value of the independent variable.
const double &OrdinaryDifferentialEquations::get_final_independent_variable() const
{
    return final_independent_variable;
}

/// Returns the initial values of the independent variables.
const Vector<double> &OrdinaryDifferentialEquations::get_initial_dependent_variables() const
{
    return initial_dependent_variables;
}

/// Returns the initial value of a single independent variable.
/// @param i Index of dependent variable.
const double &OrdinaryDifferentialEquations::get_initial_dependent_variable(const size_t &i) const
{
    return initial_dependent_variables[i];
}

/// Returns the numerical method to be used for integration of the ordinary differential equation.
const OrdinaryDifferentialEquations::SolutionMethod &OrdinaryDifferentialEquations::get_solution_method() const
{
    return solution_method;
}

/// Returns a string with the name of the numerical method to be used for integration of the ordinary differential equation.
std::string OrdinaryDifferentialEquations::write_solution_method() const
{
    if (solution_method == RungeKutta)
        return "RungeKutta";
    else if (solution_method == RungeKuttaFehlberg)
        return "RungeKuttaFehlberg";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: OrdinaryDifferentialEquations class.\n"
               << "std::string write_solution_method() const method.\n"
               << "Unknown solution method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns the number of integration points in the Runge-Kutta method.
const size_t &OrdinaryDifferentialEquations::get_points_number() const
{
    return points_number;
}

/// Returns the tolerance in the Runge-Kutta-Fehlberg method.
const double &OrdinaryDifferentialEquations::get_tolerance() const
{
    return tolerance;
}

/// Returns the initial size to be reserved for the solutions in the Runge-Kutta-Fehlberg method.
const size_t &OrdinaryDifferentialEquations::get_initial_size() const
{
    return initial_size;
}

/// Returns a warning size for the solutions in the Runge-Kutta-Fehlberg method.
const size_t &OrdinaryDifferentialEquations::get_warning_size() const
{
    return warning_size;
}

/// Returns an error size for the solutions in the Runge-Kutta-Fehlberg method.
const size_t &OrdinaryDifferentialEquations::get_error_size() const
{
    return error_size;
}

/// Sets the members of this object to be the members of another object of the same class.
/// @param other_ordinary_differential_equations Object to be copied.
void OrdinaryDifferentialEquations::set(const OrdinaryDifferentialEquations &other_ordinary_differential_equations)
{
    independent_variables_number = other_ordinary_differential_equations.independent_variables_number;
    dependent_variables_number = other_ordinary_differential_equations.dependent_variables_number;
    initial_independent_variable = other_ordinary_differential_equations.initial_independent_variable;
    final_independent_variable = other_ordinary_differential_equations.final_independent_variable;
    initial_dependent_variables = other_ordinary_differential_equations.initial_dependent_variables;
    solution_method = other_ordinary_differential_equations.solution_method;
    points_number = other_ordinary_differential_equations.points_number;
    tolerance = other_ordinary_differential_equations.tolerance;
    initial_size = other_ordinary_differential_equations.initial_size;
    warning_size = other_ordinary_differential_equations.warning_size;
    error_size = other_ordinary_differential_equations.error_size;
    display = other_ordinary_differential_equations.display;
}

/// Sets the initial value for the independent variable.
/// @param new_initial_independent_variable Initial value for the independent variable.
void OrdinaryDifferentialEquations::set_initial_independent_variable(const double &new_initial_independent_variable)
{
    initial_independent_variable = new_initial_independent_variable;
}

/// Sets the final value for the independent variable.
/// @param new_final_independent_variable Final value for the independent variable.
void OrdinaryDifferentialEquations::set_final_independent_variable(const double &new_final_independent_variable)
{
    final_independent_variable = new_final_independent_variable;
}

/// Sets the initial values for the dependent variables.
/// @param new_initial_dependent_variables Initial values for the dependent variables.
void OrdinaryDifferentialEquations::set_initial_dependent_variables(const Vector<double> &new_initial_dependent_variables)
{
    initial_dependent_variables = new_initial_dependent_variables;
}

/// Sets the initial value for a single dependent variable.
/// @param i Index of dependent variable.
/// @param new_initial_dependent_variable Initial value for the corresponding dependent variable.
void OrdinaryDifferentialEquations::set_initial_dependent_variable(const size_t &i,
                                                                   const double &new_initial_dependent_variable)
{
    initial_dependent_variables[i] = new_initial_dependent_variable;
}

/// Sets the numerical method for calculating the solution to the ordinary differential equations.
/// Available methos include the Runge-Kutta and Runge-Kutta-Fehlber methods.
/// @param new_solution_method Solution method.
void OrdinaryDifferentialEquations::set_solution_method(const SolutionMethod &new_solution_method)
{
    solution_method = new_solution_method;
}

/// Sets the numerical method for calculating the solution to the ordinary differential equations.
/// Available methos include the Runge-Kutta and Runge-Kutta-Fehlber methods.
/// @param new_solution_method String with the name of the solution method ("RungeKutta" or "RungeKuttaFehlberg").
void OrdinaryDifferentialEquations::set_solution_method(const std::string &new_solution_method)
{
    if (new_solution_method == "RungeKutta")
        set_solution_method(RungeKutta);
    else if (new_solution_method == "RungeKuttaFehlberg")
        set_solution_method(RungeKuttaFehlberg);
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: OrdinaryDifferentialEquations class.\n"
               << "void set_solution_method(const std::string&) method.\n"
               << "Unknown solution method: " << new_solution_method << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets the number of points in the Runge-Kutta method.
/// @param new_points_number Number of points.
void OrdinaryDifferentialEquations::set_points_number(const size_t &new_points_number)
{
    points_number = new_points_number;
}

/// Sets the tolerance in the Runge-Kutta-Fehlberg method.
/// @param new_tolerance Tolerance value.
void OrdinaryDifferentialEquations::set_tolerance(const double &new_tolerance)
{
    tolerance = new_tolerance;
}

/// Sets the initial size for the solution in the Runge-Kutta-Fehlberg method.
/// @param new_initial_size Initial solution size.
void OrdinaryDifferentialEquations::set_initial_size(const size_t &new_initial_size)
{
    initial_size = new_initial_size;
}

/// Sets a warning size for the solution in the Runge-Kutta-Fehlberg method.
/// @param new_warning_size Warning solution size.
void OrdinaryDifferentialEquations::set_warning_size(const size_t &new_warning_size)
{
    warning_size = new_warning_size;
}

/// Sets the error size for the solution in the Runge-Kutta-Fehlberg method.
/// @param new_error_size Error solution size.
void OrdinaryDifferentialEquations::set_error_size(const size_t &new_error_size)
{
    error_size = new_error_size;
}

/// Sets the following default values:
/// <ul>
/// <li> Independent variables number: 1.
/// <li> Dependent variables number: 0.
/// <li> Solution method: Runge-Kutta-Fehlberg.
/// <li> Points number: 101.
/// <li> Tolerance: 1e-6
/// <li> Initial size: 1e3.
/// <li> Warning size: 1e6.
/// <li> Error size: 1e9.
/// <li> Display: True.
/// </ul>
void OrdinaryDifferentialEquations::set_default()
{
    independent_variables_number = 1;
    dependent_variables_number = 0;
    solution_method = RungeKuttaFehlberg;
    points_number = 101;
    tolerance = 1.0e-6;
    initial_size = (size_t) 1.0e3;
    warning_size = (size_t) 1.0e6;
    error_size = (size_t) 1.0e9;
    display = true;
}

/// This method calculate the numerical solution of the ordinary differential equations model using the Runge-Kutta method.
/// @param neural_network Neural network which represents the external inputs to the mathematical model.
Matrix<double> OrdinaryDifferentialEquations::calculate_Runge_Kutta_solution(const NeuralNetwork &neural_network) const
{
    const size_t variables_number = count_variables_number();
    const double h = (final_independent_variable - initial_independent_variable) / (points_number - 1.0);

    // Fourth order Runge-Kutta coefficients
    Vector<Vector<double>> c(4);
    Matrix<double> solution(points_number, variables_number);
    Vector<double> variables(variables_number);

    // Initial variables
    solution(0, 0) = initial_independent_variable;
    for (size_t j = 0; j < dependent_variables_number; j++) {
        solution(0, 1 + j) = initial_dependent_variables[j];
    }

    // Main loop
    for (size_t i = 0; i < points_number - 1; i++) {
        solution(i + 1, 0) = solution(i, 0) + h;

        // First coefficient
        variables[0] = solution(i, 0);
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(i, 1 + j);
        }
        c[0] = calculate_dependent_variables_dots(neural_network, variables);

        // Second coefficient
        variables[0] = solution(i, 0) + h / 2.0;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(i, 1 + j) + h * c[0][j] / 2.0;
        }
        c[1] = calculate_dependent_variables_dots(neural_network, variables);

        // Third coefficient
        variables[0] = solution(i, 0) + h / 2.0;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(i, 1 + j) + h * c[1][j] / 2.0;
        }
        c[2] = calculate_dependent_variables_dots(neural_network, variables);

        // Fourth coefficient
        variables[0] = solution(i + 1, 0);
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(i, 1 + j) + h * c[2][j] / 2.0;
        }
        c[3] = calculate_dependent_variables_dots(neural_network, variables);

        // Dependent variables
        for (size_t j = 0; j < dependent_variables_number; j++) {
            solution(i + 1, 1 + j) = solution(i, 1 + j) +
                                     h * (c[0][j] + 2.0 * c[1][j] + 2.0 * c[2][j] + c[3][j]) / 6.0;
        }
    }

    solution(points_number - 1, 0) = final_independent_variable;
    return solution;
}

/// This method calculate the solution at the final independent variable of the ordinary differential equations model using the Runge-Kutta method.
/// @param neural_network Neural network which represents the external inputs to the mathematical model.
Vector<double> OrdinaryDifferentialEquations::calculate_Runge_Kutta_final_solution(const NeuralNetwork &neural_network) const
{
    const size_t variables_number = count_variables_number();
    const double h = (final_independent_variable - initial_independent_variable) / (points_number - 1.0);

    // Fourth order Runge-Kutta coefficients
    Vector<Vector<double>> c(4);
    Vector<double> final_solution(variables_number);
    Vector<double> variables(variables_number);

    // Initial variables
    final_solution[0] = initial_independent_variable;
    for (size_t j = 0; j < dependent_variables_number; j++) {
        final_solution[0] = initial_dependent_variables[j];
    }

    // Main loop
    for (size_t i = 0; i < points_number - 1; i++) {
        final_solution[0] = final_solution[0] + h;

        // First coefficient
        variables[0] = final_solution[0];
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j];
        }
        c[0] = calculate_dependent_variables_dots(neural_network, variables);

        // Second coefficient
        variables[0] = final_solution[0] + h / 2.0;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] + h * c[0][j] / 2.0;
        }
        c[1] = calculate_dependent_variables_dots(neural_network, variables);

        // Third coefficient
        variables[0] = final_solution[0] + h / 2.0;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] + h * c[1][j] / 2.0;
        }
        c[2] = calculate_dependent_variables_dots(neural_network, variables);

        // Fourth coefficient
        variables[0] = final_solution[0];
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] + h * c[2][j] / 2.0;
        }
        c[3] = calculate_dependent_variables_dots(neural_network, variables);

        // Dependent variables
        for (size_t j = 0; j < dependent_variables_number; j++) {
            final_solution[1 + j] = final_solution[1 + j] +
                                    h * (c[0][j] + 2.0 * c[1][j] + 2.0 * c[2][j] + c[3][j]) / 6.0;
        }
    }
    return final_solution;
}

/// This method calculate the numerical solution of the ordinary differential equations model using the Runge-Kutta method.
/// @param neural_network Neural network which represents the external inputs to the mathematical model.
Matrix<double> OrdinaryDifferentialEquations::calculate_Runge_Kutta_Fehlberg_solution(const NeuralNetwork &neural_network) const
{
    const double epsilon = 1.0e-12;//std::numeric_limits<double>::epsilon();
    const double a2 = 1.0 / 5.0;
    const double a3 = 3.0 / 10.0;
    const double a4 = 3.0 / 5.0;
    const double a5 = 1.0;
    const double a6 = 7.0 / 8.0;
    const double b21 = 1.0 / 5.0;
    const double b31 = 3.0 / 40.0;
    const double b32 = 9.0 / 40.0;
    const double b41 = 3.0 / 10.0;
    const double b42 = -9.0 / 10.0;
    const double b43 = 6.0 / 5.0;
    const double b51 = -11.0 / 54.0;
    const double b52 = 5.0 / 2.0;
    const double b53 = -70.0 / 27.0;
    const double b54 = 35.0 / 27.0;
    const double b61 = 1631.0 / 55296.0;
    const double b62 = 175.0 / 512.0;
    const double b63 = 575.0 / 13824.0;
    const double b64 = 44275.0 / 110592.0;
    const double b65 = 253.0 / 4096.0;
    const double c41 = 37.0 / 378.0;
    const double c42 = 0.0;
    const double c43 = 250.0 / 621.0;
    const double c44 = 125.0 / 594.0;
    const double c45 = 0.0;
    const double c46 = 512.0 / 1771.0;
    const double c51 = 2825.0 / 27648.0;
    const double c52 = 0.0;
    const double c53 = 18575.0 / 48384.0;
    const double c54 = 13525.0 / 55296.0;
    const double c55 = 277.0 / 14336.0;
    const double c56 = 1.0 / 4.0;
    const double d1 = c41 - c51;
    const double d2 = c42 - c52;
    const double d3 = c43 - c53;
    const double d4 = c44 - c54;
    const double d5 = c45 - c55;
    const double d6 = c46 - c56;

    const size_t variables_number = count_variables_number();
    size_t size = initial_size;
    Vector<double> errors(dependent_variables_number, 0.0);
    double error = 0.0;
    Vector<Vector<double>> c(6);
    double hmin = 0.0;
    double h = (final_independent_variable - initial_independent_variable) * 1.0e-3;
    Vector<double> variables(variables_number);
    Matrix<double> solution(size, variables_number);
    size_t point_index = 0;

    // Initial values
    solution(0, 0) = initial_independent_variable;
    for (size_t j = 0; j < dependent_variables_number; j++) {
        solution(0, 1 + j) = initial_dependent_variables[j];
    }

    // Main loop
    while (solution(point_index, 0) < final_independent_variable) {
        // Set smallest allowable stepsize
        hmin = 32.0 * epsilon * fabs(solution(point_index, 0));
        if (h < hmin) {
            if (display) {
                std::cout << "OpenNN Warning: OrdinaryDifferentialEquations class.\n"
                          << "calculate_Runge_Kutta_Fehlberg_solution() method.\n"
                          << "Step size is less than smallest allowable." << std::endl;
            }
            h = hmin;
        }
        if (solution(point_index, 0) + h > final_independent_variable)
            h = final_independent_variable - solution(point_index, 0);

        // First coefficient
        variables[0] = solution(point_index, 0);
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j);
        }
        c[0] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Second coefficient
        variables[0] = solution(point_index, 0) + a2 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j) + b21 * c[0][j];
        }
        c[1] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Third coefficient
        variables[0] = solution(point_index, 0) + a3 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j) + b31 * c[0][j] + b32 * c[1][j];
        }
        c[2] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Fourth coefficient
        variables[0] = solution(point_index, 0) + a4 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j) + b41 * c[0][j] + b42 * c[1][j] + b43 * c[2][j];
        }
        c[3] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Fifth coefficient
        variables[0] = solution(point_index, 0) + a5 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j) +
                               b51 * c[0][j] + b52 * c[1][j] + b53 * c[2][j] + b54 * c[3][j];
        }
        c[4] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Sixth coefficient
        variables[0] = solution(point_index, 0) + a6 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = solution(point_index, 1 + j) +
                               b61 * c[0][j] + b62 * c[1][j] + b63 * c[2][j] +
                               b64 * c[3][j] + b65 * c[4][j];
        }
        c[5] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Error estimate
        for (size_t j = 0; j < dependent_variables_number; j++) {
            errors[j] = fabs(d1 * c[0][j] + d2 * c[1][j] + d3 * c[2][j] +
                             d4 * c[3][j] + d5 * c[4][j] + d6 * c[5][j]);
        }
        error = errors.calculate_maximum();
        if (error <= tolerance) {
            solution(point_index + 1, 0) = solution(point_index, 0) + h;
            for (size_t j = 0; j < dependent_variables_number; j++) {
                solution(point_index + 1, 1 + j) = solution(point_index, 1 + j) +
                                                   c51 * c[0][j] + c52 * c[1][j] + c53 * c[2][j] +
                                                   c54 * c[3][j] + c55 * c[4][j] + c56 * c[5][j];
            }
            point_index++;
            if (error != 0.0)
                h *= 0.9 * pow(fabs(tolerance / error), 0.2);
            if (point_index >= size) {
                size *= 2;
                if (display && size > warning_size) {
                    std::cout << "OpenNN Warning: OrdinaryDifferentialEquations class." << std::endl
                              << "calculate_Runge_Kutta_Fehlberg_solution() method." << std::endl
                              << "Solution size is " << size << std::endl;
                } else if (size > error_size) {
                    std::ostringstream buffer;

                    buffer << "OpenNN Exception: OrdinaryDifferentialEquations class." << std::endl
                           << "calculate_Runge_Kutta_Fehlberg_solution() method." << std::endl
                           << "Solution size is bigger than greatest allowable." << std::endl;

                    throw std::logic_error(buffer.str());
                }

                // @todo Substitute resize method
                // solution.resize(size, variables_number);
            }
        } else
            h *= 0.9 * pow(fabs(tolerance / error), 0.25);
    }

    // @todo Substitute resize method
    // solution.resize(point_index+1, variables_number);

    return solution;
}

/// This method calculate the numerical solution of the ordinary differential equations model using the Runge-Kutta-Fehlberg method.
/// @param neural_network Neural network which represents the external inputs to the mathematical model.
Vector<double> OrdinaryDifferentialEquations::calculate_Runge_Kutta_Fehlberg_final_solution(const NeuralNetwork &neural_network) const
{
    const double epsilon = 1.0e-12;     //std::numeric_limits<double>::epsilon();
    const double a2 = 1.0 / 5.0;
    const double a3 = 3.0 / 10.0;
    const double a4 = 3.0 / 5.0;
    const double a5 = 1.0;
    const double a6 = 7.0 / 8.0;
    const double b21 = 1.0 / 5.0;
    const double b31 = 3.0 / 40.0;
    const double b32 = 9.0 / 40.0;
    const double b41 = 3.0 / 10.0;
    const double b42 = -9.0 / 10.0;
    const double b43 = 6.0 / 5.0;
    const double b51 = -11.0 / 54.0;
    const double b52 = 5.0 / 2.0;
    const double b53 = -70.0 / 27.0;
    const double b54 = 35.0 / 27.0;
    const double b61 = 1631.0 / 55296.0;
    const double b62 = 175.0 / 512.0;
    const double b63 = 575.0 / 13824.0;
    const double b64 = 44275.0 / 110592.0;
    const double b65 = 253.0 / 4096.0;
    const double c41 = 37.0 / 378.0;
    const double c42 = 0.0;
    const double c43 = 250.0 / 621.0;
    const double c44 = 125.0 / 594.0;
    const double c45 = 0.0;
    const double c46 = 512.0 / 1771.0;
    const double c51 = 2825.0 / 27648.0;
    const double c52 = 0.0;
    const double c53 = 18575.0 / 48384.0;
    const double c54 = 13525.0 / 55296.0;
    const double c55 = 277.0 / 14336.0;
    const double c56 = 1.0 / 4.0;
    const double d1 = c41 - c51;
    const double d2 = c42 - c52;
    const double d3 = c43 - c53;
    const double d4 = c44 - c54;
    const double d5 = c45 - c55;
    const double d6 = c46 - c56;

    const size_t variables_number = count_variables_number();
    Vector<double> errors(dependent_variables_number, 0.0);
    double error = 0.0;
    Vector<Vector<double>> c(6);
    double hmin = 0.0;
    double h = (final_independent_variable - initial_independent_variable) * 1.0e-3;
    Vector<double> variables(variables_number);
    Vector<double> final_solution(variables_number);

    // Initial values
    final_solution[0] = initial_independent_variable;
    for (size_t j = 0; j < dependent_variables_number; j++) {
        final_solution[1 + j] = initial_dependent_variables[j];
    }

    // Main loop
    while (final_solution[0] < final_independent_variable) {
        // Set smallest allowable stepsize
        hmin = 32.0 * epsilon * fabs(final_solution[0]);
        if (h < hmin) {
            if (display) {
                std::cout << "OpenNN Warning: OrdinaryDifferentialEquations class.\n"
                          << "calculate_Runge_Kutta_Fehlberg_solution() method.\n"
                          << "Step size is less than smallest allowable." << std::endl;
            }
            h = hmin;
        }
        if (final_solution[0] + h > final_independent_variable)
            h = final_independent_variable - final_solution[0];

        // First coefficient
        variables[0] = final_solution[0];
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j];
        }
        c[0] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Second coefficient
        variables[0] = final_solution[0] + a2 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] +
                               b21 * c[0][j];
        }
        c[1] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Third coefficient
        variables[0] = final_solution[0] + a3 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] +
                               b31 * c[0][j] + b32 * c[1][j];
        }
        c[2] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Fourth coefficient
        variables[0] = final_solution[0] + a4 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] +
                               b41 * c[0][j] + b42 * c[1][j] + b43 * c[2][j];
        }
        c[3] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Fifth coefficient
        variables[0] = final_solution[0] + a5 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] +
                               b51 * c[0][j] + b52 * c[1][j] + b53 * c[2][j] + b54 * c[3][j];
        }
        c[4] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Sixth coefficient

        variables[0] = final_solution[0] + a6 * h;
        for (size_t j = 0; j < dependent_variables_number; j++) {
            variables[1 + j] = final_solution[1 + j] +
                               b61 * c[0][j] + b62 * c[1][j] + b63 * c[2][j] + b64 * c[3][j] + b65 * c[4][j];
        }
        c[5] = calculate_dependent_variables_dots(neural_network, variables) * h;

        // Error estimate
        for (size_t j = 0; j < dependent_variables_number; j++) {
            errors[j] = fabs(d1 * c[0][j] + d2 * c[1][j] + d3 * c[2][j] +
                             d4 * c[3][j] + d5 * c[4][j] + d6 * c[5][j]);
        }
        error = errors.calculate_maximum();
        if (error <= tolerance) {
            final_solution[0] += h;
            for (size_t j = 0; j < dependent_variables_number; j++) {
                final_solution[1 + j] += c51 * c[0][j] + c52 * c[1][j] + c53 * c[2][j] +
                                         c54 * c[3][j] + c55 * c[4][j] + c56 * c[5][j];
            }
            if (error != 0.0)
                h *= 0.9 * pow(fabs(tolerance / error), 0.2);
        } else
            h *= 0.9 * pow(fabs(tolerance / error), 0.25);
    }

    return final_solution;
}

Matrix<double> OrdinaryDifferentialEquations::calculate_solutions(const NeuralNetwork &neural_network) const
{
    switch (solution_method) {
    case RungeKutta:
        return calculate_Runge_Kutta_solution(neural_network);

    case RungeKuttaFehlberg:
        return calculate_Runge_Kutta_Fehlberg_solution(neural_network);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Error: OrdinaryDifferentialEquations class\n"
                   << "Vector<double> calculate_solutions(const NeuralNetwork&) const method.\n"
                   << "Unknown solution method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

Vector<double> OrdinaryDifferentialEquations::calculate_final_solutions(const NeuralNetwork &neural_network) const
{
    switch (solution_method) {
    case RungeKutta:
        return calculate_Runge_Kutta_final_solution(neural_network);

    case RungeKuttaFehlberg:
        return calculate_Runge_Kutta_Fehlberg_final_solution(neural_network);

    default:
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: ScalingLayer class\n"
                   << "Vector<double> calculate_final_solutions(const NeuralNetwork&) const method.\n"
                   << "Unknown solution method.\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Returns a string representation of the current ordinary differential equations object.
std::string OrdinaryDifferentialEquations::to_string() const
{
    std::ostringstream buffer;
    buffer << "Mathematical model\n"
           << "Independent variables number: " << independent_variables_number << "\n"
           << "Dependent variables number: " << dependent_variables_number << "\n"
           << "Initial independent variable: " << initial_independent_variable << "\n"
           << "Final independent variable: " << final_independent_variable << "\n"
           << "Initial dependent variables: " << initial_dependent_variables << "\n"
           << "Solution method: " << write_solution_method() << "\n"
           << "Points number: " << points_number << "\n"
           << "Tolerance" << tolerance << "\n"
           << "Initial size: " << initial_size << "\n"
           << "Warning size: " << warning_size << "\n"
           << "Error size: " << error_size << "\n"
           << "Display: " << display << std::endl;
    return buffer.str();
}

/// Serializes the ordinary differential equations object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
tinyxml2::XMLDocument *OrdinaryDifferentialEquations::to_XML() const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    std::ostringstream buffer;
    tinyxml2::XMLElement *ordinary_differential_equations_element = document->NewElement("OrdinaryDifferentialEquations");
    document->InsertFirstChild(ordinary_differential_equations_element);

    // Independent variables number
    tinyxml2::XMLElement *indep_element = document->NewElement("IndependentVariablesNumber");
    ordinary_differential_equations_element->LinkEndChild(indep_element);
    buffer.str("");
    buffer << independent_variables_number;
    indep_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Dependent variables number
    tinyxml2::XMLElement *dep_element = document->NewElement("DependentVariablesNumber");
    ordinary_differential_equations_element->LinkEndChild(dep_element);
    buffer.str("");
    buffer << dependent_variables_number;
    dep_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Initial independent variable
    tinyxml2::XMLElement *init_ind_element = document->NewElement("InitialIndependentVariable");
    ordinary_differential_equations_element->LinkEndChild(init_ind_element);
    buffer.str("");
    buffer << initial_independent_variable;
    init_ind_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Final independent variable
    tinyxml2::XMLElement *fin_ind_element = document->NewElement("FinalIndependentVariable");
    ordinary_differential_equations_element->LinkEndChild(fin_ind_element);
    buffer.str("");
    buffer << final_independent_variable;
    fin_ind_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Initial dependent variables
    tinyxml2::XMLElement *init_dep_element = document->NewElement("InitialDependentVariables");
    ordinary_differential_equations_element->LinkEndChild(init_dep_element);
    buffer.str("");
    buffer << initial_dependent_variables;
    init_dep_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Solution method
    tinyxml2::XMLElement *sol_element = document->NewElement("SolutionMethod");
    ordinary_differential_equations_element->LinkEndChild(sol_element);
    sol_element->LinkEndChild(document->NewText(write_solution_method().c_str()));

    // Points number
    tinyxml2::XMLElement *points_element = document->NewElement("PointsNumber");
    ordinary_differential_equations_element->LinkEndChild(points_element);
    buffer.str("");
    buffer << points_number;
    points_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Tolerance
    tinyxml2::XMLElement *tol_element = document->NewElement("Tolerance");
    ordinary_differential_equations_element->LinkEndChild(tol_element);
    buffer.str("");
    buffer << tolerance;
    tol_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Initial size
    tinyxml2::XMLElement *size_element = document->NewElement("InitialSize");
    ordinary_differential_equations_element->LinkEndChild(size_element);
    buffer.str("");
    buffer << initial_size;
    size_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Warning size
    tinyxml2::XMLElement *warn_element = document->NewElement("WarningSize");
    ordinary_differential_equations_element->LinkEndChild(warn_element);
    buffer.str("");
    buffer << warning_size;
    warn_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Error size
    tinyxml2::XMLElement *err_element = document->NewElement("ErrorSize");
    ordinary_differential_equations_element->LinkEndChild(err_element);
    buffer.str("");
    buffer << error_size;
    err_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    // Display
    tinyxml2::XMLElement *display_element = document->NewElement("Display");
    ordinary_differential_equations_element->LinkEndChild(display_element);
    buffer.str("");
    buffer << display;
    display_element->LinkEndChild(document->NewText(buffer.str().c_str()));

    return document;
}

/// Deserializes a TinyXML document into this ordinary differential equations object.
/// @param document TinyXML document containing the member data.
void OrdinaryDifferentialEquations::from_XML(const tinyxml2::XMLDocument &document)
{
    // Dependent variables number
    const tinyxml2::XMLElement *dep_element = document.FirstChildElement("DependentVariablesNumber");
    if (dep_element) {
        const char *text = dep_element->GetText();
        if (text) {
            try {
                set_dependent_variables_number(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Initial independent variable
    const tinyxml2::XMLElement *init_ind_element = document.FirstChildElement("InitialIndependentVariable");
    if (init_ind_element) {
        const char *text = init_ind_element->GetText();
        if (text) {
            try {
                set_initial_independent_variable(atof(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Final independent variable
    const tinyxml2::XMLElement *fin_ind_element = document.FirstChildElement("FinalIndependentVariable");
    if (fin_ind_element) {
        const char *text = fin_ind_element->GetText();
        if (text) {
            try {
                set_final_independent_variable(atof(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Initial dependent variables
    const tinyxml2::XMLElement *init_dep_element = document.FirstChildElement("InitialDependentVariables");
    if (init_dep_element) {
        const char *text = init_dep_element->GetText();
        if (text) {
            try {
                Vector<double> new_initial_dependent_variables;
                new_initial_dependent_variables.parse(text);

                set_initial_dependent_variables(new_initial_dependent_variables);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Solution method
    const tinyxml2::XMLElement *method_element = document.FirstChildElement("SolutionMethod");
    if (method_element) {
        const char *text = method_element->GetText();
        if (text) {
            try {
                std::string new_solution_method(text);
                set_solution_method(new_solution_method);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Points number
    const tinyxml2::XMLElement *points_element = document.FirstChildElement("PointsNumber");
    if (points_element) {
        const char *text = points_element->GetText();
        if (text) {
            try {
                set_points_number(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Tolerance
    const tinyxml2::XMLElement *tolerance_element = document.FirstChildElement("Tolerance");
    if (tolerance_element) {
        const char *text = tolerance_element->GetText();
        if (text) {
            try {
                set_tolerance(atof(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Initial size
    const tinyxml2::XMLElement *initial_element = document.FirstChildElement("InitialSize");
    if (initial_element) {
        const char *text = initial_element->GetText();
        if (text) {
            try {
                set_initial_size(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Warning size
    const tinyxml2::XMLElement *warning_element = document.FirstChildElement("WarningSize");
    if (warning_element) {
        const char *text = warning_element->GetText();
        if (text) {
            try {
                set_warning_size(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Error size
    const tinyxml2::XMLElement *error_element = document.FirstChildElement("ErrorSize");
    if (error_element) {
        const char *text = error_element->GetText();
        if (text) {
            try {
                set_error_size(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Display
    const tinyxml2::XMLElement *display_element = document.FirstChildElement("Display");
    if (display_element) {
        const char *display_text = display_element->GetText();
        if (display_text) {
            try {
                std::string display_string(display_text);
                set_display(display_string != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

/// Saves the solution data of an ordinary differential equation to a data file.
/// @param neural_network Neural network which represents the external inputs to the mathematical model.
/// @param file_name Name of solution data file.
void OrdinaryDifferentialEquations::save_data(const NeuralNetwork &neural_network,
                                              const std::string &file_name) const
{
    const Matrix<double> solution = calculate_Runge_Kutta_solution(neural_network);
    solution.save(file_name);
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
