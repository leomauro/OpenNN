/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   S I M U L A T E D   A N N E A L I N G   O R D E R   C L A S S                                              */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "simulated_annealing_order.h"


namespace OpenNN {

/// Default constructor.
SimulatedAnnealingOrder::SimulatedAnnealingOrder()
        : OrderSelectionAlgorithm()
{
    set_default();
}

/// Training strategy constructor.
/// @param new_training_strategy_pointer Pointer to a training strategy object.
SimulatedAnnealingOrder::SimulatedAnnealingOrder(TrainingStrategy *new_training_strategy_pointer)
        : OrderSelectionAlgorithm(new_training_strategy_pointer)
{
    set_default();
}

/// File constructor.
/// @param file_name Name of XML simulated annealing order file.
SimulatedAnnealingOrder::SimulatedAnnealingOrder(const std::string &file_name)
        : OrderSelectionAlgorithm(file_name)
{
    load(file_name);
}

/// XML constructor.
/// @param simulated_annealing_order_document Pointer to a TinyXML document containing the simulated annealing order data.
SimulatedAnnealingOrder::SimulatedAnnealingOrder(const tinyxml2::XMLDocument &simulated_annealing_order_document)
        : OrderSelectionAlgorithm(simulated_annealing_order_document)
{
    from_XML(simulated_annealing_order_document);
}

/// Destructor.
SimulatedAnnealingOrder::~SimulatedAnnealingOrder()
{
}

/// Returns the temperature reduction factor for the simulated annealing method.
const double &SimulatedAnnealingOrder::get_cooling_rate() const
{
    return cooling_rate;
}

/// Returns the minimum temperature reached in the simulated annealing model order selection algorithm.
const double &SimulatedAnnealingOrder::get_minimum_temperature() const
{
    return minimum_temperature;
}

/// Sets the members of the model selection object to their default values.
void SimulatedAnnealingOrder::set_default()
{
    cooling_rate = 0.5;
    minimum_temperature = 1.0e-3;
}

/// Sets the cooling rate for the simulated annealing.
/// @param new_cooling_rate Temperature reduction factor.
void SimulatedAnnealingOrder::set_cooling_rate(const double &new_cooling_rate)
{

#ifdef __OPENNN_DEBUG__
    if (new_cooling_rate <= 0) {
        std::ostringstream buffer;
        buffer << "OpenNN Exception: SimulatedAnnealingOrder class.\n"
               << "void set_cooling_rate(const size_t&) method.\n"
               << "Cooling rate must be greater than 0.\n";

        throw std::logic_error(buffer.str());
    }

    if (new_cooling_rate >= 1) {
        std::ostringstream buffer;
        buffer << "OpenNN Exception: SimulatedAnnealingOrder class.\n"
               << "void set_cooling_rate(const size_t&) method.\n"
               << "Cooling rate must be less than 1.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    cooling_rate = new_cooling_rate;
}

/// Sets the minimum temperature for the simulated annealing order selection algorithm.
/// @param new_minimum_temperature Value of the minimum temperature.
void SimulatedAnnealingOrder::set_minimum_temperature(const double &new_minimum_temperature)
{

#ifdef __OPENNN_DEBUG__
    if (new_minimum_temperature < 0) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SimulatedAnnealingOrder class.\n"
               << "void set_minimum_temperature(const double&) method.\n"
               << "Minimum temperature must be equal or greater than 0.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    minimum_temperature = new_minimum_temperature;
}

/// Return the index of the optimal individual of the history considering the tolerance.
size_t SimulatedAnnealingOrder::get_optimal_selection_performance_index() const
{
    size_t index = 0;
    size_t optimal_order = order_history[0];
    double optimum_error = selection_performance_history[0];

    for (size_t i = 1; i < order_history.size(); i++) {
        size_t current_order = order_history[i];
        double current_error = selection_performance_history[i];
        if (fabs(optimum_error - current_error) < tolerance && optimal_order > current_order ||
            fabs(optimum_error - current_error) >= tolerance && current_error < optimum_error) {
            optimal_order = current_order;
            optimum_error = current_error;
            index = i;
        }
    }

    return index;
}

/// Perform the order selection with the simulated annealing method.
SimulatedAnnealingOrder::SimulatedAnnealingOrderResults *SimulatedAnnealingOrder::perform_order_selection()
{
    SimulatedAnnealingOrderResults *results = new SimulatedAnnealingOrderResults();
    NeuralNetwork *neural_network_pointer = training_strategy_pointer->get_performance_functional_pointer()
                                                                     ->get_neural_network_pointer();
    MultilayerPerceptron *mlp = neural_network_pointer->get_multilayer_perceptron_pointer();

    size_t optimal_order, current_order;
    Vector<double> optimum_performance(2);
    Vector<double> current_order_performance(2);
    Vector<double> optimum_parameters, current_parameters;

    double current_training_performance, current_selection_performance;

    bool end = false;
    size_t iterations = 0;
    size_t random_failures = 0;
    size_t upper_bound;
    size_t lower_bound;

    time_t beginning_time, current_time;
    double elapsed_time;

    double temperature;
    double boltzmann_probability;
    double random_uniform;

    if (display)
        std::cout << "Performing order selection with simulated annealing method..." << std::endl;

    time(&beginning_time);

    optimal_order = (size_t) (minimum_order + calculate_random_uniform(0., 1.) * (maximum_order - minimum_order));
    optimum_performance = perform_model_evaluation(optimal_order);
    optimum_parameters = get_parameters_order(optimal_order);

    current_training_performance = optimum_performance[0];
    current_selection_performance = optimum_performance[1];
    temperature = current_selection_performance;

    results->order_data.push_back(optimal_order);
    if (reserve_performance_data)
        results->performance_data.push_back(current_training_performance);
    if (reserve_selection_performance_data)
        results->selection_performance_data.push_back(current_selection_performance);
    if (reserve_parameters_data)
        results->parameters_data.push_back(optimum_parameters);

    time(&current_time);
    elapsed_time = difftime(current_time, beginning_time);

    if (display) {
        std::cout << "Initial values : " << std::endl;
        std::cout << "Hidden perceptrons : " << optimal_order << std::endl;
        std::cout << "Final selection performance : " << optimum_performance[1] << std::endl;
        std::cout << "Final Training Performance : " << optimum_performance[0] << std::endl;
        std::cout << "Temperature : " << temperature << std::endl;
        std::cout << "Elapsed time : " << elapsed_time << std::endl;
    }

    while (!end) {
        upper_bound = std::min(maximum_order, optimal_order + (maximum_order - minimum_order) / 3);
        if (optimal_order <= (maximum_order - minimum_order) / 3)
            lower_bound = minimum_order;
        else
            lower_bound = optimal_order - (maximum_order - minimum_order) / 3;

        current_order = (size_t) (lower_bound + calculate_random_uniform(0., 1.) * (upper_bound - lower_bound));
        while (current_order == optimal_order) {
            current_order = (size_t) (lower_bound + calculate_random_uniform(0., 1.) * (upper_bound - lower_bound));
            random_failures++;
            if (random_failures >= 5 && optimal_order != minimum_order)
                current_order = optimal_order - 1;
            else if (random_failures >= 5 && optimal_order != maximum_order)
                current_order = optimal_order + 1;
        }

        random_failures = 0;
        current_order_performance = perform_model_evaluation(current_order);
        current_training_performance = current_order_performance[0];
        current_selection_performance = current_order_performance[1];
        current_parameters = get_parameters_order(current_order);

        boltzmann_probability = std::min(1.0,
                                         exp(-(current_selection_performance - optimum_performance[1]) / temperature));
        random_uniform = calculate_random_uniform(0., 1.);
        if (boltzmann_probability > random_uniform) {
            optimal_order = current_order;
            optimum_performance = current_order_performance;
            optimum_parameters = get_parameters_order(optimal_order);
        }

        time(&current_time);
        elapsed_time = difftime(current_time, beginning_time);

        results->order_data.push_back(current_order);
        if (reserve_performance_data)
            results->performance_data.push_back(current_training_performance);
        if (reserve_selection_performance_data)
            results->selection_performance_data.push_back(current_selection_performance);
        if (reserve_parameters_data)
            results->parameters_data.push_back(current_parameters);

        temperature = cooling_rate * temperature;
        iterations++;

        // Stopping criteria
        if (temperature <= minimum_temperature) {
            end = true;
            if (display)
                std::cout << "Minimum temperature reached." << std::endl;
            results->stopping_condition = SimulatedAnnealingOrder::MinimumTemperature;
        } else if (elapsed_time > maximum_time) {
            end = true;
            if (display)
                std::cout << "Maximum time reached." << std::endl;
            results->stopping_condition = SimulatedAnnealingOrder::MaximumTime;
        } else if (optimum_performance[1] <= selection_performance_goal) {
            end = true;
            if (display)
                std::cout << "Selection performance reached." << std::endl;
            results->stopping_condition = SimulatedAnnealingOrder::SelectionPerformanceGoal;
        } else if (iterations >= maximum_iterations_number) {
            end = true;
            if (display)
                std::cout << "Maximum number of iterations reached." << std::endl;
            results->stopping_condition = SimulatedAnnealingOrder::MaximumIterations;
        }

        if (display) {
            std::cout << "Iteration : " << iterations << std::endl;
            std::cout << "Hidden neurons number : " << optimal_order << std::endl;
            std::cout << "Selection performance : " << optimum_performance[1] << std::endl;
            std::cout << "Training performance : " << optimum_performance[0] << std::endl;
            std::cout << "Current temperature : " << temperature << std::endl;
            std::cout << "Elapsed time : " << elapsed_time << std::endl;
        }
    }

    size_t optimal_index = get_optimal_selection_performance_index();
    optimal_order = order_history[optimal_index];
    optimum_performance[0] = performance_history[optimal_index];
    optimum_performance[1] = selection_performance_history[optimal_index];
    optimum_parameters = get_parameters_order(optimal_order);

    if (display) {
        std::cout << "Optimal order : " << optimal_order << std::endl;
        std::cout << "Optimum selection performance : " << optimum_performance[1] << std::endl;
        std::cout << "Corresponding training performance : " << optimum_performance[0] << std::endl;
    }

    const size_t last_hidden_layer = mlp->get_layers_number() - 2;
    const size_t perceptrons_number = mlp->get_layer_pointer(last_hidden_layer)->get_perceptrons_number();

    if (optimal_order > perceptrons_number)
        mlp->grow_layer_perceptron(last_hidden_layer, optimal_order - perceptrons_number);
    else
        for (size_t i = 0; i < (perceptrons_number - optimal_order); i++) {
            mlp->prune_layer_perceptron(last_hidden_layer, 0);
        }

    mlp->set_parameters(optimum_parameters);

    if (reserve_minimal_parameters)
        results->minimal_parameters = optimum_parameters;

    results->optimal_order = optimal_order;
    results->final_performance = optimum_performance[0];
    results->final_selection_performance = optimum_performance[1];
    results->elapsed_time = elapsed_time;
    results->iterations_number = iterations;

    return results;
}

// the most representative
Matrix<std::string> SimulatedAnnealingOrder::to_string_matrix() const
{
    std::ostringstream buffer;

    Vector<std::string> labels;
    Vector<std::string> values;

    // Minimum order
    labels.push_back("Minimum order");
    buffer.str("");
    buffer << minimum_order;
    values.push_back(buffer.str());

    // Maximum order
    labels.push_back("Maximum order");
    buffer.str("");
    buffer << maximum_order;
    values.push_back(buffer.str());

    // Step
    labels.push_back("Cooling Rate");
    buffer.str("");
    buffer << cooling_rate;
    values.push_back(buffer.str());

    // Trials number
    labels.push_back("Trials number");
    buffer.str("");
    buffer << trials_number;
    values.push_back(buffer.str());

    // Tolerance
    labels.push_back("Tolerance");
    buffer.str("");
    buffer << tolerance;
    values.push_back(buffer.str());

    // Selection performance goal
    labels.push_back("Selection performance goal");
    buffer.str("");
    buffer << selection_performance_goal;
    values.push_back(buffer.str());

    // Minimum temperature
    labels.push_back("Minimum temperature");
    buffer.str("");
    buffer << minimum_temperature;
    values.push_back(buffer.str());

    // Maximum iterations number
    labels.push_back("Maximum iterations number");
    buffer.str("");
    buffer << maximum_iterations_number;
    values.push_back(buffer.str());

    // Maximum time
    labels.push_back("Maximum time");
    buffer.str("");
    buffer << maximum_time;
    values.push_back(buffer.str());

    // Plot training performance history
    labels.push_back("Plot training performance history");
    buffer.str("");
    buffer << reserve_performance_data;
    values.push_back(buffer.str());

    // Plot selection performance history
    labels.push_back("Plot selection performance history");
    buffer.str("");
    buffer << reserve_selection_performance_data;
    values.push_back(buffer.str());

    const size_t rows_number = labels.size();
    const size_t columns_number = 2;
    Matrix<std::string> string_matrix(rows_number, columns_number);
    string_matrix.set_column(0, labels);
    string_matrix.set_column(1, values);

    return string_matrix;
}

/// Prints to the screen the simulated annealing order parameters, the stopping criteria
/// and other user stuff concerning the simulated annealing order object.
tinyxml2::XMLDocument *SimulatedAnnealingOrder::to_XML() const
{
    std::ostringstream buffer;
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;

    // Order Selection algorithm
    tinyxml2::XMLElement *root_element = document->NewElement("SimulatedAnnealingOrder");
    document->InsertFirstChild(root_element);
    tinyxml2::XMLElement *element = NULL;
    tinyxml2::XMLText *text = NULL;

    // Minimum order
    {
        element = document->NewElement("MinimumOrder");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << minimum_order;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Maximum order
    {
        element = document->NewElement("MaximumOrder");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << maximum_order;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Cooling rate
    {
        element = document->NewElement("CoolingRate");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << cooling_rate;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Trials number
    {
        element = document->NewElement("TrialsNumber");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << trials_number;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Tolerance
    {
        element = document->NewElement("Tolerance");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << tolerance;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Selection performance goal
    {
        element = document->NewElement("SelectionPerformanceGoal");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << selection_performance_goal;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Minimum temperature
    {
        element = document->NewElement("MinimumTemperature");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << minimum_temperature;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Maximum iterations
    {
        element = document->NewElement("MaximumIterationsNumber");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << maximum_iterations_number;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Maximum time
    {
        element = document->NewElement("MaximumTime");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << maximum_time;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Reserve performance data
    {
        element = document->NewElement("ReservePerformanceHistory");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << reserve_performance_data;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    // Reserve selection performance data
    {
        element = document->NewElement("ReserveSelectionPerformanceHistory");
        root_element->LinkEndChild(element);
        buffer.str("");
        buffer << reserve_selection_performance_data;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    return document;
}

/// Deserializes a TinyXML document into this simulated annealing order object.
/// @param document TinyXML document containing the member data.
void SimulatedAnnealingOrder::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *root_element = document.FirstChildElement("SimulatedAnnealingOrder");
    if (!root_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: IncrementalOrder class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "SimulatedAnnealingOrder element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Minimum order
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("MinimumOrder");
        if (element) {
            const size_t new_minimum_order = atoi(element->GetText());
            try {
                minimum_order = new_minimum_order;
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Maximum order
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("MaximumOrder");
        if (element) {
            const size_t new_maximum_order = atoi(element->GetText());
            try {
                maximum_order = new_maximum_order;
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Parameters assays number
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("TrialsNumber");
        if (element) {
            const size_t new_trials_number = atoi(element->GetText());
            try {
                set_trials_number(new_trials_number);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Performance calculation method
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("PerformanceCalculationMethod");
        if (element) {
            const std::string new_performance_calculation_method = element->GetText();
            try {
                set_performance_calculation_method(new_performance_calculation_method);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Cooling rate
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("CoolingRate");
        if (element) {
            const double new_cooling_rate = atof(element->GetText());
            try {
                set_cooling_rate(new_cooling_rate);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Reserve parameters data
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("ReserveParametersData");
        if (element) {
            const std::string new_reserve_parameters_data = element->GetText();
            try {
                set_reserve_parameters_data(new_reserve_parameters_data != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Reserve performance data
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("ReservePerformanceHistory");
        if (element) {
            const std::string new_reserve_performance_data = element->GetText();
            try {
                set_reserve_performance_data(new_reserve_performance_data != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Reserve selection performance data
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("ReserveSelectionPerformanceHistory");
        if (element) {
            const std::string new_reserve_selection_performance_data = element->GetText();
            try {
                set_reserve_selection_performance_data(new_reserve_selection_performance_data != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Reserve minimal parameters
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("ReserveMinimalParameters");
        if (element) {
            const std::string new_reserve_minimal_parameters = element->GetText();
            try {
                set_reserve_minimal_parameters(new_reserve_minimal_parameters != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Display
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("Display");
        if (element) {
            const std::string new_display = element->GetText();
            try {
                set_display(new_display != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Selection performance goal
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("SelectionPerformanceGoal");
        if (element) {
            const double new_selection_performance_goal = atof(element->GetText());
            try {
                set_selection_performance_goal(new_selection_performance_goal);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Maximum iterations number
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("MaximumIterationsNumber");
        if (element) {
            const size_t new_maximum_iterations_number = atoi(element->GetText());
            try {
                set_maximum_iterations_number(new_maximum_iterations_number);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Maximum time
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("MaximumTime");
        if (element) {
            const double new_maximum_time = atoi(element->GetText());
            try {
                set_maximum_time(new_maximum_time);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Tolerance
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("Tolerance");
        if (element) {
            const double new_tolerance = atof(element->GetText());
            try {
                set_tolerance(new_tolerance);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Minimum temperature
    {
        const tinyxml2::XMLElement *element = root_element->FirstChildElement("MinimumTemperature");
        if (element) {
            const double new_minimum_temperature = atof(element->GetText());
            try {
                set_minimum_temperature(new_minimum_temperature);
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

/// Saves to a XML-type file the members of the simulated annealing order object.
/// @param file_name Name of simulated annealing order XML-type file.
void SimulatedAnnealingOrder::save(const std::string &file_name) const
{
    tinyxml2::XMLDocument *document = to_XML();
    document->SaveFile(file_name.c_str());
    delete document;
}

/// Loads a simulated annealing order object from a XML-type file.
/// @param file_name Name of simulated annealing order XML-type file.
void SimulatedAnnealingOrder::load(const std::string &file_name)
{
    set_default();

    tinyxml2::XMLDocument document;
    if (document.LoadFile(file_name.c_str())) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: SimulatedAnnealingOrder class.\n"
               << "void load(const std::string&) method.\n"
               << "Cannot load XML file " << file_name << ".\n";

        throw std::logic_error(buffer.str());
    }

    from_XML(document);
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
