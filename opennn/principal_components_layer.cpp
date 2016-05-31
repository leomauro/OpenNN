/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P R I N C I P A L   C O M P O N E N T S   L A Y E R   C L A S S   H E A D E R                              */
/*                                                                                                              */
/*   Pablo Martin                                                                                               */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   pablomartin@artelnics.com                                                                                  */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "principal_components_layer.h"


namespace OpenNN {

/// Default constructor.
/// It creates a scaling layer object with no scaling neurons.
PrincipalComponentsLayer::PrincipalComponentsLayer()
{
    set();
}

/// Principal components neurons number constructor.
/// This constructor creates a principal components layer layer with a given size.
/// The members of this object are initialized with the default values.
/// @param new_principal_components_neurons_number Number of principal components neurons in the layer.
PrincipalComponentsLayer::PrincipalComponentsLayer(const size_t &new_principal_components_neurons_number)
{
    set(new_principal_components_neurons_number);
}

/// Copy constructor.
PrincipalComponentsLayer::PrincipalComponentsLayer(const PrincipalComponentsLayer &new_principal_components_layer)
{
    set(new_principal_components_layer);
}

/// Destructor.
PrincipalComponentsLayer::~PrincipalComponentsLayer()
{
}

/// Returns a matrix containing the eigenvectors of the variables.
Matrix<double> PrincipalComponentsLayer::get_eigenvectors() const
{
    return eigenvectors;
}

/// Returns a vector containing the means of every input variable in the data set.
Vector<double> PrincipalComponentsLayer::get_means() const
{
    return means;
}

/// Performs the principal component analysis to produce a reduced data set.
/// @param inputs Set of inputs to the principal components layer.
Vector<double> PrincipalComponentsLayer::calculate_outputs(const Vector<double> &inputs) const
{
    const size_t inputs_number = inputs.size();

#ifdef __OPENNN_DEBUG__
    if (eigenvectors.get_rows_number() != inputs_number) {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: PrincipalComponentsLayer class.\n"
               << "Vector<double> calculate_outputs(const Vector<double>&) const method.\n"
               << "Size of inputs must be equal to the number of rows of the eigenvectors matrix.\n";

        throw std::logic_error(buffer.str());
    }
#endif

    // Data adjust
    Vector<double> inputs_adjust(inputs_number);
    for (size_t i = 0; i < inputs_number; i++) {
        inputs_adjust[i] = inputs[i] - means[i];
    }

    // Outputs
    const size_t reduced_inputs_number = eigenvectors.get_rows_number();
    Vector<double> outputs(reduced_inputs_number);
    for (size_t i = 0; i < reduced_inputs_number; i++) {
        outputs[i] = eigenvectors.arrange_row(i).dot(inputs_adjust);
    }

    return outputs;
}

/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.
const bool &PrincipalComponentsLayer::get_display() const
{
    return display;
}

/// Sets the principal components layer to be empty
void PrincipalComponentsLayer::set()
{
    means.set();
    eigenvectors.set();

    set_default();
}

/// Sets a new size to the principal components layer.
/// It also sets the means to zero and the eigenvectors to identity.
void PrincipalComponentsLayer::set(const size_t &new_size)
{
    means.set(new_size, 0.0);
    eigenvectors.set_identity(new_size);

    set_default();
}

/// Sets the members of this object to be the members of another object of the same class.
/// @param new_scaling_layer Object to be copied.
void PrincipalComponentsLayer::set(const PrincipalComponentsLayer &new_principal_components_layer)
{
    eigenvectors = new_principal_components_layer.eigenvectors;
    means = new_principal_components_layer.means;
    display = new_principal_components_layer.display;
}

/// Sets a new value of the eigenvectors member.
/// @param new_eigenvectors Object to be set.
void PrincipalComponentsLayer::set_eigenvectors(const Matrix<double> &new_eigenvectors)
{
    eigenvectors = new_eigenvectors;
    means.set();

    set_default();
}

/// Sets a new value of the means member.
/// @param new_means Object to be set.
void PrincipalComponentsLayer::set_means(const Vector<double> &new_means)
{
    means = new_means;
}

/// Sets a new size and a new value to the means.
/// @param new_size New size of the vector means.
/// @param new_value New value of the vector means.
void PrincipalComponentsLayer::set_means(const size_t &new_size, const double &new_value)
{
    means.set(new_size, new_value);
}

/// Sets the members to their default value.
/// <ul>
/// <li> Display: true.
/// </ul>
void PrincipalComponentsLayer::set_default()
{
    set_display(true);
}

/// Returns the number of principal components in this layer.
size_t PrincipalComponentsLayer::get_principal_components_neurons_number() const
{
    return eigenvectors.get_rows_number();
}

/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
void PrincipalComponentsLayer::set_display(const bool &new_display)
{
    display = new_display;
}

/// Deserializes a TinyXML document into this principal components layer object.
/// @param document XML document containing the member data.
void PrincipalComponentsLayer::from_XML(const tinyxml2::XMLDocument &document)
{
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
