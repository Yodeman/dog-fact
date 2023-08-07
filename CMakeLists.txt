cmake_minimum_required(VERSION 3.20)

project(DogFact)
set(CMAKE_CXX_STANDARD 11)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE ALWAYS)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Werror -Wunused -Wpedantic)
endif()

#[[include(FetchContent)
FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY  https://github.com/yhirose/cpp-httplib.git
    GIT_TAG         c7ed1796a778592ae5a122287a16b1dd4770858a #v0.13.3 
    FIND_PACKAGE_ARGS NAMES httplib REQUIRED
)
FetchContent_MakeAvailable(cpp-httplib)
]]
find_package(httplib REQUIRED)
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    set(HTTPLIB_IS_USING_OPENSSL TRUE)
endif()

add_executable(dog_fact src/gen_dog_fact.cpp)

target_link_libraries(dog_fact PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>
)

target_compile_definitions(dog_fact PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
)
