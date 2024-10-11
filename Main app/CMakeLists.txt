cmake_minimum_required(VERSION 3.14)

project(67788106_Main_App LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Network)

add_executable(67788106_Main_App
  main.cpp
  mainwindow.h mainwindow.cpp
  additemswidget.h additemswidget.cpp
  item.h item.cpp
  bookitem.h bookitem.cpp
  magazineitem.h magazineitem.cpp
  AbstractItemFactory.h
  itemfactory.h itemfactory.cpp
  itemlist.h itemlist.cpp
  backupitemlist.h backupitemlist.cpp
  customer.h customer.cpp
  customerlist.h customerlist.cpp
  addcustomerwidget.h addcustomerwidget.cpp
  purchaseditem.h purchaseditem.cpp
  transaction.h transaction.cpp
  transactionlist.h transactionlist.cpp
  transactionwidget.h transactionwidget.cpp
  modelclass.h modelclass.cpp
  Resources.qrc
)
target_link_libraries(67788106_Main_App Qt${QT_VERSION_MAJOR}::Widgets Qt6::Xml Qt6::Network)

install(TARGETS 67788106_Main_App
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
