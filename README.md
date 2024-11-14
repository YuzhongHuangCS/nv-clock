# nv-clock

A CLI tool for under/overclocking NVIDIA GPUs using the NVML library, without requiring an Xorg dependency.

This tool is useful when encountering instability during deep learning training (potentially due to degraded hardware) and needing to downclock the GPU (particularly VRAM) to improve stability.

Existing solutions often require the GUI app `nvidia-settings`; however, this tool uses the NVML API directly, so no GUI or Xorg is needed.

Alternatively, you can use `nvidia-smi -i 0 -pl <tdp>` to limit power usage, but this does not allow you to directly limit the frequency.
