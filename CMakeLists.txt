project(xml2Struct)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

set(CMAKE_BUILD_TYPE Debug)
set(tinyXml_path ./tinyxml)
#aux_source_directory(${tinyXml_path} tinyXml_Files)
set(tinyXml_Files
    ${tinyXml_path}/tinystr.cpp
    ${tinyXml_path}/tinyxml.cpp
    ${tinyXml_path}/tinyxmlerror.cpp
    ${tinyXml_path}/tinyxmlparser.cpp)
include_directories(${tinyXml_path})
add_executable(${PROJECT_NAME} ${SRC_LIST} ${tinyXml_Files})
