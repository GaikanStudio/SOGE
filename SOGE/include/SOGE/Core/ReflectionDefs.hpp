#ifndef SOGE_CORE_REFLECTION_DEFS_HPP
#define SOGE_CORE_REFLECTION_DEFS_HPP


namespace soge
{
    /*
    * A bunch of empty macros for automatic reflection generation.
    *
    * Does nothing in real code base. Used by external header parser
    * to get class information and then generate RTTR_REGISTRATION block
    * data from it.
    *
    * All definitions can have multiple arguments to give parser an extra meta data.
    * Please, refer to https://github.com/baszalmstra/header-parser if you need more info.
    */

    #define REFLECT_CLASS(...)
    #define REFLECT_METHOD(...)
    #define REFLECT_ENUM(...)
    #define REFLECT_FIELD(...)
    #define REFLECT_CONSTRUCTOR(...)
}

#endif // !SOGE_CORE_REFLECTION_DEFS_HPP
