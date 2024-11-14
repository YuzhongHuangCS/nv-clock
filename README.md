# nv-clock

A CLI tool for under/overclocking NVIDIA GPUs using the NVML library, without requiring an Xorg dependency.

This tool is useful when encountering instability during deep learning training—potentially due to degraded hardware—and needing to downclock the GPU (particularly VRAM) to improve stability.

Existing solutions often require `nvidia-settings`; however, this tool uses the NVML API directly, so `nvidia-settings` is not needed.
