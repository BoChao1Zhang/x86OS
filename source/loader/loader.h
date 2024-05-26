#ifndef LOADER_H
#define LOADER_H

#include "comm/boot_info.h"
#include "comm/types.h"



/**
 * @brief Structure representing an SMAP (System Memory Map) entry.
 */
typedef struct SMAP_entry{
    uint32_t BaseL;     /**< Lower 32 bits of the base address. */
    uint32_t BaseH;     /**< Upper 32 bits of the base address. */
    uint32_t LengthL;   /**< Lower 32 bits of the length. */
    uint32_t LengthH;   /**< Upper 32 bits of the length. */
    uint32_t Type;      /**< Type of the memory region. */
    uint32_t ACPI;      /**< ACPI (Advanced Configuration and Power Interface) information. */
} SMAP_entry_t;


#endif // LOADER_H