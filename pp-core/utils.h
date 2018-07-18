#include <memory>

#ifndef ppcore_utils_h_included
#define ppcore_utils_h_included

/**
 * \brief Declare shared pointer type for const and non-const instances of a
 * class
 *
 * @param ClassName The name of the class; the corresponding type names will be
 * `ClassNameSpr` and `ConstClassNameSpr`
 */
#define PP_DECLARE_SHARED_POINTERS_FOR( ClassName ) \
    using ClassName##Spr = std::shared_ptr<ClassName>; \
    using Const##ClassName##Spr = std::shared_ptr<const ClassName>;

/**
 * \brief Declare unique pointer type for const and non-const instances of a
 * class
 *
 * @param ClassName The name of the class; the corresponding type names will be
 * `ClassNameUpr` and `ConstClassNameUpr`
 */
#define PP_DECLARE_UNIQUE_POINTERS_FOR( ClassName ) \
    using ClassName##Upr = std::unique_ptr<ClassName>; \
    using Const##ClassName##Upr = std::unique_ptr<const ClassName>;

/**
 * @brief Declare shared and unique pointer types corresponding to instances of
 * a given class
 *
 * @param ClassName The name of the class; corresponding type names will be
 * `ClassNameSpr`, `ConstClassNameSpr`, `ClassNameUpr` and `ConstClassNameUpr`
 */
#define PP_DECLARE_POINTERS_FOR( ClassName ) \
    PP_DECLARE_SHARED_POINTERS_FOR( ClassName ) \
    PP_DECLARE_UNIQUE_POINTERS_FOR( ClassName )

#endif // ppcore_utils_h_included
