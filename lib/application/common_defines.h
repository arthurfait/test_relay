/**
 * @brief Common defined for project usage
 */

#ifndef COMMON_DEFINES_H_
#define COMMON_DEFINES_H_


// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_MOVE_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;      \
    void operator=(const TypeName&) = delete; \
    TypeName(TypeName&&) = delete; \
    TypeName& operator=(TypeName&& classURef) = delete

#endif  // COMMON_DEFINES_H_
