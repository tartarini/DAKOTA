/*  _______________________________________________________________________

    DAKOTA: Design Analysis Kit for Optimization and Terascale Applications
    Copyright (c) 2010, Sandia National Laboratories.
    This software is distributed under the GNU Lesser General Public License.
    For more information, see the README file in the top Dakota directory.
    _______________________________________________________________________ */

//- Class:	 NonDCalibration
//- Description: Base class for generic ian inference
//- Owner:       Laura Swiler
//- Checked by:
//- Version:

#ifndef NOND_CALIBRATION_H
#define NOND_CALIBRATION_H

#include "DakotaNonD.hpp"
#include "ExperimentData.hpp"

namespace Dakota {


/// 

/** This class ...  */

class NonDCalibration: public NonD
{
public:

  //
  //- Heading: Constructors and destructor
  //

  NonDCalibration(Model& model); ///< standard constructor
  ~NonDCalibration();            ///< destructor

protected:

  //
  //- Heading: Virtual function redefinitions
  //

  //void print_results(std::ostream& s);

  /// set the passed configuration variables into the model's state vars
  void set_configuration_vars(Model& model, const RealVector& x);

  //
  //- Heading: Data
  //

  /// 1 or numFunctions standard deviations
  RealVector expStdDeviations;
  /// filename from which to read experimental data; optionally
  /// configuration vars x and standard deviations sigma
  String expDataFileName;
  /// whether the data file is in annotated format
  bool expDataFileAnnotated;
  /// number of experiments to read from data file
  size_t numExperiments;
  /// number of replicates per experiment
  IntVector numReplicates;
  /// number of columns in data file which are state variables
  size_t numExpConfigVars;
  /// how many sigmas to read from the data file (1 or numFunctions)
  size_t numExpStdDeviationsRead;

  /// Container for experimental data to which to calibrate model
  ExperimentData expData;

private:

  //
  //- Heading: Member functions
  //

  /// helper function to lookup a state_type enum variable type in the
  /// array of variables_types to find its start_index into the all
  /// array
  bool find_state_index(unsigned short state_type,
			UShortMultiArrayConstView variable_types,
			std::string context_message,
			size_t& start_index);

  //
  //- Heading: Data
  //

  /// number of continuous configuration variables
  size_t continuousConfigVars;
  /// number of discrete integer configuration variables
  size_t discreteIntConfigVars;
  /// number of discrete real configuration variables
  size_t discreteRealConfigVars;
  
  /// index of configuration variables in all continuous array
  size_t continuousConfigStart;
  /// index of configuration variables in all discrete integer array
  size_t discreteIntConfigStart;
  /// index of configuration variables in all discrete real array
  size_t discreteRealConfigStart;

};

} // namespace Dakota

#endif
