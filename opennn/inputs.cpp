/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   I N P U T S   C L A S S                                                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "inputs.h"

#define numeric_to_string(x) \
    (static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str())

namespace OpenNN
{

/// Default constructor.
/// It creates an inputs object with zero inputs.
Inputs::Inputs(void)
{
    set();
}

/// Inputs number constructor.
/// It creates an inputs object with given numbers of inputs.
/// This constructor initializes the members of the object to their default values.
/// @param new_inputs_number Number of inputs.
Inputs::Inputs(const size_t &new_inputs_number)
{
    set(new_inputs_number);
}

/// XML constructor.
/// It creates an inputs object and loads its members from a XML document.
/// @param document TinyXML document with the member data.
Inputs::Inputs(const tinyxml2::XMLDocument &document)
{
    from_XML(document);
}

/// Copy constructor.
/// It creates a copy of an existing inputs object.
/// @param other_inputs Inputs object to be copied.
Inputs::Inputs(const Inputs &other_inputs)
{
    set(other_inputs);
}

/// Destructor.
Inputs::~Inputs(void)
{
}

/// Assignment operator.
/// It assigns to this object the members of an existing inputs object.
/// @param other_inputs Inputs object to be assigned.
Inputs &Inputs::operator=(const Inputs &other_inputs)
{
    if (this != &other_inputs) {
        items = other_inputs.items;
        display = other_inputs.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_inputs Inputs object to be compared with.
bool Inputs::operator==(const Inputs &other_inputs) const
{
    return /*items == other_inputs.items &&*/ display == other_inputs.display;
}

/// Returns true if the number of inputs is zero, and false otherwise.
bool Inputs::is_empty(void) const
{
    return get_inputs_number() == 0;
}

/// Returns the names of the input variables.
/// Such names are only used to give the user basic information about the problem at hand.
Vector<std::string> Inputs::arrange_names(void) const
{
    const size_t inputs_number = get_inputs_number();
    Vector<std::string> names(inputs_number);
    for (size_t i = 0; i < inputs_number; i++) {
        names[i] = items[i].name;
    }
    return names;
}

/// Returns the name of a single input variable.
/// Such a name is only used to give the user basic information about the problem at hand.
/// @param i Index of input variable.
const std::string &Inputs::get_name(const size_t &i) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (i >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "const std::string get_name(const size_t&) const method.\n"
               << "Input variable index must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[i].name;
}

/// Returns the units of the input variables as strings.
/// Such units are only used to give the user basic information about the problem at hand.
Vector<std::string> Inputs::arrange_units(void) const
{
    const size_t inputs_number = get_inputs_number();
    Vector<std::string> units(inputs_number);
    for (size_t i = 0; i < inputs_number; i++) {
        units[i] = items[i].units;
    }
    return units;
}

/// Returns the units of a single input variable as a string.
/// Such units are only used to give the user basic information about the problem at hand.
/// @param index Index of input variable.
const std::string &Inputs::get_unit(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "const std::string get_unit(const size_t&) const method.\n"
               << "Index of input variable must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].units;
}

/// Returns the description of the input variables as strings.
/// Such descriptions are only used to give the user basic information about the problem at hand.
Vector<std::string> Inputs::arrange_descriptions(void) const
{
    const size_t inputs_number = get_inputs_number();
    Vector<std::string> descriptions(inputs_number);
    for (size_t i = 0; i < inputs_number; i++) {
        descriptions[i] = items[i].description;
    }
    return descriptions;
}

/// Returns the description of a single input variable as a string.
/// Such a description is only used to give the user basic information about the problem at hand.
/// @param index Index of input variable.

const std::string &Inputs::get_description(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "const std::string& get_description(const size_t&) const method.\n"
               << "Index of input variable must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].description;
}

/// Returns the information of all input variables from a single matrix of strings.
/// The information contains names, inputs and descriptions.
/// The number of rows in the matris is the number of inputs, and the number of columns is three.
/// Each row contains the information of a single input variable.
Matrix<std::string> Inputs::arrange_information(void) const
{
    const size_t inputs_number = get_inputs_number();
    Matrix<std::string> information(inputs_number, 3);
    for (size_t i = 0; i < inputs_number; i++) {
        information(i, 0) = items[i].name;
        information(i, 1) = items[i].units;
        information(i, 2) = items[i].description;
    }
    return information;
}

/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.
const bool &Inputs::get_display(void) const
{
    return display;
}

/// Sets zero inputs.
/// It also sets the rest of members to their default values.
void Inputs::set(void)
{
    set_inputs_number(0);
    set_default();
}

/// Sets a new number of inputs.
/// It also sets the rest of members to their default values.
/// @param new_inputs_number Number of inputs.
void Inputs::set(const size_t &new_inputs_number)
{
    set_inputs_number(new_inputs_number);
    set_default();
}

/// Sets the members of this inputs object with those from another object of the same class.
/// @param other_inputs Inputs object to be copied.
void Inputs::set(const Inputs &other_inputs)
{
    items = other_inputs.items;
    display = other_inputs.display;
}

/// Sets all the inputs from a single vector.
/// @param new_inputs_information Inputs information.
/// The format is a vector of 3 subvectors:
/// <ul>
/// <li> Inputs name.
/// <li> Inputs units.
/// <li> Inputs description.
/// </ul>
void Inputs::set(const Vector<Vector<std::string>> &new_inputs_information)
{

#ifdef __OPENNN_DEBUG__
    const size_t new_inputs_information_size = new_inputs_information.size();
    if (new_inputs_information_size != 3) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set(const Vector< Vector<std::string> >&) method.\n"
               << "Size of inputs information must be three.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    set_names(new_inputs_information[0]);
    set_units(new_inputs_information[1]);
    set_descriptions(new_inputs_information[2]);
}

/// Sets a new number of inputs.
/// @param new_inputs_number Number of inputs.
void Inputs::set_inputs_number(const size_t &new_inputs_number)
{
    items.set(new_inputs_number);
}

/// Sets the members of this object to their default values.
void Inputs::set_default(void)
{
    const size_t inputs_number = get_inputs_number();
    for (size_t i = 0; i < inputs_number; i++) {
        std::ostringstream buffer;
        buffer << "input_" << i + 1;
        items[i].name = buffer.str();
        items[i].units = "";
        items[i].description = "";
    }
    set_display(true);
}

/// Sets the names for the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_names New names for the input variables.
void Inputs::set_names(const Vector<std::string> &new_names)
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_names.size();
    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_names(const Vector<std::string>&) method.\n"
               << "Size of name of input variables vector must be equal to number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < inputs_number; i++) {
        items[i].name = new_names[i];
    }
}

/// Sets the name of a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
/// @param i Index of input variable.
/// @param new_name New name for the input variable with index i.
void Inputs::set_name(const size_t &i, const std::string &new_name)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (i >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_name(const size_t&, const std::string&) method.\n"
               << "Index of input variable must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[i].name = new_name;
}

/// Sets new units for all the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_units New units for the input variables.
void Inputs::set_units(const Vector<std::string> &new_units)
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_units.size();
    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_units(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of input variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < inputs_number; i++) {
        items[i].units = new_units[i];
    }
}

/// Sets new units for a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
/// @param index Index of input variable.
/// @param new_unit New units for that input variable.

void Inputs::set_unit(const size_t &index, const std::string &new_unit)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_unit(const size_t&, const std::string&) method.\n"
               << "Index of input must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[index].units = new_unit;
}

/// Sets new descriptions for all the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_descriptions New description for the input variables.
void Inputs::set_descriptions(const Vector<std::string> &new_descriptions)
{
    const size_t inputs_number = get_inputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_descriptions.size();
    if (size != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_descriptions(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of input variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < inputs_number; i++) {
        items[i].description = new_descriptions[i];
    }
}

/// Sets a new description for a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param index Index of input variable.
/// @param new_description New description for the input variable with index i.
void Inputs::set_description(const size_t &index, const std::string &new_description)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_description(const size_t&, const std::string&) method.\n"
               << "Index of input variable must be less than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[index].description = new_description;
}

/// Sets all the possible information about the input variables.
/// The format is a vector of vectors of size three:
/// <ul>
/// <li> Name of input variables.
/// <li> Units of input variables.
/// <li> Description of input variables.
/// </ul>
/// @param new_information Input variables information.
void Inputs::set_information(const Matrix<std::string> &new_information)
{

#ifdef __OPENNN_DEBUG__
    const size_t columns_number = new_information.get_columns_number();
    if (columns_number != 3) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void set_information(const Matrix<std::string>&) method.\n"
               << "Number of columns in matrix must be 3.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    const size_t inputs_number = get_inputs_number();
    for (size_t i = 0; i < inputs_number; i++) {
        items[i].name = new_information(i, 0);
        items[i].units = new_information(i, 1);
        items[i].description = new_information(i, 2);
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void Inputs::set_display(const bool &new_display)
{
    display = new_display;
}

/// Appends a new item to the inputs.
void Inputs::grow_input(void)
{
    const Item item;
    items.push_back(item);
}

/// Removes a given item from the inputs.
/// @param index Index of item to be pruned.
void Inputs::prune_input(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t inputs_number = get_inputs_number();
    if (index >= inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void prune_input(const size_t&) method.\n"
               << "Index of input is equal or greater than number of inputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items.erase(items.begin() + index);
}

/// Returns the default names for the input variables:
/// <ul>
/// <li> 1
/// <li> ...
/// <li> n
/// </ul>
Vector<std::string> Inputs::write_default_names(void) const
{
    const size_t inputs_number = get_inputs_number();
    Vector<std::string> default_names(inputs_number);
    for (size_t i = 0; i < inputs_number; i++) {
        std::ostringstream buffer;
        buffer << "input_" << i + 1;
        default_names[i] = buffer.str();
    }
    return default_names;
}

/// Returns a string representation of the current inputs object.
std::string Inputs::to_string(void) const
{
    std::ostringstream buffer;
    const size_t inputs_number = get_inputs_number();
    buffer << "Inputs\n";
    for (size_t i = 0; i < inputs_number; i++) {
        buffer << "Item " << i + 1 << ":\n"
               << "Name:" << items[i].name << "\n"
               << "Units:" << items[i].units << "\n"
               << "Description:" << items[i].description << "\n";
    }
    return buffer.str();
}

/// Serializes the inputs object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document->
tinyxml2::XMLDocument *Inputs::to_XML(void) const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    const size_t inputs_number = get_inputs_number();
    std::ostringstream buffer;

    // Inputs
    tinyxml2::XMLElement *inputsElement = document->NewElement("Inputs");
    document->InsertFirstChild(inputsElement);
    tinyxml2::XMLElement *element = NULL;
    tinyxml2::XMLText *text = NULL;

    // Inputs number
    {
        element = document->NewElement("InputsNumber");
        inputsElement->LinkEndChild(element);
        buffer.str("");
        buffer << inputs_number;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    for (size_t i = 0; i < inputs_number; i++) {
        element = document->NewElement("Item");
        element->SetAttribute("Index", (unsigned) i + 1);
        inputsElement->LinkEndChild(element);

        // Name
        tinyxml2::XMLElement *name_element = document->NewElement("Name");
        element->LinkEndChild(name_element);
        tinyxml2::XMLText *name_text = document->NewText(items[i].name.c_str());
        name_element->LinkEndChild(name_text);

        // Units
        tinyxml2::XMLElement *units_element = document->NewElement("Units");
        element->LinkEndChild(units_element);
        tinyxml2::XMLText *units_text = document->NewText(items[i].units.c_str());
        units_element->LinkEndChild(units_text);

        // Description
        tinyxml2::XMLElement *description_element = document->NewElement("Description");
        element->LinkEndChild(description_element);
        tinyxml2::XMLText *descriptionText = document->NewText(items[i].description.c_str());
        description_element->LinkEndChild(descriptionText);
    }
    return document;
}

/// Deserializes a TinyXML document into this inputs object.
/// @param document XML document containing the member data.
void Inputs::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *inputsElement = document.FirstChildElement("Inputs");
    if (!inputsElement) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Inputs element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Inputs number
    const tinyxml2::XMLElement *inputs_number_element = inputsElement->FirstChildElement("InputsNumber");
    if (!inputs_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Inputs class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Inputs number element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t inputs_number = atoi(inputs_number_element->GetText());
    set(inputs_number);
    unsigned index = 0; // size_t does not work
    const tinyxml2::XMLElement *start_element = inputs_number_element;
    for (size_t i = 0; i < inputs_number; i++) {
        const tinyxml2::XMLElement *item_element = start_element->NextSiblingElement("Item");
        start_element = item_element;
        if (!item_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Inputs class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Item " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        item_element->QueryUnsignedAttribute("Index", &index);
        if (index != i + 1) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Inputs class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw std::logic_error(buffer.str());
        }

        // Name
        const tinyxml2::XMLElement *name_element = item_element->FirstChildElement("Name");
        if (name_element) {
            if (name_element->GetText())
                items[index - 1].name = name_element->GetText();
        }

        // Units
        const tinyxml2::XMLElement *units_element = item_element->FirstChildElement("Units");
        if (units_element) {
            if (units_element->GetText())
                items[index - 1].units = units_element->GetText();
        }

        // Description
        const tinyxml2::XMLElement *description_element = item_element->FirstChildElement("Description");
        if (description_element) {
            if (description_element->GetText())
                items[index - 1].description = description_element->GetText();
        }
    }
}

void Inputs::to_PMML(tinyxml2::XMLElement *element,
                     const bool &is_data_scaled,
                     const Vector<Statistics<double>> &inputs_statistics)
{
    std::string element_name(element->Name());
    tinyxml2::XMLDocument *pmml_document = element->GetDocument();
    const size_t inputs_number = get_inputs_number();

    if (element_name == "DataDictionary") {
        for (size_t i = 0; i < inputs_number; i++) {
            // Create input data field
            tinyxml2::XMLElement *data_field = pmml_document->NewElement("DataField");
            element->LinkEndChild(data_field);
            data_field->SetAttribute("dataType", "double");
            data_field->SetAttribute("name", get_name(i).c_str());
            data_field->SetAttribute("optype", "continuous");
            if (is_data_scaled && !inputs_statistics.empty()) {
                tinyxml2::XMLElement *interval = pmml_document->NewElement("Interval");
                data_field->LinkEndChild(interval);
                interval->SetAttribute("closure", "closedClosed");
                interval->SetAttribute("leftMargin", inputs_statistics.at(i).minimum);
                interval->SetAttribute("rightMargin", inputs_statistics.at(i).maximum);
            }
        }
    }

    if (element_name == "MiningSchema") {
        for (size_t i = 0; i < inputs_number; i++) {
            tinyxml2::XMLElement *mining_field = pmml_document->NewElement("MiningField");
            element->LinkEndChild(mining_field);
            mining_field->SetAttribute("name", get_name(i).c_str());
        }
    }

    if (element_name == "NeuralInputs") {
        for (size_t i = 0; i < inputs_number; i++) {
            // Neural input
            tinyxml2::XMLElement *neural_input = pmml_document->NewElement("NeuralInput");
            element->LinkEndChild(neural_input);
            neural_input->SetAttribute("id", ("0," + std::to_string(i)).c_str());

            // Derived field
            tinyxml2::XMLElement *derived_field = pmml_document->NewElement("DerivedField");
            neural_input->InsertFirstChild(derived_field);
            derived_field->SetAttribute("optype", "continuous");
            derived_field->SetAttribute("dataType", "double");

            // Field ref
            tinyxml2::XMLElement *field_ref = pmml_document->NewElement("FieldRef");
            derived_field->InsertFirstChild(field_ref);
            std::string field_ref_name(get_name(i));
            if (is_data_scaled) {
                field_ref_name.append("*");
            }
            field_ref->SetAttribute("field", field_ref_name.c_str());
        }
    }
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
