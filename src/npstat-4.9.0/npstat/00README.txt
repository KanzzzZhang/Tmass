The source subdirectories are structured as follows:

interfaces -- Code that depends on the Minuit minimization package.

emsunfold  -- Code for EMS unfolding with sparse matrices. Needs Eigen
              and TRLAN.

nm         -- Some basic utilities and numerical methods.

rng        -- Generators of quasi- and pseudo-random numbers.

stat       -- Statistical data analysis and distribution modeling.

swig       -- SWIG interface files, python API generated by SWIG, and
              some additional python utilities.

wrap       -- Hand-written python interfaces to selected package functionality.

Run "doxygen doxygen.conf" in this directory to build html documentation
for the C++ API.
