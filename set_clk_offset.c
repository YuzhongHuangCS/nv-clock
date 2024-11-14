#include <nvml.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    nvmlReturn_t result;
    nvmlDevice_t device;
    unsigned int coreClockBefore, coreClockAfter;
    unsigned int memoryClockBefore, memoryClockAfter;

    // Check if the user provided an offset argument
    if (argc != 3) {
        printf("Usage: %s <core_clock_offset_MHz> <memory_clock_offset_MHz>\n", argv[0]);
        return 1;
    }

    // Convert the command line argument to an integer
    int coreClockOffsetMHz = atoi(argv[1]);
    int memoryClockOffsetMHz = atoi(argv[2]);

    // Initialize NVML
    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return 1;
    }

    // Get the first GPU device (index 0)
    result = nvmlDeviceGetHandleByIndex(0, &device);
    if (result != NVML_SUCCESS) {
        printf("Failed to get handle for device 0: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }

    // Get the current core clock before applying the offset
    result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &coreClockBefore);
    if (result != NVML_SUCCESS) {
        printf("Failed to get core clock: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Current core clock before applying offset: %u MHz\n", coreClockBefore);

    // Get the current memory clock before applying the offset
    result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_MEM, &memoryClockBefore);
    if (result != NVML_SUCCESS) {
        printf("Failed to get memory clock: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Current memory clock before applying offset: %u MHz\n", memoryClockBefore);

    // Set core clock offset
    result = nvmlDeviceSetGpcClkVfOffset(device, coreClockOffsetMHz);
    if (result != NVML_SUCCESS) {
        printf("Failed to set core clock offset: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Core clock offset set to %d MHz.\n", coreClockOffsetMHz);

    // Set the memory clock offset
    result = nvmlDeviceSetMemClkVfOffset(device, memoryClockOffsetMHz);
    if (result != NVML_SUCCESS) {
        printf("Failed to set memory clock offset: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Memory clock offset set to %d MHz.\n", memoryClockOffsetMHz);

    // Get the updated core clock after applying the offset
    result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &coreClockAfter);
    if (result != NVML_SUCCESS) {
        printf("Failed to get core clock after setting offset: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Updated core clock after applying offset: %u MHz\n", coreClockAfter);

    // Get the updated memory clock after applying the offset
    result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_MEM, &memoryClockAfter);
    if (result != NVML_SUCCESS) {
        printf("Failed to get memory clock after setting offset: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }
    printf("Updated memory clock after applying offset: %u MHz\n", memoryClockAfter);

    // Cleanup
    nvmlShutdown();
    return 0;
}
