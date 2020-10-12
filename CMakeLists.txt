cmake_minimum_required(VERSION 3.10)
project(labstor)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g")

include_directories(include)

##########TRACE TRANSFER METHODS TEST CASES
set(TRACE_TRANSFER_METHODS_ROOT ${CMAKE_SOURCE_DIR}/test/trace-transfer-methods)
set(TRACE_TRANSFER_EXEC ${CMAKE_CURRENT_BINARY_DIR}/trace-posix-io-exec)
set(TRACE_TRANSFER_METHODS_SH ${TRACE_TRANSFER_METHODS_ROOT}/trace-posix-io.sh)
set(PARSE_TRANSFER_METHODS_SH ${TRACE_TRANSFER_METHODS_ROOT}/parse.sh)
set(PRUNE_TRANSFER_METHODS_SH ${TRACE_TRANSFER_METHODS_ROOT}/prune.sh)
add_executable(trace-posix-io-exec ${TRACE_TRANSFER_METHODS_ROOT}/trace-posix-io.c)

set(SIZES 4K 64K 1M 10M 100M)
set(ITERS 1024 1024 100 100 10)
set(IO_TYPES buffered-write direct-write buffered-read direct-read)
set(IO_TYPE_IDS 0 1 2 3)

list(LENGTH SIZES SIZES_LEN)
math(EXPR SIZES_IDS_LAST "${SIZES_LEN} - 1")
foreach(SIZE_IDX RANGE ${SIZES_IDS_LAST})
    list(GET SIZES ${SIZE_IDX} SIZE)
    list(GET ITERS ${SIZE_IDX} ITER)

    list(LENGTH IO_TYPES IO_TYPES_LEN)
    math(EXPR IO_TYPES_IDS_LAST "${IO_TYPES_LEN} - 1")
    foreach(IO_TYPE_IDX RANGE ${IO_TYPES_IDS_LAST})
        list(GET IO_TYPES ${IO_TYPE_IDX} IO_TYPE)
        list(GET IO_TYPE_IDS ${IO_TYPE_IDX} IO_TYPE_ID)
        set(TEST_ID ${IO_TYPE}-${SIZE})
        add_custom_target(trace-${IO_TYPE}-${SIZE} COMMAND bash ${TRACE_TRANSFER_METHODS_SH} ${TEST_ID} ${TRACE_TRANSFER_EXEC} ${IO_TYPE_ID} ${SIZE} ${ITER})
        add_custom_target(parse-${IO_TYPE}-${SIZE} COMMAND bash ${PARSE_TRANSFER_METHODS_SH} ${TRACE_TRANSFER_METHODS_ROOT} ${TEST_ID})
        add_custom_target(prune-${IO_TYPE}-${SIZE} COMMAND bash ${PRUNE_TRANSFER_METHODS_SH} ${TRACE_TRANSFER_METHODS_ROOT} ${TEST_ID})
    endforeach()
endforeach()

##########TIME TRANSFER METHODS TEST CASES
set(TIME_TRANSFER_METHODS_ROOT ${CMAKE_SOURCE_DIR}/test/time-transfer-methods)
set(TIME_TRANSFER_METHODS_EXEC ${CMAKE_CURRENT_BINARY_DIR}/time-transfer-methods-exec)
set(TIME_TRANSFER_METHODS_SH ${TIME_TRANSFER_METHODS_ROOT}/time-transfer-methods.sh)
set(TIME_TRANSFER_STATS_SH ${TIME_TRANSFER_METHODS_ROOT}/stats.sh)
set(TIME_TRANSFER_STATS_PY ${TIME_TRANSFER_METHODS_ROOT}/stats.py)

######SUBMIT_BIO DRIVER
set(TIME_LINUX_DRIVER_IO_ROOT ${TIME_TRANSFER_METHODS_ROOT}/submit-bio-driver)
set(TIME_LINUX_DRIVER_IO_EXEC ${TIME_LINUX_DRIVER_IO_ROOT}/time-linux-driver-io-km.ko)
set(BUILD_LINUX_DRIVER_IO_SH ${TIME_LINUX_DRIVER_IO_ROOT}/build-linux-driver-io.sh)

add_library(time-linux-driver-io-um SHARED ${TIME_LINUX_DRIVER_IO_ROOT}/time-linux-driver-io-um.c)
target_include_directories(time-linux-driver-io-um PRIVATE ${TIME_LINUX_DRIVER_IO_ROOT})

add_executable(mount ${TIME_LINUX_DRIVER_IO_ROOT}/mount.c)
add_dependencies(mount time-linux-driver-io-um)
target_include_directories(mount PRIVATE ${TIME_LINUX_DRIVER_IO_ROOT})
target_link_libraries(mount time-linux-driver-io-um)

add_executable(verify-write ${TIME_LINUX_DRIVER_IO_ROOT}/verify-write.c)

add_custom_target(build-km COMMAND bash ${BUILD_LINUX_DRIVER_IO_SH} 1 ${TIME_LINUX_DRIVER_IO_ROOT})
add_custom_target(insert-km COMMAND sudo insmod ${TIME_LINUX_DRIVER_IO_EXEC})
add_custom_target(remove-km COMMAND sudo rmmod time_linux_driver_io_km)
add_custom_target(check-km COMMAND lsmod | grep time_linux_driver_io_km)
add_custom_target(check-klog COMMAND dmesg | grep time_linux_driver_io_km)
add_custom_target(clean-km COMMAND bash ${BUILD_LINUX_DRIVER_IO_SH} 2 ${TIME_LINUX_DRIVER_IO_ROOT})
add_custom_target(clean-klog COMMAND sudo dmesg --clear)

######GENERAL TIMER TEST
add_executable(time-transfer-methods-exec ${TIME_TRANSFER_METHODS_ROOT}/time-transfer-methods.cpp)
add_dependencies(time-transfer-methods-exec time-linux-driver-io-um)
target_include_directories(time-transfer-methods-exec PRIVATE ${TIME_LINUX_DRIVER_IO_ROOT})
target_link_libraries(time-transfer-methods-exec time-linux-driver-io-um)

set(SIZES 4K 64K 1M 10M 100M)
set(ITER 100)
set(REP 1)
foreach(SIZE ${SIZES})

    set(TEST_ID 0)
    set(INTERFACE 0)
    set(RW 0)
    set(BUFTYPE 0)
    add_custom_target(time-direct-read-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    set(TEST_ID 1)
    set(INTERFACE 0)
    set(RW 0)
    set(BUFTYPE 1)
    add_custom_target(time-direct-read-huge-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    set(TEST_ID 2)
    set(INTERFACE 1)
    set(RW 0)
    set(BUFTYPE 0)
    add_custom_target(time-bypass-read-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    set(TEST_ID 3)
    set(INTERFACE 0)
    set(RW 1)
    set(BUFTYPE 0)
    add_custom_target(time-direct-write-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    set(TEST_ID 4)
    set(INTERFACE 0)
    set(RW 1)
    set(BUFTYPE 1)
    add_custom_target(time-direct-write-huge-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    set(TEST_ID 5)
    set(INTERFACE 1)
    set(RW 1)
    set(BUFTYPE 0)
    add_custom_target(time-bypass-write-${SIZE} COMMAND bash ${TIME_TRANSFER_METHODS_SH} ${TIME_TRANSFER_METHODS_EXEC} ${TEST_ID} ${INTERFACE} ${RW} ${BUFTYPE} ${SIZE} ${ITER} ${REP})

    add_custom_target(time-transfer-stats-${SIZE} COMMAND bash ${TIME_TRANSFER_STATS_SH} ${TIME_TRANSFER_STATS_PY} ${SIZE})
endforeach()
