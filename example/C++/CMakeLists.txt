cmake_minimum_required(VERSION 3.10)

# vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(
	CPPKafkaTemplate
	LANGUAGES CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# kafka lib
find_package(unofficial-modern-cpp-kafka CONFIG REQUIRED)

include_directories(
        PUBLIC ${VCPKG_INSTALLED_DIR}/x64-linux/include
				PUBLIC include)

# my extentions
file(GLOB_RECURSE SRC LIST_DIRECTORIES FALSE ./src/*.cpp)
add_library(kafkaExtLib STATIC ${SRC})

# targets
add_executable(producer)
add_executable(consumer)

target_sources(producer PRIVATE ./producer.cpp)
target_sources(consumer PRIVATE ./consumer.cpp)

target_link_libraries(producer
	PUBLIC kafkaExtLib
	PRIVATE unofficial::modern-cpp-kafka::modern-cpp-kafka)
target_link_libraries(consumer
	PUBLIC kafkaExtLib
	PRIVATE unofficial::modern-cpp-kafka::modern-cpp-kafka)
