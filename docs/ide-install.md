# Arduino IDE + ESP32 Add-on

##  Инсталиране на Arduino IDE

>Има възможности за различни операционни системи, тук проследяваме инсталацията за  Windows и *Arduino IDE 1.8*. Може да изтеглите инсталатор, архив или директно приложение за Windows, съветът ни е изолзвайте инсталатора. Изтеглете най-новата версия на [Arduino IDE](https://www.arduino.cc/en/software "линк към официалния сайт") :
![web-download-ide](img/ide-installation/web-download-ide.png "ide download")

>Следвайте инструкциите на инсталатора, ако не сте инсталира Arduino IDE на вашият компютър, инсталаторът може да поиска записване и някои  драйвери за ардуино микроконтролери, запишете ги не са излишни.

??? info "Скрийншоти"

    ![install-ide-1](img/ide-installation/install-ide-1.png "съгласяване с лиценз"){ loading=lazy }
    
    ![install-ide-2](img/ide-installation/install-ide-2.png "избиране на всички компоненти"){ loading=lazy }
    
    ![install-ide-3](img/ide-installation/install-ide-3.png "инсталационна папка"){ loading=lazy }
    
    ![install-ide-4](img/ide-installation/install-ide-4.png "инсталация"){ loading=lazy }
    
    ![drivers](img/ide-installation/Arduino_Install/drivers.PNG "допълнителни драйвери"){ loading=lazy }
    
    ![install-ide-5](img/ide-installation/install-ide-5.png){ loading=lazy }



## Инсталиране на ESP32 Add-on към Arduino IDE

>След като успешно сте инсталрали най-актуалната версия на Arduino IDE е време да запишете и добавката за контролера ESP32. 



>- избираме `File>Preferences` и в полето **Additional Boards Manager URLs** въвеждаме следния линк и потвърждаваме с бутона `[ ОК ]` 

!!! caution
	Arduino ESP32 core v2.x.x cannot be used on Windows 8.x x86 (32 bits), Windows 7 or earlier. The Windows 32 bits OS is no longer supported by this toolchain.
	
	The Arduino ESP32 v1.0.6 still works on WIN32. You might want to install python 3.8.x because it is the latest release supported by Windows 7.

``` tex
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
```

???+ info "Preferences"
	![preferences_addon](img/ide-installation/Arduino_Install/preferences_addon.PNG){ loading=lazy }

>- избираме `Tools> Board: "Arduino Uno"> Boards Manager...`, което ни отваря мениджъра на възможните контролери, в полето за търсене въвеждаме `esp32` и инсталираме най-новата версия

???+ info "Boards Manager"

	![board_manager0](img/ide-installation/Arduino_Install/board_manager0.PNG){ loading=lazy }
	
	![boards_manager_install](img/ide-installation/Arduino_Install/boards_manager_install.PNG){ loading=lazy }

## Забележки
!!! warning "Kонфигурация на Arduino IDE"
	За правилна работа с контролера, който е към развойната платка, е нужно **първо** да се избере правилния модул (Board: "ESP32 Dev Module") и **след това** да се приложат следните настройки от менюто `Tools` :
    === "Конфигурация"
        ``` 
        Board: "ESP32 Dev Module"
        Upload Speed: "921600"
        CPU Frequency: "240MHz (Wifi/BT)"
        Flash Frequency: "80 MHz"
        Flash Mode: "QIO"
        Flash Size: "4MB (32Mb)"
        Partition Scheme: "Default 4MB with spiffs (1.2MB App/1.5MB SPIFFS)"
        Code Debug Level: "None"
        PSRAM: "Disabled"
        ```
    === "Снимка"
        ![settings](img/ide-installation/Arduino_Install/settings-2.png){ loading=lazy }
    
След като сте готови с инсталацията, може да преминете към [добавяне на библиотеки](libraries.md)

## Ресурси
 - [docs.espressif.com/projects/arduino-esp32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#before-installing)