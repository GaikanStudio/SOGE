#ifndef SOGE_INPUT_INPUTCOMPILEPREPROC_HPP
#define SOGE_INPUT_INPUTCOMPILEPREPROC_HPP

#include "SOGE/Utils/PreprocessorHelpers.hpp"


#define SOGE_REL_COMPILED_INPUT_IMPL_HEADER(Suffix) SOGE_REL_COMPILED_IMPL_HEADER(SOGE_INPUT_IMPL, Suffix)
#define SOGE_ABS_COMPILED_INPUT_IMPL_HEADER(IncludeDir, Suffix)                                                        \
    SOGE_ABS_COMPILED_IMPL_HEADER(SOGE_INPUT_IMPL, IncludeDir, Suffix)

#endif // SOGE_INPUT_INPUTCOMPILEPREPROC_HPP