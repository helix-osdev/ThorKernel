#ifndef EFI_API_H
#define EFI_API_H

#include <stdint.h>
#include <stdbool.h>
#include <efi_def.h>


// Forward declaration workaround for GCC/Clang
typedef struct efi_configuration_table_t efi_configuration_table_t;
typedef struct efi_memory_descriptor_t efi_memory_descriptor_t;
typedef struct efi_time_t efi_time_t;
typedef struct efi_time_capabilities_t efi_time_capabilities_t;
typedef struct efi_runtime_services_t efi_runtime_services_t;




typedef struct {
	uint32_t	time_low;
	uint16_t	time_mid;
	uint16_t	time_and_ver;
	uint8_t		clock_seq_high;
	uint8_t		clock_seq_low;
	uint8_t		node[6];
} efi_guid_t;

typedef struct efi_configuration_table_t {
	efi_guid_t		vendor_guid;
	void			*vendor_table;
} efi_configuration_table_t;

typedef struct {
	char		signature[8];
	uint8_t		checksum;
	char		oem_id[6];
	uint8_t		revision;
	uint32_t	rsdp_address;
} efi_rsdp_t;

#define EFI_GLOBAL_VARIABLE \
	{0x8BE4DF61, 0x93CA, 0x11d2, \
	{0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C}}

#define EFI_ACPI_20_TABLE_GUID \
	{0x8868e871,0xe4f1,0x11d3, \
	{0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}}

#define ACPI_TABLE_GUID \
	{0xeb9d2d30,0x2d88,0x11d3, \
	0x9a,0x16,{0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SAL_SYSTEM_TABLE_GUID \
	{0xeb9d2d32,0x2d88,0x11d3, \
	{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS_TABLE_GUID \
	{0xeb9d2d31,0x2d88,0x11d3, \
	{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS3_TABLE_GUID \
	{0xf2fd1544, 0x9794, 0x4a2c, \
	{0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94}}

#define EFI_DTB_TABLE_GUID \
	{0xb1b621d5,0xf19c,0x41a5, \
	{0x83,0x0b,0xd9,0x15,0x2c,0x69,0xaa,0xe0}}

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} efi_memory_type_t;

#define EFI_MEMORY_UC            0x0000000000000001
#define EFI_MEMORY_WC            0x0000000000000002
#define EFI_MEMORY_WT            0x0000000000000004
#define EFI_MEMORY_WB            0x0000000000000008
#define EFI_MEMORY_UCE           0x0000000000000010

#define EFI_MEMORY_WP            0x0000000000001000
#define EFI_MEMORY_RP            0x0000000000002000
#define EFI_MEMORY_XP            0x0000000000004000
#define EFI_MEMORY_RO            0x0000000000020000

#define EFI_MEMORY_NV            0x0000000000008000
#define EFI_MEMORY_RUNTIME       0x8000000000000000

#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_SP            0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO    0x0000000000080000
#define EFI_MEMORY_ISA_VALID     0x4000000000000000
#define EFI_MEMORY_ISA_MASK      0x0FFFF00000000000

typedef struct efi_memory_descriptor_t {
	efi_memory_type_t	type;
	uint32_t			__padding;
	uint64_t			physical_start;
	uint64_t			virtual_start;
	uint64_t			number_of_pages;
	uint64_t			attributes;
} efi_memory_descriptor_t;

typedef struct {
	uint32_t					version;
	uint32_t					number_of_entries;
	uint32_t					descriptor_size;
	uint32_t					flags;
	efi_memory_descriptor_t		entry[1];
} efi_memory_attributes_table_t;

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_APPEND_WRITE 0x00000040

typedef efi_status_t
(EFI_API *efi_get_variable) (
		IN char16_t			*variable_name,
		IN efi_guid_t		*vendor_guid,
		OUT uint32_t		*attributes OPTIONAL,
		IN uint64_t			data_size,
		OUT void			*data OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_get_variable_name) (
		IN OUT uint64_t		*variable_size,
		IN OUT char16_t		*variable_name,
		IN OUT efi_guid_t	*vendor_guid
		);

typedef efi_status_t
(EFI_API *efi_set_variable) (
		IN char16_t		*variable_name,
		IN efi_guid_t	*vendor_guid,
		IN uint32_t		attributes,
		IN uint64_t		data_size,
		IN void			*data
		);

typedef efi_status_t
(EFI_API *efi_get_time) (
		OUT efi_time_t				*time,
		OUT efi_time_capabilities_t	*capabilities OPTIONAL 
		);

typedef efi_status_t
(EFI_API *efi_set_time) (
		IN efi_time_t		*time
		);

typedef efi_status_t
(EFI_API *efi_get_wakeup_time) (
		OUT bool		*enabled,
		OUT bool		*pending,
		OUT efi_time_t	*time
		);

typedef efi_status_t
(EFI_API *efi_set_wakeup_time) (
		IN bool			enabled,
		IN efi_time_t	*time OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_set_virtual_address_map) (
		IN uint64_t					map_size,
		IN uint64_t					descriptor_size,
		IN uint32_t					descriptor_version,
		IN efi_memory_descriptor_t	*virtual_map
		);

#define EFI_OPTIONAL_PTR 0x00000001

typedef efi_status_t
(EFI_API *efi_convert_pointer) (
		IN uint64_t		debug_disposition,
		IN void			**address
		);

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} efi_reset_type;

typedef efi_status_t
(EFI_API *efi_reset_system) (
		IN efi_reset_type		reset_type,
		IN efi_status_t			reset_status,
		IN uint64_t				data_size,
		IN void					*reset_data OPTIONAL
		);

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef struct efi_time_capabilities_t {
	uint32_t		resolution;
	uint32_t		accuracy;
	bool			sets_to_zero;
} efi_time_capabilities_t;

typedef struct efi_time_t {
	uint16_t	year;
	uint8_t		month;
	uint8_t		day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
	uint8_t		__padding0;
	uint32_t	nano_second;
	uint16_t	time_zone;
	uint8_t		day_light;
	uint8_t		__padding1;
} efi_time_t;

typedef struct {
	uint64_t	signature;
	uint32_t	revision;
	uint32_t	header_size;
	uint32_t	crc32;
	uint32_t	reserved;
} efi_table_header_t;

typedef struct efi_runtime_services_t  {
	efi_table_header_t		hdr;
	efi_get_time			get_time;
	efi_set_time			set_time;
	efi_get_wakeup_time		get_wakeup_time;
	efi_set_wakeup_time		set_wakeup_time;
	efi_set_virtual_address_map set_virtual_address_map;
	efi_convert_pointer		convert_pointer;
	efi_get_variable		get_variable;
	efi_get_variable_name	get_variable_name;
	efi_set_variable		set_variable;
	void					*get_next_high_monotonic_count;
	efi_reset_system		reset_system;
	void					*update_capsule;
	void					*query_capsule_capabilities;
	void					*query_variable_info;
} efi_runtime_services_t;

#endif
