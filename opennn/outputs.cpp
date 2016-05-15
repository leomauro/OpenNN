/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   O U T P U T S   C L A S S                                                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "outputs.h"

#define numeric_to_string(x)    \
    (static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str())

namespace OpenNN
{
/// Default constructor.
/// It creates a outputs information object with zero outputs.
Outputs::Outputs(void)
{
    set();
}

/// Outputs number constructor.
/// It creates a outputs object with a given number of outputs.
/// This constructor initializes the members of the object to their default values.
/// @param new_outputs_number Number of outputs.
Outputs::Outputs(const size_t &new_outputs_number)
{
    set(new_outputs_number);
}

/// XML constructor.
/// It creates an outputs object and loads its members from a XML document.
/// @param outputs_document TinyXML document with the member data.
Outputs::Outputs(const tinyxml2::XMLDocument &outputs_document)
{
    from_XML(outputs_document);
}

/// Copy constructor.
/// It creates a copy of an existing outputs object.
/// @param other_outputs Outputs object to be copied.
Outputs::Outputs(const Outputs &other_outputs)
{
    set(other_outputs);
}

/// Destructor.
Outputs::~Outputs(void)
{
}

/// Assignment operator.
/// It assigns to this object the members of an existing outputs object.
/// @param other_outputs Outputs object to be assigned.
Outputs &Outputs::operator=(const Outputs &other_outputs)
{
    if (this != &other_outputs) {
        items = other_outputs.items;
        display = other_outputs.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_outputs Outputs object to be compared with.
bool Outputs::operator==(const Outputs &other_outputs) const
{
    return /*items == other_outputs.items &&*/ display == other_outputs.display;
}

/// Returns true if both the number of outputs is zero, and false otherwise.
bool Outputs::is_empty(void) const
{
    const size_t outputs_number = get_outputs_number();
    return outputs_number == 0;
}

/// Returns the names of the output variables.
/// Such names are only used to give the user basic information about the problem at hand.
Vector<std::string> Outputs::arrange_names(void) const
{
    const size_t outputs_number = get_outputs_number();
    Vector<std::string> names(outputs_number);
    for (size_t i = 0; i < outputs_number; i++) {
        names[i] = items[i].name;
    }
    return names;
}

/// Returns the name of a single output variable.
/// Such a name is only used to give the user basic information about the problem at hand.
/// @param index Index of output variable.
const std::string &Outputs::get_name(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "const std::string get_name(const size_t&) const method.\n"
               << "Output variable index must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].name;
}

/// Returns the descriptions of the output variables as strings.
/// Such descriptions are only used to give the user basic information about the problem at hand.
Vector<std::string> Outputs::arrange_descriptions(void) const
{
    return descriptions;
}

/// Returns the description of a single output variable as a string.
/// Such a description is only used to give the user basic information about the problem at hand.
/// @param index Index of output variable.
const std::string &Outputs::get_description(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "const std::string& get_description(const size_t&) const method.\n"
               << "Index of output variable must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return descriptions[index];
}

/// Returns the units of the output variables as strings.
/// Such units are only used to give the user basic information about the problem at hand.
Vector<std::string> Outputs::arrange_units(void) const
{
    return units;
}

/// Returns the units of a single output variable as a string.
/// Such units are only used to give the user basic information about the problem at hand.
/// @param index Index of output variable.
const std::string &Outputs::get_unit(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "const std::string get_unit(const size_t&) const method.\n"
               << "Index of output variable must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return units[index];
}

/// Returns all the available information about the outputs as a single matrix of strings.
/// The number of rows is the number of outputs.
/// The number of columns is three.
/// Each row contains the information of a single output (name, units and description).
Matrix<std::string> Outputs::arrange_information(void) const
{
    const size_t outputs_number = get_outputs_number();
    Matrix<std::string> information(outputs_number, 3);
    for (size_t i = 0; i < outputs_number; i++) {
        information(i, 0) = items[i].name;
        information(i, 1) = items[i].units;
        information(i, 2) = items[i].description;
    }
    return information;
}

/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.
const bool &Outputs::get_display(void) const
{
    return display;
}

/// Sets zero outputs.
/// It also sets the rest of members to their default values.
void Outputs::set(void)
{
    set_outputs_number(0);
    set_default();
}

/// Sets a new number of outputs.
/// It also sets the rest of members to their default values.
/// @param new_outputs_number Number of outputs.
void Outputs::set(const size_t &new_outputs_number)
{
    set_outputs_number(new_outputs_number);
    set_default();
}

/// Sets the members of this outputs object with those from another object of the same class.
/// @param other_outputs Outputs object to be copied.
void Outputs::set(const Outputs &other_outputs)
{
    items = other_outputs.items;
    display = other_outputs.display;
}

/// Sets all the outputs from a single vector of items.
/// @param new_items Output items.
void Outputs::set(const Vector<Item> &new_items)
{
    items = new_items;
}

/// Sets a new number of outputs.
/// @param new_outputs_number Number of outputs.
void Outputs::set_outputs_number(const size_t &new_outputs_number)
{
    items.set(new_outputs_number);
}

/// Sets the members of this object to their default values.
void Outputs::set_default(void)
{
    const size_t outputs_number = get_outputs_number();
    for (size_t i = 0; i < outputs_number; i++) {
        std::ostringstream buffer;
        buffer << "output_" << i + 1;
        items[i].name = buffer.str();
        items[i].units = "";
        items[i].description = "";
    }
    set_display(true);
}

/// Sets the names of the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_names New names for the output variables.
void Outputs::set_names(const Vector<std::string> &new_names)
{
    const size_t outputs_number = get_outputs_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_names.size();
    if (size != outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_names(const Vector<std::string>&) method.\n"
               << "Size of name of outputs vector must be equal to number of output variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < outputs_number; i++) {
        items[i].name = new_names[i];
    }
}

/// Sets the name of a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
/// @param index Index of output variable.
/// @param new_name New name for the output variable with index i.
void Outputs::set_name(const size_t &index, const std::string &new_name)
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_name(const size_t&, const std::string&) method.\n"
               << "Index of output variable must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[index].name = new_name;
}

/// Sets new units for all the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_units New units for the output variables.
void Outputs::set_units(const Vector<std::string> &new_units)
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    const size_t size = new_units.size();
    if (size != outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_units(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of output variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    units = new_units;
}

/// Sets new units for a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
/// @param index Index of output variable.
/// @param new_units New units for that output variable.
void Outputs::set_unit(const size_t &index, const std::string &new_units)
{
    const size_t outputs_number = get_outputs_number();

#ifdef __OPENNN_DEBUG__
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_units(const size_t&, const std::string&) method.\n"
               << "Index of output variable must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    if (units.size() != outputs_number)
        units.set(outputs_number);
    units[index] = new_units;
}

/// Sets new descriptions for all the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
/// @param new_descriptions New description for the output variables.
void Outputs::set_descriptions(const Vector<std::string> &new_descriptions)
{

#ifdef __OPENNN_DEBUG__
    const size_t size = new_descriptions.size();
    const size_t outputs_number = get_outputs_number();
    if (size != outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_descriptions(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    descriptions = new_descriptions;
}

/// Sets a new description for a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
/// @param index Index of output variable.
/// @param new_description New description for the output variable with index i.
void Outputs::set_description(const size_t &index, const std::string &new_description)
{
    const size_t outputs_number = get_outputs_number();

#ifdef __OPENNN_DEBUG__
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void set_description(const size_t&, const std::string&) method.\n"
               << "Index of output variable must be less than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    if (descriptions.size() != outputs_number)
        descriptions.set(outputs_number);
    descriptions[index] = new_description;
}

/// Sets all the possible information about the output variables.
/// The format is a vector of vectors of size three:
/// <ul>
/// <li> Name of output variables.
/// <li> Units of output variables.
/// <li> Description of output variables.
/// </ul>
/// @param new_information Output variables information.
void Outputs::set_information(const Matrix<std::string> &new_information)
{
    const size_t outputs_number = get_outputs_number();
    for (size_t i = 0; i < outputs_number; i++) {
        items[i].name = new_information(i, 0);
        items[i].units = new_information(i, 1);
        items[i].description = new_information(i, 2);
    }
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void Outputs::set_display(const bool &new_display)
{
    display = new_display;
}

/// Appends a new item to the outputs.
void Outputs::grow_output(void)
{
    const Item item;
    items.push_back(item);
}

/// Removes a given item from the outputs.
/// @param index Index of item to be pruned.
void Outputs::prune_output(const size_t &index)
{

#ifdef __OPENNN_DEBUG__
    const size_t outputs_number = get_outputs_number();
    if (index >= outputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void prune_output(const size_t&) method.\n"
               << "Index of output is equal or greater than number of outputs.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items.erase(items.begin() + index);
}

/// Returns the default names for the output variables:
/// <ul>
/// <li> output_1
/// <li> ...
/// <li> output_n
/// </ul>
Vector<std::string> Outputs::write_default_names(void) const
{
    const size_t outputs_number = get_outputs_number();
    Vector<std::string> default_names(outputs_number);
    for (size_t i = 0; i < outputs_number; i++) {
        std::ostringstream buffer;
        buffer << "output_" << i + 1;
        default_names[i] = buffer.str();
    }
    return default_names;
}

/// Returns a string representation of the current outputs object.
std::string Outputs::to_string(void) const
{
    std::ostringstream buffer;
    const size_t outputs_number = get_outputs_number();
    buffer << "Outputs\n";
    for (size_t i = 0; i < outputs_number; i++) {
        buffer << "Item " << i + 1 << ":\n"
               << "Name:" << items[i].name << "\n"
               << "Units:" << items[i].units << "\n"
               << "Description:" << items[i].description << "\n";
    }
    return buffer.str();
}

/// Serializes the outputs information object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
tinyxml2::XMLDocument *Outputs::to_XML(void) const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    const size_t outputs_number = get_outputs_number();
    std::ostringstream buffer;
    tinyxml2::XMLElement *outputs_element = document->NewElement("Outputs");
    document->InsertFirstChild(outputs_element);
    tinyxml2::XMLElement *element = NULL;
    tinyxml2::XMLText *text = NULL;

    // Outputs number
    {
        element = document->NewElement("OutputsNumber");
        outputs_element->LinkEndChild(element);
        buffer.str("");
        buffer << outputs_number;
        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    for (size_t i = 0; i < outputs_number; i++) {
        element = document->NewElement("Item");
        element->SetAttribute("Index", (unsigned) i + 1);
        outputs_element->LinkEndChild(element);

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

/// Deserializes a TinyXML document into this outputs object.
/// @param document XML document containing the member data.
void Outputs::from_XML(const tinyxml2::XMLDocument &document)
{
    const tinyxml2::XMLElement *outputs_element = document.FirstChildElement("Outputs");
    if (!outputs_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Outputs element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Outputs number
    const tinyxml2::XMLElement *outputs_number_element = outputs_element->FirstChildElement("OutputsNumber");
    if (!outputs_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Outputs class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Outputs number element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t outputs_number = atoi(outputs_number_element->GetText());
    set(outputs_number);
    unsigned index = 0; // size_t does not work
    const tinyxml2::XMLElement *start_element = outputs_number_element;
    for (size_t i = 0; i < outputs_number; i++) {
        const tinyxml2::XMLElement *item_element = start_element->NextSiblingElement("Item");
        start_element = item_element;
        if (!item_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Outputs class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Item " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }
        item_element->QueryUnsignedAttribute("Index", &index);
        if (index != i + 1) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Outputs class.\n"
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

void Outputs::to_PMML(tinyxml2::XMLElement *element,
                      const bool &is_probabilistic,
                      const bool &is_data_unscaled,
                      const Vector<Statistics<double>> &outputs_statistics)
{
    std::string element_name(element->Name());
    tinyxml2::XMLDocument *pmml_document = element->GetDocument();
    const size_t outputs_number = get_outputs_number();
    if (element_name == "DataDictionary") {
        if (is_probabilistic && outputs_number > 1) {
            tinyxml2::XMLElement *data_field = pmml_document->NewElement("DataField");
            element->LinkEndChild(data_field);
            data_field->SetAttribute("dataType", "string");
            data_field->SetAttribute("name", "classificationField");
            data_field->SetAttribute("optype", "categorical");
            for (size_t i = 0; i < outputs_number; i++) {
                std::string output_name = get_name(i);
                tinyxml2::XMLElement *value_field = pmml_document->NewElement("Value");
                data_field->LinkEndChild(value_field);
                value_field->SetAttribute("value", output_name.c_str());
            }
        } else {
            for (size_t i = 0; i < outputs_number; i++) {
                std::string output_name = get_name(i);
                tinyxml2::XMLElement *data_field = pmml_document->NewElement("DataField");
                element->LinkEndChild(data_field);
                data_field->SetAttribute("dataType", "double");
                data_field->SetAttribute("name", output_name.c_str());
                data_field->SetAttribute("optype", "continuous");
                if (is_data_unscaled && !outputs_statistics.empty()) {
                    tinyxml2::XMLElement *interval = pmml_document->NewElement("Interval");
                    data_field->LinkEndChild(interval);
                    interval->SetAttribute("closure", "closedClosed");
                    interval->SetAttribute("leftMargin", outputs_statistics.at(i).minimum);
                    interval->SetAttribute("rightMargin", outputs_statistics.at(i).maximum);
                }
            }
        }
    }

    if (element_name == "MiningSchema") {
        if (is_probabilistic && outputs_number > 1) {
            tinyxml2::XMLElement *mining_field = pmml_document->NewElement("MiningField");
            element->LinkEndChild(mining_field);
            mining_field->SetAttribute("name", "classificationField");
            mining_field->SetAttribute("usageType", "predicted");
        } else {
            for (size_t i = 0; i < outputs_number; i++) {
                std::string output_name = get_name(i);
                tinyxml2::XMLElement *mining_field = pmml_document->NewElement("MiningField");
                element->LinkEndChild(mining_field);
                mining_field->SetAttribute("name", output_name.c_str());
                mining_field->SetAttribute("usageType", "predicted");
            }
        }
    }

    if (element_name == "NeuralOutputs") {
        unsigned number_of_layers = element->Parent()->ToElement()->UnsignedAttribute("numberOfLayers");
        for (size_t i = 0; i < outputs_number; i++) {
            std::string output_name = get_name(i);
            tinyxml2::XMLElement *neural_output = pmml_document->NewElement("NeuralOutput");
            element->LinkEndChild(neural_output);
            std::string neural_output_id = std::to_string(number_of_layers);
            neural_output_id.append(",");
            neural_output_id.append(std::to_string(i));
            neural_output->SetAttribute("outputNeuron", neural_output_id.c_str());
            tinyxml2::XMLElement *derived_field = pmml_document->NewElement("DerivedField");
            neural_output->InsertFirstChild(derived_field);
            if (is_probabilistic && outputs_number > 1) {
                derived_field->SetAttribute("optype", "categorical");
                derived_field->SetAttribute("dataType", "string");
                tinyxml2::XMLElement *field_ref = pmml_document->NewElement("NormDiscrete");
                derived_field->InsertFirstChild(field_ref);
                field_ref->SetAttribute("field", "classificationField");
                field_ref->SetAttribute("value", output_name.c_str());
            } else {
                derived_field->SetAttribute("optype", "continuous");
                derived_field->SetAttribute("dataType", "double");
                tinyxml2::XMLElement *field_ref = pmml_document->NewElement("FieldRef");
                derived_field->InsertFirstChild(field_ref);
                std::string field_ref_name(output_name);
                if (is_data_unscaled)
                    field_ref_name.append("*");
                field_ref->SetAttribute("field", field_ref_name.c_str());
            }
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
