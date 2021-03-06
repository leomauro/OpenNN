/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   M A T H E M A T I C A L   M O D E L   C L A S S                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "mathematical_model.h"


namespace OpenNN {

/// Default constructor.
/// It constructs a default mathematical model object, with zero independent and dependent variables.
MathematicalModel::MathematicalModel()
{
    set_default();
}

/// XML constructor.
/// It creates a mathematical model and loads its members from a TinyXML document.
/// @param mathematical_model_document XML document containing the mathematical model members.
MathematicalModel::MathematicalModel(const tinyxml2::XMLDocument &mathematical_model_document)
{
    set_default();
    from_XML(mathematical_model_document);
}

/// File constructor.
/// It creates a mathematical model and loads its members from a XML file.
/// @param file_name Name of mathematical model XML file.
MathematicalModel::MathematicalModel(const std::string &file_name)
{
    set_default();
    load(file_name);
}

/// Copy constructor.
/// It creates a mathematical model object and copies its members from another object.
/// @param other_mathematical_model Mathematical model object to be copied.
MathematicalModel::MathematicalModel(const MathematicalModel &other_mathematical_model)
{
    set(other_mathematical_model);
}

/// Destructor.
/// It does not delete any object.
MathematicalModel::~MathematicalModel()
{
}

/// Assignment operator.
/// It assigns to this object the members of an existing mathematical model object.
/// @param other_mathematical_model Mathematical model object to be assigned.
MathematicalModel &MathematicalModel::operator=(const MathematicalModel &other_mathematical_model)
{
    if (this != &other_mathematical_model) {
        independent_variables_number = other_mathematical_model.independent_variables_number;
        dependent_variables_number = other_mathematical_model.dependent_variables_number;
        display = other_mathematical_model.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_mathematical_model Mathematical model to be compared with.
bool MathematicalModel::operator==(const MathematicalModel &other_mathematical_model) const
{
    return independent_variables_number == other_mathematical_model.independent_variables_number &&
           dependent_variables_number == other_mathematical_model.dependent_variables_number &&
           display == other_mathematical_model.display;
}

/// Returns the number of independent variables in the mathematical model.
const size_t &MathematicalModel::get_independent_variables_number() const
{
    return independent_variables_number;
}

/// Returns the number of dependent variables in the mathematical model.
const size_t &MathematicalModel::get_dependent_variables_number() const
{
    return dependent_variables_number;
}

/// Returns the total number variablesin the mathematical model.
/// This is the sum of the numbers of independent and dependent variables.
size_t MathematicalModel::count_variables_number() const
{
    return independent_variables_number + dependent_variables_number;
}

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.
const bool &MathematicalModel::get_display() const
{
    return display;
}

/// Sets the members of this mathematical model object with those from other mathematical model object.
/// @param other_mathematical_model Mathematical model object to be copied.
void MathematicalModel::set(const MathematicalModel &other_mathematical_model)
{
    independent_variables_number = other_mathematical_model.independent_variables_number;
    dependent_variables_number = other_mathematical_model.dependent_variables_number;
    display = other_mathematical_model.display;
}

/// Sets the number of independent variables in the mathematical model.
/// @param new_independent_variables_number Number of independent variables.
void MathematicalModel::set_independent_variables_number(const size_t &new_independent_variables_number)
{
    independent_variables_number = new_independent_variables_number;
}

/// Sets the number of dependent variables in the mathematical model.
/// @param new_dependent_variables_number Number of dependent variables.
void MathematicalModel::set_dependent_variables_number(const size_t &new_dependent_variables_number)
{
    dependent_variables_number = new_dependent_variables_number;
}

/// Sets the following default values in the mathematical model:
/// <ul>
/// <li> Number of dependent variables: 0.
/// <li> Number of independent variables: 0.
/// <li> Display: True.
/// </ul>
void MathematicalModel::set_default()
{
    dependent_variables_number = 0;
    independent_variables_number = 0;
    display = true;
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void MathematicalModel::set_display(const bool &new_display)
{
    display = new_display;
}

/// This virtual method returns the solutions to the mathematical model,
/// which are given by the independent and the dependent variables.
/// Needs to be derived, otherwise an exception is thrown.
Matrix<double> MathematicalModel::calculate_solutions(const NeuralNetwork &) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: MathematicalModel class.\n"
           << "Matrix<double> calculate_solutions(const NeuralNetwork&) const method.\n"
           << "This method has not been derived.\n";

    throw std::logic_error(buffer.str());
}

/// This virtual method returns the final solutions of the mathematical model,
/// which are given by the final independent and dependent variables.
/// Needs to be derived, otherwise an exception is thrown.
Vector<double> MathematicalModel::calculate_final_solutions(const NeuralNetwork &) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: MathematicalModel class.\n"
           << "Vector<double> calculate_final_solutions(const NeuralNetwork&) const method.\n"
           << "This method has not been derived.\n";

    throw std::logic_error(buffer.str());
}

/// This virtual method returns the dependent variables solutions to the mathematical model,
/// Needs to be derived, otherwise an exception is thrown.
Matrix<double> MathematicalModel::calculate_dependent_variables(const NeuralNetwork &, const Matrix<double> &) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: MathematicalModel class.\n"
           << "Matrix<double> calculate_dependent_variables(const NeuralNetwork&, const Matrix<double>&) const method.\n"
           << "This method has not been derived.\n";

    throw std::logic_error(buffer.str());
}

/// Returns a string representation of the current mathematical model object.
std::string MathematicalModel::to_string() const
{
    std::ostringstream buffer;

    buffer << "Mathematical model\n"
           << "Independent variables number: " << independent_variables_number << "\n"
           << "Dependent variables number: " << dependent_variables_number << "\n"
           << "Display: " << display << "\n";
    return buffer.str();
}

/// This method outputs to the console the string representation of the mathematical model.
void MathematicalModel::print() const
{
    std::cout << to_string();
}

/// Serializes the mathematical model object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
tinyxml2::XMLDocument *MathematicalModel::to_XML() const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    std::ostringstream buffer;
    tinyxml2::XMLElement *mathematical_model_element = document->NewElement("MathematicalModel");
    document->InsertFirstChild(mathematical_model_element);

    // Independent variables number
    tinyxml2::XMLElement *independent_variables_number_element = document->NewElement("IndependentVariablesNumber");
    mathematical_model_element->LinkEndChild(independent_variables_number_element);
    buffer.str("");
    buffer << independent_variables_number;
    tinyxml2::XMLText *independent_variables_number_text = document->NewText(buffer.str().c_str());
    independent_variables_number_element->LinkEndChild(independent_variables_number_text);

    // Dependent variables number
    tinyxml2::XMLElement *dependent_variables_number_element = document->NewElement("DependentVariablesNumber");
    mathematical_model_element->LinkEndChild(dependent_variables_number_element);
    buffer.str("");
    buffer << dependent_variables_number;
    tinyxml2::XMLText *dependent_variables_number_text = document->NewText(buffer.str().c_str());
    dependent_variables_number_element->LinkEndChild(dependent_variables_number_text);

    // Display
    tinyxml2::XMLElement *display_element = document->NewElement("Display");
    mathematical_model_element->LinkEndChild(display_element);
    buffer.str("");
    buffer << display;
    tinyxml2::XMLText *display_text = document->NewText(buffer.str().c_str());
    display_element->LinkEndChild(display_text);

    return document;
}

/// Deserializes a TinyXML document into this mathematical model object.
/// @param document XML document containing the member data.
void MathematicalModel::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *root_element = document.FirstChildElement("MathematicalModel");

    if (!root_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MathematicalModel class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Unkown root element.\n";

        throw std::logic_error(buffer.str());
    }

    // Independent variables number
    const tinyxml2::XMLElement *ind_element = root_element->FirstChildElement("IndependentVariablesNumber");
    if (ind_element) {
        const char *text = ind_element->GetText();
        if (text) {
            try {
                set_independent_variables_number(atoi(text));
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    // Dependent variables number
    const tinyxml2::XMLElement *dep_element = root_element->FirstChildElement("DependentVariablesNumber");
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

    // Display
    const tinyxml2::XMLElement *display_element = root_element->FirstChildElement("Display");
    if (display_element) {
        const char *text = display_element->GetText();
        if (text) {
            try {
                const std::string string(text);
                set_display(string != "0");
            }
            catch (const std::logic_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

/// Saves to a file the XML representation of the mathematical object.
/// @param file_name Name of mathematical model XML file.
void MathematicalModel::save(const std::string &file_name) const
{
    tinyxml2::XMLDocument *document = to_XML();
    document->SaveFile(file_name.c_str());
    delete document;
}

/// Loads the members of the mathematical model from a XML file.
/// @param file_name Name of mathematical model XML file.
void MathematicalModel::load(const std::string &file_name)
{
    tinyxml2::XMLDocument document;
    if (document.LoadFile(file_name.c_str())) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MathematicalModel class.\n"
               << "void load(const std::string&) method.\n"
               << "Cannot load XML file " << file_name << ".\n";

        throw std::logic_error(buffer.str());
    }
    from_XML(document);
}

/// @todo
void MathematicalModel::save_data(const NeuralNetwork &, const std::string &) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: MathematicalModel class.\n"
           << "void save_data(const NeuralNetwork&, const std::string&) const method.\n"
           << "This method has not been derived.\n";

    throw std::logic_error(buffer.str());
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
