cls
@for  %%i in (%cd:\=,%) do @set lastDir=%%i
@set pathold=%path%
@path=d:\avr\avr8-gnu-toolchain\bin
@make depend
@make %1
@avr-size.exe main.elf
@del depend.inc
@path=%pathold%
