#pragma once
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

typedef enum Result
{
    NVML_SUCCESS = 0,
    NVML_ERROR_UNINITIALIZED = 1,
    NVML_ERROR_INVALID_ARGUMENT = 2,
    NVML_ERROR_NOT_SUPPORTED = 3,
    NVML_ERROR_NO_PERMISSION = 4,
    NVML_ERROR_ALREADY_INITIALIZED = 5,
    NVML_ERROR_NOT_FOUND = 6,
    NVML_ERROR_INSUFFICIENT_SIZE = 7,
    NVML_ERROR_INSUFFICIENT_POWER = 8,
    NVML_ERROR_DRIVER_NOT_LOADED = 9,
    NVML_ERROR_TIMEOUT = 10,
    NVML_ERROR_IRQ_ISSUE = 11,
    NVML_ERROR_LIBRARY_NOT_FOUND = 12,
    NVML_ERROR_FUNCTION_NOT_FOUND = 13,
    NVML_ERROR_CORRUPTED_INFOROM = 14,
    NVML_ERROR_GPU_IS_LOST = 15,
    NVML_ERROR_UNKNOWN = 999
};

enum ThermalController
{
    NVML_THERMAL_CONTROLLER_NONE = 0,
    NVML_THERMAL_CONTROLLER_GPU_INTERNAL,
    NVML_THERMAL_CONTROLLER_ADM1032,
    NVML_THERMAL_CONTROLLER_ADT7461,
    NVML_THERMAL_CONTROLLER_MAX6649,
    NVML_THERMAL_CONTROLLER_MAX1617,
    NVML_THERMAL_CONTROLLER_LM99,
    NVML_THERMAL_CONTROLLER_LM89,
    NVML_THERMAL_CONTROLLER_LM64,
    NVML_THERMAL_CONTROLLER_G781,
    NVML_THERMAL_CONTROLLER_ADT7473,
    NVML_THERMAL_CONTROLLER_SBMAX6649,
    NVML_THERMAL_CONTROLLER_VBIOSEVT,
    NVML_THERMAL_CONTROLLER_OS,
    NVML_THERMAL_CONTROLLER_NVSYSCON_CANOAS,
    NVML_THERMAL_CONTROLLER_NVSYSCON_E551,
    NVML_THERMAL_CONTROLLER_MAX6649R,
    NVML_THERMAL_CONTROLLER_ADT7473S,
    NVML_THERMAL_CONTROLLER_UNKNOWN = -1,
};

enum ThermalTarget
{
    NVML_THERMAL_TARGET_NONE          = 0,
    NVML_THERMAL_TARGET_GPU           = 1,     //!< GPU core temperature requires NvPhysicalGpuHandle
    NVML_THERMAL_TARGET_MEMORY        = 2,     //!< GPU memory temperature requires NvPhysicalGpuHandle
    NVML_THERMAL_TARGET_POWER_SUPPLY  = 4,     //!< GPU power supply temperature requires NvPhysicalGpuHandle
    NVML_THERMAL_TARGET_BOARD         = 8,     //!< GPU board ambient temperature requires NvPhysicalGpuHandle
    NVML_THERMAL_TARGET_VCD_BOARD     = 9,     //!< Visual Computing Device Board temperature requires NvVisualComputingDeviceHandle
    NVML_THERMAL_TARGET_VCD_INLET     = 10,    //!< Visual Computing Device Inlet temperature requires NvVisualComputingDeviceHandle
    NVML_THERMAL_TARGET_VCD_OUTLET    = 11,    //!< Visual Computing Device Outlet temperature requires NvVisualComputingDeviceHandle

    NVML_THERMAL_TARGET_ALL           = 15,
    NVML_THERMAL_TARGET_UNKNOWN       = -1,
};

enum TemperatureThresholdType
{
    NVML_TEMPERATURE_THRESHOLD_SHUTDOWN = 0,
    NVML_TEMPERATURE_THRESHOLD_SLOWDOWN = 1,
    NVML_TEMPERATURE_THRESHOLD_MEM_MAX = 2,
    NVML_TEMPERATURE_THRESHOLD_GPU_MAX = 3,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_MIN = 4,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_CURR = 5,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_MAX = 6,
    NVML_TEMPERATURE_THRESHOLD_GPS_CURR = 7
};

enum PerfPolicyType
{
    NVML_PERF_POLICY_POWER = 0,             //How long did power violations cause the GPU to be below application clocks.
    NVML_PERF_POLICY_THERMAL = 1,           //How long did thermal violations cause the GPU to be below application clocks.
    NVML_PERF_POLICY_SYNC_BOOST = 2,        //How long did sync boost cause the GPU to be below application clocks.
    NVML_PERF_POLICY_BOARD_LIMIT = 3,       //How long did the board limit cause the GPU to be below application clocks.
    NVML_PERF_POLICY_LOW_UTILIZATION = 4,   //Hong did low utilization cause the GPU to be below application clocks.
    NVML_PERF_POLICY_RELIABILITY = 5,       //How long did the board reliability limit cause the GPU to be below application clocks.
    NVML_PERF_POLICY_TOTAL_APP_CLOCKS = 10, //Total time the GPU was held below application clocks by any limiter (0 - 5 above).
    NVML_PERF_POLICY_TOTAL_BASE_CLOCKS = 11,
    NumPolicyTypes = 6
};

struct Sensor {
    enum ThermalController Controller;
    int DefaultMinTemp;
    int DefaultMaxTemp;
    int CurrentTemp;
    enum ThermalTarget Target;
};

struct GpuThermalSettings {
    uint32_t Count;
    struct Sensor sensors[3];
};


enum NvmlTemperatureSensors
{
    NVML_TEMPERATURE_GPU = 0
};

struct NvmlViolationTime
{
    uint64_t ReferenceTime;
    uint64_t ViolationTime;
};

struct NvmlUtilization
{
    // Percent of time over the past sample period during which one or more kernels was executing on the GPU.
    uint32_t Gpu;

    // Percent of time over the past sample period during which global (device) memory was being read or written.
    uint32_t Memory;
};

EXPORT enum Result nvmlDeviceGetCount(uint32_t *count);
EXPORT enum Result nvmlDeviceGetHandleByIndex(uint32_t index, uint64_t *device);
EXPORT enum Result nvmlDeviceGetName(uint64_t device, char *name, uint32_t length);
EXPORT enum Result nvmlDeviceGetUtilizationRates(uint64_t device, struct NvmlUtilization *utilization);
EXPORT enum Result nvmlDeviceGetViolationStatus(uint64_t device, enum PerfPolicyType policyType, struct NvmlViolationTime *violationTime);
EXPORT enum Result nvmlDeviceGetThermalSettings(uint64_t device, uint32_t sensorIndex, struct GpuThermalSettings *pThermalSettings);
EXPORT enum Result nvmlDeviceGetTemperatureThreshold(uint64_t device, enum TemperatureThresholdType thresholdType, uint32_t *temp);