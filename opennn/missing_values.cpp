/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   M I S S I N G   V A L U E S   C L A S S                                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "missing_values.h"


namespace OpenNN {

/// Default constructor.
/// It creates a missing values object with zero missing values.
/// It also initializes the rest of class members to their default values.
MissingValues::MissingValues()
{
    set();
    set_default();
}

/// Missing values number constructor.
/// It creates a data set object with a given number of missing values.
/// It also initializes the rest of class members to their default values.
MissingValues::MissingValues(const size_t &new_instances_number, const size_t &new_variables_number)
{
    set(new_instances_number, new_variables_number);
    set_default();
}

/// XML constructor.
/// It creates a missing balues object by loading the object members from a TinyXML document.
/// @param missing_values_document XML document from the TinyXML library.
MissingValues::MissingValues(const tinyxml2::XMLDocument &missing_values_document)
{
    set(missing_values_document);
}

/// Copy constructor.
/// It creates a copy of an existing MissingValues object.
/// @param other_missing_values Missing balues object to be copied.
MissingValues::MissingValues(const MissingValues &other_missing_values)
{
    instances_number = other_missing_values.instances_number;
    variables_number = other_missing_values.variables_number;
    scrubbing_method = other_missing_values.scrubbing_method;
    items = other_missing_values.items;
    display = other_missing_values.display;
}

/// Destructor.
MissingValues::~MissingValues()
{
}

/// Assignment operator.
/// It assigns to the current object the members of an existing missing values object.
/// @param other_missing_values Missing values object to be assigned.
MissingValues &MissingValues::operator=(const MissingValues &other_missing_values)
{
    if (this != &other_missing_values) {
        instances_number = other_missing_values.instances_number;
        variables_number = other_missing_values.variables_number;
        items = other_missing_values.items;
        display = other_missing_values.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_missing_values Missing values object to be compared with.
bool MissingValues::operator==(const MissingValues &other_missing_values) const
{
    return items == other_missing_values.items && display == other_missing_values.display;
}

/// Returns the number of instances in the data set.
size_t MissingValues::get_instances_number() const
{
    return instances_number;
}

/// Returns the number of variables in the data set.
size_t MissingValues::get_variables_number() const
{
    return variables_number;
}

/// Returns a vector with the number of missing values for each variable in the data set.
/// The size of the vector is the number of variables.
Vector<size_t> MissingValues::get_missing_values_numbers() const
{
    Vector<size_t> missing_values_numbers(variables_number, 0);
    const size_t missing_values_number = get_missing_values_number();
    size_t variable_index;
    for (size_t i = 0; i < missing_values_number; i++) {
        variable_index = items[i].variable_index;
        missing_values_numbers[variable_index]++;
    }
    return missing_values_numbers;
}

/// Returns a constant reference to the vector of missing value items.
const Vector<MissingValues::Item> &MissingValues::get_items() const
{
    return items;
}

/// Returns a single missing value, with information about the instance and variable indices.
/// @param index Index of missing value.
const MissingValues::Item &MissingValues::get_item(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t missing_values_number = get_missing_values_number();

    if (index >= missing_values_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "const Item& get_item(const size_t&) const method.\n"
               << "Index (" << index << ") must be less than number of missing values (" << missing_values_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index];
}

/// Returns the method to be used for dealing with the missing values.
MissingValues::ScrubbingMethod MissingValues::get_scrubbing_method() const
{
    return scrubbing_method;
}

/// Returns a string with the name of the method used for scrubbing.
std::string MissingValues::write_scrubbing_method() const
{
    if (scrubbing_method == Unuse)
        return "Unuse";
    else if (scrubbing_method == Mean)
        return "Mean";
    else if (scrubbing_method == NoScrubbing)
        return "NoScrubbing";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "std::string write_scrubbing_method() const method.\n"
               << "Unknown scrubbing method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns a string with the name of the method used for scrubbing, as paragaph text.
std::string MissingValues::write_scrubbing_method_text() const
{
    if (scrubbing_method == Unuse)
        return "unuse";
    else if (scrubbing_method == Mean)
        return "mean";
    else if (scrubbing_method == NoScrubbing)
        return "no scrubbing";
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "std::string write_scrubbing_method_text() const method.\n"
               << "Unknown scrubbing method.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.
const bool &MissingValues::get_display() const
{
    return display;
}

/// Sets a missing values object with zero instances, variables and missing values.
void MissingValues::set()
{
    instances_number = 0;
    variables_number = 0;
    set_missing_values_number(0);
    set_default();
}

/// Sets a new number of missing values in the object.
/// @param new_instances_number Number of instances in the data set.
/// @param new_variables_number Number of variables in the data set.
void MissingValues::set(const size_t &new_instances_number, const size_t &new_variables_number)
{
    instances_number = new_instances_number;
    variables_number = new_variables_number;
    set_missing_values_number(0);
    set_default();
}

/// Sets the members of this object from a XML document.
/// @param document Pointer to a TinyXML document containing the member data.
void MissingValues::set(const tinyxml2::XMLDocument &document)
{
    set();
    from_XML(document);
}

/// Sets the number of data set instances in this object.
void MissingValues::set_instances_number(const size_t &new_instances_number)
{
    set_missing_values_number(0);
    instances_number = new_instances_number;
}

/// Sets the number of data set variables in this object.
void MissingValues::set_variables_number(const size_t &new_variables_number)
{
    set_missing_values_number(0);
    variables_number = new_variables_number;
}

/// Sets the default values to this MissingValues object:
/// <ul>
/// <li>scrubbing_method: Unuse</li>
/// <li>display: true</li>
/// </ul>
void MissingValues::set_default()
{
    scrubbing_method = Unuse;
    display = true;
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void MissingValues::set_display(const bool &new_display)
{
    display = new_display;
}

/// Sets a new vector of missing value items.
void MissingValues::set_items(const Vector<Item> &new_items)
{
    items = new_items;
}

/// Sets the indices
void MissingValues::set_item(const size_t &index, const size_t &instance_index, const size_t &variable_index)
{

#ifdef __OPENNN_DEBUG__
    const size_t missing_values_number = get_missing_values_number();

    if (index >= missing_values_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void set_item(const size_t&, const size_t&, const size_t&) method.\n"
               << "Index (" << index << ") must be less than number of missing values (" << missing_values_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if (instance_index >= instances_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void set_item(const size_t&, const size_t&, const size_t&) method.\n"
               << "Index of instance (" << instance_index << ") must be less than number of instances (" << instances_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if (variable_index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void set_item(const size_t&, const size_t&, const size_t&) method.\n"
               << "Index of variable (" << variable_index << ") must be less than number of variables (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[index].instance_index = instance_index;
    items[index].variable_index = variable_index;
}

/// Appends a new item to the vector of missing values.
/// @param instance_index Instance with a missing value.
/// @param variable_index Variable with a missing value.
void MissingValues::append(const size_t &instance_index, const size_t &variable_index)
{

#ifdef __OPENNN_DEBUG__
    if (instance_index >= instances_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void append(const size_t&, const size_t&) method.\n"
               << "Index of instance (" << instance_index << ") must be less than number of instances (" << instances_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if (variable_index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void append(const size_t&, const size_t&) method.\n"
               << "Index of variable (" << variable_index << ") must be less than number of instances (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Item item(instance_index, variable_index);
    items.push_back(item);
}

/// Sets a new number of missing values in the data set.
/// @param new_missing_values_number Number of missing values.
void MissingValues::set_missing_values_number(const size_t &new_missing_values_number)
{
    items.set(new_missing_values_number);
}

/// Sets a new method for dealing with the missing values.
/// @param new_scrubbing_method Scrubbing method.
void MissingValues::set_scrubbing_method(const ScrubbingMethod &new_scrubbing_method)
{
    scrubbing_method = new_scrubbing_method;
}

/// Sets a new method for dealing with the missing values from a string.
/// @param new_scrubbing_method String with the name of the scrubbing method.
void MissingValues::set_scrubbing_method(const std::string &new_scrubbing_method)
{
    if (new_scrubbing_method == "Unuse")
        scrubbing_method = Unuse;
    else if (new_scrubbing_method == "Mean")
        scrubbing_method = Mean;
    else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void new_scrubbing_method(const std::string&) method.\n"
               << "Unknown scrubbing method: " << new_scrubbing_method << ".\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns true if there are missing values,
/// and false if the number of missing values is zero.
bool MissingValues::has_missing_values() const
{
    return !items.empty();
}

/// Returns true if a given instance has missing values,
/// and false otherwise.
/// @param instance_index Index of instance.
bool MissingValues::has_missing_values(const size_t &instance_index) const
{
    if (items.empty())
        return false;

    const size_t missing_values_number = get_missing_values_number();
    for (size_t i = 0; i < missing_values_number; i++) {
        if (items[i].instance_index == instance_index)
            return true;
    }
    return false;
}

/// Returns true if a given instance has missing values for given variables,
/// and false otherwise.
/// @param instance_index Index of instance.
/// @param variables_indices Indices of variables.
bool MissingValues::has_missing_values(const size_t &instance_index, const Vector<size_t> &variables_indices) const
{
    const size_t missing_values_number = get_missing_values_number();
    const size_t variables_number = variables_indices.size();
    for (size_t i = 0; i < missing_values_number; i++) {
        if (items[i].instance_index == instance_index) {
            for (size_t j = 0; j < variables_number; j++) {
                if (items[i].variable_index == variables_indices[j])
                    return true;
            }
        }
    }
    return false;
}

/// Returns true if the value with given instance and variable indices is missing.
/// @param instance_index Index of instance.
/// @param variable_index Index of variable.
bool MissingValues::is_missing_value(const size_t &instance_index, const size_t &variable_index) const
{
    if (items.empty())
        return false;

    const size_t missing_values_number = get_missing_values_number();
    for (size_t i = 0; i < missing_values_number; i++) {
        if (items[i].instance_index == instance_index && items[i].variable_index == variable_index)
            return true;
    }
    return false;
}

/// Returns a vector with the indices of those instances with missing values.
Vector<size_t> MissingValues::arrange_missing_instances() const
{
    const size_t missing_values_number = get_missing_values_number();
    Vector<size_t> missing_instances;
    for (size_t i = 0; i < missing_values_number; i++) {
        if (!missing_instances.contains(items[i].instance_index))
            missing_instances.push_back(items[i].instance_index);
    }
    return missing_instances;
}

/// Returns the number of instances with missing values.
size_t MissingValues::count_missing_instances() const
{
    return arrange_missing_instances().size();
}

/// Returns a vector with the indices of those variables with missing values.
Vector<size_t> MissingValues::arrange_missing_variables() const
{
    const size_t missing_values_number = get_missing_values_number();
    Vector<size_t> missing_variables;
    for (size_t i = 0; i < missing_values_number; i++) {
        if (!missing_variables.contains(items[i].variable_index))
            missing_variables.push_back(items[i].variable_index);
    }
    return missing_variables;
}

/// @todo Complete method.
void MissingValues::convert_time_series(const size_t &lags_number)
{
    if (lags_number == 0)
        return;
}

/// @todo Implement this method.
void MissingValues::convert_autoassociation()
{
    const size_t missing_values_number = get_missing_values_number();
    Vector<Item> autoassociation_items(missing_values_number);
}

/// Returns a vector of vectors with the indices of the missing values for each variable.
/// The size of the vector is the number of variables.
/// The size of each subvector is the number of missing values for the corresponding variable.
Vector<Vector<size_t>> MissingValues::arrange_missing_indices() const
{
    Vector<Vector<size_t>> missing_indices(variables_number);
    const size_t missing_values_number = get_missing_values_number();
    size_t variable_index;
    size_t instance_index;
    for (size_t i = 0; i < missing_values_number; i++) {
        variable_index = items[i].variable_index;
        instance_index = items[i].instance_index;
        missing_indices[variable_index].push_back(instance_index);
    }
    return missing_indices;
}

/// Serializes the MissingValues object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
/// @todo
tinyxml2::XMLDocument *MissingValues::to_XML() const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    std::ostringstream buffer;

    // MissingValues
    tinyxml2::XMLElement *missing_values_element = document->NewElement("MissingValues");
    document->InsertFirstChild(missing_values_element);
    tinyxml2::XMLElement *element = NULL;
    tinyxml2::XMLText *text = NULL;
    const size_t missing_values_number = get_missing_values_number();

    // Instances number
    element = document->NewElement("InstancesNumber");
    missing_values_element->LinkEndChild(element);
    buffer.str("");
    buffer << instances_number;
    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Variables number
    element = document->NewElement("VariablesNumber");
    missing_values_element->LinkEndChild(element);
    buffer.str("");
    buffer << variables_number;
    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Scrubbing method
    element = document->NewElement("ScrubbingMethod");
    missing_values_element->LinkEndChild(element);
    text = document->NewText(write_scrubbing_method().c_str());
    element->LinkEndChild(text);

    // Missing values number
    element = document->NewElement("MissingValuesNumber");
    missing_values_element->LinkEndChild(element);
    buffer.str("");
    buffer << missing_values_number;
    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    for (size_t i = 0; i < missing_values_number; i++) {
        element = document->NewElement("Item");
        element->SetAttribute("Index", (unsigned) i + 1);
        missing_values_element->LinkEndChild(element);

        // Instance index
        tinyxml2::XMLElement *instance_index_element = document->NewElement("InstanceIndex");
        element->LinkEndChild(instance_index_element);
        buffer.str("");
        buffer << items[i].instance_index + 1;
        text = document->NewText(buffer.str().c_str());
        instance_index_element->LinkEndChild(text);

        // Variable index
        tinyxml2::XMLElement *variable_index_element = document->NewElement("VariableIndex");
        element->LinkEndChild(variable_index_element);
        buffer.str("");
        buffer << items[i].variable_index + 1;
        text = document->NewText(buffer.str().c_str());
        variable_index_element->LinkEndChild(text);
    }
    return document;
}

/// Deserializes a TinyXML document into this MissingValues object.
/// @param document XML document containing the member data.
/// @todo Check that the method i
void MissingValues::from_XML(const tinyxml2::XMLDocument &document)
{
    // Missing values element
    const tinyxml2::XMLElement *missing_values_element = document.FirstChildElement("MissingValues");
    if (!missing_values_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Pointer to MissingValues element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Instances number
    const tinyxml2::XMLElement *instances_number_element = missing_values_element->FirstChildElement("InstancesNumber");
    if (!instances_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Pointer to instances number is NULL.\n";

        throw std::logic_error(buffer.str());
    }
    instances_number = atoi(instances_number_element->GetText());

    // Variables number
    const tinyxml2::XMLElement *variables_number_element = missing_values_element->FirstChildElement("VariablesNumber");
    if (!variables_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Pointer to variables number is NULL.\n";

        throw std::logic_error(buffer.str());
    }
    variables_number = atoi(variables_number_element->GetText());

    // Scrubbing method
    const tinyxml2::XMLElement *scrubbing_method_element = missing_values_element->FirstChildElement("ScrubbingMethod");
    if (!scrubbing_method_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Pointer to scrubbing method element is NULL.\n";

        throw std::logic_error(buffer.str());
    }
    const std::string scrubbing_method_string = scrubbing_method_element->GetText();
    set_scrubbing_method(scrubbing_method_string);

    // Missing values number
    const tinyxml2::XMLElement *missing_values_number_element = missing_values_element->FirstChildElement("MissingValuesNumber");
    if (!missing_values_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MissingValues class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Pointer to missing values number is NULL.\n";

        throw std::logic_error(buffer.str());
    }
    const size_t missing_values_number = atoi(missing_values_number_element->GetText());
    set_missing_values_number(missing_values_number);
    if (missing_values_number <= 0)
        return;

    // Items
    unsigned index = 0;
    const tinyxml2::XMLElement *start_element = missing_values_number_element;
    for (size_t i = 0; i < missing_values_number; i++) {
        const tinyxml2::XMLElement *item_element = start_element->NextSiblingElement("Item");
        start_element = item_element;
        if (!item_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: MissingValues class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Item " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        item_element->QueryUnsignedAttribute("Index", &index);
        if (index != i + 1) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: MissingValues class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw std::logic_error(buffer.str());
        }

        // Instance index
        const tinyxml2::XMLElement *instance_index_element = item_element->FirstChildElement("InstanceIndex");
        if (!instance_index_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: MissingValues class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Pointer to instance index element is NULL.\n";

            throw std::logic_error(buffer.str());
        }
        const size_t new_instance_index = atoi(instance_index_element->GetText()) - 1;
        items[i].instance_index = new_instance_index;

        // Variable index
        const tinyxml2::XMLElement *variable_index_element = item_element->FirstChildElement("VariableIndex");
        if (!instance_index_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: MissingValues class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Pointer to variable index element is NULL.\n";

            throw std::logic_error(buffer.str());
        }
        const size_t new_variable_index = atoi(variable_index_element->GetText()) - 1;
        items[i].variable_index = new_variable_index;
    }
}

/// Returns a string representation of the current MissingValues object.
std::string MissingValues::to_string() const
{
    std::ostringstream buffer;
    const size_t missing_values_number = get_missing_values_number();
    buffer << "Missing values object\n"
           << "Instances number: " << instances_number << "\n"
           << "Variables number: " << variables_number << "\n"
           << "Missing values number: " << missing_values_number << "\n";
    for (size_t i = 0; i < missing_values_number; i++) {
        buffer << "Missing value " << i + 1 << ":\n"
               << "Instance index: " << items[i].instance_index << "\n"
               << "Variable index: " << items[i].variable_index << "\n";
    }
    buffer << "Scrubbing method: " << write_scrubbing_method() << "\n";

    return buffer.str();
}

/// Prints to the screen information about the missing values object.
void MissingValues::print() const
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
