/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   D A T A   S E T   C L A S S   H E A D E R                                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __DATASET_H__
#define __DATASET_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <exception>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "missing_values.h"
#include "variables.h"
#include "instances.h"

// TinyXml includes

#include <tinyxml2.h>
#include "tinyxml2-deepclone.h"

namespace OpenNN
{

/// This class represents the concept of data set for data modelling problems,
/// such as function regression, pattern recognition and time series prediction.
/// It basically consists of a data matrix plus variables and instances objects.
class DataSet
{
public:

    // DEFAULT CONSTRUCTOR
    explicit DataSet();

    // DATA CONSTRUCTOR
    explicit DataSet(const Matrix<double> &);

    // INSTANCES AND VARIABLES CONSTRUCTOR
    explicit DataSet(const size_t &, const size_t &);

    // INSTANCES, INPUTS AND TARGETS CONSTRUCTOR
    explicit DataSet(const size_t &, const size_t &, const size_t &);

    // XML CONSTRUCTOR
    explicit DataSet(const tinyxml2::XMLDocument &);

    // FILE CONSTRUCTOR
    explicit DataSet(const std::string &);

    // COPY CONSTRUCTOR
    DataSet(const DataSet &);

    // DESTRUCTOR
    virtual ~DataSet();

    // ASSIGNMENT OPERATOR
    DataSet &operator=(const DataSet &);

    // EQUAL TO OPERATOR
    bool operator==(const DataSet &) const;

    /// Enumeration of available separators for the data file.
    enum Separator {
        Space, Tab, Comma, Semicolon
    };

    /// Enumeration of available methods for scaling and unscaling the data.
    enum ScalingUnscalingMethod {
        MinimumMaximum, MeanStandardDeviation
    };

    /// Enumeration of the units used for angular variables.
    enum AngularUnits {
        Radians, Degrees
    };

    /// Enumeration of the file types
    enum FileType {
        TXT, DAT, DATA, CSV, ODS, XLSX, ARFF
    };

    /// Enumeration of the learning tasks
    enum LearningTask {
        FunctionRegression, PatternRecognition, TimeSeriesPrediction, Autoassociation
    };

    // Get methods
    FileType get_file_type() const;

    std::string write_file_type() const;

    std::string write_first_cell() const;

    std::string write_last_cell() const;

    size_t write_sheet_number() const;

    LearningTask get_learning_task() const;

    std::string write_learning_task() const;

    const std::string &get_data_file_name() const;

    const bool &get_header_line() const;

    const bool &get_rows_label() const;

    const Separator &get_separator() const;

    std::string get_separator_string() const;

    std::string write_separator() const;

    const std::string &get_missing_values_label() const;

    const size_t &get_lags_number() const;

    const size_t &get_steps_ahead() const;

    const bool &get_autoassociation() const;

    const Vector<size_t> &get_angular_variables() const;

    const AngularUnits &get_angular_units() const;

    static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string &);

    const MissingValues &get_missing_values() const;

    MissingValues *get_missing_values_pointer();

    const Variables &get_variables() const;

    Variables *get_variables_pointer();

    const Instances &get_instances() const;

    Instances *get_instances_pointer();

    const bool &get_display() const;

    bool is_binary_classification() const;

    bool is_multiple_classification() const;

    bool is_binary_variable(const size_t &) const;

    // Data methods
    bool empty() const;

    const Matrix<double> &get_data() const;

    const Matrix<double> &get_time_series_data() const;

    Matrix<double> arrange_training_data() const;

    Matrix<double> arrange_selection_data() const;

    Matrix<double> arrange_testing_data() const;

    Matrix<double> arrange_target_data() const;

    Matrix<double> arrange_training_input_data() const;

    Matrix<double> arrange_training_target_data() const;

    Matrix<double> get_selection_input_data() const;

    Matrix<double> get_selection_target_data() const;

    Matrix<double> arrange_testing_input_data() const;

    Matrix<double> arrange_testing_target_data() const;

    // Instance methods
    Vector<double> get_instance(const size_t &) const;

    Vector<double> get_instance(const size_t &, const Vector<size_t> &) const;

    // Variable methods
    Vector<double> get_variable(const size_t &) const;

    Vector<double> get_variable(const size_t &, const Vector<size_t> &) const;

    // Set methods
    void set();

    void set(const Matrix<double> &);

    void set(const size_t &, const size_t &);

    void set(const size_t &, const size_t &, const size_t &);

    void set(const DataSet &);

    void set(const tinyxml2::XMLDocument &);

    void set(const std::string &);

    // Data methods
    void set_data(const Matrix<double> &);

    void set_instances_number(const size_t &);

    void set_variables_number(const size_t &);

    void set_data_file_name(const std::string &);

    void set_file_type(const FileType &);

    void set_file_type(const std::string &);

    void set_header_line(const bool &);

    void set_rows_label(const bool &);

    void set_separator(const Separator &);

    void set_separator(const std::string &);

    void set_missing_values_label(const std::string &);

    void set_lags_number(const size_t &);

    void set_steps_ahead_number(const size_t &);

    void set_autoassociation(const bool &);

    void set_learning_task(const LearningTask &);

    void set_learning_task(const std::string &);

    void set_angular_variables(const Vector<size_t> &);

    void set_angular_units(AngularUnits &);

    // Utilities
    void set_display(const bool &);

    void set_default();

    // Instance methods
    void set_instance(const size_t &, const Vector<double> &);

    // Data resizing methods
    void add_instance(const Vector<double> &);

    void subtract_instance(const size_t &);

    void append_variable(const Vector<double> &);

    void subtract_variable(const size_t &);

    Vector<size_t> unuse_constant_variables();

    Vector<size_t> unuse_repeated_instances();

    Vector<size_t> unuse_non_significant_inputs();

    // Initialization methods
    void initialize_data(const double &);

    void randomize_data_uniform(const double &minimum = -1.0, const double &maximum = 1.0);

    void randomize_data_normal(const double &mean = 0.0, const double &standard_deviation = 1.0);

    // Statistics methods
    Vector<Statistics<double>> calculate_data_statistics() const;

    Vector<Vector<double>> calculate_data_shape_parameters() const;

    Matrix<double> calculate_data_statistics_matrix() const;

    Matrix<double> calculate_data_shape_parameters_matrix() const;

    Vector<Statistics<double>> calculate_training_instances_statistics() const;

    Vector<Statistics<double>> calculate_selection_instances_statistics() const;

    Vector<Statistics<double>> calculate_testing_instances_statistics() const;

    Vector<Vector<double>> calculate_training_instances_shape_parameters() const;

    Vector<Vector<double>> calculate_selection_instances_shape_parameters() const;

    Vector<Vector<double>> calculate_testing_instances_shape_parameters() const;

    Vector<Statistics<double>> calculate_inputs_statistics() const;

    Vector<Statistics<double>> calculate_targets_statistics() const;

    Vector<double> calculate_training_target_data_mean() const;

    Vector<double> calculate_selection_target_data_mean() const;

    Vector<double> calculate_testing_target_data_mean() const;

    // Correlation methods
    Matrix<double> calculate_linear_correlations() const;

    // Principal components mehtod
    Matrix<double> calculate_covariance_matrix() const;

    Matrix<double> perform_principal_components_analysis(const double & = 0.0);

    // Histrogram methods
    Vector<Histogram<double>> calculate_data_histograms(const size_t & = 10) const;

    Vector<Histogram<double>> calculate_targets_histograms(const size_t & = 10) const;

    // Box and whiskers
    Vector<Vector<double>> calculate_box_plots() const;

    size_t calculate_training_negatives(const size_t &) const;

    size_t calculate_selection_negatives(const size_t &) const;

    size_t calculate_testing_negatives(const size_t &) const;

    // Filtering methods
    Vector<size_t> filter_data(const Vector<double> &, const Vector<double> &);

    // Data scaling
    void scale_data_minimum_maximum(const Vector<Statistics<double>> &);

    void scale_data_mean_standard_deviation(const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_data_minimum_maximum();

    Vector<Statistics<double>> scale_data_mean_standard_deviation();

    void scale_data(const std::string &, const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_data(const std::string &);

    // Input variables scaling
    void scale_inputs_minimum_maximum(const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_inputs_minimum_maximum();

    void scale_inputs_mean_standard_deviation(const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_inputs_mean_standard_deviation();

    Vector<Statistics<double>> scale_inputs(const std::string &);

    void scale_inputs(const std::string &, const Vector<Statistics<double>> &);

    // Target variables scaling
    void scale_targets_minimum_maximum(const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_targets_minimum_maximum();

    void scale_targets_mean_standard_deviation(const Vector<Statistics<double>> &);

    Vector<Statistics<double>> scale_targets_mean_standard_deviation();

    Vector<Statistics<double>> scale_targets(const std::string &);

    void scale_targets(const std::string &, const Vector<Statistics<double>> &);

    // Data unscaling
    void unscale_data_minimum_maximum(const Vector<Statistics<double>> &);

    void unscale_data_mean_standard_deviation(const Vector<Statistics<double>> &);

    // Input variables unscaling
    void unscale_inputs_minimum_maximum(const Vector<Statistics<double>> &);

    void unscale_inputs_mean_standard_deviation(const Vector<Statistics<double>> &);

    // Target variables unscaling
    void unscale_targets_minimum_maximum(const Vector<Statistics<double>> &);

    void unscale_targets_mean_standard_deviation(const Vector<Statistics<double>> &);

    // Pattern recognition methods
    Vector<size_t> calculate_target_distribution() const;

    Vector<double> calculate_distances() const;

    Vector<size_t> balance_binary_targets_distribution(const double & = 100.0);

    Vector<size_t> balance_multiple_targets_distribution();

    Vector<size_t> unuse_most_populated_target(const size_t &);

    Vector<size_t> balance_function_regression_targets_distribution(const double & = 10.0);

    Vector<size_t> arrange_binary_inputs_indices() const;

    Vector<size_t> arrange_real_inputs_indices() const;

    void sum_binary_inputs();

    // Outlier detection
    Matrix<double> calculate_instances_distances(const size_t &) const;

    Matrix<size_t> calculate_nearest_neighbors(const Matrix<double> &, const size_t &) const;

    Vector<double> calculate_k_distances(const Matrix<double> &, const size_t &) const;

    Matrix<double> calculate_reachability_distances(const Matrix<double> &, const Vector<double> &) const;

    Vector<double> calculate_reachability_density(const Matrix<double> &, const size_t &) const;

    Vector<double> calculate_local_outlier_factor(const size_t & = 5) const;

    Vector<size_t> clean_local_outlier_factor(const size_t & = 5);

    Vector<size_t> clean_Tukey_outliers(const double & = 1.5);

    // Time series methods
    Matrix<double> calculate_autocorrelation(const size_t & = 10) const;

    Matrix<Vector<double>> calculate_cross_correlation() const;

    // Data generation
    void generate_data_function_regression(const size_t &, const size_t &);

    void generate_data_binary_classification(const size_t &, const size_t &);

    void generate_data_multiple_classification(const size_t &, const size_t &);

    // Serialization methods
    std::string to_string() const;

    void print() const;

    void print_summary() const;

    tinyxml2::XMLDocument *to_XML() const;

    void from_XML(const tinyxml2::XMLDocument &);

    void save(const std::string &) const;

    void load(const std::string &);

    void print_data() const;

    void print_data_preview() const;

    void save_data() const;

    bool has_data() const;

    // Data load methods
    void load_data();

    void load_data_binary();

    void load_time_series_data_binary();

    Vector<std::string> arrange_time_series_names(const Vector<std::string> &) const;

    Vector<std::string> arrange_autoassociation_names(const Vector<std::string> &) const;

    void convert_time_series();

    void convert_autoassociation();

    void convert_angular_variable_degrees(const size_t &);

    void convert_angular_variable_radians(const size_t &);

    void convert_angular_variables_degrees(const Vector<size_t> &);

    void convert_angular_variables_radians(const Vector<size_t> &);

    void convert_angular_variables();

    // Missing values
    void scrub_missing_values_unuse();

    void scrub_missing_values_mean();

    void scrub_input_missing_values_mean();

    void scrub_missing_values();

    // String utilities
    size_t count_tokens(std::string &) const;

    Vector<std::string> get_tokens(const std::string &) const;

    bool is_numeric(const std::string &) const;

    void trim(std::string &) const;

    std::string get_trimmed(const std::string &) const;

    std::string prepend(const std::string &, const std::string &) const;

    // Vector string utilities
    bool is_numeric(const Vector<std::string> &) const;

    bool is_not_numeric(const Vector<std::string> &) const;

    bool is_mixed(const Vector<std::string> &) const;

private:
    /// File type.
    FileType file_type;

    /// First cell.
    std::string first_cell;

    /// Last cell.
    std::string last_cell;

    /// Sheet number.
    size_t sheet_number;

    /// Data file name.
    std::string data_file_name;

    /// Header which contains variables name.
    bool header_line;

    /// Header wihch contains the rows label.
    bool rows_label;

    /// Separator character.
    Separator separator;

    /// Missing values label.
    std::string missing_values_label;

    /// Number of lags.
    size_t lags_number;

    /// Number of steps ahead
    size_t steps_ahead;

    /// Autoassociation flag.
    bool autoassociation;

    /// Learning task
    LearningTask learning_task;

    /// Indices of angular variables.
    Vector<size_t> angular_variables;

    /// Units of angular variables.
    AngularUnits angular_units;

    /// Data Matrix.
    /// The number of rows is the number of instances.
    /// The number of columns is the number of variables.
    Matrix<double> data;

    /// Time series data matrix.
    /// The number of rows is the number of instances before time series changes.
    /// The number of columns is the number of variables before time series changes.
    Matrix<double> time_series_data;

    /// Variables object (inputs and target variables).
    Variables variables;

    /// Instances  object (training, selection and testing instances).
    Instances instances;

    /// Missing values object.
    MissingValues missing_values;

    /// Display messages to screen.
    bool display;

    // METHODS
    size_t get_column_index(const Vector<Vector<std::string>> &, const size_t) const;

    void check_separator(const std::string &) const;

    size_t count_data_file_columns_number() const;

    void check_header_line();

    Vector<std::string> read_header_line() const;

    void read_instance(const std::string &, const Vector<Vector<std::string>> &, const size_t &);

    Vector<Vector<std::string>> set_from_data_file();

    void read_from_data_file(const Vector<Vector<std::string>> &);
};


}

#endif


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
