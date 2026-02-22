cmake_minimum_required(VERSION 3.16)

project(loginSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(loginSystem
    loginSystem.cpp
    UserData.hpp
    Services/DatabaseService.hpp
    Services/AUTH/PasswordService.hpp
    Services/AUTH/AuthenticationService.hpp
    Services/AUTH/AuthorizationService.hpp
    Services/AUTH/ValidationService.hpp
    Services/AuditLogService.hpp
    Services/ConfigService.hpp
    Services/UI/UIService.hpp
    Services/UI/AdminUI.hpp
    Services/UI/EmployeeUI.hpp
    Services/UI/GuestUI.hpp
)

