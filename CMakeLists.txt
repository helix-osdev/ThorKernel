cmake_minimum_required(VERSION 3.5)

project(thor_kernel LANGUAGES C ASM)

set(CMAKE_ASM_COMPILER "/usr/bin/clang")
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_LINKER "/usr/bin/clang")

set(THOR_ARCH "arm64" CACHE STRING "")

set(THOR_TARGET "kernel.elf")

set(LINKER_SCRIPT
	"${CMAKE_SOURCE_DIR}/arch/${THOR_ARCH}/thor.ld"
)


if(${THOR_ARCH} STREQUAL "arm64")
	add_executable(${THOR_TARGET})

	target_include_directories(${THOR_TARGET} PRIVATE
		"${CMAKE_SOURCE_DIR}/include"
	)

	target_compile_options(${THOR_TARGET} PRIVATE
		-target aarch64-linux-gnu
		-ffreestanding
		-fno-stack-protector
		-fno-stack-check
		-mcpu=cortex-a57
		-mgeneral-regs-only
		-Wno-unused-command-line-argument
		-fPIE
	)

	target_link_options(${THOR_TARGET} PRIVATE
		-target aarch64-linux-gnu
		-nostdlib
		-static
		-T ${LINKER_SCRIPT}
		-fuse-ld=lld
	)

	target_compile_definitions(${THOR_TARGET} PRIVATE
		-DARM64
	)
elseif(${THOR_ARCH} STREQUAL "arm")
	add_executable(${THOR_TARGET})

	target_include_directories(${THOR_TARGET} PRIVATE
		"${CMAKE_SOURCE_DIR}/include"
	)

	target_compile_options(${THOR_TARGET} PRIVATE
		-target arm-none-gnueabihf
		-ffreestanding
		-fno-stack-protector
		-fno-stack-check
		-mcpu=cortex-a15
	)

	target_link_options(${THOR_TARGET} PRIVATE
		-target arm-unknown-windows
		-nostdlib
		-T ${LINKER_SCRIPT}
		-fuse-ld=lld
	)

	target_compile_definitions(${THOR_TARGET} PRIVATE
		-DARM
	)
else()
	message(FATAL_ERROR
		"Unsupported architecture ${THOR_ARCH}"
	)
endif()



add_subdirectory(arch/${THOR_ARCH})
add_subdirectory(devices)
add_subdirectory(init)
add_subdirectory(lib)
add_subdirectory(mm)
add_subdirectory(kernel)
