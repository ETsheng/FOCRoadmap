SET PATH=D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\java8path;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;D:\Program Files (x86)\VMware16\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;D:\Program Files (x86)\Microsoft VS Code\bin;D:\Program Files (x86)\putty\;C:\Program Files\dotnet\;C:\Program Files\Docker\Docker\resources\bin;D:\program_file\matlab2023b\runtime\win64;D:\program_file\matlab2023b\bin;;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;E:\Program_Files\miniconda;E:\Program_Files\miniconda\Library\mingw-w64\bin;E:\Program_Files\miniconda\Library\usr\bin;E:\Program_Files\miniconda\Library\bin;E:\Program_Files\miniconda\Scripts;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;;E:\Program_Files\pycharm\PyCharm Community Edition 2022.3.3\bin;;E:\Program_Files\modelsim\win64
SET ARMCC6_ASMOPT=--diag_suppress=9931
SET ARMCC6_CCOPT=--diag_suppress=9931
SET ARMCC6_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=cubemx
SET CPU_CLOCK=0x007A1200
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmAsm" --Via "cubemx\startup_stm32f103xb._ia"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\main.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\gpio.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\adc.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\tim.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_it.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_msp.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\system_stm32f1xx.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\sin_table.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\svpwm.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_gpio_ex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_adc.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_adc_ex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_rcc.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_rcc_ex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_gpio.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_dma.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_cortex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_pwr.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_flash.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_flash_ex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_exti.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_tim.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f1xx_hal_tim_ex.__i"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\ArmLink" --Via "cubemx\cubemx.lnp"
"D:\Program Files (x86)\keil_MDK537\ARM\ARMCLANG\Bin\fromelf.exe" "cubemx\cubemx.axf" --i32combined --output "cubemx\cubemx.hex"
