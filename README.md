# ESP-OS
![Logo of ESP-CF](./esp-os_logo.jpeg)
An operating system that is designed for microcontrollers. Written in C++. Successor of [Esp-cf](https://github.com/HelleBenjamin/esp-cf). It's recommended to download from [the releases](https://github.com/HelleBenjamin/esp-os/releases) and use [PuTTY](https://www.putty.org/) as a serial interface.
### The development of version 1.x.x is come to an end. Consider using version [2.x.x](https://github.com/HelleBenjamin/esp-os/tree/esp-os-2)
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
Task scheduler allows you to create and schedule tasks, with different priorities, for example, blinking an led(built-in). Task scheduler also allows you to kill tasks by pid. 
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
## Versions
Legacy versions aren't supported or maintained
- Pre-Release 1.0 (Legacy version)
- Pre-Release 1.1 (Legacy version)
- Release 1.0 (Legacy version)
- Release 1.0.1 (Legacy version)
- Release 1.1.0 (Final version of v1.x.x)
- Versions 2.x.x (Supported version)
I'm not a professional and some information or things could be wrong!
