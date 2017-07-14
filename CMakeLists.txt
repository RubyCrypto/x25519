cmake_minimum_required(VERSION 2.8.4)
project(rfc7748_precomputed C)

include_directories(./include)
link_directories(./lib)
enable_language(ASM-ATT)

set(EXECUTABLE_OUTPUT_PATH ./bin)
set(LIBRARY_OUTPUT_PATH ./lib)
set(TARGET rfc7748_precomputed)
set(SRC ./src)
set(PROJECT_FLAGS "-Wall -Wextra -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=native -mtune=native")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  ${PROJECT_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  ${PROJECT_FLAGS}")

add_library(${TARGET} STATIC
	include/random.h        ${SRC}/random.c
	include/bytes.h	        src/bytes.c
	include/table_ladder_x25519.h
	include/table_ladder_x448.h
	include/fp25519_x64.h	${SRC}/fp25519_x64.c
	include/fp448_x64.h	    ${SRC}/fp448_x64.c
	${SRC}/x25519_x64.c  	${SRC}/x448_x64.c
	include/rfc7748_precompted.h
)

add_executable(bench
	apps/bench/clocks.h
	apps/bench/clocks.c
	apps/bench/bench.h
	apps/bench/bench_fp25519_x64.c
	apps/bench/bench_fp448_x64.c
	apps/bench/bench_x25519.c
	apps/bench/bench_x448.c
	apps/bench/bench.c
)
add_executable(tests
	apps/tests/tests.h
	apps/tests/test_fp25519_x64.c
	apps/tests/test_fp448_x64.c
	apps/tests/test_x25519.c
	apps/tests/test_x448.c
	apps/tests/tests.c
)
add_executable(samples
	apps/samples/samples.c
)

target_link_libraries(bench	${TARGET})
target_link_libraries(tests ${TARGET})
target_link_libraries(samples ${TARGET})

INSTALL(TARGETS ${TARGET}
		DESTINATION "lib"
)
INSTALL(FILES include/${TARGET}.h
		DESTINATION "include"
)
