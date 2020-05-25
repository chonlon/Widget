[TOC]



## status

| [Windows][win-link]| [Ubuntu][ubuntu-link]|[MacOS][macos-link]|
|---------------|---------------|-----------------|
| ![win-badge]  | ![ubuntu-badge]      | ![macos-badge] |


[win-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AWindows "WindowsAction"
[win-badge]: https://github.com/chonlon/Widget/workflows/Windows/badge.svg  "Windows"

[ubuntu-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AUbuntu "UbuntuAction"
[ubuntu-badge]: https://github.com/chonlon/Widget/workflows/Ubuntu/badge.svg "Ubuntu"

[macos-link]: https://github.com/chonlon/Widget/actions?query=workflow%3AMacOS "MacOSAction"
[macos-badge]: https://github.com/chonlon/Widget/workflows/MacOS/badge.svg "MacOS"

## 简介

基于Qt5的无边框窗口以及阴影窗口的粗糙封装, Qt5.15将会引入官方无边框窗口属性, 因此会对"无边框"谨慎优化.



## build

### 项目依赖

- qt5

- cmake 3.0.2

### 编译方式

**linux/macos:**

- exec command:

```shell
mkdir build
cd build
cmake .. -DQt5_DIR=***  #(for example: -DQt5_DIR:PATH="D:/libs/qt/5.12.3/msvc2017_64/lib/cmake/Qt5")
make
```



**windows:**

- exec command:

```shell
mkdir build
cd build
cmake .. -DQt5_DIR=***  #(for example: -DQt5_DIR:PATH="D:/libs/qt/5.12.3/msvc2017_64/lib/cmake/Qt5")
devenv.exe lon_widget.sln
```

- 直接使用:

  目前vs2019对cmake的支持已经做得非常不错了, 推荐使用这种方式.

  需要在cmakesettings.json里面设置Qt5_DIR以及BuildDemo选项.

**其它可选项:**

如果需要编译demo, 加上`-DBuildDemo=ON`

项目没有强制指定lib以及可执行文件生成路径, 可以通过如下命令自己指定: 

`-DEXECUTABLE_OUTPUT_PATH:PATH="./bin" `
`-DLIBRARY_OUTPUT_PATH:PATH="./bin/lib"`



## use
最简单的就是通过cmake的 add_subdirectory 来直接包含此项目.
另一个方式是向项目中添加此项目的 include 目录以及 链接上面生成的 LonWidgetLib.lib 文件.



## 引用仓库

[GSL](https://github.com/Microsoft/GSL)

[TTKWidgetTools](https://github.com/Greedysky/TTKWidgetTools)

在此感谢.