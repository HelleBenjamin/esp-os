# ESP-OS
![Logo of ESP-CF](https://github.com/HelleBenjamin/esp-os/blob/main/esp-os_logo.jpeg)
An operating system that is designed for microcontrollers. Written in C++. Successor of [Esp-cf](https://github.com/HelleBenjamin/esp-cf). It's recommended to download from [the releases](https://github.com/HelleBenjamin/esp-os/releases) and use [PuTTY](https://www.putty.org/) as a serial interface.
## Compatibility
- Tested and fully working on ESP8266 and Arduino Uno R4 Wifi (Requires [Arduino-Kernel](https://github.com/HelleBenjamin/esp-os/releases/tag/v1.1.0-arduino)).
- Should work on ESP32.
- May need a modded kernel for other microcontrollers.
- Kernel and OS need to be the same version for now.
## Programs
- SysInfo: View information about the system.
- Calculator: A simple calculator.
- Direct Syscall: Execute system calls directly.
## Terminal commands
The terminal allows you to enter and execute them. See available [commands](https://github.com/HelleBenjamin/esp-os/blob/main/commands.txt).
## Task scheduler
### Task scheduler is beign developed for the Lanskern Embedded kernel
Task scheduler allows you to create and schedule tasks, with different priorities, for example, blinking an led(built-in). Task scheduler also allows you to kill tasks by pid. Current scheduler uses priority-finish scheduling. This type of scheduler executes tasks and finishes them in priority order. One of the biggest disadvantages of this scheduler is that the system becomes unresponsive when one tasks includes large or infinite loops.
### Priority map:
- 0 - Highest priority, used for critical tasks
- 1 - Very high priority, used for important tasks, for example in calculations
- 2 - High priority, used for normal tasks that require frequent use
- 3-4 - Higher than normal priority, use for less frequent tasks
- 5 - Normal priority, used for normal tasks
- 6-10 - Lower priority, used for example blinking a led
### Commands
- ``scheduler.create_task(function, period, name, priority)``
- ``scheduler.kill_task(pid)``
- ``scheduler.get_tasks()``
- ``scheduler.get_pid(name)``
- ``scheduler.execute_tasks()``
## Major update
### ESP-OS 2.0.0 includes a new kernel and other major changes
The old esp-kernel is replaced by lanskern-embeded. Lanskern-embeded is an embedded version of [Lanskern](https://github.com/HelleBenjamin/Lanskern), one of my kernel projects. Its main goal is to make os developemt cross-platform compatible without major changes. Current versions will be developed for the new kernel.

A new timer interrupt-based scheduler is being developed for the kernel. This will allows for better scheduling of tasks, which leads to better responsiveness.

Direct syscall program removed due to major changes in the kernel.

New programs and features will be added in the future.

## Versions
Legacy versions aren't supported or maintained
- Pre-Release 1.0 (Legacy version)
- Pre-Release 1.1 (Legacy version)
- Release 1.0 (Legacy version)
- Release 1.0.1 (Legacy version)
- Release 1.1.0 (Latest Stable, Recommended)
- Pre-Release 2.0.0 (New kernel, Latest)
I'm not a professional and some information or things could be wrong!