### status
| [Windows][win-link]| [Ubuntu][ubuntu-link]|[MacOS][macos-link]|
|---------------|---------------|-----------------|
| ![win-badge]  | ![ubuntu-badge]      | ![macos-badge] |


[win-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AWindows "WindowsAction"
[win-badge]: https://github.com/chonlon/Widget/workflows/Windows/badge.svg  "Windows"

[ubuntu-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AUbuntu "UbuntuAction"
[ubuntu-badge]: https://github.com/chonlon/Widget/workflows/Ubuntu/badge.svg "Ubuntu"

[macos-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AMacOS "MacOSAction"
[macos-badge]: https://github.com/chonlon/Widget/workflows/MacOS/badge.svg "MacOS"


### build
qt5 required.
to build exec command:
```
mkdir build
cd build
cmake .. -DQt5_DIR=***  #(for example: -DQt5_DIR:PATH="D:/libs/qt/5.12.3/msvc2017_64/lib/cmake/Qt5")
make
```

项目没有强制指定lib以及可执行文件生成路径, 可以通过如下命令自己指定: 
-DEXECUTABLE_OUTPUT_PATH:PATH="./bin" 
-DLIBRARY_OUTPUT_PATH:PATH="./bin/lib"

### to use:
最简单的就是通过cmake的 add_subdirectory 来直接包含此项目.
另一个方式是向项目中添加此项目的 include 目录以及 链接上面生成的 LonWidgetLib.lib 文件.