/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   V A R I A B L E S   C L A S S                                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "variables.h"


namespace OpenNN
{

/// Default constructor.
/// It creates a variables object with zero variables.
/// It also initializes the rest of class members to their default values.
Variables::Variables(void)
{
    set();
}

/// Variables number constructor.
/// It creates a variables object with a given number of variables.
/// All the variables are set as inputs but the last, which is set as targets.
/// It also initializes the rest of class members to their default values.
/// @param new_variables_number Number of variables.
Variables::Variables(const size_t &new_variables_number)
{
    set(new_variables_number);
}

/// Variables number constructor.
/// It creates a variables object with a given number of input and target variables.
/// It also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.
Variables::Variables(const size_t &new_inputs_number, const size_t &new_targets_number)
{
    set(new_inputs_number, new_targets_number);
}

/// XML constructor.
/// It creates a variables object and loads its members from a XML document.
/// @param variables_document TinyXML document with the member data.
Variables::Variables(const tinyxml2::XMLDocument &variables_document)
{
    set(variables_document);
}

/// Copy constructor.
/// It creates a copy of an existing variables object.
/// @param other_variables Variables object to be copied.
Variables::Variables(const Variables &other_variables)
{
    // Items
    items = other_variables.items;

    // Utilities
    display = other_variables.display;
}

/// Destructor.
Variables::~Variables(void)
{
}

/// Assignment operator.
/// It assigns to the current object the members of an existing variables object.
/// @param other_variables Variables object to be assigned.
Variables &Variables::operator=(const Variables &other_variables)
{
    if (this != &other_variables) {
        // Items
        items = other_variables.items;

        // Utilities
        display = other_variables.display;
    }
    return *this;
}

/// Equal to operator.
/// It compares this object with another object of the same class.
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_variables Variables object to be compared with.
bool Variables::operator==(const Variables &other_variables) const
{
    return /*items == other_variables.items &&*/ display == other_variables.display;
}

/// Returns the vector Item structures in the variables object.
const Vector<Variables::Item> &Variables::get_items(void) const
{
    return items;
}

/// Returns the information about a single variable.
/// @param i Index of variable.
const Variables::Item &Variables::get_item(const size_t &i) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "const Item& get_item(const size_t&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[i];
}

/// Returns true if the number of variables is zero, and false otherwise.
bool Variables::empty(void) const
{
    return items.empty();
}

/// Returns the number of variables which are either input or target.
size_t Variables::count_used_variables_number(void) const
{
    const size_t variables_number = get_variables_number();
    const size_t unused_variables_number = count_unused_variables_number();
    return variables_number - unused_variables_number;
}

/// Returns the number of variables which will neither be used as input nor as target.
size_t Variables::count_unused_variables_number(void) const
{
    const size_t variables_number = get_variables_number();
    size_t count = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Unused)
            count++;
    }
    return count;
}

/// Returns the number of input variables of the data set.
size_t Variables::count_inputs_number(void) const
{
    const size_t variables_number = get_variables_number();
    size_t count = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Input)
            count++;
    }
    return count;
}

/// Returns the number of target variables of the data set.
size_t Variables::count_targets_number(void) const
{
    const size_t variables_number = get_variables_number();
    size_t count = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Target)
            count++;
    }
    return count;
}

/// Returns a vector containing the numbers of input, target and unused variables,
/// respectively.
/// The size of that vector is three.
Vector<size_t> Variables::count_uses(void) const
{
    Vector<size_t> count(3, 0);
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Input) {
            count[0]++;
        } else if (items[i].use == Target) {
            count[1]++;
        } else {
            count[2]++;
        }
    }
    return count;
}

/// Returns a vector containing the use of each variable.
/// The size of the vector is equal to the number of variables.
Vector<Variables::Use> Variables::arrange_uses(void) const
{
    const size_t variables_number = get_variables_number();
    Vector<Variables::Use> uses(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        uses[i] = items[i].use;
    }
    return uses;
}

/// Returns a vector of strings with the use of each variable.
/// The size of the vector is equal to the number of variables.
/// The possible values for the elements are "Unused", "Input" and "Target".
Vector<std::string> Variables::write_uses(void) const
{
    const size_t variables_number = get_variables_number();
    Vector<std::string> uses_string(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Unused) {
            uses_string[i] = "Unused";
        } else if (items[i].use == Input) {
            uses_string[i] = "Input";
        } else if (items[i].use == Target) {
            uses_string[i] = "Target";
        } else {
            std::ostringstream buffer;

            buffer << "OpenNN Exception Variables class.\n"
                   << "Vector<std::string> write_uses(void) const method.\n"
                   << "Unknown use.\n";

            throw std::logic_error(buffer.str());
        }
    }
    return uses_string;
}

/// Returns the use of a single variable.
/// @param i Variable index.
const Variables::Use &Variables::get_use(const size_t &i) const
{
    return items[i].use;
}

/// Returns a string the use of a variable.
/// @param i Variable index.
std::string Variables::write_use(const size_t &i) const
{
    if (items[i].use == Unused) {
        return "Unused";
    } else if (items[i].use == Input) {
        return "Input";
    } else if (items[i].use == Target) {
        return "Target";
    } else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "std::string write_use(const size_t&) const method.\n"
               << "Unknown use.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Returns true if the use of a variable is an input, and false otherwise.
/// @param index Index of variable.
bool Variables::is_input(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "bool is_input(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].use == Variables::Input;
}

/// Returns true if the use of a variable is a target, and false otherwise.
/// @param index Index of variable.
bool Variables::is_target(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "bool is_target(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].use == Variables::Target;
}

/// Returns true if the use of a variable is neither an input nor a target, and false otherwise.
/// @param index Index of variable.
bool Variables::is_unused(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "bool is_unused(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].use == Variables::Unused;
}

/// Returns true if the use of a variable is either input or target, and false if it is unused.
/// @param index Index of variable.
bool Variables::is_used(const size_t &index) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (index >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "bool is_used(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[index].use != Variables::Unused;
}

/// Returns all the available information about the variables as a matrix of strings.
/// The number of rows is the number of variables.
/// The number of columns is four.
/// Each row contains the information of a single variable (name, units, description and use).
Matrix<std::string> Variables::arrange_information(void) const
{
    const size_t variables_number = get_variables_number();
    Matrix<std::string> information(variables_number, 4);
    for (size_t i = 0; i < variables_number; i++) {
        information(i, 0) = items[i].name;
        information(i, 1) = items[i].units;
        information(i, 2) = items[i].description;
        information(i, 3) = write_use(i);
    }
    return information;
}

/// Returns the indices of the used variables (those which are not set unused).
Vector<size_t> Variables::arrange_used_indices(void) const
{
    const size_t variables_number = get_variables_number();
    const size_t used_variables_number = count_used_variables_number();
    Vector<size_t> used_indices(used_variables_number);
    size_t index = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Input || items[i].use == Target) {
            used_indices[index] = i;
            index++;
        }
    }
    return used_indices;
}

/// Returns the indices of the input variables.
Vector<size_t> Variables::arrange_inputs_indices(void) const
{
    const size_t variables_number = get_variables_number();
    const size_t inputs_number = count_inputs_number();
    Vector<size_t> inputs_indices(inputs_number);
    size_t index = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Input) {
            inputs_indices[index] = i;
            index++;
        }
    }
    return inputs_indices;
}

/// Returns the indices of the target variables.
Vector<size_t> Variables::arrange_targets_indices(void) const
{
    const size_t variables_number = get_variables_number();
    const size_t targets_number = count_targets_number();
    Vector<size_t> targets_indices(targets_number);
    size_t index = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Target) {
            targets_indices[index] = i;
            index++;
        }
    }
    return targets_indices;
}

/// Returns the indices of the unused variables.
Vector<size_t> Variables::arrange_unused_indices(void) const
{
    const size_t variables_number = get_variables_number();
    const size_t unused_number = count_unused_variables_number();
    Vector<size_t> unused_indices(unused_number);
    size_t index = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].use == Unused) {
            unused_indices[index] = i;
            index++;
        }
    }
    return unused_indices;
}

/// Returns the names of all the variables in the data set.
Vector<std::string> Variables::arrange_names(void) const
{
    const size_t variables_number = get_variables_number();
    Vector<std::string> names(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        names[i] = items[i].name;
    }
    return names;
}

/// Returns the names of the used variables in the data set.
Vector<std::string> Variables::arrange_used_names(void) const
{
    const size_t variables_number = get_variables_number();
    const Vector<size_t> used_variables_indices = arrange_used_indices();
    const size_t used_variables_number = count_used_variables_number();
    Vector<std::string> names(used_variables_number);
    size_t index = 0;
    for (size_t i = 0; i < variables_number; i++) {
        if (used_variables_indices.contains(i)) {
            names[index] = items[i].name;
            index++;
        }
    }
    return names;
}

/// Returns the name of a single variable in the data set.
/// @param i Index of variable.
const std::string &Variables::get_name(const size_t &i) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "std::string& get_name(size_t) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[i].name;
}

/// Returns true if all the variables have been named, and false otherwise.
bool Variables::has_names(void) const
{
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        if (items[i].name.empty())
            return false;
    }
    return true;
}

/// Returns the names of the input variables in the data set.
Vector<std::string> Variables::arrange_inputs_name(void) const
{
    const size_t inputs_number = count_inputs_number();
    const Vector<size_t> inputs_indices = arrange_inputs_indices();
    Vector<std::string> inputs_name(inputs_number);
    size_t index;
    for (size_t i = 0; i < inputs_number; i++) {
        index = inputs_indices[i];
        inputs_name[i] = items[index].name;
    }
    return inputs_name;
}

/// Returns the names of the target variables in the data set.
Vector<std::string> Variables::arrange_targets_name(void) const
{
    const size_t targets_number = count_targets_number();
    const Vector<size_t> targets_indices = arrange_targets_indices();
    Vector<std::string> targets_name(targets_number);
    size_t index;
    for (size_t i = 0; i < targets_number; i++) {
        index = targets_indices[i];
        targets_name[i] = items[index].name;
    }
    return targets_name;
}

/// Returns the units of all the variables in the data set.
Vector<std::string> Variables::arrange_units(void) const
{
    const size_t variables_number = get_variables_number();
    Vector<std::string> units(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        units[i] = items[i].units;
    }
    return units;
}

/// Returns the units of a single variable in the data set.
/// @param i Index of variable.
const std::string &Variables::get_unit(const size_t &i) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "const std::string& get_units(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[i].units;
}

/// Returns the units of the input variables in the data set.
Vector<std::string> Variables::arrange_inputs_units(void) const
{
    const Vector<size_t> inputs_indices = arrange_inputs_indices();
    const size_t inputs_number = count_inputs_number();
    Vector<std::string> inputs_units(inputs_number);
    size_t index;
    for (size_t i = 0; i < inputs_number; i++) {
        index = inputs_indices[i];
        inputs_units[i] = items[index].units;
    }
    return inputs_units;
}

/// Returns the units of the target variables in the data set.
Vector<std::string> Variables::arrange_targets_units(void) const
{
    const Vector<size_t> targets_indices = arrange_targets_indices();
    const size_t targets_number = count_targets_number();
    Vector<std::string> targets_units(targets_number);
    size_t index;
    for (size_t i = 0; i < targets_number; i++) {
        index = targets_indices[i];
        targets_units[i] = items[index].units;
    }
    return targets_units;
}

/// Returns the description of all the variables in the data set.
Vector<std::string> Variables::arrange_descriptions(void) const
{
    const size_t variables_number = get_variables_number();
    Vector<std::string> descriptions(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        descriptions[i] = items[i].description;
    }
    return descriptions;
}

/// Returns the description of a single variable in the data set.
/// @param i Index of variable.
const std::string &Variables::get_description(const size_t &i) const
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "const std::string& get_description(const size_t&) const method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    return items[i].description;
}

/// Returns the description of the input variables in the data set.
Vector<std::string> Variables::arrange_inputs_description(void) const
{
    const size_t inputs_number = count_inputs_number();
    const Vector<size_t> inputs_indices = arrange_inputs_indices();
    Vector<std::string> inputs_description(inputs_number);
    size_t index;
    for (size_t i = 0; i < inputs_number; i++) {
        index = inputs_indices[i];
        inputs_description[i] = items[index].description;
    }
    return inputs_description;
}

/// Returns the description of the target variables in the data set.
Vector<std::string> Variables::arrange_targets_description(void) const
{
    const Vector<size_t> targets_indices = arrange_targets_indices();
    const size_t targets_number = count_targets_number();
    Vector<std::string> target_descriptions(targets_number);
    size_t index;
    for (size_t i = 0; i < targets_number; i++) {
        index = targets_indices[i];
        target_descriptions[i] = items[index].description;
    }
    return target_descriptions;
}

/// Returns a single matrix with the names, units and descriptions of all the input variables.
/// The number of rows is the number of inputs, and the number of columns is 3.
Matrix<std::string> Variables::arrange_inputs_information(void) const
{
    const size_t inputs_number = count_inputs_number();
    const Vector<size_t> inputs_indices = arrange_inputs_indices();
    size_t input_index;
    Matrix<std::string> inputs_information(inputs_number, 3);
    for (size_t i = 0; i < inputs_number; i++) {
        input_index = inputs_indices[i];
        inputs_information(i, 0) = items[input_index].name;
        inputs_information(i, 1) = items[input_index].units;
        inputs_information(i, 2) = items[input_index].description;
    }
    return inputs_information;
}

/// Returns a single matrix with the names, units and descriptions of all the target variables.
/// The number of rows is the number of targets, and the number of columns is 3.
Matrix<std::string> Variables::arrange_targets_information(void) const
{
    const size_t targets_number = count_targets_number();
    const Vector<size_t> targets_indices = arrange_targets_indices();
    size_t target_index;
    Matrix<std::string> targets_information(targets_number, 3);
    for (size_t i = 0; i < targets_number; i++) {
        target_index = targets_indices[i];
        targets_information(i, 0) = items[target_index].name;
        targets_information(i, 1) = items[target_index].units;
        targets_information(i, 2) = items[target_index].description;
    }
    return targets_information;
}

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.
const bool &Variables::get_display(void) const
{
    return display;
}

/// Sets a variables object with zero variables.
void Variables::set(void)
{
    set_variables_number(0);
    set_default();
}

/// Sets a new number of variables in the current object.
/// All the variables are set as inputs, but the last one, wich is set as targets.
/// @param new_variables_number Number of variables.

void Variables::set(const size_t &new_variables_number)
{
    set_variables_number(new_variables_number);
    set_default();
}

/// Sets new numbers of of inputs and target variables in the current object.
/// The total number of variables is the number of inputs plus the number of targets.
/// The first variables are set as inputs, and last ones are set as targets.
/// @param inputs_number Number of input variables.
/// @param targets_number Number of target variables.
void Variables::set(const size_t &inputs_number, const size_t &targets_number)
{
    const size_t variables_number = inputs_number + targets_number;
    set_variables_number(variables_number);
    for (size_t i = 0; i < inputs_number; i++) {
        items[i].use = Input;
    }
    for (size_t i = inputs_number; i < variables_number; i++) {
        items[i].use = Target;
    }
    set_default();
}

/// Sets the variables information members from a XML document.
/// @param variables_document Pointer to a TinyXML document containing the member data.
void Variables::set(const tinyxml2::XMLDocument &variables_document)
{
    set_default();
    from_XML(variables_document);
}

/// Sets the default values to the variables object:
/// <ul>
/// <li>display: true</li>
/// </ul>
void Variables::set_default(void)
{
    display = true;
}

/// Sets new variable items in this object.
/// @param new_items Vector of item structures to be set.
void Variables::set_items(const Vector<Item> &new_items)
{
    items = new_items;
}

/// Sets new uses for the all the variables from a single vector.
/// It does not modify the other information on the variables (name, units or description).
/// @param new_uses Vector of use elements.
void Variables::set_uses(const Vector<Variables::Use> &new_uses)
{
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        items[i].use = new_uses[i];
    }
}

/// Sets new uses for the all the variables from a vector of strings.
/// The possible values for that strings are "Input", "Target" and "Unused".
/// @param new_uses Vector of use strings.
void Variables::set_uses(const Vector<std::string> &new_uses)
{
    const size_t new_variables_number = new_uses.size();
    for (size_t i = 0; i < new_variables_number; i++) {
        if (new_uses[i] == "Input") {
            items[i].use = Input;
        } else if (new_uses[i] == "Target") {
            items[i].use = Target;
        } else if (new_uses[i] == "Unused") {
            items[i].use = Unused;
        } else {
            std::ostringstream buffer;

            buffer << "OpenNN Exception Variables class.\n"
                   << "void set_uses(const Vector<std::string>&) method.\n"
                   << "Unknown use: " << new_uses[i] << "\n";

            throw std::logic_error(buffer.str());
        }
    }
}

/// Sets the use of a single variable.
/// @param i Index of variable.
/// @param new_use Use for that variable.
void Variables::set_use(const size_t &i, const Use &new_use)
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "void set_use(const size_t&, const Use&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[i].use = new_use;
}

/// Sets the use of a single variable from a string.
/// The possible values for that string are "Unused", "Input" and "Target".
/// @param i Index of variable.
/// @param new_use Use for that variable.
void Variables::set_use(const size_t &i, const std::string &new_use)
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "void set_use(const size_t&, const std::string&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    if (new_use == "Unused") {
        items[i].use = Unused;
    } else if (new_use == "Input") {
        items[i].use = Input;
    } else if (new_use == "Target") {
        items[i].use = Target;
    } else {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "void set_use(const std::string&) method.\n"
               << "Unknown use.\n";

        throw std::logic_error(buffer.str());
    }
}

/// Sets all the variables in the data set as input variables.
void Variables::set_input(void)
{
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        items[i].use = Input;
    }
}

/// Sets all the variables in the data set as target variables.
void Variables::set_target(void)
{
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        items[i].use = Target;
    }
}

/// Sets all the variables in the data set as unused variables.
void Variables::set_unuse(void)
{
    const size_t variables_number = get_variables_number();
    for (size_t i = 0; i < variables_number; i++) {
        items[i].use = Unused;
    }
}

/// Sets the default uses for the input and target variables:
/// <ul>
/// <li> Input indices: 0, ..., variables number-2.
/// <li> Target indices: variables number-1.
/// </ul>
void Variables::set_default_uses(void)
{
    const size_t variables_number = get_variables_number();
    if (variables_number == 0) {
        return;
    }

    if (variables_number == 1)
        items[0].use = Unused;
    else {
        set_input();

        items[variables_number - 1].use = Target;
    }
}

/// Sets new names for the variables in the data set from a vector of strings.
/// The size of that vector must be equal to the total number of variables.
/// @param new_names Name of variables.
void Variables::set_names(const Vector<std::string> &new_names)
{
    const size_t variables_number = get_variables_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_names.size();
    if (size != variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_names(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < variables_number; i++) {
        items[i].name = new_names[i];
    }
}

/// This method set the name of a single variable.
/// If the vector of names is zero the rest of elements are initialized as empty strings.
/// @param i Index of variable.
/// @param new_name Name of variable.
void Variables::set_name(const size_t &i, const std::string &new_name)
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_name(const size_t&, const std::string&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[i].name = new_name;
}

/// Sets new units for the variables in the data set from a vector of strings.
/// The size of that vector must be equal to the total number of variables.
/// @param new_units Units of variables.
void Variables::set_units(const Vector<std::string> &new_units)
{
    const size_t variables_number = get_variables_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_units.size();
    if (size != variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_units(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < variables_number; i++) {
        items[i].units = new_units[i];
    }
}

/// This method set the units of a single variable.
/// If the vector of units is zero the rest of elements are initialized as empty strings.
/// @param i Index of variable.
/// @param new_units Units of variable.
void Variables::set_units(const size_t &i, const std::string &new_units)
{
#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_units(const size_t&, const std::string&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[i].units = new_units;
}

/// Sets new descriptions for the variables in the data set from a vector of strings.
/// The size of that vector must be equal to the total number of variables.
/// @param new_descriptions Description of variables.
void Variables::set_descriptions(const Vector<std::string> &new_descriptions)
{
    const size_t variables_number = get_variables_number();

#ifdef __OPENNN_DEBUG__
    const size_t size = new_descriptions.size();

    if (size != variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_descriptions(const Vector<std::string>&) method.\n"
               << "Size must be equal to number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    for (size_t i = 0; i < variables_number; i++) {
        items[i].description = new_descriptions[i];
    }
}

/// This method sets the description of a single variable.
/// If the vector of descriptions is zero the rest of elements are initialized as empty strings.
/// @param i Index of variable.
/// @param new_description Description of variable.
void Variables::set_description(const size_t &i, const std::string &new_description)
{

#ifdef __OPENNN_DEBUG__
    const size_t variables_number = get_variables_number();
    if (i >= variables_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_description(const size_t&, const std::string&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    items[i].description = new_description;
}

/// Sets the names of the variables from a vector of vectors of names.
/// This method is used when loading a data file with nominal values.
/// @param columns_name Names of columns in the data file.
/// @param nominal_labels Values of all nominal variables in the data file.
void Variables::set_names(const Vector<std::string> &columns_name,
                          const Vector<Vector<std::string>> &nominal_labels)
{

#ifdef __OPENNN_DEBUG__
    if (columns_name.size() != nominal_labels.size()) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void set_names(const Vector<std::string>& , const Vector< Vector<std::string> >&) method.\n"
               << "Size of columns name (" << columns_name.size() << ") must be equal to size of nominal labels " << nominal_labels.size() << ".\n";

        throw std::logic_error(buffer.str());
    }
#endif

    Vector<std::string> names;
    for (size_t i = 0; i < nominal_labels.size(); i++) {
        if (nominal_labels[i].size() == 0) {
            names.push_back(columns_name[i]);
        } else if (nominal_labels[i].size() == 2) {
            if (nominal_labels[i].contains("true") ||
                nominal_labels[i].contains("True") ||
                nominal_labels[i].contains("TRUE")) {
                names.push_back(columns_name[i] + "_true");
            } else if (nominal_labels[i].contains("positive") ||
                       nominal_labels[i].contains("Positive") ||
                       nominal_labels[i].contains("POSITIVE")) {
                names.push_back(columns_name[i] + "positive");
            } else {
                names.push_back(columns_name[i]);
            }
        } else {
            for (size_t j = 0; j < nominal_labels[i].size(); j++) {
                names.push_back(nominal_labels[i][j]);
            }
        }
    }
    set_names(names);
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void Variables::set_display(const bool &new_display)
{
    display = new_display;
}

/// Converts the variables when the data set is to be used for time series prediction.
/// This method modifies the number of variables.
/// The new number of variables will be variables_number*(1+lags_number).
void Variables::convert_time_series(const size_t &lags_number)
{
    const size_t variables_number = get_variables_number();
    const size_t new_variables_number = variables_number * (1 + lags_number);
    Vector<Item> new_items(new_variables_number);
    size_t index = 0;
    for (size_t i = 0; i < 1 + lags_number; i++) {
        for (size_t j = 0; j < variables_number; j++) {
            new_items[index].name = items[j].name;
            new_items[index].units = items[j].units;
            new_items[index].description = items[j].description;
            if (i != lags_number) {
                new_items[index].name.append("_lag_").append(unsigned_to_string(lags_number - i));
                new_items[index].use = Variables::Input;
            } else {
                new_items[index].use = Variables::Target;
            }
            index++;
        }
    }
    set_items(new_items);
}

/// Arranges the variables in a proper format for autoassociation.
/// The number of variables is doubled.
/// The first half will be set as inputs, and the second half as targets.
void Variables::convert_autoassociation(void)
{
    const size_t variables_number = get_variables_number();
    set_input();
    Vector<Item> autoassociation_items(variables_number);
    for (size_t i = 0; i < variables_number; i++) {
        autoassociation_items[i].name = prepend("autoassociation_", items[i].name);
        autoassociation_items[i].units = items[i].units;
        autoassociation_items[i].description = items[i].description;
        autoassociation_items[i].use = Variables::Target;
    }
    set_items(items.assemble(autoassociation_items));
}

/// Sets a new number of variables in the variables object.
/// All variables are set as inputs but the last one, which is set as targets.
/// @param new_variables_number Number of variables.
void Variables::set_variables_number(const size_t &new_variables_number)
{
    items.set(new_variables_number);
    set_default_uses();
}

/// Returns a string representation of the current variables object.
std::string Variables::to_string(void) const
{
    std::ostringstream buffer;

    const size_t variables_number = get_variables_number();
    const size_t inputs_number = count_inputs_number();
    const size_t targets_number = count_targets_number();

    buffer << "Variables object\n"
           << "Variables number: " << variables_number << "\n"
           << "Inputs number: " << inputs_number << "\n"
           << "Target number: " << targets_number << "\n";

    buffer << "Items:\n";
    const Vector<std::string> uses_string = write_uses();
    for (size_t i = 0; i < variables_number; i++) {
        buffer << "Variable " << i + 1 << ":\n"
               << "Name: " << items[i].name << "\n"
               << "Units: " << items[i].units << "\n"
               << "Description: " << items[i].description << "\n"
               << "Use: " << write_use(i) << "\n";
    }
    return buffer.str();
}

/// Serializes the variables object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.
tinyxml2::XMLDocument *Variables::to_XML(void) const
{
    tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument;
    std::ostringstream buffer;

    // Variables
    tinyxml2::XMLElement *variables_element = document->NewElement("Variables");
    document->InsertFirstChild(variables_element);
    tinyxml2::XMLElement *element = NULL;
    tinyxml2::XMLText *text = NULL;
    const size_t variables_number = get_variables_number();

    // Variables number
    element = document->NewElement("VariablesNumber");
    variables_element->LinkEndChild(element);
    buffer.str("");
    buffer << variables_number;
    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    for (size_t i = 0; i < variables_number; i++) {
        element = document->NewElement("Item");
        element->SetAttribute("Index", (unsigned) i + 1);
        variables_element->LinkEndChild(element);

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

        // Use
        tinyxml2::XMLElement *use_element = document->NewElement("Use");
        element->LinkEndChild(use_element);
        tinyxml2::XMLText *use_text = document->NewText(write_use(i).c_str());
        use_element->LinkEndChild(use_text);
    }

    return document;
}

/// Deserializes a TinyXML document into this variables object.
/// @param document XML document containing the member data.
void Variables::from_XML(const tinyxml2::XMLDocument &document)
{
    unsigned index = 0;

    // Variables
    const tinyxml2::XMLElement *variables_element = document.FirstChildElement("Variables");
    if (!variables_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to variables element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Variables number
    const tinyxml2::XMLElement *variables_number_element = variables_element->FirstChildElement("VariablesNumber");
    if (!variables_number_element) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to variables number is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const size_t variables_number = atoi(variables_number_element->GetText());
    set_variables_number(variables_number);

    // Items
    const tinyxml2::XMLElement *start_element = variables_number_element;
    for (size_t i = 0; i < variables_number; i++) {
        const tinyxml2::XMLElement *item_element = start_element->NextSiblingElement("Item");
        start_element = item_element;
        if (!item_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Variables class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Item " << i + 1 << " is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        item_element->QueryUnsignedAttribute("Index", &index);
        if (index != i + 1) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Variables class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw std::logic_error(buffer.str());
        }

        // Name
        const tinyxml2::XMLElement *name_element = item_element->FirstChildElement("Name");
        if (name_element && name_element->GetText())
            items[index - 1].name = name_element->GetText();

        // Units
        const tinyxml2::XMLElement *units_element = item_element->FirstChildElement("Units");
        if (units_element && units_element->GetText())
            items[index - 1].units = units_element->GetText();

        // Description
        const tinyxml2::XMLElement *description_element = item_element->FirstChildElement("Description");
        if (description_element && description_element->GetText())
            items[index - 1].description = description_element->GetText();

        // Use
        const tinyxml2::XMLElement *use_element = item_element->FirstChildElement("Use");
        if (!use_element) {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: Variables class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Pointer to use element is NULL.\n";

            throw std::logic_error(buffer.str());
        }

        if (use_element->GetText())
            set_use(index - 1, use_element->GetText());
    }
}

/// Returns the string representation of number of type size_t.
std::string Variables::unsigned_to_string(const size_t &number)
{
    std::ostringstream buffer;
    buffer << number;
    return buffer.str();
}

/// Prepends the string pre to the beginning of the string str and returns the whole string.
std::string Variables::prepend(const std::string &pre, const std::string &str)
{
    std::ostringstream buffer;
    buffer << pre << str;
    return buffer.str();
}


}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2015 Roberto Lopez
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
